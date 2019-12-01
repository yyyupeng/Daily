#pragma once

#include <iostream>
#include <string>

class Message
{
public:
    Message() {}
    ~Message() {}

private:
    std::string contents;               //实际消息
    std::set<Folder *> floders;         //包含本Message的Folder
    //工具函数
    void add_to_Folders(const Message&);//将本Message添加到指向参数的Folder中
    void remove_from_Folder();          //从folders中的每个Folder中删除本Message

    friend class Folder;
};

