#include "EventLoopThreadpool.h"

ThreadpoolEventLoop::ThreadpoolEventLoop(int Threadnum)
:	threadnum(Threadnum),
	index(0)
{
	threads.reserve(threadnum);
	for(int i = 0; i < threadnum; ++i)
    {
		SP_ThreadEventLoop t(newElement<ThreadEventLoop>(), deleteElement<ThreadEventLoop>);
		threads.emplace_back(t);
	}	
}

ThreadpoolEventLoop::~ThreadpoolEventLoop()
{
	threads.clear();
}

void ThreadpoolEventLoop::start()
{
	for(auto& temp : threads)
		temp->start();
}

SP_EventLoop ThreadpoolEventLoop::getNextloop()
{
	index = (index + 1) % threadnum;
	return threads[index]->getLoop();
}
