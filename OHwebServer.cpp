#include <WS2tcpip.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <string.h>
#include <thread>
#include "menu.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;

#define BUFERSIZE 2048 //设置Buffersize
int thread_sock();
void Menu(int opt);
int file_size(char* filename);
int thread_client();

int web_status = 0;   //全局变量，当值为0关闭服务器，值为1开启服务器
char ports[20] = "80";  //存储端口号，默认值为80（可通过配置文件更改       
char webaddr[30] = "127.0.0.1"; //存储IP地址，默认值为localhost
string file_name_head("E:\\network_lab\\LAB1\\HTML\\"); //html文件路径
string http_head1 = string("GET /");    //定位http文件请求的文件名使用
string http_head2 = string("HTTP/1.1"); //定位http文件请求的文件名使用

int main(int argc, char* argv[])
{
    int opt = 0;
    char key_opt[10];
    int exit_lable = 0;
    while (1) {        //建立有限状态机
        Menu(opt, web_status);
        fgets(key_opt, 10, stdin);
        if (key_opt[0] == 's' && opt < 2 && opt >= 0) {
            opt++;
        }
        else if (key_opt[0] == 'w' && opt <= 2 && opt > 0) {
            opt--;
        }
        else if (key_opt[0] == 's' && opt == 2) {
            opt = 0;
        }
        else if (key_opt[0] == 'w' && opt == 0) {
            opt = 2;
        }
        else if (key_opt[0] == '\n') {
            switch (opt) {
            case 0: 
            {
                if (web_status == 1) {  
                    printf("---服务已开启，不要重复操作，按回车继续---\n");
                    getchar();
                }
                else {
                    web_status = 1; 
                    //新开线程并发服务器
                    std::thread t1(thread_sock);
                    t1.detach();
                }
                break;
            }
            case 1: // 退出服务
            {
                if (web_status == 0) {
                    printf("---服务未开启，请不要关闭未知线程,按回车继续---\n");
                    getchar();
                }
                else {
                    web_status = 0;
                    cout << "退出服务ing\n";
                    //向服务器发送退出命令
                    int quit_lable = thread_client();
                    if (quit_lable == 0) {
                        cout << "退出成功\n";
                    }
                    
                }
                break;
            }
            case 2: 
            {
                //退出程序
                exit_lable = 1;
                break;
            }
            }
        }
        if (exit_lable == 1) {
            break;
        }
    }
    printf("程序已退出，按回车键关闭窗口\n");
    //防止控制台一闪而过
    getchar();
    return 0;
} 

int thread_sock()
{
    char folderconfig[50];
    FILE* conf;
    //打开配置文件
    conf = fopen("E:\\network_lab\\LAB1\\OHwebServer\\Debug\\config.txt", "r");
    if (conf == NULL) {
        cout << "文件打开失败" << endl;
        web_status = 0;
        return 0;
    }
    else {
        //从文件中读出并设置服务器的IP地址
        fgets(webaddr, 20, conf);
        int len = strlen(webaddr); 
        webaddr[len - 1] = '\0';
        cout << "网址IP: " << webaddr << endl;
        //从配置文件中读出并设置服务器的端口
        fgets(ports, 10, conf);
        len = strlen(ports);
        ports[len] = '\0';
        cout << "端口号：" << ports << endl;
        //从配置文件中读出并设置HTML的资源路径
        fgets(folderconfig, 50, conf);
        len = strlen(folderconfig);
        folderconfig[len - 1] = '\0';
        file_name_head = string(folderconfig);
        cout << "文件地址：" << folderconfig << endl;
    }
    fclose(conf);
    unsigned long ul = 1;
    int file_names, file_namee;
    string headbuf = string("HTTP/1.1 200 OK\r\n");

    //初始化socket
    WORD sockVersion = MAKEWORD(2, 2);
    WSAData wasData;
    if (0 != WSAStartup(sockVersion, &wasData))
    {
        web_status = 0;
        printf("socket初始化失败！按回车键继续\n");
        return 1;
    }

    //创建套接字
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //检测是否创建成功
    if (slisten == INVALID_SOCKET)
    {
        web_status = 0;
        printf("套接字创建失败, 按回车键继续\n");
        return 2;
    }

    //服务器绑定需要的ip和端口
    sockaddr_in sin;                                //addr地址
    sin.sin_family = AF_INET;                       //ipv4
    sin.sin_port = htons(atoi(ports));              //设置端口
    sin.sin_addr.S_un.S_addr = inet_addr(webaddr);  //设置IP地址  
    
    //绑定socket
    if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        web_status = 0;
        printf("绑定地址失败, 按回车键继续\n");
        return 3;
    }

    //开始监听,设置可以监听的数量
    if (listen(slisten, 5) == SOCKET_ERROR)      
    {
        web_status = 0;
        printf("监听失败,按回车键继续\n");
        return 4;
    }
    
    //接听后 通过Tcp传数据
    SOCKET sClient;                 //创建接受http请求的套接字
    sockaddr_in remoteAddr;         //存储客户IP地址
    int nAddrlen = sizeof(remoteAddr);
    char revData[1024];
    while (1) {
        //开启服务器
        if (web_status == 0) {
            //全局变量改变时退出服务器
            int quit_sever;
            web_status = 0;
            closesocket(slisten);
            closesocket(sClient);
            if ((quit_sever = WSACleanup()) == SOCKET_ERROR) {
                web_status = 1;
                cout << "退出服务失败" << endl;
            }
            else {
                cout << "退出服务成功!\n";
                return 150;
            }
        }
        printf("\n等待连接...\n");
        //存储通信的socket
        sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
        if (sClient == INVALID_SOCKET) {
            //如果accept出错，重新开始循环
            continue;
        }
        else {
            char sendBuf[BUFERSIZE] = { '\0' };
            char rvcbuffer[BUFERSIZE];
            char quit_lable[10] = "quit";
            std::memset(rvcbuffer, 0, sizeof(rvcbuffer));
            recv(sClient, rvcbuffer, sizeof(rvcbuffer), 0);
            if (!strcmp(rvcbuffer, quit_lable)) {
                continue;
            }
            string rcvstring(rvcbuffer);
            file_names = rcvstring.find(http_head1);
            file_namee = rcvstring.find(http_head2);
            if (file_namee != -1 && file_names != -1) {
                char index_wen[100] = "E:\\network_lab\\LAB1\\HTML\\index.html";
                char four_zero[100] = "E:\\network_lab\\LAB1\\HTML\\404.html";
                printf("收到一个连接:%s \r\n", inet_ntoa(remoteAddr.sin_addr));
                cout << "/****************************************/" << endl;
                cout << "Http信息：" << endl << rcvstring << endl;
                cout << "/****************************************/" << endl;
                string file_name_tail = rcvstring.substr(file_names + 5, file_namee - 2 - file_names - 4);
                if (file_name_tail.empty()) {
                    ifstream infile(index_wen, ios::in | ios::binary);
                    if (!infile) {
                        ifstream infile(four_zero, ios::in | ios::binary);
                        headbuf = string("HTTP/1.1 404\r\n");
                        headbuf += string("Content-Type: text/html\r\nContent-Length: ");
                        int files = file_size(four_zero);
                        headbuf += to_string(files) + string("\r\n\r\n");
                        send(sClient, headbuf.c_str(), headbuf.length(), 0);
                        cout << "/***************** 404ERROR未找到相应文件 ********************/" << endl;
                        cout << headbuf << endl;
                        cout << "/****************************************/" << endl;
                        headbuf = string("HTTP/1.1 200 OK\r\n");
                        memset(sendBuf, 0, BUFERSIZE);
                        while (true) { //一直读到文件结束
                            infile.read((char*)sendBuf, BUFERSIZE);
                            int readedBytes = infile.gcount(); //看刚才读了多少字节
                            if (SOCKET_ERROR == (send(sClient, sendBuf, readedBytes, 0)))
                            {//发送失败
                                printf("发送失败！\n");
                                break;
                            }
                            //cout << sendBuf << endl;
                            memset(sendBuf, 0, BUFERSIZE);
                            if (infile.eof()) {
                                infile.close();
                                break;
                            }
                        }
                    }
                    else {
                        headbuf += string("Content-Type: text/html\r\nContent-Length: ");
                        int files = file_size(index_wen);
                        headbuf += to_string(files) + string("\r\n\r\n");
                        send(sClient, headbuf.c_str(), headbuf.length(), 0);
                        cout << "/****************************************/" << endl;
                        cout << headbuf << endl;

                        headbuf = string("HTTP/1.1 200 OK\r\n");
                        memset(sendBuf, 0, BUFERSIZE);
                        while (true) { //一直读到文件结束
                            infile.read((char*)sendBuf, BUFERSIZE);
                            int readedBytes = infile.gcount(); //看刚才读了多少字节
                            if (SOCKET_ERROR == (send(sClient, sendBuf, readedBytes, 0)))
                            {//发送失败
                                printf("发送失败！\n");
                                break;
                            }
                            //cout << sendBuf << endl;
                            memset(sendBuf, 0, BUFERSIZE);
                            if (infile.eof()) {
                                break;
                            }
                        }
                        cout << "发送成功" << endl;
                        cout << "/****************************************/" << endl;
                        infile.close();
                    }
                }
                else {
                    ifstream infile((file_name_head + file_name_tail).c_str(), ios::in | ios::binary);
                    if (!infile) {
                        ifstream infile(four_zero, ios::in | ios::binary);
                        headbuf = string("HTTP/1.1 404\r\n");
                        headbuf += string("Content-Type: text/html\r\nContent-Length: ");
                        int files = file_size(four_zero);
                        headbuf += to_string(files) + string("\r\n\r\n");
                        cout << "/***************** 404ERROR未找到相应文件 ********************/" << endl;
                        cout << headbuf << endl;
                        cout << "/****************************************/" << endl;
                        send(sClient, headbuf.c_str(), headbuf.length(), 0);
                        headbuf = string("HTTP/1.1 200 OK\r\n");
                        memset(sendBuf, 0, BUFERSIZE);
                        while (true) { //一直读到文件结束
                            infile.read((char*)sendBuf, BUFERSIZE);
                            int readedBytes = infile.gcount(); //看刚才读了多少字节
                            //检测是否发送失败
                            if (SOCKET_ERROR == (send(sClient, sendBuf, readedBytes, 0))){
                                printf("发送失败！\n");
                                break;
                            }
                            memset(sendBuf, 0, BUFERSIZE);
                            //文件发送完毕
                            if (infile.eof()) {
                                infile.close();
                                break;
                            }
                        }
                    }
                    else {
                        headbuf = string("HTTP/1.1 200 OK\r\n");
                        //判断文件类型设置http相应报头
                        if (file_name_tail.find(".txt") != -1 || file_name_tail.find(".html") != -1) {
                            headbuf += string("Content-Type: text/html\r\nContent-Length: ");
                            int files = file_size((char*)(file_name_head + file_name_tail).c_str());
                            headbuf += to_string(files) + string("\r\n\r\n");
                            send(sClient, headbuf.c_str(), headbuf.length(), 0);
                        }
                        else if (file_name_tail.find(".gif") != -1) {
                            headbuf += string("Content-Type: image/gif\r\nContent-Length: ");
                            int files = file_size((char*)(file_name_head + file_name_tail).c_str());
                            headbuf += to_string(files) + string("\r\n\r\n");
                            send(sClient, headbuf.c_str(), headbuf.length(), 0);
                        }
                        else if (file_name_tail.find(".mp4") != -1) {
                            headbuf += string("Content-Type: video/mp4\r\nContent-Length: ");
                            int files = file_size((char*)(file_name_head + file_name_tail).c_str());
                            headbuf += to_string(files) + string("\r\n\r\n");
                            send(sClient, headbuf.c_str(), headbuf.length(), 0);
                        }
                        else if (file_name_tail.find(".jpg") != -1) {
                            headbuf += string("Content-Type: image/jpeg\r\nContent-Length: ");
                            int files = file_size((char*)(file_name_head + file_name_tail).c_str());
                            headbuf += to_string(files) + string("\r\n\r\n");
                            send(sClient, headbuf.c_str(), headbuf.length(), 0);
                        }
                        cout << "/****************************************/" << endl;
                        cout << headbuf << endl;

                        headbuf = string("HTTP/1.1 200 OK\r\n");
                        memset(sendBuf, 0, BUFERSIZE);
                        while (true) { //一直读到文件结束
                            infile.read((char*)sendBuf, BUFERSIZE);
                            int readedBytes = infile.gcount(); //看刚才读了多少字节
                            if (SOCKET_ERROR == (send(sClient, sendBuf, readedBytes, 0)))
                            {//发送失败
                                printf("发送失败！\n");
                                break;
                            }
                            //cout << sendBuf << endl;
                            memset(sendBuf, 0, BUFERSIZE);
                            if (infile.eof()) {
                                break;
                            }
                        }
                        cout << "发送成功" << endl;
                        cout << "/****************************************/" << endl;
                        infile.close();
                    }
                }
            }
        }
        closesocket(sClient);
    }
}

int thread_client() {
    WSADATA wsaData;
    int nRc = WSAStartup(0x0202, &wsaData);
    if (nRc) {
        printf("Winsock  startup failed with error!\n");
    }
    if (wsaData.wVersion != 0x0202) {
        printf("Winsock version is not correct!\n");
    }
    printf("Winsock  startup Ok!\n");
    SOCKET clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int addrLen;
    //create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket != INVALID_SOCKET)
        printf("Socket create Ok!\n");
    //set client port and ip
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(0);
    clientAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    //binding
    int rtn = bind(clientSocket, (LPSOCKADDR)&clientAddr, sizeof(clientAddr));
    if (rtn != SOCKET_ERROR)
        printf("Socket bind Ok!\n");

    //set server's ip and port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(ports));          //设置端口号
    serverAddr.sin_addr.S_un.S_addr = inet_addr(webaddr);
    rtn = connect(clientSocket, (LPSOCKADDR)&serverAddr, sizeof(serverAddr));
    if (rtn == SOCKET_ERROR)
        printf("Connect to server error!\n");
    else printf("Connect to server ok!");
    int i;
    for(i=0;i<50;i++){
        char input[10] = "quit";
        cout << "quiting\n";
        //send data to server
        rtn = send(clientSocket,input, 8, 0);
        if (rtn == SOCKET_ERROR) {
            printf("Send to server failed\n");
            closesocket(clientSocket);
            WSACleanup();
            return -1;
        }
        //每隔0.2s发送一次关闭请求
        Sleep(200);
    }
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}

int file_size(char* filename) {
    char a[10000];
    int result = 0;
    ifstream infile(filename, ios::in | ios::binary);
    if (!infile) {
        printf("文件打开失败！\n");           //后续改为返回错误值
        return -1;
    }
    else {
        while (true) { //一直读到文件结束
            infile.read((char*)a, BUFERSIZE);
            int readedBytes = infile.gcount(); //看刚才读了多少字节
            result += readedBytes;
            if (infile.eof()) {
                infile.close();
                break;
            }
        }
    }
    return result;
}
