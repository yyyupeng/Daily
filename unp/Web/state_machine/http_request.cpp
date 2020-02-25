#include "http_request.h"

int main()
{
    struct sockaddr_in address;
    bzero( &address,sizeof(address));

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    
    int ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);
    
    ret = listen(listenfd,5);
    assert(ret != -1);
    std::cout << "socket successful" << std::endl;
    
    struct sockaddr_in client_address;
    socklen_t client_addrlength = sizeof(client_address);
    int fd = accept(listenfd, (struct sockaddr *)&client_address, &client_addrlength );

    if(fd < 0)
    {
        std::cout << "errno:" << errno << std::endl;
    }
    else
    {
        std::cout << "accept!" << std::endl;
        char buffer[BUFFER_SIZE];//读缓冲区
        memset(buffer,'\0',BUFFER_SIZE);
        int data_read = 0;
        int read_index = 0;         //已经读取到的数据
        int checked_index = 0;      //当前已经分析多少数据
        int start_line = 0;         //记录行在buffer中的起始数据
        
        //初始化主状态机的状态 
        CHECK_STATE checkstate = CHECK_STATE_REQUESTLINE;
        while(1)
        {
           data_read = recv(fd, buffer + read_index, BUFFER_SIZE - read_index, 0);
           std::cout << data_read << std::endl;
           if(data_read == -1)
           {
               std::cout << "read failed" << std::endl;
               break;
           }
           else if(data_read == 0)
           {
               std::cout << "Remote client has closedd the connection " << std::endl;
                break;
           }
           read_index += data_read;

           //分析目前已获得的所有客户数据 
           HTTP_CODE result = parse_content(buffer,checked_index,checkstate,read_index,start_line);

           if(result == NO_REQUEST)
           {
               continue;
           }
           else if(result == GET_REQUEST)
           {
               send(fd,szret[0],strlen(szret[0]),0);
               break;
           }
           else
           {
               send(fd,szret[1],strlen(szret[1]),0);
               break;
           }
        }
        close(fd);
    }
    close(listenfd);

    return 0;
}
