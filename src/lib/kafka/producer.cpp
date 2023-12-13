#include <cppkafka/cppkafka.h>
#include "cxxopts.hpp"

using namespace cppkafka;

int main(int argc, char *argv[])
{
    cxxopts::Options options("Kafka Calculator", "A simple calculator which uses consumer and producer to calculate");

    options.add_options()("h,help", "Print help")("num1", "Operand 1", cxxopts::value<double>())("num2", "Operand 2", cxxopts::value<double>()->default_value("output.txt"))("count", "Number of iterations", cxxopts::value<int>()->default_value("1"));

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (!result.count("num1") || !result.count("num2"))
    {
        std::cerr << "Error: Both num1 and num2 must be provided." << std::endl;
        return 1;
    }
    double operand1 = result["num1"].as<double>();
    double operand2 = result["num2"].as<double>();

    try
    {
        // Create the config
        Configuration config = {
            {"metadata.broker.list", "127.0.0.1:9092"}};

        // Create the producer
        Producer producer(config);

        // Produce a message!
        std::string message = "hey there!";
        producer.produce(MessageBuilder("my_topic").partition(0).payload(message));
        producer.flush();
    }
    catch (const cxxopts::OptionException &e)
    {
        std::cerr << "Error parsing command-line options: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
}
