#include "threadoneread.h"

ThreadOneRead::ThreadOneRead(QObject *parent)
{
    isRunning = false;
    card = -1;
    sts = 0;
    count = 0;
}

void ThreadOneRead::run()
{
    long startTime = GetTickCount();
    BOOLEAN halfReady,fStop;
    while(isRunning == true){
        do {
            AI_AsyncDblBufferHalfReady(card, &halfReady, &fStop); //是否准备好
        } while (!halfReady);
        long endTime1 = GetTickCount();
        emit signal_time_different(1,endTime1-startTime);
        AI_AsyncDblBufferTransfer(card,NULL);
        count += (read_count/2);
        AI_AsyncDblBufferOverrun(card, 0, &sts); //检查是否超限
        if(sts) { //已经超限，那么清除超限
            AI_AsyncDblBufferOverrun(card, 1, &sts);
        }
        emit signal_current_count(count);
        long endTime2 = GetTickCount();
        emit signal_time_different(2,endTime2-endTime1);
    }
}
