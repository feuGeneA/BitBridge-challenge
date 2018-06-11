#ifndef LISTUTIL_H
#define LISTUTIL_H

#include <random>
#include <string>

#include "node.h"
#include "randomstring.h"

inline node* createList(size_t nElements)
{
    if ( nElements == 0 ) return nullptr;

    node* head = new node;
    head->element = randomString();

    node * n = head;
    for ( size_t i=0 ; i < nElements-1 ; i++ )
    {
        n->next = new node;
        n = n->next;
        n->element = randomString();
    }

    // set `random` fields
    n = head;
    std::uniform_int_distribution<size_t> randomElement(0, nElements-1);
    while ( n != nullptr )
    {
        static std::default_random_engine generator;
        size_t nThisRandom = randomElement(generator);
        node* pThisRandom = head;
        for ( size_t i=0 ; i < nThisRandom ; i++ )
        {
            pThisRandom = pThisRandom->next;
        }
        n->random = pThisRandom;
        n = n->next;
    }

    return head;
}

void deleteList(node* head)
{
    for ( node* p = head ; p != nullptr ; )
    {
        node* oldP = p;
        p = p->next;
        delete oldP;
    }
}

#endif // LISTUTIL_H
