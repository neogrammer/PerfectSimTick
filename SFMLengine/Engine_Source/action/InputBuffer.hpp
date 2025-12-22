#pragma once
#include <array>
#include <optional>
#include <cstdint>
#include "Command.hpp"

enum class BufferSlot : uint8_t { Attack, Jump, Dash, Interact, COUNT };

struct BufferedCmd {
    Command cmd{};
    float   ttl{ 0.0f };        // seconds remaining
    float   pressAge{ 0.0f };   // seconds since the ORIGINAL press
    bool    poisoned{ false };  // set true if repeated presses happened
};

class InputBuffer {
public:
    void update(float dt)
    {
        for (auto& s : m_slots) {
            if (!s) continue;
            s->ttl -= dt;
            s->pressAge += dt;
            if (s->ttl <= 0.0f) s.reset();
        }
    }

    void push_poison(BufferSlot slot, const Command& cmd, float ttl)
    {
        auto& s = m_slots[(size_t)slot];
        if (!s) {
            s = BufferedCmd{ cmd, ttl, 0.0f, false };
            return;
        }

        // Spam: extend life, but DO NOT change pressAge (timestamp stays "too early")
        s->ttl = (s->ttl < ttl) ? ttl : s->ttl;  // or += ttl_small, your choice
        s->poisoned = true;
    }

    // Window check: returns true only if command originated inside [winStart, winEnd]
    // where winStart/winEnd are ages in seconds since the press is time 0.
    bool consume_if_in_window(BufferSlot slot, float winStart, float winEnd, Command& out)
    {
        auto& s = m_slots[(size_t)slot];
        if (!s) return false;

        const float age = s->pressAge;

        if (age >= winStart && age <= winEnd) {
            out = s->cmd;
            s.reset();
            return true;
        }

        // outside window: punishment behavior
        // If poisoned, keep it to block later attempts (unfair-on-purpose).
        // If not poisoned, do nothing; it may expire naturally.
        return false;
    }

    bool has(BufferSlot slot) const { return m_slots[(size_t)slot].has_value(); }
    void clear() { for (auto& s : m_slots) s.reset(); }

private:
    std::array<std::optional<BufferedCmd>, (size_t)BufferSlot::COUNT> m_slots{};
};