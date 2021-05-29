#pragma once
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<fstream>
#include <sstream>
#include"global.h"
using namespace std;

//定义保留字
static string ReservedWord[32] = {
"auto", "break", "case", "char", "const", "continue",
"default", "do", "double", "else", "enum", "extern",
"float", "for", "goto", "if", "int", "long",
"register", "return", "short", "signed", "sizeof", "static",
"struct", "switch", "typedef", "union", "unsigned", "void",
"volatile", "while"
};


//定义特殊字符和界符
static string Operator_Delimiter[36] = {
"+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
"!=", ";", "(", ")", "^", ",", "\"", "\'", "#", "&",
"&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
"}", "\\", ".", "\?", ":", "!"
};
static  string IDentifierTbl = { "" };//标识符表
int searchReserve(string ReservedWord[32], string s);
bool IsLetter(char letter);
bool IsDigit(char digit);
string filterResource(string r);
void Scanner(ofstream& fp, string s);
string readFileIntoString(ifstream& ifile);
void lexical_analysize();


