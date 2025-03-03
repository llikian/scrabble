/***************************************************************************************************
 * @file  test.cpp
 * @brief Contains the unit tests for the project
 **************************************************************************************************/

#include <cassert>
#include <fstream>
#include <iostream>

#include "Bag.hpp"
#include "Board.hpp"
#include "Dictionary.hpp"
#include "Hand.hpp"

void Dictionary::unitTests() {
    std::cout << "Dictionnary Unit Tests:\n";

    /* Manual Insertion Test */ {
        Dictionary dico;

        dico.insertWord("abc");
        // assert(dico.root->children[0]->children[1]->children[2]->value == 'C');
        assert(dico.containWord("ABC"));
        assert(!dico.containWord("A"));
        assert(!dico.containWord("ABCE"));
        assert(!dico.containWord("SKIBIDI"));

        dico.insertGADDAGWord("ABC");
        assert(!dico.containWord("+ABC"));
        assert(dico.containWord("A+BC"));
        assert(dico.containWord("BA+C"));
        assert(dico.containWord("CBA+"));

        std::cout << "  Manual Insertion Test passed !\n";
    }

    /* File Insertion Test */ {
        Dictionary dico;
        std::ifstream file("data/dico.txt");
        std::string word;
        while(file >> word) {
            if(!word.empty() && word.size() <= BOARD_SIZE) {
                dico.insertWord(word);
            }
        }

        assert(dico.containWord("AA"));
        assert(!dico.containWord("AAHJG"));
        assert(dico.containWord("MUTAZILISMES"));
        assert(!dico.containWord("VHJIDVU"));

        std::cout << "  File Insertion Test passed !\n";
    }

    /* Full Dictionary Test */ {
        Dictionary dico("data/dico.txt");

        assert(dico.containWord("F+ROMAGE"));
        assert(dico.containWord("PPAN+ASSIONS"));
        assert(!dico.containWord("BAC+C"));
        assert(!dico.containWord("A"));
        assert(!dico.containWord("ABC"));

        std::ifstream file("data/dico.txt");
        std::string word;

        while(file >> word) {
            if(!word.empty() && word.size() <= 15) {
                int len = word.length();

                word.insert(0, "+");
                assert(!dico.containWord(word));

                for(int i = 1 ; i <= len ; i++) {
                    std::rotate(word.begin(), word.begin() + i, word.begin() + i + 1);
                    assert(dico.containWord(word));
                }
            }
        }

        std::cout << "  Full Dictionary Test passed !\n";
    }

    std::cout << "All Dictionary Unit Tests passed !\n\n";
}

void Hand::unitTests() {
    std::cout << "Hand Unit Tests:\n";

    /* Player Constructor Test */ {
        Bag bag;
        Player player(bag);
        Hand hand(player);

        assert(hand.capacity == player.capacity);
        for(unsigned int i = 0 ; i < player.capacity ; ++i) {
            assert(hand.letters[i] == player.hand[i]);
        }

        std::cout << "  Player Constructor Test passed !\n";
    }

    /* Copy Constructor Test */ {
        Bag bag;
        Player player(bag);
        Hand hand(player);
        Hand copy(hand);

        assert(copy.capacity == hand.capacity);
        for(unsigned int i = 0 ; i < hand.capacity ; ++i) {
            assert(copy.letters[i] == hand.letters[i]);
        }

        std::cout << "  Copy Constructor Test passed !\n";
    }

    /* Remove Letter Copy Constructor Test */ {
        Bag bag;
        Player player(bag);
        Hand hand(player);

        for(unsigned int i = 0 ; i < hand.capacity ; ++i) {
            Hand copy(hand, i);

            assert(copy.capacity == hand.capacity - 1);

            for(int j = 0 ; j < i ; ++j) {
                assert(copy.letters[j] == hand.letters[j]);
            }

            for(int j = i ; j < hand.capacity - 1 ; ++j) {
                assert(copy.letters[j] == hand.letters[j + 1]);
            }
        }

        std::cout << "  Remove Letter Copy Constructor Test passed !\n";
    }

    /* Copy Operator Test */ {
        Bag bag;
        Player player(bag);
        Hand hand(player);
        Hand copy = hand;

        assert(copy.capacity == hand.capacity);
        for(unsigned int i = 0 ; i < hand.capacity ; ++i) {
            assert(copy.letters[i] == hand.letters[i]);
        }

        std::cout << "  Copy Operator Test passed !\n";
    }

    std::cout << "All Hand Unit Tests passed !\n\n";
}

int main() {
    Bag::unitTests();
    Dictionary::unitTests();
    Hand::unitTests();

    return 0;
}
