#include "ast.h"


PNode::PNode()
{
    this->son1 = NULL;
    this->son2 = NULL;
    this->son3 = NULL;
}

Node::Node(const char* lexeme, int type, PNode *son1, PNode *son2, PNode *son3)
{
    this->Type = type;
    this->lexeme = lexeme;
    this->son1 = son1;
    this->son2 = son2;
    this->son3 = son3;
}

NumberNode::NumberNode(const char* lexeme, int type)
{
    this->Type = type;
    this->lexeme = lexeme;
}

VariableNode::VariableNode(const char* lexeme, int type)
{
    this->Type = type;
    this->lexeme = lexeme;
}

BinExprNode::BinExprNode(const char* lexeme, int type, PNode *son1, PNode *son2, PNode *son3)
{
    this->Type = type;
    this->lexeme = lexeme;
    this->son1 = son1;
    this->son2 = son2;
    this->son3 = son3;
}

void tree_print(PNode *tree, int n)
{
    if(tree)
    {
        if(n > 1) std::cout << "|";
        for(int i = 1; i < n; i++)
            std::cout << " ";
        if(n > 1) std::cout << "=>";
        std::cout << tree->lexeme << "  " << tree->Type << std::endl;
        if(tree->son1 != NULL)
            tree_print(tree->son1, n+3);
        if(tree->son2 != NULL)
            tree_print(tree->son2, n+3);
        if(tree->son3 != NULL)
            tree_print(tree->son3, n+3);
    }
}

void free_tree(PNode *tree)
{
    if(tree)
    {
        if(tree->son1 != NULL)
            free_tree(tree->son1);
        if(tree->son2 != NULL)
            free_tree(tree->son2);
        if(tree->son3 != NULL)
            free_tree(tree->son3);
        delete(tree);
    }
}

void toJSON(rapidjson::Document& doc, PNode* node){
    if(node == NULL)
        return;
    rapidjson::Value json_val;
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.SetObject();

    json_val.SetUint64(node->Type);
    doc.AddMember("id", json_val, allocator);

    json_val.SetString(node->lexeme, allocator);
    doc.AddMember("name", json_val, allocator);
    if(node->son1 != NULL)
    {
        rapidjson::Document doc1;
        toJSON(doc1, node->son1);
        json_val.CopyFrom(doc1, allocator);
        doc.AddMember("son1", json_val, allocator);
    } 
    if(node->son2 != NULL)
    {

        rapidjson::Document doc2;
        toJSON(doc2, node->son2);
        json_val.CopyFrom(doc2, allocator);
        doc.AddMember("son2", json_val, allocator);
    }
    if(node->son3 != NULL)
    {

        rapidjson::Document doc3;
        toJSON(doc3, node->son3);
        json_val.CopyFrom(doc3, allocator);
        doc.AddMember("son3", json_val, allocator);
    }
}