#include "calculator.hpp"
// #include <cppkafka/cppkafka.h>

#include "Calculator.hpp"

template <class... Args>
auto Calculator::Add(Args... args) -> decltype((args + ...))
{
    return (args + ...);
}

template <class... Args>
auto Calculator::Subtract(Args... args) -> decltype((args - ...))
{
    return (args - ...);
}

template <class... Args>
auto Calculator::Multiply(Args... args) -> decltype((args * ...))
{
    return (args * ...);
}

template <class... Args>
auto Calculator::Divide(Args... args) -> decltype((args / ...))
{
    return (args / ...);
}
