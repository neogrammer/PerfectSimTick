#pragma once
#include <memory>
#include "Command.hpp"
#include "Events.hpp"
#include "AnimRequest.hpp"

class Entity; // forward

struct IAction {
    virtual ~IAction() = default;

    virtual bool canStart(Entity& e) const = 0;
    virtual void start(Entity& e) = 0;
    virtual void update(Entity& e, float dt) = 0;
    virtual void onEvent(Entity& e, const Event& ev) = 0;

    virtual bool isDone() const = 0;
    virtual int  priority() const { return 10; }          // used for interrupts
    virtual bool canBeInterruptedBy(const Command& cmd) const { (void)cmd; return false; }
    virtual AnimRequest anim() const = 0;
};