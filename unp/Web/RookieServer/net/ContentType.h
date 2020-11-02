#pragma once

#include <map>
#include <pthread.h>

class ContentType
{
private:
	static pthread_once_t once_control;
	static std::map<std::string, std::string> mime;
	static void init();	
	ContentType() = default;
public:
	static std::string getCont(const std::string&);
};
