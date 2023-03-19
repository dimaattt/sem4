#include <iostream>
#include <vector>
#include <list>

using namespace std;

template <typename T>
void vec_to_list(vector<T> vec, list<T> &list)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] >= 0)
            list.push_back(vec[i]);
    }
}
template <typename T>
void add_to_list(list<T> &lst)
{
    T tmp;
    typename list<T>::iterator p = lst.begin();
    for (p; p != lst.end(); p++)
        tmp += *p;
    tmp /= lst.size();
    lst.push_back(tmp);
}

/*
 * Использовать можно: int, char, double
 * Нельзя использовать: пользовательские типы данных, char*
 * Потому что сравнение/среднее арифметическое реализовывается либо сложнее, либо вообше не релизуемо  
 */
