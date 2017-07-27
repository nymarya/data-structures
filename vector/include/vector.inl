#include "vector.hpp"
#include <stdexcept>

///////////////////////////
//  [I] SPECIAL MEMBERS  //
///////////////////////////

/* Default constructor */
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
	//<! Get number of element  of the range
	std::size_t distance(0ul);
	while( temp != last ){
		distance++; temp++;
	}

	//<! Aloccate new storage area
	m_size = distance;
	m_len = m_size;
	m_data = new T[distance];

	//<! Copy elements from range
	for ( auto i(0ul); i < distance; ++first, ++i)
		m_data[i] = *first;
	
}

/* Copy constructor. */
template <typename T>
ls::Vector<T>::Vector(const Vector& other )
	:m_data(new T[other.m_size])
	,m_len( other.m_len)
	,m_size(other.m_size)
{
	//<! Copy content
	for(auto i(0ul); i< m_size; ++i)
		m_data[i] =  other.m_data[i];
}

/* Constructs the list with the contents of the initializer list. */
template<typename T>
ls::Vector<T>::Vector( std::initializer_list<T> init )
: m_len( init.size() )
, m_size( init.size() )
{
	//<! Aloccate new storage area
	m_data = new T[m_size];

	//<! Copy ocntent to new container
	int count = 0;
	for (auto &e : init)
		m_data[count++] = e;
	
}

/* Destructor. */
template <typename T>
ls::Vector<T>::~Vector( ){
	//!!< Deallocate storage area
	delete [] m_data;
}

/* Copy assignment operator. */
template <typename T>
ls::Vector<T>& ls::Vector<T>::Vector::operator=( const Vector& other ){
	if (this == &other) return *this;

	delete [] m_data; //<! Deallocate old storage area.

	//<! Allocate new storage area
	m_data = new T[other.m_size ];
	m_size = other.m_size;
	m_len  = other.m_len; 

	//<! Copy content to new container
	for(auto i(0ul); i < m_size; ++i)
		m_data[i] = other.m_data[i];

	return *this;
}

/* Replace the content of the list with the contents of the initializer list.*/
template<typename T>
ls::Vector<T>& ls::Vector<T>::operator=( std::initializer_list<T> ilist ){
	delete [] m_data; //<! Deallocate old storage area

	//<! Allocate new storage area, update size and capacity attributes
	m_data = new T[ilist.size()];
	m_len = ilist.size();
	m_size = ilist.size();

	//<! Copy content to new container
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

/* Returns an iterator pointing to the end mark of the list. */
template <typename T>
ls::VectorIterator<T> ls::Vector<T>::end( void )
{ return ls::Vector<T>::iterator(&m_data[m_len]); }

/* Returns a constant iterator pointing to the first item in the list. */
template <typename T>
typename ls::Vector<T>::const_iterator ls::Vector<T>::cbegin( void ) const
{ return ls::Vector<T>::const_iterator(&m_data[0]); }

/* Returns a constant iterator pointing to the end mark of the list. */
template <typename T>
typename ls::Vector<T>::const_iterator ls::Vector<T>::cend( void ) const
{ return ls::Vector<T>::const_iterator(&m_data[m_len]); }

///////////////////////////
//  [III] CAPACITY       //
///////////////////////////

/* Returns the number of elements in the container.*/
template <typename T>
std::size_t ls::Vector<T>::size() const
{ return m_len; }

/* Return the capacity of the container. */
template <typename T>
std::size_t ls::Vector<T>::capacity() const 
{ return m_size; }

/* Checks if the container contains no elements. */
template <typename T>
bool ls::Vector<T>::empty ()const
{ return (m_len == 0); }

/* Checks if the container is full. */
template <typename T>
bool ls::Vector<T>::full ()const
{ return (m_len == m_size); }

///////////////////////////
//  [IV] MODIFIERS       //
///////////////////////////

/* Inserts element at the end of the list. */
template <typename T>
void ls::Vector<T>::push_back(const T & value){
	//<! Reallocate if container is full
	if( full() ) reserve( m_size * 2);

	//<! Inserts value
	m_data[m_len++] = value;
}

/* Inserts element at the beginning of the container. */
template <typename T>
void ls::Vector<T>::push_front(const T & value){
	//<! Reallocate if container is full
	if ( full() ) reserve( m_size * 2 );

	//<! Moves content so the new value can be inserted
	std::copy(&m_data[0], &m_data[m_len], &m_data[1]);

	m_data[0] = value; //<! Inserts value
	m_len++;           //<! Updates size
}

/* Adds value before 'pos'. */
template <typename T>
typename ls::Vector<T>::iterator 
ls::Vector<T>::insert( iterator pos, const T & value ){
	//<! Get iterator's position
	auto position(0);
	for (auto i( begin() ); i != pos; ++i)
		position++;

	//<! Reallocate if container is full
	if( full() ) reserve(m_size * 2 );

	//<! Moves content so the new value can be inserted
	std::copy(&m_data[position], &m_data[m_len], &m_data[position+1]);
	
	m_data[position] = value; //<! Inserts value
	m_len++;      //<! Updates size
	return pos;
}

/* Inserts elements of the range [first; last) before 'pos'. */
template<typename T>
template<typename InputItr>
ls::VectorIterator<T> ls::Vector<T>::insert( iterator pos, InputItr first, InputItr last){
	//!< Get the number of elements between first and last 
	auto sz(0ul);
	auto i(first);
	while(i != last){
		sz++; i++;
	}

	//<! Get iterator's position
	auto position(0ul);
	i = begin();
	while(i != pos){
		position++; i++;
	}

	//<! Reallocate if new size is greater than capacity
	if( m_len + sz > m_size ) reserve(m_len + sz);

	//<! Moves content so the new values can be inserted
	std::copy(&m_data[position], &m_data[m_len], &m_data[sz]);

	//<! Inserts content of the range
	for( auto i(position); i < sz; ++i)
		m_data[i] = *first++;

	//<! Updates size
	m_len += sz;
	return pos;
}

/* Inserts elements from std::initializer_list before pos. */
template<typename T>
ls::VectorIterator<T> ls::Vector<T>::insert( iterator pos, std::initializer_list<T> ilist ){
	//!< Gets number of elements of the initializer list
	auto sz = ilist.size();

	//<! Gets iterator's position
	auto position(0ul);
	auto i(begin());
	while(i != pos){
		position++; i++;
	}

	//<! Reallocates if new size is greater than capacity
	if( m_len + sz > m_size ) reserve(m_len + sz);

	//<! Moves content so the new values can be inserted
	std::copy(&m_data[position], &m_data[m_len], &m_data[position+sz]);

	//<! Inserts content of the initializer list
	for( auto &e: ilist)
		m_data[position++] = e;

	//<! Updates size
	m_len += sz;
	return pos;
}

/* Removes the element at 'pos'. */
template<typename T>
ls::VectorIterator<T> ls::Vector<T>::erase( iterator pos ){
	//<! Gets position of the element to be removed
    auto position(0ul);
	for( auto i(begin()); i!= pos; ++i)
		position++;

	pos++;	

	//<! Overrides target
	std::copy(&m_data[position+1], &m_data[m_len], &m_data[position]);

	//<! Updates size
	m_len--;
	return pos;
}

/* Removes elements of the range [first, last) form the container. */
template<typename T>
ls::VectorIterator<T> ls::Vector<T>::erase( iterator first, iterator last ){
	//<! Gets position of the first element
    auto position(0ul);
	for( auto i(begin()); i!= first; ++i)
		position++;

	//<! Gets the number of elements between first and last
    auto distance(0ul);
	for( auto i(first); i!= last; ++i)
		distance++;

	//<! Gets position folowing the last element
	auto pos = ++last;

	//<! Overrides elements
	std::copy(&m_data[position+distance], &m_data[m_len], &m_data[position]);

	//<!  Updates size
	m_len -= distance;
	return pos;
}

/* Removes the element at the end of the list. */
template <typename T>
T ls::Vector<T>::pop_back(){
	//<! Throws exception if container is empty
	if(empty())
		throw std::out_of_range("[pop_back()] Cannot recover element from an empty vector.");

	return m_data[--m_len];
}

/* Removes the element at the beginning of the container. */
template <typename T>
void ls::Vector<T>::pop_front (){
	//<! Throws exception if container is empty
	if(empty())
		throw std::out_of_range("[pop_back()] Cannot recover element from an empty vector.");

	//<! Removes element
	for(auto i(0ul); i < m_len-1; ++i)
		m_data[i] = m_data[i+1];

	//<! Updates size
	m_len--; 
}

/* Replaces the content of the list with copies of 'value'. */
template <typename T>
void ls::Vector<T>::assign( const T & value ){
	//<! Replaces the content 
	for( auto i(0ul); i < m_size; ++i)
		m_data[i] = value;
}

/* Replaces the content of the list with copies of the elements of the range [first,last). */
template <typename T>
template <typename InputItr>
void ls::Vector<T>::assign( InputItr first, InputItr last){
	//<! Gets the number of elements between first and last
	auto distance(0ul);
	for(auto i(first); i!= last; ++i)
		distance++;

	//<! Reallocates storage area if new size is greater than capacity
	if(distance > m_size) reserve(distance);

	//<! Replaces the content
	for(auto i(0ul); i < distance ; ++i)
		m_data[i] = *(first++);

	//<! Updates size
	m_len = distance;
}

/* Replaces the content of the list with copies of the elements of 'ilist'. */
template< typename T>
void ls::Vector<T>::assign( std::initializer_list<T> ilist ){
	//<! Gets new size
	auto sz = ilist.size();

	//<! Reallocates storage area if new size is greater than capacity
	if(sz > m_size) reserve(sz);

	//<! Replaces the content of the container
	auto i(0);
	for(auto &e : ilist )
		m_data[i++] = e;

	//<! Updates size
	m_len = sz;

}

/* Removes all elements from container. */
template <typename T>
void ls::Vector<T>::clear()
{ m_len = 0; }

/* Increase the storage capacity of the array to a value that’s is greater or equal to 'new_cap'. */
template <typename T>
void ls::Vector<T>::reserve( std::size_t new_cap ){
	if(new_cap > m_size){
		 //<! Allocates new storage area
		T *temp = new T[ new_cap ];

		//<! Copy content to the new list
		for (auto i(0u); i < m_size; i++) 
			temp[i] = m_data[i];

		delete [] m_data;  //<! Deallocate old storage area

		m_data = temp;	  //<! Pointer pointing to the new adress
		m_size = new_cap; //<! Updates size
	}
}

/* Requests the removal of unused capacity. */
template <typename T>
void ls::Vector<T>::shrink_to_fit()
{ 
	//!< Reallocates storage area if necessary
	if( m_len < m_size ){
		
		//<! Allocates new storage area
		T *temp = new T[ m_len+1 ];

		//<! Copy content to the new list
		for (auto i(0u); i < m_len; i++) 
			temp[i] = m_data[i];

		delete [] m_data;  //<! Deallocate old storage area

		m_data = temp;	  //<! Pointer pointing to the new adress
		m_size = m_len; //<! Updates size
	}
}

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

/* Gets element at position 'pos' with bounds-checking. */
template <typename T>
T & ls::Vector<T>::at( std::size_t pos) const{
	if( pos < 0 or pos >= m_len)
		throw std::out_of_range("[at()] Cannot recover element out of range.");

	return m_data[pos];
}

/* Gets the object at position 'pos'. */
template <typename T>
T & ls::Vector<T>::operator[]( std::size_t pos) const
{ return m_data[pos]; }

/* Returns the object at the beginning of the array. */
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

/* Returns the object at the end of the array. */
template <typename T>
bool operator==( const ls::Vector<T>& lhs, const ls::Vector<T>& rhs ){
	//<! Checks the number of elements
	if( lhs.size() != rhs.size() ) return false;
	else{
		//<! Checks if all elements are the same
		for ( auto i(0ul); i < rhs.size(); ++i)
			if( rhs[i] != lhs[i] ) return false;
	}

	return true;
}

/* Checks if contents of both cantainers are the same.*/
template <typename T>
bool operator!=( const ls::Vector<T>& lhs, const ls::Vector<T>& rhs ){
	//<! Checks number of elements
	if( lhs.size() != rhs.size() ) return true;
	else{
		//<! Looking for one element different
		for ( auto i(0ul); i < rhs.size(); ++i)
			if( rhs[i] != lhs[i] ) return true;
	}

	return false;
}

///////////////////////////
//  VECTORITERATOR CLASS //
///////////////////////////

/* Iterator's default constructor. */
template <typename T>
ls::VectorIterator<T>::VectorIterator(T * current)
: m_current( current)
{ /*empty*/ }

/* Return a reference to the object located at the position pointed by the iterator. */
template <typename T>
T& ls::VectorIterator<T>::operator*() const {
	assert( m_current != nullptr); 				
	return *m_current;
}

/* Advances iterator to the next location within the list (++it) */
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

/* Moves iterator to the previous location within the list. (--it) */
template <typename T>
ls::VectorIterator<T>& ls::VectorIterator<T>::operator--() {
	m_current--;				
	return *this;
}

/* Moves iterator to the previous location within the list . (it--) */
template <typename T>
ls::VectorIterator<T> ls::VectorIterator<T>::operator--(int) {
	typename ls::Vector<T>::iterator temp = *this; 			
	m_current--; 				
	return temp;
}

/*  Returns true if both iterators refer to the same location within the list. */
template <typename T>
bool ls::VectorIterator<T>::operator==( const typename ls::VectorIterator<T> & rhs ) const{
	return m_current == rhs.m_current;
}

/* Returns true if both iterators refer to a different location within the list. */
template <typename T>
bool  ls::VectorIterator<T>::operator!=( const typename ls::VectorIterator<T> & rhs ) const{
	return m_current != rhs.m_current;
}