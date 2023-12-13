#include <cppkafka/cppkafka.h>
#include <iostream>
int main()
{
    cppkafka::Consumer consumer({{"metadata.broker.list", "127.0.0.1:9092"},
                                 {"group.id", "test_group"}});

    consumer.subscribe({"my_topic"});

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
