#ifndef MODBUS_H
#define MODBUS_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

int Modbus_StartServer(int port);
DWORD WINAPI ServerThread(LPVOID lpParam);  // 이미 있을 수도 있음

#ifdef __cplusplus
}
#endif

#endif