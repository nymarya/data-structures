#include "list.h"
#include <cassert>

int main(){

    ls::List<int> ll;

    //teste size() e empty()
    assert(ll.size() == 0);
    assert(ll.empty() );

    //teste construtor com count
    ls::List<int> n_list(8);
    assert( n_list.size() == 8);


    return 0;
}