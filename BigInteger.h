//Name: BigInteger.h;
//Author: Elena Ochkina;
//Date: 11/19/2021;
//Description: This BigInteger class provides implementation to do basic math operation with arbitary large numbers using double linked list.
               //The class implements ariphmetic and comparison operator as well as methods that support implementation of those operators;
 
#ifndef BIG_INTEGER
#define BIG_INTEGER
#include "DoublyLinkedList.h"
#include "IllegalArgumentException.h"
#include <string>

#define COMPARE_RESULT_EQUAL 0
#define COMPARE_RESULT_BIGGER 1
#define COMPARE_RESULT_SMALLER -1

using namespace std;

class BigInteger {
    private:
        DoublyLinkedList<int>* digitsList;
        bool isNegativeInteger;
    public:
        BigInteger();
        BigInteger (const string& bigIntString);

        //destructor  
        ~BigInteger();    
    
        //copy constructor
        BigInteger(const BigInteger&);   

        //copy assignment operator
        BigInteger& operator=(const BigInteger&); 

        //return true if a integer is negative;
        bool isNegative() const;
        int getLength() const;
        BigInteger operator+(const BigInteger&);
        BigInteger operator-(const BigInteger&);
        bool operator>=(const BigInteger&);
        bool operator<=(const BigInteger&);

        bool operator==(const BigInteger&);
        bool operator>(const BigInteger&);
        bool operator<(const BigInteger&);

    private:    

        //this method compares integers if they have different signs;
        //return 0 if integers are equal, 1 if the first integer is bigger, -1 if the first integer is smaller;
        static int compare(const BigInteger&, const BigInteger&);

        //this method compares absolute values of integers; 
        //return 0 if integers are equal, 1 if the first integer is bigger, -1 if the first integer is smaller;
        static int absoluteCompare(const BigInteger&, const BigInteger&);

        //this method does a simple addition of two integers absolute values;
        static void absoluteAddition (const BigInteger&, const BigInteger&, BigInteger &);

        //this method does a simple substraction of two integers absolute values;
        static void absoluteSubstraction (const BigInteger&, const BigInteger&, BigInteger &);

        ///this method trims leading zeros;
        void trimLeadingZeros();

    friend ostream& operator<<(ostream& out, const BigInteger &_integer)  {
        _integer.digitsList->setIteratorFirst();        
        if (_integer.isNegative()) {
            out<<"-";
        }
        while(!_integer.digitsList->isIteratorNULL()){
            out<<_integer.digitsList->getData()<<" ";
            _integer.digitsList->next();
        }
        return out;
        }

    friend istream& operator>>(istream& in, BigInteger &_integer)  {
        string input;
        in >> input;
        BigInteger fromInput(input);
        _integer.isNegativeInteger = fromInput.isNegativeInteger;
        *(_integer.digitsList) = *fromInput.digitsList;
        return in;
    }    
            

};
//Default constructor;
BigInteger:: BigInteger() {
    this->digitsList = new DoublyLinkedList<int>();    
    isNegativeInteger = false;
}
//Parametrized constructor;
BigInteger::BigInteger(const string& bigIntString) {//accepts a string as a parameter;
    int length = bigIntString.length();
    this->digitsList = new DoublyLinkedList<int>();
    this->isNegativeInteger = false;
    
    for (int i = 0; i < length; i++) {//string parsing and inserting integers into the list;
        if (i == 0 && bigIntString.at(0) == '-') {//check if the firts character is "-" that means that a digit is negative;
            isNegativeInteger = true;
            continue;
        }

        int digit = bigIntString.at(i) - '0';
        if (digit >= 0 && digit <=9 ) {
            this->digitsList->insertLast(digit);    
        } 
        else {
            throw IllegalArgumentException ("all inputs other than integers are illegal");
        }
        this->trimLeadingZeros();//trim zeros in case the string contains zeros at the very beginning;
    }
}
//destructor
BigInteger:: ~BigInteger() {
   
    this->digitsList->clear();
}
//copy constructor;
BigInteger::BigInteger(const BigInteger& other) {
    
    this->digitsList = new DoublyLinkedList<int>();
    // The line below assign
    *(this->digitsList) = *other.digitsList;
    this->isNegativeInteger = other.isNegativeInteger;

    
}

//Assignment Operator;
BigInteger& BigInteger:: operator=(const BigInteger& other) {
    
    if (this->digitsList != other.digitsList) {
        this->digitsList->clear();
        *(this->digitsList) = *other.digitsList;//setting value of this digit list to the other digit list. This operation triggers
                                                //assignment constructor to clone this digit list;
        this->isNegativeInteger = other.isNegativeInteger;
    }
    return *this;
}

//Checks if a digit is negative;
bool BigInteger:: isNegative() const {
    return this->isNegativeInteger;
}

//this methods returns a length of a digit;
int BigInteger:: getLength() const {
    return this->digitsList->getLength();
}
//this method does comparison;
int BigInteger:: compare(const BigInteger& first, const BigInteger& second) {
    if (&first == &second) {
        return COMPARE_RESULT_EQUAL;
    }
    if (first.isNegative() && !second.isNegative()){
        return COMPARE_RESULT_SMALLER;
    }
    else if (!first.isNegative() && second.isNegative()) {
        return COMPARE_RESULT_BIGGER;
    }
    if (first.isNegative() && second.isNegative()) {
        return -1*absoluteCompare(first, second);//the comparison of two negatives digits are the same algorithm as the compare of 
                                                 //two positive, however, the result of comparison is opposite;
    }
    else {//both digitals are positive;
        return absoluteCompare(first, second);
    }

    return COMPARE_RESULT_EQUAL;
}

//this method does comparison of digits absolute values;
int BigInteger:: absoluteCompare(const BigInteger& first, const BigInteger& second) {
    if (&first == &second) {
        return COMPARE_RESULT_EQUAL;
    }
    if (first.getLength() > second.getLength()) {
        return COMPARE_RESULT_BIGGER;
    }
    else if (first.getLength() < second.getLength()) {
        return COMPARE_RESULT_SMALLER;
    }

    first.digitsList->setIteratorFirst();//set an iterator for the first integer on the first digit;     
    second.digitsList->setIteratorFirst();//set iterator for the second integer on the first digit;
    

    //move an iterator until data exists;
    while(!first.digitsList->isIteratorNULL() && !second.digitsList->isIteratorNULL()) {
        if (first.digitsList->getData() > second.digitsList->getData()) {
            return COMPARE_RESULT_BIGGER;
        }
        else if (first.digitsList->getData() < second.digitsList->getData()) {
            return COMPARE_RESULT_SMALLER;
        }
        else {
            first.digitsList->next();
            second.digitsList->next();
        }
    }
    return COMPARE_RESULT_EQUAL;
}
//this metod does a basic addition of absolute values;
void BigInteger:: absoluteAddition (const BigInteger& first, const BigInteger& second, BigInteger &additionResult) {
    const BigInteger *longList;// a pointer to a list for a longer digit
    const BigInteger *shortList;//a pointer to a list for a shorter digit
    int addFromPreviousStep = 0; //an addtional number to add to the next digit based on the previous addition result;

    //detect which digit contains more integers
    if (first.getLength() > second.getLength() ){
        longList = &first;//now long list points to the first;
        shortList = &second;//now long list points to the second;
    }
    else {
        longList = &second;
        shortList = &first;
    }

    longList->digitsList->setIteratorLast(); //set operator on the last integer in the long list;
    shortList->digitsList->setIteratorLast();//set operator on the last integer in the short list;

    //moves an iterator until the longer digit contains integers;
    while (!longList->digitsList->isIteratorNULL()) {
        int sumResult = 0; //the result of two integers addition;
        sumResult = longList->digitsList->getData() + addFromPreviousStep;//sum of longer digit's integer and the remainder;
        //moves an iterator until the short digit has integers to sum up;
        if (!shortList->digitsList->isIteratorNULL()) {
            sumResult = sumResult + shortList->digitsList->getData();//add an integer to the sum of the longer list integer and remainder
            shortList->digitsList->prev();        
        }
        //check the case if the sum is more than 10;
        if (sumResult >=10) {
            additionResult.digitsList->insertFirst(sumResult - 10);//insert the difference of the sum and 10;
            addFromPreviousStep = 1;//make the remainder equal to one;  
        }
        //case if the sum is less than 10;
        else {
            additionResult.digitsList->insertFirst(sumResult);//insert the sum into the list;
            addFromPreviousStep = 0;//make the remainder equal to zero;  
            }
        longList->digitsList->prev();      
                  
    }  //insert the leading 1 in needed.
    if (addFromPreviousStep == 1) {
        additionResult.digitsList->insertFirst(addFromPreviousStep);        
    }
}

//this method trims leading zeros that could be as the result of a substraction;
void BigInteger:: trimLeadingZeros() {
    this->digitsList->setIteratorFirst();//set an iterator on the header;

    //iteration and trimming leading zeros but the last zero is left in the list;
    while(this->digitsList->getData() == 0 && this->getLength()>1) {
       this->digitsList->deleteFirst();
       this->digitsList->setIteratorFirst();
    }
}

//this method does a basic substraction of two absolute values;
void BigInteger:: absoluteSubstraction (const BigInteger& first, const BigInteger& second, BigInteger &substractionResult) {
    //To avoid coping BigInteger objects when assigning below lists, creating pointers to the below lists 
    //and operating with those pointers for the logic in this method;

    const BigInteger *largeList;//a pointer to a list for a bigger value digit
    const BigInteger *smallList;//a pointer to list for a smaller value digit
    int addFromPreviousStep = 0;//an addtional number to add to the next digit based on the previous substraction result;
    int compareResult = absoluteCompare(first, second);//variable for compare result of two digits absolute values. 
   
   //checking cases of comaprison and selecting the larger digits to substract from bigger digit a smaller one;  
    if (compareResult == COMPARE_RESULT_BIGGER) {
        largeList = &first;
        smallList = &second;
    }
    else if (compareResult == COMPARE_RESULT_SMALLER) {
        largeList = &second;
        smallList = &first;
    }
    //in case if two digits are equal the result of substraction is zero; insert zero and return from the method;
    else if (compareResult == COMPARE_RESULT_EQUAL) {
        substractionResult.digitsList->insertFirst(0);
        return;
        
    }
    

    largeList->digitsList->setIteratorLast();//set operator on the large integer in the long list;
    smallList->digitsList->setIteratorLast();//set operator on the small integer in the long list;

    //move an iterator until the bigger digit has integers;
    while (!largeList->digitsList->isIteratorNULL()) {
        int difference = 0;
        difference = largeList->digitsList->getData() + addFromPreviousStep;//calculate the difference of bigger digit and remainder;
        //move an iterator until the smaller digit has integers;
        if (!smallList->digitsList->isIteratorNULL()) {
            difference = difference - smallList->digitsList->getData();//calculate the difference
            smallList->digitsList->prev();
        }
        //a case if the difference is less than 10;
        if (difference<0) {
            difference = difference + 10;//calculate the intermediate result to insert into the Result List;
            substractionResult.digitsList->insertFirst(difference);
            addFromPreviousStep = -1;//set a remainder equals to -1;
        }
        //a case if the difference is more or equal to zero;
        else {
            substractionResult.digitsList->insertFirst(difference); //insert an intermediate result;
            addFromPreviousStep = 0;           
        }
        largeList->digitsList->prev();        
    }
    
    substractionResult.trimLeadingZeros();//trim leading zeros if they are exist;

}

BigInteger BigInteger::operator+(const BigInteger& other) {
    BigInteger additionResult;    
    int compareResult;

    //in case both integers are either positive or negative;
    if (this->isNegativeInteger == other.isNegativeInteger) { 
        absoluteAddition(*this, other, additionResult); //do a simple addition
        additionResult.isNegativeInteger = this->isNegativeInteger;//the signs is the same as the first digit;
    }    
    //in case both digits have different signs; do a substraction and then checks a sign depending what digit is larger by absolute value;
    else {
        absoluteSubstraction(*this, other, additionResult);        
        compareResult = absoluteCompare(*this, other);//compare modules to detect a sign of the addition result;
        if (compareResult == COMPARE_RESULT_BIGGER) {
            additionResult.isNegativeInteger = this->isNegativeInteger;//the sign of addition result will be same as a sign of this digit 
                                                                       //as its absolute value is bigger than other one;
        }
        else if (compareResult == COMPARE_RESULT_EQUAL) {
            additionResult.isNegativeInteger = false;//the result will be always zero; zero is always not negative;
        }
        else {
            additionResult.isNegativeInteger = other.isNegativeInteger;
        }
    }   
    return additionResult;  
}

BigInteger BigInteger:: operator-(const BigInteger& other) {
    BigInteger _other = other;//create a new list which is a copy of the second digit;
    _other.isNegativeInteger = !_other.isNegativeInteger; //set a signs for a copy as an opposite to the sign of the second digit;
                                                          //the algotritm substracts two digits based on a + (-b);
    return *this+_other;    
}

bool BigInteger:: operator== (const BigInteger& other) {
    int compareResult = compare(*this, other);

    if (compareResult == COMPARE_RESULT_EQUAL) {
        return true;
    }
    return false;
}

bool BigInteger:: operator>= (const BigInteger& other) {
    int compareResult = compare(*this, other);
    if ((compareResult == COMPARE_RESULT_BIGGER) || (compareResult == COMPARE_RESULT_EQUAL)) {
        return true;
    }
    return false;
}

bool BigInteger:: operator> (const BigInteger& other) {
    int compareResult = compare(*this, other);
    if (compareResult == COMPARE_RESULT_BIGGER) {
        return true;
    }
    return false;
}

bool BigInteger:: operator<= (const BigInteger& other) {
    int compareResult = compare(*this, other);
    if ((compareResult == COMPARE_RESULT_SMALLER) || (compareResult == COMPARE_RESULT_EQUAL)) {
        return true;
    }
    return false;
}

bool BigInteger:: operator< (const BigInteger& other) {
    int compareResult = compare(*this, other);
    if (compareResult == COMPARE_RESULT_SMALLER) {
        return true;
    }
    return false;
}
    
#endif
