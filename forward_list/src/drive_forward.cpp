#include "forward_list.h"

int main(){

    ls::ForwardList<int> fl;

    //Teste empty()
    assert( fl.empty() == true);

    //Teste push_back() e back()
    fl.push_back(5);
    assert(fl.front() == 5);
    fl.push_back(6);
    assert(fl.back() == 6);

    //Teste push_front() e front()
    fl.push_front(4);
    assert(fl.front() == 4);
    fl.push_front(3);
    assert(fl.front() == 3);

    //Teste size()
    assert(fl.size() == 4);

    //Teste pop_front()
    fl.pop_front();
    assert(fl.front() == 4);
    assert(fl.size() == 3);

    //Teste pop_back()
    fl.pop_back();
    assert(fl.back() == 5);
    assert(fl.size() == 2);


    return 0;
}