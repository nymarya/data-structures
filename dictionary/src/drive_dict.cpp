#include "dal.h"
#include "dsal.h"
#include <cassert>
#include <vector>

class MyKeyComparator {
	public :
		bool operator()( const int & lhs , const int & rhs ) const
		{
			return (lhs < rhs) ;
		}
};

struct Fruit{
    int calories;
    float weight;
    std::string name;

    using FrKey = std::pair < std::string , int >;

    Fruit( int c=50, float w=10.0, std::string n="None")
    :calories(c), weight(w), name(n)
    {/*empty*/}

    FrKey get_key()
    {
        std::pair<std::string, int> p(name, calories);
        return p; 
    }

    float get_weight()
    {
    	return weight;
    }

};

struct FruitCompare{
    bool operator()( const Fruit::FrKey &lhs, const Fruit::FrKey &rhs) const{
        return (lhs.second < rhs.second);
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

	//Teste min()
	auto min = myList.min();
	assert( myList.search( min, name) );
	assert( min == 2014065190);
	std::cout << " >>> Min(): {" << min << ", " << name << " }" <<std::endl;

	//Teste max()
	auto max = myList.max();
	assert( myList.search( max, name) );
	assert( max == 2017065192);
	std::cout << " >>> Max(): {" << max << ", " << name << " }" <<std::endl;

	//Teste sucessor()
	int id = 2014065192;
	std::cout << " >>> Sucessor("<< id << "): ";
	assert( myList.sucessor( id, id) );
	assert( id == 2015065190);
	std::cout << id << std::endl;


	assert( myList.sucessor( myList.max(), id) == false );

	//Teste sucessor()
	id = 2014065192;
	std::cout << " >>> Predecessor("<< id << "): ";
	assert( myList.predecessor( id, id) );
	assert( id == 2014065191);
	std::cout << id << std::endl;


	assert( myList.predecessor( myList.min(), id) == false );



	////////////////////
	///     DSAL     ///
	////////////////////


	 std::vector<Fruit> fruits = {
        Fruit( 20, 2.50, "Apple"),
        Fruit( 85, 15.25, "Kiwi"),
        Fruit( 75, 10.0, "Blueberry"),
        Fruit( 50, 11.75, "Tomate")
	};

	DSAL < Fruit::FrKey , float , FruitCompare > myDict ( 50 );

	assert( myDict.insert( fruits[0].get_key(), fruits[0].get_weight() ));
	myDict.print();
	
	assert( myDict.insert( fruits[1].get_key(), fruits[1].get_weight() ));


	myDict.print();
	assert( myDict.insert( fruits[2].get_key(), fruits[2].get_weight() ));
	myDict.print();
	assert( myDict.insert( fruits[3].get_key(), fruits[3].get_weight() ));
	myDict.print();

	return EXIT_SUCCESS;
}