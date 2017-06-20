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

	//!< Teste remove()
	assert( myList.remove( 2014065190, name) );
	assert( name == " John ");

	assert( myList.remove( 2014065190, name) == false );
	assert( myList.remove( 2015003129, name) ) ;
	assert( myList.search( 2015003129, name) == false );
	assert( name == " Jack ");

	assert( myList.insert( 2014065190 , "Batgirl" ) );
	assert( myList.insert( 2015065190 , "Poison Ivy" ) );
	assert( myList.insert( 2014065191 , "Supergirl" ) );
	assert( myList.insert( 2014065192 , "Harley Quinn" ) );
	assert( myList.insert( 2017065190 , "Wonder Woman" ) );
	assert( myList.insert( 2017065191 , "Bumblebee" ) );
	assert( myList.insert( 2017065192 , "Katana" ) );

	return EXIT_SUCCESS;
}