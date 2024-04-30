#include "game.hpp"

int main()
{
    srand((unsigned) time(NULL));
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Spades");
    sf::RectangleShape board(sf::Vector2f(1200.0f, 800.0f));
    board.setFillColor(sf::Color(100, 10, 10));

    sf::SoundBuffer soundBuff;
    soundBuff.loadFromFile("flipcard.ogg");
    sf::Sound *sound = new sf::Sound;
    sound->setBuffer(soundBuff);
    sound->setVolume(40.f);

    sf::Font font;
    font.loadFromFile("Odin Rounded - Light.otf");

    sf::Texture texture;
    texture.loadFromFile("Cards/zdefault.jpg");

    Game game;
    game.initialize(texture);
    game.setGame(window, font, texture);
    window.clear();

    Player *player1; 
    player1 = game.getP1();
    Player *player2; 
    player2 = game.getP2();
    Player *player3; 
    player3 = game.getP3();
    Player *player4; 
    player4 = game.getP4(); 
    //game.Print();


    /*cout << "Player 1" << endl;
    player1->printCards();
    cout << "Player 2" << endl;
    player2->printCards();
    cout << "Player 3" << endl;
    player3->printCards();
    cout << "Player 4" << endl;
    player4->printCards(); */
   
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
        
        window.clear();

        game.updateDisplay(window, font, texture, sound, worldPos);

        if(game.roundOver()) {
            game.awardScore();
            if(game.gameOver() == 1) {
                window.clear();
                
                window.draw(board);
                sf::Text winner;
                winner.setFont(font);
                winner.setCharacterSize(40);
                winner.setString("Team Blue Wins!");
                winner.setPosition(sf::Vector2f(600-winner.getGlobalBounds().width/2, 400-winner.getGlobalBounds().height/2));
                window.draw(winner);
                window.display();
                sf::sleep(sf::seconds(1)); 

                game.resetGame();
                game.setGame(window, font, texture);
            }
            else if(game.gameOver() == 2) {
                window.clear();
                
                window.draw(board);
                sf::Text winner;
                winner.setFont(font);
                winner.setCharacterSize(40);
                winner.setString("Team Black Wins!");
                winner.setPosition(sf::Vector2f(600-winner.getGlobalBounds().width/2, 400-winner.getGlobalBounds().height/2));
                window.draw(winner);
                window.display();
                sf::sleep(sf::seconds(1));

                game.resetGame();
                game.setGame(window, font, texture);
            }
            else {
                game.resetRound();
                game.updateBids(window, font, texture);
            }
        } 

        game.drawCards(window, font, texture);
        window.display();
        sf::sleep(sf::seconds(0.4));  
    } 

    delete sound;
    return 0; 
} 