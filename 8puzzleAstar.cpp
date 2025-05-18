#include <iostream>
#include <queue>
#include <unordered_map>
#include <set>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct Node {
    string state;
    int zero_pos;
    int g;  // Cost from start to current
    int h;  // Heuristic cost to goal
    int f;  // Total cost = g + h
    char move;        // Move taken to reach this state (U,D,L,R) or 'S' for start
    string parent;    // Parent state string

    // Comparator for priority queue (min-heap)
    bool operator>(const Node &other) const {
        return f > other.f;
    }
};

const vector<int> dx = {-1, 1, 0, 0};
const vector<int> dy = {0, 0, -1, 1};
const vector<char> move_char = {'U', 'D', 'L', 'R'};
const string goal = "123804765";

int toIndex(int r, int c) {
    return r * 3 + c;
}

// Calculate Manhattan distance heuristic
int manhattan(const string &state) {
    int dist = 0;
    for (int i = 0; i < 9; i++) {
        if (state[i] == '0') continue; // Skip blank tile
        int val = state[i] - '1'; // values 0 to 7
        int curr_r = i / 3;
        int curr_c = i % 3;
        int goal_r = val / 3;
        int goal_c = val % 3;
        dist += abs(curr_r - goal_r) + abs(curr_c - goal_c);
    }
    return dist;
}

void printState(const string &state) {
    for (int i = 0; i < 9; i++) {
        if (state[i] == '0') cout << "  ";
        else cout << state[i] << ' ';
        if ((i + 1) % 3 == 0) cout << '\n';
    }
    cout << '\n';
}

int main() {
    string start_state;
    cout << "Enter the start state (use 0 for blank) as 9 digits (e.g. 123406758): ";
    cin >> start_state;

    int start_zero = start_state.find('0');

    priority_queue<Node, vector<Node>, greater<Node>> open_set;
    set<string> closed_set;
    unordered_map<string, Node> parent_map;

    int h_start = manhattan(start_state);
    Node start_node = {start_state, start_zero, 0, h_start, h_start, 'S', ""};
    open_set.push(start_node);
    parent_map[start_state] = start_node;

    Node goal_node;
    bool found = false;

    while (!open_set.empty()) {
        Node curr = open_set.top();
        open_set.pop();

        if (curr.state == goal) {
            goal_node = curr;
            found = true;
            break;
        }

        closed_set.insert(curr.state);

        int r = curr.zero_pos / 3;
        int c = curr.zero_pos % 3;

        for (int i = 0; i < 4; i++) {
            int nr = r + dx[i];
            int nc = c + dy[i];
            if (nr >= 0 && nr < 3 && nc >= 0 && nc < 3) {
                int new_pos = toIndex(nr, nc);
                string new_state = curr.state;
                swap(new_state[curr.zero_pos], new_state[new_pos]);

                if (closed_set.find(new_state) != closed_set.end()) continue;

                int g_new = curr.g + 1;
                int h_new = manhattan(new_state);
                int f_new = g_new + h_new;

                // Check if better path or new node
                if (parent_map.find(new_state) == parent_map.end() || f_new < parent_map[new_state].f) {
                    Node next_node = {new_state, new_pos, g_new, h_new, f_new, move_char[i], curr.state};
                    open_set.push(next_node);
                    parent_map[new_state] = next_node;
                }
            }
        }
    }

    if (!found) {
        cout << "No solution found." << endl;
        return 0;
    }

    // Reconstruct path
    vector<Node> path;
    Node cur = goal_node;
    while (cur.move != 'S') {
        path.push_back(cur);
        cur = parent_map[cur.parent];
    }
    path.push_back(cur);

    cout << "\nSolution steps (total moves: " << goal_node.g << "):\n\n";

    for (int i = (int)path.size() - 1; i >= 0; i--) {
        if (path[i].move == 'S') {
            cout << "Step " << path.size() - 1 - i << ": Start State\n";
        } else {
            cout << "Step " << path.size() - 1 - i << ": Move " << path[i].move << '\n';
        }
        printState(path[i].state);
    }

    return 0;
}
