//
// Created by Foyeur on 06/02/2025.
//

#include "Test.hpp"
#include "Dictionary.hpp"

#include <cassert>
#include <iostream>
#include <fstream>

void testAll() {
    testDictionary();
    std::cout << "Test passes!\n";
}

void testDictionary() {
    //Manual insertion test
    Dictionary dico;
    dico.insertWord("abc");
    assert(dico.root->children[0]->children[1]->children[2]->value == 'C');
    assert(dico.containWord("ABC"));
    assert(!dico.containWord("A"));
    assert(!dico.containWord("ABCE"));
    assert(!dico.containWord("SKBIDI"));
    std::cout << "Manual dictionary test passes!\n";

    //File insertion test
    Dictionary dico1("data/dico.txt");
    assert(dico1.containWord("AA"));
    assert(!dico1.containWord("AAHJG"));
    assert(dico1.containWord("MUTAZILISMES"));
    assert(!dico1.containWord("VHJIDVU"));
    std::cout << "File dictionary test passes!\n";

    //GADDAG insertion test
    Dictionary dico2("data/dico.txt", true);
    assert(dico2.containWord("F+ROMAGE"));
    assert(dico2.containWord("PPAN+ASSIONS"));
    assert(!dico2.containWord("BAC+C"));
    assert(!dico2.containWord("A"));
    assert(!dico2.containWord("ABC"));
    std::cout << "Gaddag dictionary test passes!\n";

    // Full Dictionary Test
    Dictionary dico3("data/dico.txt", true);
    std::ifstream file("data/dico.txt");
    std::string word;
    while(file >> word) {
        if(word.size() >= 0 && word.size() <= 15) {
            assert(dico3.containWord(word));
        }
    }
    std::cout << "Full dictionary test passes!\n";

    std::cout << "Dictionary test passes!\n";
}