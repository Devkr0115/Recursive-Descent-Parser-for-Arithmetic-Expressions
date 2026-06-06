#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <iomanip>
#include <cctype>

using namespace std;

enum TokenType { NUMBER, ID, OPERATOR, END };

struct Token{
    TokenType type;
    string text;
    int value;
};

vector<Token> tokens;
int pos = 0;

unordered_map<string,int> symbolTable;

struct Node{
    string type;
    string name;
    int value;
    Node* left;
    Node* right;

    Node(string t,int v=0,string n="",Node* l=nullptr,Node* r=nullptr){
        type=t;
        value=v;
        name=n;
        left=l;
        right=r;
    }
};

void divider(){
    cout << "----------------------------------------------------\n";
}

void bigDivider(){
    cout << "====================================================\n";
}

Token currentToken(){
    return tokens[pos];
}

void advance(){
    if(pos < tokens.size()-1) pos++;
}

void tokenize(string input){

    tokens.clear();

    for(int i=0;i<input.size();i++){

        if(isspace(input[i])) continue;

        if(isdigit(input[i])){
            int num=0;

            while(i<input.size() && isdigit(input[i])){
                num = num*10 + (input[i]-'0');
                i++;
            }

            i--;
            tokens.push_back({NUMBER,"",num});
        }

        else if(isalpha(input[i])){
            string id;

            while(i<input.size() && isalnum(input[i])){
                id+=input[i];
                i++;
            }

            i--;
            tokens.push_back({ID,id,0});
        }

        else if(string("+-*/=()").find(input[i])!=string::npos){
            string op;
            op+=input[i];
            tokens.push_back({OPERATOR,op,0});
        }

        else{
            cout<<"Invalid character\n";
            exit(1);
        }
    }

    tokens.push_back({END,"",0});
    pos=0;
}

void printTokens(){

    cout<<left<<setw(12)<<"Lexeme"<<setw(15)<<"Token Type"<<endl;
    divider();

    for(auto &t:tokens){

        if(t.type==END) break;

        if(t.type==NUMBER)
            cout<<setw(12)<<t.value<<setw(15)<<"Number"<<endl;

        else if(t.type==ID)
            cout<<setw(12)<<t.text<<setw(15)<<"Identifier"<<endl;

        else
            cout<<setw(12)<<t.text<<setw(15)<<"Operator"<<endl;
    }
}

Node* parseExpression();

Node* parseFactor(){

    Token tok=currentToken();

    if(tok.type==NUMBER){
        advance();
        return new Node("NUMBER",tok.value);
    }

    if(tok.type==ID){
        advance();
        return new Node("VAR",0,tok.text);
    }

    if(tok.text=="("){

        advance();

        Node* node=parseExpression();

        if(currentToken().text!=")"){
            cout<<"Syntax error: missing )\n";
            exit(1);
        }

        advance();
        return node;
    }

    cout<<"Syntax error\n";
    exit(1);
}

Node* parseTerm(){

    Node* left=parseFactor();

    while(currentToken().text=="*" || currentToken().text=="/"){

        string op=currentToken().text;
        advance();

        Node* right=parseFactor();

        left=new Node(op,0,"",left,right);
    }

    return left;
}

Node* parseExpression(){

    Node* left=parseTerm();

    while(currentToken().text=="+" || currentToken().text=="-"){

        string op=currentToken().text;
        advance();

        Node* right=parseTerm();

        left=new Node(op,0,"",left,right);
    }

    return left;
}

Node* parseStatement(){

    if(currentToken().type==ID && tokens[pos+1].text=="="){

        string name=currentToken().text;
        advance();
        advance();

        Node* expr=parseExpression();

        return new Node("=",0,name,expr,nullptr);
    }

    return parseExpression();
}

int evaluate(Node* node){

    if(node->type=="NUMBER")
        return node->value;

    if(node->type=="VAR"){
        if(symbolTable.find(node->name)==symbolTable.end()){
            cout<<"Undefined variable "<<node->name<<"\n";
            exit(1);
        }

        return symbolTable[node->name];
    }

    if(node->type=="+")
        return evaluate(node->left)+evaluate(node->right);

    if(node->type=="-")
        return evaluate(node->left)-evaluate(node->right);

    if(node->type=="*")
        return evaluate(node->left)*evaluate(node->right);

    if(node->type=="/")
        return evaluate(node->left)/evaluate(node->right);

    if(node->type=="="){
        int val=evaluate(node->left);
        symbolTable[node->name]=val;
        return val;
    }

    return 0;
}

void printParseTree(Node* node,string prefix="",bool last=true){

    if(node==nullptr) return;

    cout<<prefix;

    cout<<(last ? "└── " : "├── ");

    if(node->type=="NUMBER")
        cout<<node->value<<endl;
    else if(node->type=="VAR")
        cout<<node->name<<endl;
    else
        cout<<node->type<<endl;

    string newPrefix = prefix + (last ? "    " : "│   ");

    if(node->left || node->right){
        printParseTree(node->left,newPrefix,false);
        printParseTree(node->right,newPrefix,true);
    }
}

void printSymbolTable(){

    cout<<left<<setw(15)<<"Identifier"<<setw(10)<<"Value"<<endl;
    divider();

    for(auto &p:symbolTable)
        cout<<setw(15)<<p.first<<setw(10)<<p.second<<endl;
}

int main(int argc,char* argv[]){

    if(argc<2){
        cout<<"Usage: ./parser program.txt\n";
        return 0;
    }

    ifstream file(argv[1]);
    string line;

    while(getline(file,line)){

        if(line.empty()) continue;

        bigDivider();
        cout<<"INPUT: "<<line<<endl;

        tokenize(line);

        cout<<"\nTOKENS\n";
        divider();
        printTokens();

        Node* tree=parseStatement();

        cout<<"\nPARSE TREE\n";
        divider();
        cout<<endl;

        printParseTree(tree);

        int result=evaluate(tree);

        cout<<"\nRESULT\n";
        divider();
        cout<<result<<endl;
    }

    bigDivider();
    cout<<"SYMBOL TABLE\n";
    divider();
    printSymbolTable();

    return 0;
}
