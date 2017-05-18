#include "vector.hpp"
#include <stdexcept>

///////////////////////////
//  [I] SPECIAL MEMBERS  //
///////////////////////////

/* Default constructor */;
template <typename T>
ls::Vector<T>::Vector(std::size_t size)
: m_data(new T[size])
, m_len(0)
, m_size(size)
{/*empty*/}

/* Constructs the list with the contents of the range [first, last). */
template<typename T>
template<typename InputIt >
ls::Vector<T>::Vector( InputIt first, InputIt last ){
	auto temp(first);
	//<! Get distance
	std::size_t distance(0ul);
	while( temp != last ){
		distance++; temp++;
	}

	//<! Creates new storage area
	m_size = distance;
	m_len = m_size;
	m_data = new T[distance];

	//Copia os elementos do range para o novo vetor
	for ( auto i(0ul); i < distance; ++first, ++i){
		m_data[i] = *first;
	}
}

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

/* Constructs the list with the contents of the initializer list. */
template<typename T>
ls::Vector<T>::Vector( std::initializer_list<T> init )
: m_len( init.size() )
, m_size( init.size() )
{
	//<! Creates new vector
	m_data = new T[m_size];

	//<! Backups the data into the new vector
	int count = 0;
	for (auto &e : init)
	{
		m_data[count++] = e;
	}
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

	delete [] m_data; //<! Delete the old storage area.

	//<! Creates new storage area
	m_data = new T[other.m_size ];
	m_size = other.m_size;
	m_len  = other.m_len; 

	//<! Backups the data into the new vector
	for(auto i(0ul); i < m_size; ++i)
		m_data[i] = other.m_data[i];

	return *this;
}

/* Replaces the contents with those identified by initializer list.*/
template<typename T>
ls::Vector<T>& ls::Vector<T>::operator=( std::initializer_list<T> ilist ){
	delete [] m_data; //<! Delete the old storage area

	//<! Updates logical and actual size
	m_data = new T[ilist.size()];
	m_len = ilist.size();
	m_size = ilist.size();

	//<! Backups the data into the new vector
	auto i(0);
	for (auto &e : ilist)
		m_data[i++] = e;	

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
ls::VectorIterator<T> ls::Vector<T>::end( void )
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

	m_data[0] = value; //<! Inserts value
	m_len++;           //<! Update size
}

/* Adds value into the list before the position given by the iterator pos. */
template <typename T>
typename ls::Vector<T>::iterator 
ls::Vector<T>::insert( iterator pos, const T & value ){
	//<! Counting how many elements to move
	auto position(0);
	for (auto i( begin() ); i != pos; ++i)
		position++;

	//<! Duplicate size if vector is full
	if( full() ) reserve(m_size * 2 );

	//<! Backups the data
	std::copy(&m_data[position], &m_data[m_len], &m_data[position+1]);
	
	m_data[position] = value; //<! Inserts values
	m_len++;      //<! Updates size
	return pos;
}

/* Inserts elements from the range [first; last) before pos. */
template<typename T>
template<typename InputItr>
ls::VectorIterator<T> ls::Vector<T>::insert( iterator pos, InputItr first, InputItr last){
	//!< Get distance 
	auto distance(0ul);
	auto i(first);
	while(i != last){
		distance++; i++;
	}

	//<! Get position
	auto position(0ul);
	i = begin();
	while(i != pos){
		position++; i++;
	}

	//<! Reallocate if new size is greater than capacity
	if( m_len + distance > m_size ) reserve(m_len + distance);
	//<! Backups data
	std::copy(&m_data[position], &m_data[m_len], &m_data[distance]);

	//<! Inserts elements from the range
	for( auto i(position); i < distance; ++i)
		m_data[i] = *first++;

	//<! Updates size
	m_len += distance;
	return pos;
}

/* Inserts elements from the initializer list before pos. */
template<typename T>
ls::VectorIterator<T> ls::Vector<T>::insert( iterator pos, std::initializer_list<T> ilist ){
	//!< Get distance 
	auto distance = ilist.size();

	//<! Get position
	auto position(0ul);
	auto i(begin());
	while(i != pos){
		position++; i++;
	}

	//<! Reallocate if new size is greater than capacity
	if( m_len + distance > m_size ) reserve(m_len + distance);

	//<! Backups data
	std::copy(&m_data[position], &m_data[m_len], &m_data[position+distance]);

	//<! Inserts elements from the range
	for( auto &e: ilist)
		m_data[position++] = e;

	//<! Updates size
	m_len += distance;
	return pos;
}

/* Remove o elemento na posição pos. */
template<typename T>
ls::VectorIterator<T> ls::Vector<T>::erase( iterator pos ){

	//<! Get position of the removed item
    auto position(0ul);
	for( auto i(begin()); i!= pos; ++i)
		position++;
	
	//<! Goes to the element that follow pos
	pos++;	

	//<! Overrides element
	std::copy(&m_data[position+1], &m_data[m_len], &m_data[position]);

	m_len--;
	return pos;
}

/*Remove os elementos no intervalo [first, last). */
template<typename T>
ls::VectorIterator<T> ls::Vector<T>::erase( iterator first, iterator last ){
	//<! Gets position of the first item
    auto position(0ul);
	for( auto i(begin()); i!= first; ++i)
		position++;

	//<! Gets position of the first item
    auto distance(0ul);
	for( auto i(first); i!= last; ++i)
		distance++;

	auto pos = ++last;

	//<! Overrides elements
	std::copy(&m_data[position+distance], &m_data[m_len], &m_data[position]);

	m_len -= distance;
	return pos;
}

/* Removes the element at the end of the array. */
template <typename T>
T ls::Vector<T>::pop_back(){
	//<! Throw exception is list is empty
	if(empty())
		throw std::out_of_range("[pop_back()] Cannot recover element from an empty vector.");

	return m_data[--m_len];
}

/* Removes the element at the beginning of the array. */
template <typename T>
void ls::Vector<T>::pop_front (){
	//<! Throw exception is list is empty
	if(empty())
		throw std::out_of_range("[pop_back()] Cannot recover element from an empty vector.");

	//<! Removes the element
	for(auto i(0ul); i < m_len-1; ++i)
		m_data[i] = m_data[i+1];

	//<! Update size
	m_len--; 
}

/* Replaces the content of the list with copies of value 'value' */
template <typename T>
void ls::Vector<T>::assign( const T & value ){
	//<! Replacing the content
	for( auto i(0ul); i < m_size; ++i)
		m_data[i] = value;
}

/* Replaces the contents of the list with copies of the elements in the range [first; last).*/
template <typename T>
template <typename InputItr>
void ls::Vector<T>::assign( InputItr first, InputItr last){
	//<! Get number of elements between first and last
	auto distance(0ul);
	for(auto i(first); i!= last; ++i)
		distance++;

	std::cout << distance << std::endl;

	//<! Reallocate if new size is greater than capacity
	if(distance > m_size) reserve(distance);

	//<! Replacing the content
	for(auto i(0ul); i < distance ; ++i)
		m_data[i] = *(first++);

	//<! Update size
	m_len = distance;
}

/* Clear vector. */
template <typename T>
void ls::Vector<T>::clear()
{ m_len = 0; }

/* Increase the storage capacity of the array to a value that’s is greater or equal to new_cap. */
template <typename T>
void ls::Vector<T>::reserve( std::size_t new_cap ){
	if(new_cap > m_size){
		 //<! Creates new vector
		T *temp = new T[ new_cap ];

		//<! Do copy
		std::copy(m_data, m_data + new_cap, temp);

		delete m_data;    //<! Delete old storage area

		m_data = temp;	  //<! Transfer pointer to new adress
		m_size = new_cap; //<! Update size
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
//  VECTORITERATOR CLASS //
///////////////////////////

/*Default constructor for iterator class*/
template <typename T>
ls::VectorIterator<T>::VectorIterator(T * current)
: m_current( current)
{ /*empty*/ }

/* Returns a reference to the object located at the position pointed by the iterator */
template <typename T>
T& ls::VectorIterator<T>::operator*() const {
	assert( m_current != nullptr); 				
	return *m_current;
}

/* Advances iterator to the next location within the list. */
template <typename T>
ls::VectorIterator<T>& ls::VectorIterator<T>::operator++() {
	m_current++;				
	return *this;
}

/* Advances iterator to the next location within the list. (it++) */
template <typename T>
ls::VectorIterator<T> ls::VectorIterator<T>::operator++(int) {
	typename ls::Vector<T>::iterator temp = *this; 			
	m_current++; 				
	return temp;
}

/* Advances iterator to the next location within the list. (--it) */
template <typename T>
ls::VectorIterator<T>& ls::VectorIterator<T>::operator--() {
	m_current--;				
	return *this;
}

/* Advances iterator to the next location within the list. (it--) */
template <typename T>
ls::VectorIterator<T> ls::VectorIterator<T>::operator--(int) {
	typename ls::Vector<T>::iterator temp = *this; 			
	m_current--; 				
	return temp;
}

/* Returns true if both iterators refer to the same location within the list, 
 * and false otherwise. */
template <typename T>
bool ls::VectorIterator<T>::operator==( const typename ls::VectorIterator<T> & rhs ) const{
	return m_current == rhs.m_current;
}

/* Returns true if both iterators refer to the different location within the list, 
 * and false otherwise. */
template <typename T>
bool  ls::VectorIterator<T>::operator!=( const typename ls::VectorIterator<T> & rhs ) const{
	return m_current != rhs.m_current;
}