
// --- Includes ---
#include "rtc.h"
#include "sram.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rtc.h"

// --- Defines ---
#define ASYNC_PREDIV	0x7F
#define SYNC_PREDIV		0xFF
#define RTC_INIT		0x12345678

// --- Init RTC ---
VOID InitRTC()
{
	if (BackupRAM[RTC_INDEX] != RTC_INIT)
	{
		RTC_InitTypeDef rtc_init = {RTC_HourFormat_24};

		// allow access to RTC
		PWR_BackupAccessCmd(ENABLE);

		// reset RTC domain
		RCC_BackupResetCmd(ENABLE);
		RCC_BackupResetCmd(DISABLE);

		// enable the LSE oscillator
		RCC_LSEConfig(RCC_LSE_ON);

		// wait for LSE oscillator running
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

		// select LSE clock source
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

		// enable the RTC clock
		RCC_RTCCLKCmd(ENABLE);
		RTC_WaitForSynchro();

		// smooth crystal calibration
		RTC_SmoothCalibConfig(RTC_SmoothCalibPeriod_32sec,0,27);

		// set divider for 1Hz
		rtc_init.RTC_AsynchPrediv = ASYNC_PREDIV;
		rtc_init.RTC_SynchPrediv = SYNC_PREDIV;
		RTC_Init(&rtc_init);

		// set saturday, 01.01.2000, 00:00
		SetRTCDate(1,1,0,6);
		SetRTCTime(0,0,0);

		// set init ok
		BackupRAM[RTC_INDEX] = RTC_INIT;
	}
}

// --- Set RTC time (24h format) ---
BOOL SetRTCTime(BYTE byHours,BYTE byMinutes,BYTE bySeconds)
{
	RTC_TimeTypeDef rtc_time;
	ErrorStatus status, syncro;

	PWR_BackupAccessCmd(ENABLE);

	rtc_time.RTC_Hours   = byHours;
	rtc_time.RTC_Minutes = byMinutes;
	rtc_time.RTC_Seconds = bySeconds;

	status = RTC_SetTime(RTC_Format_BIN,&rtc_time);
	syncro = RTC_WaitForSynchro();

	return status == SUCCESS && syncro == SUCCESS;
}

// --- Get RTC time (24h format) ---
VOID GetRTCTime(BYTE* pHours,BYTE* pMinutes,BYTE* pSeconds)
{
	RTC_TimeTypeDef rtc_time;

	RTC_GetTime(RTC_Format_BIN,&rtc_time);

	if (pHours)   *pHours   = rtc_time.RTC_Hours;
	if (pMinutes) *pMinutes = rtc_time.RTC_Minutes;
	if (pSeconds) *pSeconds = rtc_time.RTC_Seconds;
}

// --- Set RTC date ---
BOOL SetRTCDate(BYTE byDate,BYTE byMonth,BYTE byYear,BYTE byWeekDay)
{
	RTC_DateTypeDef rtc_date;
	ErrorStatus status, syncro;

	PWR_BackupAccessCmd(ENABLE);

	if (byWeekDay == 0)								// change sunday
		byWeekDay = 7;

	rtc_date.RTC_Date 	 = byDate;
	rtc_date.RTC_Month 	 = byMonth;
	rtc_date.RTC_Year 	 = byYear;
	rtc_date.RTC_WeekDay = byWeekDay;

	status = RTC_SetDate(RTC_Format_BIN,&rtc_date);
	syncro = RTC_WaitForSynchro();

	return status == SUCCESS && syncro == SUCCESS;
}

// --- Get RTC date ---
VOID GetRTCDate(BYTE* pDate,BYTE* pMonth,BYTE* pYear,BYTE* pWeekDay)
{
	RTC_DateTypeDef rtc_date;

	RTC_GetDate(RTC_Format_BIN,&rtc_date);

	if (rtc_date.RTC_WeekDay == 7)					// change sunday
		rtc_date.RTC_WeekDay = 0;

	if (pDate)    *pDate    = rtc_date.RTC_Date;
	if (pMonth)   *pMonth   = rtc_date.RTC_Month;
	if (pYear)    *pYear    = rtc_date.RTC_Year;
	if (pWeekDay) *pWeekDay = rtc_date.RTC_WeekDay;
}