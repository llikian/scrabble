/***************************************************************************************************
 * @file  Dictionary.cpp
 * @brief Implementation of the Dictionary class
 **************************************************************************************************/

#include "Dictionary.hpp"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include "Board.hpp"

Node::Node(const char value, const bool isTerminal) : value(value), isTerminal(isTerminal), children{} { }

Dictionary::Dictionary() : root(new Node('\0', false)) { }

Dictionary::Dictionary(const std::string& loadPath) : root(new Node('\0', false)) {
    std::ifstream file(loadPath);
    if(!file.is_open()) {
        throw std::runtime_error("Couldn't open file \"" + loadPath + "\".");
    }

    std::string word;
    while(file >> word) {
        if(!word.empty() && word.size() <= BOARD_SIZE) {
            insertGADDAGWord(word);
        }
    }
}

void Dictionary::insertWord(const std::string& word) {
    Node* current = root;

    for(char l: word) {
        if(l >= 'a' && l <= 'z') {
            LOWERCASE_TO_UPPERCASE(l);
        }

        // If char is '+', put at the end, else put at alphabet position
        const int pos = l == '+' ? ALPHABET_SIZE : l - 'A';

        if(current->children[pos] == nullptr) {
            current->children[pos] = new Node(l, false);
        }

        current = current->children[pos];
    }

    current->isTerminal = true;
}

void Dictionary::insertGADDAGWord(const std::string& word) {
    int len = word.length();

    std::string gaddagWord = word;
    gaddagWord.insert(0, "+");

    // For each letter in the word, create a word by mirroring it around the '+'
    for(int i = 1 ; i <= len ; i++) {
        std::rotate(gaddagWord.begin(), gaddagWord.begin() + i, gaddagWord.begin() + i + 1);

        insertWord(gaddagWord);
    }
}

bool Dictionary::containWord(const std::string& word) {
    const Node* current = root;

    for(const char l: word) {
        // If char is '+', check at the end, else check at alphabet position
        const int pos = l == '+' ? ALPHABET_SIZE : l - 'A';

        if(current->children[pos] == nullptr) {
            return false;
        }

        current = current->children[pos];
    }

    return current->isTerminal;
}

void Dictionary::unitTests() {
    std::cout << "Dictionnary Unit Tests:\n";

    /* Manual Insertion Test */ {
        Dictionary dico;

        dico.insertWord("abc");
        assert(dico.root->children[0]->children[1]->children[2]->value == 'C');
        assert(dico.containWord("ABC"));
        assert(!dico.containWord("A"));
        assert(!dico.containWord("ABCE"));
        assert(!dico.containWord("SKIBIDI"));

        dico.insertGADDAGWord("ABC");
        assert(!dico.containWord("+ABC"));
        assert(dico.containWord("A+BC"));
        assert(dico.containWord("BA+C"));
        assert(dico.containWord("CBA+"));

        std::cout << "  Manual insertion test passes!\n";
    }

    /* File Insertion Test */ {
        Dictionary dico;
        std::ifstream file("data/dico.txt");
        std::string word;
        while(file >> word) {
            if(!word.empty() && word.size() <= BOARD_SIZE) {
                dico.insertGADDAGWord(word);
            }
        }

        assert(dico.containWord("AA"));
        assert(!dico.containWord("AAHJG"));
        assert(dico.containWord("MUTAZILISMES"));
        assert(!dico.containWord("VHJIDVU"));

        std::cout << "  File insertion test passes!\n";
    }

    /* GADDAG Insertion Test */ {
        Dictionary dico2("data/dico.txt");

        assert(dico2.containWord("F+ROMAGE"));
        assert(dico2.containWord("PPAN+ASSIONS"));
        assert(!dico2.containWord("BAC+C"));
        assert(!dico2.containWord("A"));
        assert(!dico2.containWord("ABC"));

        std::cout << "  Gaddag insertion test passes!\n";
    }

    /* Full Dictionary Test */ {
        Dictionary dico("data/dico.txt");
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

        std::cout << "  Full dictionary test passes!\n";
    }

    std::cout << "All dictionary tests passed!\n\n";
}
