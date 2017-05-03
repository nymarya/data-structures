#include "../include/vector.hpp"
#include <cassert>

int main(){

	ls::Vector<int> v(1);
	assert ( v.size() == 0);


	v.push_front(1);
	v.push_front(2);
	
	assert( v.front() == 2);
	assert( v.at(1) == 1);
	v.pop_back();

	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_front(6);

	assert( v.at(0) == 6);
	assert( v.at(1) == 2);
	assert( v[2] == 3 );

	assert( v.capacity() == 8);
	v.reserve(20);
	assert( v.capacity() == 20);
	
	v.shrink_to_fit();
	assert( v.capacity() == 5);

	ls::Vector<int> v2(v);
	assert( v2 == v);

	v2.push_back(10);

	ls::Vector<int> v3;
	v3 = v2;

	assert( v2 == v3);


	return 0;
}