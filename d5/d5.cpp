#include <bits/stdc++.h>
#define ll long long

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

void part1(vector<string>& lines) {
    vector<string> seeds_input = split(lines[0].substr(7), " ");

    vector<ll> seeds;
    for (string s : seeds_input) {
        seeds.push_back(stoll(s));
    }

    int i = 2;
    while (i < lines.size()) {
        i++;

        vector<tuple<ll, ll, ll>> events;
        while (i < lines.size() && !lines[i].empty()) {
            vector<string> temp = split(lines[i], " ");
            events.push_back({stoll(temp[1]), stoll(temp[0]), stoll(temp[2])});
            i++;
        }
        sort(events.begin(), events.end());

        vector<ll> nxt;
        for (ll seed : seeds) {
            auto it = *prev(lower_bound(events.begin(), events.end(), make_tuple(seed, 0, 0)));

            ll s = get<0>(it), d = get<1>(it), l = get<2>(it);
            if (s <= seed <= s + l)
                nxt.push_back(d + (seed - s));
            else
                nxt.push_back(seed);
        }

        i++;
        seeds = nxt;
    }

    cout << *min_element(seeds.begin(), seeds.end()) << endl;
}

void part2(vector<string>& lines) {
    vector<string> seeds_input = split(lines[0].substr(7), " ");

    vector<ll> seeds;
    for (string s : seeds_input) {
        seeds.push_back(stoll(s));
    }

    vector<tuple<ll, ll>> ranges;
    for (int i = 0; i < seeds.size(); i += 2) {
        ranges.push_back({seeds[i], seeds[i + 1]});
    }

    int i = 2;
    while (i < lines.size()) {
        sort(ranges.begin(), ranges.end());

        i++;
        vector<tuple<ll, ll, ll>> events;
        while (i < lines.size() && !lines[i].empty()) {
            vector<string> tmp = split(lines[i], " ");
            events.push_back({stoll(tmp[1]), stoll(tmp[0]), stoll(tmp[2])});
            i++;
        }
        sort(events.begin(), events.end());

        vector<tuple<ll, ll>> nxt;
        ll s, d, l, start, length;
        for (auto& e : events) {
            tie(s, d, l) = e;
            for (int j = 0; j < ranges.size(); j++) {
                if (get<1>(ranges[j]) == 0) continue;

                tie(start, length) = ranges[j];

                if (s + l < start || start + length < s) continue;

                if (start < s) {
                    nxt.push_back({d, start + length - s});
                    ranges[j] = {start, s - start};
                } else if (start + length <= s + l) {
                    nxt.push_back({d + (start - s), length});
                    ranges[j] = {start, 0};
                } else {
                    nxt.push_back({d + (start - s), (s + l) - start});
                    ranges[j] = {s + l, (start + length) - (s + l)};
                }
            }
        }

        for (auto& r : ranges) {
            if (get<1>(r) != 0) {
                nxt.push_back(r);
            }
        }

        i++;
        ranges = nxt;
    }

    ll res = LLONG_MAX;
    for (auto& r : ranges) res = min(res, get<0>(r));
    cout << res << endl;
}

int main() {
    ifstream inputFile("d5.in");
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
