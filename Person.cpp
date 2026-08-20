#include "Person.h"

//Constructors

//default
Person::Person()
: fName(""), lName(""), bYear(0), accomplisment(""){}

//parametered
Person::Person(string firstName, string lastName, int birthYear, string whatDid)
:   fName(firstName), lName(lastName), bYear(birthYear), accomplisment(whatDid) {}

//copy
Person::Person(const Person& other)
:   fName(other.fName), lName(other.lName), bYear(other.bYear), accomplisment(other.accomplisment){}




//getters defined
string Person::getFirstName() const
{
    return fName;
}

string Person::getLastName() const
{
    return lName;
}

int Person::getBirthYear() const
{
    return bYear;
}

string Person::getAccomplishment() const
{
    return accomplisment;
}

//setters defined
void Person::setFirstName(const string& firstName)
{
    fName = firstName;
}

void Person::setLastName(const string& lastName)
{
    lName = lastName;
}

void Person::setBirthYear(int birthYear)
{
    bYear = birthYear;
}

void Person::setAccomplishment(const string& whatDid)
{
    accomplisment = whatDid;
}

//print method
void Person::printPerson() const
{
    cout << "First Name: " << fName << " Last Name: " << lName << " Birth Year: " << bYear << " Famous Contribution: " << accomplisment << "." << endl;
}