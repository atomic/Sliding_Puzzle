#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <array>
#include <algorithm>
//#include "../slidingpuzzle/sliding_puzzle.h"

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
    bool					prepareSolution();    /// input -> solution -> ready for animate
    void					syncConfigInput();    /// sync display grid with input
    void                    activateAnimation();  /// setting up animation mode
    void					renderAnimation();    /// render each iteration
    void					render();

    void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void					handleNumberInput(sf::Keyboard::Key key);

    // helper
    void                     arrangeGrid();
    /**
     * @brief functio will takes a character and find out which position to move,
     *        and what direction
     */
    pair<int,Direction>      getIndexBoxToMove(int &zero, const char &c)
    {
        switch (c) {
        case 'D': zero += 3; return pair<int, Direction>(zero, Up);    break;
        case 'U': zero -= 3; return pair<int, Direction>(zero, Down);  break;
        case 'L': zero -= 1; return pair<int, Direction>(zero, Right); break;
        case 'R': zero += 1; return pair<int, Direction>(zero, Left);  break;
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
    string                  mSolution;

    bool                    mIsGettingInput;
    bool                    mHasSolutionReady;
    bool                    mIsAnimating;

};

#endif // GAME_H

