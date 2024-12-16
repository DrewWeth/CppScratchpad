#pragma once
#include <string>


struct Person {
    std::string name;
    int age;
};

//string person_to_string(const Person& person);
std::string person_to_string(const Person& person);