#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

int n_button, itog;
int position = 0;
char *moving;

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
        //Enter A
        if ((position == 0 && n_button == 10) || n_button == 49) {
            clear();
            otobrazh = false;
            printw("%s", "Введите число А: ");

            char digit1[100];
            int x = 0;
            bool isNumber1 = true;

            scanw("%s", digit1);

            if (digit1[0] == '-') {
                x = 1;
            }

            while (digit1[x] != '\0') {
                if (!isdigit(digit1[x])) {
                    isNumber1 = false;
                    break;
                }
                x = x + 1;
            }

            if (isNumber1 == true) {
                number1 = atoi(digit1); //atoi - to int
                isdigit_check_number1 = true;
                take_number1 = true;
            }
            else {
                isdigit_check_number1 = false;
                take_number1 = false;
            }

            // scanw("%hu\n", &number1);
            clear();
            position = 0;
            Calc(position);

        }

        //Enter B
        if ((position == 1 && n_button == 10) || n_button == 50) {
            clear();
            otobrazh = false;
            printw("%s", "Введите число Б: ");

            char digit2[100];
            int y = 0;
            bool isNumber2 = true;

            scanw("%s", digit2);

            if (digit2[0] == '-') {
                y = 1;
            }

            while (digit2[y] != '\0') {
                if (!isdigit(digit2[y])) {
                    isNumber2 = false;
                    break;
                }
                y = y + 1;
            }

            if (isNumber2 == true) {
                number2 = atoi(digit2); //atoi - to int
                isdigit_check_number2 = true;
                take_number2 = true;
                if (number2 == 0) {
                        sec_number_zero = true;
                    }
                    else {
                        sec_number_zero = false;
                    }
            }
            else {
                isdigit_check_number2 = false;
                take_number2 = false;
            }

            clear();
            position = 1;
            Calc(position);

        }

        //Summ
        if ((position == 2 && n_button == 10) || n_button == 51) {
            clear();
            position = 2;
            Calc(position);
        }

        //Vichet
        if ((position == 3 && n_button == 10) || n_button == 52) {
            clear();
            position = 3;
            Calc(position);
        }
        //Ymnozh
        if ((position == 4 && n_button == 10) || n_button == 53) {
            clear();
            position = 4;
            Calc(position);
        }

        //del
        if ((position == 5 && n_button == 10) || n_button == 54) {
            clear();
            position = 5;
            Calc(position);
        }

        //info
        if ((position == 6 && n_button == 10) || n_button == 55) {
            clear();
            position = 6;
            Calc(position);
        }

        //close calc
        if ((position == 7 && n_button == 10) || n_button == 56 || n_button == 27) {
            clear();
            position = 7;
            Calc(position);
        }

        if ((position == 8 && n_button == 10) || n_button == 57 || n_button == 27) {
            clear();
            position = 8;
            Calc(position);
        }

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

        if ((position == 10 && n_button == 10) || n_button == 27) {
            break;
        }

        clear();
        endwin();
    }
    return 0;

}