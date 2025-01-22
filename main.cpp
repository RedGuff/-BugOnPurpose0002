#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Function to read a CSV file into a 2D vector
vector<vector<string>> readCSV(const string& filename) {
    vector<vector<string>> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    file.close();
    return data;
}

// Function to display a 2D vector
void displayCSV(const vector<vector<string>>& data) {
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            cout << row[i];
            if (i < row.size() - 1) {
                cout << ",";
            }
        }
        cout << endl;
    }
}

// Function to transpose a 2D vector
vector<vector<string>> transpose(const vector<vector<string>>& data) {
    if (data.empty()) return {};

    size_t numRows = data.size();
    size_t numCols = data[0].size();
    vector<vector<string>> transposed(numCols, vector<string>(numRows));

    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            transposed[j][i] = data[i][j];
        }
    }

    return transposed;
}

// Function to write a 2D vector to a CSV file
void writeCSV(const string& filename, const vector<vector<string>>& data) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not write to file " << filename << endl;
        return;
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << ",";
            }
        }
        file << endl;
    }

    file.close();
}

int main() {
    string inputFilename, outputFilename;

    cout << "Enter the input CSV filename: ";
    cin >> inputFilename;

    vector<vector<string>> data = readCSV(inputFilename);

    if (data.empty()) {
        cerr << "No data read from file." << endl;
        return 1;
    }

    cout << "\nOriginal CSV Data:" << endl;
    displayCSV(data);

    vector<vector<string>> transposedData = transpose(data);

    cout << "\nTransposed CSV Data:" << endl;
    displayCSV(transposedData);

    cout << "Enter the output CSV filename: ";
    cin >> outputFilename;

    writeCSV(outputFilename, transposedData);

    cout << "Transposed data saved to " << outputFilename << endl;
    return 0;
}
