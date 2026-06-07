#include "media_panel.h"
#include <QVBoxLayout>
#include <QTreeWidgetItem>
#include <QFileDialog>
#include <QFileInfo>
#include <QHeaderView>

MediaPanel::MediaPanel(QWidget* parent)
    : QDockWidget(tr("Media"), parent)
    , m_mediaTree(nullptr)
    , m_importButton(nullptr)
{
    setObjectName("MediaPanel");
    
    QWidget* widget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(widget);
    
    createToolbar();
    setupTreeView();
    
    mainLayout->addWidget(m_importButton);
    mainLayout->addWidget(m_mediaTree);
    
    setWidget(widget);
}

MediaPanel::~MediaPanel()
{
}

void MediaPanel::createToolbar()
{
    m_importButton = new QPushButton("Import Media", this);
    connect(m_importButton, &QPushButton::clicked, this, &MediaPanel::onImportMedia);
}

void MediaPanel::setupTreeView()
{
    m_mediaTree = new QTreeWidget(this);
    m_mediaTree->setHeaderLabels(QStringList() << "Name" << "Type" << "Size");
    m_mediaTree->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_mediaTree->setStyleSheet(R"(
        QTreeWidget {
            background-color: #1a1a1a;
            color: #e0e0e0;
            border: 1px solid #252525;
        }
    )");
    
    // Create categories
    QTreeWidgetItem* videoItem = new QTreeWidgetItem(m_mediaTree);
    videoItem->setText(0, "Video");
    
    QTreeWidgetItem* imageItem = new QTreeWidgetItem(m_mediaTree);
    imageItem->setText(0, "Images");
    
    QTreeWidgetItem* audioItem = new QTreeWidgetItem(m_mediaTree);
    audioItem->setText(0, "Audio");
}

void MediaPanel::addMediaFile(const QString& path)
{
    if (path.isEmpty()) return;
    
    QString filename = QFileInfo(path).fileName();
    QString extension = QFileInfo(path).suffix().toLower();
    
    QStringList videoFormats = {"mp4", "avi", "mov", "mkv", "wmv", "flv", "webm"};
    QStringList imageFormats = {"jpg", "jpeg", "png", "gif", "bmp", "tiff", "exr"};
    QStringList audioFormats = {"mp3", "wav", "aac", "flac", "ogg", "m4a"};
    
    QString category;
    if (videoFormats.contains(extension)) category = "Video";
    else if (imageFormats.contains(extension)) category = "Images";
    else if (audioFormats.contains(extension)) category = "Audio";
    else return;
    
    QList<QTreeWidgetItem*> items = m_mediaTree->findItems(category, Qt::MatchExactly, 0);
    if (items.isEmpty()) return;
    
    QTreeWidgetItem* fileItem = new QTreeWidgetItem(items.first());
    fileItem->setText(0, filename);
    fileItem->setText(1, extension.toUpper());
    
    qint64 size = QFileInfo(path).size();
    QString sizeStr = QString("%1 KB").arg(size / 1024);
    fileItem->setText(2, sizeStr);
    
    emit mediaFileImported(path);
}

void MediaPanel::clearMedia()
{
    for (int i = 0; i < m_mediaTree->topLevelItemCount(); ++i) {
        QTreeWidgetItem* category = m_mediaTree->topLevelItem(i);
        while (category->childCount() > 0) {
            delete category->child(0);
        }
    }
}

void MediaPanel::onImportMedia()
{
    QStringList files = QFileDialog::getOpenFileNames(
        this,
        "Import Media Files",
        "",
        "Media Files (*.mp4 *.avi *.mov *.mkv *.jpg *.png *.mp3 *.wav);;"
        "All Files (*)"
    );
    
    for (const QString& file : files) {
        addMediaFile(file);
    }
}

void MediaPanel::onDeleteMedia()
{
    QTreeWidgetItem* currentItem = m_mediaTree->currentItem();
    if (currentItem && currentItem->parent()) {
        delete currentItem;
    }
}