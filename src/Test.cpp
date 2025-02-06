//
// Created by Foyeur on 06/02/2025.
//

#include "Test.hpp"
#include "Dictionary.hpp"

#include <cassert>
#include <iostream>

void testAll() {
    testDictionary();
    std::cout << "Test passes!\n";
}

void testDictionary()
{
    //Manual insertion test
    Dictionary dico;
    dico.insertWord("abc");
    assert(dico.root->children[0]->children[1]->children[2]->value == 'c');
    assert(dico.containWord("abc"));
    assert(!dico.containWord("a"));
    assert(!dico.containWord("abce"));
    assert(!dico.containWord("skibidi"));

    //File insertion test
    Dictionary dico1("data/dico.txt");
    assert(dico1.containWord("aa"));
    assert(!dico1.containWord("aahjg"));
    assert(dico1.containWord("mutazilismes"));
    assert(!dico1.containWord("vhjidvu"));

    std::cout << "Dictionary test passes!\n";
}