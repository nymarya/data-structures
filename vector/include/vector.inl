#include "vector.hpp"
#include <stdexcept>

//<! Função auxiliar que dobra array
template <typename T>
void ls::Vector<T>::doubleArray ( T * &A , std::size_t & currentSize ){

	 T *data = new T[ currentSize * 2]; //Novo vetor

	 std::copy(A, A+currentSize, data);  //Copia para novo vetor

	 delete A;

	 A = data;							//Aponta para o novo endereço
	 currentSize *= 2;                 //Atualizar tamanho;
}


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

	if( full() ) doubleArray(m_data, m_size);

	m_data[m_len++] = value;

}

/* Inserts element at the beginning of the array. */
template <typename T>
void ls::Vector<T>::push_front(const T & value){

	if ( full() ) doubleArray(m_data, m_size);

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



template <typename T>
bool operator==( const ls::Vector<T>& lhs, const ls::Vector<T>& rhs ){
	return true;
}