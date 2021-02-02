#include "Generator.hpp"

#include <random>
#include <thread>
#include <iostream>
#include <fstream>

Generator::Generator(const bool isDigits) : isDigits_(isDigits)
{
    std::cout << "Only digits mode" << std::endl;
}

void Generator::Generate(const size_t lines, const size_t length, const std::string &filename)
{
    static const auto kBufferSize = 1000000;
    std::ofstream out;
    out.open(filename);

    auto &chars = Charset();

    std::default_random_engine rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, chars.size() - 1);
    auto randchar = [chars, &dist, &rng]() { return chars[dist(rng)]; };

    std::string strfile = "";
    if (out.is_open())
    {
        out.clear();
        for (size_t i = 0; i < lines; ++i)
        {
            std::string str(length, 0);
            std::generate_n(str.begin(), length, randchar);
            strfile += str + "\n";

            if (i % kBufferSize == 0)
            {
                out << strfile;
                strfile = "";
            }
        }
        out << strfile << std::endl;
        out.close();
    }

    std::cout << "Generated file: " << filename << std::endl
              << "lines:  " << lines << ", length: " << length << std::endl;
}
const std::vector<char> &Generator::Charset()
{
    const static std::vector<char> digits{
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
    };
    const static std::vector<char> chars{'0', '1', '2', '3', '4',
                                          '5', '6', '7', '8', '9',
                                          'A', 'B', 'C', 'D', 'E', 'F',
                                          'G', 'H', 'I', 'J', 'K',
                                          'L', 'M', 'N', 'O', 'P',
                                          'Q', 'R', 'S', 'T', 'U',
                                          'V', 'W', 'X', 'Y', 'Z',
                                          'a', 'b', 'c', 'd', 'e', 'f',
                                          'g', 'h', 'i', 'j', 'k',
                                          'l', 'm', 'n', 'o', 'p',
                                          'q', 'r', 's', 't', 'u',
                                          'v', 'w', 'x', 'y', 'z'};
    return isDigits_ ? digits : chars;
};