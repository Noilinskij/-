#include <iostream>
#include <vector>
#include <string>
#include <fstream>

typedef enum statuses {
    OK,
    OPEN_PROBLEM,
    INCORRECT_ARGUMENTS
} statuses;


class encoder {
public:
    encoder(std::vector<std::byte>);
    statuses encode(std::string, std::string, bool flag);
    void setKey(std::vector<std::byte>);
private:
    std::vector<std::byte> key_;
    std::vector<std::byte> key_stream_;
};