#include "player.hpp"

int WINNING_SCORE = 500;

class Game {
  public:
    void initialize(sf::Texture &text);
    void shuffle();
    ~Game();
    void Print() const;
    void displayBid(sf::RenderWindow &rw, sf::Font &font, Player* p, float x, float y);
    void displayScore(sf::RenderWindow &rw, sf::Font &font);
    bool setGame(sf::RenderWindow &rw, sf::Font &font, sf::Texture texture);
    void drawCards(sf::RenderWindow &rw, sf::Font &font, sf::Texture &texture, sf::Vector2f mousePosition);
    void drawCards(sf::RenderWindow &rw, sf::Font &font, sf::Texture &texture);
    bool chooseBid(sf::RenderWindow &rw, sf::Font &font, sf::Texture &texture);
    bool chooseCard(sf::RenderWindow &rw, sf::Font &font, sf::Texture &texture);
    int selectCard(Player *player, bool first);
    bool playCard(Player *player, const sf::Vector2f& mousePosition, float x, float y, bool p);
    bool validCard(Card *card, bool noSuit, bool onlySpades);
    bool nil(bool team);
    void awardBid();
    void awardScore();
    bool roundOver();
    int gameOver();
    void updateDisplay(sf::RenderWindow &rw, sf::Font &font, sf::Texture &texture, sf::Sound *sound, sf::Vector2f mousePos);
    void updateBids(sf::RenderWindow &rw, sf::Font &font, sf::Texture &texture);
    void resetRound();
    void resetGame();

    // Getters
    Player* getP1() { return p1; }
    Player* getP2() { return p2; }
    Player* getP3() { return p3; }
    Player* getP4() { return p4; }
    int getTurn() { return roundTurn; }
    char getSuit() { return currentSuit; }

  protected:
    Player *p1;
    Player *p2;
    Player *p3;
    Player *p4;
    sf::RectangleShape r1;
    sf::RectangleShape r2;
    sf::RectangleShape r3;
    sf::Texture menuText;
    
    int roundTurn;
    int gameTurn;
    char currentSuit;
    bool spades;
    bool inProgress;
    int round;
    int score1;
    int score2;
    int penalty1;
    int penalty2;
    vector <Card*> deck;
    vector <string> filenames;
};

void Game::initialize(sf::Texture &text)
{
    roundTurn = 1;
    gameTurn = roundTurn;
    currentSuit = 'N';
    score1 = 0;
    penalty1 = 0;
    score2 = 0;
    penalty2 = 0;
    round = 0;
    spades = false;
    inProgress = false;

    //sf::Texture menuText;
    menuText.loadFromFile("menu_icon.png");
    // Spades
    filenames.push_back("2_of_spades.png");
    filenames.push_back("3_of_spades.png");
    filenames.push_back("4_of_spades.png");
    filenames.push_back("5_of_spades.png");
    filenames.push_back("6_of_spades.png");
    filenames.push_back("7_of_spades.png");
    filenames.push_back("8_of_spades.png");
    filenames.push_back("9_of_spades.png");
    filenames.push_back("10_of_spades.png");
    filenames.push_back("jack_of_spades.png");
    filenames.push_back("queen_of_spades.png");
    filenames.push_back("king_of_spades.png");
    filenames.push_back("ace_of_spades2.png");
    // Hearts
    filenames.push_back("2_of_hearts.png");
    filenames.push_back("3_of_hearts.png");
    filenames.push_back("4_of_hearts.png");
    filenames.push_back("5_of_hearts.png");
    filenames.push_back("6_of_hearts.png");
    filenames.push_back("7_of_hearts.png");
    filenames.push_back("8_of_hearts.png");
    filenames.push_back("9_of_hearts.png");
    filenames.push_back("10_of_hearts.png");
    filenames.push_back("jack_of_hearts.png");
    filenames.push_back("queen_of_hearts.png");
    filenames.push_back("king_of_hearts.png");
    filenames.push_back("ace_of_hearts.png");
    // Clubs
    filenames.push_back("2_of_clubs.png");
    filenames.push_back("3_of_clubs.png");
    filenames.push_back("4_of_clubs.png");
    filenames.push_back("5_of_clubs.png");
    filenames.push_back("6_of_clubs.png");
    filenames.push_back("7_of_clubs.png");
    filenames.push_back("8_of_clubs.png");
    filenames.push_back("9_of_clubs.png");
    filenames.push_back("10_of_clubs.png");
    filenames.push_back("jack_of_clubs.png");
    filenames.push_back("queen_of_clubs.png");
    filenames.push_back("king_of_clubs.png");
    filenames.push_back("ace_of_clubs.png");
    // Diamonds
    filenames.push_back("2_of_diamonds.png");
    filenames.push_back("3_of_diamonds.png");
    filenames.push_back("4_of_diamonds.png");
    filenames.push_back("5_of_diamonds.png");
    filenames.push_back("6_of_diamonds.png");
    filenames.push_back("7_of_diamonds.png");
    filenames.push_back("8_of_diamonds.png");
    filenames.push_back("9_of_diamonds.png");
    filenames.push_back("10_of_diamonds.png");
    filenames.push_back("jack_of_diamonds.png");
    filenames.push_back("queen_of_diamonds.png");
    filenames.push_back("king_of_diamonds.png");
    filenames.push_back("ace_of_diamonds.png");

    for(int i=0; i < filenames.size(); i++)
    {
        Card *c = new Card;

        c->rank = (i % 13) + 2;
        if(i < 13) {
            c->suit = 'S';
            c->value = 1000 + c->rank;
        }
        else if(i < 26) {
            c->suit = 'H';
            c->value = 500 + c->rank;
        }
        else if(i < 39) {
            c->suit = 'C';
            c->value = 100 + c->rank;
        }
        else if(i < 52) {
            c->suit = 'D';
            c->value = 10 + c->rank;
        }
 
        c->r.setSize(sf::Vector2f(85.0f, 119.f));
        string s = "Cards/" + filenames[i];
        c->texture.loadFromFile(s);
        c->r.setTexture(&c->texture);
        c->r.setOutlineThickness(2.f);
        c->r.setOutlineColor(sf::Color::Black);
        c->placed = false;
        c->discarded = false;
        deck.push_back(c);

        r1.setSize(sf::Vector2f(85.0f, 119.0f));
        r1.setPosition(270-72, 30);
        r1.setTexture(&text);

        r2.setSize(sf::Vector2f(85.0f, 119.0f));
        r2.setPosition(630-72, 30);
        r2.setTexture(&text);
    
        r3.setSize(sf::Vector2f(85.0f, 119.0f));
        r3.setPosition(990-72, 30);
        r3.setTexture(&text);
    }

    shuffle();

    p1 = new Player(0, true, deck);
    p2 = new Player(1, false, deck);
    p3 = new Player(2, true, deck);
    p4 = new Player(3, false, deck);
}

void Game::Print() const
{
    for(Card* c : deck) cout << c->suit << ": " << c->rank << endl;
    cout << deck.size() << endl;
}

void Game::displayBid(sf::RenderWindow &rw, sf::Font &font, Player* p, float x, float y)
{
    sf::Text slash;
    sf::Text trick;
    sf::Text bid;

    slash.setFont(font);
    slash.setString("/");
    slash.setPosition(sf::Vector2f(x, y)); //600, 750
    slash.setOutlineThickness(1.f);

    trick.setFont(font);
    p->getTrick() == -1 ? trick.setString('-') : trick.setString(to_string(p->getTrick()));
    trick.setPosition(sf::Vector2f(x-25, y));
    trick.setOutlineThickness(1.f);

    bid.setFont(font);
    p->getBid() == -1 ? bid.setString('-') : bid.setString(to_string(p->getBid()));
    bid.setPosition(sf::Vector2f(x+20, y));
    bid.setOutlineThickness(1.f);

    if(p->getTeam()) {
        slash.setOutlineColor(sf::Color::Blue);
        trick.setOutlineColor(sf::Color::Blue);
        bid.setOutlineColor(sf::Color::Blue);
    }
    else {
        slash.setOutlineColor(sf::Color::Black);
        trick.setOutlineColor(sf::Color::Black);
        bid.setOutlineColor(sf::Color::Black);
    }

    rw.draw(trick);
    rw.draw(slash);
    rw.draw(bid);
}

void Game::displayScore(sf::RenderWindow &rw, sf::Font &font)
{
    sf::Text s1;
    sf::Text s2;
    sf::Text p1;
    sf::Text p2;

    s1.setFont(font);
    s1.setString(to_string(score1));
    s1.setPosition(100, 500);
    s1.setOutlineThickness(1.f);
    s1.setOutlineColor(sf::Color::Blue);
    p1.setFont(font);
    p1.setString(to_string(penalty1));
    p1.setPosition(100, 530);
    p1.setOutlineThickness(1.f);
    p1.setOutlineColor(sf::Color::Blue);
    
    s2.setFont(font);
    s2.setString(to_string(score2));
    s2.setPosition(1100, 500);
    s2.setOutlineThickness(1.f);
    s2.setOutlineColor(sf::Color::Black);
    p2.setFont(font);
    p2.setString(to_string(penalty2));
    p2.setPosition(1100, 530);
    p2.setOutlineThickness(1.f);
    p2.setOutlineColor(sf::Color::Black);
    
    rw.draw(s1);
    rw.draw(p1);
    rw.draw(s2);
    rw.draw(p2);
}

void Game::shuffle()
{
    for(int i=0; i < deck.size(); i++)
    {
        int index = rand() % 52;
        swap(deck[i], deck[index]);
    }
}

Game::~Game()
{
    for(Card *c : deck) delete c;
    delete p1;
    delete p2;
    delete p3;
    delete p4;
}

bool Game::setGame(sf::RenderWindow &rw, sf::Font &font, sf::Texture texture)
{
    sf::Texture windowTexture;
    windowTexture.loadFromFile("Red-Background-.jpg");
    sf::RectangleShape background(sf::Vector2f(rw.getSize().x, rw.getSize().y));
    background.setTexture(&windowTexture);

    while(rw.isOpen())
    {
        sf::Event event;
        while (rw.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    rw.close();
                    break;
                default:
                    break;
            }
        }

        rw.clear();
        sf::Vector2i pixelPos = sf::Mouse::getPosition(rw);
        sf::Vector2f worldPos = rw.mapPixelToCoords(pixelPos);
        
        rw.draw(background);

        sf::Text spades;
        spades.setFont(font);
        spades.setString("Spades");
        spades.setFillColor(sf::Color::White);
        spades.setCharacterSize(60);
        spades.setPosition(500, 300);
        sf::Text newGame;
        newGame.setFont(font);
        newGame.setString("New Game");
        newGame.setFillColor(sf::Color::White);
        newGame.setPosition(525, 400);
        sf::Text cont;
        cont.setFont(font);
        cont.setString("Continue");
        cont.setFillColor(sf::Color::White);
        cont.setPosition(530, 450);

        if(inProgress) {
            if(cont.getGlobalBounds().contains(worldPos)) {
                cont.setFillColor(sf::Color::Yellow);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::sleep(sf::seconds(0.5));
                    rw.clear();
                    
                    //break;
                    return true;
                }
            }

        }

        if(newGame.getGlobalBounds().contains(worldPos)) {
            newGame.setFillColor(sf::Color::Yellow);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::sleep(sf::seconds(0.5));

                if(inProgress) resetGame();
                updateBids(rw, font, texture);
                inProgress = true;
                //break;
                return false;
            }
        }

        if(inProgress) rw.draw(cont);
        rw.draw(spades);
        rw.draw(newGame);

        rw.display();

    }

    return true;
}

bool Game::validCard(Card *card, bool noSuit, bool onlySpades)
{
    if(roundTurn == 1) return card->suit != 'S' || spades || onlySpades;
     
    return card->suit == currentSuit || noSuit;
}

bool Game::chooseBid(sf::RenderWindow &rw, sf::Font &font, sf::Texture &texture)
{
    bool flag = true;
   
    while(rw.isOpen() && flag)
    {
        sf::Event event;
        while (rw.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    rw.close();
                    break;
                default:
                    break;
            }
        }

        sf::Vector2i pixelPos = sf::Mouse::getPosition(rw);
        sf::Vector2f worldPos = rw.mapPixelToCoords(pixelPos);

        rw.clear();

        drawCards(rw, font, texture);

        sf::Text text;
        text.setFont(font);
        text.setString("Choose Your Bid");
        text.setFillColor(sf::Color::White);
        text.setPosition(490, 270);
        rw.draw(text);

        vector <sf::CircleShape> bids;
        string str = "Bids/Bid";
        float y = 350;
        float x = 1;
    
        for(int i=0; i <= 13; i++)
        {
            if(i == 12) x = 3;
            sf::CircleShape c(30.0f);
            c.setPosition(60*x + 350, y);
            c.setOutlineColor(sf::Color::Black);
            c.setOutlineThickness(4.f);

            sf::Texture b;
            
            string s = str + to_string(i) + ".png";
            b.loadFromFile(s);
            c.setTexture(&b);
            rw.draw(c);
            bids.push_back(c);
            x++;

            if((i+1) % 6 == 0 && i < 12) {
                y += 75;
                x = 1;
            }
        }


        
        for(int i=0; i < bids.size(); i++)
        {
            sf::CircleShape c = bids[i];

            if(c.getGlobalBounds().contains(worldPos)){
                c.setOutlineColor(sf::Color::Yellow);
            }
        
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            
                if(c.getGlobalBounds().contains(worldPos)) {
                    p1->setBid(i);
                    p1->setTrick(0);
                    flag = false;
                    break;
                }
            }
        }


        rw.display();
    }

    return true;
}

bool Game::chooseCard(sf::RenderWindow &rw, sf::Font &font, sf::Texture &texture)
{
  
    bool flag = true;
    bool result = true;

    sf::RectangleShape menu(sf::Vector2f(64.0f, 64.0f));
    menu.setPosition(sf::Vector2f(0.f, 740.f));
    menu.setTexture(&menuText);

    bool noSuit = p1->noSuit(currentSuit);
    bool onlySpades = p1->onlySpades();
   
    while(rw.isOpen() && flag)
    {
        sf::Event event;
        while (rw.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    rw.close();
                    break;
                default:
                    break;
            }
        }

        sf::Vector2i pixelPos = sf::Mouse::getPosition(rw);
        sf::Vector2f worldPos = rw.mapPixelToCoords(pixelPos);

        rw.clear();

        drawCards(rw, font, texture, worldPos);

        sf::RectangleShape menu(sf::Vector2f(64.0f, 64.0f));
        menu.setPosition(sf::Vector2f(0.f, 740.f));
        menu.setTexture(&menuText);
        rw.draw(menu);

        for(int i=0; i < p1->getCards().size(); i++)
        {
            Card *c = p1->getCards()[i];

            if(roundTurn == 1) currentSuit = c->suit;

            if(validCard(c, noSuit, onlySpades)) {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if(c->r.getGlobalBounds().contains(worldPos)) {
                        if(!c->placed && !c->discarded) { 
                            c->r.setPosition(sf::Vector2f(558, 550));
                            c->placed = true;
                            if(c->suit == 'S') spades = true;
                            p1->setIndex(i);
                            p1->placedCards.push(c);

                            flag = false;
                            break;
                        }
                    }
                }
            } 
        } 

        

        if(menu.getGlobalBounds().contains(worldPos)) {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                result = setGame(rw, font, texture);
                if(!result) return result;
            }
        } 

        rw.display();
    }

    return result;
}

void Game::drawCards(sf::RenderWindow &rw, sf::Font &font, sf::Texture &texture)
{
    sf::RectangleShape board(sf::Vector2f(1200.0f, 800.0f));
    board.setFillColor(sf::Color(100, 10, 10));

    rw.draw(board);

    displayBid(rw, font, p1, 600.f, 750.f);
    displayBid(rw, font, p2, 115.f, 80.f);
    displayBid(rw, font, p3, 475.f, 80.f);
    displayBid(rw, font, p4, 840.f, 80.f);

    displayScore(rw, font);

    rw.draw(r1);
    rw.draw(r2);
    rw.draw(r3);

    sf::RectangleShape menu(sf::Vector2f(64.0f, 64.0f));
    menu.setPosition(sf::Vector2f(0.f, 740.f));
    menu.setTexture(&menuText);

    rw.draw(menu);


    int i=0;
    for(Card *c : p1->getCards())
    {
        if(!c->placed && !c->discarded) {
            c->r.setPosition(90*(i+1) - 72, 600);
            rw.draw(c->r);
        }

        i++;
    }
}

void Game::drawCards(sf::RenderWindow &rw, sf::Font &font, sf::Texture &texture, sf::Vector2f mousePosition)
{
    sf::RectangleShape board(sf::Vector2f(1200.0f, 800.0f));
    board.setFillColor(sf::Color(100, 10, 10));

    rw.draw(board);

    displayBid(rw, font, p1, 600.f, 750.f);
    displayBid(rw, font, p2, 115.f, 80.f);
    displayBid(rw, font, p3, 475.f, 80.f);
    displayBid(rw, font, p4, 840.f, 80.f);

    displayScore(rw, font);

    rw.draw(r1);
    rw.draw(r2);
    rw.draw(r3);

    sf::RectangleShape menu(sf::Vector2f(64.0f, 64.0f));
    menu.setPosition(sf::Vector2f(0.f, 740.f));
    menu.setTexture(&menuText);

    rw.draw(menu);

    bool noSuit = p1->noSuit(currentSuit);
    bool onlySpades = p1->onlySpades();

    int i=0;
    for(Card *c : p1->getCards())
    {
        if(!c->placed && !c->discarded) {
            c->r.setPosition(90*(i+1) - 72, 600);
            rw.draw(c->r);
            if(validCard(c, noSuit, onlySpades)) {
                     
                if(c->r.getGlobalBounds().contains(mousePosition))
                    c->r.setOutlineColor(sf::Color::Yellow);
                else 
                    c->r.setOutlineColor(sf::Color::Black);
            }
        }

        i++;
    } 

    if(!p1->getPlaced().empty()) {
        Card *c =  p1->getPlaced().top();
        c->r.setPosition(sf::Vector2f(558, 400));
        c->r.setOutlineColor(sf::Color::Black); 
        if(!c->discarded) rw.draw(c->r);
        p1->getPlaced().pop();
    }

    if(!p2->getPlaced().empty()) {
        Card *c = p2->getPlaced().top();
        if(!c->discarded) rw.draw(c->r);
        p2->getPlaced().pop();
    }

    if(!p3->getPlaced().empty()) { 
        Card *c = p3->getPlaced().top();
        if(!c->discarded) rw.draw(c->r);
        p3->getPlaced().pop();
    }

    if(!p4->getPlaced().empty()) {
        Card *c = p4->getPlaced().top();
        if(!c->discarded) rw.draw(c->r);
        p4->getPlaced().pop();
    }    
}

void Game::updateBids(sf::RenderWindow &rw, sf::Font &font, sf::Texture &texture)
{
    rw.clear();
    drawCards(rw, font, texture);
    rw.display();
    sf::sleep(sf::seconds(1));

    if(roundTurn == 1) {
        chooseBid(rw, font, texture);
        drawCards(rw, font, texture);
        rw.display();
        sf::sleep(sf::seconds(0.5));
        p2->selectBid();
        drawCards(rw, font, texture);
        rw.display();
        sf::sleep(sf::seconds(0.5));
        p3->selectBid();
        drawCards(rw, font, texture);
        rw.display();
        sf::sleep(sf::seconds(0.5));
        p4->selectBid();
        drawCards(rw, font, texture);
        rw.display();
        sf::sleep(sf::seconds(0.5));
        //rw.display(); 
    } 
    else if(roundTurn == 2) {
        p2->selectBid();
        drawCards(rw, font, texture);
        rw.display();
        sf::sleep(sf::seconds(0.5));
        p3->selectBid();
        drawCards(rw, font, texture);
        rw.display();
        sf::sleep(sf::seconds(0.5));
        p4->selectBid();
        drawCards(rw, font, texture);
        rw.display();
        sf::sleep(sf::seconds(0.5));
        chooseBid(rw, font, texture);
        drawCards(rw, font, texture);
        sf::sleep(sf::seconds(0.5));
        //rw.display();
    }
    else if(roundTurn == 3) {
        p3->selectBid();
        drawCards(rw, font, texture);
        rw.display();
        sf::sleep(sf::seconds(0.5));
        p4->selectBid();
        drawCards(rw, font, texture);
        rw.display();
        sf::sleep(sf::seconds(0.5));
        chooseBid(rw, font, texture);
        drawCards(rw, font, texture);
        rw.display();
        sf::sleep(sf::seconds(0.5));
        p2->selectBid();
        drawCards(rw, font, texture);
        rw.display();
        sf::sleep(sf::seconds(0.5));
        //rw.display(); 
    }
    else {
        p4->selectBid();
        drawCards(rw, font, texture);
        rw.display();
        sf::sleep(sf::seconds(0.5));
        chooseBid(rw, font, texture);
        drawCards(rw, font, texture);
        rw.display();
        sf::sleep(sf::seconds(0.5));
        p2->selectBid();
        drawCards(rw, font, texture);
        rw.display();
        sf::sleep(sf::seconds(0.5));
        p3->selectBid();
        drawCards(rw, font, texture);
        rw.display();
        sf::sleep(sf::seconds(0.5));
        //rw.display(); 
    }

    rw.clear();

    //rw.display(); 
} 

void Game::updateDisplay(sf::RenderWindow &rw, sf::Font &font, sf::Texture &texture, sf::Sound *sound, sf::Vector2f mousePos)
{
    //rw.clear();
    drawCards(rw, font, texture);
    rw.display();
    sf::sleep(sf::seconds(0.2));
   
    if(roundTurn == 1) {

        if(!chooseCard(rw, font, texture)) return;
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(0.5)); 
        playCard(p2, mousePos, 458, 250, 0);
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(0.5)); 
        playCard(p3, mousePos, 558, 250, 0);
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(0.5)); 
        playCard(p4, mousePos, 658, 250, 0);
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(1));
        rw.display(); 

        awardBid();
    } 
    else if(roundTurn == 2) {
    
        playCard(p2, mousePos, 458, 250, 1);
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(0.5)); 
        playCard(p3, mousePos, 558, 250, 0);
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(0.5)); 
        playCard(p4, mousePos, 658, 250, 0);
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(1));
        if(!chooseCard(rw, font, texture)) return;
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(0.5)); 
        rw.display(); 
        
        awardBid(); 
    }
    else if(roundTurn == 3) {
        
        playCard(p3, mousePos, 558, 250, 1);
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(0.5)); 
        playCard(p4, mousePos, 658, 250, 0);
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(1));
        if(!chooseCard(rw, font, texture)) return;
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(0.5));
        playCard(p2, mousePos, 458, 250, 0);
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(1));
        rw.display();

        awardBid(); 
    }
    else {
       
        playCard(p4, mousePos, 658, 250, 1);
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(1));
        if(!chooseCard(rw, font, texture)) return;
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(0.5));
        playCard(p2, mousePos, 458, 250, 0);
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(0.5));
        playCard(p3, mousePos, 558, 250, 0);
        drawCards(rw, font, texture, mousePos);
        sound->play();
        rw.display();
        sf::sleep(sf::seconds(1));
        rw.display();

        awardBid(); 
    } 
}

int Game::selectCard(Player *player, bool first)
{
    vector <Card*> hand = player->getCards();

    vector <int> valid;
    bool noSuit = player->noSuit(currentSuit);
 
    for(int i = 0; i < hand.size(); i++) 
    {
        Card *c = hand[i];

        if(!c->discarded && !c->placed) {
            if(!first) {
                if(noSuit || c->suit == currentSuit) valid.push_back(i);
            }
            else {
                if(c->suit != 'S' || spades || player->onlySpades()) valid.push_back(i);
            }
        } 

    }


    return valid[rand() % valid.size()];
}

bool Game::playCard(Player *player, const sf::Vector2f& mousePosition, float x, float y, bool p)
{
    int index = selectCard(player, p);
    vector <Card*> hand = player->getCards();

    hand[index]->r.setPosition(sf::Vector2f(x, y));
    hand[index]->r.setOutlineColor(sf::Color::Black);
    hand[index]->placed = true;

    if(hand[index]->suit == 'S') spades = true;
    player->setIndex(index);
    player->placedCards.push(hand[index]);
    if(p) currentSuit = hand[index]->suit;

    return true; 
}

void Game::awardBid()
{
    vector <Card*> placedCards;

    Card *c1 = p1->getCards().at(p1->getIndex());
    c1->discarded = true;
    placedCards.push_back(c1);

    Card *c2 = p2->getCards().at(p2->getIndex());
    c2->discarded = true;
    placedCards.push_back(c2);

    Card *c3 = p3->getCards().at(p3->getIndex());
    c3->discarded = true;
    placedCards.push_back(c3);

    Card *c4 = p4->getCards().at(p4->getIndex());
    c4->discarded = true;
    placedCards.push_back(c4);

    int maxRank = 0;
    int maxIndex = 0;

    for (int i = 0; i < placedCards.size(); i++) 
    {
        Card* c = placedCards[i];

        if (c->suit != currentSuit && c->suit != 'S') {
            continue;
        } 
        else if (c->suit != currentSuit) {
            spades = true;
            maxRank = c->rank;
            maxIndex = i;

            for (int j = i; j < placedCards.size(); j++) 
            {
                Card* card = placedCards[j];

                if (card->suit != 'S') continue;  

                if (card->rank > maxRank) {
                    maxRank = card->rank;
                    maxIndex = j;
                }
            }

            break;
        }

        if (c->rank > maxRank) {
            maxRank = c->rank;
            maxIndex = i;
        }
    }


    //placedCards[maxIndex]->r.setOutlineColor(sf::Color::Green);

    if(maxIndex == 0) {
        p1->incrementTrick();
        roundTurn = 1;
    }
    else if(maxIndex == 1) {
        p2->incrementTrick();
        roundTurn = 2;
    }
    else if(maxIndex == 2) { 
        p3->incrementTrick();
        roundTurn = 3;
    }
    else { 
        p4->incrementTrick();
        roundTurn = 4;
    }

    round++; 

}

bool Game::nil(bool team)
{
    int bid1;
    int trick1;
    int bid2;
    int trick2;

    if(team) {
        bid1 = p1->getBid();
        trick1 = p1->getTrick();
        bid2 = p3->getBid();
        trick2 = p3->getTrick();

        if(bid1 != 0 && bid2 != 0) return false;

        if(bid1 == 0) trick1 > 0 ? score1 -= 100 : score1 += 100;
        if(bid2 == 0) trick2 > 0 ? score1 -= 100 : score1 += 100;
        
    }
    else {
        bid1 = p2->getBid();
        trick1 = p2->getTrick();
        bid2 = p4->getBid();
        trick2 = p4->getTrick();

        if(bid1 != 0 && bid2 != 0) return false;

        if(bid1 == 0) trick1 > 0 ? score2 -= 100 : score2 += 100;
        if(bid2 == 0) trick2 > 0 ? score2 -= 100 : score2 += 100;
    }

    return true;
}

void Game::awardScore()
{
    int bid1 = p1->getBid() + p3->getBid();
    int tricks1 = p1->getTrick() + p3->getTrick();

    int bid2 = p2->getBid() + p4->getBid();
    int tricks2 = p2->getTrick() + p4->getTrick();

    nil(1); 
    nil(0);   

    if(tricks1 >= bid1) {
        score1 += bid1 * 10;
        int extra = tricks1 - bid1;

        score1 += extra;
        penalty1 += extra;
        if(penalty1 >= 10) {
            penalty1 -= 10;
            score1 -= 100; 
        }
    }
    else {
        score1 -= bid1 * 10;
    }

    if(tricks2 >= bid2) {
        score2 += bid2 * 10;
        int extra = tricks2 - bid2;

        score2 += extra;
        penalty2 += extra;
        if(penalty2 >= 10) {
            penalty2 -= 10;
            score2 -= 100; 
        }
    }
    else {
        score2 -= bid2 * 10;
    }
}

bool Game::roundOver()
{
    return round == 13;
}

int Game::gameOver()
{
    if(score1 > score2 && score1 >= WINNING_SCORE) {
        inProgress = false;
        return 1;
    }

    if(score2 > score1 && score2 >= WINNING_SCORE) {
        inProgress = false;
        return 2;
    }

    return 0;
}

void Game::resetGame()
{
    delete p1;
    delete p2;
    delete p3;
    delete p4;

    shuffle();
    for(Card *c : deck)
    {
        c->placed = false;
        c->discarded = false;
    }

    roundTurn = 1;
    gameTurn = roundTurn;
    currentSuit = 'N';
    score1 = 0;
    penalty1 = 0;
    score2 = 0;
    penalty2 = 0;
    round = 0;
    spades = false;
    inProgress = false;

    // Reinitialize players
    p1 = new Player(0, true, deck);
    p2 = new Player(1, false, deck);
    p3 = new Player(2, true, deck);
    p4 = new Player(3, false, deck);
}

void Game::resetRound()
{
    delete p1;
    delete p2;
    delete p3;
    delete p4;

    shuffle();
    for(Card *c : deck)
    {
        c->placed = false;
        c->discarded = false;
    }

    p1 = new Player(0, true, deck);
    p2 = new Player(1, false, deck);
    p3 = new Player(2, true, deck);
    p4 = new Player(3, false, deck);

    round = 0;
    spades = false;
    
    gameTurn += 1;
    if(gameTurn == 5) gameTurn = 1;
    roundTurn = gameTurn;
}

