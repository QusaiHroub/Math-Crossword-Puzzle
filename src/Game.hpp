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
#include <time.h>
#include <stdlib.h>
#include "GridBuilder.hpp"
#include "EquationGenerator.hpp"
#include "Checker.hpp"

using namespace std;
using namespace Cell;

class Game {
private:
    vector < vector < CoreCell *> > *m_adjMatrix;
    vector < vector < int > > *m_adjList;
    vector < node > *m_nodeList;
    int m_at[3] = {0, 2, 4};
    int m_height, m_width, m_cellLength = 9;
    double m_per;
    GridBuilder m_GridBuilder;
    EquationGenerator m_EquationGenerator;
    Checker m_Checker;
    double detPer(int n, int m);
    void printList();
    void printGame();
    vector < string > __toString();

public:
    Game(int height, int width, int per);
    Game();
    ~Game();
    void init (int height, int width, double per);
    void newGame (int startY, int startX, int height, int width, bool isVerticale);
    void setWidth (int width);
    void setHeight (int height);
    int getWidth ();
    int getHeight ();
    void playGame ();
};
