#include "list.h"
#include <cassert>
#include <vector>

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

    //Teste assign()
    n_list.assign(4);
    ls::List<int>::const_iterator itc = n_list.cbegin();
    while( itc != n_list.cend()){
        assert(*itc++ == 4);
    }

    //Teste construtor cópia
    ls::List<int> cpy( n_list );
    assert( cpy == n_list );

    //Teste construtor com initializer list
    ls::List< std::string > strs {"aa", "ee", "ii", "oo"};
    assert( strs.size() == 4);

    //Teste assign() com intervalo
    std::vector<std::string> anoes = { "atchim", "dunga", "feliz", "mestre", "zangado", "soneca", "dengoso"};
    strs.assign( anoes.begin(), anoes.end());
    auto i(0);
    for( auto it( strs.cbegin() ); it != strs.cend(); ++it )
        assert( *it == anoes[i++]);

    //Teste assign() com initializer lis
    ll.assign({1, 2, 3, 4, 5, 6, 7});
    assert( ll.size() == 7 );
    i = 1;
    for( auto it( ll.cbegin() ); it != ll.cend(); ++it )
        assert( *it == i++);

    //Teste operador de atribuição por copia
    n_list = ll;
    assert( n_list == ll);

    ls::List<int> fib;
    fib = {1, 1, 2, 3, 5, 8, 13, 21};
    ls::List<int>::const_iterator bg = fib.cbegin();
    auto a = bg;
    auto b = bg;
    b+=1;
    bg+=2;
    while( bg != fib.cend() ){
        assert(*a++ + *b++ == *bg++);
    }

    //Teste insert() com intervalo
    std::cout << "Lista original = [";
    for( auto it( ll.begin() ); it != ll.end(); ++it)
        std::cout << *it << " ";
    std::cout << "]\n\n";


    it = ll.begin();
    bg = fib.cbegin();
    bg+=5; 
    ll.insert( it+=3, bg, fib.cend() );
    std::cout << "Inserindo {8, 13, 21} antes de "<< *it << " = [";
    for( auto it( ll.begin() ); it != ll.end(); ++it)
        std::cout << *it << " ";
    std::cout << "]\n";

    //Teste insert() com initializer list
    ll.insert( it+=3, {22, 33, 44} );
    std::cout << "Inserindo {22, 33, 44} antes de "<< *it << " = [";
    for( auto it( ll.begin() ); it != ll.end(); ++it)
        std::cout << *it << " ";
    std::cout << "]\n";

    //Teste remove() com intervalo
    auto first( ll.begin() );
    auto last( ll.begin() );
    ll.erase( first+=1,last+=4);
    std::cout << "Removendo ["<< *first <<", "<< *last<<") = [";
    for( auto it( ll.begin() ); it != ll.end(); ++it)
        std::cout << *it << " ";
    std::cout << "]\n";



    std::cout << ">>>Testes realizados com sucesso!\n";

    return EXIT_SUCCESS;
}