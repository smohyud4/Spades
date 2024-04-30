#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stack>
#include <unordered_map>
using namespace std;

class Card {   
  public:
      friend class Player;
      friend class Game;
  protected:
      char suit;
      int rank;
      bool placed;
      bool discarded;
      int value;
      sf::RectangleShape r;
      sf::Texture texture;
};

class Player {
  public:

    Player(int start, bool t, vector <Card*> &d);
    void selectBid();
    bool onlySpades();
    bool noSuit(char s);
    void printCards();

    // Getters
    int getBid() { return bid; }
    int getTrick() { return trick; }
    int getIndex() { return placedIndex; }
    bool getTeam() { return team; }
    vector <Card*> getCards() { return cards; }
    stack <Card*> getPlaced() { return placedCards; }

    // Setters
    void incrementTrick() { trick += 1; }
    void setIndex(int placedIndex) { this->placedIndex = placedIndex; }
    void setBid(int bid) { this->bid = bid; }
    void setTrick(int trick) { this->trick = trick; }
    stack <Card*> placedCards;

  protected:
    void sortCards();
    int bid;
    int trick;
    int placedIndex;
    // True - Blue, False - Black
    bool team; 
    vector <class Card*> cards;
};

Player::Player(int start, bool t, vector <Card*> &d)
{
    for(int i=start; i < 52; i+=4) cards.push_back(d[i]);

    sortCards();
    trick = -1;
    bid = -1;
    placedIndex = 0;
    t ? team = true : team = false;
}

void Player::sortCards()
{
    int swap;
    Card *temp;

    for(int i=1; i < cards.size(); i++)
    {
        swap = i;
        for(int j=i-1; j >= 0; j--)
        {
            if(cards[j]->value < cards[swap]->value) {
                temp = cards[swap];
                cards[swap] = cards[j];
                cards[j] = temp; 
                swap--;
            }
        }
    
    }
}

void Player::selectBid()
{
    bid = 0;

    int score = 0;
    int spadesCount = 0;
    int heartsCount = 0;
    int diamondsCount = 0;
    int clubsCount = 0; 
    bool aceOfSpades = false;
    vector <Card*> spades;

    for(Card *c : cards)
    {

        switch(c->suit) {
            case 'S':
                spades.push_back(c);
                spadesCount += 1;
                break;
            case 'H':
                heartsCount += 1;
                break;
            case 'C':
                clubsCount += 1;
                break;
            case 'D':
                diamondsCount += 1;
                break;
            default:
                break;
        }
    }

    for(Card *c : cards)
    {
        if(c->suit == 'S') continue;
        if(c->rank == 14) bid += 1;

        if(c->rank == 13 ) {
            switch(c->suit) {
                case 'H':
                    if(heartsCount < 6) bid += 1;
                    break;
                case 'C':
                    if(clubsCount < 6) bid += 1;
                    break;
                case 'D':
                    if(diamondsCount < 6) bid += 1;
                    break;
                default:
                    break;
            }
        }
    }

    for(Card *spade : spades)
    {
        if(spade->rank < 10) score += spade->rank * 0.5;
        else score += spade->rank; 
    }

    bid += score / 13;
    trick = 0; 
    //bid = (spadesCount * score) / 8;
}

bool Player::onlySpades()
{
    for(Card *c : cards)
    {
        if(!c->placed && !c->discarded) {
            if(c->suit != 'S') return false;
        }
    }

    return true;
}

bool Player::noSuit(char s)
{
    for(Card *c : cards)
    {
        if(!c->placed && !c->discarded) {
            if(c->suit == s) return false;
        }
    }

    return true;
}

void Player::printCards()
{
    for(int i=0; i < cards.size(); i++)
    {
        Card *c = cards[i];
        cout << c->suit << ": " << c->rank <<endl;
    }
}
