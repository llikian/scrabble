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
    Dictionary dico;
    dico.insertWord("abc");
    assert(dico.root->children[0]->children[1]->children[2]->value == 'c');
    assert(dico.containWord("abc"));
    assert(!dico.containWord("a"));
    assert(!dico.containWord("abce"));
    assert(!dico.containWord("skibidi"));

    std::cout << "Dictionary test passes!\n";
}