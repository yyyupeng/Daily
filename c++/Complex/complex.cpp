#include <iostream>
#include "complex.h"

using namespace std;

int main()
{
    complex c1;
    complex c2(2,3);
    cout << c1 << endl;
    cout << c2 << endl;
    
    c1 = c2 + 1 ;
    cout << c1 << endl;
    
    c1 += c2;
    cout << c1 << endl;
    c1 -= c2;
    cout << c1 << endl;
    c1 *= c2;
    cout << c1 << endl;
    c1 /= c2;
    cout << c1 << endl;

    cout << (c1 == c2) << endl;
    cout << (c1 != c2) << endl;
    
    cout << +c2 << endl;
    cout << -c2 << endl;

    cout << conj(c2) << endl;
    return 0;
}

