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

struct KeyEqual {
	bool operator()( const Fruit::FrKey &lhs, const Fruit::FrKey &rhs) const{
        return (lhs.first == rhs.first) and (lhs.second == rhs.second);
    }
};

int main(){
	DAL < int , std::string , MyKeyComparator > myList ( 50 );
	assert( myList.insert ( 2015003129 , " Jack " ) ) ;
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

	/// Testes min e max
	assert( myList.insert( 2015065190 , "Poison Ivy" ) );
	assert( myList.insert( 2014065191 , "Supergirl" ) );
	assert( myList.insert( 2014065192 , "Harley Quinn" ) );
	assert( myList.insert( 2017065190 , "Wonder Woman" ) );
	assert( myList.insert( 2017065191 , "Bumblebee" ) );

	//Teste min()
	auto min = myList.min();
	assert( myList.search( min, name) );
	assert( min == 2014065191);

	//Teste max()
	auto max = myList.max();
	assert( myList.search( max, name) );
	assert( max == 2017065191);

	assert( myList.insert( 2014065190 , "Batgirl" ) );
	assert( myList.insert( 2017065192 , "Katana" ) );

	min = myList.min();
	assert( myList.search( min, name) );
	assert( min == 2014065190);

	max = myList.max();
	assert( myList.search( max, name) );
	assert( max == 2017065192);

	//Teste sucessor()
	int id = 2014065192;
	assert( myList.sucessor( id, id) );
	assert( id == 2015065190);


	assert( myList.sucessor( myList.max(), id) == false );

	//Teste predecessor()
	id = 2014065192;
	assert( myList.predecessor( id, id) );
	assert( id == 2014065191);


	assert( myList.predecessor( myList.min(), id) == false );



	////////////////////
	///     DSAL     ///
	////////////////////


	std::vector<Fruit> fruits = {
        Fruit( 20, 2.50, "Apple"),
        Fruit( 85, 15.25, "Kiwi"),
        Fruit( 75, 10.0, "Blueberry"),
        Fruit( 50, 11.75, "Tomato"),
        Fruit( 10, 2.00, "Banana")
	};


	DSAL < Fruit::FrKey , float , FruitCompare > myDict ( 50 );

	//Teste insert()
	assert( myDict.insert( fruits[0].get_key(), fruits[0].get_weight() ));
	
	//Teste search()
	assert( myDict.insert( fruits[1].get_key(), fruits[1].get_weight() ));

	float weight = 0.0;
	assert( myDict.search( fruits[0].get_key(), weight ) );
	assert( weight == fruits[0].get_weight()  );

	assert( myDict.search( fruits[1].get_key(), weight ) );
	assert( weight == fruits[1].get_weight()  );

	assert( myDict.insert( fruits[2].get_key(), fruits[2].get_weight() ));
	assert( myDict.search( fruits[2].get_key(), weight ) );
	assert( weight == fruits[2].get_weight() );

	assert( myDict.insert( fruits[3].get_key(), fruits[3].get_weight() ));
	assert( myDict.search( fruits[3].get_key(), weight ) );
	assert( weight == fruits[3].get_weight() );

	//Teste remove()
	float removed = 0.0;
	assert( myDict.remove( fruits[0].get_key(), removed ) );
	assert( removed == fruits[0].get_weight() );

	assert( myDict.remove( fruits[1].get_key(), removed ) );
	assert( removed == fruits[1].get_weight() );

	assert( myDict.remove( fruits[2].get_key(), removed ) );
	assert( removed == fruits[2].get_weight() );
	assert( myDict.remove( fruits[2].get_key(), removed ) == false );

	assert( myDict.remove( fruits[3].get_key(), removed ) );
	assert( removed == fruits[3].get_weight() );

	assert( myDict.remove( fruits[3].get_key(), removed ) == false );


	//Teste min() e max()
	assert( myDict.insert( fruits[0].get_key(), fruits[0].get_weight() ));
	assert( myDict.insert( fruits[2].get_key(), fruits[2].get_weight() ));
	assert( myDict.insert( fruits[3].get_key(), fruits[3].get_weight() ));
	
	auto min_dsal = myDict.min();
	assert( myDict.search( min_dsal, weight ) );
	assert( weight == fruits[0].get_weight() );

	auto max_dsal = myDict.max();
	assert( myDict.search( max_dsal, weight ) );
	assert( weight == fruits[2].get_weight() );

	/// Insere nas extremidades e recupera novos min e max
	assert( myDict.insert( fruits[1].get_key(), fruits[1].get_weight() ));
	assert( myDict.insert( fruits[4].get_key(), fruits[4].get_weight() ));

	min_dsal = myDict.min();
	assert( myDict.search( min_dsal, weight ) );
	assert( weight == fruits[4].get_weight() );

	max_dsal = myDict.max();
	assert( myDict.search( max_dsal, weight ) );
	assert( weight == fruits[1].get_weight() );


	//Teste sucessor()
	KeyEqual eq;

	std::pair<std::string, int> p;
	assert( myDict.sucessor(fruits[0].get_key(), p) );
	assert( eq(p, fruits[3].get_key() ) ); //!< Sucessor de Apple deve ser Tomato

	assert( myDict.sucessor(fruits[3].get_key(), p) );
	assert( eq(p, fruits[2].get_key() ) ); //!< Sucessor de Tomato deve ser Blueberry

	assert( myDict.sucessor(max_dsal, p) == false );

	std::cout << " >>> Normal exiting...\n";

	return EXIT_SUCCESS;
}