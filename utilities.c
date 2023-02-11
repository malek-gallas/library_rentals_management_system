#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "headers.h"

int is_alpha_space(int c){
    return (isalpha(c) || c == ' ') && !isdigit(c) && !ispunct(c);
}
int is_print(int c){
    return isprint(c);
}

void check_string_is_valid(char *msg, char *data, int (*rule)(int)){
    char user_input[BUFFER_SIZE];
    int valid=0;
    while (!valid) {
        printf("%s",msg);
        fflush (stdin);
        fgets (user_input, sizeof(user_input), stdin);
        strcpy (data, user_input);
        data[strcspn(data, "\n")] = '\0';
        int len = strlen(data);
        if (len >= 2 && len <= 15) {
            valid = 1;
            for (int i = 0; i < len; i++) {
                if (!rule(data[i])) {
                    valid = 0;
                    break;
                }
            }
        }
        if (!valid){
            printf("==> Invalid Input.\n");
        }
    }
}

