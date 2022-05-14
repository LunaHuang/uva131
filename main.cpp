#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <regex>
#include <cctype>
#include <map>
#include <vector>

#if defined(WITH_GTEST)
#include <gtest/gtest.h>
#endif

class Poker
{
    // constructions
public:
    explicit Poker(std::string &input);

    // methods
public:
    void show(void);
    void show_map(void);
    std::string display_poker(void);
    std::string get_bast_combination(void);

private:
    void poker_to_map(void);

    // data
private:
    std::vector< std::string > poker_;
    std::multimap< int, std::string > poker_map_;
};

Poker::Poker(std::string &input)
{
    std::string token;
    std::stringstream ss(input);
    while (std::getline(ss, token, ' '))
        poker_.push_back(token);
}

void Poker::show(void)
{
    for (auto &it : poker_)
        std::cout << it << " ";
    std::cout << std::endl;
}

void Poker::show_map(void)
{
    for (auto &it : poker_map_)
        std::cout << it.first << " " << it.second << " ";
    std::cout << std::endl;
}

std::string Poker::display_poker(void)
{
    int i = 0;
    std::string out;
    for (auto pos = poker_.cbegin(); pos != poker_.cend(); ++pos) {
        if (i == 0)
            out = "Hand: " + *pos + " ";
        else if (i == 5)
            out = out + "Deck: " + *pos + " ";
        else
            out = out + *pos + " ";

        i++;
    }
    return out;
}

void Poker::poker_to_map(void)
{
    for (auto &it : poker_) {
        std::cout << it << " ";
        std::string f = it.substr(0, 1);
        int f_num;
        if (f == "A")
            f_num = 1;
        else if (f == "T")
            f_num = 10;
        else if (f == "J")
            f_num = 11;
        else if (f == "Q")
            f_num = 12;
        else if (f == "K")
            f_num = 13;
        else
            f_num = stoi(f);

        poker_map_.insert({ f_num, it.substr(1, 1) });
    }
}

std::string Poker::get_bast_combination()
{
    poker_to_map();
    show_map();
    std::string combine;
    combine = "Best hand: ";
    return combine;
}

void poker_combination(std::string input, std::ostream &os)
{
    Poker poker(input);
    //    poker.show();
    std::string out = poker.display_poker();
    out = out + poker.get_bast_combination();
    os << out << std::endl;
}

void solve_uva_problem(std::istream &is, std::ostream &os)
{
    while (1) {
        std::string poker_input;
        std::getline(is, poker_input);
        if (poker_input.empty())
            break;
        poker_combination(poker_input, os);
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
