#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_1();
}

MainWindow::~MainWindow()
{
    delete ui;
    if(inputMethodOne){
        inputMethodOne->isRunning=false;
        delete inputMethodOne;
        inputMethodOne = NULL;
    }
    if(inputMethodOneThread){
        if(inputMethodOneThread->isRunning()){
            inputMethodOneThread->quit();
            inputMethodOneThread->wait();
        }
        delete inputMethodOneThread;
        inputMethodOneThread = NULL;
    }
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
    U16 channel = buttonGroup->checkedId();
    qDebug()<<cardType<<":"<<cardNum<<":"<<channel;
    init_1_thread(cardType,cardNum,channel);
}

void MainWindow::on_groupBox_1_config_pushButton_clear_clicked()
{
    ui->groupBox_1_config_cardNum->clear();
}

/**
 * @brief 第一读取方式启动类，包括注册，配置，读取等环节
 */
void MainWindow::on_groupBox_1_pushButton_start_clicked()
{
    inputMethodOneThread->start();
}

void MainWindow::init_1()
{
    cardTypeData.insert("PCI_9114DG",24);
    cardTypeData.insert("PCI_9114HG",25);
    cardNum = -1;
    cardType = -1;
    //设置第一通道默认使用
    ui->groupBox_1_listen_radioButton_com1->setChecked(true);
    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com1,0);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com2,1);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com3,2);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com4,3);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com5,4);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com6,5);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com7,6);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com8,7);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com9,8);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com10,9);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com11,10);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com12,11);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com13,12);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com14,13);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com15,14);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com16,15);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com17,16);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com18,17);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com19,18);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com20,19);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com21,20);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com22,21);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com23,22);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com24,23);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com25,24);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com26,25);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com27,26);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com28,27);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com29,28);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com30,29);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com31,30);
    buttonGroup->addButton(ui->groupBox_1_listen_radioButton_com32,31);
}

/**
 * @brief 读取方式1，线程初始化
 * @param cardType
 * @param cardNum
 * @param channel
 */
void MainWindow::init_1_thread(I16 cardType, I16 cardNum, U16 channel)
{
    inputMethodOne = new InputMethodOne(cardType,cardNum,channel,this);
    inputMethodOneThread = new QThread(this);
    inputMethodOne->moveToThread(inputMethodOneThread);
    //线程初始化
    connect(inputMethodOneThread,&QThread::started,inputMethodOne,&InputMethodOne::init);
    connect(inputMethodOneThread,&QThread::finished,inputMethodOne,&InputMethodOne::deleteLater);
    //线程业务逻辑
    connect(this,&MainWindow::signal_method_one_start,inputMethodOne,&InputMethodOne::slot_start);
    connect(this,&MainWindow::signal_method_one_stop,inputMethodOne,&InputMethodOne::slot_stop);
    connect(inputMethodOne,&InputMethodOne::signal_result,this,&MainWindow::slot_method_one_error);
}

void MainWindow::on_groupBox_1_pushButton_stop_clicked()
{
    inputMethodOneThread->quit();
    inputMethodOneThread->wait();
}

void MainWindow::slot_method_one_error(bool flag, QString message)
{
    if(flag==false){
        QMessageBox::warning(this,tr("警告"),message);
    }else{
        QMessageBox::information(this,tr("提示"),message);
    }
}
