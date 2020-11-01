#pragma once

#include "../base/ThreadEventLoop.h"
#include "../base/MemoryPool.h"

class ThreadpoolEventLoop
{
private:
	vector<SP_ThreadEventLoop> threads;	
	int threadnum;	
	int index;

public:
	ThreadpoolEventLoop(int Threadnum);
	~ThreadpoolEventLoop();
	void start();
	SP_EventLoop getNextloop();
};

typedef std::unique_ptr<ThreadpoolEventLoop, decltype(deleteElement<ThreadpoolEventLoop>)*> UP_ThreadpoolEventLoop;
