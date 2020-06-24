#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPropertyAnimation>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void myfunction();
    void myfunction2();
    void parse();





private slots:
    void on_pushButton_prev_clicked();

    void on_pushButton_play_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_minus_clicked();

    void on_pushButton_plus_clicked(); 
    void on_pushButton_clicked();

    void on_actionIP_adress_triggered();

    void on_actionExit_triggered();


    void on_actionAbout_2_triggered();

    void on_actionGitHub_triggered();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *timer2;
    QPropertyAnimation *mMoveAnimation;

};

#endif // MAINWINDOW_H
