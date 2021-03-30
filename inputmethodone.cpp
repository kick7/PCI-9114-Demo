#include "inputmethodone.h"
#include <QDebug>

InputMethodOne::InputMethodOne(QObject *parent) : QObject(parent)
{

}

InputMethodOne::InputMethodOne(I16 cardType, I16 cardNum, U16 channel, QObject *parent)
{
    this->cardType = cardType;
    this->cardNum = cardNum;
    this->channel = channel;
}

InputMethodOne::~InputMethodOne()
{
    if(isRunning){
        isRunning = false;
    }
}

void InputMethodOne::init()
{
    isRunning = false;
    flag = true;
    m_register();
    if(flag == false){
        return;
    }
    m_config();
    if(flag == false){
        return;
    }
    m_read();
}

void InputMethodOne::m_read()
{

}

void InputMethodOne::m_config()
{
    if(AI_GetView(card,&viewAddr)!=0){
        flag = false;
        message = "AI_GetView 错误！";
        emit signal_result(flag,message);
        return;
    }
    if(AI_InitialMemoryAllocated (card, &MemSize)!=0){
        flag = false;
        message = "AI_InitialMemoryAllocated 错误！";
        emit signal_result(flag,message);
        return;
    }
    Db_buf[0] = viewAddr; //1st DB buffer address
    Db_buf[1] = viewAddr + (MemSize*1024/2); //2nd DB buffer address
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
    if(AI_ContReadChannel(card,channel,range,0,read_count,(F64)sample_rate, ASYNCH_OP)!=0){
        flag = false;
        message = "AI_ContReadChannel 错误！";
        emit signal_result(flag,message);
        return;
    }
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
    isRunning = true;
}

void InputMethodOne::slot_stop()
{
    isRunning =false;
    if(card >= 0){
        U32 count = 0;
        AI_AsyncClear(card,&count);
        Release_Card(card);
    }
}

void InputMethodOne::slot_status()
{
    emit signal_status(isRunning);
}
