#include "inputmethodone.h"
#include <QDebug>
#include <QThread>

//InputMethodOne::InputMethodOne(QObject *parent) : QObject(parent)
//{
//}

InputMethodOne::InputMethodOne(I16 cardType, I16 cardNum, U16 channel, QObject *parent)
{
    qDebug()<<"线程"<<QThread::currentThread()<<"开始创建";
    this->cardType = cardType;
    this->cardNum = cardNum;
    this->channel = channel;
    thread1 = new ThreadOneRead(this);
    connect(thread1,&ThreadOneRead::signal_current_count,this,&InputMethodOne::slot_thread_current_count);
    connect(thread1,&ThreadOneRead::signal_time_different,this,&InputMethodOne::slot_thread_time_different);
}

InputMethodOne::~InputMethodOne()
{
    qDebug()<<"线程"<<QThread::currentThread()<<"开始销毁";
    if(thread1->isRunning==true){
        thread1->isRunning=false;
        count = thread1->count;
        if(card >= 0){
            AI_AsyncClear(card,&count1);
            count += count1;
            Release_Card(card);
        }
        delete thread1;
    }
}

void InputMethodOne::init()
{
    flag = true;
    range=AD_B_5_V;
    read_count = DataSize;
    MemSize=0;
    count1 = 0;

    m_register();
    if(flag == false){
        return;
    }
    m_config();
    if(flag == false){
        return;
    }
}

void InputMethodOne::m_config()
{
    //    if(AI_GetView(card,&viewAddr)!=0){
    //        flag = false;
    //        message = "AI_GetView 错误！";
    //        emit signal_result(flag,message);
    //        return;
    //    }
    //    if(AI_InitialMemoryAllocated (card, &MemSize)!=0){
    //        flag = false;
    //        message = "AI_InitialMemoryAllocated 错误！";
    //        emit signal_result(flag,message);
    //        return;
    //    }
    //    Db_buf[0] = viewAddr; //1st DB buffer address
    //    Db_buf[1] = viewAddr + (MemSize*1024/2); //2nd DB buffer address
    if(AI_9114_Config(card, TRIG_INT_PACER)!=0){
        flag = false;
        message = "AI_9114_Config 错误！";
        emit signal_result(flag,message);
        return;
    }
    if(AI_AsyncDblBufferMode(card,TRUE)!=0){
        flag = false;
        message = "AI_AsyncDblBufferMode 错误！";
        emit signal_result(flag,message);
        return;
    }
    //数据存储到文件
    if(AI_ContScanChannelsToFile(card, channel, range, (unsigned char*)"demo" , read_count, (F64) sample_rate, ASYNCH_OP)!=0){
        flag = false;
        message = "AI_ContScanChannelsToFile 错误！";
        emit signal_result(flag,message);
        return;
    }
    //    if(AI_ContReadChannel(card,channel,range,0,read_count,(F64)sample_rate, ASYNCH_OP)!=0){
    //        flag = false;
    //        message = "AI_ContReadChannel 错误！";
    //        emit signal_result(flag,message);
    //        return;
    //    }
}

void InputMethodOne::m_register()
{
    if((card=Register_Card (cardType, cardNum))>=0){
        flag = true;
        message = QString("注册成功！卡号为:%1").arg(card);
    }else{
        flag = false;
        message = "注册失败！";
    }
    emit signal_result(flag,message);
}


void InputMethodOne::slot_start()
{
    qDebug()<<QThread::currentThread()<<"线程启动";
    thread1->card = card;
    thread1->read_count = read_count;
    thread1->isRunning=true;
    thread1->start();

    //        pthread_t t;
    //        pthread_create(&t,NULL,read_read,this);
    //        QtConcurrent::run([=](){
    //           this->m_read();
    //        });
}

void InputMethodOne::slot_stop()
{
    qDebug()<<QThread::currentThread()<<"线程关闭";
    thread1->isRunning=false;
}

void InputMethodOne::slot_status()
{
    emit signal_status(thread1->isRunning);
}

void InputMethodOne::slot_thread_current_count(unsigned long count)
{
    emit signal_current_count(count);
}

void InputMethodOne::slot_thread_time_different(int type,long time)
{
    emit signal_time_different(type,time);
}

