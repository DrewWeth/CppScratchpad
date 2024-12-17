#pragma once
#include <string>
#include "Log.h"
#include <thread>
#include <stdlib.h>     //for using the function sleep
#include <iostream>     //for using cout
//#include <stdlib.h>     //for using the function sleep
//#include <Windows.h>

using namespace std;    //for using cout

using std::string, std::thread;

void task1(string msg);

void startThreads();