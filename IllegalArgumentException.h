#ifndef ILLEGAL_ARGUMENT
#define ILLEGAL_ARGUMENT

#include <stdexcept>
#include <string>

class IllegalArgumentException: public std::invalid_argument
{
    public:
       IllegalArgumentException(const std::string& message =""): invalid_argument("Illegal Argument" + message){
        }
};


#endif