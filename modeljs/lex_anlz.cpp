#include <iostream>
#include<iomanip>
#include <fstream>
#include <ctype.h>
#include <cstring>

#include <vector>

using namespace std;

enum types_lex {
    LEX_PROGRAM,
    LEX_INT, LEX_STRING, LEX_BOOLEAN,
    LEX_FALSE, LEX_TRUE,
    LEX_AND, LEX_OR, LEX_NOT, LEX_IF, LEX_ELSE,
    LEX_WHILE, LEX_BREAK, LEX_READ, LEX_WRITE,
    LEX_LCURLY, LEX_RCURLY, LEX_SEMICOLON, LEX_COMMA, LEX_COLON, LEX_ASSIGN, LEX_LPAREN, LEX_RPAREN,
    LEX_EQ, LEX_LESS, LEX_GREATER, LEX_LEQ, LEX_NEQ, LEX_GEQ,
    LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH,
    LEX_NUM, LEX_ID, LEX_STRLITERAL,
    LEX_NULL,
};

class Lex {
    types_lex type_;
    int val_;
public:
    Lex(types_lex new_t = LEX_NULL, int new_val = 0) : type_(new_t), val_(new_val) {}

    types_lex get_type() const { return type_; }

    int get_val() const { return val_; }

    friend ostream &operator<<(ostream &os, const Lex out_lex) {
        os << "type = ";
        switch (out_lex.get_type()) {
            case LEX_PROGRAM:
                os << left << setw(15) << "LEX_PROGRAM";
                break;
            case LEX_INT:
                os << left << setw(15) << "LEX_INT";
                break;
            case LEX_STRING:
                os << left << setw(15) << "LEX_STRING";
                break;
            case LEX_BOOLEAN:
                os << left << setw(15) << "LEX_BOOLEAN";
                break;
            case LEX_FALSE:
                os << left << setw(15) << "LEX_FALSE";
                break;
            case LEX_TRUE:
                os << left << setw(15) << "LEX_TRUE";
                break;
            case LEX_AND:
                os << left << setw(15) << "LEX_AND";
                break;
            case LEX_OR:
                os << left << setw(15) << "LEX_OR";
                break;
            case LEX_NOT:
                os << left << setw(15) << "LEX_NOT";
                break;
            case LEX_IF:
                os << left << setw(15) << "LEX_IF";
                break;
            case LEX_ELSE:
                os << left << setw(15) << "LEX_ELSE";
                break;
            case LEX_WHILE:
                os << left << setw(15) << "LEX_WHILE";
                break;
            case LEX_BREAK:
                os << left << setw(15) << "LEX_BREAK";
                break;
            case LEX_READ:
                os << left << setw(15) << "LEX_READ";
                break;
            case LEX_WRITE:
                os << left << setw(15) << "LEX_WRITE";
                break;
            case LEX_LCURLY:
                os << left << setw(15) << "LEX_LCURLY";
                break;
            case LEX_RCURLY:
                os << left << setw(15) << "LEX_RCURLY";
                break;
            case LEX_SEMICOLON:
                os << left << setw(15) << "LEX_SEMICOLON";
                break;
            case LEX_COMMA:
                os << left << setw(15) << "LEX_COMMA";
                break;
            case LEX_COLON:
                os << left << setw(15) << "LEX_COLON";
                break;
            case LEX_ASSIGN:
                os << left << setw(15) << "LEX_ASSIGN";
                break;
            case LEX_LPAREN:
                os << left << setw(15) << "LEX_LPAREN";
                break;
            case LEX_RPAREN:
                os << left << setw(15) << "LEX_RPAREN";
                break;
            case LEX_EQ:
                os << left << setw(15) << "LEX_EQ";
                break;
            case LEX_LESS:
                os << left << setw(15) << "LEX_LESS";
                break;
            case LEX_GREATER:
                os << left << setw(15) << "LEX_GREATER";
                break;
            case LEX_LEQ:
                os << left << setw(15) << "LEX_LEQ";
                break;
            case LEX_NEQ:
                os << left << setw(15) << "LEX_NEQ";
                break;
            case LEX_GEQ:
                os << left << setw(15) << "LEX_GEQ";
                break;
            case LEX_PLUS:
                os << left << setw(15) << "LEX_PLUS";
                break;
            case LEX_MINUS:
                os << left << setw(15) << "LEX_MINUS";
                break;
            case LEX_TIMES:
                os << left << setw(15) << "LEX_TIMES";
                break;
            case LEX_SLASH:
                os << left << setw(15) << "LEX_SLASH";
                break;
            case LEX_NUM:
                os << left << setw(15) << "LEX_NUM";
                break;
            case LEX_ID:
                os << left << setw(15) << "LEX_ID";
                break;
            case LEX_STRLITERAL:
                os << left << setw(15) << "LEX_STRLITERAL";
                break;
            case LEX_NULL:
                os << left << setw(15) << "LEX_NULL";
                break;
        }
        return os << "value = " << out_lex.get_val() << endl;
    }
};

const char *TW[] = {"program", "int", "boolean", "string", "true", "false", "and", "or",
                    "not", "if", "else", "while", "break", "read", "write", NULL};
const char *TD[] = {"{", "}", ";", ",", ":", "=", "(", ")", "==", "<", ">",
                    "<=", "!=", ">=", "+", "-", "*", "/", NULL};

int lex_num(string str, const char **id) {
    int i = 0;

    while ((id[i] != NULL) && (string(id[i])) != str) { i++; }
    if (id[i] == NULL) { return -1; }

    return i;
}

vector<string> TID;
vector<string> TConst;

Lex get_lex() {
    enum state {
        H, IDENT, NUMB, STRING, COM, COMP, SYMB
    };
    char c;
    int n;
    string buf;
    state CS = H;
    while (true) {
        cin.get(c);
        switch (CS) {
            case H:
                if (cin.eof()) {
                    return Lex();
                }
                if (c == ' ' || c == '\n' || c == '\t');
                else if (isalpha(c)) {
                    buf.push_back(c);
                    CS = IDENT;
                } else if (isdigit(c)) {
                    n = c - '0';
                    CS = NUMB;
                } else if (c == '+' || c == '-' || c == '*' || c == '{' || c == '}' || c == ';' || c == ',' || c == ':'
                           || c == '(' || c == ')') {
                    CS = SYMB;
                    cin.unget();
                } else if (c == '/') {
                    if (cin.peek() == '*') {
                        cin.get();
                        CS = COM;
                    } else {
                        cin.unget();
                        CS = SYMB;
                    }
                } else if (c == '=' || c == '>' || c == '<' || c == '!') {
                    if (cin.peek() == '=') {
                        CS = COMP;
                    } else {
                        CS = SYMB;
                    }
                    cin.unget();
                } else if (c == '"') {
                    CS = STRING;
                } else {
                    throw -1;
                }
                break;
            case IDENT:
                if (isdigit(c) || isalpha(c)) {
                    buf.push_back(c);
                } else {
                    cin.unget();
                    int i = lex_num(buf, TW);
                    if (i == -1) {
                        TID.push_back(buf);
                        return Lex(LEX_ID, TID.size() - 1);
                    } else {
                        return Lex((types_lex) i, i);
                    }
                }
                break;
            case NUMB:
                if (isdigit(c)) {
                    n = n * 10 + (c - '0');
                } else {
                    cin.unget();
                    return Lex(LEX_NUM, n);
                }
                break;
            case COM:
                if (cin.eof()) {
                    throw -2;
                }
                if (c == '*') {
                    if (cin.peek() == '/') {
                        cin.get(c);
                        CS = H;
                    } else {
                        cin.unget();
                    }
                }
                break;
            case STRING:
                if (cin.eof()) {
                    throw -3;
                }
                if (c != '"') {
                    buf.push_back(c);
                } else {
                    TConst.push_back(buf);
                    return Lex(LEX_STRLITERAL, TConst.size() - 1);
                }
                break;
            case COMP: {  // {}
                string s1 = "";
                s1.push_back(c);
                s1.push_back(cin.get());
                int i1 = lex_num(s1, TD);
                return Lex((types_lex) (i1 + 15), i1);
                break;
            }
            case SYMB:
                string ss = "";
                ss.push_back(c);
                int ii = lex_num(ss, TD);
                return Lex((types_lex) (ii + 15), ii);
                break;
        }
    }
}

int main() {
    Lex lex;

    while (true) {
        lex = get_lex();
        if (lex.get_type() == LEX_NULL)
            break;
        else
            cout << lex;
    }

    return 0;
}
