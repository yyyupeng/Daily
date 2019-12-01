#pragma once

#include<iostream>
#include<string>

class data
{
public:
    data(int y = 2000, int m = 1, int d = 1) : year(y), month(m), day(d) 
    {
        std::cout << "data(ctor): " << show() << std::endl;
    }
    data(const data& dt)
    {
        year = dt.year;
        month = dt.month;
        day = dt.day;
        std::cout << "data(copy ctor): " << show() << std::endl;
    }
    int getday() const { return day; }
    void setday(int d) { day = d; }
    std::string show() const { return (std::to_string(year) + '-' + std::to_string(month) + '-' + std::to_string(day)); }
    //~data() {}
private:
    int year;
    int month;
    int day;
};

