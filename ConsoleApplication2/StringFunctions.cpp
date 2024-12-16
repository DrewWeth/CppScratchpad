#include "StringFunctions.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>




template <typename Iterator>
std::string join(Iterator begin, Iterator end, const std::string& delimiter = " ") {
    std::ostringstream result;

    if (begin != end) {
        result << *begin;  // Add the first element without delimiter.
        begin++;  // Move the iterator to the next element
    }

    // Iterate through the rest of the elements and add the delimiter between them.
    for (; begin != end; ++begin) {
        result << delimiter << *begin;
    }

    return result.str();
}


static std::string join_str_vector(std::vector<string>& strVector, const std::string& delimiter = " ") {
    return join(strVector.begin(), strVector.end(), delimiter);
    //return "";
}