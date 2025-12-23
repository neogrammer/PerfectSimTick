#ifndef DIR8_HPP
#define DIR8_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdint>

enum class Dir8 : std::uint8_t
{
    S = 0,
    SE = 1,
    E = 2,
    NE = 3,
    N = 4,
    NW = 5,
    W = 6,
    SW = 7
};

// SFML y+ is down, so "South" is (0,+1).
// This mapping makes angle 0 point to South, then rotates clockwise by rows.
inline Dir8 dir8_from_vec(sf::Vector2f v, Dir8 fallback = Dir8::S)
{
    const float eps = 0.001f;
    const float len2 = v.x * v.x + v.y * v.y;
    if (len2 < eps * eps) return fallback;

    // Swap args: atan2(x, y) gives 0 at +Y (South), 90° at +X (East)
    float a = std::atan2(v.x, v.y);

    const float pi = 3.1415926535f;
    const float twoPi = 2.0f * pi;

    // Round to nearest 45°
    a += (pi / 8.0f);
    if (a < 0) a += twoPi;

    int bucket = int((a / twoPi) * 8.0f) & 7;
    return static_cast<Dir8>(bucket);
}

#endif