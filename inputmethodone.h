#ifndef INPUTMETHODONE_H
#define INPUTMETHODONE_H

#include <QObject>
#include <conio.h>
#include <windows.h>
#include "Dask.h"
#include "threadoneread.h"


#define DataSize  2048
#define sample_rate  6000
#define ScaleSize 32

class InputMethodOne : public QObject
{
    Q_OBJECT
public:
    //    explicit InputMethodOne(QObject *parent = nullptr);
    explicit InputMethodOne(I16 cardType,I16 cardNum,U16 channel,QObject *parent = nullptr);
    ~InputMethodOne();
    void init();
private:
    void m_config();
    void m_register();

signals:
    void signal_result(bool flag,QString message);

    void signal_status(bool isRunning);

    void signal_current_count(unsigned long count);

    void signal_time_different(int type,long time);

public slots:
    void slot_start();
    void slot_stop();
    void slot_status();

    void slot_thread_current_count(unsigned long count);

    void slot_thread_time_different(int type,long time);
public:
    I16 card;
    I16 cardType,cardNum;
    U16 channel,range;
    U32 read_count,count,count1;
    U32 viewAddr, MemSize, Db_buf[2];
    F64 voltageArray[ScaleSize];
    bool flag;
    QString message;
    ThreadOneRead *thread1;
};

#endif // INPUTMETHODONE_H
