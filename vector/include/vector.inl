#include "vector.hpp"
#include <stdexcept>

///////////////////////////
//  [I] SPECIAL MEMBERS  //
///////////////////////////

/* Construtor padrão */
template <typename T>
ls::Vector<T>::Vector(std::size_t size)
: m_data(new T[size])
, m_len(0)
, m_size(size)
{/*empty*/}

/* Constroi a lista com os elementos do intervalo [first, last). */
template<typename T>
template<typename InputIt >
ls::Vector<T>::Vector( InputIt first, InputIt last ){
	auto temp(first);
	//<! Guarda número de elementos no intervalo
	std::size_t distance(0ul);
	while( temp != last ){
		distance++; temp++;
	}

	//<! Aloca novo espaço na memória
	m_size = distance;
	m_len = m_size;
	m_data = new T[distance];

	//<! Copia os elementos do range para o novo vetor
	for ( auto i(0ul); i < distance; ++first, ++i)
		m_data[i] = *first;
	
}

/* Construtor cópia */
template <typename T>
ls::Vector<T>::Vector(const Vector& other )
	:m_data(new T[other.m_size])
	,m_len( other.m_len)
	,m_size(other.m_size)
{
	//<! Copia os elementos de um vetor para o outro
	for(auto i(0ul); i< m_size; ++i)
		m_data[i] =  other.m_data[i];
}

/* Constructs the list with the contents of the initializer list. */
template<typename T>
ls::Vector<T>::Vector( std::initializer_list<T> init )
: m_len( init.size() )
, m_size( init.size() )
{
	//<! Aloca novo espaço na memória
	m_data = new T[m_size];

	//<! Copia os elementos para a nova lista
	int count = 0;
	for (auto &e : init)
		m_data[count++] = e;
	
}

/* Destructor. */
template <typename T>
ls::Vector<T>::~Vector( ){
	delete [] m_data;
}

/* Operador de atribuição por cópia. */
template <typename T>
ls::Vector<T>& ls::Vector<T>::Vector::operator=( const Vector& other ){
	if (this == &other) return *this;

	delete [] m_data; //<! Remove a área de armazenamento antiga.

	//<! Aloca novo espaço na memória
	m_data = new T[other.m_size ];
	m_size = other.m_size;
	m_len  = other.m_len; 

	//<! Copia os elementos para a nova lista
	for(auto i(0ul); i < m_size; ++i)
		m_data[i] = other.m_data[i];

	return *this;
}

/* Substitui o conteúdo da lista pelos elementos de ilist.*/
template<typename T>
ls::Vector<T>& ls::Vector<T>::operator=( std::initializer_list<T> ilist ){
	delete [] m_data; //<! Remove área de armazenamento existente

	//<! Aloca nova area de armazenamento, atualiza tamanho e capacidade
	m_data = new T[ilist.size()];
	m_len = ilist.size();
	m_size = ilist.size();

	//<! Copia os elementos para a lista
	auto i(0);
	for (auto &e : ilist)
		m_data[i++] = e;	

	return *this;
}

///////////////////////////
//  [II] ITERATORS       //
///////////////////////////

/* Retorna terador que aponta para o começo do vetor. */
template <typename T>
typename ls::Vector<T>::iterator ls::Vector<T>::begin( void )
{ return ls::Vector<T>::iterator(&m_data[0]); }

/* Retorna iterador que aponta para o final do vetor. */
template <typename T>
ls::VectorIterator<T> ls::Vector<T>::end( void )
{ return ls::Vector<T>::iterator(&m_data[m_len]); }

/* Retorna iterador constante que aponta para o começo do vetor. */
template <typename T>
typename ls::Vector<T>::const_iterator ls::Vector<T>::cbegin( void ) const
{ return ls::Vector<T>::const_iterator(&m_data[0]); }

/* Retorna iterador constante que aponta para o final do vetor. */
template <typename T>
typename ls::Vector<T>::const_iterator ls::Vector<T>::cend( void ) const
{ return ls::Vector<T>::const_iterator(&m_data[m_len]); }

///////////////////////////
//  [III] CAPACITY       //
///////////////////////////

/* Retorna número de elementos da lista. */
template <typename T>
std::size_t ls::Vector<T>::size() const
{ return m_len; }

/* Retorna o tamanho físico da lista. */
template <typename T>
std::size_t ls::Vector<T>::capacity() const 
{ return m_size; }

/* Verifica se o vetor não tem elementos. */
template <typename T>
bool ls::Vector<T>::empty ()const
{ return (m_len == 0); }

/* Verifica se vetor está cheio. */
template <typename T>
bool ls::Vector<T>::full ()const
{ return (m_len == m_size); }

///////////////////////////
//  [IV] MODIFIERS       //
///////////////////////////

/* Insere elemento no final da lista. */
template <typename T>
void ls::Vector<T>::push_back(const T & value){
	//<! Realoca se a lista está cheia
	if( full() ) reserve( m_size * 2);

	//<! Insere elemento
	m_data[m_len++] = value;
}

/* Insere elemento no início da lista. */
template <typename T>
void ls::Vector<T>::push_front(const T & value){
	//<! Realoca se a lista está cheia
	if ( full() ) reserve( m_size * 2 );

	//<! Abre espaço para o novo elemento que será inserido
	std::copy(&m_data[0], &m_data[m_len], &m_data[1]);

	m_data[0] = value; //<! Insere valor
	m_len++;           //<! Atualiza tamanho
}

/* Adiciona valor value antes de pos. */
template <typename T>
typename ls::Vector<T>::iterator 
ls::Vector<T>::insert( iterator pos, const T & value ){
	//<! Guarda a posição do iterador
	auto position(0);
	for (auto i( begin() ); i != pos; ++i)
		position++;

	//<! Realoca se a lista está cheia
	if( full() ) reserve(m_size * 2 );

	//<! Abre espaço para o novo elemento que será inserido
	std::copy(&m_data[position], &m_data[m_len], &m_data[position+1]);
	
	m_data[position] = value; //<! Insere valor
	m_len++;      //<! Atualiza tamanho
	return pos;
}

/* Insere os elementos do intervalo [first; last) antes de pos. */
template<typename T>
template<typename InputItr>
ls::VectorIterator<T> ls::Vector<T>::insert( iterator pos, InputItr first, InputItr last){
	//!< Guarda o número de elementos entre first e last 
	auto sz(0ul);
	auto i(first);
	while(i != last){
		sz++; i++;
	}

	//<! Guarda a posição do iterador
	auto position(0ul);
	i = begin();
	while(i != pos){
		position++; i++;
	}

	//<! Realoca se o novo tamanho é maior que a capacidade
	if( m_len + sz > m_size ) reserve(m_len + sz);

	//<! Abre espaço para os novos elementos que serão inseridos
	std::copy(&m_data[position], &m_data[m_len], &m_data[sz]);

	//<! Insere os elementos do intervalo
	for( auto i(position); i < sz; ++i)
		m_data[i] = *first++;

	//<! Atualiza tamanho
	m_len += sz;
	return pos;
}

/* Insere elementos de std::initializer_list antes de pos. */
template<typename T>
ls::VectorIterator<T> ls::Vector<T>::insert( iterator pos, std::initializer_list<T> ilist ){
	//!< Guarda o número de elementos 
	auto sz = ilist.size();

	//<! Guarda a posição do iterador
	auto position(0ul);
	auto i(begin());
	while(i != pos){
		position++; i++;
	}

	//<! Realoca se o novo tamanho é maior que a capacidade
	if( m_len + sz > m_size ) reserve(m_len + sz);

	//<! Abre espaço para os novos elementos que serão inseridos
	std::copy(&m_data[position], &m_data[m_len], &m_data[position+sz]);

	//<! Insere os elemento de ilist
	for( auto &e: ilist)
		m_data[position++] = e;

	//<! Atualiza tamanho
	m_len += sz;
	return pos;
}

/* Remove o elemento na posição pos. */
template<typename T>
ls::VectorIterator<T> ls::Vector<T>::erase( iterator pos ){
	//<! Guarda a posição do item a ser removido
    auto position(0ul);
	for( auto i(begin()); i!= pos; ++i)
		position++;
	
	//<! Avança para o elemento posterior ao pos
	pos++;	

	//<! Sobrescreve o elemento
	std::copy(&m_data[position+1], &m_data[m_len], &m_data[position]);

	//<! Atualiza tamanho
	m_len--;
	return pos;
}

/* Remove os elementos no intervalo [first, last). */
template<typename T>
ls::VectorIterator<T> ls::Vector<T>::erase( iterator first, iterator last ){
	//<! Guarda a posição do primeiro item
    auto position(0ul);
	for( auto i(begin()); i!= first; ++i)
		position++;

	//<! Guarda o número de elementos entre first e last
    auto distance(0ul);
	for( auto i(first); i!= last; ++i)
		distance++;

	//<! Guarda a posição do elemento posterior ao que será removido
	auto pos = ++last;

	//<! Sobrescreve os elementos
	std::copy(&m_data[position+distance], &m_data[m_len], &m_data[position]);

	//<! Atualiza tamanho
	m_len -= distance;
	return pos;
}

/* Remove o elemento no final da lista. */
template <typename T>
T ls::Vector<T>::pop_back(){
	//<! Joga exceçao se lista está vazia
	if(empty())
		throw std::out_of_range("[pop_back()] Cannot recover element from an empty vector.");

	return m_data[--m_len];
}

/* Remove o elemento no início do array. */
template <typename T>
void ls::Vector<T>::pop_front (){
	//<! Joga exceçao se lista está vazia
	if(empty())
		throw std::out_of_range("[pop_back()] Cannot recover element from an empty vector.");

	//<! Remove o elemento
	for(auto i(0ul); i < m_len-1; ++i)
		m_data[i] = m_data[i+1];

	//<! Atualiza tamanho
	m_len--; 
}

/* Substitui o conteúdo da lista por cópias do valor 'value' */
template <typename T>
void ls::Vector<T>::assign( const T & value ){
	//<! Substitui o conteudo 
	for( auto i(0ul); i < m_size; ++i)
		m_data[i] = value;
}

/* Substitui o conteúdo da lista por cópias dos elementes no intervalo [first,last).*/
template <typename T>
template <typename InputItr>
void ls::Vector<T>::assign( InputItr first, InputItr last){
	//<! Guarda o numero de elementos entre first e last
	auto distance(0ul);
	for(auto i(first); i!= last; ++i)
		distance++;

	//<! Realoca se o novo tamanho é maior que a capacidade
	if(distance > m_size) reserve(distance);

	//<! Substitui o conteudo da lista
	for(auto i(0ul); i < distance ; ++i)
		m_data[i] = *(first++);

	//<! Atualiza tamanho
	m_len = distance;
}

/* Substitui o conteúdo da lista pelos elementos de ilist. */
template< typename T>
void ls::Vector<T>::assign( std::initializer_list<T> ilist ){
	//<! Guarda novo tamanho
	auto sz = ilist.size();

	//<! Realoca se o novo tamanho é maior que a capacidade
	if(sz > m_size) reserve(sz);

	//<! Substitui o conteudo da lista
	auto i(0);
	for(auto &e : ilist )
		m_data[i++] = e;

	//<! Atualiza tamanho
	m_len = sz;

}

/* Limpa vector. */
template <typename T>
void ls::Vector<T>::clear()
{ m_len = 0; }

/* Aumenta a capacidade de armazenamento da lista para um valor que é maior ou igual a new_cap. */
template <typename T>
void ls::Vector<T>::reserve( std::size_t new_cap ){
	if(new_cap > m_size){
		 //<! Aloca novo espaço na memória
		T *temp = new T[ new_cap ];

		//<! Copia os valores para a nova lista
		std::copy(m_data, m_data + new_cap, temp);

		delete m_data;    //<! Deleta espaço de armazenamento antigo

		m_data = temp;	  //<! Transfere o ponteiro para o novo endereço
		m_size = new_cap; //<! Atualiza tamanho
	}
}

/* Remove capacidade que não é utilizada. */
template <typename T>
void ls::Vector<T>::shrink_to_fit()
{ m_size = m_len; }

///////////////////////////
//  [V] ELEMENT ACCESS   //
///////////////////////////

/* Imprime vector. */
template <typename T>
void ls::Vector<T>::print( ) const{
	std::cout << ">>> [";
	std::copy( &m_data[0], &m_data[m_len], std::ostream_iterator<T>(std::cout, " "));

	std::cout << "], len=" << m_len << ", capacity=" << m_size <<".\n"; 
}

/* Recupera elemento na posição pos. */
template <typename T>
T & ls::Vector<T>::at( std::size_t pos) const{
	if( pos < 0 or pos >= m_len)
		throw std::out_of_range("[at()] Cannot recover element out of range.");

	return m_data[pos];
}

/* Retorna o objeto na posição pos. */
template <typename T>
T & ls::Vector<T>::operator[]( std::size_t pos) const
{ return m_data[pos]; }

/* Retorna primeiro elemento da lista. */
template <typename T>
T ls::Vector<T>::front() const{
	//<! Joga exceção se o vetor está vazio
	if(empty())
		throw std::out_of_range("[front()] Cannot recover element from an empty vector.");

	return m_data[0];
}

/* Retorna último elemento da lista. */
template <typename T>
T ls::Vector<T>::back() const {
	//<! Joga exceção se o vetor está vazio
	if(empty())
		throw std::out_of_range("[back()] Cannot recover element from an empty vector.");

	return m_data[m_len-1];
}

///////////////////////////
//  [V] OPERATORS        //
///////////////////////////

/* Checa se os conteúdos de lhs e rhs são iguais.*/
template <typename T>
bool operator==( const ls::Vector<T>& lhs, const ls::Vector<T>& rhs ){
	//<! Checa o número de elementos
	if( lhs.size() != rhs.size() ) return false;
	else{
		//<! Verifica se todos os elementos são iguais
		for ( auto i(0ul); i < rhs.size(); ++i)
			if( rhs[i] != lhs[i] ) return false;
	}

	return true;
}

/* Verifica se os conteúdos de lhs e rhs são iguais.*/
template <typename T>
bool operator!=( const ls::Vector<T>& lhs, const ls::Vector<T>& rhs ){
	//<! Checa o número de elementos
	if( lhs.size() != rhs.size() ) return true;
	else{
		//<! Verifica se há algum elemento diferente
		for ( auto i(0ul); i < rhs.size(); ++i)
			if( rhs[i] != lhs[i] ) return true;
	}

	return false;
}

///////////////////////////
//  VECTORITERATOR CLASS //
///////////////////////////

/* Construtor padrão para classe iterator. */
template <typename T>
ls::VectorIterator<T>::VectorIterator(T * current)
: m_current( current)
{ /*empty*/ }

/* Retorna uma referência para o objeto lozalizado na posição apontada pelo iterador */
template <typename T>
T& ls::VectorIterator<T>::operator*() const {
	assert( m_current != nullptr); 				
	return *m_current;
}

/* Avança iterador para a próxima posição na lista. (++it)*/
template <typename T>
ls::VectorIterator<T>& ls::VectorIterator<T>::operator++() {
	m_current++;				
	return *this;
}

/* Avança iterador para a próxima posição na lista. (it++) */
template <typename T>
ls::VectorIterator<T> ls::VectorIterator<T>::operator++(int) {
	typename ls::Vector<T>::iterator temp = *this; 			
	m_current++; 				
	return temp;
}

/* Move iterador para a posição anterior na lista. (--it) */
template <typename T>
ls::VectorIterator<T>& ls::VectorIterator<T>::operator--() {
	m_current--;				
	return *this;
}

/* Move iterador para a posição anterior na lista. (it--) */
template <typename T>
ls::VectorIterator<T> ls::VectorIterator<T>::operator--(int) {
	typename ls::Vector<T>::iterator temp = *this; 			
	m_current--; 				
	return temp;
}

/* Retorna verdadeiro se os iteradores fazem referência para o mesmo ponto da lista. */
template <typename T>
bool ls::VectorIterator<T>::operator==( const typename ls::VectorIterator<T> & rhs ) const{
	return m_current == rhs.m_current;
}

/* Retorna verdadeiro se os iteradores fazem referência para pontos diferentes da lista. */
template <typename T>
bool  ls::VectorIterator<T>::operator!=( const typename ls::VectorIterator<T> & rhs ) const{
	return m_current != rhs.m_current;
}