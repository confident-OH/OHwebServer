#include <WS2tcpip.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
    //初始化socket
    WORD sockVersion = MAKEWORD(2, 2);
    WSAData wasData;
    if (0 != WSAStartup(sockVersion, &wasData))
    {
        return 0;
    }
    //创建套接字
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //如果为空
    if (slisten == INVALID_SOCKET)
    {
        printf("套接字创建失败");
        return 0;
    }
    //服务器绑定需要的ip和端口
    sockaddr_in sin;             //addr地址
    sin.sin_family = AF_INET;         //ipv4
    sin.sin_port = htons(80);         //设置端口
    sin.sin_addr.S_un.S_addr = INADDR_ANY; //任意地址都可以访问  
    //绑定
    if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        printf("绑定地址失败");
    }
    //开始监听
    if (listen(slisten, 5) == SOCKET_ERROR) //可以监听的数量
    {
        printf("监听失败");
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
            printf("文件打开失败！\n");
        }
        else 
            while (true)
            {
                //缓存清零
                memset(sendBuf, 0, sizeof(sendBuf));
                fread(sendBuf, 1,sizeof(sendBuf), infile);
                if (SOCKET_ERROR == (send(sClient, sendBuf, sizeof(sendBuf), 0)))
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
        
    }
    //防止控制台一闪而过
    getchar();
}