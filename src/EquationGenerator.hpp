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
#include "lib.hpp"

using namespace std;
using namespace Cell;

class EquationGenerator {
private:
    int m_width, m_height, m_startNode = 0, m_maxNumberLength = 7;
    int **eNumber = new int*[3];
    NumericCell *nCell;
    OperatorCell *oCell;
    int numberOfNONnull;
    int  newY, newX;
    vector < vector < CoreCell * > > *m_adjMatrix;
    vector < vector < int > > *m_adjList;
    vector < node > *m_nodeList;
    vector < vector < bool > > m_visited;
    vector < bool > m_Visited;
    const string m_oList[4] = {"+", "×", "-", "÷"};
    int nextCell[3] = {0, 2 , 4};
    void DFS (const int n);
    string detOpr (short numberOfNONnull);
    void detNum (short numberOfNONnull, char o);
    void setMathEQ (int n);
    int gcd(int a, int b);
    void setMaxNumberLength(int newLength);

public:
    EquationGenerator();
    EquationGenerator(int height, int width);
    void setWidth(int width);
    void setHeight(int height);
    void generateEquation (int startNode, vector < vector < CoreCell * > > *adjMatrix,
                           vector < vector < int > > *adjList, vector < node > *nodeList);
    void generateEquation (vector < vector < CoreCell * > > *adjMatrix,
                           vector < vector < int > > *adjList, vector < node > *nodeList);
    void generateEquation ();
    int getCellLenght();
};

