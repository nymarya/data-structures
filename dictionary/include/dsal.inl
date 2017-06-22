#include "dsal.h"
#include <cstring>


///Construtor padrão
template < typename Key , typename DataType , typename KeyComparator >
DSAL<Key, DataType, KeyComparator>::DSAL( std::size_t size)
:DAL<Key, DataType, KeyComparator>( size )
{ /* empty*/ }

/// Destrutor
template < typename Key , typename DataType , typename KeyComparator >
DSAL<Key, DataType, KeyComparator>::~DSAL()
{ /*empty*/ }

/// Método de busca auxiliar
template < typename Key , typename DataType , typename KeyComparator >
int DSAL<Key, DataType, KeyComparator>::_search ( const Key & k ) const
{
	auto data( DAL<Key, DataType, KeyComparator>::m_data );
	auto first(0);
	auto last(DAL<Key, DataType, KeyComparator>::m_len);

	KeyComparator cmp;

	//!< busca do limite inferior
	auto n = last-first; //!< número de candidatos a limite inferior
	while( n > 0)
	{
		auto mid = n/2;

		if(  cmp(data[first + mid].id, k ) ){
			first = first + mid + 1; //!< Guarda candidato
			n -= mid + 1; //!< diminui o número de candidatos
		}else{
			n = mid; //!< Diminui número de candidatos
		}
	}

    return first;
}


/// Método que insere novo elemento no dicionário
template < typename Key , typename DataType , typename KeyComparator >
bool DSAL<Key, DataType, KeyComparator>::insert ( const Key & new_key , const DataType & new_info )
{
	auto data = DAL<Key, DataType, KeyComparator>::m_data;
	auto len = DAL<Key, DataType, KeyComparator>::m_len;

	if( len == DAL<Key, DataType, KeyComparator>::m_capacity) 
		return false;

	//!< Busca posição de onde pode inserir
	auto pos = _search( new_key);
	//!< Realiza deslocamento
	for( auto i(len); i > pos; --i)
	{
		data[i].id = data[i-1].id;
		data[i].data = data[i-1].data;
	}

	//!< Insere
	data[pos].id = new_key;
	data[pos].data = new_info;
	DAL<Key, DataType, KeyComparator>::m_len++; //!< Atualiza
	return true;
}