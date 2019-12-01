#include <iostream>
#include <string>
#include "my_string.h"

using namespace std;

int main()
{
    string s;
    cout << s << endl;
    my_string s1;
    my_string s2("hello");
    s1 = s2;
    cout << s1 << endl;
    cout << s2 << endl;
    my_string s3(s2);
    my_string s4 = s2;
    cout << s3 << " " << s4 << endl;
    return 0;
}

