#include "vector.hpp"
#include <stdexcept>

///////////////////////////
//  [I] SPECIAL MEMBERS  //
///////////////////////////

/* Default constructor */;
template <typename T>
ls::Vector<T>::Vector(std::size_t size)
: m_data(new T[size + 1]) //<! Posição extra para end()
, m_len(0)
, m_size(size)
{/*empty*/}

/* Copy constructor. */
template <typename T>
ls::Vector<T>::Vector(const Vector& other )
	:m_data(new T[other.m_size])
	,m_len( other.m_len)
	,m_size(other.m_size)
{

	for(auto i(0ul); i< m_size; ++i)
		m_data[i] =  other.m_data[i] ;
}

/* Destructor. */
template <typename T>
ls::Vector<T>::~Vector( ){
	delete [] m_data;
}

/* Copy assignment operator. */
template <typename T>
ls::Vector<T>& ls::Vector<T>::Vector::operator=( const Vector& other ){
	if (this == &other) return *this;

	delete [] m_data; //<! Deallocate any previous value

	m_data = new T[other.m_size ];
	m_size = other.m_size;
	m_len  = other.m_len; 

	//<! Copy values from other to this
	for(auto i(0ul); i < m_size; ++i)
		m_data[i] = other.m_data[i];

	return *this;
}

///////////////////////////
//  [II] ITERATORS       //
///////////////////////////

/* Returns an iterator pointing to the first item in the list. */
template <typename T>
typename ls::Vector<T>::iterator ls::Vector<T>::begin( void )
{ return ls::Vector<T>::iterator(&m_data[0]); }

/* Returns an iterator pointing to the end mark in the list. */
template <typename T>
typename ls::Vector<T>::iterator ls::Vector<T>::end( void )
{ return ls::Vector<T>::iterator(&m_data[m_len]); }

/* Returns a constant iterator pointing to the first item in the list. */
template <typename T>
typename ls::Vector<T>::const_iterator ls::Vector<T>::cbegin( void ) const
{ return ls::Vector<T>::const_iterator(&m_data[0]); }

/* Returns a constant iterator pointing to the end mark in the list. */
template <typename T>
typename ls::Vector<T>::const_iterator ls::Vector<T>::cend( void ) const
{ return ls::Vector<T>::const_iterator(&m_data[m_len]); }

///////////////////////////
//  [III] CAPACITY       //
///////////////////////////

/* Return number of elements of array. */
template <typename T>
std::size_t ls::Vector<T>::size() const
{ return m_len; }

/* Return the actual size of array. */
template <typename T>
std::size_t ls::Vector<T>::capacity() const 
{ return m_size; }

/* Returns true is vector has no elements. */
template <typename T>
bool ls::Vector<T>::empty ()const
{ return (m_len == 0); }

/* Returns true if vector is full. */
template <typename T>
bool ls::Vector<T>::full ()const
{ return (m_len == m_size); }

///////////////////////////
//  [IV] MODIFIERS       //
///////////////////////////

/* Inserts element at the end of the array. */
template <typename T>
void ls::Vector<T>::push_back(const T & value){
	if( full() ) reserve( m_size * 2);

	m_data[m_len++] = value;
}

/* Inserts element at the beginning of the array. */
template <typename T>
void ls::Vector<T>::push_front(const T & value){
	if ( full() ) reserve( m_size * 2 );

	for ( auto i(m_len+1); i > 0; --i)
		m_data[i] =  m_data[i-1];

	m_data[0] = value;
	m_len++;
}

/* Removes the element at the end of the array. */
template <typename T>
T ls::Vector<T>::pop_back(){
	if(empty())
		throw std::out_of_range("[pop_back()] Cannot recover element from an empty vector.");

	return m_data[--m_len];
}

/* Removes the element at the beginning of the array. */
template <typename T>
void ls::Vector<T>::pop_front (){
	if(empty())
		throw std::out_of_range("[pop_back()] Cannot recover element from an empty vector.");

	for(auto i(0ul); i < m_len-1; ++i)
		m_data[i] = m_data[i+1];

	m_len--;
}

/* Replaces the content of the list with copies of value 'value' */
template <typename T>
void ls::Vector<T>::assign( const T & value ){
	for( auto i(0ul); i < m_size; ++i)
		m_data[i] = value;
}

/* Clear vector. */
template <typename T>
void ls::Vector<T>::clear()
{ m_len = 0; }

/* Increase the storage capacity of the array to a value that’s is greater or equal to new_cap. */
template <typename T>
void ls::Vector<T>::reserve( std::size_t new_cap ){
	if(new_cap > m_size){
		T *temp = new T[ new_cap ]; //Novo vetor

		std::copy(m_data, m_data + new_cap, temp);  //Copia para novo vetor

		delete m_data;

		m_data = temp;							//Aponta para o novo endereço
		m_size = new_cap; //Atualizar tamanho;
	}
}

/* Requests the removal of unused capacity. */
template <typename T>
void ls::Vector<T>::shrink_to_fit()
{ m_size = m_len; }

///////////////////////////
//  [V] ELEMENT ACCESS   //
///////////////////////////

/* Prints vector. */
template <typename T>
void ls::Vector<T>::print( ) const{
	std::cout << ">>> [";
	std::copy( &m_data[0], &m_data[m_len], std::ostream_iterator<T>(std::cout, " "));

	std::cout << "], len=" << m_len << ", capacity=" << m_size <<".\n"; 
}

/* Gets element at some position. */
template <typename T>
T & ls::Vector<T>::at( std::size_t pos) const{
	if( pos < 0 or pos >= m_len)
		throw std::out_of_range("[at()] Cannot recover element out of range.");

	return m_data[pos];
}

/* Returns the object at the position pos. */
template <typename T>
T & ls::Vector<T>::operator[]( std::size_t pos) const
{ return m_data[pos]; }

/* Returns first element of the array. */
template <typename T>
T ls::Vector<T>::front() const{
	if(empty())
		throw std::out_of_range("[front()] Cannot recover element from an empty vector.");

	return m_data[0];
}

/* Returns last element of the array. */
template <typename T>
T ls::Vector<T>::back() const {
	if(empty())
		throw std::out_of_range("[back()] Cannot recover element from an empty vector.");

	return m_data[m_len-1];
}

///////////////////////////
//  [V] OPERATORS        //
///////////////////////////

/* Checks if the contents of lhs and rhs are equal.*/
template <typename T>
bool operator==( const ls::Vector<T>& lhs, const ls::Vector<T>& rhs ){
	if( lhs.size() != rhs.size() ) return false;
	else{
		for ( auto i(0ul); i < rhs.size(); ++i)
			if( rhs[i] != lhs[i] ) return false;
	}

	return true;
}

/* Checks if the contents of lhs and rhs are different.*/
template <typename T>
bool operator!=( const ls::Vector<T>& lhs, const ls::Vector<T>& rhs ){
	if( lhs.size() != rhs.size() ) return true;
	else{
		for ( auto i(0ul); i < rhs.size(); ++i)
			if( rhs[i] != lhs[i] ) return true;
	}

	return false;
}

///////////////////////////
//  [VI] VECTORITERATOR  //
///////////////////////////

/*Default constructor for iterator class*/
template <typename T>
ls::Vector<T>::iterator::VectorIterator(T * current)
: m_current( current)
{ /*empty*/ }

/* Returns a reference to the object located at the position pointed by the iterator */
template <typename T>
 T& ls::Vector<T>::iterator::operator*() const {
	assert( m_current != nullptr); 				
	return *m_current;
}

/* Advances iterator to the next location within the list. */
template <typename T>
typename ls::Vector<T>::iterator& ls::Vector<T>::iterator::operator++() {
	m_current++;				
	return *this;
}

/* Advances iterator to the next location within the list. (it++) */
template <typename T>
typename ls::Vector<T>::iterator ls::Vector<T>::iterator::operator++(int) {
	ls::Vector<T>::iterator temp = *this; 			
	m_current++; 				
	return temp;
}

/* Advances iterator to the next location within the list. (--it) */
template <typename T>
typename ls::Vector<T>::iterator& ls::Vector<T>::iterator::operator--() {
	m_current--;				
	return *this;
}

/* Advances iterator to the next location within the list. (it--) */
template <typename T>
typename ls::Vector<T>::iterator ls::Vector<T>::iterator::operator--(int) {
	ls::Vector<T>::iterator temp = *this; 			
	m_current--; 				
	return temp;
}

/* Returns true if both iterators refer to the same location within the list, 
 * and false otherwise. */
template <typename T>
bool ls::Vector<T>::iterator::operator==( const ls::Vector<T>::iterator & rhs ) const{
	return m_current == rhs.m_current;
}

/* Returns true if both iterators refer to the different location within the list, 
 * and false otherwise. */
template <typename T>
bool  ls::Vector<T>::iterator::operator!=( const  ls::Vector<T>::iterator & rhs ) const{
	return m_current != rhs.m_current;
}