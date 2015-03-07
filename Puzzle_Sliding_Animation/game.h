#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <array>

enum Direction {
    Up, Down, Left, Right
};

using namespace std;

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
    void					activateAnimation();

    void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void					handleNumberInput(sf::Keyboard::Key key);

    // helper
    void                     arrangeGrid();
    /**
     * @brief functio will takes a character and find out which position to move,
     *        and what direction
     */
    pair<int,Direction>      getIndexBoxToMove(const char &c)
    {
        int zero;
        // find pos of 0 in configuration
        for(int n = 0; n < 9; n++) {
            if(mConfiguration[n/3][n%3] == 0) { zero = n; break; }
        }

        switch (c) {
        case 'D': return pair<int, Direction>(zero + 3, Up);  break;
        case 'U': return pair<int, Direction>(zero - 3, Down);  break;
        case 'L': return pair<int, Direction>(zero - 1, Right);  break;
        case 'R': return pair<int, Direction>(zero + 1, Left);  break;
        default:
            break;
        }
    };

private:
    sf::RenderWindow		mWindow;

    // Resources
    sf::Font                mFontGui;
    sf::Texture             mTextureBox;

    // my sprite
    vector<sf::Sprite>      mSpriteBoxes;

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

    vector<pair<int,Direction>> mMovingSequence;
    int                         mCurrentMovingIndex;



    // LOGIC Part
    static const sf::Vector2f GridPos;

    string                  mStrInput;
    int **                  mConfiguration;

    bool                    mIsGettingInput;
    bool                    mIsAnimating;

};

#endif // GAME_H

