#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <regex>
#include <cctype>
#include <map>
#include <vector>
#include <algorithm> 

#if defined(WITH_GTEST)
#include <gtest/gtest.h>
#endif

enum Level
{
	Straight_flush,
	Four_kind,
	Full_house,
	Flush,
	Straight,
	Three_kind,
	Two_pairs,
	One_pair,
	High_card,
};

class Poker
{
    // constructions
public:
    explicit Poker(std::string &input);

    // methods
public:
    void show();
    void show(std::vector< auto >);
    std::string display_poker(void);
    std::string display_bast_combination(void);

private:
    int flush_straight_test(void);
    int pairs_test(void);
    int other_test(void);
    int get_bast_combination(void);

    // data
private:
    std::vector< std::string > poker_;
    std::vector< int > poker_num_;
    std::vector< char > poker_suit_;
};

Poker::Poker(std::string &input)
{
    std::string token;
    std::stringstream ss(input);
    while (std::getline(ss, token, ' ')){
        poker_.push_back(token);
        poker_suit_.push_back(token[1]);
        std::string f = token.substr(0, 1);
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
        poker_num_.push_back(f_num);
	}
}

void Poker::show(void)
{
    std::cout <<"input poker: " << std::endl;
    for (auto &it: poker_)
        std::cout << it << " ";
    std::cout << std::endl;
}

void Poker::show(std::vector< auto > vector)
{
    std::cout <<"vector: " << std::endl;
//    for (auto &it: vector)
	for(int i = 0; i < vector.size(); i++)
        std::cout << vector[i] << " ";
        //std::cout << it << " ";
    std::cout << std::endl;
}

int Poker::flush_straight_test()
{
	int ret = Level::High_card;
	int hand_num = 0;
	std::vector<char> suit{'C', 'D', 'H', 'S'};
    for (auto &it : suit){
		int count = std::count(poker_suit_.begin(), poker_suit_.end(), it);
		//std::cout << "get " << it << ":" << count << std::endl;
		if(count >= 5){
			//std::map<int, int> matches;
			std::vector<int> matches;
			for(int i = 0; i < poker_suit_.size(); i++){
				if(poker_suit_[i] == it){
					matches.push_back(poker_num_[i]);
				//	matches[poker_num_[i]] = i;
				//	std::cout << poker_num_[i] <<":"<< i << std::endl;
					if(i < 5)
						hand_num++;
					if(i > (count - hand_num + 5))
						break;
				}
				ret = Level::Flush;
			}
			if(ret == Level::Flush){
				std::sort(matches.begin(), matches.end());
				show(matches);
				std::vector<int> straight1 { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
				std::vector<int> straight2 { 1,10,11,12,13 };

				for(int i=0; (i+5) <= matches.size();i++){
					std::vector<int>::iterator it = search(straight1.begin(), straight1.end(), &matches[i], &matches[5 + i]);
					if (it != straight1.end()){
						ret = Level::Straight_flush;
						break;
					}
					it = search(straight2.begin(), straight2.end(), &matches[i], &matches[5 + i]);
					if (it != straight2.end()){
						ret = Level::Straight_flush;
						break;
					}
				}
			}
		}
	}
	return ret;
}

int Poker::pairs_test()
{
	int ret = Level::High_card;
	std::vector<char> suit{'C', 'D', 'H', 'S'};
    for (auto &it : suit){
		int count = std::count(poker_suit_.begin(), poker_suit_.end(), it);
		std::cout << "get " << it << ":" << count << std::endl;
	}
	return ret;
}

int Poker::other_test()
{
	int ret = Level::High_card;
	std::vector<char> suit{'C', 'D', 'H', 'S'};
    for (auto &it : suit){
		int count = std::count(poker_suit_.begin(), poker_suit_.end(), it);
		std::cout << "get " << it << ":" << count << std::endl;
	}
	return ret;
}

int Poker::get_bast_combination()
{
	int ret = Level::High_card;
	ret = flush_straight_test();
	return ret;
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

std::string Poker::display_bast_combination()
{
    std::string combine;
    combine = "Best hand: ";
	int best = get_bast_combination();
	switch(best) {
		case Level::Straight_flush:
			combine = combine + "straight-flush";
			break;
		case Level::Four_kind:
			combine = combine + "four-of-a-kind";
			break;
		case Level::Full_house:
			combine = combine + "full-house";
			break;
		case Level::Flush:
			combine = combine + "flush";
			break;
		case Level::Straight:
			combine = combine + "straight";
			break;
		case Level::Three_kind:
			combine = combine + "three-of-a-kind";
			break;
		case Level::Two_pairs:
			combine = combine + "two-pairs";
			break;
		case Level::One_pair:
			combine = combine + "one-pair";
			break;
		default:
			combine = combine + "highest-card";
	}
    return combine;
}

void poker_combination(std::string input, std::ostream &os)
{
    Poker poker(input);
    poker.show();
    std::string out = poker.display_poker();
    out = out + poker.display_bast_combination();
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
