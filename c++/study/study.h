#pragma once

#include <iostream>
#include <string>
#include "data.h"

enum class Gander { male, female };

class study
{
public:
    study() : study("无", Gander::male, data(2000, 1, 1)) {}
    study(std::string name, Gander gander, data bir) : name(name), gander(gander) 
    { 
        this->bir = new data{bir};
        ++num;
        std::cout << "Now there are " << num << " students" << std::endl;
    }
    study(const study& stu)
    {
        this->name = stu.name;
        this->gander = stu.gander;
        this->bir = new data{*stu.bir};
        ++num;
        std::cout << "copy ctor" << std::endl;
        std::cout << "Now there are " << num << " students" << std::endl;
    }
    study& operator = (const study& stu)
    {
        auto newp = new data{*stu.bir};
        this->name = stu.name;
        this->gander = stu.gander;
        delete this->bir;
        this->bir = newp;
        ++num;
        std::cout << "op ctor" << std::endl;
        std::cout << "Now there are " << num << " students" << std::endl;
        return *this;
    }
    std::string getname() const { return name; }
    void setname(std::string name) { this->name = name; }
    std::string show() const 
    {   
        return (name + ' ' + (gander == Gander::male ? std::string("male") : std::string("female")) + ' ' + bir->show()); 
    }
    ~study() 
    {
        delete bir;
        bir = nullptr;
        --num;
        std::cout << "Now there are " << num << " students" << std::endl;
    }

private:
    std::string name;
    Gander gander;
    data *bir;
    static int num;
};

