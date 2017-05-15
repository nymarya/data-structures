#include "../include/vector.hpp"
#include <cassert>
#include <vector>

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

	//ls::Vector<int> v3;
	//v3 = v2;

	//assert( (v2 != v3) == false );

	ls::Vector<int> v4(v2.begin(), v2.end() );
	assert( v4 == v2 );
	
	auto v_begin = v.begin();
	auto v2_begin = v2.begin();
	assert( *v_begin == v[0]);
	assert( *v2_begin == v2[0]);
	assert( v_begin != v2_begin);

	v_begin++;
	assert( *v_begin == v[1]);

	v.insert(v_begin, 10);
	for( auto i( v.begin() ); i!= v.end(); ++i ){
		std::cout << *i << " ";
	}
	std::cout << std::endl;
	
	std::cout << ">>>Normal exiting..." <<std::endl;
	return 0;
}