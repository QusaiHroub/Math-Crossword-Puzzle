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

#include "lib.hpp"
#include "Cell.hpp"
#include <vector>

using namespace std;
using namespace Cell;

class GridBuilder {
private:
    int maxC;
    vector< vector < CoreCell *> > *m_adjMatrix = nullptr;
    vector< vector < int > > *m_adjList = nullptr;
    vector< node > *m_nodeList = nullptr;
    int l2List[3][2] = { {0, 1},
                         {1, 2},
                         {0, 2} };
    bool cheak (int y, int x, bool isV, bool isMid, bool dir);

public:
    GridBuilder();
    void init (int height, int width);
    void creatAdjMatrix(vector< vector < CoreCell *> > **adjMatrix, vector< vector < int > > **adjList,
                        vector<node> **nodeList, int height, int width, int startY, int startX, bool isV, double per);
    void creatPuzzle (int height, int width, int startY, int startX, bool isV);
    void freeMem(vector < vector < CoreCell *> > *adjM);

};
