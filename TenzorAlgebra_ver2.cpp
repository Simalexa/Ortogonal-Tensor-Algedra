#include <iostream>
#include "Equation.h"

int main()
{
    try
    {
        Tenzor *T1 = new Tenzor;
        Tenzor* T2 = new Tenzor;
        T1->createTenzor("1ii +2jj +3kk");
        T2->createTenzor("1ii +2ji +3ik");
       equation e("(TenA xx TenB + TenA) ** TenA");
        e.createTenzorMap("TenA", T1);
        e.createTenzorMap("TenB", T2);
        e.solveEquation();
    }
    catch (const char* msg)
    {
        std::cout << msg;
        return -1;
    }
    return 0;
}
