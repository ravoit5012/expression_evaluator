/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

bool isVariable(const string& token){
    return !token.empty() && isalpha(token[0]);
}

bool isOperator(const std::string& token){
    return token == "+" || token == "-" || token == "*" || token == "/";
}

Evaluator::Evaluator(){
    symtable = new SymbolTable();
    vector<ExprTreeNode*> exp;
    expr_trees = exp;
}

Evaluator::~Evaluator(){delete symtable;}

void Evaluator::parse(vector<string> tokens){
    vector<ExprTreeNode*> nodeStack;
    vector<string> tokenStack;
    for(int i = 0; i < tokens.size(); i++){
        if(i==0){
            ExprTreeNode *newNode = new ExprTreeNode;
            newNode->type = "VAR";
            newNode->id = tokens[0];
            nodeStack.push_back(newNode);
        } else if (i==1) {
            ExprTreeNode *newNode = new ExprTreeNode;
            newNode->type = "";
            nodeStack.push_back(newNode);
        } else if (tokens[i] == "("){
            tokenStack.push_back("(");
        } else if (tokens[i] == ")"){
            tokenStack.pop_back();
            ExprTreeNode *newNode = nodeStack[nodeStack.size()-2];
            newNode->right = nodeStack.back();
            newNode->left = nodeStack[nodeStack.size() - 3];
            nodeStack.pop_back();
            nodeStack.pop_back();
            nodeStack.pop_back();
            nodeStack.push_back(newNode);
        } else {
            if(tokens[i] == "+"){
                ExprTreeNode *newNode = new ExprTreeNode;
                newNode->type = "ADD";
                nodeStack.push_back(newNode);
            } else if (tokens[i] == "-"){
                ExprTreeNode *newNode = new ExprTreeNode;
                newNode->type = "SUB";
                nodeStack.push_back(newNode);
            } else if (tokens[i] == "*"){
                ExprTreeNode *newNode = new ExprTreeNode;
                newNode->type = "MUL";
                nodeStack.push_back(newNode);
            } else if (tokens[i] == "/"){
                ExprTreeNode *newNode = new ExprTreeNode;
                newNode->type = "DIV";
                nodeStack.push_back(newNode);
            } else if (tokens[i] == "%"){
                ExprTreeNode *newNode = new ExprTreeNode;
                newNode->type = "MOD";
                nodeStack.push_back(newNode);
            } else if (isVariable(tokens[i])){
                ExprTreeNode *newNode = new ExprTreeNode;
                newNode->type = "VAR";
                newNode->id = tokens[i];
                nodeStack.push_back(newNode);
            } else {
                UnlimitedInt *intValue = new UnlimitedInt(tokens[i]);
                ExprTreeNode *newNode = new ExprTreeNode("VAL", intValue);
                nodeStack.push_back(newNode);
            }
        }
    }

    if(nodeStack.size()>=3){
        nodeStack[1]->left = nodeStack[0];
        nodeStack[1]->right = nodeStack[2];
        nodeStack.pop_back();
        nodeStack.pop_back();
        nodeStack.pop_back();
        expr_trees.push_back(nodeStack[1]);
    }
}

// void Evaluator::parse(vector<string> tokens) {
//     vector<ExprTreeNode*> nodeStack;
//     vector<string> opStack;

//     for (const string& token : tokens) {
//         if (token == "(") {
//             opStack.push_back(token);
//         } else if (token == ")") {
//             // Build subtree
//             ExprTreeNode* right = nodeStack.back(); nodeStack.pop_back();
//             ExprTreeNode* opNode = nodeStack.back(); nodeStack.pop_back();
//             ExprTreeNode* left = nodeStack.back(); nodeStack.pop_back();

//             opNode->left = left;
//             opNode->right = right;

//             nodeStack.push_back(opNode);
//             opStack.pop_back(); // pop the "("
//         } else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%") {
//             ExprTreeNode* opNode = new ExprTreeNode;

//             if (token == "+") opNode->type = "ADD";
//             else if (token == "-") opNode->type = "SUB";
//             else if (token == "*") opNode->type = "MUL";
//             else if (token == "/") opNode->type = "DIV";
//             else if (token == "%") opNode->type = "MOD";

//             nodeStack.push_back(opNode);
//         } else if (token == "=") {
//             ExprTreeNode* assignNode = new ExprTreeNode;
//             assignNode->type = "ASS";
//             nodeStack.push_back(assignNode);
//         } else if (isVariable(token)) {
//             ExprTreeNode* varNode = new ExprTreeNode;
//             varNode->type = "VAR";
//             varNode->id = token;
//             nodeStack.push_back(varNode);
//         } else {
//             // It's a number
//             UnlimitedInt* intVal = new UnlimitedInt(token);
//             ExprTreeNode* valNode = new ExprTreeNode("VAL", intVal);
//             nodeStack.push_back(valNode);
//         }
//     }

//     // Final expression tree
//     if (!nodeStack.empty()) {
//         expr_trees.push_back(nodeStack.back());
//     }
// }

UnlimitedRational *evalHelper(ExprTreeNode *node, SymbolTable *symbolTable){
    if(!node){return nullptr;}

    if(node->type == "VAL"){
        node->evaluated_value = node->val;
    } else if (node->type == "VAR"){
        node->evaluated_value = symbolTable->search(node->id);
    } else {
        UnlimitedRational *leftResult = evalHelper(node->left, symbolTable);
        UnlimitedRational *rightResult = evalHelper(node->right, symbolTable);

        if(leftResult && rightResult){
            if(node->type == "ADD"){
                node->evaluated_value = UnlimitedRational::add(leftResult, rightResult);
            } else if (node->type == "SUB"){
                node->evaluated_value = UnlimitedRational::sub(leftResult, rightResult);
            } else if (node->type == "MUL"){
                node->evaluated_value = UnlimitedRational::mul(leftResult, rightResult);
            } else if (node->type == "DIV"){
                node->evaluated_value = UnlimitedRational::div(leftResult, rightResult);
            }
        }
    }
    return node->evaluated_value;
}

void Evaluator::eval(){
    if(expr_trees.empty()) return;

    ExprTreeNode *root = expr_trees.back();
    if(!root) return;
    UnlimitedRational *result = evalHelper(root->right, symtable);
    symtable->insert(root->left->id, result);
}

// int main(){
//     vector<string> arr={"e", ":=", "(", "(","a", "*", "c", ")", "+","(","(", "b","*","d", ")", "*","4",")",")"};
//     Evaluator* ev=new Evaluator();
//     ev->parse(arr);
//     ev->eval();
//     ExprTreeNode* node=ev->expr_trees[0];
//     cout << node->left->type;
//     cout<<node;
// }