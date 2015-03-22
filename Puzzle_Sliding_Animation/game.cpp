#include "game.h"
#include "yekun_solution/sliding_puzzle.h"
#include "alex_solution/anode.h"
#include "algol/solvability.h"

const sf::Vector2f Game::SCREENSIZE = sf::Vector2f(1044,640);
const sf::Vector2f Game::GridPos = sf::Vector2f(424,20);
const int          Game::GDim   = 200;
const int          Game::GSIZE  = 600;
const int Game::FrameThickness = 5;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);
const int Game::AnimSpeed = 200;

/**
 * @brief Constructor to set the size of windows
 *        and initialize objects
 */
Game::Game()
    : mWindow(sf::VideoMode(SCREENSIZE.x, SCREENSIZE.y), "SFML Application", sf::Style::Close),
      mFrameStepDone(0), mIsAnimating(false), mIndexToAnimate(-1), mIndexDirection(Up),
      mDelayTime(50), mDelayPassed(0), mStrInput(""),
      mConfiguration(new int*[3]),
      mYekunWay(true),
      mIsGettingInput(false), mHasSolutionReady(false)
{
    // get resources
    mFontGui.loadFromFile("../Sliding_Puzzle/Resources/proximanova.ttf");
    mTextureBox.loadFromFile("../Sliding_Puzzle/Resources/mgrid_600.png",
                             sf::IntRect(0,0,600,600));// start at from the pic, grab 32x32

    mSpriteBoxes.push_back(sf::Sprite()); // sprite for empty box, we never draw this

    // Fill vector of sprite with numbered boxes
    for (int i = 0; i < 8; ++i) {
        mSpriteBoxes.push_back(sf::Sprite());
        mSpriteBoxes[i+1].setTexture(mTextureBox);
        mSpriteBoxes[i+1].setTextureRect(sf::IntRect( (i % 3)*GDim, (i / 3)*GDim, GDim, 200));
    }

    int spacing = 20; int box_w(320), box_h = 50;
    // Set the configuration for INPUT TEXT BOX
    mBoxCombInput.setSize(sf::Vector2f(box_w,box_h));
    mBoxCombInput.setFillColor(sf::Color::Cyan);        mBoxCombInput.setOutlineColor(sf::Color::Red);
    mBoxCombInput.setPosition(sf::Vector2f(30, spacing));

    // Set the configuration for SOLUTION TEXT BOX
    mBoxSolution.setSize(sf::Vector2f(box_w,box_h));
    mBoxSolution.setFillColor(sf::Color::Yellow);
    mBoxSolution.setPosition(sf::Vector2f(30,box_h + spacing*2));

    // set the configuration for PUZZLE_FRAME BOX
    mBoxPuzzleFrame.setSize(sf::Vector2f(GSIZE + FrameThickness*2,GSIZE + FrameThickness*2));
    mBoxPuzzleFrame.setPosition(GridPos.x - FrameThickness, GridPos.y - FrameThickness);
    mBoxPuzzleFrame.setFillColor(sf::Color(214,214,238));
    mBoxPuzzleFrame.setOutlineColor(sf::Color::Red);
    mBoxPuzzleFrame.setOutlineThickness(FrameThickness);


    // set the configuration for INPUT TEXT DISPLAYS
    mTextInput.setFont(mFontGui);     mTextInput.setString(" your combination ");
    mTextInput.setPosition(32,spacing);    mTextInput.setScale(0.9,0.9);

    // set the configuration for SOLUTION TEXT DISPLAYS
    mTextSolution.setFont(mFontGui);  mTextSolution.setString("solution");
    mTextSolution.setPosition(32,box_h + spacing*2);
    mTextSolution.setScale(0.5,0.5); mTextSolution.setColor(sf::Color::Blue);

    // set the configuration for DIRECTION TEXT DISPLAYS
    mTextDirection.setFont(mFontGui); mTextDirection.setString(
                "space : Input combination\nBackSpace : Reset\nr : Randomize\nEnter : get solution\n/ : animate");
    mTextDirection.setPosition(23,200);
    mTextInput.setColor(sf::Color::Red); mTextDirection.setScale(0.9, 0.9);

    // set config for Yekun,Alex notification text
    mTextYekun.setFont(mFontGui);     mTextYekun.setString("Yekun");
    mTextYekun.setPosition(22,164);   mTextYekun.setScale(0.7, 0.7); mTextYekun.setColor(sf::Color::Red);
    mTextYekun.setStyle(sf::Text::Bold);
    mTextAlex.setFont(mFontGui);     mTextAlex.setString("Alex");
    mTextAlex.setPosition(110,164);   mTextAlex.setScale(0.5, 0.5);   mTextAlex.setColor(sf::Color::Magenta);


    // initialize space for my int-configuration of the puzzle ground
    mConfiguration[0] = new int[3] {1,2,3};
    mConfiguration[1] = new int[3] {4,5,6};
    mConfiguration[2] = new int[3] {7,8,0};

    arrangeGrid();
}

/**
 * @brief a function to start the whole game mode
 */
void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update(TimePerFrame); // information
        }
        render(); // graphics
    }
}

/**
 * @brief Function to reset all items needed to animate, or inputs
 * @param what
 * @return none
 */
void Game::reset(bool clearInput, bool clearSolution)
{

    if (clearInput)    { mStrInput.clear(); mTextInput.setString(" --cleared-- ");    }
    if (clearSolution) { mSolution.clear(); mTextSolution.setString(" --cleared-- "); mHasSolutionReady = false ;}

    mZeroIndexes.clear();
    mMovingSequence.clear();
    mTranslateBox = sf::Transform::Identity; mFrameStepDone = 0; //mStep,aStep handled by animation
    mBoxPuzzleFrame.setOutlineColor(sf::Color::Blue); mIsResetingDone = false; mDelayPassed = 0;
}

/**
 * @brief receives events and
 *          and acts accordingly
 */
void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            if(mIsGettingInput)
                handleNumberInput(event.key.code);
            else handlePlayerInput(event.key.code, true);
            break;

        case sf::Event::KeyReleased:
            if(!mIsGettingInput && !mIsAnimating) // Prevent doing crazy stuffs when getting input
                handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        default:
            break;
        }
    }
}

/**
 * @brief Based on the key inputs, do actions
 * @param key inputted, whether key is pressed or released
 */
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::Escape)                        mWindow.close();
    else if (key == sf::Keyboard::BackSpace && isPressed)   reset();
    else if (key == sf::Keyboard::Space     && isPressed)   mIsGettingInput = true;
    else if (key == sf::Keyboard::R         && isPressed)   getRandomInput();
    else if (key == sf::Keyboard::Tab       && isPressed)   {
        mYekunWay = !mYekunWay;
        mTextAlex .setStyle(mYekunWay ? sf::Text::Regular : sf::Text::Bold);
        mTextAlex .setColor(mYekunWay ? sf::Color::Magenta: sf::Color::Red);
        mTextAlex .setScale(mYekunWay ? 0.5 : 0.8, mYekunWay ? 0.5 : 0.8);
        mTextYekun.setStyle(mYekunWay ? sf::Text::Bold    : sf::Text::Regular);
        mTextYekun.setColor(mYekunWay ? sf::Color::Red    : sf::Color::Magenta);
        mTextYekun.setScale(mYekunWay ? 0.8 : 0.5, mYekunWay ? 0.8 : 0.5);
    }
    else if (key == sf::Keyboard::Slash && isPressed)   {
        if(mHasSolutionReady)  {
            activateAnimation();
            mBoxPuzzleFrame.setOutlineColor(sf::Color::Green);
        }
    }
}

/**
 * @brief Based on the key inputs, only register numbers
 * @param key inputted, whether key is pressed or released
 */
void Game::handleNumberInput(sf::Keyboard::Key key)
{
    switch (key) {
    case sf::Keyboard::Num0: mStrInput += to_string(0); break;
    case sf::Keyboard::Num1: mStrInput += to_string(1); break;
    case sf::Keyboard::Num2: mStrInput += to_string(2); break;
    case sf::Keyboard::Num3: mStrInput += to_string(3); break;
    case sf::Keyboard::Num4: mStrInput += to_string(4); break;
    case sf::Keyboard::Num5: mStrInput += to_string(5); break;
    case sf::Keyboard::Num6: mStrInput += to_string(6); break;
    case sf::Keyboard::Num7: mStrInput += to_string(7); break;
    case sf::Keyboard::Num8: mStrInput += to_string(8); break;
    case sf::Keyboard::Num9: mStrInput += to_string(9); break;
    case sf::Keyboard::Space: mIsGettingInput = false;  break;
    case sf::Keyboard::Return:
        mHasSolutionReady = prepareSolution();
        mIsGettingInput   = mHasSolutionReady? false : true; // if no solution, don't exit input mode
        if(mHasSolutionReady) syncConfigInput(); // solution is ready
        else {
            // print message about no possible solution
        }
        break;
    case sf::Keyboard::BackSpace: mStrInput.clear();    break;
    default:
        break;
    }
}

/**
 * @brief Function will be called when user press r,
 *        Then, fill the input box with randomly generated combination
 */
void Game::getRandomInput()
{
    srand(time(NULL));
    Alex::board b(3);
    mStrInput = b.randomize();
    mTextInput.setString(mStrInput);
}

/**
 * @brief handle where to display all the grids
 */
void Game::arrangeGrid()
{
    /// from the 2D array in mConfiguration,
    /// plot the boxes side by side with starting position at GridPos
    ///  o ->  j/x
    ///  ↓
    ///  i/y

    int i, j;
    for(int N = 0; N < 9; N++) {
        i = N / 3; j = N % 3;
        if(mConfiguration[i][j] != 0)
            mSpriteBoxes[mConfiguration[i][j]].setPosition(GridPos.x + j*GDim,
                                                       GridPos.y + i*GDim);
    }
}

/// Sync input with display grid
void Game::syncConfigInput()
{
    int i = 0;
    for(auto c : mStrInput) {
        mConfiguration[i/3][i%3] = atoi(&c);
        i++;
    }
}


/**
 * @brief Will checks whether there exists solution yet
 */
bool Game::prepareSolution()
{
    string copyOfInput = mStrInput.substr();
    sort(copyOfInput.begin(), copyOfInput.end());
    // checks for solution existence
    if(mStrInput.size() != 9)             return false;
    if(copyOfInput != "012345678")        return false; // see algol for way to check
    if(!Algol::isSolvable(mStrInput))     return false; // if not solvable, return false
    // up to this point, input is valid
    syncConfigInput();
    arrangeGrid();

    if(mYekunWay) {
        Yekun::Sliding_Puzzle solveThis(mStrInput.c_str());
        Yekun::Node solution = solveThis.getSolution();
        mSolution = solution.order;
        mTextSolution.setString(solution.order + string(" (") + to_string(solution.step) + string(")"));
    } else {
        using namespace Alex;
        Node n(board(3, mStrInput.c_str()));
        n.solve();
        mSolution = n.solution();
        mTextSolution.setString(mSolution + string(" (") + to_string(n.steps()) + string(")"));
    }
    return true;
}

/**
 * @brief update informations to next thread
 */
void Game::update(sf::Time elapsedTime)
{
    // Color the input text box outline
    mBoxCombInput.setOutlineThickness(mIsGettingInput ? 3 : 0);
    if(mIsGettingInput) mTextInput.setString(mStrInput);

    // do sliding animation
    if(mIsAnimating && mFrameStepDone < GDim) {
        prepareAnimation(elapsedTime);
    } else if(mIsAnimating && !isSequenceComplete()) {
        proceedSequence(); // update mFramestepdone, and other stuffs
        updateNextGrid(); // last grid does not get updated
        mFrameStepDone = 0;
        mStep++; aStep++;
    } else if(mIsAnimating && isSequenceComplete()) {
        // TODO: clear stuffs here
        reset(false);
        mIsAnimating = false;
        mBoxPuzzleFrame.setOutlineColor(sf::Color::Red);
    }

    if(!mIsResetingDone) {
        if(mDelayPassed < mDelayTime)
            mDelayPassed++;
        else { // turn off delay
            mIsResetingDone = true; mDelayPassed = 0;
            mBoxPuzzleFrame.setOutlineColor(sf::Color::Red);
        }
    }
}


/**
 * NOTE : This should be run first before every animation
 * @brief Check for sequence to animate
 */
void Game::proceedSequence()
{
    // don't touch this anymore
    if(aStep < mSolution.length()) {
        mIndexToAnimate = mMovingSequence[aStep].first;
        mIndexDirection = mMovingSequence[aStep].second;
    }
}

/**
  * @brief Update next grid, this should run after proceedSequence
  *
  */
void Game::updateNextGrid()
{
    int prev_zero;
    int next_zero;

    prev_zero = mZeroIndexes[mStep];
    next_zero = mZeroIndexes[mStep + 1]; // BUG : THIS LINE, swap or animate, not both
    swap(mConfiguration[prev_zero/3][prev_zero%3],
            mConfiguration[next_zero/3][next_zero%3]);
    arrangeGrid();

    // then we reset to their correct position
    mTranslateBox = sf::Transform::Identity; // reset the translation matrix
}

/**
 * @pre   hasSolution is true, mSolution contains the order of solution
 * @brief activate and ready the animation sequence
 */
void Game::activateAnimation()
{
    // find initial pos of 0 in configuration
    int zero;
    for(int n = 0; n < 9; n++) {
        if(mConfiguration[n/3][n%3] == 0) { zero = n; break; }
    }
    mZeroIndexes.push_back(zero);
    // for the strings of solution, populate the vector mMovingSequence with the slides
    for(auto N : mSolution) {
        mMovingSequence.push_back(getIndexBoxToMove(zero, N)); // zero will updates inside
        mZeroIndexes.push_back(zero); // we store twin series later making swapping easier
    }


    // then start animation, and keep track of it.
    // start aStep ahead of mStep
    mIndexToAnimate = mMovingSequence[0].first;
    mIndexDirection = mMovingSequence[0].second;
    aStep = 1; // aStep is used to keep track of animation logic, ahead of mStep

    mStep = 0; // mStep is used to keep track of swapping logic
    mIsAnimating = true; // this should signal next update to start sequence animation
}

/**
 * This is called every frame (depending on the time)
 * @brief a function to render the animation of one box, and draw the rest static
 */
void Game::prepareAnimation(sf::Time elapsedTime)
{
    float frame_delta = AnimSpeed*elapsedTime.asSeconds();
    mFrameStepDone += frame_delta;
    // find out direction of animation
    switch (mIndexDirection) {
    case Up:   mTranslateBox.translate(0, -frame_delta);   break;
    case Down: mTranslateBox.translate(0,  frame_delta);   break;
    case Left: mTranslateBox.translate(-frame_delta, 0);   break;
    case Right:mTranslateBox.translate( frame_delta, 0);   break;
    default:
        break;
    }
}

/**
 * @brief a function to draw objects
 */
void Game::render()
{
    mWindow.clear();
    mWindow.draw(mBoxCombInput);
    mWindow.draw(mBoxSolution);

    mWindow.draw(mTextInput);
    mWindow.draw(mTextSolution);
    mWindow.draw(mTextDirection);
    mWindow.draw(mTextYekun);
    mWindow.draw(mTextAlex);

    mWindow.draw(mBoxPuzzleFrame);


    if (!mIsAnimating) { // the animation is handled on update()->renderAnimation
        for(auto box : mSpriteBoxes)
            mWindow.draw(box); // if not animating, just draw static boxes
    } else {
        int value_animate = mConfiguration[mIndexToAnimate/3][mIndexToAnimate%3];
        for (int n = 0; n < 9; ++n) {
            if(n != mIndexToAnimate)
                mWindow.draw(mSpriteBoxes[mConfiguration[n/3][n%3]]);
        }
        mWindow.draw(mSpriteBoxes[value_animate], mTranslateBox);
    }

    mWindow.display();
}

/// some notes
/// link for references : https://n-puzzle-solver.appspot.com/
