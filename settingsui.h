#ifndef SETTINGSUI_H
#define SETTINGSUI_H

#include <QDialog>

namespace Ui {
class settingsUI;
}

class settingsUI : public QDialog
{
    Q_OBJECT

public:
    explicit settingsUI(QWidget *parent = nullptr);
    ~settingsUI();

private slots:
    void on_buttonBox_accepted();



private:
    Ui::settingsUI *ui;
};

#endif // SETTINGSUI_H
