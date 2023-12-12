#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

namespace Calculator
{
    class Calculator
    {
    public:
        template <class... Args>
        auto Add(Args... args) noexcept -> boost::multiprecision::cpp_dec_float_50
        {
            return (... + args);
        }

        template <class... Args>
        auto Subtract(Args... args) noexcept -> boost::multiprecision::cpp_dec_float_50
        {
            return (... - args);
        }

        template <class... Args>
        auto Multiply(Args... args) noexcept -> boost::multiprecision::cpp_dec_float_50
        {
            return (... * args);
        }

        template <class... Args>
        auto Divide(Args... args) noexcept -> boost::multiprecision::cpp_dec_float_50
        {
            return (... / args);
        }
    };
}
#endif