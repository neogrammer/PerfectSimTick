#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <utility> // for std::move
#include <optional>
#include <array>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <tilemap/Tilemap.hpp>
#include <tilemap/AnimTile.hpp>


enum class GameState
{
	Stage,
    Paused,
    Died,
    GameOver,
    Victory,
    StageSelect,
    MenuState,
    Options,
    MiniBoss,
    Boss,
    Dialog,
    Count,
    UNINITIALIZED
};

enum class StageName
{
	Intro,
    Count,
    UNINITIALIZED
};

class Game
{
    int id_{};
    std::string name_;

    sf::Sprite bgStars_;
    std::array<sf::IntRect, 75> bgRects_{ sf::IntRect{{0,0},{800,600}},  };
    double bgFrameDelay_{0.016667 };
    double bgFrameElapsed_{ 0.0 };
    size_t bgFrameIndex_{ 0 };
    sf::View playView_;
    sf::View screenView_;
    Tilemap tmap_;
    GameState currentState_{GameState::Stage};
    StageName currentStage_{ StageName::Intro };
    std::shared_ptr<AnimTile> aTile_;
    sf::Sprite sprShadow{ Assets::textures.get((int)Assets::Textures::Knight_Idle_Shadow) };
    sf::Sprite sprBody{ Assets::textures.get((int)Assets::Textures::Knight_Idle) };
public:
	
	// Default constructor
    Game(const Game& other);                  // Copy constructor
    Game(Game&& other) noexcept;              // Move constructor
    Game(int id = 0,const std::string& name = "GAME");              // Parameterized constructor

    // --- Assignment Operators ---
    Game& operator=(const Game& other);       // Copy assignment
    Game& operator=(Game&& other) noexcept;   // Move assignment

    // --- Destructor ---
    ~Game();

    // --- Getters / Setters ---
    [[nodiscard]] int getId() const noexcept { return id_; }
    [[nodiscard]] const std::string& getName() const noexcept { return name_; }
    void setId(int newId) noexcept { id_ = newId; }
    void setName(std::string newName) { name_ = std::move(newName); }

private:
    void pollWindow(sf::RenderWindow& wnd);
    void handleEvent(const sf::Event& evt);
    void input();
    void update(double dt);
    void render(sf::RenderWindow& wnd);

public:
    void run();


};



#endif