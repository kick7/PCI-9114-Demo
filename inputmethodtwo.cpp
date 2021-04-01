#include "inputmethodtwo.h"

InputMethodTwo::InputMethodTwo(QObject *parent) : QObject(parent)
{
    isRunning = true;
}

void InputMethodTwo::m_init()
{
    hDAQPilotTask = NULL;

    hDAQPilotTask = DAQPilot_LoadTask(taskName.toLocal8Bit().constData(),FALSE);
    if(!hDAQPilotTask){
        emit signal_error_information(tr("Load task failed!"));
        isRunning = false;
        return;
    }
}

void InputMethodTwo::m_start()
{
    DAQPilotStatusID dwError = DP_STATUS_NOERROR;
    DWORD dwThreadId = 0;
    HANDLE hThread = NULL;
    dwError = DAQPilot_Start(hDAQPilotTask);
    if( dwError < DP_STATUS_NOERROR )
    {
        LPCSTR lpszMsg = DAQPilot_GetErrorMessage(dwError); //得到错误信息
        emit signal_error_information(QString(lpszMsg));
        isRunning = false;
        return;
    }
    //    hThread = CreateThread(NULL,0,)

}

//DWORD WINAPI ThreadFunc(LPVOID lpParam){
//    HANDLE hDAQPilotTask = NULL; //任务为空
//    WORD * pChNoList = NULL;
//    DWORD  i=0;
//    int    j=0, k=0;
//    int	  nNumOfChannel  = 0;
//    DWORD dwDisplayCount = 0;
//    DAQPilotAnalogData DAQPilotData; //DAQ数据 （struct结构体）

//    hDAQPilotTask = *((HANDLE*)lpParam); //任务转化
//    //Display caption
//    nNumOfChannel = DAQPilot_GetEnabledChannelList(hDAQPilotTask, &pChNoList); //获取任务状态
//    printf("No");
//    for(k=0; k < nNumOfChannel; k++)
//        printf("   Channel %d", pChNoList[k]);
//    printf("\n");

//    do
//    {
//        DAQPilotStatusID dwError = DAQPilot_GetAIWaveform(hDAQPilotTask, &DAQPilotData, INFINITE); //采集信号，第三位，设置采集不停止，一直开始
//        if( dwError < DP_STATUS_NOERROR ) //出现错误就停止
//            break;
//        dwDisplayCount = min(10, DAQPilotData.dwNumOfScan); //最少10
//        for(i=0; i < dwDisplayCount; i++)
//        {
//            printf("%d", i);
//            for(j=0; j < DAQPilotData.nNumOfChannel; j++) //采集的通道数
//            {
//                printf("    %f", ((double*)DAQPilotData.lpScaledData)[(i*DAQPilotData.nNumOfChannel)+j]);
//            }
//            printf("\n");
//        }
//        printf("====================================================================\n");
//    } while(TRUE);
//    return 0;
//}


