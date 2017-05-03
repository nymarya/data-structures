#include "../include/vector.hpp"
#include <cassert>

int main(){

	ls::Vector<int> v(1);
	std::cout << "Size: " << v.size() << std::endl;


	v.push_front(1);
	v.push_front(2);
	v.print();
	v.pop_back();
	v.print();

	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_front(6);
	v.print();

	std::cout << v.at(1) << std::endl;
	std::cout << v[2] << std::endl;

	assert( v.capacity() == 8);
	v.reserve(20);
	assert( v.capacity() == 20);
	
	v.shrink_to_fit();
	assert( v.capacity() == 5);

	ls::Vector<int> v2(v);
	v2.print();

	v2.push_back(10);

	ls::Vector<int> v3;
	v3 = v2;

	v3.print();

	assert( v2 == v);


	return 0;
}