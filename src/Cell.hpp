#include <string>

using namespace std;

namespace Cell {

class CoreCell {
private :
    int m_lenght = 7;
public:
    virtual string toString() = 0;
    void setLength(int newLingth);
    int getLength();
    CoreCell(int len);
    CoreCell();
};

class ValuedCell : public CoreCell {
protected:
    string m_value;
    bool m_state = true;
public:
    virtual void setValue (string value) = 0;
    virtual string getValue() = 0;
    virtual void setState(bool s) = 0;
    ValuedCell();
    ValuedCell(int len);
    ValuedCell(string value, int len);
};

class BlockedCell : public CoreCell {
public:
    string toString();
};

class OperatorCell : public ValuedCell {
public:
    string toString ();
    string getValue ();
    void setValue ( string v);
    bool getState ();
    void setState ( bool s);
    OperatorCell (string __value, bool s);
    OperatorCell(string Value);
};

class NumericCell : public ValuedCell{
private:
    bool m_visible = true;
    string m_gValue = "";
public:
    string toString ();
    string getValue ();
    void setValue ( string v);
    bool getState ();
    void setState ( bool s);
    NumericCell ();
    NumericCell (string Value);
    NumericCell (string Value, bool s);
    void setV(bool v);
    bool getV();
    string getGValue ();
    void setGValue (string val);
};

}
