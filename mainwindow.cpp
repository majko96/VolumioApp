#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QDir>
#include <QInputDialog>
#include <QMessageBox>

/*
#include <QNetworkReply>
#include <unistd.h>
#include <iostream>
#include <QLabel>
#include <QFile>
*/

#include <pwd.h>
#include <unistd.h>



using namespace std;
std::string ip_address,label;
std::string url1 ="http://", url_state= "/api/v1/getState";
QString qIP_address;



/*
void MainWindow::loop()

{

for(;;)

{

    QNetworkAccessManager *manager;
    manager = new QNetworkAccessManager(this);

        std::string label = qIP_address.toStdString();
        std::string url2 = url1 + label + url_state;
        QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url2.c_str())));

        QEventLoop eventloop;
            connect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
            eventloop.exec();
        QByteArray bts = reply->readAll();
        QString str(bts);
        qDebug() << str;
        usleep(5000000);
        }

    qDebug() << "ahoj";
    usleep(5000000);}
}
*/



void readip()
{
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    std::string h = std::string(homedir);
    std::string path_read = h + "/.volumiox/data.txt";


    QFile file(path_read.c_str());
    file.open(QIODevice::ReadOnly);
    if (!file.isOpen())
        return;
    QTextStream stream(&file);
    QString line = stream.readLine();

    while (!line.isNull()) {
        /* process information */


        qIP_address = line;
        std::string label = qIP_address.toStdString();
        break;
}
}



MainWindow::MainWindow(QWidget *parent)

    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    readip();
    ui->setupUi(this);
    this->setWindowTitle("Volumio");
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_prev_clicked()
{
    QNetworkAccessManager *manager;
    manager = new QNetworkAccessManager(this);

        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));

        std::string label = qIP_address.toStdString();
        std::string url = url1 + (label)  +"/api/v1/commands/?cmd=prev";
        manager->get(QNetworkRequest(QUrl(url.c_str())));


}

void MainWindow::on_pushButton_play_clicked()
{

    QNetworkAccessManager *manager;
    manager = new QNetworkAccessManager(this);

        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));

        std::string label = qIP_address.toStdString();
        std::string url = url1 + label + "/api/v1/commands/?cmd=toggle";

        manager->get(QNetworkRequest(QUrl(url.c_str())));

}




void MainWindow::on_pushButton_next_clicked()
{
    QNetworkAccessManager *manager;
    manager = new QNetworkAccessManager(this);

        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));

        std::string label = qIP_address.toStdString();
        std::string url = url1 + label +"/api/v1/commands/?cmd=next";

        manager->get(QNetworkRequest(QUrl(url.c_str())));
}

void MainWindow::on_pushButton_minus_clicked()
{
    QNetworkAccessManager *manager;
    manager = new QNetworkAccessManager(this);

        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));

        std::string label = qIP_address.toStdString();
        std::string url = url1 + label + "/api/v1/commands/?cmd=volume&volume=minus";

        manager->get(QNetworkRequest(QUrl(url.c_str())));
}

void MainWindow::on_pushButton_plus_clicked()
{

    QNetworkAccessManager *manager;
    manager = new QNetworkAccessManager(this);

        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));

        std::string label = qIP_address.toStdString();
        std::string url = url1 + label + "/api/v1/commands/?cmd=volume&volume=plus";
        manager->get(QNetworkRequest(QUrl(url.c_str())));
}





void MainWindow::on_pushButton_clicked()
{
    QNetworkAccessManager *manager;
    manager = new QNetworkAccessManager(this);

        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));

        std::string label = qIP_address.toStdString();
        std::string url = url1 + label + "/api/v1/commands/?cmd=volume&volume=mute";

        manager->get(QNetworkRequest(QUrl(url.c_str())));
}

void MainWindow::on_actionIP_adress_triggered()
{
    std::string label = qIP_address.toStdString();
    bool ok;
    QString text = QInputDialog::getText(this, tr("IP"),
                                             tr("IP address of Volumio:"), QLineEdit::Normal,
                                             tr(label.c_str()), &ok);

    if (ok && !text.isEmpty()) {
        QString input = text;
        std::string input1=input.toStdString();
        ip_address = input1;


        struct passwd *pw = getpwuid(getuid());
        const char *homedir = pw->pw_dir;
        std::string h = std::string(homedir);
            std::string path = h + "/.volumiox/";
            std::string data = path + "data.txt";

        QDir dir(path.c_str());
        if (!dir.exists())
             dir.mkpath(".");

        QString filename = data.c_str();
        QFile file(filename);
        file.open(QFile::WriteOnly|QFile::Truncate);
        QTextStream stream(&file);
        stream << ip_address.c_str();
        file.close();
        readip();}



}

void MainWindow::on_actionExit_triggered()
{
   QCoreApplication::exit();
}




void MainWindow::on_actionAbout_2_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.setText("Created by majko96");
    msgBox.exec();
}
