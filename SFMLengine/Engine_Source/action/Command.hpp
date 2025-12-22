#pragma once
#include <cstdint>

struct Vec2 { float x{}, y{}; };

enum class CommandType : uint8_t {
    MoveTo,
    MoveDir,     // optional
    UseAbility,
    Cancel,
    Interact
};

struct Command {
    CommandType type{};
    Vec2        v{};        // destination or direction
    int         abilityId{ -1 };
};