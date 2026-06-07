#ifndef MEDIA_PANEL_H
#define MEDIA_PANEL_H

#include <QDockWidget>
#include <QWidget>
#include <QTreeWidget>
#include <QPushButton>

/**
 * @class MediaPanel
 * @brief Panel for managing media files
 */
class MediaPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit MediaPanel(QWidget* parent = nullptr);
    ~MediaPanel();

    void addMediaFile(const QString& path);
    void clearMedia();

public slots:
    void onImportMedia();
    void onDeleteMedia();

signals:
    void mediaFileSelected(const QString& path);
    void mediaFileImported(const QString& path);

private:
    void createToolbar();
    void setupTreeView();

private:
    QTreeWidget* m_mediaTree;
    QPushButton* m_importButton;
};

#endif // MEDIA_PANEL_H