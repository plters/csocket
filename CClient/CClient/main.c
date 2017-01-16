//
//  main.c
//  CClient
//
//  Created by apple on 2017/1/16.
//  Copyright © 2017年 plters. All rights reserved.
//

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
int main(int argc, const char * argv[]) {
    
    //创建一个套接字
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
    
    int server_socket = socket(AF_INET,SOCK_STREAM , 0); //tcp udp
    if(server_socket == -1)
    {
        printf("连接套接字失败\n");
        return 1;
    }
    //连接到服务器端
    int result = connect(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(result==0)
    {
      //数据的收发
        printf("连接服务器成功! \n");
    }
    else
    {
        printf("连接服务器失败! \n");
    }
    //传送数据
    char recv_msg[1024]; //接受到的数据字符串
    char send_msg[1024]; //要发送的数据字符串
    while(1)
    {
        bzero(recv_msg, 1024);//清空
        bzero(send_msg, 1024);//清空
        //接受服务端的信息
        long num = recv(server_socket, recv_msg, 1024, 0);
        recv_msg[num] = '\0';
        printf("你发送了个%ld字节\n",num);
        printf("服务端发来了: %s\n",recv_msg);
        printf("请输入你想发给服务器端的信息:");
        scanf("%s",send_msg); //从键盘上得到发给服务器的内容
        //把信息发给服务器
        num = send(server_socket, send_msg, 1024, 0);
        
       
        printf("接受到了个%ld个字节",num);
        
        
        
    }

    
    
    
    return 0;
}
