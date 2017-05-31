#include "list.h"
#include <cassert>

int main(){

    ls::List<int> ll;

    //teste size() e empty()
    assert(ll.size() == 0);
    assert(ll.empty() );

    //teste push_front() e front()-
    ll.push_front(1);
    assert(ll.size() == 1);
    assert(ll.front() == 1);

    //Teste insert()
    ls::List<int>::iterator it = ll.begin();
    auto v = ll.insert(it, 10);
    assert( ll.size() == 2);
    assert( ll.front() == *v);

    //teste construtor com count
    ls::List<int> n_list(8);
    assert( n_list.size() == 8);


    return 0;
}