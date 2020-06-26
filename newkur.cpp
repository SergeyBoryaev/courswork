#include <iostream>
#include "BigInt.h"

int main()
{
    BigInt b;
    BigInt a;
    std::cout << "A: ";
    std::cin >> a;
    std::cout << "B: ";
    std::cin >> b;
    std::cout << "Number A: " << a << std::endl;
    std::cout << "Number B: " << b << std::endl;
    std::cout << "A+B: " << a + b << std::endl;
    std::cout << "A-B: " << a - b << std::endl;
    std::cout << "A*B: " << a * b << std::endl;
    try
    {
        std::cout << "A / B: " << a / b << std::endl;
    }
    catch (int error)
    {
        if (error == 1)
            std::cout << "0 devision error" << std::endl;
    }
    std::cout << "A==B? ";
    if (a == b)
        std::cout << "True" << std::endl;
    else
        std::cout << "False" << std::endl;
    std::cout << "A>B? ";
    if (a > b)
        std::cout << "True" << std::endl;
    else
        std::cout << "False" << std::endl;
}