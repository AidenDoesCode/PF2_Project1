#include <iostream>
#include <string>
using namespace std;

class Person
{

    private:

        //attributes
        string fName;
        string lName;
        int bYear;
        string accomplisment;

    public:
        //constructors
        Person();
        Person(string firstName, string lastName, int birthYear, string whatDid);
        Person(const Person& other);   //copy constructor 

        //methods

        //getters
        string getFirstName() const;
        string getLastName() const;
        string getAccomplishment() const;
        int getBirthYear() const;

        //setters
        void setFirstName(const string& firstName);
        void setLastName(const string& lastName);
        void setAccomplishment(const string& whatDid);
        void setBirthYear(int birthYear);

        void printPerson() const;
};