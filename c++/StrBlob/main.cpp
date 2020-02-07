#include <iostream>
#include "StrBlob.h"
using namespace std;

int main()
{
    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2;
        cout << b1.size() << endl;
        cout << b2.size() << endl;
    }
    b1.push_back("lalala");
    cout << b1.size() << endl;
    cout << b1.front() << "\t" << b1.back() << endl;

    return 0;
}

