#ifndef PLAYER_ANIMATOR_HPP
#define PLAYER_ANIMATOR_HPP

#include <array>
#include <cstdint>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <action/AnimRequest.hpp>
#include <objects/Dir8.hpp>
#include <resources/Assets.hpp>

struct PlayerPose
{
    Assets::Textures bodyTex{ Assets::Textures::Invariant };
    sf::IntRect      bodyRect{ {0,0},{0,0} };
    sf::Vector2f     bodyOff{ 0.f,0.f };

    Assets::Textures shadowTex{ Assets::Textures::Invariant };
    sf::IntRect      shadowRect{ {0,0},{0,0} };
    sf::Vector2f     shadowOff{ 0.f,0.f };
};

struct ClipDef
{
    Assets::Textures bodyTex{ Assets::Textures::Invariant };
    Assets::Textures shadowTex{ Assets::Textures::Invariant };

    int frameW{ 0 };
    int frameH{ 0 };
    int frames{ 1 };            // per direction
    float frameTime{ 0.08f };   // seconds per frame (base)
    bool loop{ true };

    sf::Vector2f bodyOff{ 0.f,0.f };
    sf::Vector2f shadowOff{ 0.f,0.f };
};

class PlayerAnimator
{
public:
    void setClip(AnimKey key, const ClipDef& def)
    {
        m_clips[(int)key] = def;
    }

    // Call once per frame.
    // - req.key chooses clip
    // - req.speed01 scales playback rate (run faster, etc.)
    // - dir chooses which of the 8 rows
    PlayerPose update(double dt, const AnimRequest& req, Dir8 dir)
    {
        const int k = (int)req.key;

        // Switch clip if needed
        if (!m_hasClip || req.key != m_currKey)
        {
            m_currKey = req.key;
            m_frame = 0;
            m_t = 0.f;
            m_hasClip = true;
        }

        const ClipDef& c = m_clips[(int)m_currKey];

        // Playback scaling: speed01=0..1-ish, but allow >1
        const float sp = (req.speed01 <= 0.01f) ? 1.0f : req.speed01;
        const float ft = (c.frameTime > 0.f) ? (c.frameTime / sp) : 0.08f;

        if (ft > 0.f)
        {
            m_t += (float)dt;
            if (m_t >= ft)
            {
                m_t -= ft;
                ++m_frame;

                if (m_frame >= c.frames)
                    m_frame = (c.loop && req.loop) ? 0 : (c.frames - 1);
            }
        }

        PlayerPose out{};
        out.bodyTex = c.bodyTex;
        out.shadowTex = c.shadowTex;

        out.bodyRect = rectFor(c, dir, m_frame);
        out.shadowRect = out.bodyRect; // shadows match indexing

        out.bodyOff = c.bodyOff;
        out.shadowOff = c.shadowOff;

        return out;
    }

    void force(AnimKey key, int frame = 0)
    {
        m_currKey = key;
        m_frame = frame;
        m_t = 0.f;
        m_hasClip = true;
    }

private:
    static sf::IntRect rectFor(const ClipDef& c, Dir8 dir, int frame)
    {
        const int row = (int)dir;    // 0..7
        const int col = frame;       // 0..frames-1
        return sf::IntRect{ { col * c.frameW, row * c.frameH}, {c.frameW, c.frameH} };
    }

private:
    std::array<ClipDef, 256> m_clips{}; // AnimKey likely small; big is fine for now

    bool   m_hasClip{ false };
    AnimKey m_currKey{ AnimKey::Idle };
    int    m_frame{ 0 };
    float  m_t{ 0.f };
};

#endif