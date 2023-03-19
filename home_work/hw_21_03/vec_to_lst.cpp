#include <iostream>
#include <vector>
#include <list>

using namespace std;

void vec_to_list(vector<int> vec, list<int> &list)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] >= 0)
            list.push_back(vec[i]);
    }
}

// Пример выполнения программы 
int main()
{
    vector<int> arr;
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(-9);
    arr.push_back(0);
    list<int> lst;
    vec_to_list(arr, lst);
    list<int>::iterator p = lst.begin();
    while (p != lst.end())
    {
        cout << *p << ' ';
        p++;
    }
    cout << endl;
    return 0;
}
