#include <bits/stdc++.h>

using namespace std;

bool isValid(int x, int y, int rows, int cols) { return (x >= 0 && x < rows && y >= 0 && y < cols); }

int getSum(vector<string>& lines, int& r, int& c) {
    int res = 0;

    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        int nr = r + dx[i], nc = c + dy[i];
        if (!isValid(nr, nc, lines.size(), lines[0].length())) continue;

        if (isdigit(lines[nr][nc])) {
            int l = nc, rr = nc;
            while (l - 1 >= 0) {
                if (!isdigit(lines[nr][l - 1])) break;
                l--;
            }

            while (rr + 1 < lines[0].length()) {
                if (!isdigit(lines[nr][rr + 1])) break;
                rr++;
            }

            int t = 0;
            for (int j = l; j <= rr; j++) {
                t = t * 10 + (lines[nr][j] - '0');
                lines[nr][j] = '.';
            }

            res += t;
        }
    }

    return res;
}

void part1(vector<string>& lines) {
    int res = 0;
    int m = lines.size(), n = lines[0].length();

    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            if (!isdigit(lines[r][c]) && lines[r][c] != '.') {
                res += getSum(lines, r, c);
            }
        }
    }

    cout << res << endl;
}

int getGearRatio(vector<string>& lines, int& r, int& c) {
    int res = 1;

    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int cnt = 0;
    for (int i = 0; i < 8; i++) {
        int nr = r + dx[i], nc = c + dy[i];
        if (!isValid(nr, nc, lines.size(), lines[0].length())) continue;

        if (isdigit(lines[nr][nc])) {
            int l = nc, rr = nc;
            while (l - 1 >= 0) {
                if (!isdigit(lines[nr][l - 1])) break;
                l--;
            }

            while (rr + 1 < lines[0].length()) {
                if (!isdigit(lines[nr][rr + 1])) break;
                rr++;
            }

            int t = 0;
            for (int j = l; j <= rr; j++) {
                t = t * 10 + (lines[nr][j] - '0');
                lines[nr][j] = '.';
            }

            if (cnt >= 2) return 0;
            res *= t;
            cnt++;
        }
    }

    return cnt == 2 ? res : 0;
}

void part2(vector<string>& lines) {
    int res = 0;
    int m = lines.size(), n = lines[0].length();

    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            if (lines[r][c] == '*') {
                res += getGearRatio(lines, r, c);
            }
        }
    }

    cout << res << endl;
}

int main() {
    ifstream inputFile("d3-in.txt");
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
