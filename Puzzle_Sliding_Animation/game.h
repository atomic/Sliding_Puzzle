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
    void					update(sf::Time elapsedTime);
    void					render();
    void					renderAnimation();

    void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void					handleNumberInput(sf::Keyboard::Key key);

    // helper
    void                    arrangeGrid();

private:
    sf::RenderWindow		mWindow;

    // Resources
    sf::Font                mFontGui;
    sf::Texture             mTextureBox;

    // my sprite
    std::vector<sf::Sprite> mSpriteBoxes;

    // Shapes
    static const int        FrameThickness;
    sf::RectangleShape      mBoxCombInput;
    sf::RectangleShape      mBoxSolution;
    sf::RectangleShape      mBoxPuzzleFrame;

    // direction notices does not need boxes
    sf::Text                mTextInput;
    sf::Text                mTextSolution;
    sf::Text                mTextDirection;

    // Animation
    static const sf::Time	TimePerFrame;
    sf::Transform           mTranslateBox;
    float                   mStepDone;


    // LOGIC Part
    static const sf::Vector2f GridPos;

    std::string             mStrInput;
    int **                  mConfiguration;

    bool                    mIsGettingInput;
    bool                    mIsAnimating;

};

#endif // GAME_H

