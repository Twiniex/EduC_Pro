#include <windows.h>
#include "modbus.h"
#include "PlcData.h"
#include <stdio.h>
#include <conio.h>
#include "HwControl.h"

extern void InitServerThread(void);
void (*dummy)(void) = InitServerThread;

// toPlc[90] 과 fromPlc[90] 을 써야 한다.
int main() {
    char text[10];
    int text_idx;

    while (1) {
        if (_kbhit()){
            char ch = _getch();
            if (ch == '\r' || ch == '\n'){
                text[text_idx] = '\0';

                if (strcmp(text, "auto") == 0){
                    printf("auto mode changed\n");
                }else if (strcmp(text, "manual") == 0){
                    printf("manual mode changed\n");
                }else{
                    printf("unknown command : %s\n", text);
                }

                text_idx = 0;
                text[0] = '\0';
            }
            else if (ch == '\b' && text_idx > 0){
                text[--text_idx] = '\0';
                printf("\b \b");
            }
            else if (text_idx < sizeof(text) - 1 && ch >= 32 && ch <= 126){
                text[text_idx++] = ch;
                text[text_idx] = '\0';
                putchar(ch);
            }
        }
        Sleep(10);
    }
    
    return 0;
}
