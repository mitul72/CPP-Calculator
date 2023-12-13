# C++ Calculator

## Description

This repository contains a C++ application that implements a Calculator class capable of performing basic arithmetic operations (addition, subtraction, multiplication, and division) and factorial calculations on integers. The application is designed to be multi-threaded for efficient asynchronous factorial calculations. Additionally, Kafka streaming functionality is integrated to consume messages from a Kafka topic, perform arithmetic operations using the Calculator class, display results, and write them to an output file.

## Components

### 1. Unit Tests

Unit tests are implemented using google test. They ensure the correctness of the Calculator class and the overall application. Each test case covers specific scenarios to validate the functionality of the implemented features.

#### Running Unit Tests

```bash
# Build and run unit tests
cmake -B build
cd build
make
./tests
```

### 2. Threading

The application leverages multi-threading to perform time-consuming factorial calculations asynchronously. Multiple worker threads are created to calculate the factorial of large numbers. Synchronization mechanisms are implemented to handle potential concurrency issues.

### 3. Streaming with Kafka

Kafka streaming functionality is integrated into the application. It consumes messages from a Kafka topic, processes them using the Calculator class, displays the results, and writes them to an output file. The Kafka connection settings are configurable to ensure the application gracefully handles Kafka connection and message consumption.

## Building and Running the Application

### Prerequisites

List any prerequisites or dependencies that need to be installed.

```bash
# Example installation commands
sudo apt-get install libboost-all-dev
```

### Building

```bash
# Build the C++ application
cmake -B build
cd build
make
```

### Running

```bash
# Run unit tests
./tests

# Produce messages to Kafka
./producer-kafka

# Consume and calculate with Kafka
./consumer-kafka
```

## Author

mitul72
