#pragma once
#include <cstdint>

enum class AnimKey : uint16_t
{
    Idle, Walk, Run, Jump,
    Attack, Block, GotHit, Death
};

struct AnimRequest {
    AnimKey key{ AnimKey::Idle };
    float   speed01{ 0.0f };     // 0..1 (for walk/run rate scaling)
    bool    loop{ true };
    int     priority{ 0 };       // higher wins
};