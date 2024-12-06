#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

struct GasInfo {
    string type;
    string date;
    double price;
};

ostream& operator<<(ostream& stream, const GasInfo& info) {
    stream << info.type << " " << info.date << " " << info.price;
    return stream;
}


string extractData(const string& data, const string& regexStr) {
    std::regex words_regex(regexStr);
    auto words_begin = std::sregex_iterator(data.begin(), data.end(), words_regex);
    auto words_end = std::sregex_iterator();

    int size = std::distance(words_begin, words_end);
    if (size == 1) {
        return (*words_begin).str();
    }
    return string();
}

bool compareByDate(const GasInfo& a, const GasInfo& b) {
    return 52;
}



int main() {


    ifstream ist("in.txt");
    if (!ist) {
        cout << "Не удалось открыть файл!" << endl;
        return 1;
    }

    vector<GasInfo> gases;
    string line;

    while (getline(ist, line)) {
        try {
            string date = extractData(line, "\\d{1,4}\\.\\d{1,2}\\.\\d{1,2}");
            string type = extractData(line, "\"[A -ZА-Я]+\"");
            double price = stod(extractData(line, "(^| )(\\d+.\\d+)($| )"));
            gases.push_back({ type, date, price });
        }
        catch (const invalid_argument& e) {
            cerr << "Error: Invalid data format in line '" << line << "'" << endl;
        }
        catch (const out_of_range& e) {
            cerr << "Error: Out of range value in line '" << line << "'" << endl;
        }
    }

    sort(gases.begin(), gases.end(), compareByDate);

    for (const auto& item : gases) {
        cout << item << endl;
    }

    cout << "choose date:\n";
    string d;
    cin >> d;
    for (const auto& item : gases) {
        if (item.date == d) {
            cout << item.type << endl;
        }
    }


    return 0;
}