int op_level(StatementFormulaSymbles op)
{
    if (op == Equivalence)
        return 0;
    if (op == Implication)
        return 1;
    if (op == Conjunction)
        return 2;
    if (op == Disjunction)
        return 3;
    if (op == Negation)
        return 4;
    if (op == LeftParenthesis || op == RightParenthesis)
        return 5;

    return -1;
}

int is_op(StatementFormulaSymbles x)
{
    return (x == Equivalence || x == Implication || x == Conjunction || \
            x == Disjunction || x == Disjunction || x == Negation || \
            x == LeftParenthesis || x == RightParenthesis);
}

int is_whitespace(StatementFormulaSymbles x)
{
    return x == ' ';
}

int is_value(StatementFormulaSymbles x)
{
    return x == PropositionalVariable;
}

int is_bino_op(StatementFormulaSymbles x)
{
    return is_op(x) && (x == Conjunction || x == Disjunction || \
                        x == Implication || x == Equivalence);
}

Boolean IsStatementFormula(pStatementFormula pFormula)
{
    StatementFormulaSymbles x, op;
    int vt, opt, level;
    StatementFormulaSymbles ops[1000];

    vt = -1; opt = -1;
    while ((x = getCurrentSymbleType(pFormula)) != EndOfFormula) {
        nextPos(pFormula);
        if (is_value(x)) {
            vt += 1;
        } else if (is_op(x)) {
            level = op_level(x);
            while (opt >= 0 && level < op_level(ops[opt]) && \
                    ops[opt] != LeftParenthesis) {
                op = ops[opt];
                opt -= 1;
                if (is_bino_op(op))
                    vt -= 1;
                if (vt < 0)
                    return false;
            }
            if (x == RightParenthesis) {
                while (opt >= 0 && ops[opt] != LeftParenthesis) {
                    op = ops[opt];
                    if (is_bino_op(op))
                        vt -= 1;
                    if (vt < 0)
                        return false;
                    opt -= 1;
                }
                if (opt < 0)
                    return false;
                opt -= 1;
            } else {
                ops[++opt] = x;
            }
        } else if (!is_whitespace(x)){
            return false;
        }
    }

    while (opt >= 0) {
        op = ops[opt];
        if (op == LeftParenthesis)
            return false;
        if (is_bino_op(op))
            vt -= 1;
        if (vt < 0)
            return false;
        opt -= 1;
    }

    if (vt == 0 && opt == -1)
        return true;
    return false;
}
