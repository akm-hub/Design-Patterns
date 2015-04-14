/**
  * @purpose     Demonstrate Interpreter design pattern
  *              Convert a Roman number to decimal number
  *
  * @description Map a domain to a language, the language to a grammar, and the
  *              grammar to a hierarchical object-oriented design.
  *              
  * @author      Ashish
  * @license     MIT license
  * @version     1.0, Doxygen compatible comments
  */

#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Interpreter {
 private:
    Interpreter *thousands;
    Interpreter *hundreds;
    Interpreter *tens;
    Interpreter *ones;

 public:
    Interpreter();
    Interpreter(bool);  /// to avoid infinite recursion of constructor calls

    int interpret(const string&);  /// interpret() for client
    virtual void interpret(string &input, int &total);

 protected:
    virtual string one() {};
    virtual string four() {};
    virtual string five() {};
    virtual string nine() {};
    virtual int multiplier() {};
};

class Thousand: public Interpreter {
 public:
    /// provide parameterized constructor to 
    /// avoid infinite loop in base class constructor
    Thousand(int): Interpreter(false){}
 protected:
    string one() {
        return "M";
    }
    string four() {
        return "";
    }
    string five() {
        return "";
    }
    string nine() {
        return "";
    }
    int multiplier() {
        return 1000;
    }
};

class Hundred: public Interpreter {
 public:
    Hundred(int) : Interpreter(false){}
 protected:
    string one() {
        return "C";
    }
    string four() {
        return "CD";
    }
    string five() {
        return "D";
    }
    string nine() {
        return "CM";
    }
    int multiplier() {
        return 100;
    }
};

class Ten: public Interpreter {
  public:
    Ten(int): Interpreter(false){}
  protected:
    string one() {
        return "X";
    }
    string four() {
        return "XL";
    }
    string five() {
        return "L";
    }
    string nine() {
        return "XC";
    }
    int multiplier() {
        return 10;
    }
};

class One: public Interpreter {
 public:
    One(int): Interpreter(false){}
 protected:
    string one() {
        return "I";
    }
    string four() {
        return "IV";
    }
    string five() {
        return "V";
    }
    string nine() {
        return "IX";
    }
    int multiplier() {
        return 1;
    }
};

Interpreter::Interpreter(bool dummy) {
}

Interpreter::Interpreter() {
    thousands = new Thousand(false);
    hundreds = new Hundred(false);
    tens = new Ten(false);
    ones = new One(false);
}

void Interpreter::interpret(string& input, int &total) {
    // for internal use
    int index;
    index = 0;
    if (!input.compare(0, 2, nine())) {
        total += 9 * multiplier();
        index += 2;
    } else if (!input.compare(0, 2, four())) {
        total += 4 * multiplier();
        index += 2;
    } else {
        if (!input.compare(0, 1, five())) {
            total += 5 * multiplier();
            index = 1;
        } else {
            index = 0;
        }
  
        for (int end = index + 3; index < end; index++) {
            if (!input.compare(index, 1, one())) {
                total += 1 * multiplier();
            } else {
                break;
            }
        }
    }
    input = input.substr(index);  /// remove leading chars processed
}

int Interpreter::interpret(const string &roman_number) {
    string input = roman_number;
    int total = 0;
    if (!input.empty()) {
        thousands->interpret(input, total);
        hundreds->interpret(input, total);
        tens->interpret(input, total);
        ones->interpret(input, total);
        if (!input.empty())
            total = 0;
    }
    return total;
}

int main() {
    Interpreter interpreter;
    string input = "MCMXCVI";
    cout << input << " interpretation is " << interpreter.interpret(input) << endl;
    input = "MMMCMXCIX";
    cout << input << " interpretation is " << interpreter.interpret(input) << endl;
    input = "MMMM";
    cout << input << " interpretation is " << interpreter.interpret(input) << endl;
    input = "MDCLXVIIII";
    cout << input << " interpretation is " << interpreter.interpret(input) << endl;
    input = "CXCX";
    cout << input << " interpretation is " << interpreter.interpret(input) << endl;
    input = "MDCLXVI";
    cout << input << " interpretation is " << interpreter.interpret(input) << endl;
    input = "DCCCLXXXVIII";
    cout << input << " interpretation is " << interpreter.interpret(input) << endl;
    return 0;
}

