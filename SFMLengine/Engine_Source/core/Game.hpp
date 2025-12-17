#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <utility> // for std::move
#include <optional>

#include <SFML/Graphics/RenderWindow.hpp>

class Game
{
    int id_{};
    std::string name_;

public:
  
    Game();                                      // Default constructor
    Game(const Game& other);                  // Copy constructor
    Game(Game&& other) noexcept;              // Move constructor
    Game(int id,const std::string& name);              // Parameterized constructor

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