#include <iostream>
#include "calculator.hpp"

int main()
{
    Calculator myCalculator;
    int res = myCalculator.Add(3, 3, 4);
    std::cout << res << std::endl;
    std::cout << "hello" << std::endl;
}