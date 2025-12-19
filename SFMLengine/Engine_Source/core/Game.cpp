
#include "Game.hpp"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <resources/Assets.hpp>

#include <misc/util.hpp>

Game::~Game() = default;




Game::Game(const Game& other)
    : Game{}
{
}

Game::Game(Game&& other) noexcept
    : Game{}
{
}

Game::Game(int id, const std::string& name)
    : id_{ id }, name_{ name }
    , bgStars_{ TX(BG_Animated_Stars) }
	, tmap_{}
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
		-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    tmap_.setMap(data, 25 * 19, 25);
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

    
}

void Game::render(sf::RenderWindow& wnd)
{
    //static bool firstRun{ true };
    //while (firstRun)
    //{
    //    wnd.requestFocus();
    //    if (wnd.hasFocus())
    //    {
    //        firstRun = false;
    //    }
    //}
    

    // Clear the frame to get ready for new drawing
    wnd.clear(sf::Color::Blue);


    wnd.setView(screenView_);
    wnd.draw(bgStars_);


    wnd.setView(playView_);


    // draw BG layers
    //starsBG.render(wnd);

    // draw ground layer

    // draw tilemap and game objects together from front to back including player
    tmap_.render(wnd);


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
            accumulator -= fps_60_micros;
        }
        if (fpsCounterTimer.getElapsedTime().asSeconds() >= 1)
        {
            if (fpsCounter == 60)
            {
                
                update(static_cast<double>(accumulator));
                fpsCounter++;
                accumulator = 0i64;
            }
            fpsCounterTimer.restart();
            std::cout << "FPS: " << (fpsCounter - 1) << "\n";
            fpsCounter = 0;
        }
        render(wnd);

    }

}

