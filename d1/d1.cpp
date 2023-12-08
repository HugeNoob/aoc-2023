#include <bits/stdc++.h>

using namespace std;

void part1(const vector<string>& lines) {
    int res;

    for (const string& line : lines) {
        char f = 0, l = 0;
        for (char c : line) {
            if (isdigit(c)) {
                if (f == 0) f = c;
                l = c;
            }
        }

        stringstream s;
        s << f << l;
        int z;
        s >> z;
        res += z;
    }

    cout << res << endl;
}

void part2(const vector<string>& lines) {
    int res;
    unordered_map<string, char> mp{
        {"one", '1'}, {"two", '2'},   {"three", '3'}, {"four", '4'}, {"five", '5'},
        {"six", '6'}, {"seven", '7'}, {"eight", '8'}, {"nine", '9'},
    };

    for (const string& line : lines) {
        char f = 0, l = 0;
        for (int i = 0; i < line.length(); i++) {
            if (isdigit(line[i])) {
                if (f == 0) f = line[i];
                l = line[i];
            } else {
                if (i >= 2 && mp.count(line.substr(i - 2, 3))) {
                    int t = mp.at(line.substr(i - 2, 3));
                    if (f == 0) f = t;
                    l = t;
                } else if (i >= 3 && mp.count(line.substr(i - 3, 4))) {
                    int t = mp.at(line.substr(i - 3, 4));
                    if (f == 0) f = t;
                    l = t;
                } else if (i >= 4 && mp.count(line.substr(i - 4, 5))) {
                    int t = mp.at(line.substr(i - 4, 5));
                    if (f == 0) f = t;
                    l = t;
                }
            }
        }

        stringstream s;
        s << f << l;
        int z;
        s >> z;
        res += z;
    }

    cout << res << endl;
}

int main() {
    ifstream inputFile("d1-in.txt");
    vector<string> lines;
    string line;

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            lines.push_back(line);
        }

        inputFile.close();
    }

    part2(lines);
    return 0;
}