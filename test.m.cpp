#include <iostream>
#include <memory>
#include <string>

#include <gtest/gtest.h>

#include "nodelist.h"
#include "randomstring.h"

bool operator==(NodeList const& lhs, NodeList const& rhs);
std::ostream & operator<<(std::ostream & os, NodeList const& n);

TEST(DeepCopyTest, example)
{
    // create and copy a node list like the one described in the example in the
    // assignment instructions.

    NodeList::node *A, *B, *C, *D, *E;

    for ( NodeList::node** i : {&A,&B,&C,&D,&E} )
    {
        *i = new NodeList::node;
        (*i)->element = randomString();
    }

    A->next = B;
    B->next = C;
    C->next = D;
    D->next = E;
    E->next = nullptr;

    A->random = E; // per email
    B->random = A; // per email
    C->random = E; // per email
    D->random = B; // not specified in email
    E->random = C; // not specified in email

    NodeList exampleList(A);

    // for visual inspection:
    std::cout << "original list:" << std::endl << exampleList << std::endl;

    NodeList deepCopy(exampleList);

    // for visual inspection:
    std::cout << "copy: " << std::endl << deepCopy << std::endl;

    ASSERT_TRUE( exampleList == deepCopy );
}

TEST(DeepCopyTest, emptyList)
{
    NodeList list(static_cast<size_t>(0)); // cast to avoid ambiguity w/ nullptr
    NodeList deepCopy(list);
    ASSERT_TRUE( list == deepCopy );
}

TEST(DeepCopyTest, oneElement)
{
    NodeList list(1);
    NodeList deepCopy(list);
    ASSERT_TRUE( list == deepCopy );
}

TEST(DeepCopyTest, aHundredElements)
{
    NodeList list(100);
    NodeList deepCopy(list);
    ASSERT_TRUE( list == deepCopy );
}

TEST(DeepCopyTest, aThousandElements)
{
    NodeList list(1000);
    NodeList deepCopy(list);
    ASSERT_TRUE( list == deepCopy );
}

std::ostream & operator<<(std::ostream & os, NodeList const& n)
{
    const NodeList::node* pn = n.head;
    do {
        os << "@" << pn << ":(element=" << pn->element << ",next=" << pn->next
            << ",random=" << pn->random << ")" << std::endl;
        pn = pn->next;
    } while (pn != nullptr);
    return os;
}

bool operator==(NodeList const& lhs, NodeList const& rhs)
{
    const NodeList::node *l = lhs.head,
                         *r = rhs.head;

    while ( (l==nullptr && r==nullptr)==false )
    {
        if ( l == nullptr || r == nullptr ) return false;
        if ( l->element != r->element ) return false;
        if ( l->random->element != r->random->element ) return false;
        l = l->next;
        r = r->next;
    }

    return true;
}

