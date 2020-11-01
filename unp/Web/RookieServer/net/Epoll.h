#pragma once

#include "Channel.h"
#include "../base/Packet.h"
#include "Http_conn.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include "../base/MemoryPool.h"

#define MAXFDS 10000
#define EVENTS 4096
#define EPOLLWAIT_TIME -1

class Channel;
typedef std::shared_ptr<Channel> SP_Channel; 

class Epoll
{
private:
	int epollfd;
	std::vector<SE> events;
	std::unordered_map<int, SP_Channel> Channelmap;

public:
	Epoll();
	~Epoll();
	void add(const SP_Channel& request);
	void update(const SP_Channel& request);
	void del(const SP_Channel& request);
	void poll(std::vector<SP_Channel>& request);
};

