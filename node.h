#ifndef NODE_H
#define NODE_H

#include <map>
#include <string>

struct node
{
    std::string element;
    node * next = nullptr;
    node * random = nullptr;
};

inline node* deepCopy(node* head)
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

#endif // NODE_H
