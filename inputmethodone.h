#ifndef INPUTMETHODONE_H
#define INPUTMETHODONE_H

#include <QObject>
#include <conio.h>
#include <windows.h>
#include "Dask.h"


#define DataSize  2048
#define sample_rate  4000
#define ScaleSize 32

class InputMethodOne : public QObject
{
    Q_OBJECT
public:
    explicit InputMethodOne(QObject *parent = nullptr);
    explicit InputMethodOne(I16 cardType,I16 cardNum,U16 channel,QObject *parent = nullptr);
    ~InputMethodOne();
    void init();
private:
    void m_read();
    void m_config();
    void m_register();

signals:
    void signal_result(bool flag,QString message);

    void signal_status(bool isRunning);


public slots:
    void slot_start();
    void slot_stop();
    void slot_status();
public:
    bool isRunning;
    I16 card;
    I16 cardType,cardNum;
    U16 channel,range=AD_B_5_V;
    U32 read_count = DataSize, count = 0;
    U32 viewAddr, MemSize=0, Db_buf[2];
    F64 voltageArray[ScaleSize];
    bool flag;
    QString message;
};

#endif // INPUTMETHODONE_H
