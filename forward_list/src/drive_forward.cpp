#include "forward_list.h"
#include <vector>

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

    //teste iterator
    ls::ForwardList<int>::iterator it = fl.begin();

    auto i(3);
    while( it != fl.end() ){
    	fl.push_front(--i);
    	++it;
    }
	assert(fl.size() == 4);

    //teste insert()
    it = fl.begin();
    it+=1;
    fl.insert(it, 10);
    assert(fl.size() == 5);

    std::cout << ">>> Inserindo 10 após {" << *it<< "} = [";
    it = fl.begin();
    while( it != fl.end() ){
    	std::cout << *it++ << " ";
    }
	std::cout << "]"<< std::endl;

	//teste insert() com intervalo [first, last)
	std::vector<int> array = {11, 22, 33};
	it = fl.begin();
    it+=2;
    fl.insert(it, array.begin(), array.end());
    assert(fl.size() == 8);
    std::cout << ">>> Inserindo {11, 22, 33} após {" << *it<< "} = [";
    it = fl.begin();
    while( it != fl.end() ){
    	std::cout << *it++ << " ";
    }
	std::cout << "]"<< std::endl;


    return 0;
}