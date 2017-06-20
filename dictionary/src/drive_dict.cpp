#include "dal.h"

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
	myList.insert ( 2015003129 , " Jack " );
	std::cout << " >>> Inserindo {2014065190 , \" John \"} " << std::endl ;
	myList.insert ( 2014065190 , " John " );

	return 0;
}