#include <iostream>
#include <list>

using namespace std;

void add_to_list(list<double> &lst)
{
    double tmp;
    list<double>::iterator p = lst.begin();
    for (p; p != lst.end(); p++)
        tmp += *p; // можно было бы tmp += *p / lst.size() чтобы избежать переполнения 
    tmp /= lst.size();
    lst.push_back(tmp);
}

void print(list<double> &lst)
{
    list<double>::iterator p = lst.begin();
    for (p; p != lst.end(); p++)
        cout << *p << ' ';
    cout << '\n';
}

int main()
{
    list<double> lst;
    lst.push_back(3);
    lst.push_back(3);
    lst.push_back(2);
    add_to_list(lst);
    print(lst);
    return 0;
}
