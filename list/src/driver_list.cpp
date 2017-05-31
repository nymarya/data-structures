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
    ls::List<int>::const_iterator it = ll.cbegin();
    auto v = ll.insert(it, 10);
    assert( ll.size() == 2);
    assert( ll.front() == *v);

    //teste push_back() e back()
    ll.push_back(2);
    assert( ll.size() == 3);
    assert(ll.back() == 2);
    ll.push_back(3);
    ll.push_back(4);
    ll.push_back(5);
    assert(ll.size() == 6);
    assert( ll.back() == 5);

    //Teste pop_front() 
    ll.pop_front();
    assert( ll.front() == 1);

    //Teste pop_back()
    ll.pop_back();
    assert( ll.back() == 4);

    //Teste clear()
    ll.clear();
    assert( ll.empty());

    //teste construtor com count
    ls::List<int> n_list(8);
    assert( n_list.size() == 8);

    //Teste construtor com intervalo
    ls::List<int> cp_list( n_list.begin(), n_list.end() );
    assert(cp_list == n_list);

    std::cout << ">>>Testes realizados com sucesso!\n";

    return EXIT_SUCCESS;
}