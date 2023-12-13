#include <cppkafka/cppkafka.h>
#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "config_json.hpp"

using namespace cppkafka;
using json = nlohmann::json;

int main(int argc, char *argv[])
{
    double operand1 = 0;
    double operand2 = 0;
    double _operator = 0;

    std::cout << "Enter Operand1: ";
    std::cin >> operand1;

    std::cout << "Enter Operator (0 for add, 1 for subtract, 2 for multiply, 3 for divide, 4 for factorial): ";
    std::cin >> _operator;

    if (_operator != 4)
    {
        std::cout << "Enter Operand2: ";
        std::cin >> _operator;
    }
    try
    {
        auto configJson = ConfigKF::GetConfigJson("config.json");
        Configuration config = {
            {"metadata.broker.list", configJson["kafka"]["broker"].get<std::string>()}};

        // Create the producer
        Producer producer(config);

        // Produce a message for operand1
        std::string message1 = "Operand 1: " + std::to_string(operand1);
        producer.produce(MessageBuilder(configJson["kafka"]["topic"].get<std::string>()).partition(0).payload(message1));

        // Produce a message for the operator
        std::string message2 = "Operator: " + std::to_string(_operator);
        producer.produce(MessageBuilder(configJson["kafka"]["topic"].get<std::string>()).partition(0).payload(message2));

        if (_operator != 4)
        {
            // Produce a message for operand2
            std::string message3 = "Operand 2: " + std::to_string(operand2);
            producer.produce(MessageBuilder(configJson["kafka"]["topic"].get<std::string>()).partition(0).payload(message3));
        }

        producer.flush();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
}
