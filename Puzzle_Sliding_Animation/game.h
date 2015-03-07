#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <array>

class Game : private sf::NonCopyable
{
public:
    Game();
    void					run();

private:
    void					processEvents();
    void					update();
    void					render();

    void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void					handleNumberInput(sf::Keyboard::Key key);


private:
    sf::RenderWindow		mWindow;

    // Resources
    sf::Font                mFontGui;
    sf::Texture             mTextureBox;

    // my sprite
    std::vector<sf::Sprite> mSpriteBoxes;

    // Shapes
    sf::RectangleShape      mBoxCombInput;
    sf::RectangleShape      mBoxSolution;

    // direction notices does not need boxes
    sf::Text                mTextInput;
    sf::Text                mTextSolution;
    sf::Text                mTextDirection;


    // LOGIC Part
    std::string             mStrInput;
    int **                  mConfiguration;

    bool                    mIsGettingInput;
    bool                    mIsAnimating;

};

#endif // GAME_H

