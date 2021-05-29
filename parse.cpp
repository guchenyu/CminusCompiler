#include<string>
#include"global.h"
#include"util.h"
#include"iostream"
static  TokenType token;   /* holds current token */
TreeNode* parse(void);
TreeNode* declaration_list(void);
TreeNode* declaration(void);
TreeNode* params(void);
TreeNode* param_list(TreeNode* k);
TreeNode* param(TreeNode* k);
TreeNode* compound_stmt(void);
TreeNode* local_declaration(void);
TreeNode* statement_list(void);
TreeNode* statement(void);
TreeNode* expression_stmt(void);
TreeNode* selection_stmt(void);
TreeNode* iteration_stmt(void); 
TreeNode* return_stmt(void);
TreeNode* expression(void);
TreeNode* var(void);
TreeNode* simple_expression(TreeNode* k);
TreeNode* additive_expression(TreeNode* k);
TreeNode* term(TreeNode* k);
TreeNode* factor(TreeNode* k);
TreeNode* call(TreeNode* k);
TreeNode* args(void);
static   void  syntaxError(string message)
{
    cout << "/******* Syntax error *******/"<<"at line" <<"  "<< linenum <<"  "<< message<<"----->";
    Error = true;
}

static   void  match(TokenType expected)
{
    if (token == expected)
        token = getTokens();
    else
    {
        syntaxError("unexpected token>>");
        printError(token, tokenString);
    }
}
TreeNode* parse(void)
{
    TreeNode* t;
    token = getTokens();
    t = declaration_list();
    if (token != ENDFILE)
    {
        syntaxError("endfile_error");
    }
    return  t;
}
TreeNode* declaration_list(void)
{
    TreeNode* t = declaration();
    TreeNode* pt = t;
    while ((token != INT) && (token != VOID) && (token != ENDFILE))
    {
        syntaxError(" 开始不是类型声明 ");
        token = getTokens();
        if (token == ENDFILE)
            break;
    }
    while (token == INT || token == VOID)
    {
        TreeNode* m;
        m = declaration();
        if (m != NULL)
        {
            if (t == NULL)
            {
                t = pt ;
                pt = m;
            }
            else
            {
                pt->sibling = m;
                pt = m;
            }
        }
        
    }
    match(ENDFILE);
    return  t;
}
TreeNode* declaration(void)
{
    TreeNode* t = NULL;
    TreeNode* p = NULL;
    TreeNode* q = NULL;
    TreeNode* s = NULL;
    TreeNode* a = NULL;
    if (token == INT)
    {
        p = newNode(IntK);
        match(INT);
    }
    else   if (token == VOID)
    {
        p = newNode(VoidK);
        match(VOID);
    }
    else
    {
        syntaxError("Type Error!");
    }
    if (p != NULL && token == ID)
    {
        q = newNode(IdK);
        q->attr.name = copyString(tokenString);
        match(ID);

        if (token == LPAREN)
        {
            t = newNode(FunK);
            t->child[0] = p;   //p 是 t 子节点
            t->child[1] = q;

            match(LPAREN);
            t->child[2] = params();
            match(RPAREN);
            t->child[3] = compound_stmt();
        }
        else   if (token == LBRACKET)
        {
            t = newNode(Var_DeclK);
            a = newNode(Arry_DeclK);
            t->child[0] = p;   //p 是 t 子节点
            t->child[1] = a;
            match(LBRACKET); 
            s = newNode(ConstK);
            s->attr.val = atoi(tokenString);
            match(NUM);
            a->child[0] = q;
            a->child[1] = s;
            match(RBRACKET);
            match(SEMI);
        }
        else   if (token == SEMI)
        {
            t = newNode(Var_DeclK);
            t->child[0] = p;
            t->child[1] = q;

            match(SEMI);
        }
        else
        {
            syntaxError("");
        }
    }
    else
    {
        syntaxError("");
    }
    return  t;
}
TreeNode* params(void)
{
    TreeNode* t = newNode(ParamsK);
    TreeNode* p = NULL;
    if (token == VOID)
    {
        p = newNode(VoidK);
        match(VOID);
        if (token == RPAREN)
        {
            if (t != NULL)
                t->child[0] = p;
        }
        else // 参数列表为 (void id,[……]) 
        {
            t->child[0] = param_list(p);
        }
    }
    else   if (token == INT)
    {
        t->child[0] = param_list(p);
    }
    else
    {
        syntaxError("");
    }
    return  t;
}
TreeNode* param_list(TreeNode* k)
{
    TreeNode* t = param(k);
    TreeNode* p = t;
    k = NULL; // 没有要传给 param 的 VoidK ，所以将 k 设为 NULL
    while (token == COMMA)
    {
        TreeNode* q = NULL;
        match(COMMA);
        q = param(k);
        if (q != NULL)
        {
            if (t == NULL)
            {
                t = p = q;
            }
            else
            {
                p->sibling = q;
                p = q;
            }
        }
    }
    return  t;
}
TreeNode* param(TreeNode* k)
{
    TreeNode* t = newNode(ParamK);
    TreeNode* p = NULL;
    TreeNode* q = NULL;
    if (k == NULL && token == VOID)
    {
        p = newNode(VoidK);
        match(VOID);
    }
    else   if (k == NULL && token == INT)
    {
        p = newNode(IntK);
        match(INT);
    }
    else   if (k != NULL)
    {
        p = k;
    }
    if (p != NULL)
    {
        t->child[0] = p;
        if (token == ID)
        {
            q = newNode(IdK);
            q->attr.name = copyString(tokenString);
            t->child[1] = q;
            match(ID);
        }
        else
        {
            syntaxError("");
        }
        if (token == LBRACKET && (t->child[1] != NULL)) 
        {
            match(LBRACKET);
            t->child[2] = newNode(IdK);
            match(RBRACKET);
        }
        else
        {
            return  t;
        }
    }
    else
    {
        syntaxError("");
    }
    return  t;
}
TreeNode* compound_stmt(void)
{
    TreeNode* t = newNode(CompK);
    match(LCBRACKET);
    t->child[0] = local_declaration();
    t->child[1] = statement_list();
    match(RCBRACKET);
    return  t;
}
TreeNode* local_declaration(void)
{
    TreeNode* t = NULL;
    TreeNode* q = NULL;
    TreeNode* p = NULL;
    while (token == INT || token == VOID)
    {
        p = newNode(Var_DeclK);
        if (token == INT)
        {
            TreeNode* q1 = newNode(IntK);
            p->child[0] = q1;
            match(INT);
        }
        else   if (token == VOID)
        {
            TreeNode* q1 = newNode(VoidK);
            p->child[0] = q1;
            match(INT);
        }
        if ((p != NULL) && (token == ID))
        {
            TreeNode* q2 = newNode(IdK);
            q2->attr.name = copyString(tokenString);
            p->child[1] = q2;
            match(ID);

            if (token == LBRACKET)
            {
                TreeNode* q3 = newNode(Var_DeclK);
                p->child[3] = q3;
                match(LBRACKET);
                match(RBRACKET);
                match(SEMI);
            }
            else   if (token == SEMI)
            {
                match(SEMI);
            }
            else
            {
                match(SEMI);
            }
        }
        else
        {
            syntaxError("");
        }
        if (p != NULL)
        {
            if (t == NULL)
                t = q = p;
            else
            {
                q->sibling = p;
                q = p;
            }
        }
    }
    return  t;
}
TreeNode* statement_list(void)
{
    TreeNode* t = statement();
    TreeNode* p = t;
    while (IF == token || LCBRACKET == token ||SEMI == token || LPAREN == token || NUM == token ||ID == token || WHILE == token || RETURN == token )
    {
        TreeNode* q;
        q = statement();
        if (q != NULL)
        {
            if (t == NULL)
            {
                t = p = q;
            }
            else
            {
                p->sibling = q;
                p = q;
            }
        }
    }
    return  t;
}
TreeNode* statement(void)
{
    TreeNode* t = NULL;
    switch (token)
    {
    case  IF:
        t = selection_stmt();
        break;
    case  WHILE:
        t = iteration_stmt();
        break;
    case  RETURN:
        t = return_stmt();
        break;
    case  LCBRACKET:
        t = compound_stmt();
        break;
    case  ID:   case  SEMI:   case  LPAREN:   case  NUM:
        t = expression_stmt();
        break;
    default:
        syntaxError("");
        token = getTokens();
        break;
    }
    return  t;
}
TreeNode* selection_stmt(void)
{
    TreeNode* t = newNode(Selection_StmtK);
    match(IF);
    match(LPAREN);
    if (t != NULL)
    {
        t->child[0] = expression();
    }
    match(RPAREN);
    t->child[1] = statement();
    if (token == ELSE)
    {
        match(ELSE);
        if (t != NULL)
        {
            t->child[2] = statement();
        }
    }
    return  t;
}
TreeNode* expression_stmt(void)
{
    TreeNode* t = NULL;
    if (token == SEMI)
    {
        match(SEMI);
        return  t;
    }
    else
    {
        t = expression();
        match(SEMI);
    }
    return  t;
}
TreeNode* iteration_stmt(void)
{
    TreeNode* t = newNode(Iteration_StmtK);
    match(WHILE);
    match(LPAREN);
    if (t != NULL)
    {
        t->child[0] = expression();
    }
    match(RPAREN);
    if (t != NULL)
    {
        t->child[1] = statement();
    }
    return  t;
}
TreeNode* return_stmt(void)
{
    TreeNode* t = newNode(Return_StmtK);
    match(RETURN);
    if (token == SEMI)
    {
        match(SEMI);
        return  t;
    }
    else
    {
        if (t != NULL)
        {
            t->child[0] = expression();
        }
    }
    match(SEMI);
    return  t;
}
TreeNode* expression(void)
{
    TreeNode* t = var();
    if (t == NULL) // 不是以 ID 开头，只能是 simple_expression 情况
    {
        t = simple_expression(t);
    }
    else // 以 ID 开头，可能是赋值语句，或 simple_expression 中的 var 和 call 类型的情况
    {
        TreeNode* p = NULL;
        if (token == ASSIGN) // 赋值语句
        {
            p = newNode(AssignK);
            //p->attr.name = ;
            match(ASSIGN);
            p->child[0] = t;
            p->child[1] = expression();
            return  p;
        }
        else   //simple_expression 中的 var 和 call 类型的情况
        {
            t = simple_expression(t);
        }
    }
    return  t;
}
TreeNode* simple_expression(TreeNode* k)
{
    TreeNode* t = additive_expression(k);
    k = NULL;
    if (EQ == token || GT == token || GEQ == token || LT == token || LEQ == token || NEQ == token)
    {
        TreeNode* q = newNode(OpK);
        q->attr.op = token;
        q->child[0] = t;
        t = q;
        match(token);
        t->child[1] = additive_expression(k);
        return  t;
    }
    return  t;
}
TreeNode* additive_expression(TreeNode* k)
{
    TreeNode* t = term(k);
    k = NULL;
    while ((token == PLUS) || (token == MINUS))
    {
        TreeNode* q = newNode(OpK);
        q->attr.op = token;
        q->child[0] = t;
        match(token);
        q->child[1] = term(k);
        t = q;
    }
    return t;
}
TreeNode* term(TreeNode* k)
{
    TreeNode* t = factor(k);
    k = NULL;
    while ((token == TIMES) || (token == OVER))
    {
        TreeNode* q = newNode(OpK);
        q->attr.op = token;
        q->child[0] = t;
        t = q;
        match(token);
        q->child[1] = factor(k);
    }
    return t;
}
TreeNode* factor(TreeNode* k)
{
    TreeNode* t = NULL;
    if (k != NULL)//k 为上面传下来的已经解析出来的以 ID 开头的 var, 可能为 call 或 var
    {
        if (token == LPAREN && k->nodekind != Arry_ElemK) //call
        {
            t = call(k);
        }
        else
        {
            t = k;
        }
    }
    else// 没有从上面传下来的 var
    {
        switch (token)
        {
        case LPAREN:
            match(LPAREN);
            t = expression();
            match(RPAREN);
            break;
        case ID:
            k = var();
            if (LPAREN == token && k->nodekind != Arry_ElemK)
            {
                t = call(k);
            }
            else
                t = k;
            break;
        case NUM:
            t = newNode(ConstK);
            if ((t != NULL) && (token == NUM))
            {
                t->attr.val = atoi(tokenString);
            }
            match(NUM);
            break;
        default:
            syntaxError("");
            token = getTokens();
            break;
        }
    }
    return t;
}
TreeNode* var(void)
{
    TreeNode* t = NULL;
    TreeNode* p = NULL;
    TreeNode* q = NULL;
    if (token == ID)
    {
        p = newNode(IdK);
        p->attr.name = copyString(tokenString);
        match(ID);
        if (token == LBRACKET)
        {
            match(LBRACKET);
            q = expression();
            match(RBRACKET);
            t = newNode(Arry_ElemK);
            t->child[0] = p;
            t->child[1] = q;
        }
        else
        {
            t = p;
        }
    }
    return t;
}
TreeNode* call(TreeNode* k)
{
    TreeNode* t = newNode(CallK);
    if (k != NULL)
        t->child[0] = k;
    match(LPAREN);
    if (token == RPAREN)
    {
        match(RPAREN);
        return t;
    }
    else if (k != NULL)
    {
        t->child[1] = args();
        match(RPAREN);
    }
    return t;
}
TreeNode* args(void)
{
    TreeNode* t = newNode(ArgsK);
    TreeNode* s = NULL;
    TreeNode* p = NULL;
    if (token != RPAREN)
    {
        s = expression();
        p = s;
        while (token == COMMA)
        {
            TreeNode* q;
            match(COMMA);
            q = expression();
            if (q != NULL)
            {
                if (s == NULL)
                {
                    s = p = q;
                }
                else
                {
                    p->sibling = q;
                    p = q;
                }
            }
        }
    }
    if (s != NULL)
    {
        t->child[0] = s;
    }
    return t;
}
