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

#include "Cell.hpp"
#include <vector>
#include <string>
#include "lib.hpp"

using namespace std;
using namespace Cell;

class Checker {

private:
    int x_d[4] = {0,1,-1,0};
    int y_d[4] = {1,0,0,-1};
    int nextCell[3] = {0, 2 , 4};
    int newX, newY;
    vector < vector < CoreCell *> > *m_adjMatrix;
    vector < node > *m_nodeList;
    vector < vector < int > > *m_adjList;
    vector < bool > m_visited;
    bool DFSForCheakIsAllFill(int n);
    bool DFSForTestSolution(int n);
    bool getR (string o, int a, int b, int r);

public:
    bool cheakIsAllFill(vector < vector < CoreCell *> > *adjMatrix,
                         vector < vector < int > > *adjList, vector < node > *nodeList);
    bool testSolution (vector < vector < CoreCell *> > *adjMatrix,
                        vector < vector < int > > *adjList, vector < node > *nodeList);

};
