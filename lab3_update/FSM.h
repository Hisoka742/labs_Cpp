#ifndef LAB3_FSM_H
#define LAB3_FSM_H

#include <iterator>
#include <map>
#include <set>
#include <string>

namespace FSM {
    template <typename T_symbol, typename T_state>
    class transition_functor {
    public:
        transition_functor(
            std::map<T_state, std::map<T_symbol, T_state>> transition_list,
            T_state devil_state)
            :

            transition_list_(transition_list),
            devil_state_(devil_state) {}

        T_state& operator()(T_state current_state, T_symbol symbol) {
            if (current_state == devil_state_) {
                return devil_state_;
            }
            if (transition_list_[current_state].count(symbol)) {
                return transition_list_[current_state][symbol];
            }
            return devil_state_;
        }

        T_state get_devil_state() const { return devil_state_; }

    private:
        std::map<T_state, std::map<T_symbol, T_state>> transition_list_;
        T_state devil_state_;
    };

    template <typename T_symbol, typename T_state, typename T_sequence>
    class FSM {
    public:
        FSM(transition_functor<T_symbol, T_state>& transition_functor,
            std::set<T_state> acceptable_states, T_state start_state)
            : transition_functor_(transition_functor),
            start_state_(start_state),
            acceptable_states_(acceptable_states) {}

        bool check(const T_sequence& seq) {
            T_state current_state = start_state_;
            for (auto& i : seq) {
                current_state = transition_functor_(current_state, i);
            }
            return acceptable_states_.count(current_state);
        }

    private:
        transition_functor<T_symbol, T_state>& transition_functor_;
        std::set<T_state> acceptable_states_;
        T_state start_state_;
    };

    // частичная специализация для случая, когда алфавит - строки, и
    // последовательность для обработки - строка
    template <typename T_state>
    class FSM<std::string, T_state, std::string> {
    public:
        FSM(transition_functor<std::string, T_state>& transition_functor,
            std::set<T_state> acceptable_states, T_state start_state)
            : transition_functor_(transition_functor),
            start_state_(start_state),
            acceptable_states_(acceptable_states) {}

        bool check(const std::string& seq) {
            T_state current_state = this->start_state_;
            std::string parsed;
            for (char i : seq) {
                parsed += i;
                int next_state = this->transition_functor_(current_state, parsed);
                if (next_state != this->transition_functor_.get_devil_state()) {
                    current_state = next_state;
                    parsed = "";
                }
            }
            return acceptable_states_.count(current_state);
        }

    private:
        transition_functor<std::string, T_state>& transition_functor_;
        std::set<T_state> acceptable_states_;
        T_state start_state_;
    };
}  // namespace FSM
#endif  // LAB3_FSM_H
