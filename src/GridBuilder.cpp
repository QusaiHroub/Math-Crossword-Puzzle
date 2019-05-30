#include "GridBuilder.hpp"
#include <vector>
#include <queue>
#include <time.h>
#include <stdlib.h>

using namespace std;

GridBuilder::GridBuilder() {}

void GridBuilder::freeMem(vector < vector < CoreCell *> > *adjM) {
    for (int i = 0; i < (*adjM).size(); i++) {
        for (int j = 0; j < (*adjM)[i].size(); j++) {
            delete (*adjM)[i][j];
        }
    }
    delete adjM;
    adjM = nullptr;
}


void GridBuilder::init (int n, int m) {
    freeMem(m_adjMatrix);
    m_adjMatrix = new  vector< vector < CoreCell *> >();
    m_adjMatrix->assign(n, vector<CoreCell * > (m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            (*m_adjMatrix)[i][j] = new BlockedCell();
        }
    }
}

void GridBuilder::creatAdjMatrix(vector< vector < CoreCell *> > &adjMatrix, vector< vector < node > > &adjList,
                                 int n, int m, int i, int j, bool isV, int __per) {

    adjList = vector< vector < node > >();
    srand (time(NULL));
    int maxC = (int)((n * m / 5) * (__per / 10.0));
    m_adjList = new vector< vector < node > >();
    while (m_adjList->size() < maxC) {
        delete m_adjList;
        m_adjList = new vector< vector < node > >();
        creatPuzzle(n, m, i, j, isV);
    }
    adjMatrix = *m_adjMatrix;
}

 void GridBuilder::creatPuzzle (int n, int m, int i, int j, bool isV) {
    init(n, m);
    queue<lNode> q;
    lNode list;
    list.isV = isV;
    list.i = i;
    list.j = j;
    list.isMid = false;
    list.dir = true;
    q.push(list);
    while (!q.empty()) {
        lNode head = q.front();
        q.pop();
        if (!cheak(head.i, head.j, head.isV, head.isMid, head.dir)) {
            continue;
        }
        m_adjList->push_back(vector <node> ());
        if (head.isV) {
            int newI = head.i;
            if (!head.dir && !head.isMid) {
                newI -= 4;
            }
            for (int k = newI; k < newI + 5;k++) {
                if (k == newI + 1) {
                    delete (*m_adjMatrix)[k][head.j];
                    (*m_adjMatrix)[k][head.j] = new OperatorCell("X");
                } else if (k == newI + 3) {
                    delete (*m_adjMatrix)[k][head.j];
                    (*m_adjMatrix)[k][head.j] = new OperatorCell("=" , false);
                } else {
                    delete (*m_adjMatrix)[k][head.j];
                    (*m_adjMatrix)[k][head.j] = new NumericCell("0");
                    head.list[head.ctr] = k;
                    head.ctr++;
                }
            }
        } else {
            int newJ = head.j;
            if (!head.dir && !head.isMid) {
                newJ -= 4;
            }
            for (int k = newJ; k < newJ + 5;k++) {
                if (k == newJ + 1) {
                    delete (*m_adjMatrix)[head.i][k];
                    (*m_adjMatrix)[head.i][k] = new OperatorCell("X");
                } else if (k == newJ + 3) {
                    delete (*m_adjMatrix)[head.i][k];
                    (*m_adjMatrix)[head.i][k] = new OperatorCell("=" , false);
                } else {
                    delete (*m_adjMatrix)[head.i][k];
                    (*m_adjMatrix)[head.i][k] = new NumericCell("0");
                    head.list[head.ctr] = k;
                    head.ctr++;
                }
            }
        }
        int newAdj = rand() % 12;
        if ((*m_adjList).size() < ((*m_adjMatrix).size() * (*m_adjMatrix)[0].size() / 5) * 0.3) {
            newAdj = 1;
        }

        switch (newAdj) {
            case 0: case 3: case 6: case 9: case 11:
                for (int k = 0; k < 2; k++){
                    lNode n;
                    int c = rand() % 3;
                    n.j = head.isV ? head.j : head.list[l2List[c][k]];
                    n.i = head.isV ? head.list[l2List[c][k]] : head.i;
                    n.isV = !head.isV;
                    n.isMid = rand() % 2;
                    n.dir = rand() % 2;
                    if(n.isMid && n.isV) {
                        n.i -= 2;
                        n.dir = true;
                    } else if (n.isMid) {
                        n.j -= 2;
                        n.dir = true;
                    }
                    if (n.i < 0 || n.j < 0) {
                        continue;
                    }
                    q.push(n);
                }
                break;
            case 1: case 5: case 7: case 8: case 10:
                for (int k = 0; k < 3; k++) {
                    lNode n;
                    n.j = head.isV ? head.j : head.list[k];
                    n.i = head.isV ? head.list[k] : head.i;
                    n.isV = !head.isV;
                    n.isMid = rand() % 2;
                    n.dir = rand() % 2;
                    if(n.isMid && n.isV) {
                        n.i -= 2;
                        n.dir = true;
                    } else if (n.isMid) {
                        n.j -= 2;
                        n.dir = true;
                    }
                    if (n.i < 0 || n.j < 0) {
                        continue;
                    }
                    q.push(n);
                }
                break;
            default:
                lNode n;
                n.j = head.isV ? head.j : head.list[rand() % 3];
                n.i = head.isV ? head.list[rand() % 3] : head.i;
                n.isV = !head.isV;
                n.isMid = rand() % 2;
                n.dir = rand() % 2;
                if(n.isMid && n.isV) {
                    n.i -= 2;
                    n.dir = true;
                } else if (n.isMid) {
                    n.j -= 2;
                    n.dir = true;
                }
                if (n.i < 0 || n.j < 0) {
                    continue;
                }
                q.push(n);
                break;
        }
    }
}

bool GridBuilder::cheak (int i, int j, bool isV, bool isMid, bool dir) {
    if (isV) {
        if (dir) {
            if (i + 5 > (*m_adjMatrix).size()) {
                return false;
            }
            if (i + 6 < (*m_adjMatrix).size() && (typeid(BlockedCell) != typeid(*(*m_adjMatrix)[i + 5][j]))) {
                return false;
            }
            if (i > 0 && typeid(BlockedCell) != typeid(*(*m_adjMatrix)[i - 1][j])) {
                return false;
            }
            if (typeid(BlockedCell) != typeid(*(*m_adjMatrix)[i + 3][j])
                || typeid(BlockedCell) != typeid(*(*m_adjMatrix)[i + 1][j])) {
                return false;
            }
            if (typeid(*(*m_adjMatrix)[i + 1][j]) == typeid(OperatorCell)) {
                OperatorCell *o = dynamic_cast<OperatorCell*>((*m_adjMatrix)[i + 1][j]);
                if (o->getValue() == "=") {
                    return false;
                }
            }
        } else {
            if (i - 5 < 0) {
                return false;
            }
            if (i - 4 > 0 && typeid(*(*m_adjMatrix)[i - 5][j]) ==  typeid(OperatorCell)) {
                OperatorCell *o = dynamic_cast<OperatorCell*>((*m_adjMatrix)[i - 5][j]);
                if (o->getValue() == "=") {
                    return false;
                }
            }
            if (i + 1 < (*m_adjMatrix).size() && typeid(*(*m_adjMatrix)[i + 1][j]) != typeid(BlockedCell)) {
                return false;
            }
            if (i > 0 && typeid(*(*m_adjMatrix)[i - 1][j]) != typeid(BlockedCell)) {
                return false;
            }
            if (typeid(*(*m_adjMatrix)[i - 1][j]) != typeid(BlockedCell)
                || typeid(*(*m_adjMatrix)[i - 3][j]) != typeid(BlockedCell) ) {
                return false;
            }
            if (typeid(*(*m_adjMatrix)[i - 3][j]) == typeid(OperatorCell)) {
                OperatorCell *o = dynamic_cast<OperatorCell*>((*m_adjMatrix)[i + 1][j]);
                if (o->getValue()== "=") {
                    return false;
                }
            }
        }
    } else {
        if (dir) {
            if (j + 5 > (*m_adjMatrix)[i].size()) {
                return false;
            }
            if (j + 6  < (*m_adjMatrix)[i].size() && typeid(*(*m_adjMatrix)[i][j + 5]) != typeid(BlockedCell)) {
                return false;
            }
            if (j > 0 && typeid(*(*m_adjMatrix)[i][j - 1]) != typeid(BlockedCell)) {
                return false;
            }
            if (typeid(*(*m_adjMatrix)[i][j + 3]) != typeid(BlockedCell)
                || typeid(*(*m_adjMatrix)[i][j + 1]) != typeid(BlockedCell)) {
                return false;
            }
            if (typeid(*(*m_adjMatrix)[i][j + 1]) == typeid(OperatorCell)) {
                OperatorCell *o = dynamic_cast<OperatorCell*>((*m_adjMatrix)[i + 1][j]);
                if (o->getValue() == "=") {
                    return false;
                }
            }
        } else {
            if (j - 5 < 0) {
                return false;
            }
            if (j - 4 > 0 && typeid(*(*m_adjMatrix)[i][j - 5]) ==  typeid(OperatorCell)) {
                OperatorCell *o = dynamic_cast<OperatorCell*>((*m_adjMatrix)[i][j - 5]);
                if (o->getValue() == "=") {
                    return false;
                }
            }
            if (j + 1 < (*m_adjMatrix)[i].size() && typeid(*(*m_adjMatrix)[i][j + 1]) != typeid(BlockedCell)) {
                return false;
            }
            if (j > 0 && typeid(*(*m_adjMatrix)[i][j - 1]) != typeid(BlockedCell)) {
                return false;
            }
            if (typeid(*(*m_adjMatrix)[i][j - 1]) != typeid(BlockedCell)
                || typeid(*(*m_adjMatrix)[i][j - 3]) != typeid(BlockedCell) ) {
                return false;
            }
            if (typeid(*(*m_adjMatrix)[i][j - 3]) == typeid(OperatorCell)) {
                OperatorCell *o = dynamic_cast<OperatorCell*>((*m_adjMatrix)[i + 1][j]);
                if (o->getValue() == "=" ) {
                    return false;
                }
            }
        }
    }
    return true;
}
