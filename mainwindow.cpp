#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

//读取方式1，默认配置
#define CardNum   12
#define DataSize  2048
#define sample_rate  4000
#define ScaleSize 32

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cardTypeData.insert("PCI_9114DG",24);
    cardTypeData.insert("PCI_9114HG",25);
    cardNum = -1;
    cardType = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_groupBox_1_config_pushButton_ok_clicked()
{
    switch (cardTypeData[ui->groupBox_1_config_cardType->currentText()]) {
    case PCI_9114DG:
        cardType = PCI_9114DG;
        break;
    case PCI_9114HG:
        cardType = PCI_9114HG;
        break;
    default:
        QMessageBox::warning(this,tr("警告"),tr("卡号错误，没有该卡号!"));
        exit(1);
    }
    cardNum = ui->groupBox_1_config_cardNum->text().toInt();
}

void MainWindow::on_groupBox_1_config_pushButton_clear_clicked()
{
    ui->groupBox_1_config_cardNum->clear();
}

void MainWindow::on_groupBox_1_pushButton_start_clicked()
{
    //    QRadioButton *pbtn = qobject_cast<QRadioButton*>(ui-> ->checkedButton());
}
