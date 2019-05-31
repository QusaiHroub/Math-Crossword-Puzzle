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


void EquationGenerator::generateEquation (int startY, int startX, vector < vector < CoreCell * > > *adjMatrix) {
    m_startY = startY;
    m_startX = startX;
    generateEquation(adjMatrix);
}

void EquationGenerator::generateEquation (vector < vector < CoreCell * > > *adjMatrix) {
    m_adjMatrix = adjMatrix;
    generateEquation();
}

void EquationGenerator::generateEquation (){
    srand(time(0));
    m_visited.assign(m_height, vector < bool >(m_width, 0));
    NumericCell *nCell = dynamic_cast<NumericCell *>((*m_adjMatrix)[m_startY][m_startX]);
    nCell->setValue(to_string((rand() % 89) + 10));
    setMaxNumberLength(nCell->getValue().size());
    nCell->setState(false);
    for (int k = 0; k < 4; k++) {
        int newX, newY;
        newY = m_startY + y_d[k];
        newX = m_startX + x_d[k];
        if (newY >= 0 && newX >= 0 && newY < m_adjMatrix->size() && newX < (*m_adjMatrix)[newY].size()) {
            if (typeid(*(*m_adjMatrix)[newY][newX]) == typeid(OperatorCell)) {
                OperatorCell *aboCell = dynamic_cast<OperatorCell *>((*m_adjMatrix)[newY][newX]);
                if (aboCell->getValue() == "X") {
                    DFS(m_startY, m_startX, newX == m_startX);
                }
            }
        }
    }
}

void EquationGenerator::DFS (const int y, const int x, bool isV) {
    int **eNumber = new int*[3];
    for (int i = 0; i < 3; i ++) {
        (eNumber[i]) = nullptr;
    }
    NumericCell *nCell;
    OperatorCell *oCell;
    if (isV) {
        if (m_visited[y + 1][x]) {
            return;
        }
        m_visited[y + 1][x] = true;
        nCell = dynamic_cast<NumericCell *>((*m_adjMatrix)[y][x]);
        if (nCell->getValue() == "") {
            delete eNumber[0];
            eNumber[0] = nullptr;
        } else {
            delete eNumber[0];
            eNumber[0] = new int(stoi(nCell->getValue()));
        }
        nCell = dynamic_cast<NumericCell *>((*m_adjMatrix)[y + 2][x]);
        if (nCell->getValue() == "") {
            delete eNumber[1];
            eNumber[1] = nullptr;
        } else {
            delete eNumber[1];
            eNumber[1] = new int (stoi(nCell->getValue()));
        }
        nCell = dynamic_cast<NumericCell *>((*m_adjMatrix)[y + 4][x]);
        if (nCell->getValue() == "") {
            delete eNumber[2];
            eNumber[2] = nullptr;
        } else {
            delete eNumber[2];
            eNumber[2] = new int(stoi(nCell->getValue()));
        }
        // bug when all value in eNumber equals to 0
        int numberOfNONnull = 0;
        for (int v = 0 ; v < 3; v++) {
            if (eNumber[v] != 0) {
                numberOfNONnull++;
            }
        }
        oCell = dynamic_cast<OperatorCell *>((*m_adjMatrix)[y + 1][x]);
        oCell->setValue(detOpr(eNumber, numberOfNONnull));
        oCell->setState(false);
        detNum(eNumber, numberOfNONnull, oCell->getValue());
        setMathEQ(y, x, eNumber, true);
        // TODO

    } else {
        if (m_visited[y][x + 1]) {
            return;
        }
        m_visited[y][x + 1] = true;
        nCell = dynamic_cast<NumericCell *>((*m_adjMatrix)[y][x]);
        if (nCell->getValue() == "") {
            delete eNumber[0];
            eNumber[0] = nullptr;
        } else {
            delete eNumber[0];
            eNumber[0] = new int(stoi(nCell->getValue()));
        }
        nCell = dynamic_cast<NumericCell *>((*m_adjMatrix)[y][x + 2]);
        if (nCell->getValue() == "") {
            delete eNumber[1];
            eNumber[1] = nullptr;
        } else {
            delete eNumber[1];
            eNumber[1] = new int (stoi(nCell->getValue()));
        }
        nCell = dynamic_cast<NumericCell *>((*m_adjMatrix)[y][x + 4]);
        if (nCell->getValue() == "") {
            delete eNumber[2];
            eNumber[2] = nullptr;
        } else {
            delete eNumber[2];
            eNumber[2] = new int(stoi(nCell->getValue()));
        }
        // bug when all value in eNumber equals to 0
        int numberOfNONnull = 0;
        for (int v = 0 ; v < 3; v++) {
            if (eNumber[v] != 0) {
                numberOfNONnull++;
            }
        }
        oCell = dynamic_cast<OperatorCell *> ((*m_adjMatrix)[y][x + 1]);
        oCell->setValue(detOpr(eNumber, numberOfNONnull));
        oCell->setState(false);
        detNum(eNumber, numberOfNONnull, oCell->getValue());
        setMathEQ(y,x, eNumber, false);
        // TODO
    }
    for (int i = 0; i < 3; i ++) {
        delete (eNumber[i]);
    }
    delete eNumber;
    int  newY, newX, a, b;
    for (int l = 0; l < 3; l++ ) {
        newY = y;
        newX = x;
        newY += isV ? nextCell[l] : 0;
        newX += !isV ? nextCell[l] : 0;
        for (int k = 0; k < 4; k++) {
            a = newY + y_d[k];
            b = newX + x_d[k];
            if (a >= 0 && b >= 0 && a < m_adjMatrix->size() && b < (*m_adjMatrix)[a].size()) {
                if (typeid(*(*m_adjMatrix)[a][b]) == typeid(OperatorCell)) {
                    oCell = dynamic_cast<OperatorCell *>((*m_adjMatrix)[a][b]);
                    if (oCell->getValue() == "X") {
                        if (b == newX) {
                            if  (y_d[k] == -1) {
                                newY -= 2;
                            }
                        } else if (x_d[k] == -1) {
                            newX -= 2;
                        }
                        DFS(newY,newX, b == newX);
                    } else if (oCell->getValue() == "="){
                        OperatorCell *__oCell;
                        if (b == newX) {
                            __oCell = dynamic_cast<OperatorCell *>((*m_adjMatrix)[a - 2][b]);
                            if  (y_d[k] == -1 && __oCell->getValue() == "X") {
                                newY -= 4;
                                DFS(newY,newX, b == newX);
                            } else if (y_d[k] == 1 && __oCell->getValue() == "X"){
                                newY -= 2;
                                DFS(newY,newX, b == newX);
                            }
                        } else {
                            __oCell = dynamic_cast<OperatorCell *>((*m_adjMatrix)[a][b - 2]);
                            if  (x_d[k] == -1 && __oCell->getValue() == "X") {
                                newX -= 4;
                                DFS(newY,newX, b == newX);
                            } else if (x_d[k] == 1 && __oCell->getValue() == "X"){
                                newX -= 2;
                                DFS(newY,newX, b == newX);
                            }
                        }
                    }
                }
            }
        }
    }
}


string EquationGenerator::detOpr (int **eNumber, int numberOfNONnull) {
    int nullptrI = 0;
    switch(numberOfNONnull) {
        case 1: {
            int oI = 0;
            for (int i = 1; i< 3; i++) {
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
                    if (*eNumber[1] > 0 && *eNumber[1] < *eNumber[2]) {
                        if (*eNumber[2] % *eNumber[1] == 0)
                            r = rand() % 2;
                        else
                            r = 0;
                    } else if (*eNumber[1] > 0 && *eNumber[2] % *eNumber[1] == 0){
                        r = (rand() % 2) + 2;
                    } else {
                        r = 2;
                    }
                    return m_oList[r];
                case 1:
                    if (*eNumber[0] < *eNumber[2]) {
                        if (*eNumber[0] > 0 && *eNumber[2] % *eNumber[0] == 0) {
                            return m_oList[rand() % 2];
                        }
                        return "+";
                    } else {
                        if (*eNumber[0] % *eNumber[2] == 0) {
                            return m_oList[(rand() % 2) + 2];
                        }
                        return "-";
                    }
                default:
                    if (*eNumber[0] > *eNumber[1]) {
                        if (*eNumber[1] > 0 && rand() % 2 && *eNumber[0] % *eNumber[1] == 0) {
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
                        if (*eNumber[0] / *eNumber[1] == *eNumber[2]) {
                            return m_oList[(rand() % 2) + 2];
                        }
                        return "-";
                    } else  if (*eNumber[0] / *eNumber[1] == *eNumber[2]) {
                        return "÷";
                    } else {
                        // bug
                        return " ";
                    }
                case 1:
                    // bug ...
                    return " ";
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
                        return " ";
                    }
            }
            break;
        }
    }
    return m_oList[rand() % 4];
}

int otoi(string o) {
    if (o == "-") {
        return 0;
    }
    if (o == "+") {
        return 1;
    }
    if (o == "×") {
        return 2;
    }
    return 3;
}

void EquationGenerator::detNum (int **eNumber, int numberOfNONnull, string o) {
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
                    switch (otoi(o)) {
                        case 0:
                            r = rand() % (abs(*eNumber[0] - 1) == 0 ? 10 : abs(*eNumber[0] - 1) ) + 1;
                            eNumber[1] = new int (r);
                            eNumber[2] = new int (*eNumber[0] - r);
                            break;
                        case 1:
                            r = (rand() % 89) + 10;
                            eNumber[1] = new int (r);
                            eNumber[2] = new int (*eNumber[0] + r);
                            break;
                        case 2:
                            r = (rand() % 10) + 2;
                            eNumber[1] = new int (r);
                            eNumber[2] = new int (*eNumber[0] * r);
                            break;
                        case 3:
                            r = (rand() % 10) + 2;
                            if (*eNumber[0] % r != 0) {
                                r = gcd (*eNumber[0], r);
                            }
                            eNumber[1] = new int (r);
                            eNumber[2] = new int (*eNumber[0] / r);
                            break;
                    }
                    break;
                case 1:
                    switch (otoi(o)) {
                        case 0:
                            r = (rand() % (89 + *eNumber[1])) + 10;
                            if (r < *eNumber[1]) {
                                eNumber[2] = new int (r);
                                eNumber[0] = new int (r + *eNumber[1]);
                            } else {
                                eNumber[0] = new int (r);
                                eNumber[2] = new int (*eNumber[0] - *eNumber[1]);
                            }
                            break;
                        case 1:
                            r = (rand() % 89) + 10;
                            eNumber[0] = new int (r);
                            eNumber[2] = new int (*eNumber[1] + r);
                            break;
                        case 2:
                            r = (rand() % 10) + 2;
                            eNumber[0] = new int (r);
                            eNumber[2] = new int (*eNumber[1] * r);
                            break;
                        case 3:
                            r = (rand() % 10) + 2;
                            eNumber[0] = new int (*eNumber[1] * r);
                            eNumber[2] = new int (r);
                            break;
                    }
                    break;
                default:
                    switch (otoi(o)) {
                        case 0:
                            r = rand() % ((abs(*eNumber[2] - 1)) <= 0 ? 10 : abs(*eNumber[2] - 1)) + 1;
                            eNumber[0] = new int (r + *eNumber[2]);
                            eNumber[1] = new int (r);
                            break;
                        case 1:
                            r = rand() % ((abs(*eNumber[2] - 1)) <= 0 ? 10 : abs(*eNumber[2] - 1)) + 1;
                            eNumber[0] = new int (r);
                            eNumber[1] = new int (*eNumber[2] - r);
                            break;
                        case 2:
                            r = (rand() % 10) + 2;
                            if (*eNumber[2] % r != 0) {
                                    r = gcd(r, *eNumber[2]);
                            }
                            eNumber[0] = new int (r);
                            eNumber[1] = new int (*eNumber[2] / r);
                            break;
                        case 3:
                            r = (rand() % 10) + 2;
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
                    switch (otoi(o)) {
                        case 0:
                            eNumber[0] = new int (*eNumber[2] + *eNumber[1]);
                            break;
                        case 1:
                            eNumber[0] = new int (*eNumber[2] - *eNumber[1]);
                            break;
                        case 2:
                            eNumber[0] = new int (*eNumber[2] / *eNumber[1]);
                            break;
                        case 3:
                            eNumber[0] = new int (*eNumber[2] * *eNumber[1]);
                            break;
                    }
                    break;
                case 1:
                    switch (otoi(o)) {
                        case 0:
                            eNumber[1] = new int (*eNumber[0] - *eNumber[2]);
                            break;
                        case 1:
                            eNumber[1] = new int (*eNumber[2] - *eNumber[0]);
                            break;
                        case 2:
                            eNumber[1] = new int (*eNumber[2] / *eNumber[0]);
                            break;
                        case 3:
                            eNumber[1] = new int (*eNumber[0] / *eNumber[2]);
                            break;
                    }
                    break;
                default:
                    switch (otoi(o)) {
                        case 0:
                            eNumber[2] = new int (*eNumber[0] - *eNumber[1]);
                            break;
                        case 1:
                            eNumber[2] = new int (*eNumber[0] + *eNumber[1]);
                            break;
                        case 2:
                            eNumber[2] = new int (*eNumber[0] * *eNumber[1]);
                            break;
                        case 3:
                            eNumber[2] = new int (*eNumber[0] / *eNumber[1]);
                            break;
                    }
                    break;
            }
            break;
        }
    }
}

void EquationGenerator::setMathEQ (int y, int x, int **eNumber, bool isV) {
    string cellNewValue;
    int ctr = 0;
    if (isV) {
        int newY = y % 2;
        for (int k = y; k < y + 5; k ++ ){
            if ((k + newY) % 2 == 0) {
                if (!m_visited[k][x]) {
                    NumericCell *nCell = dynamic_cast<NumericCell *> ((*m_adjMatrix)[k][x]);
                    cellNewValue = to_string(*eNumber[ctr]);
                    setMaxNumberLength(cellNewValue.size());
                    nCell->setValue(cellNewValue);
                    nCell->setState(false);
                    m_visited[k][x] = true;
                }
                ctr++;
            }
        }
    } else {
        int newX = x % 2;
        for (int k = x; k < x + 5; k ++ ){
            if ((k + newX) % 2 == 0) {
                if (!m_visited[y][k]) {
                    NumericCell *nCell = dynamic_cast<NumericCell *> ((*m_adjMatrix)[y][k]);
                    cellNewValue = to_string(*eNumber[ctr]);
                    setMaxNumberLength(cellNewValue.size());
                    nCell->setValue(cellNewValue);
                    nCell->setState(false);
                    m_visited[y][k] = true;
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
