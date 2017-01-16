//
//  main.c
//  CSocket
//
//  Created by apple on 2017/1/16.
//  Copyright © 2017年 plters. All rights reserved.
//

#include <stdio.h> //基本输入输出
#include <sys/socket.h> //套接字
#include <arpa/inet.h> //internet相关
#include <string.h>
int main(int argc, const char * argv[]) {
    
    //创建一个结构 用来处理ip的
    struct sockaddr_in server_addr;
    //设定大小
    server_addr.sin_len=sizeof(struct sockaddr_in);
    //设定地址家族
    server_addr.sin_family=AF_INET; //使用internet的地址家族
    //设定端口
    server_addr.sin_port=htons(22222);
    //设定ip
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //设定为0
    bzero(&server_addr.sin_zero, 8);
    //创建一个服务器端套接字 第一个参数是地址族,第二个参数是传送协议(可靠,不可靠)
    int server_socket = socket(AF_INET,SOCK_STREAM , 0); //tcp udp
    if(server_socket==-1)
    {
        printf("套接字创建失败!\n");
        return 1;
    }
    //绑定套接字刀ip和port
    int result = bind(server_socket,(struct sockaddr*) &server_addr, sizeof(server_addr));
    if(result==-1)
    {
        printf("套接字绑定失败!\n");
//        close(server_socket);
        return 1;
    }
    
    //开始监听(等待连接进来)
    if(listen(server_socket, 5)==-1)
    {
        printf("监听失败!\n");
//        close(server_socket);
        return 1;
    }
    //连接进来客户地址
    struct sockaddr_in client_addr;
    socklen_t addr_len;
    //得到连接
    int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);
    if(client_socket==-1)
    {
        printf("这次客户端连接失败");
//        close(server_socket);
        return 1;
    }
    printf("有连接进来了! \n");
    //传送数据
    char recv_msg[1024]; //接受到的数据字符串
    char send_msg[1024]; //要发送的数据字符串
    while(1)
    {
        bzero(recv_msg, 1024);//清空
        bzero(send_msg, 1024);//清空
        printf("请输入你想发给客户端的信息:");
        scanf("%s",send_msg); //从键盘上得到发给客户端的内容
        //把信息发给客户端
        long num = send(client_socket, send_msg, 1024, 0);
        printf("你发送了个%ld字节",num);
        //接受客户端得到信息
        num = recv(client_socket, recv_msg, 1024, 0);
        printf("接受到了个%ld个字节",num);
        recv_msg[num] = '\0';
        printf("客户端发来了: %s",recv_msg);
        
    }
    
    //关闭套接字
    
    
    
    return 0;
}
