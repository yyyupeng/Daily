#ifndef _TASK_H
#define _TASK_H

#include "include.h"

const char *path = "/home/liyupeng/Daily/unp/Web/webserver";
const int BUFFER_SIZE = 4096;
using namespace std;

class task
{
public:
    task() {}
    ~task() {}
    task(int fd) : connfd(fd) {}
    
    void response_err(char *mes, int statu);
    void response_file(int size, int statu);
    void response_get(char *text);
    void response_post(char *text, char *ar);
    void doit();

private:
    int connfd;
};

/* 错误响应函数 */
void task::response_err(char *mes, int statu)
{
    char buf[512];
    sprintf(buf, "HTTP/1.1 %d OK\r\nConnection: Close\r\n""content-length:%zu\r\n\r\n", statu, strlen(mes));
    sprintf(buf, "%s%s", buf, mes);
    send(connfd, buf, strlen(buf), 0);
}

/* 请求静态文件响应函数 */
void task::response_file(int size, int statu)
{
    char buf[512];
    sprintf(buf, "HTTP/1.1 %d OK\r\nConnection: Close\r\n""content-length%d\r\n\r\n", statu, size);
    send(connfd, buf, strlen(buf), 0);
}

/* get */
void task::response_get(char *text)
{
    char temp[100];
    strncpy(temp, path, strlen(path));
    bool flag = false;
    char ch[50];    //请求文件名
    int i = 0;

    //查找是否有？号
    while(text[i] != '?' && text[i] != '\0')
        ++i;
    if(text[i] == '?')  //找到？号，这是动态请求
    {
        int j = i++;
        int k = 0;
        //分离参数和文件名
        while(text[i] != '\0')
            ch[k++] = text[i++];
        ch[k] = '\0';
        text[j] = '\0';
        flag = true;
    }

    if(strcmp(text, "/") == 0)
        strcat(temp, "/index.html");
    else
        strcat(temp, text);
    cout << "path:" << temp << endl;

    /* stat函数：取得指定文件的文件属性，文件属性存储在结构体stat里 */
    struct stat tempstat;
    int ret = stat(temp, &tempstat);
    if(ret < 0 || S_ISDIR(tempstat.st_mode))    //temp不存在
    {
        char message[BUFFER_SIZE];
		sprintf(message, "<html><title>RookieWeb Error</title>");
		sprintf(message, "%s<body>\r\n", message);
		sprintf(message, "%s 404\r\n", message);
		sprintf(message, "%s <p>GET: Can't find the file", message);
		sprintf(message, "%s<hr><h3>The Rookie Web Server<h3></body>", message);
		response_err(message, 404);
		return;
    }
    
    if(flag)    //动态请求
    {
        //创建进程，多线程中，创建子进程，只有当前线程被复制
        if(fork() == 0)
        {
            //将标准输出重定向到socked
            dup2(connfd, STDOUT_FILENO);
            execl(temp, ch, NULL);    //执行子程序
        }
        wait(NULL);
    }
    else        //静态请求
    {
        int fd = open(temp, O_RDONLY);
        response_file(tempstat.st_size, 200);
        sendfile(connfd, fd, NULL, tempstat.st_size);
    }
}

/* post */
void task::response_post(char *text, char *ar)
{
    char temp[100];
    strncpy(temp, path, strlen(path));
    strncat(temp, text, strlen(text));
    cout << "path:" << temp << endl;
    
    /* stat函数：取得指定文件的文件属性，文件属性存储在结构体stat里 */
    struct stat tempstat;
    int ret = stat(temp, &tempstat);
    if(ret < 0 || S_ISDIR(tempstat.st_mode))    //temp不存在
    {
        char message[BUFFER_SIZE];
		sprintf(message, "<html><title>RookieWeb Error</title>");
		sprintf(message, "%s<body>\r\n", message);
		sprintf(message, "%s 404\r\n", message);
		sprintf(message, "%s <p>GET: Can't find the file", message);
		sprintf(message, "%s<hr><h3>The Rookie Web Server<h3></body>", message);
		response_err(message, 404);
		return;
    }
    
    char argv[20];
	int a, b;
	ret = sscanf(ar, "a=%d&b=%d", &a, &b);  //判断参数是否正确
	if(ret < 0 || ret != 2)
	{
		char message[BUFFER_SIZE];
		sprintf(message, "<html><title>RookieWeb Error</title>");
		sprintf(message, "%s<body>\r\n", message);
		sprintf(message, "%s 404\r\n", message);
		sprintf(message, "%s <p>GET: Parameter error", message);
		sprintf(message, "%s<hr><h3>The RookieWeb Web Server<h3></body>", message);
		response_err(message, 404);
		return;
	}
    int len = strlen(text);
    char ch[20];
    while(text[--len] != '/' && len >= 0);
    strcpy(ch, text + len + 1);
	sprintf(argv, "%d&%d", a, b);
    cout << ch << " " << argv << endl;
	if(fork() == 0) 
	{
		dup2(connfd, STDOUT_FILENO);  
		execl(temp, ch, argv, NULL); 
	}
	wait(NULL);
}

void task::doit()
{
    char buf[BUFFER_SIZE];
    int size;
    //读取解析请求
    while(1)
    {
        size = recv(connfd, buf, BUFFER_SIZE - 1, 0);   //接受请求
        cout << "size: " << size << "\n" << buf;
        if(size > 0)//如果有数据的话
		{
			char method[5];     //请求方法
			char filename[50];  //文件
			int i = 0, j = 0;
			while(buf[j] != ' ' && buf[j] != '\0')      //获取请求方法
			{
				method[i++] = buf[j++];
			}
			++j;
			method[i] = '\0';
			i = 0;
			while(buf[j] != ' ' && buf[j] != '\0')      //请求文件
			{
				filename[i++] = buf[j++];
			}
			filename[i] = '\0';
            cout << "method:" << method << ' ' << "filename:" << filename << endl;

			if(strcasecmp(method, "GET") == 0)          //如果是get方法
			{
				response_get(filename);
			}
			else if(strcasecmp(method,"POST") == 0)     //如果是post方法
			{
				char argv[100];
				memset(argv, 0, sizeof(argv));
				int k = 0;
				char *ch = NULL;
				++j;
				while((ch = strstr(argv,"Content-Length")) == NULL)     //查找请求头部中的Content-Length行
				{
					k = 0;
					memset(argv, 0, sizeof(argv));
					while(buf[j] != '\r' && buf[j] != '\0')             //不是换行不是结束
					{
						argv[k++] = buf[j++];
					}
					j++;
				}
				int len = 0;
				char *ss = strchr(argv, ':');          //post请求数据长度
				ss++;
				sscanf(ss, "%d", &len);
				j = strlen(buf) - len;               //从尾部获取请求数据
				k = 0;
				memset(argv, 0, sizeof(argv));
				while(buf[j] != '\r' && buf[j] != '\0')
				{
					argv[k++] = buf[j++];
				}
				argv[k] = '\0';
				response_post(filename, argv);          //post
			}
			else    //其他方法
			{
				char message[BUFFER_SIZE];
				sprintf(message,"<html><title>RookieWeb Error</title>");
				sprintf(message,"%s<body>\r\n", message);
				sprintf(message,"%s 501\r\n", message);
				sprintf(message,"%s <p>%s: Httpd does not implement this method",message,method);
				sprintf(message,"%s<hr><h3>The RookieWeb Web Server<h3></body>", message);
				response_err(message, 501);
			}
		}
 		else if(size < 0)   //读取失败，重新读取
		{
			continue;
		}

        close(connfd);
        break;
    }
}

#endif
