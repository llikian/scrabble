/***************************************************************************************************
 * @file  test.cpp
 * @brief Contains the unit tests for the project
 **************************************************************************************************/

#include "Dictionary.hpp"

#include <cassert>
#include <iostream>
#include <fstream>

void testDictionary() {
    std::cout << "Dictionnary Tests:\n";

    // Manual insertion test
    Dictionary dico;
    dico.insertWord("abc");
    assert(dico.root->children[0]->children[1]->children[2]->value == 'C');
    assert(dico.containWord("ABC"));
    assert(!dico.containWord("A"));
    assert(!dico.containWord("ABCE"));
    assert(!dico.containWord("SKBIDI"));
    std::cout << "\tManual insertion test passes!\n";

    // File insertion test
    Dictionary dico1("data/dico.txt");
    assert(dico1.containWord("AA"));
    assert(!dico1.containWord("AAHJG"));
    assert(dico1.containWord("MUTAZILISMES"));
    assert(!dico1.containWord("VHJIDVU"));
    std::cout << "\tFile insertion test passes!\n";

    // GADDAG insertion test
    Dictionary dico2("data/dico.txt", true);
    assert(dico2.containWord("F+ROMAGE"));
    assert(dico2.containWord("PPAN+ASSIONS"));
    assert(!dico2.containWord("BAC+C"));
    assert(!dico2.containWord("A"));
    assert(!dico2.containWord("ABC"));
    std::cout << "\tGaddag insertion test passes!\n";

    // Full Dictionary Test
    Dictionary dico3("data/dico.txt", true);
    std::ifstream file("data/dico.txt");
    std::string word;
    while(file >> word) {
        if(!word.empty() && word.size() <= 15) {
            assert(dico3.containWord('+' + word));
        }
    }
    std::cout << "\tFull dictionary test passes!\n";

    std::cout << "All dictionary tests passed!\n\n";
}

int main() {
    testDictionary();

    return 0;
}