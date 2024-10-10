#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int n_button, itog;
int position = 0;
char *moving;

int timeA1, timeA2, timeA3, timeB1, timeB2, timeB3;
int dataA1, dataA2, dataA3, dataB1, dataB2, dataB3;

// int timeA1 = 22, timeA2 = 10, timeA3 = 30, timeB1 = 10, timeB2 = 15, timeB3 = 45;
// int dataA1 = 02, dataA2 = 02, dataA3 = 2028, dataB1 = 15, dataB2 = 05, dataB3 = 2004;

int plus_data,plus_time_h, plus_time_m, plus_time_s;

bool take_number1 = false,take_number2 = false, f_flag = false , sec_number_zero = false, isdigit_check_number1 = true, isdigit_check_number2 = true,otobrazh = false, del_flag = false;


void Calc() {

    printw("%s", "Calendar by Tikhanov Oleg\n");
    printw("%s", "ver 0.1\n");
    printw("%s", "\n");
    printw("%s", "Перед использованием прочитайте инструкцию 10 п.\n");
    printw("%s", "-----------------\n");
    printw("%s", "\n");

    char screen[12][60] = {
        "1. Ввести первое время",
        "2. Ввести первую дату",
        "3. Ввести второе время",
        "4. Ввести вторую дату",
        "5. Результат (1-4 п.)",
        "6. К-во дней к первой дате",
        "7. Результат (6 п.)",
        "8. К-во часов к первому времени",
        "9. Результат (8 п.)",
        "10. Инструкция",
        "11. Выход",
        "",
    };

    for (int i = 0; i <= 11; ++i) {
        if (i == position) {
            printw("%s  %s\n", screen[i], "<---");
        } else {
            printw("%s\n", screen[i]);
        }

            // Check for debil
        // if (i == 11 && isdigit_check_number1 == false) {
        //     printw("%s", "В переменную А вы ввели не число!\n");
        // }
        // else if (i == 11 && take_number1 == false) {
        //     printw("%s" , "Число А не введено!\n");
        // }

        // if (i==11) {
        //     printw("%d",plus_data);
        // }


        // if (i == 11 && isdigit_check_number2 == false) {
        //     printw("%s", "В переменную Б вы ввели не число!\n");
        // }
        // else if (i == 11 && take_number2 == false) {
        //     printw("%s" , "Число Б не введено!\n");
        // }

        // if (i == 11 && otobrazh == true && f_flag == true && take_number1 == true && take_number2 == true) {
        //     if (sec_number_zero == true && del_flag == true) {
        //         printw("%s", "Делить на 0 нельзя!");
        //     }
        //     else {
        //         printw("%s %d %s %d = %d", "Результат:", number1, moving, number2, itog);
        //     }
        // }

    }
}

////Високоска для 6п
int is_leap_year_6(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        return 1;
    }
    return 0;
}

//Вискоска
int is_leap_year(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        return 1;
    }
    return 0;
}

//Дней в месяцах
int days_in_month_6(int month, int year) {
    int days_in_months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year_6(year)) {
        return 29; // Февраль в високосный год
    }
    return days_in_months[month - 1];
}

//Дней в каждом месяце
int days_in_month(int month, int year) {
    int days_in_months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) {
        return 29; // Февраль в високосный год
    }
    return days_in_months[month - 1];
}

//Дней от 01.01 до  даты в это году
int days_since_new_year(int day, int month, int year) {
    int total_days = 0;
    for (int m = 1; m < month; m++) {
        total_days += days_in_month(m, year);
    }
    total_days += day;
    return total_days;
}

//День недели - Зеллер
int get_day_of_week(int day, int month, int year) {
    if (month == 1) {
        month = 13;
        year--;
    }
    if (month == 2) {
        month = 14;
        year--;
    }
    int q = day;
    int m = month;
    int k = year % 100;
    int j = year / 100;
    int h = q + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j;
    return h % 7;
}


//Расчет секунд всего вр
void calculate_time_difference(int h1, int m1, int s1, int h2, int m2, int s2, int *hours, int *minutes, int *seconds) {
    int total_seconds1 = h1 * 3600 + m1 * 60 + s1;
    int total_seconds2 = h2 * 3600 + m2 * 60 + s2;
    int total_diff = abs(total_seconds1 - total_seconds2);

    if (total_diff / 3600 == 0) {
        *hours = 0;
    }
    else {
        *hours =( total_diff / 3600) + 1;
    }

    *minutes = (total_diff % 3600) / 60;
    *seconds = total_diff % 60;
}

//Обмен б и м даты
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
    int total_days1 = 0;
    if (y1 == y2) {
        // Если год один и тот же, просто вычитаем дни
        total_days1 = days_since_new_year(d1, m1, y1) - days_since_new_year(d2, m2, y2);
    } else {
        // Если год отличается, сначала считаем дни до конца года первой даты
        total_days1 += 365 + is_leap_year(y2) - days_since_new_year(d2, m2, y2); // Дни с начала года до второй даты
        total_days1 += days_since_new_year(d1, m1, y1); // Дни от начала года до первой даты
        // Добавляем дни для промежуточных лет
        for (int year = y2 + 1; year < y1; ++year) {
            total_days1 += 365 + is_leap_year(year);
        }
    }

    // Рассчет разницы во времени
    int hours, minutes, seconds;
    calculate_time_difference(h1, min1, s1, h2, min2, s2, &hours, &minutes, &seconds);

    printw("Прошло: %d дней %d часов %d минут %d секунд\n", total_days1, hours, minutes, seconds);
}

//доп время к 1 времени
void first_time_plus_dop_time(int h1, int min1, int s1,
                             int h2, int min2, int s2) {
    int total_hours = h1+h2;
    int total_minutes = min1 + min2;
    int total_seconds = s1 + s2;
    int total_days = 0;

    while (total_hours >= 24) {
        total_hours -= 24;
        total_days++;
    }
    while (total_minutes >= 60) {
        total_minutes -= 60;
    }
    while (total_seconds >= 60) {
        total_seconds -= 60;
    }
    printw("Прошло: %d дней %d часов %d минут %d секунд\n\n",total_days,total_hours,total_minutes,total_seconds);
}


//для 6 шага + к дням
void calculate_date_difference_to_6step(int *day, int *month, int *year, int daysToAdd) {
    while (daysToAdd > 0) {
        int daysInCurrentMonth = days_in_month_6(*month, *year);

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
    printw("Новая дата: %02d.%02d.%02d\n\n", *day, *month, *year);
}


int main() {
    setlocale(LC_ALL, "");
    initscr();
    while (true) {
        Calc(position);

        n_button = getch();
        if (n_button == 27) {
            // ESC
            n_button = getch();
            if (n_button == 91) {
                // enter
                n_button = getch();
                if (n_button == 65) {
                    // up
                    position = position - 1;
                    if (position < 0) {
                        position = 10;
                    }
                } else if (n_button == 66) {
                    // down
                    position = position + 1;
                    if (position > 10) {
                        position = 0;
                    }
                }
            }
        }


        // 49 - 55; 1 - 7
        //1 - Enter time A
        if ((position == 0 && n_button == 10) || n_button == 49) {
            clear();
            otobrazh = false;
            printw("%s", "Введите время А (Ч:М:С): ");
            otobrazh = true;

            bool isNumber1 = true;
            isdigit_check_number1 = true;
            take_number1 = true;

            //Разделение по двоеточию
            char input[100];


            scanw("%s",input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            char *ctimeA1 = strtok(input, ":");
            char *ctimeA2 = strtok(NULL, ":");
            char *ctimeA3 = strtok(NULL, ":");


            if (ctimeA1 == NULL || ctimeA2 == NULL || ctimeA3 == NULL) {
                ctimeA1 = "0";
                ctimeA2 = "0";
                ctimeA3 = "0";
            }

            timeA1 = atoi(ctimeA1);
            timeA2 = atoi(ctimeA2);
            timeA3 = atoi(ctimeA3);


            clear();
            position = 0;
            Calc(position);

        }

        //2 - Enter data A
        if ((position == 1 && n_button == 10) || n_button == 50) {
            clear();
            otobrazh = false;
            printw("%s", "Введите дату А (Д.М.Г (01.01.2020)): ");
            otobrazh = true;

            bool isNumber1 = true;
            isdigit_check_number1 = true;
            take_number1 = true;

            //Разделение по двоеточию
            char input[100];


            scanw("%s",input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            char *cdataA1 = strtok(input, ".");
            char *cdataA2 = strtok(NULL, ".");
            char *cdataA3 = strtok(NULL, ".");

            if (cdataA1 == NULL || cdataA2 == NULL || cdataA3 == NULL) {
                cdataA1 = "0";
                cdataA2 = "0";
                cdataA3 = "0";
            }

            dataA1 = atoi(cdataA1);
            dataA2 = atoi(cdataA2);
            dataA3 = atoi(cdataA3);

            clear();
            position = 1;
            Calc(position);

        }

        //3 - Enter time B
        if ((position == 2 && n_button == 10) || n_button == 51) {
            clear();
            otobrazh = false;

            printw("%s", "Введите время Б (Ч:М:С): ");

            otobrazh = true;

            bool isNumber2 = true;
            isdigit_check_number2 = true;
            take_number2 = true;
            char input[100];


            scanw("%s",input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            char *ctimeB1 = strtok(input, ":");
            char *ctimeB2 = strtok(NULL, ":");
            char *ctimeB3 = strtok(NULL, ":");


            if (ctimeB1 == NULL || ctimeB2 == NULL || ctimeB3 == NULL) {
                ctimeB1 = "0";
                ctimeB2 = "0";
                ctimeB3 = "0";
            }

            timeB1 = atoi(ctimeB1);
            timeB2 = atoi(ctimeB2);
            timeB3 = atoi(ctimeB3);

            clear();
            position = 2;
            Calc(position);
        }

        //4 - Enter data B
        if ((position == 3 && n_button == 10) || n_button == 52) {
            clear();
            otobrazh = false;

            printw("%s", "Введите дату Б (Д.М.Г (01.01.2020)): ");

            otobrazh = true;

            bool isNumber2 = true;
            isdigit_check_number2 = true;
            take_number2 = true;
            char input[100];


            scanw("%s",input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            char *cdataB1 = strtok(input, ".");
            char *cdataB2 = strtok(NULL, ".");
            char *cdataB3 = strtok(NULL, ".");

            if (cdataB1 == NULL || cdataB2 == NULL || cdataB3 == NULL) {
                cdataB1 = "0";
                cdataB2 = "0";
                cdataB3 = "0";
            }

            dataB1 = atoi(cdataB1);
            dataB2 = atoi(cdataB2);
            dataB3 = atoi(cdataB3);

            clear();
            position = 3;
            Calc(position);
        }

////////////////

        //5 - Rez 1-4p
        if ((position == 4 && n_button == 10) || n_button == 53) {
            clear();

            // Рассчет разницы между датами
            calculate_date_difference(dataA1, dataA2, dataA3, timeA1, timeA2, timeA3,
                                      dataB1, dataB2, dataB3, timeB1, timeB2, timeB3);

            // Определение дня недели для первой и второй даты
            char *days_of_week[] = {"Суббота", "Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница"};
            int dow1 = get_day_of_week(dataA1, dataA2, dataA3);
            int dow2 = get_day_of_week(dataB1, dataB2, dataB3);

            printw("День недели первой даты: %s\n", days_of_week[dow1]);
            printw("День недели второй даты: %s\n\n", days_of_week[dow2]);
            printw("%s", "Для выхода в главное меню нажмите любую кнопку...\n");
            n_button = getch();
            if (n_button != 27) {
                clear();
                position = 4;
                Calc(position);
            }
        }


        //6 - + to 1 data
        if ((position == 5 && n_button == 10) || n_button == 54) {
            clear();

            printw("%s", "Введите сколько дней вы хотите добавить к первой дате: ");
            scanw("%d",&plus_data);

            clear();
            position = 5;
            Calc(position);
        }

        //7 - rez p6
        if ((position == 6 && n_button == 10) || n_button == 55) {
            clear();

            printw("Первая дата: %02d.%02d.%02d\n",dataA1,dataA2,dataA3);
            printw("Сколько дней прибавить: %d\n",plus_data);
            // Рассчет разницы между датами
            calculate_date_difference_to_6step(&dataA1, &dataA2, &dataA3, plus_data);

            printw("%s", "Для выхода в главное меню нажмите любую кнопку...\n");
            n_button = getch();
            if (n_button != 27) {
                clear();
                position = 6;
                Calc(position);
            }
        }


        //8 - + to 1 time
        if ((position == 7 && n_button == 10) || n_button == 56) {
            clear();
            otobrazh = false;

            printw("%s", "Введите сколько прибавить к 1 времени (Ч:М:С): ");

            otobrazh = true;

            char input[100];

            scanw("%s",input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            char *cplus_time1 = strtok(input, ":");
            char *cplus_time2 = strtok(NULL, ":");
            char *cplus_time3 = strtok(NULL, ":");

            if (cplus_time1 == NULL || cplus_time2 == NULL || cplus_time3 == NULL) {
                cplus_time1 = "0";
                cplus_time2 = "0";
                cplus_time3 = "0";
            }

            plus_time_h = atoi(cplus_time1);
            plus_time_m = atoi(cplus_time2);
            plus_time_s = atoi(cplus_time3);

            clear();
            position = 7;
            Calc(position);
        }


        //9 - rez p8
        if ((position == 8 && n_button == 10) || n_button == 57) {
            clear();

            printw("Первое время: %02d:%02d:%02d\n", timeA1, timeA2, timeA3);
            printw("Сколько времени прибавить: %02d:%02d:%02d\n", plus_time_h, plus_time_m, plus_time_s);

            first_time_plus_dop_time(timeA1, timeA2, timeA3,
                                        plus_time_h,plus_time_m,plus_time_s);

            printw("%s", "Для выхода в главное меню нажмите любую кнопку...\n");

            n_button = getch();
            if (n_button != 27) {
                clear();
                position = 8;
                Calc(position);
            }
        }


        //10 - intruction
        if (position == 9 && n_button == 10) {
            clear();
            position = 9;
            otobrazh = false;
            printw("%s", "Calendar by Tikhanov Oleg\n");
            printw("%s", "ver 0.1\n");
            printw("%s", "\n");
            printw("%s", "https://github.com/bad1and/KurvaCalendar\n");
            printw("%s", "\n");
            printw("%s", "Tyt budet instruction...)\n");
            n_button = getch();
            if (n_button != 27) {
                clear();
                Calc(position);
            }
        }


        //11 - exit
        if ((position == 10 && n_button == 10) || n_button == 27) {
            break;
        }

        clear();
        endwin();
    }
    return 0;

}