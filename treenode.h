#pragma once
#include<string>
#include"global.h"

typedef   struct  treeNode
{
    struct  treeNode* child[4];
    struct  treeNode* sibling;
    int  lineno;
    Kind nodekind;
    union { 
    TokenType op;   
    int  val;   
    char* name; } attr;
    ExpType type;
}  TreeNode;