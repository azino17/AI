#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

struct Node;

struct Edge {
    Node* target;
    double cost;
    Edge(Node* t, double c) : target(t), cost(c) {}
};

struct Node {
    string value;
    vector<Edge> adjacencies;
    double g_scores = numeric_limits<double>::infinity();  // Cost from start to this node
    double h_scores;                                       // Heuristic estimate to goal
    double f_scores = numeric_limits<double>::infinity();  // g + h
    Node* parent = nullptr;

    Node(const string& val, double h) : value(val), h_scores(h) {}

    // For priority queue ordering by f_scores (lowest first)
    bool operator>(const Node& other) const {
        return f_scores > other.f_scores;
    }
};

struct NodeComparator {
    bool operator()(Node* lhs, Node* rhs) {
        return lhs->f_scores > rhs->f_scores; // Min-heap based on f_scores
    }
};

vector<Node*> printPath(Node* target) {
    vector<Node*> path;
    for (Node* node = target; node != nullptr; node = node->parent) {
        path.push_back(node);
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<Node*> AstarSearch(Node* source, Node* goal) {
    unordered_set<Node*> explored;
    vector<Node*> visitedOrder;

    priority_queue<Node*, vector<Node*>, NodeComparator> queue;

    source->g_scores = 0;
    source->f_scores = source->h_scores;
    queue.push(source);

    int step = 1;

    while (!queue.empty()) {
        Node* current = queue.top();
        queue.pop();
        visitedOrder.push_back(current);
        explored.insert(current);

        cout << "\nStep " << step++ << ": Expanding Node: " << current->value << "\n";

        if (current == goal) break;

        for (auto& e : current->adjacencies) {
            Node* child = e.target;
            double cost = e.cost;
            double temp_g = current->g_scores + cost;
            double temp_f = temp_g + child->h_scores;

            cout << " Neighbor: " << child->value
                 << " | g=" << temp_g
                 << " | h=" << child->h_scores
                 << " | f=" << temp_f << "\n";

            if (explored.find(child) != explored.end() && temp_f >= child->f_scores) {
                continue;
            }

            if (temp_f < child->f_scores) {
                child->parent = current;
                child->g_scores = temp_g;
                child->f_scores = temp_f;
                queue.push(child);
            }
        }
    }

    return visitedOrder;
}

int main() {
    // Create nodes with heuristic values
    Node n1("Pune", 366);
    Node n2("Amravati", 374);
    Node n3("Mumbai", 380);
    Node n4("Kolhapur", 253);
    Node n5("Solapur", 178);
    Node n6("Sangli", 193);
    Node n7("Ratnagiri", 98);
    Node n8("Latur", 329);
    Node n9("Nagpur", 244);
    Node n10("Nanded", 241);
    Node n11("SambhajiNagar", 242);
    Node n12("Nashik", 160);
    Node n13("Gadchiroli", 0);  // Goal node
    Node n14("Buldhana", 77);

    // Define edges
    n1.adjacencies = {Edge(&n2, 75), Edge(&n4, 140), Edge(&n8, 118)};
    n2.adjacencies = {Edge(&n1, 75), Edge(&n3, 71)};
    n3.adjacencies = {Edge(&n2, 71), Edge(&n4, 151)};
    n4.adjacencies = {Edge(&n1, 140), Edge(&n5, 99), Edge(&n3, 151), Edge(&n6, 80)};
    n5.adjacencies = {Edge(&n4, 99), Edge(&n13, 211)};
    n6.adjacencies = {Edge(&n4, 80), Edge(&n7, 97), Edge(&n12, 146)};
    n7.adjacencies = {Edge(&n6, 97), Edge(&n13, 101), Edge(&n12, 138)};
    n8.adjacencies = {Edge(&n1, 118), Edge(&n9, 111)};
    n9.adjacencies = {Edge(&n8, 111), Edge(&n10, 70)};
    n10.adjacencies = {Edge(&n9, 70), Edge(&n11, 75)};
    n11.adjacencies = {Edge(&n10, 75), Edge(&n12, 120)};
    n12.adjacencies = {Edge(&n11, 120), Edge(&n6, 146), Edge(&n7, 138)};
    n13.adjacencies = {Edge(&n7, 101), Edge(&n14, 90), Edge(&n5, 211)};
    n14.adjacencies = {Edge(&n13, 90)};

    // Run A* from Pune to Gadchiroli
    vector<Node*> visitedNodes = AstarSearch(&n1, &n13);

    cout << "\n---------------- Visited Nodes ----------------\n";
    int count = 1;
    for (Node* node : visitedNodes) {
        cout << count++ << ". " << node->value << " (f=" << node->f_scores << ")\n";
    }

    cout << "\n---------------- Final Path ----------------\n";
    vector<Node*> path = printPath(&n13);
    double totalCost = 0;

    for (size_t i = 0; i < path.size(); i++) {
        Node* current = path[i];
        cout << current->value << " (g=" << current->g_scores << ")";
        if (i < path.size() - 1) {
            cout << " -> ";
            // Find edge cost to next node
            for (auto& e : current->adjacencies) {
                if (e.target == path[i + 1]) {
                    totalCost += e.cost;
                    break;
                }
            }
        }
    }
    cout << "\n\nTotal Path Cost: " << totalCost << endl;

    return 0;
}
