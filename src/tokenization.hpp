#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#pragma once

enum TokenType {
    _return,
    num,
    semi,
    _fail,
    _int,
    _double,
    _float,
    _bool,
    letter,
    print,
    openPara,
    closePara,
    openParaz,
    closeParaz,
    openParazz,
    closeParazz,
    _void,
    _char,
    _input,
    _if,
    _while,
    _for,
    _else
};

struct Token {
    TokenType type;
    std::string value;
};

std::string GetFileContent(std::string FilePath) {
    std::string FileContents;
    std::string OneLine;
    std::ifstream Program(FilePath);
    while(std::getline(Program, OneLine)) {
        FileContents += OneLine;
    }
    Program.close();

    return FileContents;
}

void removeTextFromString(std::string &str, const std::string &removedText) {
    size_t pos = str.find(removedText);
    while (pos != std::string::npos) {
        str.erase(pos, removedText.length());
        pos = str.find(removedText, pos);
    }
}

std::vector<Token> Tokenize(std::string str1) {
    std::vector<Token> Tokens;

    // Check for includes
    std::string str;
    std::vector<std::string> removedText;

    for(int i = 0; i < str1.length(); ++i) {
        if (str1.substr(i, 10) == "#include \"") {
            i+=10;
            std::string includePath;
            for(int j = 0; i+j < str1.length() && str1[i+j] != '\"'; ++j) {
                includePath += str1[i + j];
            }
            str += GetFileContent(includePath);
            removedText.push_back("#include \"" + includePath + "\"");
            i += includePath.length();
        } else {
            str += str1[i];
        }
    }

    // Remove the #include paths from str1
    for(int i = 0; i < removedText.size(); ++i) {
        removeTextFromString(str, removedText[i]);
    }

    for(int i = 0; i <= str.length(); ++i) {
        if(str.substr(i, 1) == ";") {                    // Semicolen
            Token token = {semi, ";"};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 7) == "return ") {       // Return
            i+=6;
            Token token = {_return, "return "};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(std::isdigit(str[i]) || str[i] == '=' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '.' || str[i] == '%' || str[i] == '&' || str[i] == '|' || str[i] == '!') {                // Numbers
            Token token = {num, str.substr(i, 1)};
            Tokens.push_back(token);
        } else if(str.substr(i, 4) == "int ") {
            i+=3;
            Token token = {_int, "int "};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 6) == "float ") {
            i+=5;
            Token token = {_float, "float "};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 7) == "double ") {
            i+=6;
            Token token = {_double, "double "};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 5) == "bool ") {
            i+=4;
            Token token = {_bool, "bool "};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 5) == "print") {
            i+=4;
            Token token = {print, "print"};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 1) == "(") {
            Token token = {openPara, "("};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 1) == ")") {
            Token token = {closePara, ")"};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 1) == "{") {
            Token token = {openParaz, "{\n"};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 1) == "}") {
            Token token = {closeParaz, "}\n"};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 1) == "[") {
            Token token = {openParazz, "["};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 1) == "]") {
            Token token = {closeParazz, "]"};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 5) == "void ") {
            i+=4;
            Token token = {_void, "void "};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 5) == "chat ") {
            i+=4;
            Token token = {_char, "char "};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 6) == "input ") {
            i+=5;
            std::string inputValue;
            int j;
            for(j = 0; str[i+j] != ';'; ++j) {
                inputValue += str[i+j];
            }
            std::string Value = "fgets("+inputValue+", sizeof("+inputValue+"), stdin);\n";
            Token token = {_input, Value};
            Tokens.insert(Tokens.end(), 1, token);
            i+=j;
        } else if(str.substr(i, 2) == "if") {
            i+=1;
            Token token = {_if, "if"};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 3) == "for") {
            i+=2;
            Token token = {_for, "for"};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 5) == "while") {
            i+=4;
            Token token = {_while, "while"};
            Tokens.insert(Tokens.end(), 1, token);
        } else if(str.substr(i, 4) == "else") {
            i+=3;
            Token token = {_else, "else"};
            Tokens.insert(Tokens.end(), 1, token);
        } else {
            Token token = {letter, str.substr(i, 1)};
            Tokens.push_back(token);
        }
    }
    return Tokens;
}