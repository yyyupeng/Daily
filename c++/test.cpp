#include <iostream>
#include <list>
#include <iterator>
#include <vector>

using namespace std;

//capacity, size, reverse
int main()
{
    vector<int> vec;
    cout << "vec: size: " << vec.size() << " capacity: " << vec.capacity() << endl;
    for(vector<int>::size_type i = 0; i != 24; ++i)
        vec.push_back(i);
    cout << "vec: size: " << vec.size() << " capacity: " << vec.capacity() << endl;
    vec.reserve(50);
    cout << "vec: size: " << vec.size() << " capacity: " << vec.capacity() << endl;
    return 0;
}



/*
//插入迭代器
int main()
{
    list<int> lst = {1,2,3,4};
    list<int> lst2, lst3;
    copy(lst.cbegin(), lst.cend(), front_inserter(lst2));
    copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin()));
    for(auto &r : lst2)
        cout << r << " ";
    cout << endl;
    for(auto it = lst3.cbegin(); it != lst3.cend(); ++it)
        cout << *it << " ";
    cout << endl;
    return 0;
}
*/
