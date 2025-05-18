#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

struct State {
    int jug1, jug2;
    vector<string> path;

    State(int a, int b, vector<string> p) : jug1(a), jug2(b), path(p) {}
};

void bfs(int cap1, int cap2, int target) {
    set<pair<int, int>> visited;
    queue<State> q;

    q.push(State(0, 0, {}));
    visited.insert({0, 0});

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        int x = current.jug1;
        int y = current.jug2;

        if (x == target || y == target) {
            current.path.push_back("Final State: (" + to_string(x) + ", " + to_string(y) + ")");
            cout << "Solution found:\n";
            for (auto &step : current.path) {
                cout << step << endl;
            }
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
            if (visited.find({state.jug1, state.jug2}) == visited.end()) {
                visited.insert({state.jug1, state.jug2});
                q.push(state);
            }
        }
    }

    cout << "No solution possible.\n";
}

int main() {
    int cap1 = 4, cap2 = 3, target = 2;
    cout << "Water Jug Problem using BFS\n";
    cout << "Jug1: " << cap1 << "L, Jug2: " << cap2 << "L, Target: " << target << "L\n\n";
    bfs(cap1, cap2, target);
    return 0;
}
