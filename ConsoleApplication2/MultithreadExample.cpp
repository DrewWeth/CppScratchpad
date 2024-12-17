#include "MultithreadExample.h"
#include <vector>

void task1(string msg)
{
	const int max = 5;
	int sent = 0;
	for (int i = 1; i <= max; i++) {
		string a = " (" + to_string(i) + "/" + to_string(max) + ")";
		Log(msg + a);
		sent++;
		std::this_thread::sleep_for(chrono::milliseconds(rand() % 500));
	}
	Log("**** Completed " + msg + ". Sent " + to_string(sent));
}

void startThreads()
{
	thread t1(task1, "[1] Hello");
	thread t2(task1, "[2] Bonjour");
	thread t3(task1, "[3] Hola");

	std::vector<thread*> threads = {
		&t1,
		&t2,
		&t3
	};

	// Add one. References to thread
	thread t4(task1, "[4] Whoa");
	threads.push_back(&t4);

	// Add one. References to thread
	thread t5(task1, "[5] Neato");
	threads.push_back(&t5);

	for (auto& t : threads) {
		t->join();
	}
}


