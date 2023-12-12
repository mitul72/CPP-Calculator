#include <iostream>
#include "calculator.hpp"

int main()
{
    Calculator::Calculator myCalculator;
    auto res = myCalculator.Add(3, 3, 4);
    auto res2 = myCalculator.Subtract(3, 3, 4);
    auto res3 = myCalculator.Divide(3.2, 3.3, 4.1).convert_to<double>();
    if (res3 == 0.236511)
    {
        std::cout << "hello" << std::endl;
    }
    std::cout << res << std::endl;
    std::cout << res2 << std::endl;
    std::cout << res3 << std::endl;
}