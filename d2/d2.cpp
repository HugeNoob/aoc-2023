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

void part1(const vector<string>& lines) {
    int res = 0;

    for (const string& line : lines) {
        size_t t = line.find(":");
        string setsData = line.substr(t + 2);
        vector<string> sets = split(setsData, "; ");

        bool ok = true;
        for (auto s : sets) {
            unordered_map<string, int> mp{
                {"red", 0},
                {"blue", 0},
                {"green", 0},
            };
            for (auto c : split(s, ", ")) {
                vector<string> parts = split(c, " ");
                int cnt = stoi(parts[0]);
                string color = parts[1];
                mp[color] += cnt;
            }

            if (mp["red"] > 12 || mp["green"] > 13 || mp["blue"] > 14) {
                ok = false;
            }
        }

        if (ok) {
            res += stoi(line.substr(4, t - 4));
        }
    }

    cout << res << endl;
}

void part2(const vector<string>& lines) {
    int res = 0;

    for (const string& line : lines) {
        size_t t = line.find(":");
        string setsData = line.substr(t + 2);
        vector<string> sets = split(setsData, "; ");

        unordered_map<string, int> mp{
            {"red", 0},
            {"blue", 0},
            {"green", 0},
        };
        for (auto s : sets) {
            for (auto c : split(s, ", ")) {
                vector<string> parts = split(c, " ");
                int cnt = stoi(parts[0]);
                string color = parts[1];
                mp[color] = max(mp[color], cnt);
            }
        }
        res += mp["red"] * mp["blue"] * mp["green"];
    }

    cout << res << endl;
}

int main() {
    ifstream inputFile("d2-in.txt");
    vector<string> lines;
    string line;

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            lines.push_back(line);
        }

        inputFile.close();
    }

    part1(lines);
    part2(lines);
    return 0;
}
