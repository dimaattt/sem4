#include <iostream>

using namespace std;

class BadRectangle
{
};
class BadAdd
{
    int x1, y1, x2, y2;

public:
    BadAdd(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
    int GetX1() const { return x1; }
    int GetY1() const { return y1; }
    int GetX2() const { return x2; }
    int GetY2() const { return y2; }
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
    IntRectangle() : IntPair(0, 0) {}
    IntRectangle(int x, int y) : IntPair(x, y)
    {
        if (GetLen() < 0 || GetWid() < 0)
            throw BadRectangle();
    }
    int Measure() const override
    {
        return GetLen() * GetWid();
    }
    IntRectangle operator+(const IntRectangle box)
    {
        int new_len = GetLen(), new_wid = GetWid();
        bool flag = false;
        if (GetWid() == box.GetWid())
        {
            new_len = GetLen() + box.GetLen();
            flag = true;
        }
        if (GetLen() == box.GetLen())
        {
            new_wid = GetWid() + box.GetWid();
            flag = true;
        }
        if (flag)
            return IntRectangle(new_len, new_wid);
        throw BadAdd(GetLen(), GetWid(), box.GetLen(), box.GetWid());
    }
};

int main()
{
    try
    {
        IntRectangle a(5, 4), b(7, 4), c(2, 1), d(2, 3);
        IntRectangle p, q;
        p = a + b;
        q = c + d;
        cout << (p + q).Measure() << endl;
        cout << (p + d).Measure() << endl;
    }
    catch (const BadAdd &bad)
    {
        cout << "Bad add: (" << bad.GetX1() << 'x' << bad.GetY1() << ") + (" << bad.GetX2() << 'x' << bad.GetY2() << ")\n";
    }
    catch (BadRectangle b)
    {
        cout << "Bad rectangle\n";
    }
    return 0;
}
