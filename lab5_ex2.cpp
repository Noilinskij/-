#include "lab5_ex2.h"

encoder::encoder(std::vector<std::byte> key) {
    int size = 256;
    key_ = key;
    key_stream_ = std::vector<std::byte>(size);
    for (int i = 0; i < size; i++) {
        key_stream_[i] = (std::byte) i;
    }
    int i = 0;
    for (int j = 0; j < size; j++) {
        i = (i + (int)key_stream_[j] + (int) key_[j % key_.size()]) % size;
        std::swap(key_stream_[i], key_stream_[j]);
    }
}

statuses encoder::encode(std::string in, std::string out, bool flag) {
    std::ifstream input(in);
    if (!input) {
        return OPEN_PROBLEM;
    }
    std::ofstream output(out);
    if (!output) {
        output.close();
        return OPEN_PROBLEM;
    }
    if (in == out) {
        return INCORRECT_ARGUMENTS;
    }
    char current;
    int count = 0;
    while(input.get(current)) {
        output.put((char) ((std::byte) current ^ key_stream_[count % key_stream_.size()]));

    }
    return OK;
}

void encoder::setKey(std::vector<std::byte> key) {
    int size = 256;
    key_ = key;
    for (int i = 0; i < size; i++) {
        key_stream_[i] = (std::byte) i;
    }
    int i = 0;
    for (int j = 0; j < size; j++) {
        i = (i + (int)key_stream_[j] + (int) key_[j % key_.size()]) % size;
        std::swap(key_stream_[i], key_stream_[j]);
    }
}


int main() {
    encoder a({(std::byte) 'a', (std::byte) 'b', (std::byte) 'c'});
    statuses status  = a.encode("pic.png", "in.png", true);
    statuses status_b  = a.encode("in.png", "out.png", true);
    if (status == OPEN_PROBLEM) {
        std::cout << "open problem";
        return OPEN_PROBLEM;
    }
    else if (status == INCORRECT_ARGUMENTS) {
        std::cout << "incorrect arguments";
        return INCORRECT_ARGUMENTS;
    }
    return OK;

}