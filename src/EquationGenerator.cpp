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

#include "EquationGenerator.hpp"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>

using namespace std;


EquationGenerator::EquationGenerator() {
    EquationGenerator(6, 6);
}
EquationGenerator::EquationGenerator(int height, int width) {
    setHeight(height);
    setWidth(width);
}

void EquationGenerator::setHeight(int height) {
    if (height < 6) {
        height = 6;
    }
    m_height = height;
}

void EquationGenerator::setWidth(int width) {
    if (width < 6 ) {
        width = 6;
    }
    m_width = width;
}

int EquationGenerator::getCellLenght () {
    return m_maxNumberLength + 2;
}
void EquationGenerator::setMaxNumberLength(int newLength) {
    if (newLength > m_maxNumberLength) {
        m_maxNumberLength = newLength;
    }
}


void EquationGenerator::generateEquation (int startNode, vector < vector < CoreCell * > > *adjMatrix,
                                          vector < vector < int > > *adjList, vector < node > *nodeList) {
    m_startNode = startNode;
    generateEquation(adjMatrix, adjList, nodeList);
}

void EquationGenerator::generateEquation (vector < vector < CoreCell * > > *adjMatrix,
                                          vector < vector < int > > *adjList, vector < node > *nodeList) {
    m_adjMatrix = adjMatrix;
    m_adjList = adjList;
    m_nodeList = nodeList;
    generateEquation();
}

void EquationGenerator::generateEquation (){
    m_visited.assign(m_height, vector < bool >(m_width, 0));
    m_Visited.assign(m_nodeList->size(), 0);
    m_maxNumberLength = 7;
    for (int i = 0; i < 3; i++) {
        eNumber[i] = nullptr;
    }
    NumericCell *nCell = dynamic_cast<NumericCell *>((*m_adjMatrix)[(*m_nodeList)[m_startNode].y][(*m_nodeList)[m_startNode].x]);
    nCell->setValue(to_string((rand() % 89) + 10));
    setMaxNumberLength(nCell->getValue().size());
    nCell->setState(false);
    DFS(m_startNode);
}

void EquationGenerator::DFS(const int n) {
    if (m_Visited[n]) {
        return;
    }
    m_Visited[n] = true;
    for (int i = 0; i < 3; i++) {
        newX = (*m_nodeList)[n].x + (!((*m_nodeList)[n].isVerticale) * nextCell[i]);
        newY = (*m_nodeList)[n].y + ((*m_nodeList)[n].isVerticale * nextCell[i]);
        nCell = dynamic_cast<NumericCell *>((*m_adjMatrix)[newY][newX]);
        if (nCell->getValue() == "") {
            delete eNumber[i];
            eNumber[i] = nullptr;
        } else {
            delete eNumber[i];
            eNumber[i] = new int(stoi(nCell->getValue()));
        }
    }
    numberOfNONnull = 0;
    for (int v = 0 ; v < 3; v++) {
        if (eNumber[v] != 0) {
            numberOfNONnull++;
        }
    }
    newX = (*m_nodeList)[n].x + (!((*m_nodeList)[n].isVerticale));
    newY = (*m_nodeList)[n].y + ((*m_nodeList)[n].isVerticale);
    oCell =  dynamic_cast<OperatorCell *> ((*m_adjMatrix)[newY][newX]);
    oCell->setValue(detOpr(numberOfNONnull));
    oCell->setState(false);
    detNum(numberOfNONnull, *(oCell->getValue().begin()));
    setMathEQ(n);
    for (int i = 0; i < (*m_adjList)[n].size(); i++) {
        DFS((*m_adjList)[n][i]);
    }
}

string EquationGenerator::detOpr (short numberOfNONnull) {
    int nullptrI = 0;
    switch(numberOfNONnull) {
        case 1: {
            int oI = 0;
            for (int i = 1; i < 3; i++) {
                if (eNumber[i] != 0){
                    oI = i;
                }
            }
            if (eNumber[oI] == 0 && oI != 3) {
                return "+";
            }
            break;
        } case 2: {
            for (int i = 1; i < 3; i++ ) {
                if ( eNumber[i] == 0 ) {
                    nullptrI = i;
                }
            }
            switch (nullptrI) {
                case 0:
                    int r;
                    if (*eNumber[1] < *eNumber[2]) {
                        if (*eNumber[1] != 0 && *eNumber[2] % *eNumber[1] == 0)
                            r = rand() % 2;
                        else
                            r = 0;
                    } else if (*eNumber[1] != 0 && *eNumber[2] % *eNumber[1] == 0){
                        r = (rand() % 2) + 2;
                    } else {
                        r = 2;
                    }
                    return m_oList[r];
                case 1:
                    if (*eNumber[0] < *eNumber[2]) {
                        if (*eNumber[0] != 0 && *eNumber[2] % *eNumber[0] == 0) {
                            return m_oList[rand() % 2];
                        }
                        return "+";
                    } else {
                        if (*eNumber[2] != 0 && *eNumber[0] % *eNumber[2] == 0) {
                            return m_oList[(rand() % 2) + 2];
                        }
                        return "-";
                    }
                default:
                    if (*eNumber[0] > *eNumber[1]) {
                        if (*eNumber[1] != 0 && *eNumber[0] % *eNumber[1] == 0) {
                            return m_oList[rand() % 4];
                        }
                        return m_oList[rand() % 3];
                    } else {
                        return m_oList[rand() % 2];
                    }
            }
            break;
        } case 3: {
            int maxI = 0;
            for (int i = 1; i < 3; i++) {
                if (*eNumber[i] > *eNumber[maxI]) {
                    maxI = i;
                }
            }
            switch (maxI) {
                case 0:
                    if (*eNumber[0] - *eNumber[1] == *eNumber[2]) {
                        if (*eNumber[1] != 0 && *eNumber[0] / *eNumber[1] == *eNumber[2]) {
                            return m_oList[(rand() % 2) + 2];
                        }
                        return "-";
                    } else  if (*eNumber[1] != 0 && *eNumber[0] / *eNumber[1] == *eNumber[2]) {
                        return "÷";
                    } else {
                        // bug
                        return "?";
                    }
                case 1:
                    // bug ...
                    return "?";
                default:
                    if (*eNumber[0] + *eNumber[1] == *eNumber[2]) {
                        if (*eNumber[0] * *eNumber[1] == *eNumber[2]) {
                            return m_oList[rand() % 2];
                        } else {
                            return "+";
                        }
                    } else if (*eNumber[0] * *eNumber[1] == *eNumber[2]) {
                        return "×";
                    } else {
                        // bug ...
                        return "?";
                    }
            }
            break;
        }
    }
    return m_oList[rand() % 4];
}

void EquationGenerator::detNum (short numberOfNONnull, char o) {
    if (numberOfNONnull == 3)
        return;
    int r;
    switch (numberOfNONnull) {
        case 1: {
            int oI = 0;
            for (int i = 1; i< 3; i++) {
                if (eNumber[i] != 0){
                    oI = i;
                }
            }
            switch(oI) {
                case 0:
                    switch (o) {
                        case '-':
                            r = rand() % (abs(*eNumber[0] - 1) == 0 ? 11 : abs(*eNumber[0] - 1) ) + 1;
                            eNumber[1] = new int (r);
                            eNumber[2] = new int (*eNumber[0] - r);
                            break;
                        case '+':
                            r = (rand() % 89) + 10;
                            eNumber[1] = new int (r);
                            eNumber[2] = new int (*eNumber[0] + r);
                            break;
                        case '×':
                            r = (rand() % 11) + 2;
                            eNumber[1] = new int (r);
                            eNumber[2] = new int (*eNumber[0] * r);
                            break;
                        case '÷':
                            r = (rand() % 11) + 2;
                            if (*eNumber[0] % r != 0) {
                                r = gcd (*eNumber[0], r);
                            }
                            eNumber[1] = new int (r);
                            eNumber[2] = new int (*eNumber[0] / r);
                            break;
                    }
                    break;
                case 1:
                    switch (o) {
                        case '-':
                            r = (rand() % (89 + *eNumber[1])) + 10;
                            if (r < *eNumber[1]) {
                                eNumber[2] = new int (r);
                                eNumber[0] = new int (r + *eNumber[1]);
                            } else {
                                eNumber[0] = new int (r);
                                eNumber[2] = new int (*eNumber[0] - *eNumber[1]);
                            }
                            break;
                        case '+':
                            r = (rand() % 89) + 10;
                            eNumber[0] = new int (r);
                            eNumber[2] = new int (*eNumber[1] + r);
                            break;
                        case '×':
                            r = (rand() % 11) + 2;
                            eNumber[0] = new int (r);
                            eNumber[2] = new int (*eNumber[1] * r);
                            break;
                        case '÷':
                            r = (rand() % 11) + 2;
                            eNumber[0] = new int (*eNumber[1] * r);
                            eNumber[2] = new int (r);
                            break;
                    }
                    break;
                default:
                    switch (o) {
                        case '-':
                            r = (rand() % 89) + 10;
                            eNumber[0] = new int (r + *eNumber[2]);
                            eNumber[1] = new int (r);
                            break;
                        case '+':
                            r = (rand() % ((abs(*eNumber[2] - 1)) == 0 ? 11 : abs(*eNumber[2] - 1)) + 1) + 2;
                            eNumber[0] = new int (r);
                            eNumber[1] = new int (*eNumber[2] - r);
                            break;
                        case '×':
                            r = (rand() % 11) + 2;
                            if (*eNumber[2] % r != 0) {
                                    r = gcd(r, *eNumber[2]);
                            }
                            eNumber[0] = new int (r);
                            eNumber[1] = new int (*eNumber[2] / r);
                            break;
                        case '÷':
                            r = (rand() % 11) + 2;
                            eNumber[0] = new int (*eNumber[2] * r);
                            eNumber[1] = new int (r);
                            break;
                    }
                    break;
            }
            break;
        }
        case 2:
            {
            int nullptrI = 0;
            for (int i = 1; i< 3; i++) {
                if (eNumber[i] == 0){
                    nullptrI = i;
                }
            }
            switch(nullptrI) {
                case 0:
                    switch (o) {
                        case '-':
                            eNumber[0] = new int (*eNumber[2] + *eNumber[1]);
                            break;
                        case '+':
                            eNumber[0] = new int (*eNumber[2] - *eNumber[1]);
                            break;
                        case '×':
                            if (*eNumber[1] == 0) {
                                eNumber[0] = new int(0);
                                break;
                            }
                            eNumber[0] = new int (*eNumber[2] / *eNumber[1]);
                            break;
                        case '÷':
                            eNumber[0] = new int (*eNumber[2] * *eNumber[1]);
                            break;
                    }
                    break;
                case 1:
                    switch (o) {
                        case '-':
                            eNumber[1] = new int (*eNumber[0] - *eNumber[2]);
                            break;
                        case '+':
                            eNumber[1] = new int (*eNumber[2] - *eNumber[0]);
                            break;
                        case '×':
                            if (*eNumber[0] == 0) {
                                eNumber[0] = new int(0);
                                break;
                            }
                            eNumber[1] = new int (*eNumber[2] / *eNumber[0]);
                            break;
                        case '÷':
                            eNumber[1] = new int (*eNumber[0] / *eNumber[2]);
                            break;
                    }
                    break;
                default:
                    switch (o) {
                        case '-':
                            eNumber[2] = new int (*eNumber[0] - *eNumber[1]);
                            break;
                        case '+':
                            eNumber[2] = new int (*eNumber[0] + *eNumber[1]);
                            break;
                        case '×':
                            eNumber[2] = new int (*eNumber[0] * *eNumber[1]);
                            break;
                        case '÷':
                            eNumber[2] = new int (*eNumber[0] / *eNumber[1]);
                            break;
                    }
                    break;
            }
            break;
        }
    }
}

void EquationGenerator::setMathEQ (int n) {
    string cellNewValue;
    int ctr = 0, rTime = 1;
    if (m_nodeList->at(n).isVerticale) {
        int newY = m_nodeList->at(n).y % 2;
        for (int k = m_nodeList->at(n).y; k < m_nodeList->at(n).y + 5; k ++ ){
            if ((k + newY) % 2 == 0) {
                if (!m_visited[k][m_nodeList->at(n).x]) {
                    bool is;
                    if (rTime) {
                        is = rand() % 7;
                    } else {
                        is = 0;
                    }
                    if (k == m_nodeList->at(n).y + 4) {
                        is = rTime;
                    }
                    NumericCell *nCell = dynamic_cast<NumericCell *> ((*m_adjMatrix)[k][m_nodeList->at(n).x]);
                    cellNewValue = to_string(*eNumber[ctr]);
                    setMaxNumberLength(cellNewValue.size());
                    nCell->setValue(cellNewValue);
                    nCell->setState(is);
                    m_visited[k][m_nodeList->at(n).x] = true;
                    rTime -= is;
                }
                ctr++;
            }
        }
    } else {
        int newX = m_nodeList->at(n).x % 2;
        for (int k = m_nodeList->at(n).x; k < m_nodeList->at(n).x + 5; k ++ ){
            if ((k + newX) % 2 == 0) {
                if (!m_visited[m_nodeList->at(n).y][k]) {
                    bool is;
                    if (rTime) {
                        is = rand() % 7;
                    } else {
                        is = 0;
                    }
                    if (k == m_nodeList->at(n).x + 4) {
                        is = rTime;
                    }
                    NumericCell *nCell = dynamic_cast<NumericCell *> ((*m_adjMatrix)[m_nodeList->at(n).y][k]);
                    cellNewValue = to_string(*eNumber[ctr]);
                    setMaxNumberLength(cellNewValue.size());
                    nCell->setValue(cellNewValue);
                    nCell->setState(is);
                    m_visited[m_nodeList->at(n).y][k] = true;
                    rTime -= is;

                }
                ctr++;
            }
        }
    }
}

int EquationGenerator::gcd(int a, int b) {
    while (b != 0) {
        int t = a;
        a = b;
        b = t % b;
    }
    return a;
}
