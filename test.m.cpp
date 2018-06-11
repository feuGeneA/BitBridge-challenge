#include <iostream>
#include <memory>
#include <string>

#include <gtest/gtest.h>

#include "listutil.h"
#include "node.h"
#include "randomstring.h"

bool operator==(node const& lhs, node const& rhs);
std::ostream & operator<<(std::ostream & os, node const& n);

class DeepCopyTestFixture : public ::testing::Test
{
protected:
    node *list = nullptr,
         *copy = nullptr;
    void TearDown()
    {
        if ( list != nullptr ) deleteList(list);
        if ( copy != nullptr ) deleteList(copy);
    }
};

TEST_F(DeepCopyTestFixture, example)
{
    // create and copy a node list like the one described in the example in the
    // assignment instructions.

    node A, B, C, D, E;

    for ( node* i : {&A,&B,&C,&D,&E} )
    {
        i->element = randomString();
    }

    A.next = &B;
    B.next = &C;
    C.next = &D;
    D.next = &E;
    E.next = nullptr;

    A.random = &E; // per email
    B.random = &A; // per email
    C.random = &E; // per email
    D.random = &B; // not specified in email
    E.random = &C; // not specified in email

    // for visual inspection:
    std::cout << "original list:" << std::endl << A << std::endl;

    // make a deep copy of the node list
    node* copy = deepCopy(&A);

    // for visual inspection:
    std::cout << "copy: " << std::endl << *copy << std::endl;

    ASSERT_TRUE( A == *copy );
}

TEST_F(DeepCopyTestFixture, emptyList)
{
    node *list = createList(0),
         *copy = deepCopy(list);
    ASSERT_TRUE( *list == *copy );
}

TEST_F(DeepCopyTestFixture, oneElement)
{
    node *list = createList(1),
         *copy = deepCopy(list);
    ASSERT_TRUE( *list == *copy );
}

TEST_F(DeepCopyTestFixture, aHundredElements)
{
    node *list = createList(100),
         *copy = deepCopy(list);
    ASSERT_TRUE( *list == *copy );
}

TEST_F(DeepCopyTestFixture, aThousandElements)
{
    node *list = createList(1000),
         *copy = deepCopy(list);
    ASSERT_TRUE( *list == *copy );
}

std::ostream & operator<<(std::ostream & os, node const& n)
{
    const node* pn = &n;
    do {
        os << "@" << pn << ":(element=" << pn->element << ",next=" << pn->next
            << ",random=" << pn->random << ")" << std::endl;
        pn = pn->next;
    } while (pn != nullptr);
    return os;
}

bool operator==(node const& lhs, node const& rhs)
{
    const node *l = &lhs,
               *r = &rhs;

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

