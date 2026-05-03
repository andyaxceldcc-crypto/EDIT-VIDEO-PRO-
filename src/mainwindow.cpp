#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QFileDialog>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QToolBar>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMessageBox>
#include "subscriptionmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), isSubscribed(false)
{
    setWindowTitle("Filmora Editor Pro - Video Editing Suite");
    setWindowIcon(QIcon(":/icons/app_icon.png"));
    setGeometry(100, 100, 1600, 900);
    
    setupUI();
    createMenuBar();
    createToolbars();
    createStatusBar();
    connectSignals();
    checkSubscriptionOnStartup();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // Layout principal
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    
    // Panel izquierdo: proyecto y archivos
    QVBoxLayout *leftLayout = new QVBoxLayout();
    QLabel *projectLabel = new QLabel("Proyecto");
    projectLabel->setStyleSheet("font-weight: bold; color: #ffffff;");
    effectsList = new QListWidget();
    effectsList->setMaximumWidth(250);
    leftLayout->addWidget(projectLabel);
    leftLayout->addWidget(effectsList);
    
    // Panel central: preview y timeline
    QVBoxLayout *centerLayout = new QVBoxLayout();
    
    // Preview
    previewLabel = new QLabel();
    previewLabel->setStyleSheet("background-color: #000000; border: 1px solid #444;");
    previewLabel->setMinimumHeight(400);
    previewLabel->setAlignment(Qt::AlignCenter);
    previewLabel->setText("Preview - Video aquí");
    centerLayout->addWidget(previewLabel, 3);
    
    // Timeline
    timeline = new VideoTimeline();
    centerLayout->addWidget(timeline, 2);
    
    // Controles de reproducción
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    playButton = new QPushButton("▶ Play");
    pauseButton = new QPushButton("⏸ Pause");
    timeSlider = new QSlider(Qt::Horizontal);
    timeLabel = new QLabel("00:00 / 00:00");
    
    controlsLayout->addWidget(playButton);
    controlsLayout->addWidget(pauseButton);
    controlsLayout->addWidget(timeSlider, 1);
    controlsLayout->addWidget(timeLabel);
    
    centerLayout->addLayout(controlsLayout);
    
    // Panel derecho: efectos y transiciones
    QVBoxLayout *rightLayout = new QVBoxLayout();
    QLabel *effectsLabel = new QLabel("Efectos");
    effectsLabel->setStyleSheet("font-weight: bold; color: #ffffff;");
    addEffectButton = new QPushButton("+ Agregar Efecto");
    transitionsList = new QListWidget();
    transitionsList->setMaximumWidth(250);
    
    QLabel *transitionsLabel = new QLabel("Transiciones");
    transitionsLabel->setStyleSheet("font-weight: bold; color: #ffffff;");
    addTransitionButton = new QPushButton("+ Agregar Transición");
    
    rightLayout->addWidget(effectsLabel);
    rightLayout->addWidget(addEffectButton);
    rightLayout->addWidget(transitionsList, 1);
    rightLayout->addWidget(transitionsLabel);
    rightLayout->addWidget(addTransitionButton);
    
    // Splitter para resize
    QWidget *leftWidget = new QWidget();
    leftWidget->setLayout(leftLayout);
    
    QWidget *centerWidget = new QWidget();
    centerWidget->setLayout(centerLayout);
    
    QWidget *rightWidget = new QWidget();
    rightWidget->setLayout(rightLayout);
    
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(leftWidget);
    splitter->addWidget(centerWidget);
    splitter->addWidget(rightWidget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);
    splitter->setStretchFactor(2, 1);
    
    mainLayout->addWidget(splitter);
    
    // Estilo oscuro
    centralWidget->setStyleSheet(
        "QMainWindow { background-color: #1e1e1e; color: #e0e0e0; }"
        "QLabel { color: #e0e0e0; }"
        "QPushButton { background-color: #0066cc; color: white; border: none; padding: 6px; border-radius: 3px; }"
        "QPushButton:hover { background-color: #0052a3; }"
        "QSlider { background-color: #2d2d2d; }"
        "QListWidget { background-color: #2d2d2d; color: #e0e0e0; border: 1px solid #444; }"
    );
}

void MainWindow::createMenuBar()
{
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    
    // Menú Archivo
    QMenu *fileMenu = menuBar->addMenu("Archivo");
    QAction *newProject = fileMenu->addAction("Nuevo Proyecto");
    QAction *openProject = fileMenu->addAction("Abrir Proyecto");
    QAction *saveProject = fileMenu->addAction("Guardar Proyecto");
    fileMenu->addSeparator();
    QAction *importVideo = fileMenu->addAction("Importar Video");
    QAction *exportVideo = fileMenu->addAction("Exportar Video");
    fileMenu->addSeparator();
    QAction *exit = fileMenu->addAction("Salir");
    
    // Menú Edición
    QMenu *editMenu = menuBar->addMenu("Edición");
    editMenu->addAction("Deshacer");
    editMenu->addAction("Rehacer");
    editMenu->addSeparator();
    editMenu->addAction("Cortar");
    editMenu->addAction("Copiar");
    editMenu->addAction("Pegar");
    
    // Menú Suscripción
    QMenu *subscriptionMenu = menuBar->addMenu("Suscripción");
    subscriptionStatus = new QLabel("Estado: Sin suscripción");
    subscriptionButton = new QPushButton("Comprar Suscripción ($100/mes)");
    QAction *subAction = subscriptionMenu->addAction("Plan Premium");
    
    // Menú Ayuda
    QMenu *helpMenu = menuBar->addMenu("Ayuda");
    helpMenu->addAction("Acerca de");
    helpMenu->addAction("Documentación");
    
    connect(importVideo, &QAction::triggered, this, &MainWindow::onImportVideo);
    connect(exportVideo, &QAction::triggered, this, &MainWindow::onExportVideo);
    connect(exit, &QAction::triggered, this, &QWidget::close);
    connect(subAction, &QAction::triggered, this, &MainWindow::onSubscription);
}

void MainWindow::createToolbars()
{
    QToolBar *mainToolbar = addToolBar("Principal");
    
    importButton = new QPushButton("📁 Importar");
    exportButton = new QPushButton("💾 Exportar");
    subscriptionButton = new QPushButton("⭐ Premium ($100/mes)");
    
    mainToolbar->addWidget(importButton);
    mainToolbar->addWidget(exportButton);
    mainToolbar->addSeparator();
    mainToolbar->addWidget(subscriptionButton);
    
    connect(importButton, &QPushButton::clicked, this, &MainWindow::onImportVideo);
    connect(exportButton, &QPushButton::clicked, this, &MainWindow::onExportVideo);
    connect(subscriptionButton, &QPushButton::clicked, this, &MainWindow::onSubscription);
}

void MainWindow::createStatusBar()
{
    subscriptionStatus = new QLabel("Estado: Sin suscripción");
    statusBar()->addWidget(subscriptionStatus);
}

void MainWindow::connectSignals()
{
    connect(playButton, &QPushButton::clicked, this, &MainWindow::onPlayPause);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::onPlayPause);
    connect(addEffectButton, &QPushButton::clicked, this, &MainWindow::onAddEffect);
    connect(addTransitionButton, &QPushButton::clicked, this, &MainWindow::onAddTransition);
    connect(timeline, &VideoTimeline::timeClicked, this, &MainWindow::onTimelineClicked);
}

void MainWindow::onImportVideo()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        "Importar Video", "",
        "Archivos de Video (*.mp4 *.avi *.mov *.mkv);;Todos los archivos (*)");
    
    if (!fileName.isEmpty()) {
        currentProjectPath = fileName;
        statusBar()->showMessage("Video importado: " + fileName);
        videoEditor = new VideoEditor();
        videoEditor->loadVideo(fileName);
    }
}

void MainWindow::onExportVideo()
{
    if (!isSubscribed) {
        QMessageBox::warning(this, "Suscripción Requerida",
            "Debes tener una suscripción activa para exportar videos.\n"
            "Precio: $100/mes");
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(this,
        "Exportar Video", "",
        "MP4 (*.mp4);;AVI (*.avi);;MOV (*.mov)");
    
    if (!fileName.isEmpty()) {
        statusBar()->showMessage("Exportando: " + fileName);
    }
}

void MainWindow::onPlayPause()
{
    statusBar()->showMessage("Reproduciendo...");
}

void MainWindow::onSubscription()
{
    if (isSubscribed) {
        QMessageBox::information(this, "Suscripción",
            "Ya tienes suscripción activa.\n"
            "Vencimiento: " + QDate::currentDate().addMonths(1).toString());
        return;
    }
    
    int reply = QMessageBox::question(this, "Plan Premium",
        "Suscripción Filmora Pro\n"
        "Precio: $100/mes\n\n"
        "Características incluidas:\n"
        "- Exportación sin límite\n"
        "- +500 efectos profesionales\n"
        "- Transiciones avanzadas\n"
        "- Soporte prioritario\n"
        "- Uso comercial\n\n"
        "¿Deseas suscribirte?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        PaymentManager payment;
        if (payment.processPayment(100.0)) {
            isSubscribed = true;
            subscriptionStatus->setText("Estado: Premium (válido hasta " + 
                QDate::currentDate().addMonths(1).toString() + ")");
            subscriptionButton->setText("✓ Premium Activo");
            subscriptionButton->setEnabled(false);
            QMessageBox::information(this, "Éxito", "¡Suscripción activada!");
        }
    }
}

void MainWindow::onAddEffect()
{
    QMessageBox::information(this, "Efectos", "Selecciona un efecto:\n- Desenfoque\n- Brillo\n- Contraste\n- Sepia");
}

void MainWindow::onAddTransition()
{
    QMessageBox::information(this, "Transiciones", "Selecciona una transición:\n- Fade\n- Slide\n- Zoom\n- Dissolve");
}

void MainWindow::onTimelineClicked(double time)
{
    statusBar()->showMessage("Posición: " + QString::number(time) + "s");
}

void MainWindow::onPositionChanged(qint64 position)
{
}

void MainWindow::onDurationChanged(qint64 duration)
{
}

void MainWindow::onSubscriptionExpired()
{
    isSubscribed = false;
    subscriptionStatus->setText("Estado: Suscripción expirada");
    QMessageBox::warning(this, "Suscripción Expirada", 
        "Tu suscripción ha vencido. Renuévala para continuar usando todas las características.");
}

void MainWindow::checkSubscriptionOnStartup()
{
    SubscriptionManager subManager;
    isSubscribed = subManager.isSubscriptionActive();
    
    if (isSubscribed) {
        subscriptionStatus->setText("Estado: Premium Activo");
        subscriptionButton->setText("✓ Premium Activo");
    }
}
