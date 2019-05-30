/* mathCrossWordPuzzle
* Copyright 2019 Qusai Hroub.
*
* This file is part of the mathCrossWordPuzzle.
*
* Authors:
* Qusai Hroub <qusaihroub.r@gmail.com>
*
* This program is free software; you can redislineibute it and/or modify it
* under the terms and conditions of the GNU General Public License,
* version 3, as published by the Free Software Foundation.
*
* This program is dislineibuted in the hope it will be useful, but WITHOUT ANY
* WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
* more details.
*/

#include "Game.hpp"
#include <vector>
#include <string>

Game::Game(){}
void Game::setWidth (int width) {
    if (width < 6) {
        width = 6;
    }
    m_width = width;
}
void Game::setHeight (int height) {
    if (height < 6) {
        height = 6;
    }
    m_height = height;
}
int Game::getWidth (){
    return m_width;
}
int Game::getHeight () {
    return m_height;
}

void Game::init (int height, int width, int per) {
    setWidth(width);
    setHeight(height);
    m_per = per;
}

int Game::detPer(int height, int width){
    int x = height * width;
    if (x <= 100) {
        return 6;
    } else if (x <= 1225) {
        return 5;
    } else if (x <= 5625) {
        return 4;
    }
    return 3;
}

void Game::newGame (int startY, int startX, int height, int width, bool isVerticale) {
    int per = detPer(height, width);
    init(height, width, per);
    m_GridBuilder.creatAdjMatrix(m_adjMatrix, m_adjList, m_height, m_width, startY, startX, isVerticale, per);
}

vector < string >  Game::__toString() {
    vector < string > slist;
    string line = "";
    string s1 = "";
    int c = m_max - 2;
    while (c != 0) {
        s1 += " ";
        c--;
    }
    string s2 = "";
    int c2 = m_max;
    s2 += "+";
    c2--;
    for (int i = 1 ;i < c2; i++){
        s2 += "-";
    }
    s2 += "+";
    string ss = "";
    for (int i = 1 ;i < c2; i++){
        ss += "-";
    }
    ss += "+";
    bool is = true;
    for (int j = 0; j < m_adjMatrix[0].size();j++) {
        if (typeid(*m_adjMatrix[0][j]) != typeid(BlockedCell)) {
            if (is) {
                line += s2;
                is = false;
            } else {
                line += ss;
            }
        } else {
            line += s1;
            if (is) {
                line += " ";
            }
            is = true;
        }
    }
    slist.push_back(line);
    for (int i = 0; i < m_adjMatrix.size(); i++) {
        string sline = "";
        line = "";
        bool __is;
        for (int j = 0; j < m_adjMatrix[i].size(); j++) {
            __is = false;
            if (j == 0) {
                if (typeid(*m_adjMatrix[i][j]) != typeid(BlockedCell)) {
                    sline += "|";
                } else {
                    sline += " ";
                }
            } else {
                if (typeid(*m_adjMatrix[i][j]) == typeid(BlockedCell) && j > 0 && typeid(*m_adjMatrix[i][j - 1]) != typeid(BlockedCell)) {
                    sline += "|";
                } else if (typeid(*m_adjMatrix[i][j]) == typeid(BlockedCell)) {
                    if (__is) {
                        __is = false;
                        sline += "|";
                    } else {
                        sline += " ";
                    }
                } else {
                    sline += "|";
                    __is = true;
                }
            }

            sline += m_adjMatrix[i][j]->toString();
            if (j == m_adjMatrix[i].size() - 1 && typeid(*m_adjMatrix[i][j]) != typeid(BlockedCell)) {
                sline += "|";
            }
        }
        __is = true;
        for (int j = 0; j < m_adjMatrix[i].size();j++) {
            if ((typeid(*m_adjMatrix[i][j]) != typeid(BlockedCell)) || (i < m_adjMatrix.size() - 1 && (typeid(*m_adjMatrix[i + 1][j]) != typeid(BlockedCell)))) {
                if (__is) {
                    line += s2;
                    __is = false;
                } else {
                    line += ss;
                }
            } else {
                line += s1;
                if (__is) {
                    line += " ";
                }
                __is = true;
            }
        }
        slist.push_back(sline);
        slist.push_back(line);
    }
    return slist;
}
