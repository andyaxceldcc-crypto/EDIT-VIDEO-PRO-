#include "dark_theme.h"

QString DarkTheme::getStyleSheet()
{
    return R"(
        QMainWindow {
            background-color: #1a1a1a;
            color: #e0e0e0;
        }

        QMenuBar {
            background-color: #252525;
            color: #e0e0e0;
            border-bottom: 1px solid #1a1a1a;
        }

        QMenuBar::item:selected {
            background-color: #ff9d00;
            color: #1a1a1a;
        }

        QMenu {
            background-color: #252525;
            color: #e0e0e0;
            border: 1px solid #1a1a1a;
        }

        QMenu::item:selected {
            background-color: #ff9d00;
            color: #1a1a1a;
        }

        QDockWidget {
            background-color: #1a1a1a;
            color: #e0e0e0;
            border: 1px solid #252525;
        }

        QDockWidget::title {
            background-color: #252525;
            padding: 5px;
            border-bottom: 1px solid #1a1a1a;
        }

        QScrollBar:vertical {
            background-color: #2d2d2d;
            width: 12px;
        }

        QScrollBar::handle:vertical {
            background-color: #555555;
            border-radius: 6px;
        }

        QScrollBar::handle:vertical:hover {
            background-color: #666666;
        }

        QPushButton {
            background-color: #2d2d2d;
            color: #e0e0e0;
            border: 1px solid #555555;
            padding: 5px 15px;
            border-radius: 3px;
        }

        QPushButton:hover {
            background-color: #3d3d3d;
            border: 1px solid #ff9d00;
        }

        QPushButton:pressed {
            background-color: #1a1a1a;
        }

        QLineEdit, QTextEdit {
            background-color: #2d2d2d;
            color: #e0e0e0;
            border: 1px solid #555555;
            padding: 3px;
            border-radius: 3px;
        }

        QLineEdit:focus, QTextEdit:focus {
            border: 1px solid #ff9d00;
        }

        QLabel {
            color: #e0e0e0;
        }

        QSpinBox, QDoubleSpinBox {
            background-color: #2d2d2d;
            color: #e0e0e0;
            border: 1px solid #555555;
            padding: 3px;
        }

        QComboBox {
            background-color: #2d2d2d;
            color: #e0e0e0;
            border: 1px solid #555555;
            padding: 3px;
        }

        QSlider::groove:horizontal {
            background-color: #2d2d2d;
            border: 1px solid #555555;
            height: 6px;
        }

        QSlider::handle:horizontal {
            background-color: #ff9d00;
            width: 14px;
            margin: -4px 0;
            border-radius: 7px;
        }

        QHeaderView::section {
            background-color: #252525;
            color: #e0e0e0;
            padding: 3px;
            border: none;
            border-right: 1px solid #1a1a1a;
        }

        QTableWidget, QTreeWidget {
            background-color: #1a1a1a;
            alternate-background-color: #252525;
            color: #e0e0e0;
            gridline-color: #2d2d2d;
        }
    )";
}

QString DarkTheme::getNodeGraphStyleSheet()
{
    return R"(
        QGraphicsView {
            background-color: #1f1f1f;
            border: none;
        }
    )";
}

QString DarkTheme::getViewerStyleSheet()
{
    return R"(
        QOpenGLWidget {
            background-color: #000000;
        }
    )";
}
