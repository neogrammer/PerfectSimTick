#include "ActionMachine.hpp"
#include "Entity.hpp"

void ActionMachine::update(Entity& e, float dt)
{
    tryConsume(e);

    if (current) {
        current->update(e, dt);
        e.requestAnim(current->anim());

        if (current->isDone()) {
            current.reset();
            mode = Mode::Idle;
            // optional: emit Ev_ActionDone here
        }
    }
    else {
        // locomotion / idle anim based on velocity etc.
        e.requestAnim(e.locomotionAnim());
    }
}

void ActionMachine::dispatchEvent(Entity& e, const Event& ev)
{
    if (current) current->onEvent(e, ev);

    // example: hit taken can force mode switch regardless
    if (std::holds_alternative<Ev_HitTaken>(ev)) {
        // if you want hitstun to override:
        // current.reset(); mode = Mode::Hitstun;
    }
}

void ActionMachine::tryConsume(Entity& e)
{
    if (queue.empty()) return;

    Command cmd = queue.front();

    // Interrupt logic
    if (current && current->canBeInterruptedBy(cmd)) {
        current.reset();
        mode = Mode::Idle;
    }

    if (current) return; // still busy

    // Here: map command -> action factory (per-entity ability set)
    if (cmd.type == CommandType::UseAbility) {
        auto action = e.makeAbilityAction(cmd.abilityId);
        if (action && action->canStart(e)) {
            queue.pop_front();
            current = std::move(action);
            mode = Mode::PerformAction;
            current->start(e);
            return;
        }
    }

    // Commands that don’t produce actions (move) can go straight to locomotion
    if (cmd.type == CommandType::MoveTo) {
        queue.pop_front();
        e.setMoveTarget(sf::Vector2f((float)cmd.v.x, (float)cmd.v.y));
        mode = Mode::Locomote;
        return;
    }

    // If we get here: ignored (or keep it queued if you prefer)
    queue.pop_front();
}