#include "dal.h"

///Construtor padrão
template < typename Key , typename DataType , typename KeyComparator >
DAL<Key, DataType, KeyComparator>::DAL( std::size_t size)
:m_capacity( size )
,m_len(0)
,m_data( new Node[size])
{ /* empty*/ }

/// Destrutor
template < typename Key , typename DataType , typename KeyComparator >
DAL<Key, DataType, KeyComparator>::~DAL()
{ delete [] m_data; }

/// Método de busca auxiliar
template < typename Key , typename DataType , typename KeyComparator >
int DAL<Key, DataType, KeyComparator>::_search ( const Key & k ) const
{

	for( auto i(0); i < m_len; ++i){
		//!< Busca linear por elemento com chave k
        if( m_data[i].id == k)
            return i; //!< Se encontrar, retorna seu índice
    }

    //!< Se não encontrar elemento
    return -1;
}

/// Método que remove elemento com chave 'k'
template < typename Key , typename DataType , typename KeyComparator >
bool DAL<Key, DataType, KeyComparator>::remove( const Key & k , DataType & info )
{
	//!< Verifica se elemento existe
    auto index = _search(k);
    if( index != -1){
    	info = m_data[index].data;

    	m_data[index ] = m_data[--m_len];
    	return true;
    }

    return false;
}


/// Método de busca que recupera o elemento com chave 'k'
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

/// Método que insere novo elemento no dicionário.
template < typename Key , typename DataType , typename KeyComparator >
bool DAL<Key, DataType, KeyComparator>::insert( const Key & new_key , const DataType & new_info )
{
	//!< Verifica se elemento já existe
    auto index = _search(new_key);
    if( index != -1){
    	m_data[index].data = new_info;
    	return false;
    }
    //!<Insere elemento
    m_data[ m_len ].id = new_key;
    m_data[ m_len++ ].data = new_info;

    return true;
}

/// Método que retorna menor chave
template < typename Key , typename DataType , typename KeyComparator >
Key DAL<Key, DataType, KeyComparator>::min() const
{
	KeyComparator cmp; //!< Instancia functor para comparar

	Key min = m_data[0].id;
	for( auto i(1); i< m_len; ++i)
	{
		if( cmp( m_data[i].id, min) )
			min = m_data[i].id;
	}

	return min;
}

/// Método que retorna maior chave
template < typename Key , typename DataType , typename KeyComparator >
Key DAL<Key, DataType, KeyComparator>::max() const
{
    KeyComparator cmp; //!< Instancia functor para comparar

    Key max = m_data[0].id;
    for( auto i(1); i< m_len; ++i)
    {
        if( !cmp( m_data[i].id, max) )
            max = m_data[i].id;
    }

    return max;
}

/// Recupera informação cuja chave é imediatamente posterior a chave 'k'
template < typename Key , typename DataType , typename KeyComparator >
bool DAL<Key, DataType, KeyComparator>::sucessor ( const Key & k , Key & k_ ) const{
    KeyComparator cmp; //!< Instancia functor para comparar

    Key suc = max();
    auto has_sucessor(false);
    for( auto i(1); i< m_len; ++i)
    {
        if( cmp( k, m_data[i].id) ){
            if( cmp(m_data[i].id, suc)){
                suc = m_data[i].id;
                has_sucessor =  true;
            }

        }

    }
    k_ = suc;
    return has_sucessor;
}