#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Проверка на високосный год
int is_leap_year(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        return 1;
    }
    return 0;
}

// Количество дней в каждом месяце
int days_in_month(int month, int year) {
    int days_in_months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) {
        return 29; // Февраль в високосный год
    }
    return days_in_months[month - 1];
}

// Количество дней от 1 января до данной даты в том же году
int days_since_new_year(int day, int month, int year) {
    int total_days = 0;
    for (int m = 1; m < month; m++) {
        total_days += days_in_month(m, year);
    }
    total_days += day;
    return total_days;
}

// Алгоритм для определения дня недели (воскресенье = 0, понедельник = 1, и т.д.)
int get_day_of_week(int day, int month, int year) {
    // Алгоритм Зеллера
    if (month < 3) {
        month += 12;
        year--;
    }
    int K = year % 100;
    int J = year / 100;
    int f = day + (13 * (month + 1)) / 5 + K + K / 4 + J / 4 - 2 * J;
    return (f + 7) % 7;
}


// Рассчет количества секунд в промежутке времени
void calculate_time_difference(int h1, int m1, int s1, int h2, int m2, int s2, int *hours, int *minutes, int *seconds) {
    int total_seconds1 = h1 * 3600 + m1 * 60 + s1;
    int total_seconds2 = h2 * 3600 + m2 * 60 + s2;
    int total_diff = abs(total_seconds1 - total_seconds2);

    *hours = total_diff / 3600;
    *minutes = (total_diff % 3600) / 60;
    *seconds = total_diff % 60;
}

// Рассчет разницы в днях, часах, минутах и секундах между двумя датами
void calculate_date_difference(int d1, int m1, int y1, int h1, int min1, int s1,
                               int d2, int m2, int y2, int h2, int min2, int s2) {
    // Упорядочим даты, чтобы первая была больше второй
    if (y1 < y2 || (y1 == y2 && m1 < m2) || (y1 == y2 && m1 == m2 && d1 < d2)) {
        // Обмен значениями, если вторая дата больше
        int temp;
        temp = d1; d1 = d2; d2 = temp;
        temp = m1; m1 = m2; m2 = temp;
        temp = y1; y1 = y2; y2 = temp;
        temp = h1; h1 = h2; h2 = temp;
        temp = min1; min1 = min2; min2 = temp;
        temp = s1; s1 = s2; s2 = temp;
    }

    // Рассчет разницы в днях
    int total_days1 = d1;
    for (int year = y1 - 1; year >= y2; year--) {
        total_days1 += 365 + is_leap_year(year);
    }
    total_days1 += days_since_new_year(d1, m1, y1) - days_since_new_year(d2, m2, y2);

    // Рассчет разницы во времени
    int hours, minutes, seconds;
    calculate_time_difference(h1, min1, s1, h2, min2, s2, &hours, &minutes, &seconds);

    printf("Прошло: %d дней %d часов %d минут %d секунд\n", total_days1, hours, minutes, seconds);
}

int main() {

    // Рассчет разницы между датами
    calculate_date_difference(dataA1, dataA2, dataA3, timeA1, timeA2, timeA3,
                              dataB1, dataB2, dataB3, timeB1, timeB2, timeB3);

    // Определение дня недели для первой и второй даты
    char *days_of_week[] = {"Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота"};
    int dow1 = get_day_of_week(dataA1, dataA2, dataA3);
    int dow2 = get_day_of_week(dataB1, dataB2, dataB3);

    printf("День недели первой даты: %s\n", days_of_week[dow1]);
    printf("День недели второй даты: %s\n", days_of_week[dow2]);

    return 0;
}
