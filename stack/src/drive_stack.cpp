#include "../include/stack.hpp"
#include <cassert>

int main(){

    Stack<int> v;

    v.push(4);

    assert( v.top() == 4);

    try{
		 v.pop();
	}
	catch(const std::length_error &e){
		
		std::cout << ">> Error: " << e.what() << std::endl;
	}

    assert( v.top() == 0);

    try{
		 v.pop();
	}
	catch(const std::length_error &e){
		
		std::cout << ">> Error: " << e.what() << std::endl;
	}

    return EXIT_SUCCESS;

}