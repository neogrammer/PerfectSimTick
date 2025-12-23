
#include "Game.hpp"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <resources/Assets.hpp>

#include <misc/util.hpp>

#include "anim/init_knight_clips.hpp"
#include "anim/PlayerAnimator.hpp"

Game::~Game() = default;




Game::Game(const Game& other)
    : Game{other.id_, other.name_}
{
}

Game::Game(Game&& other) noexcept
    : Game{ other.id_, other.name_ }
{
}

Game::Game(int id, const std::string& name)
    : id_{ id }, name_{ name }
    , bgStars_{ TX(BG_Animated_Stars) }
	, tmap_{}
	, aTile_{nullptr}
{
    int y = 0;
    for (; y < 4; y++)
    {
        for (int x = 0; x < 18; x++)
        {
            bgRects_[x + (y * 18)] = sf::IntRect{ {x * 800, y * 600},{800,600} };
        }
    }
    
    for (int x =0; x < 3; x++)
    {
	    
        bgRects_[x + (y * 18)] = sf::IntRect{ {x * 800, y * 600},{800,600} };
    }

    bgStars_.setTextureRect(bgRects_[0]);
    bgStars_.setPosition({ 0.f,0.f });

   // tmap_.setTileset(Assets::Textures::Tileset_Objects_1, 4096, 64, { 32.f,32.f });
  
    int* data = new int[]{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    tmap_.setMap(data, 25 * 19, 25);
    tmap_.getTileset()->setAnimTiles(1, { 0 }, { 2 });
    tmap_.getTileset()->getAnimTile(0).setDelays({ 0.2f, 0.2f});
}

Game& Game::operator=(const Game& other)
{
    id_ = 0;
    name_ = "GAME";
    bgStars_.setTexture(TX(BG_Animated_Stars));
    int y = 0;
    for (; y < 4; y++)
    {
        for (int x = 0; x < 18; x++)
        {
            bgRects_[x + (y * 18)] = sf::IntRect{ {x * 800, y * 600},{800,600} };
        }
    }

    for (int x = 0; x < 3; x++)
    {

        bgRects_[x + (y * 18)] = sf::IntRect{ {x * 800, y * 600},{800,600} };
    }
    bgStars_.setTextureRect(bgRects_[0]);
    bgStars_.setPosition({ 0.f,0.f });
	return *this;
}

Game& Game::operator=(Game&& other) noexcept
{
    id_ = 0;
    name_ = "GAME";
    bgStars_.setTexture(TX(BG_Animated_Stars));
    int y = 0;
    for (; y < 4; y++)
    {
        for (int x = 0; x < 18; x++)
        {
            bgRects_[x + (y * 18)] = sf::IntRect{ {x * 800, y * 600},{800,600} };
        }
    }

    for (int x = 0; x < 3; x++)
    {

        bgRects_[x + (y * 18)] = sf::IntRect{ {x * 800, y * 600},{800,600} };
    }
    bgStars_.setTextureRect(bgRects_[0]);
    bgStars_.setPosition({ 0.f,0.f });
    return *this;
}


void Game::pollWindow(sf::RenderWindow& wnd)
{
    static bool canToggleScreen = { true };
    static bool isFullScreen = {false};
    while (const std::optional event = wnd.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            wnd.close();
        if (auto key = event->getIf<sf::Event::KeyReleased>())
        {
            if (key->code == sf::Keyboard::Key::Escape)
            {
                wnd.close();
            }
            if (key->code == sf::Keyboard::Key::Enter && !canToggleScreen)
            {
                canToggleScreen = true;
            }
        }

        if (canToggleScreen)
        {
            if (auto key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->alt && key->code == sf::Keyboard::Key::Enter)
                {
                    canToggleScreen = false;
                    sf::ContextSettings settings;
                    settings.antiAliasingLevel = 8;
                    if (isFullScreen)
                    {
                        wnd.create(sf::VideoMode{ {800U,600U},32U }, "SFMLengine", sf::Style::Close | sf::Style::Titlebar, sf::State::Windowed, settings);
                     
                    }
                    else
                    {
                        wnd.create(sf::VideoMode{ {800U,600U},32U }, "SFMLengine", sf::Style::None, sf::State::Fullscreen, settings);
                  
                    }
                    wnd.setVerticalSyncEnabled(true);
                    isFullScreen = !isFullScreen;
                }
            }
        }

        handleEvent(event.value());
    }
}

void Game::handleEvent(const sf::Event& evt)
{
}

void Game::input()
{
}

void Game::update(double dt)
{
   

    bgFrameElapsed_ += dt;
    

    if (bgFrameElapsed_ >= bgFrameDelay_)
    {
        bgFrameElapsed_ = 0.f;
        ++bgFrameIndex_ %= 75;
       
            bgStars_.setTextureRect(bgRects_[bgFrameIndex_]);
    }
   
    tmap_.getTileset()->update(dt);
    
}

void Game::render(sf::RenderWindow& wnd)
{   

    // Clear the frame to get ready for new drawing
    wnd.clear(sf::Color::Blue);


    wnd.setView(screenView_);
    wnd.draw(bgStars_);


    wnd.setView(playView_);


    // draw BG layers

    // draw ground layer

    // draw tilemap and game objects together from front to back including player
    tmap_.render(wnd);
    wnd.draw(sprShadow);
    wnd.draw(sprBody);

    // draw foreground layer

    // draw UI

    // draw overlay (pause text, dim screen, things like this)

    wnd.setView(screenView_);

    // ImGui if using


    wnd.setView(playView_);

    wnd.display();

    
}

void Game::run()
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;

	sf::RenderWindow wnd{ sf::VideoMode{{800U,600U},32U}, "SFMLengine", sf::Style::Close | sf::Style::Titlebar, sf::State::Windowed, settings };
    wnd.setVerticalSyncEnabled(true);
    sf::Clock frameTimer{};
    sf::Clock fpsCounterTimer{};

    screenView_ = wnd.getDefaultView();
    playView_ = wnd.getDefaultView();

 
    int64_t accumulator{0};
    constexpr double fps_60_millis{ (1000.0 * (1.0 / 60.0)) };
    constexpr int64_t fps_60_micros{ static_cast<int64_t>(1000.0 * fps_60_millis) };

    constexpr double fps_60_double{ 1.0 / 60.0 };
 
    PlayerAnimator anim;
    initKnightClips(anim);

    AnimRequest req{};
    req.key = AnimKey::Attack;
    req.loop = true;
    req.priority = 0;
    req.speed01 = 1.0f;

    Dir8 facing = Dir8::S;
   

    // pick a starting world/screen position for now
    sf::Vector2f playerPos{ 600.f, 350.f };
    
    Assets::Textures curBody = Assets::Textures::Knight_Attack;
    Assets::Textures curShadow = Assets::Textures::Knight_Attack_Shadow;
    while (wnd.isOpen())
    {
    	pollWindow(wnd);
        input();

        accumulator += std::min<int64_t>(frameTimer.restart().asMicroseconds(), 50000);
        static int fpsCounter{ 0 };
        
        while (accumulator >= fps_60_micros)
        {
        	fpsCounter++;
            
        	update(fps_60_double);
            PlayerPose pose = anim.update(fps_60_double, req, facing);

            if (pose.bodyTex != curBody) {
                sprBody.setTexture(Assets::textures.get((int)pose.bodyTex), true);
                curBody = pose.bodyTex;
            }
            sprBody.setTextureRect(pose.bodyRect);
            sprBody.setPosition(playerPos + pose.bodyOff);

           
            if (pose.shadowTex != curShadow) {
                sprShadow.setTexture(Assets::textures.get((int)pose.shadowTex), true);
                curShadow = pose.shadowTex;
            }
            sprShadow.setTextureRect(pose.shadowRect);
            sprShadow.setPosition(playerPos + pose.shadowOff);
        
            accumulator -= fps_60_micros;
        }
     
        render(wnd);

    }

}

