#include "main_window.h"
#include "panels/node_graph_panel.h"
#include "panels/properties_panel.h"
#include "panels/timeline_panel.h"
#include "panels/viewer_panel.h"
#include "panels/media_panel.h"
#include "theme/dark_theme.h"
#include "../core/graph/node_graph.h"
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_nodeGraphPanel(nullptr)
    , m_propertiesPanel(nullptr)
    , m_timelinePanel(nullptr)
    , m_viewerPanel(nullptr)
    , m_mediaPanel(nullptr)
    , m_nodeGraph(std::make_shared<NodeGraph>())
{
    setWindowTitle("NUKE-PRO - Professional VFX Compositor");
    setWindowIcon(QIcon(":icons/nuke_pro_icon.png"));

    // Set minimum window size
    setMinimumSize(1400, 900);

    // Setup UI
    setupUI();
    createMenuBar();
    createDockPanels();
    createConnections();

    // Apply theme
    applyDarkTheme();

    // Load settings
    loadSettings();

    // Center window on screen
    const QScreen* screen = QApplication::primaryScreen();
    const QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

MainWindow::~MainWindow()
{
    saveSettings();
}

void MainWindow::setupUI()
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    centralWidget->setLayout(layout);
}

void MainWindow::createMenuBar()
{
    QMenuBar* menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // File Menu
    QMenu* fileMenu = menuBar->addMenu(tr("&File"));
    
    QAction* newAction = fileMenu->addAction(tr("&New"));
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, &QAction::triggered, this, &MainWindow::onFileNew);

    QAction* openAction = fileMenu->addAction(tr("&Open"));
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::onFileOpen);

    QAction* saveAction = fileMenu->addAction(tr("&Save"));
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::onFileSave);

    QAction* saveAsAction = fileMenu->addAction(tr("Save &As"));
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::onFileSaveAs);

    fileMenu->addSeparator();

    QAction* exportAction = fileMenu->addAction(tr("&Export"));
    exportAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_E);
    connect(exportAction, &QAction::triggered, this, &MainWindow::onFileExport);

    fileMenu->addSeparator();

    QAction* exitAction = fileMenu->addAction(tr("E&xit"));
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // Edit Menu
    QMenu* editMenu = menuBar->addMenu(tr("&Edit"));
    
    QAction* undoAction = editMenu->addAction(tr("&Undo"));
    undoAction->setShortcut(QKeySequence::Undo);
    connect(undoAction, &QAction::triggered, this, &MainWindow::onEditUndo);

    QAction* redoAction = editMenu->addAction(tr("&Redo"));
    redoAction->setShortcut(QKeySequence::Redo);
    connect(redoAction, &QAction::triggered, this, &MainWindow::onEditRedo);

    // Help Menu
    QMenu* helpMenu = menuBar->addMenu(tr("&Help"));
    
    QAction* aboutAction = helpMenu->addAction(tr("&About"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onHelpAbout);
}

void MainWindow::createDockPanels()
{
    // Node Graph Panel (left)
    m_nodeGraphPanel = new NodeGraphPanel(this);
    addDockWidget(Qt::LeftDockWidgetArea, m_nodeGraphPanel);

    // Properties Panel (right)
    m_propertiesPanel = new PropertiesPanel(this);
    addDockWidget(Qt::RightDockWidgetArea, m_propertiesPanel);

    // Timeline Panel (bottom)
    m_timelinePanel = new TimelinePanel(this);
    addDockWidget(Qt::BottomDockWidgetArea, m_timelinePanel);

    // Viewer Panel (center)
    m_viewerPanel = new ViewerPanel(this);
    addDockWidget(Qt::CenterDockWidgetArea, m_viewerPanel);

    // Media Panel (left, tabbed with node graph)
    m_mediaPanel = new MediaPanel(this);
    addDockWidget(Qt::LeftDockWidgetArea, m_mediaPanel);
    tabifyDockWidget(m_nodeGraphPanel, m_mediaPanel);
}

void MainWindow::createConnections()
{
    // Connect signals/slots as needed
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    // TODO: Prompt to save if unsaved changes
    event->accept();
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent* event)
{
    // Handle dropped files
    const QMimeData* mimeData = event->mimeData();
    if (mimeData->hasUrls())
    {
        for (const QUrl& url : mimeData->urls())
        {
            qDebug() << "Dropped file:" << url.toLocalFile();
        }
    }
}

void MainWindow::onFileNew()
{
    qDebug() << "File > New";
}

void MainWindow::onFileOpen()
{
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open Project"), "", tr("NUKE-PRO Projects (*.nkp);;All Files (*)"));
    if (!filename.isEmpty())
    {
        qDebug() << "Opening:" << filename;
    }
}

void MainWindow::onFileSave()
{
    qDebug() << "File > Save";
}

void MainWindow::onFileSaveAs()
{
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Save Project As"), "", tr("NUKE-PRO Projects (*.nkp)"));
    if (!filename.isEmpty())
    {
        qDebug() << "Saving as:" << filename;
    }
}

void MainWindow::onFileExport()
{
    qDebug() << "File > Export";
}

void MainWindow::onEditUndo()
{
    qDebug() << "Edit > Undo";
}

void MainWindow::onEditRedo()
{
    qDebug() << "Edit > Redo";
}

void MainWindow::onHelpAbout()
{
    QMessageBox::about(this, tr("About NUKE-PRO"),
        tr("NUKE-PRO v0.1.0\n\n"
           "Professional VFX Compositor\n"
           "Inspired by Foundry Nuke\n\n"
           "© 2024 VFX Engineering Team"));
}

void MainWindow::applyDarkTheme()
{
    setStyleSheet(DarkTheme::getStyleSheet());
}

void MainWindow::loadSettings()
{
    QSettings settings("NUKE-PRO", "NUKE-PRO");
    
    if (settings.contains("windowGeometry"))
    {
        restoreGeometry(settings.value("windowGeometry").toByteArray());
    }
    
    if (settings.contains("windowState"))
    {
        restoreState(settings.value("windowState").toByteArray());
    }
}

void MainWindow::saveSettings()
{
    QSettings settings("NUKE-PRO", "NUKE-PRO");
    settings.setValue("windowGeometry", saveGeometry());
    settings.setValue("windowState", saveState());
}
