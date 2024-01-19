#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#define sizebump 60
#define true 1
#define false 0

void error(char *str){ printf("%s\n", str); exit(1); }
char *help = "hextime 0.0.0\n\thextime (convert current time to hextime)\n\thextime hh mm ss (convert given time to hextime)\n\thextime yyyy mm dd hh mm ss [-l] (convert given timedate to hex timeday, set -l for leap years)";
const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December", "Eve"};

typedef struct {
    uint64_t year;
    uint64_t mon;
    uint64_t mday;
    uint64_t yday;
    uint64_t hour;
    uint64_t min;
    uint64_t sec;
} regtime_t;

typedef struct {
    uint64_t year;
    uint64_t mon;
    uint64_t mday;
    uint64_t yday;
    uint64_t d1;
    uint64_t d2;
    uint64_t d3;
    uint64_t d4;
} hextime_t;

void print_hexTime(hextime_t *hex){ printf("%d %s %d, %1x%1x:%1x%1x\n", hex->mday+1, months[hex->mon], hex->year, hex->d1, hex->d2, hex->d3, hex->d4); }

int daysIntoYear(int year, int month, int day, int leap) {
    int MonthInc[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; if ( leap == 1 ) { MonthInc[1]++; } 
    int days = 0;
    for (int i = 1; i < month; i++) { days += MonthInc[i]; }
    days += day;
    return days; }

regtime_t *regtime_str(int argc, char **argv){
    regtime_t *stamp = malloc(sizeof(regtime_t));
    int leap = (argc == 8)? true:false;
    if (argc == 4){
        stamp->year = 1900;
        stamp->mon = 0;
        stamp->mday = 0;
        stamp->yday = 0;
        stamp->hour = atoi( argv[1] );
        stamp->min = atoi( argv[2] );
        stamp->sec = atoi( argv[3] );
    }
    else if (argc >= 7){
        stamp->year = atoi( argv[1]);
        stamp->mon = atoi( argv[2] );
        stamp->mday = atoi( argv[3] )-1;
        stamp->hour = atoi( argv[4] );
        stamp->min = atoi( argv[5] );
        stamp->sec = atoi( argv[6] );
    } else { error(help); }
    if (stamp->mon > 12 || stamp->mday > 31 || stamp->hour > 23 || stamp->min > 59 || stamp->sec > 59) { error("invalid timestamp"); }
    stamp->yday = daysIntoYear(stamp->year, stamp->mon, stamp->mday, leap);
    return stamp;
}
regtime_t *currentTime(){
    regtime_t *now = malloc(sizeof(regtime_t));
    time_t rawtime; time ( &rawtime );
    struct tm * dtime; dtime = localtime ( &rawtime );
    now->year = dtime->tm_year + 1900;
    now->mon = dtime->tm_mon;
    now->mday = dtime->tm_mday;
    now->yday = dtime->tm_yday;
    now->hour = dtime->tm_hour;
    now->min = dtime->tm_min;
    now->sec = dtime->tm_sec;
    return now;
}
hextime_t *hexTime(regtime_t *dtime){
    hextime_t *hex = malloc(sizeof(hextime_t));
    // Month and Month-day
    hex->year =     dtime->year;
    hex->yday =     dtime->yday;
    hex->mon =      dtime->yday / 28; if (hex->mon > 12){hex->mon = 12;}
    hex->mday =     hex->yday - (hex->mon * 28);
    // Cast time to dayseconds
    uint64_t maxdayseconds = 24*60*60;
    uint64_t dayseconds = \
        ( (dtime->hour * (60*60)) +
        (dtime->min * (60)) +
        (dtime->sec) ) * sizebump;
    // Current time in hex units
    uint64_t db1 = 5400     * sizebump;
    uint64_t db2 = 337.5    * sizebump;
    uint64_t db3 = 21.09    * sizebump;
    uint64_t db4 = 1.31     * sizebump;
    hex->d1 = dayseconds / db1;
    hex->d2 = (dayseconds - (db1*hex->d1)) / db2;
    hex->d3 = (dayseconds - (db1*hex->d1) - (db2*hex->d2)) / db3;
    hex->d4 = (dayseconds - (db1*hex->d1) - (db2*hex->d2) - (db3*hex->d3)) / db4;
    return hex;
}
