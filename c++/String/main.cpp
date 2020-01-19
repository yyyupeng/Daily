#include <iostream>
#include <cstdlib>
#include "my_string.h"

using namespace std;

int main()
{
    my_string s1("hello"), s2, s(10, 'c');
    cin >> s2;
    cout << "s2: " << s2 << endl;
    cout << "s1: " << s1 << endl;
    cout << "s: " << s << endl;
    my_string s3 = s1 + s2;
    cout << "s3: " << s3 << endl;
    cout << "s3[5]: " << s3[5] << endl;
    
    if(s1 > s2)
        cout << "s1 > s2" << endl;
    else
        cout << "s1 < s2" << endl;

    s1.swap(s2);
    cout << "s2: " << s2 << endl;
    cout << "s1: " << s1 << endl;

    s3.resize(10, 'o');
    cout << "s3: " << s3 << endl;

    char *a = s3.substr(3, 3);
    cout << a << endl;

    my_string *s4 = new my_string(s3);
    my_string::my_iterator it = s4;
    cout << "s4: " << *s4 << endl;

    for(it = s4->begin(); it < s4->end(); ++it)
        cout << *it ;
    cout << endl;
    delete s4;

    return 0;
}

