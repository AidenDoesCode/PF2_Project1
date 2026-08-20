#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include "Person.h"

// Parses a single CSV line into fields, respecting double-quoted fields
// that may contain commas (e.g. "Turing machine, and foundations...").
vector<string> parseCSVLine(const string& line) {
    vector<string> fields;
    string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (inQuotes) {
            if (c == '"') {
                if (i + 1 < line.size() && line[i + 1] == '"') {
                    field += '"';
                    ++i;
                } else {
                    inQuotes = false;
                }
            } else {
                field += c;
            }
        } else {
            if (c == '"') {
                inQuotes = true;
            } else if (c == ',') {
                fields.push_back(field);
                field.clear();
            } else {
                field += c;
            }
        }
    }
    fields.push_back(field); // last field
    return fields;
}

void initInputFile(const string& fileName, vector<Person>& people)
{
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Error: could not open file " << fileName << endl;
        return; // just exit the function
    }

    string line;
    bool isHeader = true;
    vector<string> headers;

    while (getline(file, line)) {
        if (line.empty()) continue;

        vector<string> fields = parseCSVLine(line);

        if (isHeader) {
            headers = fields;
            isHeader = false;
            continue; // skip building a Person from the header row
        }

        if (fields.size() < 4) {
            cerr << "Warning: skipping malformed row: " << line << endl;
            continue;
        }

        string firstName = fields[0];
        string lastName  = fields[1];
        int birthYear    = stoi(fields[2]);
        string whatDid   = fields[3];

        people.push_back(Person(firstName, lastName, birthYear, whatDid));
    }

    file.close();
}

//print the UI
void printMenu()
{

    cout << "Please choose which option you want to do." << endl;
    cout << "1. Read Input File. " << endl;
    cout << "2. Search by first name. " << endl;
    cout << "3. Search by last name. " << endl;
    cout << "4. Search by birth year. " << endl;

    getUserChoice();
}

int getUserChoice
{
    int userChoice;

    // Loop continues as long as the input fails to parse as an integer
    while (!(cin >> userChoice)) 
    {
        cout << "Invalid input! Please enter a valid integer: ";
        
        cin.clear(); //clear the error flag so cin can function again
        
        //Discard everything remaining in the input buffer until the next newline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return userChoice
}

int main() {
    //init vector of people objects, empty right now
    vector<Person> people;


    //loop to print the objects for checking
    for (const Person& p : people) {
        p.printPerson();
    }

    return 0;
}

