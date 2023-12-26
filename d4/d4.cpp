#include <bits/stdc++.h>

using namespace std;

vector<string> split(string s, string delimiter) {
    vector<string> res;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        res.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    token = s.substr(0, pos);
    res.push_back(token);
    return res;
}

vector<string> split_numbers(string& numbersString) {
    std::vector<string> numbers;
    std::istringstream iss(numbersString);
    string num;
    while (iss >> num) {
        numbers.push_back(num);
    }
    return numbers;
}

void part1(vector<string>& lines) {
    int res = 0;

    for (string l : lines) {
        int curr = 0;

        vector<string> numbers = split(split(l, ": ")[1], " | ");

        vector<string> winning = split_numbers(numbers[0]);
        vector<string> mine = split_numbers(numbers[1]);

        set<string> winning_set(winning.begin(), winning.end());

        for (string x : mine) {
            if (winning_set.find(x) != winning_set.end()) {
                ++curr;
            }
        }

        if (curr > 0) res += pow(2, curr - 1);
    }

    cout << res << endl;
}

void part2(vector<string>& lines) {
    int res = 0;
    vector<int> pf = vector<int>(lines.size() + 1, 0);
    pf[0] = 1;
    pf[lines.size() + 1] = -1;

    int cum = 0;

    for (int i = 0; i < lines.size(); i++) {
        string l = lines[i];
        cum += pf[i];
        if (cum == 0) break;
        int curr = 0;
        res += cum;

        vector<string> numbers = split(split(l, ": ")[1], " | ");

        vector<string> winning = split_numbers(numbers[0]);
        vector<string> mine = split_numbers(numbers[1]);

        set<string> winning_set(winning.begin(), winning.end());

        for (string x : mine) {
            if (winning_set.find(x) != winning_set.end()) {
                ++curr;
            }
        }

        if (curr > 0) {
            pf[i + 1] += cum;
            pf[i + 1 + curr] -= cum;
        }
    }

    cout << res << endl;
}

int main() {
    ifstream inputFile("d4.in");
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
