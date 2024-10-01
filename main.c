#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int n_button, itog;
int position = 0;
char *moving;
char *timeA1, *timeA2, *timeA3, *timeB1, *timeB2, *timeB3;
char *dataA1, *dataA2, *dataA3, *dataB1, *dataB2, *dataB3;


short int number1,number2;
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
        if (i == 11) {
            printw("Time A: %s %s %s\n", timeA1, timeA2, timeA3);
            printw("Data A: %s %s %s\n", dataA1, dataA2, dataA3);
            printw("Time B: %s %s %s\n", timeB1, timeB2, timeB3);
            printw("Data B: %s %s %s", dataB1, dataB2, dataB3);
        }

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

            timeA1 = strtok(input, ":");
            timeA2 = strtok(NULL, ":");
            timeA3 = strtok(NULL, ":");


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

            dataA1 = strtok(input, ".");
            dataA2 = strtok(NULL, ".");
            dataA3 = strtok(NULL, ".");

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

            timeB1 = strtok(input, ":");
            timeB2 = strtok(NULL, ":");
            timeB3 = strtok(NULL, ":");


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

            dataB1 = strtok(input, ".");
            dataB2 = strtok(NULL, ".");
            dataB3 = strtok(NULL, ".");


            clear();
            position = 3;
            Calc(position);
        }



        //Rez 1-4p
        if ((position == 4 && n_button == 10) || n_button == 53) {
            clear();
            position = 4;
            Calc(position);
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