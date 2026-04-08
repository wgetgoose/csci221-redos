#include "echo_chamber.h"
#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    uint8_t reverse = 0;
    // REDO: Reverse flag now works at any position
    for (uint8_t i = 0; i < argc; i++) {
        if ((argv[i][0] == '-') && (argv[i][1] == 'r')) {
            printf("Reverse activated!\n");
            reverse = 1;
        }   
    }
    // limited to 100 character strings
    char user_text [101]; 
    int copies = 0;
    printf("What is your string?\n");
    scanf("%101s", user_text);
    printf("How many copies do you want?\n");
    scanf("%d", &copies);
    switch (reverse)
    {
    case 0:
        for (uint8_t i = 0; i < copies; i++) {
            printf("%s\n", user_text);
        }
        break;
    case 1:
        // janky, janky, janky
        char reverse_text [101];
        uint8_t nul_char_index = 0;
        for (uint8_t i = 0; i <= 100; i++) {
            if (user_text[i] == '\0') {
                nul_char_index = i;
                break;
            } else {
                continue;
            }
        }
        for (uint8_t i = 0; i < nul_char_index; i++) {
            reverse_text[i] = user_text[(nul_char_index - 1 - i)];
        }
        reverse_text[nul_char_index] = '\0';
        for (uint8_t i = 0; i < copies; i++) {
            printf("%s\n", reverse_text);
        }
        break;
    }
    return 1;
}