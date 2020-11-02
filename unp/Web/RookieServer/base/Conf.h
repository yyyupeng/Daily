#pragma once

#include <string>
#include <fstream>
#include <map>
#include <iostream>
#include <cstring>

using namespace std;

class Conf
{
private:
	char conf[100];
	int threads;
	string port;
	int listenq;
	int keepalive;
	string storage;
	string logfile;
	int capacity;	

public:
	void init(const char *path);
	int getthreads();
	string getport();
	int getlistenq();
	string getstorage();
	string getlogfile();
	int getkeepalive();
	int getcapacity();
	Conf();

private:	
	int getpos(string& buf, int start, int end, bool flag);
	void parse(map<string,string>& m,string& buf);
	void pretreatment(string& buf);

};

Conf& getconf();
