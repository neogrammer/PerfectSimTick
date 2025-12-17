#include "Game.hpp"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

Game::Game() = default;

Game::~Game() = default;


Game::Game(const Game& other)
{
}

Game::Game(Game&& other) noexcept
{
}

Game::Game(int id, const std::string& name)
{
}

Game& Game::operator=(const Game& other)
{
	return *this;
}

Game& Game::operator=(Game&& other) noexcept
{
	return *this;
}


void Game::pollWindow(sf::RenderWindow& wnd)
{
    while (const std::optional event = wnd.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            wnd.close();

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

    // draw BG layers

    // draw ground layer

    // draw tilemap and game objects together from front to back including player

    // draw foreground layer

    // draw UI

    // draw overlay (pause text, dim screen, things like this)

    // ImGui if using

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
 
    int64_t accumulator{0};
    constexpr double fps_60_millis{ (1000.0 * (1.0 / 60.0)) };
    constexpr int64_t fps_60_micros{ static_cast<int64_t>(1000.0 * fps_60_millis) };

    constexpr double fps_60_double{ 1.0 / 60.0 };
 
    while (wnd.isOpen())
    {
    	pollWindow(wnd);
        input();

        accumulator += frameTimer.restart().asMicroseconds();

        
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

