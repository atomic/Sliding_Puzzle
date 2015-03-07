#include "game.h"

const sf::Vector2f Game::GridPos = sf::Vector2f(280,20);
const int Game::FrameThickness = 5;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

/**
 * @brief Constructor to set the size of windows
 *        and initialize objects
 */
Game::Game()
    : mWindow(sf::VideoMode(450,200), "SFML Application", sf::Style::Close),
      mStepDone(0), mStrInput(""),
      mConfiguration(new int*[3]), mIsGettingInput(false), mIsAnimating(false)
{
    // get resources
    mFontGui.loadFromFile("../Sliding_Puzzle/Resources/proximanova.ttf");
    mTextureBox.loadFromFile("../Sliding_Puzzle/Resources/mgrid.png",
                             sf::IntRect(0,0,150,150));// start at from the pic, grab 32x32

    mSpriteBoxes.push_back(sf::Sprite()); // sprite for empty box, we never draw this
    // Fill vector of sprite with numbered boxes
    for (int i = 0; i < 8; ++i) {
        mSpriteBoxes.push_back(sf::Sprite());
        mSpriteBoxes[i+1].setTexture(mTextureBox);
        mSpriteBoxes[i+1].setTextureRect(sf::IntRect( (i%3)*50, (i/3)*50, 50, 50));
    }

    // Set the configuration for input text box
    mBoxCombInput.setSize(sf::Vector2f(250,35));
    mBoxCombInput.setFillColor(sf::Color::Cyan); mBoxCombInput.setOutlineColor(sf::Color::Red);
    mBoxCombInput.setPosition(sf::Vector2f(10,10));
    // Set the configuration for solution text box
    mBoxSolution.setSize(sf::Vector2f(250,35));
    mBoxSolution.setFillColor(sf::Color::Yellow);
    mBoxSolution.setPosition(sf::Vector2f(10,50));
    // set the configuration for frame box
    mBoxPuzzleFrame.setSize(sf::Vector2f(150 + FrameThickness*2,150 + FrameThickness*2));
    mBoxPuzzleFrame.setPosition(GridPos.x - FrameThickness, GridPos.y - FrameThickness);
//    mBoxPuzzleFrame.setPosition(GridPos.x - FrameThickness/2, GridPos.y - FrameThickness/2);
    mBoxPuzzleFrame.setFillColor(sf::Color(214,214,238));
    mBoxPuzzleFrame.setOutlineColor(sf::Color::Red);
    mBoxPuzzleFrame.setOutlineThickness(FrameThickness);


    // set the configuration for text displays
    mTextInput.setFont(mFontGui);     mTextInput.setString(" your combination ");
    mTextInput.setPosition(12,10);    mTextInput.setScale(0.9,0.9);

    mTextSolution.setFont(mFontGui);  mTextSolution.setString("solution");
    mTextSolution.setPosition(12,50); mTextSolution.setScale(0.9,0.9); mTextSolution.setColor(sf::Color::Blue);

    mTextDirection.setFont(mFontGui); mTextDirection.setString("space : change combination\nenter : get solution\n/ : animate");
    mTextDirection.setPosition(12,90);
    mTextInput.setColor(sf::Color::Red); mTextDirection.setScale(0.5, 0.5);


    // initialize space for my int-configuration of the puzzle ground
    mConfiguration[0] = new int[3] {8,1,2};
    mConfiguration[1] = new int[3] {3,4,5};
    mConfiguration[2] = new int[3] {6,7,0};

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
            update(TimePerFrame);
        }
        render();
    }
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
            if(!mIsGettingInput)       // Prevent doing crazy stuffs when getting input
                handlePlayerInput(event.key.code, false);
            break;

        case sf::Event::Closed:
            mWindow.close();
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
    if (key == sf::Keyboard::Escape)
        mWindow.close();
    else if (key == sf::Keyboard::BackSpace)
        mWindow.close();
    else if (key == sf::Keyboard::Space && isPressed)
        mIsGettingInput = true;
    else if (key == sf::Keyboard::Return)
        mWindow.close();
    else if (key == sf::Keyboard::Slash && isPressed)
        mIsAnimating = !mIsAnimating;
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
    case sf::Keyboard::Space: mIsGettingInput = false; break;
    case sf::Keyboard::Return: /* to be implemented */break;
    default:
        break;
    }
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
    // Loop the whole mConfiguration
    for(int N = 0; N < 9; N++) {
        i = N / 3; j = N % 3;
        if(mConfiguration[i][j] != 0)
            mSpriteBoxes[mConfiguration[i][j]].setPosition(GridPos.x + j*50,
                                                       GridPos.y + i*50);
    }
}


/**
 * @brief update informations to next thread
 */
void Game::update(sf::Time elapsedTime)
{
    mBoxCombInput.setOutlineThickness(mIsGettingInput ? 3 : 0);
    if(mIsGettingInput) mTextInput.setString(mStrInput);

    // do sliding animation
    mStepDone += 50*elapsedTime.asSeconds();
    if(mIsAnimating && mStepDone < 50)
        mTranslateBox.translate(0, 50*elapsedTime.asSeconds());
    else {
        mIsAnimating = false;
        mTranslateBox = sf::Transform::Identity;
        mStepDone = 0; // reset here? hmm
        // if not animating
        arrangeGrid(); // might be too much process to do this every loop
                       // move this to other part after calculation perhaps
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

    mWindow.draw(mBoxPuzzleFrame);
    if(mIsAnimating)
        renderAnimation();
    else {
        for(auto box : mSpriteBoxes)
            mWindow.draw(box, mTranslateBox);
    }
    mWindow.draw(mTextDirection);
    mWindow.display();
}

/**
 * @brief a function to render the animation of one box, and draw the rest static
 */
void Game::renderAnimation()
{
    // find from the first string, which box to animate
    // draw everything, except that box, then draw that box with translation

    // test animate one box first (move 5 down)
    for (int n = 0; n < 9; ++n) {
        if(mConfiguration[n / 3][n % 3] != 5)
            mWindow.draw(mSpriteBoxes[n]);
    }
    mWindow.draw(mSpriteBoxes[5], mTranslateBox);
}


/**
 * @brief Will checks whether there exists solution yet and then activate animation
 */
void Game::activateAnimation()
{
    // checks for solution existence
    // for the strings of solution, populate the vector mMovingSequence with the slides
    // then start animation, and keep track of it.
}


/// some notes
/// link for references : https://n-puzzle-solver.appspot.com/
