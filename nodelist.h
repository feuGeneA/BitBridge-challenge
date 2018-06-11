#ifndef NODELIST_H
#define NODELIST_H

#include <random>
#include <string>

#include "randomstring.h"

struct NodeList
{
    struct node
    {
        std::string element;
        node * next = nullptr;
        node * random = nullptr;
    };

    static node* deepCopy(node* head)
    {
        if ( head == nullptr ) return nullptr;

        std::map<node*, node*> oldToNew;

        node* newHead = new node;
        oldToNew[head] = newHead;
        newHead->element = head->element;

        node *iterOld = head->next,
             *iterNew = newHead;
        while ( iterOld != nullptr )
        {
            iterNew->next = new node;
            iterNew->next->element = iterOld->element;

            oldToNew[iterOld] = iterNew->next;

            iterOld = iterOld->next;
            iterNew = iterNew->next;
        }
        iterNew->next = nullptr;

        iterOld = head;
        iterNew = newHead;
        while ( iterOld != nullptr )
        {
            iterNew->random = oldToNew[iterOld->random];
            iterOld = iterOld->next;
            iterNew = iterNew->next;
        }

        return newHead;
    }

    NodeList(NodeList const& source)
        : head(nullptr)
    {
        head = deepCopy(source.head);
    }

    node * head;

    // construct a new list of `nElements` elements, assigning a random string
    // to each `element` field, and randomly initializing each `random` field.
    NodeList(size_t nElements)
        : head(new node)
    {
        if ( nElements == 0 ) { head = nullptr; return; }

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
    }

    // receive a manually constructed list of nodes, and assume responsibility
    // for deleting its elements.
    NodeList(node* h) : head(h) {}

    ~NodeList()
    {
        for ( node* p = head ; p != nullptr ; )
        {
            node* oldP = p;
            p = p->next;
            delete oldP;
        }
    }
};

#endif // NODELIST_H
