#include "../header.hpp"

template<typename T> class SyntaxTree {
private:
    class node {
    public:
        int opr; // the type of operations
        T val; // the result of its subtree
        node *left, *right;
        node(int opr_, T val_, node *lc, node *rc)
            : opr(opr_), val(val_), left(lc), right(rc){};
    };
    node* alloc(T val){
        return new node(-1, val, nullptr, nullptr);
    }
    node* alloc(int opr_, node* lc, node* rc){
        return new node(opr_, func[opr_](lc->val, rc->val), lc, rc);
    }
    node* expr(const string& s, int& pos){
        node* lc = term(s, pos);
        while(s[pos] == '+' || s[pos] == '-'){
            int opr_ = ((s[pos++] == '+') ? (0) : (1));
            lc = alloc(opr_, lc, term(s, pos));
        }
        return lc;
    }
    node* term(const string& s, int& pos){
        node* lc = factor(s, pos);
        while(s[pos] == '*' || s[pos] == '/'){
            int opr_ = ((s[pos++] == '*') ? (2) : (3));
            lc = alloc(opr_, lc, factor(s, pos));
        }
        return lc;
    }
    node* factor(const string& s, int& pos){
        if(isdigit(s[pos])) return number(s, pos);
        pos++; // '('をとばす
        node* res = expr(s, pos);
        pos++; // ')'をとばす
        return res;
    }
    node* number(const string& s, int& pos){
        T res = 0;
        do{
            res *= 10;
            res += (s[pos++] - '0');
        }while(isdigit(s[pos]));
        return alloc(res);
    }
    function< T(T, T) > func[4];

public:
    node* root;
    SyntaxTree(){
        func[0] = [&](const T x, const T y){ return x + y; };
        func[1] = [&](const T x, const T y){ return x - y; };
        func[2] = [&](const T x, const T y){ return x * y; };
        func[3] = [&](const T x, const T y){ return x / y; };
    }
    void construct(const string& s){
        int pos = 0;
        root = expr(s, pos);
    }
};
