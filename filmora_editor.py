import sys
import json
from datetime import datetime, timedelta
from PyQt6.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout, 
                             QHBoxLayout, QSplitter, QLabel, QPushButton, 
                             QListWidget, QListWidgetItem, QSlider, QFileDialog,
                             QMessageBox, QMenuBar, QMenu, QStatusBar, QToolBar,
                             QDialog, QLineEdit, QFormLayout)
from PyQt6.QtCore import Qt, pyqtSignal, QTimer, QSize
from PyQt6.QtGui import QColor, QFont, QIcon
from PyQt6.QtMultimedia import QMediaPlayer, QAudioOutput
from PyQt6.QtCore import QUrl

class TimelineWidget(QWidget):
    timeClicked = pyqtSignal(float)
    
    def __init__(self):
        super().__init__()
        self.clips = []
        self.current_time = 0
        self.zoom_level = 1.0
        self.setStyleSheet("background-color: #1a1a1a; border: 1px solid #444;")
        self.setMinimumHeight(150)
    
    def add_clip(self, filename, start_time, duration):
        self.clips.append({
            'filename': filename,
            'start_time': start_time,
            'duration': duration
        })
        self.update()
    
    def mousePressEvent(self, event):
        if self.width() > 0:
            self.current_time = (event.x() / self.width()) * 60
            self.timeClicked.emit(self.current_time)
            self.update()
    
    def wheelEvent(self, event):
        if event.angleDelta().y() > 0:
            self.zoom_level *= 1.2
        else:
            self.zoom_level /= 1.2
        
        self.zoom_level = max(0.5, min(5.0, self.zoom_level))
        self.update()

class PaymentDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Plan Premium - $100/mes")
        self.setGeometry(200, 200, 450, 400)
        self.setStyleSheet("""
            QDialog { background-color: #2d2d2d; }
            QLabel { color: #e0e0e0; }
            QLineEdit { background-color: #1e1e1e; color: #e0e0e0; border: 1px solid #444; padding: 5px; }
            QPushButton { background-color: #0066cc; color: white; padding: 8px; border-radius: 3px; }
            QPushButton:hover { background-color: #0052a3; }
        """)
        
        layout = QFormLayout()
        
        title = QLabel("Suscripción Filmora Pro")
        title.setFont(QFont("Arial", 14, QFont.Weight.Bold))
        layout.addRow(title)
        
        features = QLabel(
            "✓ Exportación sin límites\n"
            "✓ +500 efectos profesionales\n"
            "✓ Transiciones avanzadas\n"
            "✓ Soporte prioritario\n"
            "✓ Uso comercial"
        )
        layout.addRow(features)
        
        price = QLabel("Precio: $100/mes")
        price.setFont(QFont("Arial", 12, QFont.Weight.Bold))
        price.setStyleSheet("color: #00ff00;")
        layout.addRow(price)
        
        layout.addRow(QLabel(""))
        layout.addRow(QLabel("Número de Tarjeta:"))
        self.card_input = QLineEdit()
        self.card_input.setPlaceholderText("1234 5678 9012 3456")
        layout.addRow(self.card_input)
        
        layout.addRow(QLabel("CVV:"))
        self.cvv_input = QLineEdit()
        self.cvv_input.setPlaceholderText("123")
        layout.addRow(self.cvv_input)
        
        button_layout = QHBoxLayout()
        subscribe_btn = QPushButton("Suscribirse")
        cancel_btn = QPushButton("Cancelar")
        
        subscribe_btn.clicked.connect(self.accept)
        cancel_btn.clicked.connect(self.reject)
        
        button_layout.addWidget(subscribe_btn)
        button_layout.addWidget(cancel_btn)
        layout.addRow(button_layout)
        
        self.setLayout(layout)

class FilmoraEditor(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Filmora Editor Pro - Video Editing Suite")
        self.setGeometry(100, 100, 1600, 900)
        self.setStyleSheet("""
            QMainWindow { background-color: #1e1e1e; }
            QLabel { color: #e0e0e0; }
            QPushButton { 
                background-color: #0066cc; 
                color: white; 
                border: none; 
                padding: 8px 16px; 
                border-radius: 4px;
                font-weight: bold;
            }
            QPushButton:hover { background-color: #0052a3; }
            QPushButton:pressed { background-color: #003d7a; }
            QSlider { background-color: #2d2d2d; }
            QListWidget { background-color: #2d2d2d; color: #e0e0e0; border: 1px solid #444; }
            QMenuBar { background-color: #2d2d2d; color: #e0e0e0; border-bottom: 1px solid #444; }
            QMenu { background-color: #2d2d2d; color: #e0e0e0; }
            QMenu::item:selected { background-color: #0066cc; }
        """)
        
        self.is_subscribed = False
        self.current_project = ""
        self.subscription_expiry = None
        self.load_subscription_data()
        
        self.setup_ui()
        self.create_menu_bar()
        self.create_toolbars()
        self.create_status_bar()
        self.connect_signals()

    def setup_ui(self):
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        
        main_layout = QHBoxLayout(central_widget)
        
        # Panel izquierdo: Archivos
        left_layout = QVBoxLayout()
        left_label = QLabel("Archivos")
        left_label.setFont(QFont("Arial", 10, QFont.Weight.Bold))
        left_label.setStyleSheet("color: #ffffff;")
        self.files_list = QListWidget()
        left_layout.addWidget(left_label)
        left_layout.addWidget(self.files_list)
        
        # Panel central: Preview y Timeline
        center_layout = QVBoxLayout()
        
        # Preview
        self.preview_label = QLabel("Preview - Haz clic para importar video")
        self.preview_label.setStyleSheet("background-color: #000000; border: 2px solid #444;")
        self.preview_label.setMinimumHeight(400)
        self.preview_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.preview_label.setStyleSheet("background-color: #000000; color: #666; font-size: 14px; border: 2px solid #444;")
        center_layout.addWidget(self.preview_label, 3)
        
        # Timeline
        self.timeline = TimelineWidget()
        center_layout.addWidget(self.timeline, 2)
        
        # Controles de reproducción
        controls_layout = QHBoxLayout()
        self.play_btn = QPushButton("▶ Play")
        self.pause_btn = QPushButton("⏸ Pause")
        self.time_slider = QSlider(Qt.Orientation.Horizontal)
        self.time_label = QLabel("00:00 / 00:00")
        self.time_label.setStyleSheet("color: #e0e0e0; min-width: 80px;")
        
        controls_layout.addWidget(self.play_btn)
        controls_layout.addWidget(self.pause_btn)
        controls_layout.addWidget(self.time_slider, 1)
        controls_layout.addWidget(self.time_label)
        
        center_layout.addLayout(controls_layout)
        
        # Panel derecho: Efectos
        right_layout = QVBoxLayout()
        
        effects_label = QLabel("Efectos")
        effects_label.setFont(QFont("Arial", 10, QFont.Weight.Bold))
        effects_label.setStyleSheet("color: #ffffff;")
        
        self.add_effect_btn = QPushButton("+ Agregar Efecto")
        self.effects_list = QListWidget()
        
        # Agregar algunos efectos de ejemplo
        efectos = ["Brillo", "Contraste", "Saturación", "Desenfoque", "Sepia", "Escala de Grises"]
        for efecto in efectos:
            item = QListWidgetItem(efecto)
            self.effects_list.addItem(item)
        
        right_layout.addWidget(effects_label)
        right_layout.addWidget(self.add_effect_btn)
        right_layout.addWidget(self.effects_list)
        
        # Crear splitter
        left_widget = QWidget()
        left_widget.setLayout(left_layout)
        left_widget.setMaximumWidth(250)
        
        center_widget = QWidget()
        center_widget.setLayout(center_layout)
        
        right_widget = QWidget()
        right_widget.setLayout(right_layout)
        right_widget.setMaximumWidth(250)
        
        splitter = QSplitter(Qt.Orientation.Horizontal)
        splitter.addWidget(left_widget)
        splitter.addWidget(center_widget)
        splitter.addWidget(right_widget)
        splitter.setStretchFactor(0, 1)
        splitter.setStretchFactor(1, 2)
        splitter.setStretchFactor(2, 1)
        
        main_layout.addWidget(splitter)

    def create_menu_bar(self):
        menubar = self.menuBar()
        
        # Menú Archivo
        file_menu = menubar.addMenu("Archivo")
        file_menu.addAction("Nuevo Proyecto", self.new_project)
        file_menu.addAction("Abrir Proyecto", self.open_project)
        file_menu.addAction("Guardar Proyecto", self.save_project)
        file_menu.addSeparator()
        file_menu.addAction("Importar Video", self.import_video)
        file_menu.addAction("Exportar Video", self.export_video)
        file_menu.addSeparator()
        file_menu.addAction("Salir", self.close)
        
        # Menú Edición
        edit_menu = menubar.addMenu("Edición")
        edit_menu.addAction("Deshacer")
        edit_menu.addAction("Rehacer")
        edit_menu.addSeparator()
        edit_menu.addAction("Cortar")
        edit_menu.addAction("Copiar")
        edit_menu.addAction("Pegar")
        
        # Menú Suscripción
        sub_menu = menubar.addMenu("Suscripción")
        sub_menu.addAction("Plan Premium ($100/mes)", self.show_subscription)
        
        # Menú Ayuda
        help_menu = menubar.addMenu("Ayuda")
        help_menu.addAction("Acerca de", self.show_about)

    def create_toolbars(self):
        toolbar = self.addToolBar("Principal")
        toolbar.setIconSize(QSize(24, 24))
        
        self.import_btn = toolbar.addAction("📁 Importar")
        self.export_btn = toolbar.addAction("💾 Exportar")
        toolbar.addSeparator()
        self.subscription_btn = toolbar.addAction("⭐ Premium")
        
        self.import_btn.triggered.connect(self.import_video)
        self.export_btn.triggered.connect(self.export_video)
        self.subscription_btn.triggered.connect(self.show_subscription)

    def create_status_bar(self):
        self.status_label = QLabel("Estado: Sin suscripción")
        self.statusBar().addWidget(self.status_label)
        self.update_subscription_status()

    def connect_signals(self):
        self.play_btn.clicked.connect(self.on_play)
        self.pause_btn.clicked.connect(self.on_pause)
        self.add_effect_btn.clicked.connect(self.add_effect)
        self.timeline.timeClicked.connect(self.on_timeline_clicked)

    def import_video(self):
        file_path, _ = QFileDialog.getOpenFileName(
            self, 
            "Importar Video", 
            "", 
            "Archivos de Video (*.mp4 *.avi *.mov *.mkv);;Todos los archivos (*)"
        )
        
        if file_path:
            self.current_project = file_path
            self.preview_label.setText(f"Video cargado: {file_path.split('/')[-1]}")
            self.statusBar().showMessage(f"Video importado: {file_path}")
            
            item = QListWidgetItem(file_path.split('/')[-1])
            self.files_list.addItem(item)
            
            self.timeline.add_clip(file_path, 0, 60)

    def export_video(self):
        if not self.is_subscribed:
            QMessageBox.warning(self, "Suscripción Requerida",
                "Debes tener una suscripción activa para exportar videos.\n\n"
                "Precio: $100/mes\n"
                "✓ Exportación sin límites\n"
                "✓ +500 efectos\n"
                "✓ Uso comercial")
            return
        
        file_path, _ = QFileDialog.getSaveFileName(
            self,
            "Exportar Video",
            "",
            "MP4 (*.mp4);;AVI (*.avi);;MOV (*.mov)"
        )
        
        if file_path:
            self.statusBar().showMessage(f"Exportando: {file_path}")
            QMessageBox.information(self, "Exportación", "¡Video exportado exitosamente!")

    def new_project(self):
        self.current_project = ""
        self.files_list.clear()
        self.timeline.clips.clear()
        self.preview_label.setText("Preview - Nuevo proyecto")

    def open_project(self):
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Abrir Proyecto",
            "",
            "Proyectos Filmora (*.fproj);;Todos los archivos (*)"
        )
        
        if file_path:
            self.current_project = file_path
            self.statusBar().showMessage(f"Proyecto abierto: {file_path}")

    def save_project(self):
        if not self.current_project:
            file_path, _ = QFileDialog.getSaveFileName(
                self,
                "Guardar Proyecto",
                "",
                "Proyectos Filmora (*.fproj)"
            )
            if file_path:
                self.current_project = file_path
        
        if self.current_project:
            project_data = {
                "clips": self.timeline.clips,
                "timestamp": datetime.now().isoformat()
            }
            
            with open(self.current_project, 'w') as f:
                json.dump(project_data, f)
            
            self.statusBar().showMessage(f"Proyecto guardado: {self.current_project}")

    def show_subscription(self):
        if self.is_subscribed:
            expires = self.subscription_expiry.strftime("%d/%m/%Y")
            QMessageBox.information(self, "Suscripción Activa",
                f"Plan Premium Activo\n\n"
                f"Vencimiento: {expires}\n"
                f"Días restantes: {(self.subscription_expiry - datetime.now()).days}")
            return
        
        dialog = PaymentDialog(self)
        if dialog.exec() == QDialog.DialogCode.Accepted:
            card = dialog.card_input.text()
            cvv = dialog.cvv_input.text()
            
            if len(card) >= 13 and len(cvv) >= 3:
                self.activate_subscription()
                QMessageBox.information(self, "Éxito",
                    "¡Suscripción activada exitosamente!\n\n"
                    "Disfrutarás de acceso completo durante 30 días.")
            else:
                QMessageBox.warning(self, "Error", "Datos de tarjeta inválidos")

    def activate_subscription(self):
        self.is_subscribed = True
        self.subscription_expiry = datetime.now() + timedelta(days=30)
        self.save_subscription_data()
        self.update_subscription_status()
        self.subscription_btn.setText("✓ Premium Activo")

    def update_subscription_status(self):
        if self.is_subscribed and self.subscription_expiry:
            if datetime.now() < self.subscription_expiry:
                days = (self.subscription_expiry - datetime.now()).days
                self.status_label.setText(f"Estado: Premium Activo ({days} días)")
                self.subscription_btn.setText("✓ Premium Activo")
            else:
                self.is_subscribed = False
                self.save_subscription_data()
                self.status_label.setText("Estado: Sin suscripción")
        else:
            self.status_label.setText("Estado: Sin suscripción")

    def save_subscription_data(self):
        data = {
            "is_subscribed": self.is_subscribed,
            "expiry_date": self.subscription_expiry.isoformat() if self.subscription_expiry else None
        }
        with open("subscription.json", 'w') as f:
            json.dump(data, f)

    def load_subscription_data(self):
        try:
            with open("subscription.json", 'r') as f:
                data = json.load(f)
                self.is_subscribed = data.get("is_subscribed", False)
                expiry_str = data.get("expiry_date")
                if expiry_str:
                    self.subscription_expiry = datetime.fromisoformat(expiry_str)
        except FileNotFoundError:
            pass

    def on_play(self):
        self.statusBar().showMessage("Reproduciendo...")

    def on_pause(self):
        self.statusBar().showMessage("Pausa")

    def add_effect(self):
        QMessageBox.information(self, "Agregar Efecto",
            "Selecciona un efecto de la lista derecha")

    def on_timeline_clicked(self, time):
        minutes = int(time) // 60
        seconds = int(time) % 60
        self.time_label.setText(f"{minutes:02d}:{seconds:02d} / 01:00")

    def show_about(self):
        QMessageBox.about(self, "Acerca de Filmora Editor Pro",
            "Filmora Editor Pro v1.0\n\n"
            "Editor de video profesional con suscripción\n"
            "Precio: $100/mes\n\n"
            "Características:\n"
            "✓ Timeline interactivo\n"
            "✓ +50 efectos profesionales\n"
            "✓ Transiciones suaves\n"
            "✓ Exportación 4K\n"
            "✓ Gestión de proyectos\n\n"
            "© 2026 Filmora Editor Pro")

def main():
    app = QApplication(sys.argv)
    editor = FilmoraEditor()
    editor.show()
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
