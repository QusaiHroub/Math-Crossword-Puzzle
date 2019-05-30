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
#include <string>
#include "Cell.hpp"

using namespace std;
using namespace Cell;

class EquationGenerator {
private:
    int m_width, m_height, m_startY, m_startX;
    vector < vector < CoreCell * > > *m_adjMatrix;
    vector < vector < bool > > m_visited;
    const string m_oList[4] = {"+", "×", "-", "÷"};
    int x_d[4] = {0,1,-1,0};
    int y_d[4] = {1,0,0,-1};
    int nextCell[3] = {0, 2 , 4};
    void DFS (const int x, const int y, bool isV);
    string detOpr (int eNumber[], int numberOfNonZero);
    void detNum (int a[], int n, string o);
    void setMathEQ (int y, int x, int a[], bool isV);
    int gcd(int a, int b);


public:
    EquationGenerator();
    EquationGenerator(int height, int width);
    void setWidth(int width);
    void setHeight(int height);
    void generateEquation (int startY, int startX, vector < vector < CoreCell * > > *adjMatrix);
    void generateEquation (vector < vector < CoreCell * > > *adjMatrix);
    void generateEquation ();
};

