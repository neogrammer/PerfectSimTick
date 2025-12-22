#pragma once
#include <deque>
#include <memory>
#include "IAction.hpp"

enum class Mode : uint8_t { Idle, Locomote, PerformAction, Hitstun, Dead };

struct ActionMachine {
    Mode mode{ Mode::Idle };
    std::deque<Command> queue{};
    std::unique_ptr<IAction> current{};

    void push(Command c) { queue.push_back(c); }

    void update(Entity& e, float dt);
    void dispatchEvent(Entity& e, const Event& ev);

private:
    void tryConsume(Entity& e);
};