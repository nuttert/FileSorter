#include "Sorter.hpp"

#include <iostream>
#include <condition_variable>
#include <future>
#include <vector>
#include <set>
#include <unordered_map>
#include <fstream>
#include <random>
#include <thread>
#include <limits>

namespace
{
    std::pair<size_t, size_t> GetFileSizeAndLineLength(std::ifstream &file)
    {
        std::string line;
        std::getline(file, line);
        const size_t line_length = line.size();
        file.seekg(0, std::ios::end);
        auto file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        return {file_size, line_length};
    }

    std::fstream &GotoLine(std::fstream &file, unsigned int num)
    {
        for (int i = 0; i < num - 1; ++i)
        {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return file;
    }
} // namespace

StringsSorter::StringsSorter(const size_t buffer_size) : buffer_size_(buffer_size) {}

void StringsSorter::BasicSort(const std::string &input_filename, const std::string &output_filename)
{
    std::string line;
    std::vector<std::string> buffer;
    buffer.reserve(buffer_size_);
    size_t index = 0;

    std::ifstream file(input_filename);
    std::ofstream sorted_file(output_filename);

    if (!file.is_open())
        std::runtime_error("Couldn't open input file");
    if (!sorted_file.is_open())
        std::runtime_error("Couldn't open output file");
    // Оптимизация - чтобы merge sort производилась не с уровня сравнения двух строк
    while (!file.eof())
    {
        while (index < buffer_size_ && getline(file, line) && !line.empty())
        {
            ++index;
            buffer.push_back(line);
        }

        std::sort(buffer.begin(), buffer.end());
        for (size_t i = 0; i < index; ++i)
            sorted_file << buffer[i] << std::endl;
        buffer.clear();
        buffer.reserve(buffer_size_);
        index = 0;
    }
    sorted_file.close();
    file.close();
}

void StringsSorter::Sort(const std::string &input_filename, const std::string &output_filename)
{
    using namespace std::chrono_literals;
    static const std::string kTempFilename = "GeneratedData/temp_file.txt";

    std::cout << "Start sorting" << std::endl;
    std::cout << "Waiting..." << std::endl;

    std::string line;
    std::ifstream file(input_filename);

    size_t counter = 0;
    size_t carriage_1_line_index = 0;
    size_t carriage_2_line_index = 0;
    std::string line_1;
    std::string line_2;
    size_t bucket_size = buffer_size_;
    std::string source_filename = output_filename;
    std::string dest_filename = kTempFilename;
    const auto [file_size, line_length] = GetFileSizeAndLineLength(file);

    if (!file.is_open())
        std::runtime_error("Couldn't open input file");
    BasicSort(input_filename, output_filename);

    while (bucket_size * line_length <= file_size)
    {
        std::fstream carriage_1(source_filename);
        std::fstream carriage_2(source_filename);
        std::ofstream temp_file(dest_filename);

        GotoLine(carriage_2, bucket_size+1);

        while (carriage_1 ||
               carriage_2)
        {
            line_1.clear();
            line_2.clear();

            bool firstReading = true;

            while (carriage_1 && carriage_2 &&
                   carriage_1_line_index < bucket_size &&
                   carriage_2_line_index < bucket_size)
            {
                if (firstReading)
                {
                    std::getline(carriage_1, line_1);
                    std::getline(carriage_2, line_2);
                    firstReading = false;
                    if (line_1.empty() || line_2.empty())
                        break;
                }

                if (line_1 < line_2)
                {
                    temp_file << line_1 << std::endl;
                    ++carriage_1_line_index;
                    getline(carriage_1, line_1);
                }
                else
                {
                    temp_file << line_2 << std::endl;
                    ++carriage_2_line_index;
                    getline(carriage_2, line_2);
                }
            }

            if (!firstReading)
            {
                carriage_1.seekg(-line_1.size() - 1, std::ios::cur);
                carriage_2.seekg(-line_2.size() - 1, std::ios::cur);
            }

            while (carriage_1_line_index < bucket_size)
            {
                if (!carriage_1)
                    break;
                std::getline(carriage_1, line_1);
                if (line_1.empty())
                    break;

                temp_file << line_1;
                ++carriage_1_line_index;

                if (carriage_1 || carriage_2)
                    temp_file << std::endl;
            }

            while (carriage_2_line_index < bucket_size)
            {
                if (!carriage_2)
                    break;
                getline(carriage_2, line_2);
                if (line_2.empty())
                    break;
                temp_file << line_2;
                ++carriage_2_line_index;

                if (carriage_1 || carriage_2)
                    temp_file << std::endl;
            }

            carriage_1_line_index = 0;
            carriage_2_line_index = 0;

            GotoLine(carriage_1, bucket_size+1);
            GotoLine(carriage_2, bucket_size+1);
        }

        std::swap(source_filename, dest_filename);
        bucket_size *= 2;

        temp_file.close();
        carriage_2.close();
        carriage_1.close();
        ++counter;
    }
    std::swap(source_filename, dest_filename);
    std::cout << dest_filename << " " << output_filename;
    if (counter % 2 == 1){
        std::rename(dest_filename.c_str(), output_filename.c_str());
    }
    std::remove(kTempFilename.c_str());

    std::cout << "Successfully sorted: " << output_filename << std::endl;
    file.close();
}