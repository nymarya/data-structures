#include "list.h"


///////////////////////////
// [I] MEMBROS ESPECIAIS //
///////////////////////////
/*! Construtor padrão. */
template <typename T>
ls::List<T>::List()
:m_size(0)
,m_head(new Node())
,m_tail(new Node())
{
	m_head->next = m_tail;
	m_tail->prev = m_head;
}

/*! Constrói a lista com count cópias de T. */
template <typename T>
ls::List<T>::List(size_type count)
:m_size(count)
,m_head(new Node())
,m_tail(new Node())
{
	m_head->next = m_tail;
	m_tail->prev = m_head;
	auto current(m_head);
	while(count-- > 0){
		//<!Cria novo nó
		auto n_node = new Node(T(), current, current->next);

		//<!O anterior do next aponta para o novo
		current->next->prev = n_node;

		//<! O proximo do current é o novo
		current->next = n_node;
		//<! Avança
		current = current->next;
	}
}

/*! Destrutor. */
template<typename T>
ls::List<T>::~List( ){
	//clear()
	delete m_head; //<! Remove nó cabeça
	delete m_tail; //<! Remove nó calda
}


///////////////////////////
// [II] ITERADORES       //
///////////////////////////

///////////////////////////
// [III] CAPACIDADE      //
///////////////////////////

/*! Retorna número de elementos da lista. */
template <typename T>
std::size_t ls::List<T>::size( ) const{
	return m_size;
}

/*! Verifica se a lista não tem elementos. */
template <typename T>
bool ls::List<T>::empty( ) const{
	return (m_head->next == m_tail and m_tail->prev == m_head);
}

///////////////////////////
// [IV] CONSULTA         //
///////////////////////////

///////////////////////////
// [V] MODIFICADORES     //
///////////////////////////