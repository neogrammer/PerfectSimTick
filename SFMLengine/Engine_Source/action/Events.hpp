#pragma once
#include <variant>
#include "Command.hpp"

struct Ev_AnimMarker { int markerId; };      // e.g. "spawn_hitbox"
struct Ev_HitTaken { int damage; Vec2 knock; };
struct Ev_ActionDone { int abilityId; };

using Event = std::variant<Ev_AnimMarker, Ev_HitTaken, Ev_ActionDone>;