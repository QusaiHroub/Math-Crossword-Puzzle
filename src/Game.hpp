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

#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "GridBuilder.hpp"

using namespace std;
using namespace Cell;

class Game {
private:
    vector < vector < CoreCell *> > *m_adjMatrix;
    vector < vector < node > > *m_adjList;
    const char m_oList[4] = {'+', '×', '-', '÷'};
    int m_at[3] = {0, 2, 4};
    int m_height, m_width, m_max = 9, m_per;
    GridBuilder m_GridBuilder;
    int detPer(int n, int m);
    void printList();
    void printGame();
    vector < string > __toString();

public:
    Game(int height, int width, int per);
    Game();
    void init (int height, int width, int per);
    void newGame (int startY, int startX, int height, int width, bool isVerticale);
    void setWidth (int width);
    void setHeight (int height);
    int getWidth ();
    int getHeight ();
    void playGame ();
};
