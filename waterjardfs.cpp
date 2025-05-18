#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

struct State {
    int jug1, jug2;
    vector<string> path;

    State(int j1, int j2, const vector<string>& p) : jug1(j1), jug2(j2), path(p) {}

    bool operator<(const State& other) const {
        return jug1 < other.jug1 || (jug1 == other.jug1 && jug2 < other.jug2);
    }
};

void dfs(int cap1, int cap2, int target) {
    stack<State> s;
    set<pair<int,int>> visited;

    s.push(State(0, 0, {}));
    visited.insert({0, 0});

    while (!s.empty()) {
        State current = s.top();
        s.pop();

        int x = current.jug1;
        int y = current.jug2;

        // Check goal condition
        if (x == target || y == target) {
            cout << "Solution found:\n";
            for (auto &step : current.path) {
                cout << step << "\n";
            }
            cout << "(" << x << ", " << y << ")\n";
            return;
        }

        vector<State> nextStates;

        // Fill Jug 1
        nextStates.emplace_back(cap1, y, current.path);
        nextStates.back().path.push_back("Fill Jug1: (" + to_string(cap1) + ", " + to_string(y) + ")");

        // Fill Jug 2
        nextStates.emplace_back(x, cap2, current.path);
        nextStates.back().path.push_back("Fill Jug2: (" + to_string(x) + ", " + to_string(cap2) + ")");

        // Empty Jug 1
        nextStates.emplace_back(0, y, current.path);
        nextStates.back().path.push_back("Empty Jug1: (0, " + to_string(y) + ")");

        // Empty Jug 2
        nextStates.emplace_back(x, 0, current.path);
        nextStates.back().path.push_back("Empty Jug2: (" + to_string(x) + ", 0)");

        // Pour Jug1 -> Jug2
        int pour = min(x, cap2 - y);
        nextStates.emplace_back(x - pour, y + pour, current.path);
        nextStates.back().path.push_back("Pour Jug1 -> Jug2: (" + to_string(x - pour) + ", " + to_string(y + pour) + ")");

        // Pour Jug2 -> Jug1
        pour = min(y, cap1 - x);
        nextStates.emplace_back(x + pour, y - pour, current.path);
        nextStates.back().path.push_back("Pour Jug2 -> Jug1: (" + to_string(x + pour) + ", " + to_string(y - pour) + ")");

        for (auto &state : nextStates) {
            pair<int,int> pos = {state.jug1, state.jug2};
            if (visited.find(pos) == visited.end()) {
                visited.insert(pos);
                s.push(state);
            }
        }
    }
    cout << "No solution possible.\n";
}

int main() {
    int cap1 = 4, cap2 = 3, target = 2;
    dfs(cap1, cap2, target);
    return 0;
}
