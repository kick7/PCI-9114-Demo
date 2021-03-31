#ifndef THREADONEREAD_H
#define THREADONEREAD_H

#include <QObject>
#include <QThread>
#include <conio.h>
#include <windows.h>
#include "Dask.h"

class ThreadOneRead : public QThread
{
    Q_OBJECT
public:
    explicit ThreadOneRead(QObject *parent = nullptr);

    void run() override;

    bool isRunning;

    I16 card;

    U16 sts;

    U32 count;

    U32 read_count;
signals:
    void signal_current_count(unsigned long count);

    void signal_time_different(int type,long time);
};

#endif // THREADONEREAD_H
