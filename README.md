# hextime
A toy app that shows the date and time using 13-month calendar and base-16 time. 

## What is base-16 time?
I made this up because of a comment thread about how "base 12 sucks" and we should represent time elsewise.
I thought it'd be fun to just divide the day up using base-16. Using four digits, we can represent down to the seconds,
unlike in normal "base 2\*12\*60" time where this requires 6 digits (hh:mm:ss).

In base-16 time, the first digit represents 1.5 hours,
the second about 5 minutes and 38 seconds,
the third about 21 seconds,
and the fourth about 1.31 seconds.

## What is the 13-month calendar?
The 13-month calendar is one that just takes the Gregorian calendar's year, splits it into 13 months of 28 days long (4-weeks exactly), and then takes any remaining days
and puts at the end of the last month. Some versions of the 13-month calendar assert that the first day of the year is also always a Monday,
and that eve-month basically is in day-of-the-week limbo.

## Installation
If you want to use the gnome-shell example (`clock.c`), you're going to need to be on a GNOME system
with GNOME Tweaks and the Extension Manager installed,
as well as Freddez' `gnome-shell-simple-message` ([GitHub](https://github.com/freddez/gnome-shell-simple-message), [Gnome.org](https://extensions.gnome.org/extension/5018/simple-message/)). From there, all you really need to do is build from source, move the executable to somewhere in your `$PATH`,
and make sure the executable is running in the background somewhere. The plugin helpfully lets you make it so clicking it 
launches the background service, but like, I wouldn't recommend clicking it a whole bunch because I did nothing at all
to make sure it doesn't spawn a whole bunch of the same redundant process.
![image](https://github.com/user-attachments/assets/55244bac-be1b-4f66-ab23-c7fce764ee20)
