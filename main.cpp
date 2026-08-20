#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
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

int main() {
    const string filename = "computer_scientists.csv";
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        return 1;
    }

    string line;
    bool isHeader = true;
    vector<string> headers;
    vector<Person> people;

    while (getline(file, line)) {
        if (line.empty()) continue;

        vector<string> fields = parseCSVLine(line);

        if (isHeader) {
            headers = fields;
            isHeader = false;
            continue; // skip building a Person from the header row
        }

        // Guard against malformed rows that don't have enough fields
        if (fields.size() < 4) {
            cerr << "Warning: skipping malformed row: " << line << endl;
            continue;
        }

        // fields[0] = FirstName, fields[1] = LastName,
        // fields[2] = BirthYear,  fields[3] = Accomplishment
        string firstName = fields[0];
        string lastName  = fields[1];
        int birthYear    = stoi(fields[2]); // convert string -> int
        string whatDid   = fields[3];

        people.push_back(Person(firstName, lastName, birthYear, whatDid));
    }

    file.close();

    // Now print each Person using the class's own method
    for (const Person& p : people) {
        p.printPerson();
    }

    return 0;
}