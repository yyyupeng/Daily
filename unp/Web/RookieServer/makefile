objects=main.o Server.o Http_conn.o ContentType.o EventLoop.o Epoll.o Channel.o TimerManager.o Logging.o AsyncLogging.o LogStream.o LogFile.o FileUtil.o EventLoopThreadpool.o ThreadEventLoop.o Thread.o Packet.o Conf.o MemoryPool.o LFUCache.o 

origins=main.cc net/Server.cc net/Http_conn.cc net/ContentType.cc base/Packet.cc net/EventLoop.cc net/Epoll.cc net/Channel.cc net/TimerManager.cc log/Logging.cc log/AsyncLogging.cc log/LogStream.cc log/LogFile.cc log/FileUtil.cc net/EventLoopThreadpool.cc base/ThreadEventLoop.cc base/Thread.cc base/Conf.cc base/MemoryPool.cc base/LFUCache.cc

g11=g++ -std=c++11
 
WebServer:$(objects)
	$(g11) -o WebServer $(objects) -lpthread 

$(objects):$(origins)
	$(g11) -g -c $(origins)

.PHONY:clean
clean:
	rm $(objects)

.PHONY:cleanout
cleanout:
	rm WebServer 

