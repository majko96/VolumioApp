#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QDir>
#include <QInputDialog>
#include <QMessageBox>

#include <QNetworkReply>
#include <QLabel>
#include <QFile>
#include <pwd.h>
#include <unistd.h>
#include <QJsonObject>
#include <QJsonDocument>




using namespace std;
std::string ip_address,label,volume_str,str1,songa;
std::string url1 ="http://", url_state= "/api/v1/getState";
QString qIP_address, qstatus,text;
double volumed;

std::string title_str, artist_str, is_playing;


struct passwd *pw = getpwuid(getuid());
const char *homedir = pw->pw_dir;
std::string h = std::string(homedir);
std::string path = h + "/.volumiox/";
std::string data_parse = path + "parse.txt";
std::string data1 = path + "data.txt";




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
        qIP_address = line;
        std::string label = qIP_address.toStdString();
        break;
}
    file.close();
}



MainWindow::MainWindow(QWidget *parent)

    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    readip();
    ui->setupUi(this);
    this->setWindowTitle("VolumioX");
    timer = new QTimer(this);
    timer2 = new QTimer(this);
    parse();
    myfunction();
    connect(timer2,SIGNAL(timeout()),this,SLOT(parse()));
    timer2 ->start(500);
    connect(timer,SIGNAL(timeout()),this,SLOT(myfunction()));
    timer ->start(50);
    connect(timer,SIGNAL(timeout()),this,SLOT(myfunction2()));
    timer ->start(50);
    ui->song->setText(title_str.c_str());
    ui->artist->setText(artist_str.c_str());
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::myfunction()
{

    QString text = ui->song->text();
    songa = text.toStdString();
    ui->volume->setText(str1.c_str());
    if (is_playing == "play")
    {
      ui->playing->setText("Playing...");
    }
    else
    {
     ui->playing->setText("");
    }
}


void MainWindow::parse()
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

            QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
            QJsonObject jsonObject = jsonResponse.object();
            QString qstatus = jsonObject["title"].toString();
            title_str = qstatus.toStdString();

            QString qartist = jsonObject["artist"].toString();
            artist_str = qartist.toStdString();
            QString qisplayng = jsonObject["status"].toString();
            is_playing = qisplayng.toStdString();
            int qvolume = jsonObject["volume"].toInt();
            str1 = std::to_string(qvolume);
            volume_str = qvolume;
            delete manager;
}

void MainWindow::myfunction2()
{
    if(songa != title_str)
    {
        ui->song->setText(title_str.c_str());
        ui->artist->setText(artist_str.c_str());
    }
    else{

    }

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
        //QTimer::singleShot(1000, this, SLOT(myfunction2()));

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
        //QTimer::singleShot(1000, this, SLOT(myfunction2()));

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

        QDir dir(path.c_str());
        if (!dir.exists())
             dir.mkpath(".");

        QString filename = data1.c_str();
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
    msgBox.setText("Created by majko96\nmr.babinec@gmail.com");
    msgBox.exec();
}

void MainWindow::on_actionGitHub_triggered()
{
    QMessageBox msgBox1;
    msgBox1.setWindowTitle("GitHub");
    msgBox1.setText("<a href='https://github.com/majko96/VolumioApp'>Github</a>");
    msgBox1.exec();
}
