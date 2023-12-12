#include <iostream>
#include <iomanip>

#include "calculator.hpp"
int main()
{
    Calculator::Calculator calculator;
    calculator.num_threads = 4;
    std::cout << std::fixed << calculator.Factorial(300);
}