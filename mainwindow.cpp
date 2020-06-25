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
std::string ip_address,label,volume_str,str1,songa,status_response;
std::string url1 ="http://", url_state= "/api/v1/getState", url_ping= "/api/v1/ping";
QString qIP_address, qstatus,text,str_re;
double volumed;

std::string title_str, artist_str, is_playing,odpoved;


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


        QColor darkGray(53, 53, 53);
        QColor gray(128, 128, 128);
        QColor black(25, 25, 25);
        QColor blue(42, 130, 218);

        QPalette darkPalette;
        darkPalette.setColor(QPalette::Window, darkGray);
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, black);
        darkPalette.setColor(QPalette::AlternateBase, darkGray);
        darkPalette.setColor(QPalette::ToolTipBase, blue);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, darkGray);
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::Link, blue);
        darkPalette.setColor(QPalette::Highlight, blue);
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);

        darkPalette.setColor(QPalette::Active, QPalette::Button, gray.darker());
        darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, gray);
        darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, gray);
        darkPalette.setColor(QPalette::Disabled, QPalette::Text, gray);
        darkPalette.setColor(QPalette::Disabled, QPalette::Light, darkGray);
        qApp->setPalette(darkPalette);


    timer = new QTimer(this);
    timer2 = new QTimer(this);
    parse();
    myfunction();
    status();
    connect(timer2,SIGNAL(timeout()),this,SLOT(parse()));
    timer2 ->start(500);
    connect(timer,SIGNAL(timeout()),this,SLOT(myfunction()));
    connect(timer,SIGNAL(timeout()),this,SLOT(myfunction2()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(status()));
    timer ->start(50);
    ui->song->setText(title_str.c_str());
    ui->artist->setText(artist_str.c_str());
    if(status_response !="pong")
    {
        ui->on_off->setText("OFF");
    }
    else
    {
     ui->on_off->setText("ON");
    }

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
    if(status_response !="pong")
    {
        ui->on_off->setText("OFF");
    }
    else
    {
     ui->on_off->setText("ON");
    }

}

void MainWindow::status(){

    QNetworkAccessManager *manager;
    manager = new QNetworkAccessManager(this);
    std::string label = qIP_address.toStdString();
    std::string url3 = url1 + label + url_ping;

    QNetworkReply *reply1 = manager->get(QNetworkRequest(QUrl(url3.c_str())));
    QEventLoop eventloop;
        connect(reply1,SIGNAL(finished()),&eventloop,SLOT(quit()));

        eventloop.exec();
        QByteArray bts1 = reply1->readAll();
        status_response = bts1.toStdString();
        //qDebug()<<(status_response.c_str());
        if(status_response !="pong")
        {
            ui->on_off->setText("OFF");
        }
        else
        {
         ui->on_off->setText("ON");
        }
        delete manager;
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
            QString str_re(bts);


            QJsonDocument jsonResponse = QJsonDocument::fromJson(str_re.toUtf8());
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
        readip();
        status();
        myfunction();

      }

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
