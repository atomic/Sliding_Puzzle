#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

enum Direction {
    Up = -3, Down = 3, Left = -1, Right = 1
};

using namespace std;

class Game : private sf::NonCopyable
{
public:
    Game();
    void					run();
    void					reset(bool clearInput = true, bool clearSolution = true);

private:
    void					processEvents();
    void					update(sf::Time elapsedTime);
    bool					prepareSolution();    /// input -> solution -> ready for animate
    void					syncConfigInput();    /// sync display grid with input
    void                    activateAnimation();  /// setting up animation mode
    void					prepareAnimation(sf::Time elapsedTime);    /// render each iteration
    void					render();

    void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void					handleNumberInput(sf::Keyboard::Key key);

    // helper
    void                     arrangeGrid();
    bool                     isSequenceComplete() { return mStep == mSolution.length(); };
    void                     proceedSequence();       /// prepare for next animation sequence
    void                     updateNextGrid();  /// intersession between one animation to another
    void                     intSwap(int &A, int &B) { int temp = B; B = A; A = temp; }
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
        } throw logic_error("ERROR: No index to move");
    };

private:
    static const sf::Vector2f SCREENSIZE;
    static const int          GDim;
    static const int          GSIZE;
    sf::RenderWindow		  mWindow;

    // Resources
    sf::Font                  mFontGui;
    sf::Texture               mTextureBox;

    // my sprite
    vector<sf::Sprite>        mSpriteBoxes;

    // Shapes
    static const sf::Vector2f GridPos;
    static const int          FrameThickness;
    sf::RectangleShape        mBoxCombInput;
    sf::RectangleShape        mBoxSolution;
    sf::RectangleShape        mBoxPuzzleFrame;

    // direction notices does not need boxes
    sf::Text                  mTextInput;
    sf::Text                  mTextSolution;
    sf::Text                  mTextDirection;
    sf::Text                  mTextYekun;
    sf::Text                  mTextAlex;

    // Animation
    static const sf::Time	  TimePerFrame;
    static const int          AnimSpeed;
    sf::Transform             mTranslateBox;
    float                     mFrameStepDone;     // For one frame
    bool                      mIsAnimating;
    size_t                    mStep;     // For iteration swapping
    size_t                    aStep;     // For animation, ahead of mStep

    vector<pair<int,Direction>> mMovingSequence;
    vector<int>               mZeroIndexes; // just to make swapping easier
    int                       mIndexToAnimate;
    Direction                 mIndexDirection;

    // Display
    int                       mDelayTime; // to make the delay for some color changes(number in terms of frames?)
    int                       mDelayPassed; // to make the delay for some color changes
    bool                      mIsResetingDone;



    // LOGIC Part

    string                    mStrInput;
    int **                    mConfiguration;
    string                    mSolution;
    bool                      mYekunWay; // 2 different approaches

    bool                      mIsGettingInput;
    bool                      mHasSolutionReady;

};

#endif // GAME_H
/// Notes:
/// 1.Unvoled sequences
///  470586312 (28 steps)
/// 2. Performance Comparison
///  427168035 (Yekun : 26 steps in ~4 seconds, 26 steps in ~7 seconds)
