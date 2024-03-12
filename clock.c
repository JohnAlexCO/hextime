#include "tigr.h"
#include "tigr.c"
#include "hextime.c"
#define strsize 32
#define br 0
#define bg 0
#define bb 0
#define fr 255
#define fg 255
#define fb 255

int hexof(int v){
    if( v < 10 ){ return v + 48; }
    else { return v + 97 - 10; }
}

void strDate(hextime_t time, char *result){
    for (int i=0;i<strsize-1;i++){result[i]=0;}
    strcpy(result, months[time.mon]);
    int offset = strlen(result);
    result[offset] = 32;
    int n1 = time.mday / 10;
    int n2 = time.mday % 10+1;
    result[offset+1] = hexof(n1);
    result[offset+2] = hexof(n2);
    result[offset+3] = 0;
}

void strTime(hextime_t time, char *result){
    for (int i=0;i<strsize-1;i++){result[i]=0;}
    result[0] = hexof(time.d1); result[1] = hexof(time.d2);
    result[3] = hexof(time.d3); result[4] = hexof(time.d4);
    result[2] = 58; // colon
    result[5] = 0;
}

int main(int argc, char *argv[])
{
    // Setup hextime
    hextime_t *now = malloc(sizeof(hextime_t));
    char *str_date = malloc(strsize); 
    char *str_time = malloc(strsize);

    TPixel white = tigrRGB(fr, fg, fb);
    Tigr *screen = tigrWindow(120, 40, "Hexclock - Modula.dev", TIGR_FIXED);
    while (!tigrClosed(screen))
    {
        now = hexTime(currentTime());
        strDate(*now, str_date);
        strTime(*now, str_time);
        tigrClear(screen, tigrRGB(br, bg, bb));
        tigrPrint(screen, tfont, 5, 5, white, str_date);
        tigrPrint(screen, tfont, 5, 15, white, str_time); // stringTime()
        tigrPrint(screen, tfont, 5, 25, white, "modula.dev");
        tigrUpdate(screen);
    }
    tigrFree(screen);
    return 0;
}