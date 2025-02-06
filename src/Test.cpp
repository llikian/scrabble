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
    std::cout << "Manual dictionary test passes!\n";

    //File insertion test
    Dictionary dico1("data/dico.txt");
    assert(dico1.containWord("aa"));
    assert(!dico1.containWord("aahjg"));
    assert(dico1.containWord("mutazilismes"));
    assert(!dico1.containWord("vhjidvu"));
    std::cout << "File dictionary test passes!\n";

    //GADAG insertion test
    Dictionary dico2;
    dico2.insertGADAGWord("anticonstitutionnellement");
    dico2.insertGADAGWord("abc");
    dico2.insertGADAGWord("fromage");
    assert(dico2.containWord("a+bc"));
    assert(dico2.containWord("cba+"));
    assert(dico2.containWord("f+romage"));
    assert(dico2.containWord("ennoitutitsnocitna+llement"));
    assert(!dico2.containWord("ab+c"));
    assert(!dico2.containWord("a"));
    assert(!dico2.containWord("abc"));
    std::cout << "Gadag dictionary test passes!\n";

    std::cout << "Dictionary test passes!\n";
}