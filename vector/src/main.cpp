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

	//Test c++11 initializer list syntax
	ls::Vector<std::string > strs{ "aa","ee", "ii", "oo", "uu"};

	assert( strs[2] == "ii");
	strs = { "aa", "bbb", "ccc", "dd"};
	assert( strs[2] == "ccc");
	
	//Test iterators
	v.reserve(20);
	auto v_it = v.begin();
	auto v2_begin = v2.begin();
	assert( *v_it == v[0]);
	assert( *v2_begin == v2[0]);
	assert( v_it != v2_begin);

	v_it++;
	assert( *v_it == v[1]);
	std::cout << "Inserting -10- before " << *v_it << " at position 1 = [";
	v_it = v.insert(v_it, 10); //Inserts before position 1
	ls::Vector<int>::iterator it = v.begin();
	for( /*empty*/; it != v.end(); ++it ){
		std::cout << *it << " ";
	}
	std::cout <<"]" << std::endl;

	//Test insert elements from range
	v3 = {1, 2, 3};
	it = v.begin();
	std::cout << "Inserting {1, 2, 3} before " << *it << " at 0 = [";
	v.insert(it, v3.begin(), v3.end());
	for( /*empty*/; it != v.end(); ++it ){
		std::cout << *it << " ";
	}
	std::cout << "]"<<std::endl;

	//Test insert elements from initializer list
	it = v.begin();
	it++;
	std::cout << "Inserting {11, 22, 33} before " << *it << " at 1 = [";
	v.insert(it, {11, 22, 33});
	it = v.begin();
	for( /*empty*/; it != v.end(); ++it ){
		std::cout << *it << " ";
	}
	std::cout <<"]"<< std::endl;
	
	std::cout << ">>>Normal exiting..." <<std::endl;
	return 0;
}
