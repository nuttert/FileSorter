#pragma once
#include <vector>
#include <string>

class Generator
{
public:
    Generator(const bool isDigits = false);
    void Generate(const size_t lines, const size_t length, const std::string &filename);

private:
    const std::vector<char> &Charset();
private:
    const bool isDigits_;
};
