/* mathCrossWordPuzzle
* Copyright 2019 Qusai Hroub.
*
* This file is part of the mathCrossWordPuzzle.
*
* Authors:
* Qusai Hroub <qusaihroub.r@gmail.com>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms and conditions of the GNU General Public License,
* version 3, as published by the Free Software Foundation.
*
* This program is distributed in the hope it will be useful, but WITHOUT ANY
* WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
* more details.
*/

#include "GridBuilder.hpp"
#include <vector>
#include <queue>
#include <time.h>
#include <stdlib.h>

using namespace std;

GridBuilder::GridBuilder() {}

void GridBuilder::freeMem(vector < vector < CoreCell *> > **adjM) {
    if (*adjM == nullptr) {
        return;
    }
    for (int i = 0; i < (*(*adjM)).size(); i++) {
        for (int j = 0; j < (*(*adjM))[i].size(); j++) {
            delete (*(*adjM))[i][j];
        }
    }
    delete (*adjM);
    (*adjM) = nullptr;
}


void GridBuilder::init (int height, int width) {
    freeMem(&m_adjMatrix);
    m_adjMatrix = new  vector< vector < CoreCell *> >();
    m_adjMatrix->assign(height, vector<CoreCell * > (width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            (*m_adjMatrix)[i][j] = new BlockedCell();
        }
    }
}

void GridBuilder::creatAdjMatrix(vector< vector < CoreCell *> > **adjMatrix, vector< vector < node > > **adjList,
                                 int height, int width, int startY, int startX, bool isV, int per) {

    srand (time(NULL));
    int maxC = (int)((height * width / 5) * (per / 11.0));
    m_adjList = new vector< vector < node > >();
    while (m_adjList->size() < maxC) {
        delete m_adjList;
        m_adjList = new vector< vector < node > >();
        creatPuzzle(height, width, startY, startX, isV);
    }
    *adjMatrix = m_adjMatrix;
    *adjList = m_adjList;
}

 void GridBuilder::creatPuzzle (int height, int width, int startY, int startX, bool isV) {
    init(height, width);
    queue<lNode> q;
    lNode list;
    list.isV = isV;
    list.y = startY;
    list.x = startX;
    list.isMid = false;
    list.dir = true;
    q.push(list);
    while (!q.empty()) {
        lNode head = q.front();
        q.pop();
        if (!cheak(head.y, head.x, head.isV, head.isMid, head.dir)) {
            continue;
        }
        m_adjList->push_back(vector <node> ());
        if (head.isV) {
            int newY = head.y;
            if (!head.dir && !head.isMid) {
                newY -= 4;
            }
            for (int k = newY; k < newY + 5;k++) {
                if (k == newY + 1) {
                    delete (*m_adjMatrix)[k][head.x];
                    (*m_adjMatrix)[k][head.x] = new OperatorCell("X");
                } else if (k == newY + 3) {
                    delete (*m_adjMatrix)[k][head.x];
                    (*m_adjMatrix)[k][head.x] = new OperatorCell("=" , false);
                } else {
                    delete (*m_adjMatrix)[k][head.x];
                    (*m_adjMatrix)[k][head.x] = new NumericCell("");
                    head.list[head.ctr] = k;
                    head.ctr++;
                }
            }
        } else {
            int newX = head.x;
            if (!head.dir && !head.isMid) {
                newX -= 4;
            }
            for (int k = newX; k < newX + 5;k++) {
                if (k == newX + 1) {
                    delete (*m_adjMatrix)[head.y][k];
                    (*m_adjMatrix)[head.y][k] = new OperatorCell("X");
                } else if (k == newX + 3) {
                    delete (*m_adjMatrix)[head.y][k];
                    (*m_adjMatrix)[head.y][k] = new OperatorCell("=" , false);
                } else {
                    delete (*m_adjMatrix)[head.y][k];
                    (*m_adjMatrix)[head.y][k] = new NumericCell("");
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
                    n.x = head.isV ? head.x : head.list[l2List[c][k]];
                    n.y = head.isV ? head.list[l2List[c][k]] : head.y;
                    n.isV = !head.isV;
                    n.isMid = rand() % 2;
                    n.dir = rand() % 2;
                    if(n.isMid && n.isV) {
                        n.y -= 2;
                        n.dir = true;
                    } else if (n.isMid) {
                        n.x -= 2;
                        n.dir = true;
                    }
                    if (n.y < 0 || n.x < 0) {
                        continue;
                    }
                    q.push(n);
                }
                break;
            case 1: case 5: case 7: case 8: case 10:
                for (int k = 0; k < 3; k++) {
                    lNode n;
                    n.x = head.isV ? head.x : head.list[k];
                    n.y = head.isV ? head.list[k] : head.y;
                    n.isV = !head.isV;
                    n.isMid = rand() % 2;
                    n.dir = rand() % 2;
                    if(n.isMid && n.isV) {
                        n.y -= 2;
                        n.dir = true;
                    } else if (n.isMid) {
                        n.x -= 2;
                        n.dir = true;
                    }
                    if (n.y < 0 || n.x < 0) {
                        continue;
                    }
                    q.push(n);
                }
                break;
            default:
                lNode n;
                n.x = head.isV ? head.x : head.list[rand() % 3];
                n.y = head.isV ? head.list[rand() % 3] : head.y;
                n.isV = !head.isV;
                n.isMid = rand() % 2;
                n.dir = rand() % 2;
                if(n.isMid && n.isV) {
                    n.y -= 2;
                    n.dir = true;
                } else if (n.isMid) {
                    n.x -= 2;
                    n.dir = true;
                }
                if (n.y < 0 || n.x < 0) {
                    continue;
                }
                q.push(n);
                break;
        }
    }
}

bool GridBuilder::cheak (int y, int x, bool isV, bool isMid, bool dir) {
    if (isV) {
        if (dir) {
            if (y + 5 > (*m_adjMatrix).size()) {
                return false;
            }
            if (y + 6 < (*m_adjMatrix).size() && (typeid(BlockedCell) != typeid(*(*m_adjMatrix)[y + 5][x]))) {
                return false;
            }
            if (y > 0 && typeid(BlockedCell) != typeid(*(*m_adjMatrix)[y - 1][x])) {
                return false;
            }
            if (typeid(BlockedCell) != typeid(*(*m_adjMatrix)[y + 3][x])
                || typeid(BlockedCell) != typeid(*(*m_adjMatrix)[y + 1][x])) {
                return false;
            }
            if (typeid(*(*m_adjMatrix)[y + 1][x]) == typeid(OperatorCell)) {
                OperatorCell *o = dynamic_cast<OperatorCell*>((*m_adjMatrix)[y + 1][x]);
                if (o->getValue() == "=") {
                    return false;
                }
            }
        } else {
            if (y - 5 < 0) {
                return false;
            }
            if (y - 4 > 0 && typeid(*(*m_adjMatrix)[y - 5][x]) ==  typeid(OperatorCell)) {
                OperatorCell *o = dynamic_cast<OperatorCell*>((*m_adjMatrix)[y - 5][x]);
                if (o->getValue() == "=") {
                    return false;
                }
            }
            if (y + 1 < (*m_adjMatrix).size() && typeid(*(*m_adjMatrix)[y + 1][x]) != typeid(BlockedCell)) {
                return false;
            }
            if (y > 0 && typeid(*(*m_adjMatrix)[y - 1][x]) != typeid(BlockedCell)) {
                return false;
            }
            if (typeid(*(*m_adjMatrix)[y - 1][x]) != typeid(BlockedCell)
                || typeid(*(*m_adjMatrix)[y - 3][x]) != typeid(BlockedCell) ) {
                return false;
            }
            if (typeid(*(*m_adjMatrix)[y - 3][x]) == typeid(OperatorCell)) {
                OperatorCell *o = dynamic_cast<OperatorCell*>((*m_adjMatrix)[y + 1][x]);
                if (o->getValue()== "=") {
                    return false;
                }
            }
        }
    } else {
        if (dir) {
            if (x + 5 > (*m_adjMatrix)[y].size()) {
                return false;
            }
            if (x + 6  < (*m_adjMatrix)[y].size() && typeid(*(*m_adjMatrix)[y][x + 5]) != typeid(BlockedCell)) {
                return false;
            }
            if (x > 0 && typeid(*(*m_adjMatrix)[y][x - 1]) != typeid(BlockedCell)) {
                return false;
            }
            if (typeid(*(*m_adjMatrix)[y][x + 3]) != typeid(BlockedCell)
                || typeid(*(*m_adjMatrix)[y][x + 1]) != typeid(BlockedCell)) {
                return false;
            }
            if (typeid(*(*m_adjMatrix)[y][x + 1]) == typeid(OperatorCell)) {
                OperatorCell *o = dynamic_cast<OperatorCell*>((*m_adjMatrix)[y + 1][x]);
                if (o->getValue() == "=") {
                    return false;
                }
            }
        } else {
            if (x - 5 < 0) {
                return false;
            }
            if (x - 4 > 0 && typeid(*(*m_adjMatrix)[y][x - 5]) ==  typeid(OperatorCell)) {
                OperatorCell *o = dynamic_cast<OperatorCell*>((*m_adjMatrix)[y][x - 5]);
                if (o->getValue() == "=") {
                    return false;
                }
            }
            if (x + 1 < (*m_adjMatrix)[y].size() && typeid(*(*m_adjMatrix)[y][x + 1]) != typeid(BlockedCell)) {
                return false;
            }
            if (x > 0 && typeid(*(*m_adjMatrix)[y][x - 1]) != typeid(BlockedCell)) {
                return false;
            }
            if (typeid(*(*m_adjMatrix)[y][x - 1]) != typeid(BlockedCell)
                || typeid(*(*m_adjMatrix)[y][x - 3]) != typeid(BlockedCell) ) {
                return false;
            }
            if (typeid(*(*m_adjMatrix)[y][x - 3]) == typeid(OperatorCell)) {
                OperatorCell *o = dynamic_cast<OperatorCell*>((*m_adjMatrix)[y + 1][x]);
                if (o->getValue() == "=" ) {
                    return false;
                }
            }
        }
    }
    return true;
}
