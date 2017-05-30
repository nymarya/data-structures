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

/*! Destrutor. */
template<typename T>
ls::List<T>::~List( ){
	//clear()
	delete m_head; //<! Remove nó cabeça
	delete m_tail; //<! Remove nó calda
}
