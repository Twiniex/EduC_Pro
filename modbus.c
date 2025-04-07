#include "modbus.h"
#include "PlcData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

DWORD WINAPI ServerThread(LPVOID lpParam) {
    Modbus_StartServer(505);
    return 0;
}


// ✅ 자동 실행 함수
void __cdecl InitServerThread(void) {
    CreateThread(NULL, 0, ServerThread, NULL, 0, NULL);
    printf("🛠 서버 쓰레드 자동 실행됨!\n");
}

#if defined(_MSC_VER)

// ✅ MSVC 호환: .CRT$XCU 섹션 등록 (MSVC에서만 작동)
#pragma section(".CRT$XCU", read)
__declspec(allocate(".CRT$XCU")) void (__cdecl* _init_server_thread_)(void) = InitServerThread;

#else
// ✅ GCC: 자동 호출 등록 (GCC에서만 작동)
__attribute__((constructor))
static void RegisterInit() {
    InitServerThread();
}
#endif



int Modbus_StartServer(int port) {
    WSADATA wsa;
    SOCKET server_sock, client_sock;
    struct sockaddr_in server, client;
    int c, recv_size;
    char recv_buf[256], send_buf[256];

    WSAStartup(MAKEWORD(2,2), &wsa);
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == INVALID_SOCKET) return -1;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    bind(server_sock, (struct sockaddr*)&server, sizeof(server));
    listen(server_sock, 3);
    printf("서버 시작됨...\n");

    c = sizeof(struct sockaddr_in);
    while ((client_sock = accept(server_sock, (struct sockaddr*)&client, &c)) != INVALID_SOCKET) {
        printf("클라이언트 접속됨\n");
        recv_size = recv(client_sock, recv_buf, sizeof(recv_buf), 0);

        if (recv_size > 0) {
            // 기본 헤더 복사
            memcpy(send_buf, recv_buf, 6);
            send_buf[6] = recv_buf[6];
            send_buf[7] = recv_buf[7];

            switch (recv_buf[7]) {
                case 4:
                    // Function Code 4
                    send_buf[9] = 200;
                    for (int i = 0; i < 100; i++) {
                        send_buf[9 + (i * 2)] = toPlc[i] >> 8;
                        send_buf[10 + (i * 2)] = toPlc[i] & 0xFF;
                    }
                    send(client_sock, send_buf, 209, 0);
                    break;

                case 23:
                    // Function Code 23
                    send_buf[9] = 200;
                    for (int i = 0; i < 100; i++) {
                        send_buf[9 + (i * 2)] = fromPlc[i] >> 8;
                        send_buf[10 + (i * 2)] = fromPlc[i] & 0xFF;
                    }
                    send(client_sock, send_buf, 209, 0);

                    for (int i = 0; i < 100; i++) {
                        toPlc[i] = (recv_buf[17 + (i * 2)] << 8) | recv_buf[18 + (i * 2)];
                    }
                    break;
            }
        }
        closesocket(client_sock);
    }

    closesocket(server_sock);
    WSACleanup();
    return 0;
}


__attribute__((used)) static void* dummy_force_reference = (void*)&InitServerThread;