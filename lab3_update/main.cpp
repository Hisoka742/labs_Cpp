#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <array> 

#include "FSM.h"

using namespace std;

void test1() {
    cout << "Test 1" << endl;
    map<int, map<char, int>> move = {
        {0,
         map<char, int>{
             {'a', 1},
             {'b', 2},
         }},
        {1,
         map<char, int>{
             {'a', -1},
             {'b', 2},
         }},
        {2,
         map<char, int>{
             {'a', 1},
             {'b', -1},
         }},
    };

    set<int> acceptable_states = { 1, 2 };

    FSM::transition_functor<char, int> move_functor(move, -1);

    FSM::FSM<char, int, string> fsm1(move_functor, acceptable_states, 0);
    FSM::FSM<char, int, vector<char>> fsm2(move_functor, acceptable_states, 0);

    cout << fsm1.check("ababab") << endl;
    cout << fsm2.check(vector<char>{'a', 'b', 'c'}) << endl;
}

void test2() {
    cout << "Test 2" << endl;
    map<int, map<string, int>> move = { {0, {{"a", 1}, {"ab", 2}}},
                                       {1, {{"b", 3}, {"aa", 0}}},
                                       {2, {{"ba", 1}, {"", 0}}},
                                       {3, {{"bbb", 0}, {"a", 2}}} };
    set<int> acceptable_states = { 3 };
    FSM::transition_functor<string, int> move_functor(move, -1);
    FSM::FSM<string, int, array<string, 4>> fsm(move_functor,
        acceptable_states, 0);

    cout << fsm.check({ "a", "aa", "a", "b" }) << endl;
    cout << fsm.check({ "a", "aa", "a", "aa" }) << endl;
}

void test3() {
    cout << "Test 3" << endl;
    map<int, map<string, int>> move = { {0, {{"x", 1}, {"ab", 2}}},
                                       {1, {{"b", 3}, {"aa", 0}}},
                                       {2, {{"ba", 1}, {"z", 0}}},
                                       {3, {{"bbb", 0}, {"a", 2}}} };
    set<int> acceptable_states = { 3 };
    FSM::transition_functor<string, int> move_functor(move, -1);
    FSM::FSM<string, int, string> fsm(move_functor, acceptable_states, 0);

    cout << fsm.check("abbab") << endl;
    cout << fsm.check("baba") << endl; // Test case "baba"
    cout << fsm.check("bba") << endl;  // Test case "bba"
    cout << fsm.check("baab") << endl; // Test case "baab"
}

int main() {
    test1();
    test2();
    test3();
}

