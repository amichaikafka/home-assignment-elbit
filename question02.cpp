//Question 2 - threads & synchronization

//Task: Improve execution time by using multi-threading instead of calling operation1 and operation2 serially, make sure that sum=EXPECTED_SUM after using threads
// please explain the changes you made and what new aspects you had to deal with when shifting from serial execution to parallel execution 

// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify the constexpr variables

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

constexpr size_t ITERATIONS = 1000*1000ULL;
constexpr size_t OP1_PARAM = 2ULL;
constexpr size_t OP2_PARAM = 1ULL;
constexpr size_t EXPECTED_SUM = 1000001000000ULL;
//number of threads
constexpr size_t NUMBER_OF_THREADS = 2;
/*Explention:
* 1.The minimum time of execution this program is 10000 milisecond due to the sleeping  time in operation2, so my goal is to be the closest to 10000
* 2.sum is a common resource,so when we want to change sum its a critical section, i used mutex to lock critical section.
* At the beginning i locked only the lines when sum changed (see exsample line 40) the time i reached using two thread: approximately:10390.
* In order to improve this time, i realized that the fact the lock was insade the for loop couse to a lot of contact swich between the threads
* which increas the time, so to decrease the amount of contact swich i put the for loop insade the lock to,the time i reached using two thread: approximately:10016(almost 10000)
* I didnt use in more then 2 threads because it would couse to a lot of unesesary  contact swich and just increas the time.
* */
size_t sum = 0;
//define lock to synchroniz when the thread using a commen resource  
std::mutex myLock;

void operation1(size_t arg) {

	std::cout << "Performing operation1" << std::endl;
	myLock.lock();
	for (size_t i = 0; i < ITERATIONS; i++) {

		 
		//myLock.lock(); not used 
		sum += (arg+i);
		//myLock.unlock();
	}
	myLock.unlock();
	std::this_thread::sleep_for(std::chrono::seconds(5)); //Simulate some heavy work
	std::cout << "Operation1 Performed" << std::endl;
}


void operation2(size_t arg) {
	
	std::cout << "Performing operation2" << std::endl;
	myLock.lock();
	for (size_t i = 0; i <ITERATIONS; i++) {
		
		sum += (arg*i);
		
	}
	myLock.unlock();
	std::this_thread::sleep_for(std::chrono::seconds(10));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
}


int main(int argc, char** argv)
{
	//creat a thread pool in order to control the amount of threads
	std::thread threads[NUMBER_OF_THREADS];
	auto start = std::chrono::steady_clock::now();
	for (size_t i = 0; i < NUMBER_OF_THREADS; i++)
	{
		if (i%2==0)
		{
			threads[i] = std::thread(operation1, OP1_PARAM);
		}
		else {
			threads[i] = std::thread(operation2, OP2_PARAM);
		}
		
	}
	for (size_t i = 0; i < NUMBER_OF_THREADS; i++)
	{
		//make sure all the threads finshed there job
		threads[i].join();
	}

	auto end = std::chrono::steady_clock::now();

	std::cout << "Total execution duration in milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	std::cout << "Result:  " << sum <<  ", " <<(sum == EXPECTED_SUM ? "success" : "failure!")<< std::endl;
	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}