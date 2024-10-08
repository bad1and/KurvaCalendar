#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int n_button, itog;
int position = 0;
char *moving;

// int timeA1, timeA2, timeA3, timeB1, timeB2, timeB3;
// int dataA1, dataA2, dataA3, dataB1, dataB2, dataB3;

int timeA1 = 22, timeA2 = 10, timeA3 = 30, timeB1 = 10, timeB2 = 15, timeB3 = 45;
int dataA1 = 02, dataA2 = 10, dataA3 = 2024, dataB1 = 15, dataB2 = 05, dataB3 = 2004;

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

    printw("Прошло: %d дней %d часов %d минут %d секунд\n", total_days1, hours, minutes, seconds);
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
        //Enter time A
        if ((position == 0 && n_button == 10) || n_button == 49) {
            clear();
            otobrazh = false;
            printw("%s", "Введите время А (ч:м:с): ");
            otobrazh = true;

            bool isNumber1 = true;
            isdigit_check_number1 = true;
            take_number1 = true;

            //Разделение по двоеточию
            char input[100];


            scanw("%s",input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            char *ctimeA1 = strtok(input, ":");
            timeA1 = atoi(ctimeA1);
            char *ctimeA2 = strtok(NULL, ":");
            timeA2 = atoi(ctimeA2);
            char *ctimeA3 = strtok(NULL, ":");
            timeA3 = atoi(ctimeA3);


            clear();
            position = 0;
            Calc(position);

        }

        //Enter data A
        if ((position == 1 && n_button == 10) || n_button == 50) {
            clear();
            otobrazh = false;
            printw("%s", "Введите дату А (д.м.г): ");
            otobrazh = true;

            bool isNumber1 = true;
            isdigit_check_number1 = true;
            take_number1 = true;

            //Разделение по двоеточию
            char input[100];


            scanw("%s",input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            char *cdataA1 = strtok(input, ".");
            dataA1 = atoi(cdataA1);
            char *cdataA2 = strtok(NULL, ".");
            dataA2 = atoi(cdataA2);
            char *cdataA3 = strtok(NULL, ".");
            dataA3 = atoi(cdataA3);

            clear();
            position = 1;
            Calc(position);

        }

        //Enter time B
        if ((position == 2 && n_button == 10) || n_button == 51) {
            clear();
            otobrazh = false;

            printw("%s", "Введите время Б (ч:м:с): ");

            otobrazh = true;

            bool isNumber2 = true;
            isdigit_check_number2 = true;
            take_number2 = true;
            char input[100];


            scanw("%s",input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            char *ctimeB1 = strtok(input, ":");
            timeB1 = atoi(ctimeB1);
            char *ctimeB2 = strtok(NULL, ":");
            timeB2 = atoi(ctimeB2);
            char *ctimeB3 = strtok(NULL, ":");
            timeB3 = atoi(ctimeB3);


            clear();
            position = 2;
            Calc(position);
        }

        //Enter data B
        if ((position == 3 && n_button == 10) || n_button == 52) {
            clear();
            otobrazh = false;

            printw("%s", "Введите дату Б (ч:м:с): ");

            otobrazh = true;

            bool isNumber2 = true;
            isdigit_check_number2 = true;
            take_number2 = true;
            char input[100];


            scanw("%s",input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            char *cdataB1 = strtok(input, ".");
            dataB1 = atoi(cdataB1);
            char *cdataB2 = strtok(NULL, ".");
            dataB2 = atoi(cdataB2);
            char *cdataB3 = strtok(NULL, ".");
            dataB3 = atoi(cdataB3);


            clear();
            position = 3;
            Calc(position);
        }



        //Rez 1-4p
        if ((position == 4 && n_button == 10) || n_button == 53) {
            clear();

            // Рассчет разницы между датами
            calculate_date_difference(dataA1, dataA2, dataA3, timeA1, timeA2, timeA3,
                                      dataB1, dataB2, dataB3, timeB1, timeB2, timeB3);

            // Определение дня недели для первой и второй даты
            char *days_of_week[] = {"Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота"};
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

        //+ to 1 data
        if ((position == 5 && n_button == 10) || n_button == 54) {
            clear();
            position = 5;
            Calc(position);
        }

        //rez p6
        if ((position == 6 && n_button == 10) || n_button == 55) {
            clear();
            position = 6;
            Calc(position);
        }

        //+ to 1 time
        if ((position == 7 && n_button == 10) || n_button == 56 || n_button == 27) {
            clear();
            position = 7;
            Calc(position);
        }

        //rez p8
        if ((position == 8 && n_button == 10) || n_button == 57 || n_button == 27) {
            clear();
            position = 8;
            Calc(position);
        }

        //intruction
        if (position == 9 && n_button == 10) {
            clear();
            position = 9;
            otobrazh = false;
            printw("%s", "Calendar by Tikhanov Oleg\n");
            printw("%s", "ver 0.1\n");
            printw("%s", "\n");
            printw("%s", "https://github.com/bad1and/KurvaCalendar\n");
            printw("%s", "\n");
            printw("%s", "Tyt budet instruction.\n");
            n_button = getch();
            if (n_button != 27) {
                clear();
                Calc(position);
            }
        }


        //exit
        if ((position == 10 && n_button == 10) || n_button == 27) {
            break;
        }

        clear();
        endwin();
    }
    return 0;

}