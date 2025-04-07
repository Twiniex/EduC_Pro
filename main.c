#include <windows.h>
#include "modbus.h"
#include "PlcData.h"
#include <stdio.h>
#include <conio.h>
#include "HwControl.h"

extern void InitServerThread(void);
void (*dummy)(void) = InitServerThread;


int main() {
    while (1) {
        if (_kbhit()){
            char ch = _getch();
            
            if (ch == '1')
            {
                doPutOne(0, true);
            }
            if(ch == '2')
            {
                doPutOne(0, false);
            }
            if (ch == '3')
            {
                doPutOne(1, true);
            }
            if(ch == '4')
            {
                doPutOne(1, false);
            }
        }
    }
    
    return 0;
}
