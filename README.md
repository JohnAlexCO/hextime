# hextime
A toy app that shows the date and time using 13-month calendar and base-16 time. 
<br><img width="400px" src="https://github.com/JohnAlexCO/hextime/assets/81481181/838016f9-bc9a-4cd8-8f0a-503c401af627" />
<img width="400px" src="https://github.com/JohnAlexCO/hextime/assets/81481181/2ac5a540-abb2-4662-8f54-0be0f14403dc" />


## What is base-16 time?
I made this up because of a comment thread about how "base 12 sucks" and we should represent time elsewise.
I thought it'd be fun to just divide the day up using base-16. Using four digits, we can represent down to the seconds,
unlike in normal "base 12" time where this requires 6 digits (hh:mm:ss).

In base-16 time, the first digit represents 1.5 hours,
the second about 5 minutes and 38 seconds,
the third about 21 seconds,
and the fourth about 1.31 seconds.

## What is the 13-month calendar?
The 13-month calendar is one that just takes the Gregorian calendar's year, splits it into 13 months of 28 days long (4-weeks exactly), and then takes any remaining days
and puts at the end of the last month. Some versions of the 13-month calendar assert that the first day of the year is also always a Monday,
and that eve-month basically is in day-of-the-week limbo.

## Installation
For the applet showing the current time, save `clock.c` and `hextime.c` and clone [tigr](https://github.com/erkkah/tigr) and then compile based on the system you're on; for me in Linux, that looks like `gcc -o hexclock clock.c -lGLU -lGL -lX11`.

For standalone use, save the `hex.c` file and compile it using `gcc` or `clang`.

For use within a project, save `hextime.c` and compile it using `gcc` or `clang`.
I personally recommend just doing `gcc -o hextime ./hextime.c`.
Compilation will depend on
_<stdlib.h>_,
_<stdio.h>_,
_<time.h>_,
_<stdint.h>_, and
_<string.h>_.

## Standalone Usage

`hexclock` will open a graphical window that displays the current date and time.

`hextime` will just print the current local time in the terminal.

`hextime hh mm ss` will print the given regular time as hextime.

`hextime yyyy mm dd hh mm ss [-l]` will print the given datetime as 13-month hextime. the `-l` flag tells hextime this is a leap-year.

## Import Usage
If you'd like to use this inside of another program, 
remove the `main` function and `#include "hex.c"`.

### currentTime()
`currentTime` takes no arguments and returns a `regtime_t` struct populated with the current local date and time.

### regtime_str()
The `regtime_str` function expects to be passed `int argc` and `char **argv`.
`argc` should be the length of argv.
`argv` should store the string representations of each digit in the regular-time representation, starting at index 1 instead of 0,
such as `4, [null, "02", "33", "16"]` to represent 02:33 plus 16 sec,
or `7, [null, "1999", "04", "01", "12", "41", "00"]` to represent 12:41 plus 0 sec on April 1st, 1999.

### hextime()
The `hexTime` function expects to be passed a `regtime_t` struct, which looks like
```
typedef struct {
    uint64_t year; uint64_t mon; uint64_t mday; uint64_t yday;
    uint64_t hour; uint64_t min; uint64_t sec;
} regtime_t;
```
and will return a `hextime_t` struct which looks like
```
typedef struct {
    uint64_t year;  uint64_t mon; uint64_t mday; uint64_t yday;
    uint64_t d1;    uint64_t d2;  uint64_t d3;   uint64_t d4;
} hextime_t;
```

### print_hexTime
`print_hexTime` accepts a `hextime_t` struct and prints it out to `stdout` in a nice readable form.
