#include "dal.h"
#include <cassert>

class MyKeyComparator {
	public :
		bool operator()( const int & lhs , const int & rhs ) const
		{
			return (lhs < rhs) ;
		}
};


int main(){
	DAL < int , std::string , MyKeyComparator > myList ( 50 );
	std::cout << " >>> Inserindo {2015003129 , \" Jack \"} " << std::endl ;
	assert( myList.insert ( 2015003129 , " Jack " ) ) ;
	std::cout << " >>> Inserindo {2014065190 , \" John \"} " << std::endl ;
	assert( myList.insert ( 2014065190 , " John " ) );

	//Teste retrieve
	std::string name;
	assert( myList.search( 2014065190, name) );
	assert( name == " John ");

	return 0;
}