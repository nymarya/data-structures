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
	//!< Retorna indice se achar
	for( auto i(0); i < m_len; ++i){
		//!< Busca linear por elemento com chave k
        if( m_data[i].id == k)
            return i; //!< Se encontrar, retorna seu índice
    }

    //!< faz upper/lower bound se n estiver

    //!< Se não encontrar elemento
    return -1;
}


/// Método que insere novo elemento no dicionário
template < typename Key , typename DataType , typename KeyComparator >
bool DSAL<Key, DataType, KeyComparator>::insert ( const Key & new_key , const DataType & new_info )
{
	auto data = DAL<Key, DataType, KeyComparator>::m_data;
	auto len = DAL<Key, DataType, KeyComparator>::m_len;

	if( len == DAL<Key, DataType, KeyComparator>::m_capacity) 
		return false;
	// if( len == 0 ){
	// 	data[len].id = new_key;
	// 	data[len].data = new_info;
	// 	DAL<Key, DataType, KeyComparator>::m_len++;
	// 	return true;
	// }
	KeyComparator cmp;
	std::cout << "inserindo " << new_key.first << " \n";
	for( auto i(0); i < len; ++i){
		if( cmp(new_key, data[i].id)){
			//!< desloca
			DAL<Key, DataType, KeyComparator>::m_len++;
			std::cout << "vai mudar ";
			for( auto j(i); j < len; ++j)
				std::cout << data[j].id.first << " ";
			std::cout << std::endl;
			std::copy(&data[i], &data[len+1], &data[i+1]);
			data[i].id = new_key;
			data[i].data = new_info;
			return true;
		}
	}

	data[len].id = new_key;
	data[len].data = new_info;
	DAL<Key, DataType, KeyComparator>::m_len++;
	return true;
}