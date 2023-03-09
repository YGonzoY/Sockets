// ConsoleApplication13Client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <WS2tcpip.h>
#include <windows.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;


int main()
{
    string adress = "127.0.0.1";
    int port = 54000;
    //initialize socket
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    int winSock = WSAStartup(ver, &wsData);
    if (winSock != 0)
    {
        cerr << "can not initialize Winsock";
        return 403;
    }
    //create socket
    SOCKET connection = socket(AF_INET, SOCK_STREAM, 0);
    if (connection == 0)
    {
        cerr << "can not initialize SOCKET";
        return 404;
    }
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, adress.c_str(), &hint.sin_addr);
    int connResult = connect(connection, (sockaddr*)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR)
    {
        cerr << "no connection" << WSAGetLastError() << "\n";
        closesocket(connection);
        WSACleanup();
        return 0;
    }
    char buff[4096];
    string userInput;
    do
    {
        cout << ">";
        getline(cin, userInput);
        if (userInput.size() > 0)
        {
            int sendResult = send(connection, userInput.c_str(), (int)(userInput.size()) + 1, 0);
            if (sendResult != SOCKET_ERROR)
            {
                ZeroMemory(buff, 4096);
                int bytesRecieved = recv(connection, buff, 4096, 0);
                if (bytesRecieved > 0)
                {
                    cout << "SERVER" << string(buff, 0, bytesRecieved);
                }
            }
        }
    } while (userInput.size() > 0);
    int error = closesocket(connection);
    WSACleanup();
    return 0;
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
