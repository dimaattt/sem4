#include <iostream>

using namespace std;

class BadRectangle
{
};

class IntPair
{
    int len;
    int wid;

public:
    virtual int Measure() const = 0; // для вычисления некоторой меры
    IntPair(int x, int y) : len(x), wid(y) {}
    int GetLen() const { return len; }
    int GetWid() const { return wid; }
};

class IntRectangle : public IntPair
{
public:
    IntRectangle(int x, int y) : IntPair(x, y)
    {
        if (GetLen() < 0 || GetWid() < 0)
            throw BadRectangle();
    }
    int Measure() const override
    {
        return GetLen() * GetWid();
    }
};

int main()
{
    try
    {
        IntRectangle a(5, 4), b(7, 4), c(2, 1), d(2, -3);
    }
    catch (BadRectangle b)
    {
        cout << "Bad rectangle\n";
    }
    return 0;
}
