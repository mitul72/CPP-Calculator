#include <cppkafka/cppkafka.h>
#include <iostream>
#include "config_json.hpp"
int main()
{
    auto configJson = ConfigKF::GetConfigJson("config.json");
    cppkafka::Consumer consumer({{"metadata.broker.list", configJson["kafka"]["broker"].get<std::string>()},
                                 {"group.id", configJson["kafka"]["group"].get<std::string>()}});

    consumer.subscribe({configJson["kafka"]["topic"].get<std::string>()});

    while (true)
    {
        cppkafka::Message msg = consumer.poll();
        if (msg)
        {
            if (msg.get_error())
            {
                std::cout << "Error: " << msg.get_error() << std::endl;
            }
            else
            {
                std::cout << "Received message: " << msg.get_payload() << std::endl;
            }
        }
    }

    return 0;
}
