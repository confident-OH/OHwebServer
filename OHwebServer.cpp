#include <WS2tcpip.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>
#include <thread>
#pragma comment(lib, "ws2_32.lib")

int thread_sock();
void Menu(int opt);
int con_status = 0;
int web_status = 0;

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

                }
                break;
            }
            case 1: //
            {
                if (web_status == 0) {
                    printf("---服务未开启，请不要关闭未知线程,按回车继续---\n");
                    getchar();
                }
                else {
                    web_status = 0;

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
    //初始化socket
    WORD sockVersion = MAKEWORD(2, 2);
    WSAData wasData;
    if (0 != WSAStartup(sockVersion, &wasData))
    {
        web_status = 0;
        printf("socket初始化失败！按回车键继续\n");
        getchar();
        return 1;
    }
    //创建套接字
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //如果为空
    if (slisten == INVALID_SOCKET)
    {
        web_status = 0;
        printf("套接字创建失败, 按回车键继续\n");
        getchar();
        return 2;
    }
    //服务器绑定需要的ip和端口
    sockaddr_in sin;             //addr地址
    sin.sin_family = AF_INET;         //ipv4
    sin.sin_port = htons(80);         //设置端口
    sin.sin_addr.S_un.S_addr = INADDR_ANY; //任意地址都可以访问  
    //绑定
    if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        web_status = 0;
        printf("绑定地址失败, 按回车键继续\n");
        getchar();
        return 3;
    }
    //开始监听
    if (listen(slisten, 5) == SOCKET_ERROR) //可以监听的数量
    {
        web_status = 0;
        printf("监听失败,按回车键继续\n");
        getchar();
        return 4;
    }
    //接听后 通过Tcp传数据
    SOCKET sClient;      //接收套接字
    sockaddr_in remoteAddr; //对方地址
    int nAddrlen = sizeof(remoteAddr);
    char revData[1024];
    while (1) //服务器一直服务
    {
        printf("等待连接...\n");
        //存储通信的socket
        sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
        if (sClient == INVALID_SOCKET)
        {
            printf("连接失败");
            continue;
        }
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

    }
}