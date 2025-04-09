#include <windows.h>
#include "modbus.h"
#include "PlcData.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include "HwControl.h"

extern void InitServerThread(void);
void (*dummy)(void) = InitServerThread;

#define CMD_MAX_LEN 32

// 모드 상태 전역변수
bool isAutoMode = false;

// 명령 처리 함수 선언
void handleCommand(const char* cmd);
void setAutoMode(bool enable);
void runCw(bool enable);
void runCcw(bool enable);
void stopMotor(void);
bool IsCwSensor(void);
bool IsCcwSensor(void);

int main() {
    char text[CMD_MAX_LEN] = {0};
    int text_idx = 0;
    int nStep = 0;

    while (1) {
        if (_kbhit()) {
            char ch = _getch();

            if (ch == '\r' || ch == '\n') {
                text[text_idx] = '\0';  // 문자열 종료
                printf("\n");

                handleCommand(text);    // 명령어 처리 함수 호출

                text_idx = 0;           // 초기화
                text[0] = '\0';
            }
            else if (ch == '\b' && text_idx > 0) {
                text[--text_idx] = '\0';
                printf("\b \b");
            }
            else if (text_idx < CMD_MAX_LEN - 1 && ch >= 32 && ch <= 126) {
                text[text_idx++] = ch;
                text[text_idx] = '\0';
                putchar(ch);
            }
        }
        
        if(isAutoMode){
            switch (nStep)
            {
            case 0:
                if (IsCcwSensor()){
                    runCw(true);
                    runCcw(false);
                    nStep = 100;
                }
                break;
            case 100:
                if (IsCwSensor()){
                    runCcw(true);
                    runCw(false);
                    nStep = 0;
                }
                break;
            default:
                break;
            }
        }
        Sleep(10);
    }

    return 0;
}

void handleCommand(const char* cmd) {
    if (strcmp(cmd, "auto") == 0) {
        setAutoMode(true);
    }
    else if (strcmp(cmd, "manual") == 0) {
        setAutoMode(false);
    }
    else if (strcmp(cmd, "cw run") == 0) {
        if(!isAutoMode) runCw(true);
    }
    else if (strcmp(cmd, "ccw run") == 0) {
        if(!isAutoMode) runCcw(true);
    }
    else if (strcmp(cmd, "stop") == 0) {
        if(!isAutoMode) stopMotor();
    }
    else {
        printf("unknown command: %s\n", cmd);
    }
}

void setAutoMode(bool enable) {
    isAutoMode = enable;
    printf("%s mode changed\n", enable ? "auto" : "manual");
}

void runCw(bool enable) {
    doPutOne(0, enable);
    printf("CW Run started\n");
}

void runCcw(bool enable) {
    doPutOne(1, enable);
    printf("CCW Run started\n");
}

void stopMotor(void) {
    doPutOne(0, false);
    doPutOne(1, false);
    printf("Motor stopped\n");
}

bool IsCwSensor(void){
    return diGetOne(1);
}

bool IsCcwSensor(void){
    return diGetOne(0);
}