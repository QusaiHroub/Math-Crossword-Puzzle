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

using namespace Cell;

CoreCell::~CoreCell() {

}

int CoreCell::m_lenght = 7;

CoreCell::CoreCell(int len) {
    CoreCell::setLength(len);
}

CoreCell::CoreCell(){}

void CoreCell::setLength(int newLength) {
    if (newLength < 7) {
        newLength = 7;
    }
    CoreCell::m_lenght = newLength;
}

int CoreCell::getLength() {
    return CoreCell::m_lenght;
}

ValuedCell::ValuedCell(){}

ValuedCell::ValuedCell(int len): CoreCell(len) {
}

ValuedCell::ValuedCell(string value, int len) : CoreCell(len){
    m_value = value;
}

string BlockedCell::toString () {
    string str;
    str.assign(getLength(), ' ');
    return str;
}

string OperatorCell::toString () {
    string str;
    int n = getLength() - getValue().length();
    int m = n / 2;
    str.assign(m, ' ');
    str += getValue();
    m += (n & 1);
    for (int i = 0; i < m; i++) {
        str += " ";
    }
    return str;
}
string OperatorCell::getValue () {
    return m_value;
}
void OperatorCell::setValue ( string v) {
        if (m_state) {
            m_value = v;
        }
    }
bool OperatorCell::getState () {
    return m_state;
}
void OperatorCell::setState ( bool s) {
    if (m_state) {
        m_state = s;
    }
}
OperatorCell::OperatorCell (string __value, bool s) {
    setValue(__value);
    setState(s);
}
OperatorCell::OperatorCell(string Value) {
    setValue(Value);
}

string NumericCell::toString () {
    string str;
    if (!getState()) {
        int n = getLength() - getValue().length();
        int m = n / 2;
        str.assign(m, ' ');
        str += getValue();
        m += (n & 1);
        for (int i = 0; i < m; i++) {
            str += " ";
        }
    } else {
        int n = getLength() - getGValue().length();
        int m = n / 2;
        str.assign(m, ' ');
        str+= m_gValue;
        m += (n & 1);
        for (int i = 0; i < m; i++) {
            str += " ";
        }
    }
    return str;
}
string NumericCell::getValue () {
    return m_value;
}
void NumericCell::setValue ( string v) {
    if (m_state) {
        m_value = v;
    }
}
bool NumericCell::getState () {
    return m_state;
}
void NumericCell::setState ( bool s) {
    m_state = s;
}
NumericCell::NumericCell () {}
NumericCell::NumericCell (string Value) {
    setValue(Value);
}
NumericCell::NumericCell (string Value, bool s) {
    setValue(Value);
    setState(s);
}
string NumericCell::getGValue () {
    if (!m_state)
        return m_value;
    return m_gValue;
}
void NumericCell::setGValue (string val) {
    m_gValue = val;
}
