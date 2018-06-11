Deep copy of a
    struct node
    {
        std::string element;
        node * next;
        node * random;
    };
implemented in nodelist.h:NodeList(NodeList const&), tested in test.m.cpp, and
benchmarked in benchmark.m.cpp.

Algorithm:

First, do a simple deep copy of the linked list, following `next` pointers.
Along the way, though, populate a std::map which maps addresses of nodes in the
old linked list to addresses of corresponding nodes in the duplicate list.

Then, after copying all the nodes and initializing their `next` pointers, go
back and fix up the `random` pointers in the duplicate list.  Specifically,
simultaneously iterate through both the original and duplicate lists, by
following the next pointers; in each iteration, set the duplicate node's
`random` field to the map value stored at the key equal to the original node's
`random` address.

The runtime complexity is O(n*log n).  The initial copy of just `next` elements
is O(n), and the map insertions add up to be O(log 0)+O(log 1)+...+O(log n),
which collapses to just O(log n), so the initial stage, of just
copy-following-`next`, is O(n*log n).  Similarly, the final stage, of setting
the `random` pointers, requires a O(log n) map search for each element in the
list of n elements, yielding O(n*log n).  So overall, the process is O(2*(n*log
n)), or, simplified, O(n*log n).  More specifically, benchmarking revealed that
the runtime complexity is approximately O(575*n*log(n)+1114).
