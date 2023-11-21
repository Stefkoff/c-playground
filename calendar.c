/**
 * Print a calendar to the console. It could print the current year calendar or any specific.
 * Build: cc calendar.c
 * run: ./a.out [year]
 *
 * Created by stefkoff on 21.11.23.
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define JANUARY 0
#define FEBRUARY 1
#define MARCH 2
#define APRIL 3
#define MAY 4
#define JUNE 5
#define JULY 6
#define AUGUST 7
#define SEPTEMBER 8
#define OCTOBER 9
#define NOVEMBER 10
#define DECEMBER 11

#define SUNDAY 0
#define MONDAY 1
#define TUESDAY 2
#define WEDNESDAY 3
#define THURSDAY 4
#define FRIDAY 5
#define SATURDAY 6

const char* DAYS_OF_WEEK[7] = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

const char* MONTH_NAME[12] = {
        "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
};


const int MONTH_DAYS[12] = {
        31, 28, 31,30, 31, 30, 31, 31,30, 31, 30, 31
};

const int MONTH_INDEX[12] = {
        0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5
};


const int getCenturyCode(const int year) {
    if(year >= 1700 && year < 1800) {
        return 4;
    } else if(year >= 1800 && year < 1900) {
        return 2;
    } else if(year >= 1900 && year < 2000) {
        return 0;
    } else if(year >= 2000 && year < 2100) {
        return 6;
    } else if(year >= 2100 && year < 2200) {
        return 4;
    } else if(year >= 2200 && year < 2300) {
        return 2;
    }

    return 0;
}

int getYearLastTo(int year) {
    return year % 100;
}

/**
 * Check if the year is leap
 * @param month
 * @param year
 * @return
 */
const int isLeapYear(const int month, const int year) {
    if(month == FEBRUARY) {
        if((year % 4) == 0) {
            // leap year

            if((year % 100) == 0 && (year % 400) == 0) {
                return 1;
            }

            return 0;
        }

        return 0;
    }

    return 0;
}
/**
 * Calculate the day of the week, based on the following formula:
 * (Year Code + Month Code + Century Code + Date Number - Leap Year Code) mod 7
 * @see https://artofmemory.com/blog/how-to-calculate-the-day-of-the-week/
 * @param day
 * @param month
 * @param year
 * @return
 */
int getDayOfWeek(int day, int month, int year) {
    int lastToYear = getYearLastTo(year);
    lastToYear = (lastToYear + (lastToYear >> 2) % 7);
    lastToYear += MONTH_INDEX[month];
    lastToYear += getCenturyCode(year);
    lastToYear += day;

    if(month < MARCH) {
        if((month == JANUARY && isLeapYear(month + 1, year)) || (month == FEBRUARY && isLeapYear(month, year))) {
            lastToYear -= 1;
        }
    }

    return (lastToYear % 7) ;
}
const int getMonthDays(const int month, const int year) {
    return MONTH_DAYS[month] + isLeapYear(month, year);
}

void printWeek(int startDay, int month, int year) {
    while(startDay <= getMonthDays(month, year)) {
        printf("%d\t", startDay);
        int dayOfWeek = getDayOfWeek(startDay, month, year);
        if(dayOfWeek == SATURDAY) {
            printf("\n");
        }
        startDay++;
    }
}

void printMonth(int month, int year) {
    const int firstDayOfWeek = getDayOfWeek(1, month, year);
    printf("\t\t%s (%d)\n\n", MONTH_NAME[month], year);
    printf("S\tM\tT\tW\tT\tF\tS\n");
    for(int i = 0; i < firstDayOfWeek; i++) {
        printf(" \t");
    }

    printWeek(1, month, year);

    printf("\n");
}

void printYear(int year) {
    int month = 0;

    while(month < 12) {
        printMonth(month, year);
        month++;
    }
}

int main(int argc, const char** argv) {
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    int year = local->tm_year + 1900;

    if(argc == 2) {
        year = atoi(argv[1]);
    }
    printYear(year);
    return 0;
}