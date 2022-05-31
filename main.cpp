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

enum Level {
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

#define DECK_START_NUM 5
#define HAND_NUM       5
class Poker
{
    // constructions
public:
    explicit Poker(std::string &input);

    // methods
public:
    void show();
    std::string display_poker(void);
    std::string display_bast_combination(void);

private:
    int flush_straight_test(void);
    int kind_test(void);
    int other_test(void);
    bool straight_test(void);
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
    while (std::getline(ss, token, ' ')) {
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
    std::cout << "input poker: " << std::endl;
    for (auto &it : poker_)
        std::cout << it << " ";
    std::cout << std::endl;
}

int Poker::flush_straight_test()
{
    int ret = Level::High_card;
    std::vector< char > suit { 'C', 'D', 'H', 'S' };
    for (auto &it : suit) {
        int count = std::count(poker_suit_.begin(), poker_suit_.end(), it);
        int hand_num = 0;
        int deck_num = 0;
        if (count >= 5) {
            std::vector< int > matches;
            for (int i = 0; i < poker_suit_.size(); i++) {
                if (i < 5) {
                    if (poker_suit_[i] == it) {
                        hand_num++;
                        matches.push_back(poker_num_[i]);
                    }
                    continue;
                } else {
                    if ((poker_suit_[i] != it) && ((deck_num + hand_num) < 5)) {
                        break;
                    }
                    if (poker_suit_[i] == it) {
                        if (i >= (count - hand_num + DECK_START_NUM)) {
                            break;
                        } else {
                            matches.push_back(poker_num_[i]);
                            deck_num++;
                            if ((deck_num + hand_num) >= 5)
                                ret = Level::Flush;
                        }
                    }
                }
            }
            if (ret == Level::Flush) {
                std::sort(matches.begin(), matches.end());
                std::vector< int > straight1 { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
                std::vector< int > straight2 { 1, 10, 11, 12, 13 };

                for (int i = 0; (i + 5) <= matches.size(); i++) {
                    std::vector< int >::iterator it = search(straight1.begin(), straight1.end(), &matches[i], &matches[5 + i]);
                    if (it != straight1.end()) {
                        ret = Level::Straight_flush;
                        break;
                    }
                    it = search(straight2.begin(), straight2.end(), &matches[i], &matches[5 + i]);
                    if (it != straight2.end()) {
                        ret = Level::Straight_flush;
                        break;
                    }
                }
            }
        }
    }
    return ret;
}

int Poker::kind_test()
{
    int ret = Level::High_card;
    std::vector< int > number { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
    for (auto &it : number) {
        int hand_num = 0;
        int count = std::count(poker_num_.begin(), poker_num_.end(), it);
        int check_num = count;
        if (count == 4) {
            for (int i = 0; i < poker_num_.size(); i++) {
                //				std::cout << "i " << i << " " << hand_num<< std::endl;
                if (poker_num_[i] == it) {
                    if (i < HAND_NUM) {
                        hand_num++;
                        check_num--;
                        continue;
                    }
                    if (i > (4 - hand_num + DECK_START_NUM)) {
                        //						std::cout << "fail 1" << std::endl;
                        break;
                    }
                    check_num--;
                }
                if ((ret > Level::Four_kind) && (check_num == 0))
                    ret = Level::Four_kind;
            }
        } else if (count == 3) {
            for (int i = 0; i < poker_num_.size(); i++) {
          //      std::cout << "i " << i << " " << hand_num << std::endl;
                if (poker_num_[i] == it) {
                    if (i < HAND_NUM) {
                        hand_num++;
                        check_num--;
                        continue;
                    }
                    if (i > (4 - hand_num + DECK_START_NUM)) {
                        std::cout << "fail 2" << std::endl;
                        break;
                    }
                    check_num--;
                }
                if ((ret > Level::Three_kind) && (check_num == 0))
                    ret = Level::Three_kind;
            }
        } else if (count == 2) {
            for (int i = 0; i < poker_num_.size(); i++) {
                if (poker_num_[i] == it) {
                    if (i < HAND_NUM) {
                        hand_num++;
                        check_num--;
                        continue;
                    }
                    if (i > (4 - hand_num + DECK_START_NUM)) {
                        //						std::cout << "fail" << std::endl;
                        break;
                    }
                    check_num--;
                }
                if ((ret > Level::One_pair) && (check_num == 0))
                    ret = Level::One_pair;
            }
        }
    }
    return ret;
}

int Poker::other_test()
{
    int ret = Level::High_card;

    std::vector< int > poker_num = poker_num_;
    std::vector< int > number { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
    for (auto &it : number) {
        int count = std::count(poker_num_.begin(), poker_num_.end(), it);
		if(count >= 3){
			int hand_num = 0;
			int num = 0;
			std::map< int, int > candidate_value;
			int more_count = count - 3;
			count = 3;
            for (num = 0; num < poker_num_.size(); num++) {
                if (poker_num_[num] == it){
					if (num < HAND_NUM)
                        hand_num++;
                    if (num > (4 - hand_num + DECK_START_NUM))
                        break;
                    count--;
					if (count == 0)
						break;
				} else
					candidate_value[poker_num_[num]]++;
			}
			for (std::map< int, int >::iterator it = candidate_value.begin(); it != candidate_value.end(); ++it) {
				if(it->second >= 2){
					int count_sec = std::count(poker_num_.begin(), poker_num_.begin()+HAND_NUM, it->first);
					if((num + hand_num + count_sec) < poker_num_.size())
						return Level::Full_house;
				}
			}
		}
		if(count >= 2){
			int hand_num = 0;
			int num = 0;
			std::map< int, int > candidate_value;
			count = 2;
            for (num = 0; num < poker_num_.size(); num++) {
                if (poker_num_[num] == it){
					if (num < HAND_NUM)
                        hand_num++;
                    if (num > (4 - hand_num + DECK_START_NUM))
                        break;
                    count--;
					if (count == 0)
						break;
				} else
					candidate_value[poker_num_[num]]++;
			}
			for (std::map< int, int >::iterator it = candidate_value.begin(); it != candidate_value.end(); ++it) {
				if(it->second >= 2){
					int count_sec = std::count(poker_num_.begin(), poker_num_.begin()+HAND_NUM, it->first);
					if((num + hand_num + count_sec) < poker_num_.size())
						if (ret > Level::Two_pairs)
							ret = Level::Two_pairs;
				}
			}
		}

    }
	return ret;
}

bool Poker::straight_test()
{
    std::map< int, int > candidate_value;

    for (auto &it : poker_num_) {
        candidate_value[it]++;
    }

    if (candidate_value.size() < 5)
        return false;

    int count = 0;
    int last = 0;
    for (std::map< int, int >::iterator it = candidate_value.begin(); it != candidate_value.end(); ++it) {
        if (last == 0) {
            last = it->first;
            count++;
            continue;
        }
        if ((it->first - last) != 1) {
            count = 0;
            continue;
        }
        last = it->first;
        count++;
        if (count == 5)
            break;
    }
    if (count != 5)
        return false;
    std::vector< int > deck_num;
    for (int i = 0; i < count; i++) {
        std::vector< int >::iterator it = std::find(poker_num_.begin(), poker_num_.begin() + HAND_NUM, last - i);
        if (it == poker_num_.begin() + HAND_NUM) {
            deck_num.push_back(last - i);
        }
    }
    for (int i = 0; i < deck_num.size(); i++) {
        std::vector< int >::iterator it = std::find(poker_num_.begin(), poker_num_.begin() + HAND_NUM + deck_num.size(), deck_num[i]);
        if (it == poker_num_.begin() + HAND_NUM + deck_num.size()) {
            return false;
        }
    }
    return true;
}

int Poker::get_bast_combination()
{
    int ret = Level::High_card;
    //check Straight_flush or Flush
    int ret_temp = flush_straight_test();
    if (ret_temp == Level::Straight_flush)
        return ret_temp;
    //check Four_kind/Three_kind/One_pair
    int ret_temp2 = kind_test();
    if (ret_temp2 == Level::Four_kind)
        return ret_temp2;
    //check Full_house/Two_pairs
    int ret_temp3 = other_test();
    if (ret_temp3 == Level::Full_house)
        return ret_temp3;
    //check Straight
    if (straight_test())
        return Level::Straight;
    return std::min({ ret, ret_temp, ret_temp2, ret_temp3 });
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
    switch (best) {
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
