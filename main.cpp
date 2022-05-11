#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <regex>
#include <cctype>
#include <map>
#include <deque>
#include <vector>

#if defined(WITH_GTEST)
#include <gtest/gtest.h>
#endif

class Train
{

public:
    void show(void)
    {
        for (auto &it : on_rail_) {
            std::cout << it << " ";
        }
        std::cout << std::endl;
    }

    void operator<<(const std::string &line)
    {
        char *token = strtok(const_cast< char * >(line.c_str()), " ");
        while (token != nullptr) {
            on_rail_.push_back(std::stoi(std::string(token)));
            token = strtok(nullptr, " ");
        }
    }

private:
    std::deque< int > on_rail_;
    std::deque< int > on_station_;
};

void solve_uva_problem(std::istream &is, std::ostream &os)
{
    std::string numbers;
    std::getline(is, numbers);
    int num = std::stoi(numbers);
    while (1) {
        std::getline(is, numbers);
        if (numbers.compare("0") != 0) {
            if (check_permutations(numbers, num) == true)
                os << "Yes" << std::endl;
            else
                os << "No" << std::endl;
        } else {
            os << std::endl;
            std::getline(is, numbers);
            if (numbers.compare("0") == 0)
                break;
            else
                num = std::stoi(numbers);
        }
    }
}

int main(int argc, char **argv)
{
#if !defined(WITH_GTEST)
    solve_uva_problem(std::cin, std::cout);
#else
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif
}
