// DAQPilotAPI.h: interface for the DAQPilot APIs
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DAQPILOTAPI_H__6C0FCD3F_9A74_4149_B084_943B661B940C__INCLUDED_)
#define AFX_DAQPILOTAPI_H__6C0FCD3F_9A74_4149_B084_943B661B940C__INCLUDED_

#include "DAQPilotAdvancedProperties.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifndef AFX_API_EXPORT
	#define AFX_API_EXPORT __declspec(dllimport)
#endif

// Define the event handle under LabVIEW by Roger in 20120423, 20120718
#ifdef _EXTCODE_LABVIEW
//#define _EXTCODE_LABVIEW
#include "extcode.h"
#endif //_EXTCODE_LABVIEW

#include <OAIdl.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __BORLANDC__
#pragma option -a1
#endif //__BORLANDC__

#ifdef _MSC_VER
#pragma pack(1)
#endif //__MSC_VER

typedef signed long        int32;

//Callback event support
typedef struct TagDAQPilotAnalogData
{
	double* lpScaledData;
	double* lpThermoData;
	DWORD   dwNumOfScan;
	int     nNumOfChannel;
	LPWORD  lpChannelNoList;
	//Advance data format info
	LPBYTE  lpRawData;
	LPDWORD lpdwRawData;
	int     nRawDataWidth;//Unit: Byte
} DAQPilotAnalogData;

typedef struct TagDAQPilotDigitalData
{
	DWORD   dwNumOfScan;
	int     nNumOfChannel;
	LPWORD  lpPortOrLineList;
	//lpRawData pointer to byte array when nRawDataBits in 1 through 8 range.
    LPBYTE  lpRawData;
	int     nRawDataBits;//Unit: Bit
} DAQPilotDigitalData;

#ifdef __BORLANDC__
#pragma option -a.
#endif //__BORLANDC__

#ifdef _MSC_VER
#pragma pack()
#endif //_MSC_VER

//Initial(Uninitial) API
AFX_API_EXPORT HANDLE DAQPilot_LoadTask(LPCSTR lpszTaskName, BOOL bShowErrorMessage);
AFX_API_EXPORT BOOL   DAQPilot_EndTask(HANDLE hTask);

//Status API
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_GetTaskStatus(HANDLE hTask);
AFX_API_EXPORT int	DAQPilot_GetEnabledChannelList(HANDLE hTask, WORD ** ppChNoList);

//Operation API
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_Config(HANDLE hTask);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_Start(HANDLE hTask);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_Stop(HANDLE hTask);

//Data notification event
AFX_API_EXPORT HANDLE DAQPilot_GetNotifyEvent(HANDLE hTask);

//Analog input functions
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_AI_CreateChanCfg(HANDLE hTask, WORD wChanCfg, WORD wTrigCtrl, WORD wPollSpeed, WORD wMAvgStage, WORD InType, WORD ThermoType );
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_AI_ReadChannel(HANDLE hTask, double * pdbValue);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_AI_ReadChannels(HANDLE hTask, DAQPilotAnalogData * pstDataInfo);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_GetAIWaveform(HANDLE hTask, DAQPilotAnalogData * pstDataInfo, DWORD dwTimeOut);

//Analog output functions
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_AO_WriteChannel(HANDLE hTask, double dbValue);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_AO_WriteChannels(HANDLE hTask, DAQPilotAnalogData * pstDataInfo);
//Timeout will be assigned for continue AO output to get next AO buffer
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_GetAOBuffer(HANDLE hTask, DAQPilotAnalogData * pstDataInfo, DWORD dwTimeOut);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_SetAOWaveform(HANDLE hTask, DAQPilotAnalogData * pstDataInfo);

//Digital input functions
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_DI_ReadPort(HANDLE hTask, DWORD * pdwValue);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_DI_ReadLine(HANDLE hTask, BOOL * pbValue);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_DI_ReadChannels(HANDLE hTask, DAQPilotDigitalData * pstDataInfo);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_GetDIPattern(HANDLE hTask, DAQPilotDigitalData * pstDataInfo, DWORD dwTimeOut);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_DI_Control(HANDLE hTask, DWORD dwFltrCh, double dbFltrPlsWidth);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_DI_GetCosLatchData(HANDLE hTask, BOOL bAutoResetCosInt, DWORD * pdwValue);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_DI_GetCosINTLatchData(HANDLE hTask, DWORD * pdwValue);

AFX_API_EXPORT DAQPilotStatusID  DAQPilot_DI_SetCosEvent(HANDLE hTask, DWORD dwIntCtrl, DWORD dwTimeOut, VARIANT * rwer );
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_DI_SetCosInterrupt(HANDLE hTask, DWORD dwIntCtrl, DWORD dwTimeOut);
//Digital output functions
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_DO_WritePort(HANDLE hTask, DWORD dwValue);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_DO_WriteLine(HANDLE hTask, BOOL  bValue);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_DO_WriteChannels(HANDLE hTask, DAQPilotDigitalData * pstDataInfo);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_DO_ReadBackPort(HANDLE hTask, DWORD * pdwValue);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_DO_ReadBackLine(HANDLE hTask, BOOL * pbValue);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_DO_ReadBackChannels(HANDLE hTask, DAQPilotDigitalData * pstDataInfo);

//Timeout will be assigned for continue DO output to get next DO buffer
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_GetDOBuffer(HANDLE hTask, DAQPilotDigitalData * pstDataInfo, DWORD dwTimeOut);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_SetDOPattern(HANDLE hTask, DAQPilotDigitalData * pstDataInfo);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_GetDOInitialPattern(HANDLE hTask, DWORD * pstDataInfo);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_SetDOInitialPattern(HANDLE hTask, DWORD stDataInfo);

//Timer/Counter functions
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_TC_GetValue(HANDLE hTask, DWORD * pdwValue);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_TC_ReadCounters(HANDLE hTask, DAQPilotDigitalData * pstDataInfo);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_TC_GetValue(HANDLE hTask, DWORD * pdwValue);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_TC_Control(HANDLE hTask, DWORD dwFltrSw, double dbFltrPlsWidth, DWORD dwAtvChan);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_TC_ReadFrequency(HANDLE hTask, DWORD dwAtvChan, double * pdbValue);
AFX_API_EXPORT DAQPilotStatusID  DAQPilot_TC_ReadRisingEdgeCounter(HANDLE hTask, DWORD dwAtvChan, DWORD * pdwValue);

//Error message support
AFX_API_EXPORT LPCSTR DAQPilot_GetErrorMessage(DAQPilotStatusID eErrorCode);
AFX_API_EXPORT LPCSTR DAQPilot_GetLastErrorMessage();

//Event handle function
AFX_API_EXPORT DAQPilotStatusID DAQPilot_SetUserEventRef( HANDLE hTask, int EventSW, int EventType, void * rwer );
AFX_API_EXPORT DAQPilotStatusID DAQPilot_SetGptcEventRef( HANDLE hTask, USHORT GCtrNum, USHORT GMode, USHORT GSrcCtrl, USHORT GPolCtrl, ULONG GRegVal1, ULONG GRegVal2, SHORT GEventSW, SHORT GEventType, USHORT GParamID, USHORT GParamSW, void * rwer );

#ifdef __cplusplus
}
#endif
#endif // !defined(AFX_DAQPILOTAPI_H__6C0FCD3F_9A74_4149_B084_943B661B940C__INCLUDED_)
