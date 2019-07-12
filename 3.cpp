
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int val;
    int possible;
    vector<pair<int, char> > nextpos;
    vector<pair<int, char> > prevpos;

    Node(int INval, int INpossible) {
        possible = INpossible;
        val = INval;
    }
};

long long int rek(Node * x, Node * y, vector< vector<long long int> > * values, vector<Node*> nodes, int depth) {
    long long int count = 0;
    if ((*values)[x->val][y->val] != -1) {
        count += (*values)[x->val][y->val];
    } else {
        for (int i = 0; i < x->possible; i++) {
            for (int j = 0; (unsigned) j < y->prevpos.size(); j++) {
                if ((x->nextpos[i].first == y->val && y->prevpos[j].first == x->val) ||
                        (x->nextpos[i].first == y->prevpos[j].first && x->nextpos[i].second == y->prevpos[j].second)) {
                    count += 1;
                } else if ((x->nextpos[i].first == y->val && y->prevpos[j].first != x->val) || ((x->nextpos[i].first != y->val && y->prevpos[j].first == x->val)))
                    continue;
                else if (x->nextpos[i].second == y->prevpos[j].second) {
                    count += rek(nodes[x->nextpos[i].first], nodes[y->prevpos[j].first], values, nodes, depth + 1) % 1000000007;
                }
            }
        }
    }
    (*values)[x->val][y->val] = count % 1000000007;
    return count;
}

int createParents(vector<Node*> nodes, Node* start) {
    //    cout<< "pro "<<start->val <<endl;
    for (int i = 0; i < start->possible; i++) {
        Node * current = nodes[start->nextpos[i].first];
        current->prevpos.push_back(make_pair(start->val, start->nextpos[i].second));
        //    cout<<"do:"<< start->nextpos[i].first << start->nextpos[i].second <<" ";
        Node * next = nodes[start->nextpos[i].first];
        createParents(nodes, next);
    }
    return 0;
}

vector<Node*> initVec(vector<Node*> vec, int size) {
    for (int i = 0; i < size; i++) {
        Node* tmp = new Node(i, 0);
        vec.push_back(tmp);
    }
    return vec;
}

int main(int argc, char** argv) {

    vector<Node*> nodes;
    int positions = 0;
    int mistakes = 0;
    int start = 0;
    int end = 0;

    cin >> positions;
    cin >> mistakes;
    cin >> start;
    cin >> end;

    nodes = initVec(nodes, positions);

    for (int i = 0; i < positions; i++) {
        int possible = 0;
        cin >> possible;
        nodes[i]->possible = possible;
        for (int j = 0; j < possible; j++) {
            int val;
            char a;
            cin >> val;
            cin >> a;
            nodes[val]->prevpos.push_back(make_pair(i, a));
            nodes[i]->nextpos.push_back(make_pair(val, a));
        }
    }

    Node * StartNode = nodes[start];
    Node * EndNode = nodes[end];

    vector< vector<long long int> > * values = new vector< vector<long long int> >();
    (*values).resize(positions, vector<long long int>(positions, -1));

    long long int result = rek(StartNode, EndNode, values, nodes, 0);
    cout << result % 1000000007 << endl;
    //    for (int i = 0; i < positions; i++) {
    //        for (int j = 0; j < positions; j++)
    //            cout << "["<<(*values)[i][j]<<"]";
    //        cout << endl;
    //    }
    return 0;
}

