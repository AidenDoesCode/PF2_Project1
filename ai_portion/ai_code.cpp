#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Parses a single CSV line into fields, respecting double-quoted fields
// that may contain commas (e.g. "Turing machine, and foundations...").
std::vector<std::string> parseCSVLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (inQuotes) {
            if (c == '"') {
                // Check for an escaped quote ("")
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
    const std::string filename = "computer_scientists.csv";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return 1;
    }

    std::string line;
    bool isHeader = true;
    std::vector<std::string> headers;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::vector<std::string> fields = parseCSVLine(line);

        if (isHeader) {
            headers = fields;
            isHeader = false;
            continue; // skip printing the header row itself
        }

        for (size_t i = 0; i < fields.size(); ++i) {
            std::string label = (i < headers.size()) ? headers[i] : ("Field" + std::to_string(i));
            std::cout << label << ": " << fields[i] << std::endl;
        }
        std::cout << "----------------------------------------" << std::endl;
    }

    file.close();
    return 0;
}