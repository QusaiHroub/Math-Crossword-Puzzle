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
* FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
* more details.
*/

#include "lib.hpp"
#include "Cell.hpp"
#include <vector>

using namespace std;
using namespace Cell;

class GridBuilder {
private:
    vector< vector < CoreCell *> > *m_adjMatrix = new  vector< vector < CoreCell *> >();
    vector< vector < node > > *m_adjList = nullptr;
    int l2List[3][2] = { {0, 1},
                         {1, 2},
                         {0, 2} };
    bool cheak (int i, int j, bool isV, bool isMid, bool dir);
    void freeMem(vector < vector < CoreCell *> > *adjM);
public:
    GridBuilder();
    void init (int n, int m);
    void creatAdjMatrix(vector< vector < CoreCell *> > &adjMatrix, vector< vector < node > > &adjList,
                        int n, int m, int i, int j, bool isV, int __per);
    void creatPuzzle (int n, int m, int i, int j, bool isV);

};
