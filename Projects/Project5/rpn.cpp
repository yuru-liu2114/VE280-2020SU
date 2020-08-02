#include <iostream>
#include "dlist.h"
#include <sstream>
#include <string>
using namespace std;
template <class T>
class Stack:public Dlist<T>{
public:
    void push(T* op);
    void pop();
    T* top() const;
};
template <class T>
void Stack<T>::push(T* op) {
    this->insertFront(op);
}
template <class T>
void Stack<T>::pop() {
    if(this->isEmpty()){return;}
    T* tmp = this->removeFront();
    delete tmp;
}
template <class T>
T* Stack<T>::top() const{
    Dlist<T> dupli(*this);
    return dupli.removeFront();
}

bool is_num(string c){
    return c[0] >= 48 && c[0] <= 57;
}

bool is_operator(string c){
    return c=="+" || c=="-" || c=="*" || c=="/";
}

int higher_pre(string op1,string op2){ // output 0 if equal, 1 if op1>op2, -1 if op1<op2
    if(!is_operator(op1) || !is_operator(op2)) {
        return -2;
    }
    if(op1[0]=='+' || op1[0]=='-'){
        if(op2[0]=='+' || op2[0]=='-'){
            return 0;
        }
        return -1;
    }
    else{
        if(op2[0]=='+' || op2[0]=='-'){
            return 1;
        }
        return 0;
    }
}

int main(){
    string output_str;
    Stack<string> operator_str;
    string line,c;
    getline(cin,line);
    istringstream istream(line);
    while(istream){
        istream>>c;
        if(istream){
            if(is_num(c)){
                output_str+=c;
                output_str+=" ";
            }
            else if(is_operator(c)){
                auto* ptr= new string(c);
                string* top;
                bool det;
                bool b1=!operator_str.isEmpty();
                if(!b1){
                    det = false;
                }
                else{
                    top = operator_str.top();
                    bool b2=higher_pre(c,*top)==0 || higher_pre(c,*top)==-1; // c has less or equal pre than top
                    bool b3=*top!="(";
                    det = b2 && b3;
                }
                while(det){
                    top = operator_str.top();
                    output_str+=*top;
                    output_str+=" ";
                    operator_str.pop();
                    b1=!operator_str.isEmpty();
                    if(!b1){
                        det = false;
                    }
                    else{
                        top = operator_str.top();
                        bool b2=higher_pre(c,*top)==0 || higher_pre(c,*top)==-1; // c has less or equal pre than top
                        bool b3=*top!="(";
                        det = b2 && b3;
                    }
                }
                operator_str.push(ptr);
            }
            else if(c=="("){
                auto* ptr= new string(c);
                operator_str.push(ptr);
            }
            else if(c==")"){
                bool b1=!operator_str.isEmpty();
                if(!b1){
                    cout << "ERROR: Parenthesis mismatch" << endl;
                    exit(0);
                }
                else{
                string* top=operator_str.top();
                while(*top!="(" && b1){
                    top = operator_str.top();
                    output_str+=*top;
                    output_str+=" ";
                    operator_str.pop();
                    b1=!operator_str.isEmpty();
                    if(b1){top = operator_str.top();}
                }
                if(!b1){
                        cout << "ERROR: Parenthesis mismatch" << endl;
                        exit(0);
                }
                if(!operator_str.isEmpty() && *top=="(") {
                    operator_str.pop();
                }
            }}
       }
    }
    while(!operator_str.isEmpty()){
        string* top = operator_str.top();
        if(*top=="(") {
            cout << "ERROR: Parenthesis mismatch" << endl;
            exit(0);
        }
        output_str+=*top;
        output_str+=" ";
        operator_str.pop();
    }
    cout<<output_str<<endl;
    istringstream istream1(output_str);
    string item;
    Stack<int> operand;
    int size=0;
    while(istream1>>item){
        if(istream1){
            if(is_num(item)){
                int* int_op = new int(stoi(item));
                operand.push(int_op);
                size++;
            }
            else if(is_operator(item)){
                if(size>=2){
                int* op2 = operand.top();
                int ope2 = *op2;
                operand.pop();
                size--;
                int* op1 = operand.top();
                int ope1= *op1;
                operand.pop();
                size--;
                int result=0;
                switch(item[0]){
                    case('+'):
                        result = ope1 + ope2;
                        break;
                    case('-'):
                        result = ope1 - ope2;
                        break;
                    case('*'):
                        result = ope1 * ope2;
                        break;
                    case('/'):
                        if(ope2==0){
                            cout << "ERROR: Divide by zero" << endl;
                            exit(0);
                        }
                        result = ope1 / ope2;
                        break;
                }
                int* push_int = new int(result);
                operand.push(push_int);
                size++;
            }
                else{
                    cout << "ERROR: Not enough operands" << endl;
                    exit(0);
                }
            }
        }
    }
    if(size>1) {
        cout << "ERROR: Too many operands" << endl;
        exit(0);
    }
    cout<<*operand.top()<<endl;
    operand.pop();
    return 0;
}