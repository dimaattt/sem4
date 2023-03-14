#include <iostream>

using namespace std;

class Assign
{
    int a_y;

public:
    Assign() : a_y(0) {}
    int Get() const { return a_y; }

    class Proxy
    {
        int &a_x;
        Assign &assing;

    public:
        Proxy(Assign &assing, int &x) : assing(assing), a_x(x) {}

        void operator()(int y)
        {
            assing.a_y = y;
            a_x = y;
        }
        operator int() const
        {
            return assing.a_y;
        }
    };

    Proxy operator[](int &x)
    {
        return Proxy(*this, x);
    }
};

int main()
{
    Assign a;
    int x, y = 5;
    a[x](y);
    cout << a.Get() << endl; // напечатается 5
    cout << x << endl;       // напечатается 5
    return 0;
}
