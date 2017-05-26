#include "forward_list.h"

int main(){

    ls::ForwardList<int> fl;

    //Teste empty()
    assert( fl.empty() == true);

    //Teste push_back() e forn()
    fl.push_back(5);
    assert(fl.front() == 5);
    fl.push_back(6);
    assert(fl.back() == 6);

    //Teste push_front() e fornt()
    fl.push_front(4);
    assert(fl.front() == 4);
    fl.push_front(3);
    assert(fl.front() == 3);

    return 0;
}