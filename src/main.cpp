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

#include <iostream>
#include "Game.hpp"
#include <stdio.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

Game *game;
bool isVerticale;
int height = 20, width = 20;

void printList() {
    cout << "1- Start new Game..." << endl
        << "5- Exit." << endl
        << "Chose one : ";
}

void init () {
    game = new Game();
    srand(time(NULL));
    int startY = 0, startX = 0;
    isVerticale = rand() % 2;
    if (isVerticale) {
        startY = rand() % (height - 5);
        if (startY < 0)
            startY = 0;
    } else {
        startX = rand() % (width - 5);
        if (startX < 0)
            startX = 0;
    }
    game->newGame(startX, startX, height, width, isVerticale);
    game->playGame();
}

int main() {
    int yourChoice = 0;
    while (printList(), cin >> yourChoice) {
        switch(yourChoice) {
            case 1:
                cout << "Enter grid size (h , w), max (100, 100), min (6, 6) : ";
                cin >> height >> width;
                if (height < 6) {
                    height = 6;
                }
                if (width < 6) {
                    width = 6;
                }
                if (height > 100) {
                    height = 100;
                }
                if (width > 100) {
                    width = 100;
                }
                init();
                break;
            case 5:
                goto exit;
        }
    }
    exit:
    delete game;
    return 0;
}
