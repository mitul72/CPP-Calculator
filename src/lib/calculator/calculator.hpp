#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

class Calculator
{
public:
    template <class... Args>
    auto Add(Args... args) -> decltype((args + ...));

    template <class... Args>
    auto Subtract(Args... args) -> decltype((args - ...));

    template <class... Args>
    auto Multiply(Args... args) -> decltype((args * ...));

    template <class... Args>
    auto Divide(Args... args) -> decltype((args / ...));
};

#endif