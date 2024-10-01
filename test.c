//char digit1[100];
//char *a[10];
//int i = 0;
//
//fgets(digit1, sizeof(digit1), stdin);
//
//digit1[strcspn(digit1, "\n")] = 0;
//
//char *token = strtok(digit1, ":");
//while (token != NULL && i < 10) {
//    a[i++] = token;
//    token = strtok(NULL, ":");
//}

#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    char *num1, *num2, *num3;

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character

    num1 = strtok(input, ":");
    num2 = strtok(NULL, ":");
    num3 = strtok(NULL, ":");

    // printf("%s %s %s\n", num1, num2, num3);

    return 0;
}





