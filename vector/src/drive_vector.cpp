#include "../include/vector.hpp"
#include <cassert>

int main(){

	ls::Vector<int> v(1);
	//Teste size()
	assert ( v.size() == 0);

	//Teste push_front()
	v.push_front(1);
	v.push_front(2);
	
	//Teste front() e pop_back()
	assert( v.front() == 2);
	assert( v.at(1) == 1);
	v.pop_back();

	//Teste push_back()
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_front(6);

	assert( v.at(0) == 6);
	assert( v.at(1) == 2);

	//Teste []
	assert( v[2] == 3 );

	//Teste reserve()
	assert( v.capacity() == 8);
	v.reserve(20);
	assert( v.capacity() == 20);
	
	//Teste shrink_to_fit()
	v.shrink_to_fit();
	assert( v.capacity() == 5);

	//Teste construtor copia
	ls::Vector<int> v2(v);
	assert( v2 == v);

	v2.push_back(10);

	//Teste construtor com intervalo
	ls::Vector<int> v3(v.begin(), v.end() );
	assert( v3 == v );

	//Teste operador de substituição por copia.
	v3 = v2;
	assert( v3 == v2 );

	//Teste c++11 initializer list syntax
	ls::Vector<std::string > strs{ "aa","ee", "ii", "oo", "uu"};

	assert( strs[2] == "ii");
	strs = { "aa", "bbb", "ccc", "dd"};
	assert( strs[2] == "ccc");
	
	//Teste iteradores
	v.reserve(20);
	auto v_it = v.begin();
	auto v2_begin = v2.begin();
	assert( *v_it == v[0]);
	assert( *v2_begin == v2[0]);
	assert( v_it != v2_begin);

	v_it++;
	assert( *v_it == v[1]);
	std::cout << "Inserindo [10] antes de [" << *v_it << "] na posição 1 = [";
	v_it = v.insert(v_it, 10); //Insere antes da posição 1
	ls::Vector<int>::iterator it = v.begin();
	for( /*empty*/; it != v.end(); ++it ){
		std::cout << *it << " ";
	}
	std::cout <<"]" << std::endl;

	//Teste insert com intervalo
	v3 = {16, 26, 36};
	it = v.begin();
	std::cout << "Inserindo {16, 26, 36} antes de " << *it << " em 0 = [";
	v.insert(it, v3.begin(), v3.end());
	for( /*empty*/; it != v.end(); ++it ){
		std::cout << *it << " ";
	}
	std::cout << "]"<<std::endl;

	//Teste insert com initializer list
	it = v.begin();
	it++;
	std::cout << "Inserindo {11, 22, 33} antes de " << *it << " em 1 = [";
	v.insert(it, {11, 22, 33});
	it = v.begin();
	for( /*empty*/; it != v.end(); ++it ){
		std::cout << *it << " ";
	}
	std::cout <<"]"<< std::endl;

	//Teste erase
	it--;
	it--;
	ls::Vector<int>::iterator result = v.erase(it);
	assert(*result == 5);

	//Teste erase com intervalo
	it--;
	it--;
	auto iterat = v.begin();
	std::cout << "Removendo ["<<*(++iterat) << ", "<< *it << ") = [";
	result = v.erase(iterat, it);
	assert( v.size() == 4 );
	it = v.begin();
	for( /*empty*/; it != v.end(); ++it ){
		std::cout << *it << " ";
	}
	std::cout <<"]"<< std::endl;

	//Test assign with input iterator
	v2.assign(v3.begin(), v3.end());
	it = v2.begin();
	std::cout << "Substituindo v2 por v3{16, 26, 36}, V = [";
	for( /*empty*/; it != v2.end(); ++it ){
		std::cout << *it << " ";
	}
	std::cout <<"]"<< std::endl;

	//Teste assign com initialize list
	v2.assign({123, 132, 321, 231});
	it = v2.begin();
	std::cout << "Substituindo v2 por {123, 132, 321, 231}, V = [";
	for( /*empty*/; it != v2.end(); ++it ){
		std::cout << *it << " ";
	}
	std::cout <<"]"<< std::endl;

	
	std::cout << "\n>>>Saindo..." <<std::endl;
	return 0;
}
