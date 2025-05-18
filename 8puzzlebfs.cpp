#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

struct Node {
    string state;
    int zero_pos;
    int depth;
    char move;          // Move taken to reach this state (U, D, L, R), or 'S' for start
    string parent;      // Parent state string
};

bool isGoal(const string &state) {
    return state == "123456780";
}

const vector<int> dx = {-1, 1, 0, 0};
const vector<int> dy = {0, 0, -1, 1};
const vector<char> move_char = {'U', 'D', 'L', 'R'};

int toIndex(int row, int col) {
    return row * 3 + col;
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
    queue<Node> q;
    set<string> visited;

    // Map state to Node info to reconstruct path later
    unordered_map<string, Node> parent_map;

    Node start_node = {start_state, start_zero, 0, 'S', ""};
    q.push(start_node);
    visited.insert(start_state);
    parent_map[start_state] = start_node;

    string goal_state = "123804765";
    Node goal_node;
    bool found = false;

    while (!q.empty()) {
        Node curr = q.front(); q.pop();

        if (isGoal(curr.state)) {
            goal_node = curr;
            found = true;
            break;
        }

        int r = curr.zero_pos / 3;
        int c = curr.zero_pos % 3;

        for (int i = 0; i < 4; i++) {
            int nr = r + dx[i];
            int nc = c + dy[i];

            if (nr >= 0 && nr < 3 && nc >= 0 && nc < 3) {
                int new_pos = toIndex(nr, nc);
                string new_state = curr.state;

                swap(new_state[curr.zero_pos], new_state[new_pos]);

                if (visited.find(new_state) == visited.end()) {
                    visited.insert(new_state);
                    Node next_node = {new_state, new_pos, curr.depth + 1, move_char[i], curr.state};
                    q.push(next_node);
                    parent_map[new_state] = next_node;
                }
            }
        }
    }

    if (!found) {
        cout << "No solution found." << endl;
        return 0;
    }

    // Reconstruct path by walking backward from goal to start
    stack<Node> path_stack;
    Node cur = goal_node;
    while (cur.move != 'S') {
        path_stack.push(cur);
        cur = parent_map[cur.parent];
    }
    path_stack.push(cur); // Push the start node

    cout << "\nSolution steps (total moves: " << goal_node.depth << "):\n\n";

    char last_move = 'S';
    int step_num = 0;
    while (!path_stack.empty()) {
        Node step = path_stack.top();
        path_stack.pop();

        if (step.move == 'S') {
            cout << "Step " << step_num << ": Start State\n";
        } else {
            cout << "Step " << step_num << ": Move " << step.move << '\n';
        }

        printState(step.state);
        step_num++;
    }

    return 0;
}
