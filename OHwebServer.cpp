#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>
#include <thread>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int thread_sock();
void Menu(int opt);
int cuss = 1;
int con_status = 0;
int web_status = 0;
char head_buf[] = "HTTP/1.1 200 OK\r\nAccept-Ranges: bytes\r\n\
					 Content-Length: 1024\r\n\
					 Content-Type: text/html;charset=UTF-8\r\n\
					 Connection: close\r\n\r\n";
string file_name_head = string("E:\\network_lab\\LAB1\\HTML\\");
string http_head1 = string("GET /");
string http_head2 = string("HTTP/1.1");

int main(int argc, char* argv[])
{
    int opt = 0;
    char key_opt[100];
    int exit_lable = 0;
    
    while (1) {
        Menu(opt);
        fgets(key_opt, 100, stdin);
        if (key_opt[0] == 's'&&opt<2&&opt>=0) {
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
            case 0: //生成线程启动服务
            {
                if (web_status == 1) {
                    printf("---服务已开启，不要重复操作，按回车继续---\n");
                    getchar();
                }
                else {
                    web_status = 1;
                    con_status = 1;
                    thread_sock();
                    std::cout << "test\n";
                    getchar();
                    //std::thread t1(thread_sock);
                    //t1.join();

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
                    con_status = 0;

                }
                break;
            }
            case 2: //退出程序
            {
                exit_lable = 1;
                break;
            }
            }
        }
        if (exit_lable == 1) {
            break;
        }
    }
    //防止控制台一闪而过
    printf("程序已退出，按回车键关闭窗口\n");
    getchar();
}

void Menu(int opt) {
    system("cls");
    printf("/***********************************************************************************************************************************************/\n");
    printf("                                                                                                                                      \n");
    printf("       OOOOOOOOO    HHHHHHHHH     HHHHHHHHH  SSSSSSSSSSSSSSS\n");
    printf("     OO:::::::::OO  H:::::::H     H:::::::HSS:::::::::::::::S\n");
    printf("   OO:::::::::::::OOH:::::::H     H:::::::S:::::SSSSSS::::::S\n");
    printf("  O:::::::OOO:::::::HH::::::H     H::::::HS:::::S     SSSSSSS\n");
    printf("  O::::::O   O::::::O H:::::H     H:::::H S:::::S               eeeeeeeeeeee vvvvvvv           vvvvvvveeeeeeeeeeee   rrrrr   rrrrrrrrr   \n");
    printf("  O:::::O     O:::::O H:::::H     H:::::H S:::::S             ee::::::::::::eev:::::v         v:::::ee::::::::::::ee r::::rrr:::::::::r\n");
    printf("  O:::::O     O:::::O H::::::HHHHH::::::H  S::::SSSS         e::::::eeeee:::::ev:::::v       v:::::e::::::eeeee:::::er:::::::::::::::::r \n");
    printf("  O:::::O     O:::::O H:::::::::::::::::H   SS::::::SSSSS   e::::::e     e:::::ev:::::v     v:::::e::::::e     e:::::rr::::::rrrrr::::::r\n");
    printf("  O:::::O     O:::::O H:::::::::::::::::H     SSS::::::::SS e:::::::eeeee::::::e v:::::v   v:::::ve:::::::eeeee::::::er:::::r     r:::::r\n");
    printf("  O:::::O     O:::::O H::::::HHHHH::::::H        SSSSSS::::Se:::::::::::::::::e   v:::::v v:::::v e:::::::::::::::::e r:::::r     rrrrrrr\n");
    printf("  O:::::O     O:::::O H:::::H     H:::::H             S:::::e::::::eeeeeeeeeee     v:::::v:::::v  e::::::eeeeeeeeeee  r:::::r\n");
    printf("  O::::::O   O::::::O H:::::H     H:::::H             S:::::e:::::::e               v:::::::::v   e:::::::e           r:::::r \n");
    printf("  O:::::::OOO:::::::HH::::::H     H::::::HSSSSSSS     S:::::e::::::::e               v:::::::v    e::::::::e          r:::::r\n");
    printf("   OO:::::::::::::OOH:::::::H     H:::::::S::::::SSSSSS:::::Se::::::::eeeeeeee        v:::::v      e::::::::eeeeeeee  r:::::r\n");
    printf("     OO:::::::::OO  H:::::::H     H:::::::S:::::::::::::::SS  ee:::::::::::::e         v:::v        ee:::::::::::::e  r:::::r\n");
    printf("       OOOOOOOOO    HHHHHHHHH     HHHHHHHHHSSSSSSSSSSSSSSS      eeeeeeeeeeeeee          vvv           eeeeeeeeeeeeee  rrrrrrr \n");
    printf("\n");
    printf("/***********************************************************************************************************************************************/\n\n\n\n");
    printf("欢迎来到OHSever！\n\n");
    if (web_status == 1) {
        printf("Sever状态: 已打开\n\n\n");
    }
    else {
        printf("Sever状态: 未打开\n\n\n");
    }
    printf("/***********************************************************************************************************************************************/\n");
    if (opt == 0) {
        printf("\033[1;31;44m         功能一：打开服务器\033[0m\n");
    }
    else {
        printf("         功能一：打开服务器\n");
    }
    if (opt == 1) {
        printf("\033[1;31;44m         功能二：关闭服务器\033[0m\n");
    }
    else {
        printf("         功能二：关闭服务器\n");
    }
    if (opt == 2) {
        printf("\033[1;31;44m         功能三：退出程序\033[0m\n\n");
    }
    else {
        printf("         功能三：退出程序\n\n");
    }
    printf("输入s/w可以上下移动图标，回车键进入对应功能\n");
    printf("您的输入：");                                                                                                                                        
}

int thread_sock()
{
    WSADATA wsaData;
    fd_set rfds;				//用于检查socket是否有数据到来的的文件描述符，用于socket非阻塞模式下等待网络事件通知（有数据到来）
    fd_set wfds;				//用于检查socket是否可以发送的文件描述符，用于socket非阻塞模式下等待网络事件通知（可以发送数据）
    bool first_connetion = true;

    int nRc = WSAStartup(0x0202, &wsaData);

    if (nRc) {
        printf("Winsock  startup failed with error!\n");
    }

    if (wsaData.wVersion != 0x0202) {
        printf("Winsock version is not correct!\n");
    }

    printf("Winsock  startup Ok!\n");


    SOCKET srvSocket;
    sockaddr_in addr, clientAddr;
    SOCKET sessionSocket;
    int addrLen;
    //create socket
    srvSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (srvSocket != INVALID_SOCKET)
        printf("Socket create Ok!\n");
    //set port and ip
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    //binding
    int rtn = bind(srvSocket, (LPSOCKADDR)&addr, sizeof(addr));
    if (rtn != SOCKET_ERROR)
        printf("Socket bind Ok!\n");
    //listen
    rtn = listen(srvSocket, 5);
    if (rtn != SOCKET_ERROR)
        printf("Socket listen Ok!\n");

    clientAddr.sin_family = AF_INET;
    addrLen = sizeof(clientAddr);
    char recvBuf[4096];

    u_long blockMode = 1;//将srvSock设为非阻塞模式以监听客户连接请求

    if ((rtn = ioctlsocket(srvSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO：允许或禁止套接口s的非阻塞模式。
        cout << "ioctlsocket() failed with error!\n";
        return 0;
    }
    cout << "ioctlsocket() for server socket ok!	Waiting for client connection and data\n";

    //清空read,write描述符，对rfds和wfds进行了初始化，必须用FD_ZERO先清空，下面才能FD_SET
    FD_ZERO(&rfds);
    FD_ZERO(&wfds);

    //设置等待客户连接请求
    FD_SET(srvSocket, &rfds);

    while (1) {
        char sendBuf[1000] = { '\0' };
        char rvcbuffer[1000];
        memset(rvcbuffer, 0, strlen(rvcbuffer));
        //清空read,write描述符
        FD_ZERO(&rfds);
        FD_ZERO(&wfds);

        //设置等待客户连接请求
        FD_SET(srvSocket, &rfds);

        if (!first_connetion) {
            //设置等待会话SOKCET可接受数据或可发送数据
            FD_SET(sessionSocket, &rfds);
            FD_SET(sessionSocket, &wfds);
        }

        //开始等待
        int nTotal = select(0, &rfds, &wfds, NULL, NULL);

        //如果srvSock收到连接请求，接受客户连接请求
        if (FD_ISSET(srvSocket, &rfds)) {
            nTotal--;
            //产生会话SOCKET
            sessionSocket = accept(srvSocket, (LPSOCKADDR)&clientAddr, &addrLen);
            if (sessionSocket != INVALID_SOCKET)
                printf("Socket listen one client request!\n");

            //把会话SOCKET设为非阻塞模式
            if ((rtn = ioctlsocket(sessionSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO：允许或禁止套接口s的非阻塞模式。
                cout << "ioctlsocket() failed with error!\n";
                return 0;
            }
            cout << "ioctlsocket() for session socket ok!	Waiting for client connection and data\n";
            recv(sessionSocket, rvcbuffer, sizeof(rvcbuffer), 0);

            string recvstring = string((const char*)rvcbuffer);
            
            cout << recvstring << endl;
            int file_start = recvstring.find(http_head1);
            int file_end = recvstring.find(http_head2);
            if (file_end != -1 && file_start != -1) {
                string file_name_tail = recvstring.substr(file_start + 5, file_end - file_start - 6);
                cout << file_name_tail << endl;
                int res = send(sessionSocket, head_buf, strlen(head_buf), 0);
                if (res == 0) { std::cout << "Failed write!\n"; }
                FILE* infile, * tail;
                infile = fopen((file_name_head + file_name_tail).c_str(), "rb");
                if (infile == NULL) {
                    web_status = 0;
                    printf("文件打开失败！按回车键继续\n");
                    getchar();
                    return -1;
                }
                tail = fopen((file_name_head + file_name_tail).c_str(), "rb");
                char tail_buff[1000];
                while (!feof(tail)) {
                    fgets(tail_buff, 1000, tail);
                }
                if (tail == infile) {
                    std::cout << "文件大小为0\n";
                }
                else {
                    std::cout << "文件大小：" << (unsigned)tail - (unsigned)infile << endl;
                }
                while (true)
                {
                    //缓存清零
                    int sendlen = 100;
                    memset(sendBuf, 0, sizeof(sendBuf));
                    if ((unsigned)tail - (unsigned)infile <= 100) {
                        sendlen = (unsigned)tail - (unsigned)infile;
                    }
                    std::cout << "tail-infile:" << (unsigned)tail - (unsigned)infile << endl;
                    fread(sendBuf, 1, sendlen, infile);
                    if (SOCKET_ERROR == (send(sessionSocket, sendBuf, sendlen, 0)))
                    {//发送失败
                        printf("发送失败！\n");
                        fclose(infile);
                        fclose(tail);
                        break;
                    }
                    std::cout << "发送了" << sendlen << "字节\n";
                    if (feof(infile)) {
                        printf("发送成功！\n");
                        fclose(infile);
                        fclose(tail);
                        break;
                    }

                }
            }
            else {

            }
            FD_SET(sessionSocket, &rfds);
            FD_SET(sessionSocket, &wfds);
            first_connetion = false;

        }
           
        //检查会话SOCKET是否有数据到来
        if (nTotal > 0) {
            //如果会话SOCKET有数据到来，则接受客户的数据
            if (FD_ISSET(sessionSocket, &rfds)) {
                //receiving data from client
                memset(recvBuf, '\0', 4096);
                rtn = recv(sessionSocket, recvBuf, 256, 0);
                if (rtn > 0) {
                    printf("Received %d bytes from client: %s\n", rtn, recvBuf);
                }
                else {
                    printf("Client leaving ...\n");
                    closesocket(sessionSocket);  //既然client离开了，就关闭sessionSocket
                    first_connetion = 1;
                }

            }
        }
    }
}

/*
//接下来需要同学们来处理请求的数据
        char sendBuf[100] = { '\0' };
        char rvcbuffer[1000];
        memset(rvcbuffer, 0, sizeof(rvcbuffer));
        recv(sClient, rvcbuffer, sizeof(rvcbuffer), 0);
        printf("收到一个连接:%s \r\n", inet_ntoa(remoteAddr.sin_addr));
        printf("客户信息：\n%s\n", rvcbuffer);
        FILE* infile;
        infile = fopen("E:\\network_lab\\LAB1\\OHwebServer\\html\\index.html", "rb");
        if (infile == NULL) {
            web_status = 0;
            printf("文件打开失败！按回车键继续\n");
            getchar();
            return -1;
        }
        else
            while (true)
            {
                //缓存清零
                memset(sendBuf, 0, sizeof(sendBuf));
                fread(sendBuf, 1, 100, infile);
                int sendlen;
                sendlen = strlen(sendBuf);
                if (sendlen < 100) {
                    if (SOCKET_ERROR == (send(sClient, sendBuf, sendlen, 0)))
                    {//发送失败
                        printf("发送失败！\n");
                        break;
                    }
                }
                else if (SOCKET_ERROR == (send(sClient, sendBuf, sizeof(sendBuf), 0)))
                {//发送失败
                    printf("发送失败！\n");
                    break;
                }
                if (feof(infile)) {
                    printf("发送成功！\n");
                    break;
                }

            }
        fclose(infile);
        closesocket(sClient);

*/