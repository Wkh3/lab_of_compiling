#pragma once
#include <unordered_map>
namespace lab {

template <typename T, typename U, typename F>
class StatusMachine {
public:
    using HandlerMap = std::unordered_map<T, F>;
    using StateType = T;
    using ValueType = U;

    StatusMachine() = default;

    StatusMachine(StateType state, const HandlerMap &m = HandlerMap())
        : state_(state), handlers_(m) {}

    void Register(StateType state, const F &f) {
        handlers_[state] = f;
    }

    void Register(const HandlerMap &m) {
        handlers_.insert(m.begin(), m.end());
    }

    void setState(StateType state) {
        state_ = state;
    }
    void getState() const {
        return state_;
    }

    virtual bool Post(U c) = 0;

    virtual ~StatusMachine() {}

protected:
    StateType state_;
    HandlerMap handlers_;
};

}   // namespace lab