// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


// httplib.h has dependency that refined byte 
#define _HAS_STD_BYTE 0

#include <iostream>
#include <fstream>
#include "Monster.h"
#include "Log.h"
#include "Main.h"
#include <chrono>
#include <format>
#include "Timestamp.h"
#include "FileInfo.h"
#include <map>
#include "Person.h"
#include "StringFunctions.cpp"
#include "Mammal.h"
#include "MultithreadExample.h"
#include "httplib.h"
#include <algorithm>

using std::array, std::unique_ptr;
using namespace std::chrono_literals;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


void RunHttpServer();
string MakeGetRequest(string url);
void TestRequest();

int main()
{
    
    PrintOutPointerTest();

    // Date
    auto currentTimestamp = GetCurrentTimestamp();
    Log(currentTimestamp);


    // Read and write to file
    ofstream testFile("output_file_overwrite.txt");
    testFile << "Neat this file isn't empty!";
    testFile.close();

    ofstream outfileAppend;
    outfileAppend.open("output_file_appended.txt", std::ios::app); // append.
    outfileAppend << "File opened at " + currentTimestamp + "\n";
    outfileAppend.close();


    // Struct
    FileInfo fileInfo {
        "hello/Im/A/Filepath"    
    };  
    Log(fileInfo.filePath);


    // String manipulation
    auto strVector = std::vector<string> { "Hello", "World", "Wasuupppp"};
    auto joined_str = join(strVector.begin(), strVector.end(), "___");
    Log("String output: " + joined_str);


    std::array<string, 5> intArr = {"A", "AB", "ABC"};
    int idx = 0;
    //const auto* pAddressOfItemZero = &(*intArr.begin());

    for (auto& ele: intArr) {
        //const auto* pAddressOfElement = &ele;

        printf("Address of element %i is %p\n", idx, &ele);
        idx++;
    }

    printf("Address of String is %p\n", &"HELLO");
    //auto str1 = strstr("DEFABC", "ABC");
    //Log(str1);


    // Map<string, int>
    // Map<string, Struct or class>
    // Nested container with custom class
    std::vector<std::map<std::string, Person>> people_vector = {
        {{"person1", Person("Alice", 30)}, {"person2", Person("Bob", 25)}},
        {{"person3", Person("Charlie", 35)}, {"person4", Person("David", 28)}}
    };


    // Array & Vector iteraton
    for (auto &personMap : people_vector) {
        // Print map keys.
        for (auto it = personMap.begin(); it != personMap.end(); it++) {
            auto k = it->first;
            Log(k);
        }
    }
    for (auto& personMap : people_vector) {
        // Use of Structured binding with std::map
        for (const auto& [key, person] : personMap) {
            string out = "Key: " + key + ". Value: " + person_to_string(person);
            Log(out);
        }
    }

    std::vector<Person> more_people;
    more_people.reserve(5);
    more_people.emplace_back("Larry", 50);
    more_people.emplace_back("Maurice", 35);

    int i = 0;
    for (auto& [name, age]: more_people) {
        
        Log("Index " + to_string(i) + ": " + name + " (age " + to_string(age) + ").");

        // Just another way of assembling a string.
        vector<string> v = {
            "Index",
            to_string(i),
            name,
            "(age " + to_string(age) + ")."
        };
        
        Log(join_str_vector(v, " "));

        i++;
    }


    // End of tests. May do some more tomorrow.
    // Future tests: 
    // 1. JSON serialization and deserialization to structs. (need reflection or external library).
    // 2. Multithreaded work on an array of 1M strings. Possibly sort the characters in the strings alphabetically.
    // 3. Implement interface (abstract class). Multiple interfaces?

    startThreads();

    thread tHttpServ(RunHttpServer);
    tHttpServ.detach();
    //tHttpServ.join();



    Log("Press enter to make GET Request");
    //if (cin.get()) {
        TestRequest();
        TestRequest();
        TestRequest();
    //}

    Log("************* COMPLETED *************");
}

void TestRequest() {
    auto t1 = high_resolution_clock::now();

    thread r3(MakeGetRequest, "127.0.0.1:8080");
    r3.join();

    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    duration<double, std::milli> ms_double = t2 - t1;

    Log("Request time: " + to_string(ms_double.count()) + "ms");
}

void RunHttpServer() {
    // HTTP
    httplib::Server svr;
    // HTTPS
    //httplib::SSLServer svr;
    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
        Log("Loading /");
        res.set_content("Hello World from Server :8080!", "text/plain");
        });

    Log("Running on 127.0.0.1:8080");

    svr.listen("127.0.0.1", 8080);
}

// This is why Monster sayName function needs to be virtual.
// The virtual keyword introduces Late-binding to execute the most-specific type's defined function.
void CallFunctionOnMonster(Monster* monster) {
    monster->sayName();
}


string MakeGetRequest(string url) {
    // HTTPS
    httplib::Client cli(url);

    auto res = cli.Get("/");
    string code = to_string(res->status);
    Log("[GET] " + url + " " + code);
    
    return res->body;
}

void PrintOutPointerTest()
{
    // Stack allocation.
    Monster stackMonster{ "Drew" };
    auto name = stackMonster.getName();
    Log("Hello Im logging name name, which is: " + name);
    Monster* stackPtr = &stackMonster;
    stackPtr->sayName();

    //free(stackPtr);

    // Heap allocation
    Monster heapMonster = Monster("Mr. Heap monster");
    heapMonster.sayName();

    // Call function from point to class on heap.
    Monster* mPtr = &heapMonster;
    mPtr->sayName();

    auto uPtrConstructed = make_unique<Monster>("UNIQUE Monster");
    uPtrConstructed->sayName();

    auto uPtrFromRawPtr = make_unique<Monster*>(mPtr);
    (*uPtrFromRawPtr)->sayName();


    unique_ptr<Mammal> mammalPtr = make_unique<Mammal>("MAMMAL NAME");
    mammalPtr->sayName();
    CallFunctionOnMonster(mammalPtr.get());
}
