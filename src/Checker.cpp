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

#include <vector>
#include <iostream>
#include "Cell.hpp"
#include "Checker.hpp"
#include <string>

using namespace std;
using namespace Cell;

bool Checker::cheakIsAllFill(vector < vector < CoreCell *> > *adjMatrix,
                              vector < vector < int > > *adjList, vector < node > *nodeList) {
    m_adjList = adjList;
    m_adjMatrix = adjMatrix;
    m_nodeList = nodeList;
    m_visited.assign(m_nodeList->size(), 0);
    return DFSForCheakIsAllFill(0);
}

bool Checker::DFSForCheakIsAllFill(int n) {
    if (m_visited[n]) {
        return true;
    }
    m_visited[n] = true;
    NumericCell *nCell;
    for (int i = 0; i < 3; i++) {
        newX = (*m_nodeList)[n].x + (!((*m_nodeList)[n].isVerticale) * nextCell[i]);
        newY = (*m_nodeList)[n].y + ((*m_nodeList)[n].isVerticale * nextCell[i]);
        nCell = dynamic_cast<NumericCell *>((*m_adjMatrix)[newY][newX]);
        if (nCell->getGValue() == "") {
            cout << "Cell " << newX << " " << newY << " is not fill." << endl;
            return false;
        }
    }
    for (int i = 0; i < (*m_adjList)[n].size(); i++) {
        if (DFSForCheakIsAllFill((*m_adjList)[n][i]) == false) {
            return false;
        }
    }
    return true;
}

bool Checker::testSolution (vector < vector < CoreCell *> > *adjMatrix,
                             vector < vector < int > > *adjList, vector < node > *nodeList) {
     m_adjList = adjList;
    m_adjMatrix = adjMatrix;
    m_nodeList = nodeList;
    m_visited.assign(m_nodeList->size(), 0);
    return DFSForTestSolution(0);
}

bool Checker::DFSForTestSolution(int n) {
    if (m_visited[n]) {
        return true;
    }
    m_visited[n] = true;
    NumericCell **nCell = new NumericCell*[3];
    for (int i = 0; i < 3; i++) {
        newX = (*m_nodeList)[n].x + (!((*m_nodeList)[n].isVerticale) * nextCell[i]);
        newY = (*m_nodeList)[n].y + ((*m_nodeList)[n].isVerticale * nextCell[i]);
        nCell[i] = dynamic_cast<NumericCell *> ((*m_adjMatrix)[newY][newX]);
    }
    newX = (*m_nodeList)[n].x + (!((*m_nodeList)[n].isVerticale));
    newY = (*m_nodeList)[n].y + ((*m_nodeList)[n].isVerticale);
    OperatorCell *oCell =  dynamic_cast<OperatorCell *> ((*m_adjMatrix)[newY][newX]);
    if (!getR(*(oCell->getValue().begin()),
            stoi(nCell[0]->getGValue()),
            stoi(nCell[1]->getGValue()),
            stoi(nCell[2]->getGValue()))) {
        cout << "Operator " << newX << " " << newY << " has wrong operand value." << endl;
        return false;
    }
    delete[] nCell;
    for (int i = 0; i < (*m_adjList)[n].size(); i++) {
        if (DFSForTestSolution((*m_adjList)[n][i]) == false) {
            return false;
        }
    }
    return true;
}

bool Checker::getR (char o, int a, int b, int r) {
    switch (o) {
        case '+':
            return a + b == r;
        case '-':
            return a - b == r;
        case '×':
            return a * b == r;
        case '÷':
            if (b == 0) {
                return false;
            }
            return a / b == r;
        case ' ':
            return true;
    }
    return false;
}
