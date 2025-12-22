// IN objects/Entity.hpp
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <functional>
#include <cmath>

#include <SFML/System/Vector2.hpp>

#include <objects/VisObj.hpp>

// Action system headers (yours)
#include "Command.hpp"
#include "Events.hpp"
#include "AnimRequest.hpp"
#include "InputBuffer.hpp"
#include "ActionMachine.hpp"

class IAction;

class Entity : public VisObj
{
public:
    using AbilityFactoryFn = std::function<std::unique_ptr<IAction>(int abilityId)>;

private:
    // --- core systems ---
    InputBuffer  m_inputBuffer{};
    ActionMachine m_actions{};

    // --- animation request (picked by priority) ---
    AnimRequest m_animReq{};
    bool        m_hasAnimReq{ false };

    // --- simple locomotion (optional; can be replaced with your own movement) ---
    sf::Vector2f m_vel{ 0.f, 0.f };

    sf::Vector2f m_moveTarget{ 0.f, 0.f };
    bool         m_hasMoveTarget{ false };

    float m_walkSpeed{ 120.f };
    float m_runSpeed{ 220.f };
    float m_stopDist{ 2.0f };

    // --- combo helpers ---
    float m_timeSinceLastDash{ 9999.f };

    // --- ability/action creation ---
    AbilityFactoryFn m_makeAbility{};

public:
    Entity(obj::type type_ = obj::type::vis_obj,
        Assets::Textures tex_ = Assets::Textures::Invariant,
        sf::IntRect rect_ = { {0,0},{0,0} },
        sf::Vector2f texOff_ = { 0.f,0.f })
        : VisObj(type_, tex_, rect_, texOff_)
    {
    }

    // ---- update ----
    void update(float dt)
    {
        // timers/buffers
        m_inputBuffer.update(dt);
        m_timeSinceLastDash += dt;

        // clear per-frame anim request "winner"
        m_hasAnimReq = false;
        m_animReq = AnimRequest{};

        // actions decide what we are doing + request animation
        m_actions.update(*this, dt);

        // if no action requested an anim, fall back to locomotion/idle
        if (!m_hasAnimReq)
            requestAnim(locomotionAnim());

        // simple movement step (only if you use move targets)
        stepMoveTarget(dt);
    }

    // ---- access to subsystems ----
    InputBuffer& inputBuffer() noexcept { return m_inputBuffer; }
    const InputBuffer& inputBuffer() const noexcept { return m_inputBuffer; }

    ActionMachine& actions() noexcept { return m_actions; }
    const ActionMachine& actions() const noexcept { return m_actions; }

    // ---- events from animation/physics/etc ----
    void dispatchEvent(const Event& ev) { m_actions.dispatchEvent(*this, ev); }

    // ---- animation API (actions/states call this) ----
    void requestAnim(const AnimRequest& req)
    {
        if (!m_hasAnimReq || req.priority >= m_animReq.priority) {
            m_animReq = req;
            m_hasAnimReq = true;
        }
    }

    bool hasAnimRequest() const noexcept { return m_hasAnimReq; }
    const AnimRequest& animRequest() const noexcept { return m_animReq; }

    // ---- locomotion animation fallback ----
    AnimRequest locomotionAnim() const
    {
        const float sp = std::sqrt(m_vel.x * m_vel.x + m_vel.y * m_vel.y);

        AnimRequest r{};
        if (sp < 0.01f) {
            r.key = AnimKey::Idle;
            r.loop = true;
            r.speed01 = 0.0f;
            r.priority = 0;
            return r;
        }

        // crude: walk vs run threshold
        const float runThresh = (m_walkSpeed + m_runSpeed) * 0.5f;
        r.key = (sp >= runThresh) ? AnimKey::Run : AnimKey::Walk;
        r.loop = true;

        // scale playback a bit (0..1-ish)
        const float denom = (r.key == AnimKey::Run) ? m_runSpeed : m_walkSpeed;
        r.speed01 = (denom > 0.f) ? (sp / denom) : 1.f;

        r.priority = 0;
        return r;
    }

    // ---- ability creation (ActionMachine calls this) ----
    void setAbilityFactory(AbilityFactoryFn fn) { m_makeAbility = std::move(fn); }

    std::unique_ptr<IAction> makeAbilityAction(int abilityId)
    {
        if (!m_makeAbility) return {};
        return m_makeAbility(abilityId);
    }

    // ---- movement helpers (optional) ----
    void setVelocity(sf::Vector2f v) { m_vel = v; }
    const sf::Vector2f& velocity() const noexcept { return m_vel; }

    void setMoveTarget(sf::Vector2f p)
    {
        m_moveTarget = p;
        m_hasMoveTarget = true;
    }

    void clearMoveTarget() { m_hasMoveTarget = false; }

    void setWalkSpeed(float s) { m_walkSpeed = s; }
    void setRunSpeed(float s) { m_runSpeed = s; }
    void setStopDist(float d) { m_stopDist = d; }

    // ---- combo helpers ----
    void noteDashStarted() { m_timeSinceLastDash = 0.f; }
    float timeSinceLastDash() const noexcept { return m_timeSinceLastDash; }

private:
    void stepMoveTarget(float dt)
    {
        if (!m_hasMoveTarget) {
            // if nobody sets velocity manually, decay
            m_vel = { 0.f, 0.f };
            return;
        }

        const sf::Vector2f pos = getWPos();
        sf::Vector2f d{ m_moveTarget.x - pos.x, m_moveTarget.y - pos.y };

        const float dist2 = d.x * d.x + d.y * d.y;
        if (dist2 <= (m_stopDist * m_stopDist)) {
            m_hasMoveTarget = false;
            m_vel = { 0.f, 0.f };
            return;
        }

        const float dist = std::sqrt(dist2);
        d.x /= dist;
        d.y /= dist;

        const float speed = m_walkSpeed; // you can switch to run based on state/command
        m_vel = { d.x * speed, d.y * speed };

        moveWPos({ m_vel.x * dt, m_vel.y * dt });
    }
};

#endif