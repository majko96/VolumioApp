#include "settingsui.h"
#include "ui_settingsui.h"
#include "mainwindow.h"

#include <QDebug>
#include <QDir>
#include <pwd.h>
#include <unistd.h>


using namespace std;

QString ipcka;
extern std::string path, data1, ip_address, label;
extern QString qIP_address;


extern struct passwd *pw;
extern const char *homedir;

void readip();



settingsUI::settingsUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsUI)
{
    ui->setupUi(this);
    ui->lineEdit->setText(qIP_address);
    //qDebug()<< qIP_address;
}

settingsUI::~settingsUI()
{
    delete ui;
}



void settingsUI::on_buttonBox_accepted()
{
    /*std::string label = qIP_address.toStdString();
    bool ok;
    QString text = QInputDialog::getText(this, tr("IP"),
                                             tr("IP address of Volumio:"), QLineEdit::Normal,
                                             tr(label.c_str()), &ok);*/

        ipcka = ui->lineEdit->text();
        qDebug()<< qIP_address;
        std::string label = ipcka.toStdString();
        //qDebug(label.c_str());
        /*QLineEdit lineEdit = ;
        std::string input1=input.toStdString();
        ip_address = input1;*/

        QDir dir(path.c_str());
        if (!dir.exists())
             dir.mkpath(".");

        QString filename = data1.c_str();
        QFile file(filename);
        file.open(QFile::WriteOnly|QFile::Truncate);
        QTextStream stream(&file);
        stream << ipcka;
        file.close();
        readip();
        void status();
        void myfunction();
}

