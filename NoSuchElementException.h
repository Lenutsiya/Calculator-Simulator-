#ifndef NOSUCH_ARGUMENT
#define NOSUCH_ARGUMENT

#include <stdexcept>
#include <string>

class NoSuchElementException: public std::invalid_argument
{
    public:
       NoSuchElementException(const std::string& message =""): invalid_argument("No Such Argument" + message){
        }
};


#endif