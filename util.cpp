#pragma once
#include<fstream>
#include<iostream>
#include"global.h"
#include "util.h"
using namespace std;
extern const int MAXCHILDREN;
ofstream fileout("result.txt");
void  OutToken(TokenType token, const   char* tokenString)
{
    switch (token)
    {
    case  ELSE:
    case  IF:
    case  INT:
    case RETURN:
    case VOID:
    case WHILE:
        fileout<<"reserved word"<< tokenString<<endl;
        break;
    case PLUS:
        fileout<< "+"<<endl;
        break;
    case MINUS:
        fileout<<"-"<<endl;
        break;
    case TIMES:
        fileout<<"*"<<endl;
        break;
    case SELFPLUS:
        fileout<< "++"<<endl;
        break;
    case SELFMINUS:
        fileout << "--" << endl;
        break;
    case OVER:
        fileout << "/" << endl;
        break;
    case PLUSASSIGN:
        fileout << "+=" << endl;
        break;
    case MINUSASSIGN:
        fileout << "-=" << endl;
        break;
    case TIMESASSIGN:
        fileout << "*=" << endl;
        break;
    case LT:
        fileout << "<" << endl;
        break;
    case LEQ:
        fileout << "<=" << endl;
        break;
    case GT:
        fileout << ">" << endl;
        break;
    case GEQ:
        fileout << ">=" << endl;
        break;
    case EQ:
        fileout << "==" << endl;
        break;
    case NEQ:
        fileout << "!=" << endl;
        break;
    case ASSIGN:
        fileout << "=" << endl;
        break;
    case SEMI:
        fileout << ";" << endl;
        break;
    case COMMA:
        fileout << "," << endl;
        break;
    case COLON:
        fileout << ":" << endl;
        break;
    case LPAREN:
        fileout << "(" << endl;
        break;
    case RPAREN:
        fileout << ")" << endl;
        break;
    case LBRACKET:
        fileout << "[" << endl;
        break;
    case RBRACKET:
        fileout << "]" << endl;
        break;
    case LCBRACKET:
        fileout << "{" << endl;
        break;
    case RCBRACKET:
        fileout << "}" << endl;
        break;
    case LCOMMENT:
        fileout << "/*" << endl;
        break;
    case RCOMMENT:
        fileout << "*/" << endl;
        break;
    case ENDFILE:
        fileout << "EOF" << endl;
        break;
    case ID:
        fileout<<"ID,name= "<<tokenString<<endl;
        break;
    case CHARACTER:
        fileout << "CHARACTER,val=" << tokenString << endl;
        break;
    case STRING:
        fileout << "STRING,val=" << tokenString << endl;
        break;
    case NUM:
        fileout << "NUM,val=" << tokenString << endl;
        break;
    case ERROR:
        fileout << "ERROR:" << tokenString << endl;
        break;
    default:
        fileout << "Unknown token:" << tokenString << endl;
        break;
    }
}
void  printError(TokenType token, const   char* tokenString)
{
    switch (token)
    {
    case  ELSE:
    case  IF:
    case  INT:
    case RETURN:
    case VOID:
    case SELFPLUS:
        cout << "++" << endl;
        break;
    case SELFMINUS:
        cout << "--" << endl;
        break;
    case OVER:
        cout << "/" << endl;
        break;
    case PLUSASSIGN:
        cout << "+=" << endl;
        break;
    case MINUSASSIGN:
        cout << "-=" << endl;
        break;
    case TIMESASSIGN:
        cout << "*=" << endl;
        break;
    case LT:
        cout << "<" << endl;
        break;
    case LEQ:
        cout << "<=" << endl;
        break;
    case WHILE:
        cout << "reserved word" << tokenString << endl;
        break;
    case PLUS:
        cout << "+" << endl;
        break;
    case MINUS:
        cout << "-" << endl;
        break;
    case TIMES:
        cout << "*" << endl;
        break;
    case GT:
        cout << ">" << endl;
        break;
    case GEQ:
        cout << ">=" << endl;
        break;
    case EQ:
        cout << "==" << endl;
        break;
    case NEQ:
        cout << "!=" << endl;
        break;
    case ASSIGN:
        cout << "=" << endl;
        break;
    case SEMI:
        cout << ";" << endl;
        break;
    case COMMA:
        cout << "," << endl;
        break;
    case COLON:
        cout << ":" << endl;
        break;
    case LPAREN:
        cout << "(" << endl;
        break;
    case RPAREN:
        cout << ")" << endl;
        break;
    case LBRACKET:
        cout << "[" << endl;
        break;
    case RBRACKET:
        cout << "]" << endl;
        break;
    case LCBRACKET:
        cout << "{" << endl;
        break;
    case RCBRACKET:
        cout << "}" << endl;
        break;
    case LCOMMENT:
        cout << "/*" << endl;
        break;
    case RCOMMENT:
        cout << "*/" << endl;
        break;
    case ENDFILE:
        cout << "EOF" << endl;
        break;
    case ID:
        cout << "ID,name= " << tokenString << endl;
        break;
    case CHARACTER:
        cout << "CHARACTER,val=" << tokenString << endl;
        break;
    case STRING:
        cout << "STRING,val=" << tokenString << endl;
        break;
    case NUM:
        cout << "NUM,val=" << tokenString << endl;
        break;
    case ERROR:
        cout << "ERROR:" << tokenString << endl;
        break;
    default:
        cout << "Unknown token:" << tokenString << endl;
        break;
    }
}
TreeNode* newNode(Kind kind)
{
    
    TreeNode* t =new TreeNode;
    int i;
    if (t == NULL)
        cout<<"Out of memory error at line "<<linenum;
    else {
        for (i = 0; i < 4; i++)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = kind;

        t->lineno = linenum;
        if (kind == OpK || kind == IntK || kind == IdK)
        {
            if (kind == IdK)
                t->attr.name = "";
            t->type = Integer;
        }
        if (kind == ConstK)
            t->attr.val = 0;
    }
    return t;
}
int retract = 0;
static void printSpaces(void)
{
    int i;
    for (i = 0; i < retract; i++) {
        fileout << " ";
        cout << " ";
    }
}
void outTree(TreeNode* tree)
{
    int i;
    retract += 4;
    while (tree != NULL)
    {
        printSpaces();
        switch (tree->nodekind)
        {
        case VoidK:
            fileout<<"Void"<<endl;
            cout << "Void" << endl;
            break;
        case IntK:
            fileout << "Int" << endl;
            cout << "Int" << endl;
            break;
        case IdK:
            fileout << "ID:" << tree->attr.name <<endl;
            cout << "ID:" << tree->attr.name << endl;
            break;
        case ConstK:
            fileout << "Const:" << tree->attr.val << endl;
            cout << "Const:" << tree->attr.val << endl;
            break;
        case Var_DeclK:
            fileout<<"Var_Decl"<<endl;
            cout << "Var_Decl" << endl;
            break;
        case Arry_DeclK:
            fileout << "Arry_Decl" << endl;
            cout << "Arry_Decl" << endl;
            break;
        case FunK:
            fileout << "Func" << endl;
            cout << "Func" << endl;
            break;
        case ParamsK:
            fileout << "Params" << endl;
            cout << "Params" << endl;
            break;
        case ParamK:
            fileout << "Params" << endl;
            cout << "Params" << endl;
            break;
        case CompK:
            fileout << "Comp" << endl;
            cout << "Comp" << endl;
            break;
        case Selection_StmtK:
            fileout << "If" << endl;
            cout << "If" << endl;
            break;
        case Selection_StmtK1:
            fileout << "Else" << endl;
            cout << "Else" << endl;
            break;
        case Iteration_StmtK:
            fileout << "While" << endl;
            cout << "While" << endl;
            break;
        case Return_StmtK:
            fileout << "Return" << endl;
            cout << "Return" << endl;
            break;
        case AssignK:
            fileout << "Assign" << endl;
            cout << "Assign" << endl;
            break;
        case OpK:
            fileout << "OP:";
            cout << "OP:";
            OutToken(tree->attr.op, "\0");
            printError(tree->attr.op, "\0");
            break;
        case Arry_ElemK:
            fileout << "Arry_Elem" << endl;
            cout << "Arry_Elem" << endl;
            break;
        case CallK:
            fileout << "Call" << endl;
            cout << "Call" << endl;
            break;
        case ArgsK:
            fileout << "Arg_s" << endl;
            cout << "Arg_s" << endl;
            break;
        default:
            cout << "Unknown node kind" << endl;
            break;
        }

        //else fprintf(listing,"Unknown node kind\n");
        for (i = 0; i < 4; i++)
            outTree(tree->child[i]);
        tree = tree->sibling;
    }
    retract -= 4;
}
char* copyString(char* s)
{
    int n;
    char* t;
    if (s == NULL) return NULL;
    n = strlen(s) + 1;
    t =(char *) malloc(n);
    strcpy(t, s);
    return t;
}
