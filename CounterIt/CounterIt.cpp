// CounterIt.cpp : Defines the entry point for the application.
//

#include "CounterIt.hpp"

#include <iostream>
#include <algorithm>
#include <execution>

class Test {
private:
	int m_start = 3;
	int m_end = 6;
public:
	inline Kewl::Counter getTestCounter() { return Kewl::Counter( m_start, m_end ); }
};

int main()
{
	Test test;
	//Kewl::Counter<3,6> count; // template type args can not be dynamic
	//Kewl::Counter count( 3, 6 ); // constructor args cam be dynamic
	auto count = test.getTestCounter();

	std::cout << "Hello! Welcome to CounterIt." << std::endl;

	std::cout << std::endl << "Kewl::Counter( 3, 6 );";
	// A standered for_each test.
	std::cout << std::endl << "A standered for_each test." << std::endl;
	std::for_each( count.begin(), count.end(), []( const int& i ) { std::cout << " " << i; });
	std::cout << std::endl;

	// A multi-threaded for_each test.
	std::cout << std::endl << "A multi-threaded for_each test." << std::endl;
	std::cout << "May be out of order due to being proccessed in parallel!" << std::endl;
	std::for_each( std::execution::par, count.begin(), count.end(), []( const int& i ) { std::cout << " " << i; });
	std::cout << std::endl;

	// Dump the begin() and end() value test.
	std::cout << std::endl << "Test the begin/end and rbegin/rend functions." << std::endl;
	std::cout << "begin():" << *count.begin() << std::endl;
	std::cout << "end():" << *count.end() << std::endl;
	std::cout << "rbegin():" << *count.rbegin() << std::endl;
	std::cout << "rend():" << *count.rend() << std::endl;

	// Postfix increment test.
	std::cout << std::endl << "Postfix increment test." << std::endl;
	auto it = count.begin();
	std::cout << "before it++:" << *it << std::endl;
	it++;
	std::cout << "after it++:" << *it << std::endl;

	// Prefix increment test.
	std::cout << std::endl << "Prefix increment test." << std::endl;
	std::cout << "before ++it:" << *it << std::endl;
	++it;
	std::cout << "after ++it:" << *it << std::endl;

	// Standard for loop using begin/end functions test.
	std::cout << std::endl << "Standard for loop using begin/end functions test." << std::endl;
	for (auto it = count.begin(); it != count.end(); it++) {
		std::cout << " " << *it;
	}
	// Standard for loop using rbegin/rend functions test.
	std::cout << std::endl << "Standard for loop using rbegin/rend functions test." << std::endl;
	for (auto itr = count.rbegin(); itr != count.rend(); itr++) {
		std::cout << " " << *itr;
	}
	std::cout << std::endl;

	// 0 to 10 counts
	auto count10 = Kewl::Counter( 10 ); // counts [0,10]
	std::cout << std::endl << "Kewl::Counter( 10 );";
	std::cout << std::endl << "Count from 0 to 10 inclusive." << std::endl;
	std::for_each( count10.begin(), count10.end(), []( const int& i ) { std::cout << " " << i; });
	std::cout << std::endl << "In reverse inclusive." << std::endl;
	std::for_each( count10.rbegin(), count10.rend(), []( const int& i ) { std::cout << " " << i; } );
	std::cout << std::endl;

	// 0 to -10 counts
	auto countMinus10 = Kewl::Counter( -10 ); // counts [0,-10]
	std::cout << std::endl << "Kewl::Counter( -10 );";
	std::cout << std::endl << "Count from 0 to -10 in inclusive." << std::endl;
	std::for_each( countMinus10.begin(), countMinus10.end(), []( const int& i ) { std::cout << " " << i; } );
	std::cout << std::endl << "In reverse inclusive." << std::endl;
	std::for_each( countMinus10.rbegin(), countMinus10.rend(), []( const int& i ) { std::cout << " " << i; } );
	std::cout << std::endl;

	// -10 to 0
	auto countMinus10a = Kewl::Counter( -10, 0 ); // counts [-10,0]
	std::cout << std::endl << "Kewl::Counter( -10, 0 );";
	std::cout << std::endl << "Count from -10 to 0 in inclusive." << std::endl;
	std::for_each( countMinus10a.begin(), countMinus10a.end(), []( const int& i ) { std::cout << " " << i; } );
	std::cout << std::endl << "In reverse inclusive." << std::endl;
	std::for_each( countMinus10a.rbegin(), countMinus10a.rend(), []( const int& i ) { std::cout << " " << i; } );
	std::cout << std::endl;

	return 0;
}
