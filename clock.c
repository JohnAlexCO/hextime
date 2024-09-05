/*
    The new below example is an integration with the GNOME extension
        https://extensions.gnome.org/extension/5018/simple-message/
    and allows it to be used to display the time in base-16
*/
#include <unistd.h>
#include <stdbool.h>
#include "hextime.c"

#define offset 65
char *timeBuffer[255];
char AMPM[] = {"AM\0"};
int hexof(int v) { if( v < 10 ){ return v + '0'; } if ( v > 15 ) { return 'F'; } return v + 'A' - 10; }
void strTime(hextime_t time, regtime_t r){
    /* Hexidecimal v. Sexagesimal */
    if (r.hour >=12 ) { AMPM[0]='P'; } else { AMPM[0]='A'; }
    if (r.hour > 12)  { r.hour-=12; }
    sprintf(
        timeBuffer,
        "dconf write /org/gnome/shell/extensions/simple-message/message \
        '\"%c%c:%c%c\t%d:%02d.%02d %s\"'",
        hexof(time.d1), hexof(time.d2), hexof(time.d3), hexof(time.d4),
        r.hour, r.min, r.sec, AMPM
    );
}

void updateTime(regtime_t *r, hextime_t *h){
    regTime(r); hexTime(h, r); strTime(*h, *r);
}

#define updatetime  120
#define sleeptime   300
int main(int argc, char **argv)
{
    int until = 0; char last = 'x';
    regtime_t *r = malloc(sizeof(regtime_t));
    hextime_t *h = malloc(sizeof(hextime_t));
    updateTime(r, h);
    while (true) {
        updateTime(r, h);
        if ( last != timeBuffer[4] ) {
            last = timeBuffer[4];
            system(timeBuffer);
        }   sleep(1);
    }
    return 0;
}