// ConsoleApplication13.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <WS2tcpip.h>
#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

bool minus_a(int a, int b, int& c)
{
    c = a - b;
    return (a - b) > 0;
}
int main()
{
    //initialize socket
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    int winSock = WSAStartup(ver, &wsData);
    if (winSock != 0)
    {
        cerr << "not opened";
        return 403;
    }
    //create socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET)
    {
        cerr << "can not create socket";
        return 404;
    }
    //bend socket and port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;
    bind(listening, (sockaddr*)(&hint), sizeof(hint));
    //Show socket is on to listen to port
    listen(listening, SOMAXCONN);
    //get connection
    sockaddr_in client;
    int clientSize = sizeof(client);
    SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
    char host[NI_MAXHOST];
    char service[NI_MAXHOST];
    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(service, NI_MAXHOST);
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXHOST, 0) == 0) 
    {
        cout << host << "connection on port" << service << "\n";
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << "connection on port" << service << "\n";
    }
    //close listening socket
    closesocket(listening);
    //Echo
    char buff[4096];
    while (true)
    {
        ZeroMemory(buff, 4096);
        int bytesRecieved = recv(clientSocket, buff, 4096, 0);
        if (bytesRecieved == SOCKET_ERROR)
        {
            cerr << "recieving error in recv, exiting";
            break;
        }
        if (bytesRecieved == 0)
        {
            cout << "client is off";
            break;
        }


        if (bytesRecieved > 0)
        {
            if (strcmp(buff, "exit") == 0)
            {
                send(clientSocket, "Good-buy", (int)strlen("Good-buy") + 1, 0);
                break;
            }

            if (strcmp(buff, "password") == 0)
            {
                send(clientSocket, "All correct", (int)strlen("All Correct") + 1, 0);
            }
            else
            {
                send(clientSocket, buff, (int)strlen(buff) + 1, 0);
            }
        }
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
