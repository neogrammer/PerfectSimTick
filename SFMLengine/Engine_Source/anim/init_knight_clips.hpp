#ifndef INIT_KNIGHT_CLIPS_HPP
#define INIT_KNIGHT_CLIPS_HPP

#include "PlayerAnimator.hpp"

inline void initKnightClips(PlayerAnimator& anim)
{
    constexpr int FW = 299;
    constexpr int FH = 240;

    // You can tweak these later. Keep them simple for now.
    constexpr float FT_IDLE = 0.08f;
    constexpr float FT_WALK = 0.07f;
    constexpr float FT_RUN = 0.055f;
    constexpr float FT_JUMP = 0.06f;
    constexpr float FT_ATTACK = 0.05f;
    constexpr float FT_BLOCK = 0.06f;
    constexpr float FT_HIT = 0.06f;
    constexpr float FT_DEATH = 0.09f;

    anim.setClip(AnimKey::Idle, ClipDef{
        .bodyTex = Assets::Textures::Knight_Idle,
        .shadowTex = Assets::Textures::Knight_Idle_Shadow,
        .frameW = FW, .frameH = FH, .frames = 16, .frameTime = FT_IDLE, .loop = true
        });

    anim.setClip(AnimKey::Walk, ClipDef{
        .bodyTex = Assets::Textures::Knight_Walk,
        .shadowTex = Assets::Textures::Knight_Walk_Shadow,
        .frameW = FW, .frameH = FH, .frames = 15, .frameTime = FT_WALK, .loop = true
        });

    anim.setClip(AnimKey::Run, ClipDef{
        .bodyTex = Assets::Textures::Knight_Run,
        .shadowTex = Assets::Textures::Knight_Run_Shadow,
        .frameW = FW, .frameH = FH, .frames = 17, .frameTime = FT_RUN, .loop = true
        });

    anim.setClip(AnimKey::Jump, ClipDef{
        .bodyTex = Assets::Textures::Knight_Jump,
        .shadowTex = Assets::Textures::Knight_Jump_Shadow,
        .frameW = FW, .frameH = FH, .frames = 16, .frameTime = FT_JUMP, .loop = false
        });

    anim.setClip(AnimKey::Attack, ClipDef{
        .bodyTex = Assets::Textures::Knight_Attack,
        .shadowTex = Assets::Textures::Knight_Attack_Shadow,
        .frameW = FW, .frameH = FH, .frames = 18, .frameTime = FT_ATTACK, .loop = false
        });

    anim.setClip(AnimKey::Block, ClipDef{
        .bodyTex = Assets::Textures::Knight_Block,
        .shadowTex = Assets::Textures::Knight_Block_Shadow,
        .frameW = FW, .frameH = FH, .frames = 17, .frameTime = FT_BLOCK, .loop = true
        });

    anim.setClip(AnimKey::GotHit, ClipDef{
        .bodyTex = Assets::Textures::Knight_GotHit,
        .shadowTex = Assets::Textures::Knight_GotHit_Shadow,
        .frameW = FW, .frameH = FH, .frames = 13, .frameTime = FT_HIT, .loop = false
        });

    anim.setClip(AnimKey::Death, ClipDef{
        .bodyTex = Assets::Textures::Knight_Death,
        .shadowTex = Assets::Textures::Knight_Death_Shadow,
        .frameW = FW, .frameH = FH, .frames = 9, .frameTime = FT_DEATH, .loop = false
        });
}

#endif