#include <iostream>

#include "header.hpp"
#include "timer.hpp"



int main()
{
	Timer<std::chrono::microseconds> t;
	Timer<std::chrono::seconds> t2;
	FastSort<short> fs;

	t2.start();
	fs.generateRandom(10000000);
	t2.stop();
	std::cout << "Gen time: " << t2 << "seconds" << std::endl;
	
	t.start();
	fs.quickSort();
	t.stop();

	std::cout << "Sorted time: " << t << "microseconds" << std::endl;

	t2.start();
	fs.saveToFile("sorted_data.txt");
	t2.stop();

	std::cout << "Write file time: " << t2 << "seconds" << std::endl;

	return 0;
}