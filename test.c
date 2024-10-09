#include <stdio.h>

// Структура для хранения даты
struct Date {
    int day;
    int month;
    int year;
};

// Функция для проверки високосного года
int is_leap_year(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        return 1;
    }
    return 0;
}

// Функция для определения количества дней в месяце
int days_in_month(int month, int year) {
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) {
        return 29; // Февраль в високосный год
    }
    return days_in_month[month - 1];
}


// Функция для добавления дней к дате
void calculate_date_difference_to_6step(int *day, int *month, int *year, int daysToAdd) {
    while (daysToAdd > 0) {
        int daysInCurrentMonth = days_in_month(*month, *year);

        // Если оставшихся дней больше, чем осталось в текущем месяце
        if (daysToAdd + *day > daysInCurrentMonth) {
            daysToAdd -= (daysInCurrentMonth - *day + 1);
            *day = 1;
            (*month)++;

            // Переход на следующий год
            if (*month > 12) {
                *month = 1;
                (*year)++;
            }
        } else {
            *day += daysToAdd;
            daysToAdd = 0;
        }
    }
    printf("Новая дата: %02d.%02d.%d\n", *day, *month, *year);
}

int main() {
    // Входные переменные
    int dataA1 = 12;  // День
    int dataA2 = 12;  // Месяц
    int dataA3 = 2023;  // Год
    int plus_data = 100;  // Количество дней для добавления

    // Добавляем дни к дате
    calculate_date_difference_to_6step(&dataA1, &dataA2, &dataA3, plus_data);

    return 0;
}
