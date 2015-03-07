#include "game.h"

const sf::Vector2f Game::GridPos = sf::Vector2f(300,50);

/**
 * @brief Constructor to set the size of windows
 *        and initialize objects
 */
Game::Game()
    : mWindow(sf::VideoMode(800,500), "SFML Application", sf::Style::Close),
      mIsAnimating(false), mIsGettingInput(false), mStrInput(""),
      mConfiguration(new int*[3])
{
    // get resources
    mFontGui.loadFromFile("../Sliding_Puzzle/Resources/proximanova.ttf");
    mTextureBox.loadFromFile("../Sliding_Puzzle/Resources/mgrid.png",
                             sf::IntRect(0,0,150,150));// start at from the pic, grab 32x32

    mSpriteBoxes.push_back(sf::Sprite()); // sprite for empty box
    mSpriteBoxes[0].setTexture(mTextureBox);
    mSpriteBoxes[0].setTextureRect(sf::IntRect( 2*50, 2*50, 50, 50));
    // let's populate our vector
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

    // set the configuration for text displays
    mTextInput.setFont(mFontGui);     mTextInput.setString(" your combination ");
    mTextInput.setPosition(12,10);    mTextInput.setScale(0.9,0.9);

    mTextSolution.setFont(mFontGui);  mTextSolution.setString("solution");
    mTextSolution.setPosition(12,50); mTextSolution.setScale(0.9,0.9); mTextSolution.setColor(sf::Color::Blue);

    mTextDirection.setFont(mFontGui); mTextDirection.setString("space : change combination\nenter : get solution\n/ : animate");
    mTextInput.setColor(sf::Color::Red);


    // initialize space for my int-configuration of the puzzle ground
    mConfiguration[0] = new int[3] {0,1,2};
    mConfiguration[1] = new int[3] {3,4,5};
    mConfiguration[2] = new int[3] {6,7,8};

}

/**
 * @brief a function to start the whole game mode
 */
void Game::run()
{
    while (mWindow.isOpen())
    {
        processEvents();
        update();
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
    else if (key == sf::Keyboard::Slash)
        mWindow.close();
}

/**
 * @brief Based on the key inputs, only register numbers
 * @param key inputted, whether key is pressed or released
 */
void Game::handleNumberInput(sf::Keyboard::Key key)
{
    using namespace std;
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
void Game::displayGrid()
{
}

/**
 * @brief update informations to next thread
 */
void Game::update()
{
    mBoxCombInput.setOutlineThickness(mIsGettingInput ? 3 : 0);
    if(mIsGettingInput) mTextInput.setString(mStrInput);
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

    mWindow.draw(mSpriteBoxes[0]);
//    mWindow.draw(mTextDirection);
    mWindow.display();
}

