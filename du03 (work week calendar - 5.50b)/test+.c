#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct
{
  int m_TotalDays;
  int m_WorkDays;
} TResult;
#endif /* __PROGTEST__ */

/*
roky nejsou přestupné,
s výjimkou let dělitelných 4, které jsou přestupné,
s výjimkou let dělitelných 100, které nejsou přestupné,
s výjimkou let dělitelných 400, které jsou přestupné,
s výjimkou let dělitelných 4000, které nejsou přestupné.
*/
int isYearLeap (int year) {
    if (year % 4 == 0 && (year % 100 != 0 || (year % 400 == 0 && year % 4000 != 0))) {
        return 1;
    }
    return 0;
}
/*
STATNI SVATKY
*/
int isHoliday(int day, int month) {
    if (month == 1 && day == 1) return 1;
    if (month == 5 && (day == 1 || day == 8)) return 1;
    if (month == 7 && (day == 5 || day == 6)) return 1;
    if (month == 9 && day == 28) return 1;
    if (month == 10 && day == 28) return 1;
    if (month == 11 && day == 17) return 1;
    if (month == 12 && (day == 24 || day == 25 || day == 26)) return 1;
    return 0;
}
/**
 * DNY V TYDNU
 * 0 - Nedele
 * 1 - Pondeli
 * 2 - Utery
 * 3 - Streda
 * 4 - Ctvrtek
 * 5 - Patek
 * 6 - Sobota
*/
int dayOfWeek(int year, int month, int dayNumber){
    int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(isYearLeap(year)){
        months[1] = 29;
    }
    for(int i = 1900; i < year; i++){
        if(isYearLeap(i)){
            dayNumber += 366;
        } else {
            dayNumber += 365;
        }
    }
    for (int i = 0; i < month - 1; i++){
        dayNumber += months[i];
    }
    return dayNumber % 7;
}

int isValidDate(int year, int month, int day) {
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 2000) {
        return 0;
    }
    if (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) {
        return 0;
    }
    if (month == 2) {
        if (day > 29) {
            return 0;
        }
        if (day == 29 && !isYearLeap(year)) {
            return 0;
        }
    }
    return 1;
}

bool isWorkDay(int year, int month, int day){
    if(!isValidDate(year, month, day)){
      return false;
    }
    int dayNumber = dayOfWeek(year, month, day);
    if(dayNumber >= 1 && dayNumber <= 5 && !isHoliday(day, month)){
        return true;
    }
    return false;
}

TResult countDays(int y1, int m1, int d1, int y2, int m2, int d2) {
    TResult result = {-1, -1};

    if (y1 > y2 || (y1 == y2 && m1 > m2) || (y1 == y2 && m1 == m2 && d1 > d2)) {
        return result;
    }
    if (!isValidDate(y1, m1, d1) || !isValidDate(y2, m2, d2)) {
        return result;
    }

    int total_days = (y2 - y1) * 365 + (y2 - y1) / 4 - (y2 - y1) / 100 + (y2 - y1) / 400 - (y2 - y1) / 4000;
    total_days += ((m2 * 306 + 5) / 10) - ((m1 * 306 + 5) / 10);
    total_days += d2 - d1;

    int work_days = total_days - total_days / 7 * 2; // subtract weekends

    // subtract holidays
    for (int year = y1; year <= y2; year++) {
        if (isHoliday(1, 1) && isValidDate(year, 1, 1)) work_days--;
        if (isHoliday(1, 5) && isValidDate(year, 5, 1)) work_days--;
        if (isHoliday(8, 5) && isValidDate(year, 5, 8)) work_days--;
        if (isHoliday(5, 7) && isValidDate(year, 7, 5)) work_days--;
        if (isHoliday(6, 7) && isValidDate(year, 7, 6)) work_days--;
        if (isHoliday(28, 9) && isValidDate(year, 9, 28)) work_days--;
        if (isHoliday(28, 10) && isValidDate(year, 10, 28)) work_days--;
        if (isHoliday(17, 11) && isValidDate(year, 11, 17)) work_days--;
        if (isHoliday(24, 12) && isValidDate(year, 12, 24)) work_days--;
        if (isHoliday(25, 12) && isValidDate(year, 12, 25)) work_days--;
        if (isHoliday(26, 12) && isValidDate(year, 12, 26)) work_days--;
    }

    result.m_TotalDays = total_days;
    result.m_WorkDays = work_days;
    return result;
}



#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{

  TResult r;
  assert ( isWorkDay ( 2023, 10, 10 ) );
  assert ( ! isWorkDay ( 2023, 11, 11 ) );
  assert ( ! isWorkDay ( 2023, 11, 17 ) );
  assert ( ! isWorkDay ( 2023, 11, 31 ) );
  assert ( ! isWorkDay ( 2023,  2, 29 ) );
  assert ( ! isWorkDay ( 2004,  2, 29 ) );
  assert ( isWorkDay ( 2008,  2, 29 ) );
  assert ( ! isWorkDay ( 2001,  2, 29 ) );
  assert ( ! isWorkDay ( 1996,  1,  2 ) );
  
  r = countDays ( 2023, 11,  1,
                  2023, 11, 30 );
  assert ( r . m_TotalDays == 30 );
  assert ( r . m_WorkDays == 21 );
  r = countDays ( 2023, 11,  1,
                  2023, 11, 17 );
  assert ( r . m_TotalDays == 17 );
  assert ( r . m_WorkDays == 12 );
  r = countDays ( 2023, 11,  1,
                  2023, 11,  1 );
  assert ( r . m_TotalDays == 1 );
  assert ( r . m_WorkDays == 1 );
  r = countDays ( 2023, 11, 17,
                  2023, 11, 17 );
  assert ( r . m_TotalDays == 1 );
  assert ( r . m_WorkDays == 0 );
  r = countDays ( 2023,  1,  1,
                  2023, 12, 31 );
  assert ( r . m_TotalDays == 365 );
  assert ( r . m_WorkDays == 252 );
  r = countDays ( 2024,  1,  1,
                  2024, 12, 31 );
  assert ( r . m_TotalDays == 366 );
  assert ( r . m_WorkDays == 254 );
  r = countDays ( 2000,  1,  1,
                  2023, 12, 31 );
  assert ( r . m_TotalDays == 8766 );
  assert ( r . m_WorkDays == 6072 );
  r = countDays ( 2001,  2,  3,
                  2023,  7, 18 );
  assert ( r . m_TotalDays == 8201 );
  assert ( r . m_WorkDays == 5682 );
  r = countDays ( 2021,  3, 31,
                  2023, 11, 12 );
  assert ( r . m_TotalDays == 957 );
  assert ( r . m_WorkDays == 666 );
  r = countDays ( 2001,  1,  1,
                  2000,  1,  1 );
  assert ( r . m_TotalDays == -1 );
  assert ( r . m_WorkDays == -1 );
  r = countDays ( 2001,  1,  1,
                  2023,  2, 29 );
  assert ( r . m_TotalDays == -1 );
  assert ( r . m_WorkDays == -1 );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
