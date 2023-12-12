#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include <vector>
#include <thread>
#include <mutex>

namespace Calculator
{
    class Calculator
    {
    private:
        std::mutex mut;
        std::vector<std::thread> threads;
        boost::multiprecision::cpp_int totalResult = 1;

        static boost::multiprecision::cpp_int CalculateFactorial(int start, int end)
        {
            boost::multiprecision::cpp_int result = 1;
            for (int i = start; i <= end; ++i)
            {
                result *= i;
            }
            return result;
        }

        void FactorialWorker(int id, int n)
        {
            int chunkSize = n / num_threads;
            int start = id * chunkSize + 1;
            int end = (id == num_threads - 1) ? n : (id + 1) * chunkSize;

            boost::multiprecision::cpp_int partialResult = CalculateFactorial(start, end);

            // Synchronize access to shared result variable
            std::lock_guard<std::mutex> lock(mut);

            // Accumulate partialResult to the total result
            totalResult *= partialResult;
        }

    public:
        int num_threads = 2;

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

        auto Factorial(int n) noexcept -> boost::multiprecision::cpp_int
        {
            // Create worker threads
            for (int i = 0; i < this->num_threads; ++i)
            {
                threads.emplace_back(&Calculator::FactorialWorker, this, i, n);
            }

            // Wait for all threads to finish
            for (auto &thread : threads)
            {
                thread.join();
            }

            // Return the total result
            return totalResult;
        }
    };
} // namespace Calculator

#endif
