#include "dal.h"

template < typename Key , typename DataType , typename KeyComparator >
DAL<Key, DataType, KeyComparator>::DAL( std::size_t size)
:m_capacity( size )
,m_len(0)
,m_data( new Node[size])
{ /* empty*/ }

template < typename Key , typename DataType , typename KeyComparator >
DAL<Key, DataType, KeyComparator>::~DAL()
{ delete [] m_data; }

/// Método de busca auxiliar
template < typename Key , typename DataType , typename KeyComparator >
int DAL<Key, DataType, KeyComparator>:: _search ( const Key & k ) const{

	for( auto i(0ul); i < m_len; ++i){
		//!< Busca linear por elemento com chave k
        if( m_data[i].id == k)
            return i; //!< Se encontrar, retorna seu índice
    }

    //!< Se não encontrar elemento
    return -1;
}

template < typename Key , typename DataType , typename KeyComparator >
bool DAL<Key, DataType, KeyComparator>::search ( const Key & k , DataType & info ) const 
{
  	//!< Busca índice da chave
    auto index = _search(k);
    if( index != -1){
    	info = m_data[index].data;
    	return true;
    }

    return false;
}

template < typename Key , typename DataType , typename KeyComparator >
bool DAL<Key, DataType, KeyComparator>::insert( const Key & new_key , const DataType & new_info )
{
	//!< Verifica se elemento já existe
    auto index = _search(new_key);
    if( index != -1){
    	m_data[index].data = new_info;
    	return false;
    }
    m_len++;//!<Atualiza tamanho
    //!<Insere elemento
    m_data[ m_len ].id = new_key;
    m_data[ m_len ].data = new_info;

    return true;
}