#include "net/Server.h"
#include <signal.h>
#include "base/Conf.h"

int main(int argc, char *argv[])
{
	init_memorypool();
	const char *conf = "base/WebServer.conf";
	getconf().init(conf);
	getCache().init();
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, EventLoop::setquit);
	signal(SIGQUIT, EventLoop::setquit);
	Server server(getconf().getport().c_str(), getconf().getthreads());
	server.start();
}
