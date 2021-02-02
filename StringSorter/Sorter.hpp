#pragma once
#include <string>

class StringsSorter
{
public:
    StringsSorter(const size_t buffer_size = 2);
    void Sort(const std::string &input_filename, const std::string &output_filename);

private:
    void BasicSort(const std::string &input_filename, const std::string &output_filename);

private:
    size_t buffer_size_;
};
