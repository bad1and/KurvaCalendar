#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

char getchh() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);           // настройки терминала
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);         // выкл отображение символов
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // применение изменений в newt
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // возврат настроек
    return ch;
}

int main() {
    char time[9];
    int index = 0;

    printf("Введите время в формате HHMMSS: ");


    while (index < 6) {
        char ch = getchh();  // получение
        if (ch >= '0' && ch <= '9') {
            if (index == 2 || index == 4) {
                printf(":");
            }
            printf("%c", ch);
            time[index] = ch;  // сохранениее цифры в память
            index++;
        }
    }

    time[6] = '\0';


    char hours[3], minutes[3], seconds[3];


    hours[0] = time[0];
    hours[1] = time[1];
    hours[2] = '\0';

    minutes[0] = time[2];
    minutes[1] = time[3];
    minutes[2] = '\0';

    seconds[0] = time[4];
    seconds[1] = time[5];
    seconds[2] = '\0';

    int h = atoi(hours);
    int m = atoi(minutes);
    int s = atoi(seconds);

    printf("\nЧасы: %d, Минуты: %d, Секунды: %d\n", h, m, s);
    return 0;
}
