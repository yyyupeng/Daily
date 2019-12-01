#include <iostream>
#include "data.h"
#include "study.h"

int study::num = 0;
int main()
{
    study X;
    study x{X};
    study z = X;
    study *y = new study{"qsj", Gander::male, data(2000, 6, 6)};
    x.setname("zzk");
    std::cout << "X " << X.show() << std::endl;
    std::cout << "x " << x.show() << std::endl;
    std::cout << "z " << z.show() << std::endl;
    std::cout << y->show() << std::endl;
    delete y;

    return 0;
}

