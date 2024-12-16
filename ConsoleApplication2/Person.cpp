#include <string>
#include "Person.h"

using std::string, std::to_string;


std::string person_to_string(const Person& person)
{
	return "Age: " + to_string(person.age) + ". Name: " + person.name;

	//return string();
}

//std::ostream& operator<<(std::ostream& os, const Person& person) {
//	os << "Person{name: " << person.name << ", age: " << person.age << "}";
//	return os;
//}