#include "Cell.hpp"

using namespace Cell;

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
    string str = "";
    for (int i = 0; i < getLength(); i++) {
        str += " ";
    }
    return str;
}

string OperatorCell::toString () {
    string str = "";
    int n = getLength() - getValue().length();
    for (int i = 0; i < n/ 2; i++) {
        str += " ";
    }
    str+= getValue();
    for (int i = 0; i < n/ 2; i++) {
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
    string str = "";
    if (m_visible) {
        int n = getLength() - getValue().length();
        for (int i = 0; i < n/ 2; i++) {
            str += " ";
        }
        str+= getValue();
        for (int i = 0; i < n/ 2 + n % 2; i++) {
            str += " ";
        }
    } else {
        int n = getLength() - m_gValue.length();
        for (int i = 0; i < n/ 2; i++) {
            str += " ";
        }
        str+= m_gValue;
        for (int i = 0; i < n/ 2 + n % 2; i++) {
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
void NumericCell::setV(bool v) {
    m_visible = v;
}
bool NumericCell::getV() {
    return m_visible;
}
string NumericCell::getGValue () {
    if (!m_state)
        return m_value;
    return m_gValue;
}
void NumericCell::setGValue (string val) {
    m_gValue = val;
}
