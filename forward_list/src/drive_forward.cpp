#include "forward_list.h"

int main(){

    ls::ForwardList<int> fl;

    //Teste empty()
    assert( fl.empty() == true);

    //Teste push_front() e fornt()
    fl.push_front(4);
    assert(fl.front() == 4);
    fl.push_front(3);
    assert(fl.front() == 3);

    return 0;
}