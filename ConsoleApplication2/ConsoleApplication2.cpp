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


#include <iostream>
#include <fstream>
#include "Monster.h"
#include "Log.h"
#include "ConsoleApplication2.h"
#include <chrono>
#include <format>
#include "Timestamp.h"
#include "FileInfo.h"
#include <map>
#include "Person.h"
#include "StringFunctions.cpp"
#include "Mammal.h"

using std::array, std::unique_ptr;

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
    Log("************* COMPLETED *************");
}


// This is why Monster sayName function needs to be virtual.
// The virtual keyword introduces Late-binding to execute the most-specific type's defined function.
void CallFunctionOnMonster(Monster* monster) {
    monster->sayName();
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
