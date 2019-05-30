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
#include <iostream>

using namespace std;

Game::Game(){}

Game::~Game(){
    m_GridBuilder.freeMem(m_adjMatrix);
}

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
    if (x < 100) {
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
    m_GridBuilder.creatAdjMatrix(&m_adjMatrix, &m_adjList, m_height, m_width, startY, startX, isVerticale, per);
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
    for (int j = 0; j < (*m_adjMatrix)[0].size();j++) {
        if (typeid(*(*m_adjMatrix)[0][j]) != typeid(BlockedCell)) {
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
    for (int i = 0; i < (*m_adjMatrix).size(); i++) {
        string sline = "";
        line = "";
        bool __is;
        for (int j = 0; j < (*m_adjMatrix)[i].size(); j++) {
            __is = false;
            if (j == 0) {
                if (typeid(*(*m_adjMatrix)[i][j]) != typeid(BlockedCell)) {
                    sline += "|";
                } else {
                    sline += " ";
                }
            } else {
                if (typeid(*(*m_adjMatrix)[i][j]) == typeid(BlockedCell) && j > 0 && typeid(*(*m_adjMatrix)[i][j - 1]) != typeid(BlockedCell)) {
                    sline += "|";
                } else if (typeid(*(*m_adjMatrix)[i][j]) == typeid(BlockedCell)) {
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

            sline += (*m_adjMatrix)[i][j]->toString();
            if (j == (*m_adjMatrix)[i].size() - 1 && typeid(*(*m_adjMatrix)[i][j]) != typeid(BlockedCell)) {
                sline += "|";
            }
        }
        __is = true;
        for (int j = 0; j < (*m_adjMatrix)[i].size();j++) {
            if ((typeid(*(*m_adjMatrix)[i][j]) != typeid(BlockedCell)) || (i < (*m_adjMatrix).size() - 1 && (typeid(*(*m_adjMatrix)[i + 1][j]) != typeid(BlockedCell)))) {
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

void Game::printGame() {
    vector < string > slist = __toString();
    printf("\n%5s    ", " ");
    for (int i = 0; i < m_width; i++ ) {
        if (i > 9) {
            printf("   %2d   ", i);
        } else {
            printf("    %d   ", i);
        }
    }
    cout << endl << endl;
    printf("%5s    %s\n", " ",slist[0].c_str());
    int ctr = 0;
    for (int i = 1; i < slist.size(); i += 2) {
        printf("%5d    %s\n", ctr, slist[i].c_str());
        printf("%5s    %s\n", " ", slist[i + 1].c_str());
        ctr++;
    }
    cout << endl;
}
void Game::printList() {
    cout << "1- Enter new value..." << endl
        << "2- Cheak Solution." << endl
        << "3- End game." << endl
        << "Chose one : ";
}

void Game::playGame () {
    printGame();
    printList();
    int choice, x , y, newValue;
    bool getNewValue;
    bool isEnded = false;
    while (cin >> choice && !isEnded) {
        switch (choice) {
            case 1 :
                getNewValue = true;
                while (getNewValue) {
                    cout << "Enter x , y , new value : ";
                    cin >> x >> y >> newValue;
                    if (typeid(*(*m_adjMatrix)[y][x]) == typeid(BlockedCell) || typeid(*(*m_adjMatrix)[y][x]) == typeid(OperatorCell)) {
                        cout << "Locked cell, Try with another Cell.." << endl;
                    } else {
                        NumericCell *nCell = dynamic_cast<NumericCell*>((*m_adjMatrix)[y][x]);
                        if (!nCell->getState()) {
                            cout << "Locked cell, Try with another Cell.." << endl;
                        } else {
                            getNewValue = false;
                            nCell->setGValue(to_string(newValue));
                            printGame();
                        }
                    }
                }
                break;
            case 2:

                break;
            case 3:
                isEnded = true;
                m_GridBuilder.freeMem(m_adjMatrix);
                return;
        }
        if (!isEnded)
            printList();
    }
}