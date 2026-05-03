#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QMediaPlayer>
#include "videotimeline.h"
#include "videoeditor.h"
#include "paymentmanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onImportVideo();
    void onExportVideo();
    void onPlayPause();
    void onSubscription();
    void onAddEffect();
    void onAddTransition();
    void onTimelineClicked(double time);
    void onPositionChanged(qint64 position);
    void onDurationChanged(qint64 duration);
    void onSubscriptionExpired();

private:
    void setupUI();
    void createMenuBar();
    void createToolbars();
    void createStatusBar();
    void connectSignals();
    void checkSubscriptionOnStartup();

    // UI Components
    VideoTimeline *timeline;
    VideoEditor *videoEditor;
    PaymentManager *paymentManager;
    
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *importButton;
    QPushButton *exportButton;
    QPushButton *subscriptionButton;
    QPushButton *addEffectButton;
    QPushButton *addTransitionButton;
    
    QSlider *volumeSlider;
    QSlider *timeSlider;
    
    QLabel *timeLabel;
    QLabel *subscriptionStatus;
    QLabel *previewLabel;
    
    QListWidget *effectsList;
    QListWidget *transitionsList;
    
    QMediaPlayer *mediaPlayer;
    
    bool isSubscribed;
    QString currentProjectPath;
};

#endif // MAINWINDOW_H
