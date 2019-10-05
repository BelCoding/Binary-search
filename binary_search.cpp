
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

/*
 * Parameters:
  Const Vector containing the objects,
  Const object that we want to search,
  Window length to search (Size of the vector),
  Initial pos of the vector ( left of the window, 0) and this parameter will return the position of the object found,
  Counter of iterations (could be removed from he algorithm)
 */
template<typename T>
bool binary_search_research(const std::vector<T>& v, const T& thing2search, int& window_length, int& pos_left_w){


if( window_length == 0 )
{
	return false;

}else{

	int midpos = pos_left_w + (window_length)/2;

	if( thing2search < v[midpos]) // Is on the left side:
	{

		window_length = window_length/2; // new window length
		// Next position (left of the window)
		// pos_left_w is tha same than before

		//std::cout << rest << "[rest]. Go to left, " << v[pos_left_w] << "["<<pos_left_w<<"], with input window length: " << window_length << std::endl;
		return binary_search_research(v, thing2search, window_length, pos_left_w, it_count);

	}else if (thing2search > v[midpos]){ // It is on the rigth side:

		// when window_length is even number, the window to the right side, must be 1 less position
		window_length = (window_length-1)/2;

		// Next position (left of the window)
		pos_left_w = midpos+1;

		//std::cout << rest << "[rest]. Go to right, " << v[pos_left_w] << "["<<pos_left_w<<"], with input window length: " << window_length << std::endl;
		return binary_search_research(v, thing2search, window_length, pos_left_w, it_count);

	}else{

		pos_left_w = midpos;
		return true;
	}


}

}




// Same function but with a counter of interations
template<typename T>
bool binary_search_research(const std::vector<T>& v, const T& thing2search, int& window_length, int& pos_left_w, int& it_count){

it_count++;


if( window_length == 0 )
{
	return false;

}else{

	int midpos = pos_left_w + (window_length)/2;

/*
 * 	int rest = window_length % 2;
 *
	for(int i=pos_left_w; i< pos_left_w + window_length; i++)
	{
		std::cout << v[i] << "["  << i << "],";

	}
	std::cout << std::endl;
	std::cout << v[midpos] << "["  << midpos << "]" << std::endl;
*/

	if( thing2search < v[midpos]) // Is on the left side:
	{

		window_length = window_length/2; // new window length
		// Next position (left of the window)
		// pos_left_w is tha same than before

		//std::cout << rest << "[rest]. Go to left, " << v[pos_left_w] << "["<<pos_left_w<<"], with input window length: " << window_length << std::endl;
		return binary_search_research(v, thing2search, window_length, pos_left_w, it_count);

	}else if (thing2search > v[midpos]){ // It is on the rigth side:

		// when window_length is even number, the window to the right side, must be 1 less position
		window_length = (window_length-1)/2;

		// Next position (left of the window)
		pos_left_w = midpos+1;

		//std::cout << rest << "[rest]. Go to right, " << v[pos_left_w] << "["<<pos_left_w<<"], with input window length: " << window_length << std::endl;
		return binary_search_research(v, thing2search, window_length, pos_left_w, it_count);

	}else{

		pos_left_w = midpos;
		return true;
	}


}

}



// returns 1 when the test succeed
int run_test(const std::vector<int> v, int number2search){

	
	int window_length = static_cast<int>(v.size()); // full window range in which we want to search


	std::cout << "Number to search: " << number2search << std::endl;
	int pos = 0;
	int it_count = 0; // iteration count

	if (binary_search_research(v, number2search, window_length, pos, it_count))
	{
		std::cout << "Found in the pos number " << pos << std::endl;

		if( std::find(v.begin(), v.end(), number2search) != v.end() )
		{
			std::cout << "Test succeed " << std::endl;
			return 1;
		}else{

			std::cout << "Test fail " << std::endl;
			return 0;
		}

	}else{

		std::cout << "Not found, that number is not in the list" << std::endl;
		std::cout << "Number of iterations needed: " << it_count << std::endl;

		if ( std::find(v.begin(), v.end(), number2search) == v.end() )
		{
			std::cout << "Test succeed " << std::endl << std::endl;
			return 1;

		}else{

			std::cout << "Test fail " << std::endl << std::endl;
			return 0;
		}
	}


}
//                 .         .
//-------------------------------------

int main(){


	int totaltest=0;
	int testsucc=0;

	srand( (int)time(0));

	const int MAX_LEN = 1 + (rand() % 100);
	const int RND_RANGE = MAX_LEN/5;

	std::vector<int> v;
	// Creates a vector of ordered numbers, separated by a random distance with average RND_RANGE
	for(int i = 0; i < MAX_LEN; i++){

		int number = i*RND_RANGE + (rand() % RND_RANGE);
		v.push_back( number );

		if(i < MAX_LEN-1){
			std::cout << number << "["  << i << "]" << ",";
		}else{
			std::cout << number<< "["  << i << "]" << std::endl;
		}

	}

	std::cout << std::endl;
	int number2search = v[0];

	testsucc=testsucc+run_test(v, number2search);
	totaltest++;
	number2search = v[static_cast<int>(v.size())-1];
	testsucc=testsucc+run_test(v, number2search);
	totaltest++;

	std::cout << std::endl;
	number2search = v[0]-1;

	testsucc=testsucc+run_test(v, number2search);
	totaltest++;
	number2search = v[static_cast<int>(v.size())-1]+1;
	testsucc=testsucc+run_test(v, number2search);
	totaltest++;

	for(int i=1; i< 100 ; i++){

	    srand( (int)time(0)+i);

		std::vector<int> v;
		// Creates a vector of ordered numbers, separated by a random distance with average RND_RANGE
		for(int i = 0; i < MAX_LEN; i++){

			int number = i*RND_RANGE + (rand() % RND_RANGE);
			v.push_back( number );

			if(i < MAX_LEN-1){
				std::cout << number << "["  << i << "]" << ",";
			}else{
				std::cout << number<< "["  << i << "]" << std::endl;
			}

		}

		std::cout << std::endl;
		int number2search = (rand() % (MAX_LEN*RND_RANGE));

		testsucc=testsucc+run_test(v, number2search);
		totaltest++;
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}

	std::cout << "Total tests: " << totaltest << std::endl;
	std::cout << "Total testsucc: " << testsucc << std::endl;

return 0;
}
