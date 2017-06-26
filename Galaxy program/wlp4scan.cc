//
//  main.cpp
//  wlp4scan.cc
//
//  Created by Siyuan Guo on 2016-11-02.
//  Copyright © 2016 Siyuan Guo. All rights reserved.
//

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

enum Kind{
    ID,
    NUM,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    RETURN,
    IF,
    ELSE,
    WHILE,
    PRINTLN,
    WAIN,
    BECOMES,
    INT,
    EQ,
    NE,
    LT,
    GT,
    LE,
    GE,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    PCT,
    COMMA,
    SEMI,
    NEW,
    DELETE,
    LBRACK,
    RBRACK,
    AMP,
    Null,     //null string
    WHITESPACE,
    COMMENT,
    ERR,
};



const string kindStrings[] ={
    "ID",
    "NUM",
    "LPAREN",
    "RPAREN",
    "LBRACE",
    "RBRACE",
    "RETURN",
    "IF",
    "ELSE",
    "WHILE",
    "PRINTLN",
    "WAIN",
    "BECOMES",
    "INT",
    "EQ",
    "NE",
    "LT",
    "GT",
    "LE",
    "GE",
    "PLUS",
    "MINUS",
    "STAR",
    "SLASH",
    "PCT",
    "COMMA",
    "SEMI",
    "NEW",
    "DELETE",
    "LBRACK",
    "RBRACK",
    "AMP",
    "NULL",     //null string
    "WHITESPACE",
    "COMMENT"
    "ERR",
};

enum State {
    ST_START,
    ST_ID,
    ST_NUM,
    ST_ZERO,
    ST_LPAREN,
    ST_RPAREN,
    ST_LBRACE,
    ST_RBRACE,
    ST_R,
    ST_RE,
    ST_RET,
    ST_RETU,
    ST_RETUR,
    ST_RETURN,
    ST_I,
    ST_IF,
    ST_E,
    ST_EL,
    ST_ELS,
    ST_ELSE,
    ST_W,
    ST_WH,
    ST_WHI,
    ST_WHIL,
    ST_WHILE,
    ST_P,
    ST_PR,
    ST_PRI,
    ST_PRIN,
    ST_PRINT,
    ST_PRINTL,
    ST_PRINTLN,
    ST_WA,
    ST_WAI,
    ST_WAIN,
    ST_BECOMES,
    ST_IN,
    ST_INT,
    ST_EQ,
    ST_NE,
    ST_LT,
    ST_GT,
    ST_LE,
    ST_GE,
    ST_PLUS,
    ST_MINUS,
    ST_STAR,
    ST_SLASH,
    ST_PCT,
    ST_COMMA,
    ST_SEMI,
    ST_N,
    ST_Ne,
    ST_NEW,
    ST_D,
    ST_DE,
    ST_DEL,
    ST_DELE,
    ST_DELET,
    ST_DELETE,
    ST_LBRACK,
    ST_RBRACK,
    ST_AMP,
    ST_n,
    ST_Nu,
    ST_Nul,
    ST_Null, //null string
    ST_WHITESPACE,
    ST_COMMENT,
    ST_NOT, //!
    ST_ERR,
};


Kind stateKinds[] = {
    ERR, // start is null?
    ID,
    NUM,
    NUM,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    ID,
    ID,
    ID,
    ID,
    ID,
    RETURN,
    ID,
    IF,
    ID,
    ID,
    ID,
    ELSE,
    ID,
    ID,
    ID,
    ID,
    WHILE,
    ID,
    ID,
    ID,
    ID,
    ID,
    ID,
    PRINTLN,
    ID,
    ID,
    WAIN,
    BECOMES,
    ID,
    INT,
    EQ,
    NE,
    LT,
    GT,
    LE,
    GE,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    PCT,
    COMMA,
    SEMI,
    ID,
    ID,
    NEW,
    ID,
    ID,
    ID,
    ID,
    ID,
    DELETE,
    LBRACK,
    RBRACK,
    AMP,
    ID,
    ID,
    ID,
    Null, //null string
    WHITESPACE,
    COMMENT,
    ERR, //再看
    ERR,
};

const string whitespace = "\t\n\r ";
const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const string digits = "0123456789";
const string hexDigits = "0123456789ABCDEFabcdef";
const string oneToNine =  "123456789";

class Token{
    Kind kind;
    string lexeme;
public:
    Token(Kind kind, string lexeme): kind(kind), lexeme(lexeme) {}
    static Token* makeToken(Kind kind, std::string lexeme) {
        return new Token(kind,lexeme);
    }
    string getLexeme() const {
        return lexeme;
    }
    Kind getKind() const{
        return kind;
    }
    string toString() const {
        return kindStrings[kind];
    }
};

class Lexer {
    static const int maxStates = 71; // change when state change
    static const int maxTrans = 256;
    // Transition function
    State delta[maxStates][maxTrans];
public:
    void setTrans(State from, const string& chars, State to) {
        for(string::const_iterator it = chars.begin(); it != chars.end(); ++it)
            delta[from][static_cast<unsigned int>(*it)] = to;
    }
    Lexer(){
        for(int i=0; i < maxStates; ++i){
            for(int j=0; j < maxTrans; ++j){
                delta[i][j] = ST_ERR;
            }
        }
        setTrans( ST_START,      whitespace,     ST_WHITESPACE );
        setTrans( ST_WHITESPACE, whitespace,     ST_WHITESPACE );
        setTrans( ST_START,      letters,        ST_ID         );
        setTrans( ST_ID,         letters+digits, ST_ID         );
        setTrans( ST_START,      "0",            ST_ZERO       );
        setTrans( ST_ZERO,       digits+letters, ST_ERR        );
        setTrans( ST_START,      oneToNine,      ST_NUM        );
        setTrans( ST_NUM,        digits,         ST_NUM        );
        setTrans( ST_NUM,        letters,        ST_ERR        );
        setTrans( ST_START,      "(",            ST_LPAREN     );
        setTrans( ST_START,      ")",            ST_RPAREN     );
        setTrans( ST_START,      "{",            ST_LBRACE     );
        setTrans( ST_START,      "}",            ST_RBRACE     );
        setTrans( ST_START,      "=",            ST_BECOMES    );
        setTrans( ST_BECOMES,    "=",            ST_EQ         );
        setTrans( ST_START,      "!",            ST_NOT        ); // 再看
        setTrans( ST_NOT,        "=",            ST_NE         );
        setTrans( ST_START,      "<",            ST_LT         );
        setTrans( ST_START,      ">",            ST_GT         );
        setTrans( ST_LT,         "=",            ST_LE         );
        setTrans( ST_GT,         "=",            ST_GE         );
        setTrans( ST_START,      "+",            ST_PLUS       );
        setTrans( ST_START,      "-",            ST_MINUS      );
        setTrans( ST_MINUS,      digits,         ST_NUM        );
        setTrans( ST_START,      "*",            ST_STAR       );
        setTrans( ST_START,      "/",            ST_SLASH      );
        setTrans( ST_START,      "/",            ST_COMMENT    );
        setTrans( ST_START,      "%",            ST_PCT        );
        setTrans( ST_START,      ",",            ST_COMMA      );
        setTrans( ST_START,      ";",            ST_SEMI       );
        setTrans( ST_START,      "]",            ST_LBRACK     );
        setTrans( ST_START,      "[",            ST_RBRACK     );
        setTrans( ST_START,      "&",            ST_AMP        );
        
        setTrans( ST_START,      "w",            ST_W          );
        setTrans( ST_W,          "a",            ST_WA         );
        setTrans( ST_WA,         "i",            ST_WAI        );
        setTrans( ST_WAI,        "n",            ST_WAIN       );
        
        setTrans( ST_START,      "i",            ST_I          );
        setTrans( ST_I,          "n",            ST_IN         );
        setTrans( ST_IN,         "t",            ST_INT        );
        
        setTrans( ST_I,          "f",            ST_IF         );
        
        setTrans( ST_START,      "e",            ST_E          );
        setTrans( ST_E,          "l",            ST_EL         );
        setTrans( ST_EL,         "s",            ST_ELS        );
        setTrans( ST_ELS,        "e",            ST_ELSE       );
        
        setTrans( ST_W,          "h",            ST_WH         );
        setTrans( ST_WH,         "i",            ST_WHI        );
        setTrans( ST_WHI,        "l",            ST_WHIL       );
        setTrans( ST_WHIL,       "e",            ST_WHILE      );
        
        setTrans( ST_START,      "p",            ST_P          );
        setTrans( ST_P,          "r",            ST_PR         );
        setTrans( ST_PR,         "i",            ST_PRI        );
        setTrans( ST_PRI,        "n",            ST_PRIN       );
        setTrans( ST_PRIN,       "t",            ST_PRINT      );
        setTrans( ST_PRINT,      "l",            ST_PRINTL     );
        setTrans( ST_PRINTL,     "n",            ST_PRINTLN    );
        
        setTrans( ST_START,      "r",            ST_R          );
        setTrans( ST_R,          "e",            ST_RE         );
        setTrans( ST_RE,         "t",            ST_RET        );
        setTrans( ST_RET,        "u",            ST_RETU       );
        setTrans( ST_RETU,       "r",            ST_RETUR      );
        setTrans( ST_RETUR,      "n",            ST_RETURN     );
        
        setTrans( ST_START,      "N",            ST_n          );
        setTrans( ST_n,          "U",            ST_Nu         );
        setTrans( ST_Nu,         "L",            ST_Nul        );
        setTrans( ST_Nul,        "L",            ST_Null       );
        
        setTrans( ST_START,      "n",            ST_N          );
        setTrans( ST_N,          "e",            ST_Ne         );
        setTrans( ST_Ne,         "w",            ST_NEW        );
        
        setTrans( ST_START,      "d",            ST_D          );
        setTrans( ST_D,          "e",            ST_DE         );
        setTrans( ST_DE,         "l",            ST_DEL        );
        setTrans( ST_DEL,        "e",            ST_DELE       );
        setTrans( ST_DELE,       "t",            ST_DELET      );
        setTrans( ST_DELET,      "e",            ST_DELETE     );
        
        for(int j=0; j < maxTrans; ++j) delta[ST_COMMENT][j] = ST_COMMENT;
    };
    vector<Token*> scan(const string& line){
        vector<Token*> ret;
        if(line.size() == 0) return ret;
        State currState = ST_START;
        string::const_iterator startIter = line.begin();
        for(string::const_iterator it = line.begin();;){
            State nextState = ST_ERR;
            if(it != line.end())
                nextState = delta[currState][static_cast<unsigned int>(*it)];
            if(ST_ERR == nextState){
                Kind currKind = stateKinds[currState];
                if(ERR == currKind){
                    vector<Token*>::iterator vit;
                    for(vit = ret.begin(); vit != ret.end(); ++vit)
                        delete *vit;
                    throw "ERROR in lexing after reading " + string(line.begin(),it);
                }
                if(WHITESPACE != currKind)
                ret.push_back(Token::makeToken(currKind,string(startIter,it)));
                startIter = it;
                currState = ST_START;
                if(it == line.end()) break;
            } else {
                currState = nextState;
                ++it;
            }
        } // for loop end
        return ret;
    }
};

int main(int argc, char* argv[]){
    // Nested vector representing lines of Tokens
    // Needs to be used here to cleanup in the case
    // of an exception
    vector< vector<Token*> > tokLines;
    try{
        // Create a MIPS recognizer to tokenize
        // the input lines
        Lexer lexer;
        // Tokenize each line of the input
        string line;
        while(getline(cin,line)){
            tokLines.push_back(lexer.scan(line));
        }
        
        // Iterate over the lines of tokens and print them
        // to standard error
        vector<vector<Token*> >::iterator it;
        for(it = tokLines.begin(); it != tokLines.end(); ++it){
            vector<Token*>::iterator it2;
            for(it2 = it->begin(); it2 != it->end(); ++it2){
                if ((*it2)->getKind() == WHITESPACE || (*it2)->getKind() == COMMENT) {
                    continue;
                }
                if ((*it2)->getKind() == ERR) {
                    throw "ERROR";
                }
                cout << (*it2)->toString()  << " " << (*it2)->getLexeme() << endl;
            }
        }
    } catch(const string& msg){
        // If an exception occurs print the message and end the program
        cerr << msg << endl;
    }
    // Delete the Tokens that have been made
    vector<vector<Token*> >::iterator it;
    for(it = tokLines.begin(); it != tokLines.end(); ++it){
        vector<Token*>::iterator it2;
        for(it2 = it->begin(); it2 != it->end(); ++it2){
            delete *it2;
        }
    }
}



