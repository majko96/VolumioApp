#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPointer>
#include <QSlider>
#include <QSystemTrayIcon>
#include <QSettings>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSystemTrayIcon *trayIcon;
    QMenu *trayContextMenu;
    QAction *actShow;
    QAction *actHide;
    QAction *actExit;
    QSettings *settings;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void myfunction();
    void myfunction2();
    void parse();
    void status();


protected:
    void changeEvent(QEvent *);



private slots:
    void on_pushButton_prev_clicked();

    void on_pushButton_play_clicked();

    void on_pushButton_next_clicked();

    void on_actionExit_triggered();

    void on_actionAbout_2_triggered();


    void on_horizontalSlider_valueChanged(int value);

    void trayIcon_activated(QSystemTrayIcon::ActivationReason reason);
    void actShow_Triggered();
    void actHide_Triggered();
    void actExit_Triggered();
    void writeSettings();
    void readSettings();
    void on_Settings_triggered();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *timer2;
    QSlider *slider;

};

#endif // MAINWINDOW_H
