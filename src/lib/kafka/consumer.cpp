#include <cppkafka/cppkafka.h>
#include <iostream>
#include <fstream>
#include "config_json.hpp"
#include <vector>
#include "calculator.hpp"
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

int main()
{

    auto configJson = ConfigKF::GetConfigJson("config.json");

    cppkafka::Consumer consumer({{"metadata.broker.list", configJson["kafka"]["broker"].get<std::string>()},
                                 {"group.id", configJson["kafka"]["group"].get<std::string>()}});

    consumer.subscribe({configJson["kafka"]["topic"].get<std::string>()});
    Calculator::Calculator mycalc;
    while (true)
    {
        // Open the file in append mode
        std::ofstream outputFile("output.txt", std::ios::app);

        cppkafka::Message msg = consumer.poll();
        if (msg)
        {
            if (msg.get_error())
            {
                std::cout << "Error: " << msg.get_error() << std::endl;
            }
            else
            {
                std::cout << msg.get_payload() << std::endl;
                try
                {
                    double res = 0.0;
                    // boost::multiprecision::cpp_int res_fact = 0;
                    std::string payload = msg.get_payload();

                    // Parse the JSON
                    json messageJson = json::parse(payload);

                    double op1 = messageJson["operand1"].get<double>();
                    double op2 = messageJson["operand2"].get<double>();
                    int _operator = messageJson["operator"].get<int>();
                    switch (_operator)
                    {
                    case 0:
                        res = (double)mycalc.Add(op1, op2);
                        break;
                    case 1:
                        res = (double)mycalc.Subtract(op1, op2);
                        break;
                    case 2:
                        res = (double)mycalc.Multiply(op1, op2);
                        break;
                    case 3:
                        res = (double)mycalc.Divide(op1, op2);
                        break;
                    case 4:
                        res = (int)mycalc.Factorial((int)op1);
                        break;

                    default:
                        break;
                    }
                    std::cout << "The result is: " << res << std::endl;

                    if (outputFile.is_open())
                    {
                        // Write data to the file
                        outputFile << msg.get_payload() << "\n";
                        outputFile << "The result is: " << res << "\n";
                        // Close the file
                        outputFile.close();
                        std::cout << "written" << std::endl;
                    }
                    else
                    {
                        std::cerr << "Unable to open the file." << std::endl;
                        return 1;
                    }
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Exception caught: " << e.what() << std::endl;
                    return 1;
                }
            }
        }
    }
    // Close the file
    outputFile.close();

    std::cout << "Data appended to the file successfully." << std::endl;

    return 0;
}
