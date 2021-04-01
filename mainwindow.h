#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <conio.h>
#include <windows.h>
#include "Dask.h"
#include <QMap>
#include <QButtonGroup>
#include "inputmethodone.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_groupBox_1_config_pushButton_ok_clicked();

    void on_groupBox_1_config_pushButton_clear_clicked();

    void on_groupBox_1_pushButton_start_clicked();

    void on_groupBox_1_pushButton_stop_clicked();

    void slot_method_one_error(bool flag,QString message);

    void slot_method_one_current_count(unsigned long count);

    void slot_method_one_time_different(int type,long time);

    void on_groupBox_2__pushButton_start_clicked();

private:
    void init_1();
    void init_1_thread(I16 cardType,I16 cardNum,U16 channel);

signals:
    void signal_method_one_start();
    void signal_method_one_stop();
    void signal_methid_one_read_status();

private:
    Ui::MainWindow *ui;
    I16 cardType,cardNum;
    QMap<QString,int> cardTypeData;
    QButtonGroup *buttonGroup;
    InputMethodOne *inputMethodOne;
    QThread *inputMethodOneThread;
};
#endif // MAINWINDOW_H
