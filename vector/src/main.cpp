#include "../include/vector.hpp"
#include <cassert>

int main(){

	ls::Vector<int> v(1);
	//Test size()
	assert ( v.size() == 0);

	//Test push_front()
	v.push_front(1);
	v.push_front(2);
	
	//Test front() and pop_back()
	assert( v.front() == 2);
	assert( v.at(1) == 1);
	v.pop_back();

	//Test push_back()
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_front(6);

	
	assert( v.at(0) == 6);
	assert( v.at(1) == 2);

	//Test []
	assert( v[2] == 3 );

	//Test reserve()
	assert( v.capacity() == 8);
	v.reserve(20);
	assert( v.capacity() == 20);
	
	//Test shrink_to_fit()
	v.shrink_to_fit();
	assert( v.capacity() == 5);

	//Test copy constructor
	ls::Vector<int> v2(v);
	assert( v2 == v);

	v2.push_back(10);

	//Test constructor with the contents of the range [first, last)
	ls::Vector<int> v3(v.begin(), v.end() );
	assert( v3 == v );

	//Test copy assignment operator.
	v3 = v2;
	assert( v3 == v2 );

	//Test construtor initialize_list
	ls::Vector<std::string > strs{ "aa","ee", "ii", "oo", "uu"};

	std::cout << strs[0];
	std::cout << " " << strs[1];

	strs = { "aa", "bb"};

	std::cout << strs[0];
	std::cout << " " << strs[1];
	
	//Test iterators
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