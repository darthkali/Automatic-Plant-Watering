
#ifndef RTC_H
#define RTC_H

// --- Includes ---
#include "conf.h"
#include "types.h"

// --- Prototypes ---
VOID InitRTC();
BOOL SetRTCTime(BYTE byHours,BYTE byMinutes,BYTE bySeconds);
VOID GetRTCTime(BYTE* pHours,BYTE* pMinutes,BYTE* pSeconds);
BOOL SetRTCDate(BYTE byDate,BYTE byMonth,BYTE byYear,BYTE byWeekDay);
VOID GetRTCDate(BYTE* pDate,BYTE* pMonth,BYTE* pYear,BYTE* pWeekDay);

#endif