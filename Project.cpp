
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<iostream>
#include <math.h>
#include <cstring>
#include<string.h>

using namespace std;

#define maxLengthStack1 100
#define maxLengthQueue  100
#define maxLengthStack2 100
//first stack definition
struct firstStack{
  string Elements[maxLengthStack1];
  int topIndex;
};

void nullStack(firstStack *S){
    S->topIndex = maxLengthStack1;
}

bool emptyStackCheck(firstStack S){
    return (S.topIndex == maxLengthStack1);
}

bool fullStackCheck(firstStack S){
    return (S.topIndex == 0);
};

string topIndexValue(firstStack S){
    if(emptyStackCheck(S)){
        cout<<"Stack rong"<<endl;
        return "";
    } else {
        return S.Elements[S.topIndex];
    }
}

void Push(string x, firstStack *S){
    if(fullStackCheck(*S)){
        cout<<"Stack da day"<<endl;
    } else {
        S->topIndex = (S->topIndex - 1);
        S->Elements[S->topIndex] = x;
    }
}

void Pop(firstStack *S){
    if(emptyStackCheck(*S)){
        printf("Stack rong");
    } else {
        S->topIndex = (S->topIndex + 1);
    }
}

// second stack definition
struct secondStack{
  float Elements_[maxLengthStack2];
  int topIndex_;
};

void nullStackf(secondStack *U){
    U->topIndex_ = maxLengthStack2;
}

bool emptyStackCheckf(secondStack U){
    return (U.topIndex_ == maxLengthStack2);
}

bool fullStackCheckf(secondStack U){
    return (U.topIndex_ == 0);
};

float topIndexValuef(secondStack U){
    if(emptyStackCheckf(U)){
        printf("Stack rong");
        return 0;
    } else {
        return U.Elements_[U.topIndex_];
    }
}

void Pushf(float x, secondStack *U){
    if(fullStackCheckf(*U)){
        printf("Stack day");
    } else {
        U->topIndex_ = (U->topIndex_ - 1);
        U->Elements_[U->topIndex_] = x;
    }
}

void Popf(secondStack *U){
    if(emptyStackCheckf(*U)){
        cout<<"Stack rong"<<endl;
    } else {
        U->topIndex_ = (U->topIndex_ + 1);
    }
}

// Queue definition
struct Queue
{
    string qElements[maxLengthQueue];
    int front, rear;
};

void nullQueue(Queue *Q){
    Q->front=-1;
    Q->rear=-1;
}

bool fullQueueCheck(Queue Q){
    return(Q.rear -Q.front + 1) == maxLengthQueue;
}

bool emptyQueueCheck(Queue Q){
    return (Q.front ==-1);
}

void enQueue(string q, Queue *Q){
    if(fullQueueCheck(*Q)){
        printf("Queue day");
    } else {
        if(emptyQueueCheck(*Q)) Q->front=0;
        if(Q->rear == maxLengthQueue-1){
            for(int i = Q->front;i<Q->rear;i++){
                Q->qElements[i-Q->front]= Q->qElements[i];
            }
            Q->rear = maxLengthQueue - Q->front-1;
            Q->front=0;
        }
        Q->rear = Q->rear+1;
        Q->qElements[Q->rear] = q;
    }
}

void deQueue(Queue *Q){
    if(emptyQueueCheck(*Q)){
        printf("Queue rong");
    } else {
        Q->front = Q->front+1;
        if(Q->front >Q->rear){
            nullQueue(Q);
        }
    }
}

string getFrontValue(Queue Q){
    return Q.qElements[Q.front];
}

string getRearValue(Queue Q){
    return Q.qElements[Q.rear];
}


// process input

string getInputVAlue(string &inputData){
    int size = inputData.size();
    string result;
    if(inputData[0] == '+' || inputData[0]=='-' || inputData[0]=='/' || inputData[0]=='*' || inputData[0]=='^' || inputData[0]=='(' || inputData[0]==')'){
        result.resize(1);
        result = inputData[0];
        inputData.erase(0,1);
        return result;
    }
    int i = 0;
    while(i<size){
        if(inputData[i]>='0' && inputData[i]<='9'){
            result.resize(i+1);
            result[i]= inputData[i];
        } else {
            break;
        }
        i++;
    }
    inputData.erase(0,i);
    return result;
}

int operatorClassify(string Token)
{
    if( Token == "+" || Token =="-"|| Token =="*" || Token =="/" || Token =="^"){
        return 1;
    }
    if (Token=="(" || Token==")"){
        return -1;
    }else{
        return 0;
    }
}

int operatorPriority(string operatorItems){
    if(operatorItems == "^") return 3;
    if (operatorItems == "*" || operatorItems == "/") return 2;
    if (operatorItems == "+" || operatorItems == "-") return 1;
    return -1;
}
float Caculate(string operatorItem, float a, float b){
    if(operatorItem == "+") return a+b;
    if(operatorItem == "-") return a-b;
    if(operatorItem == "*") return a*b;
    if(operatorItem == "/") return a/b;
    if(operatorItem == "^") return pow(a,b);
    return 0;
}

void InfixtoPostfixAndCal(){
    firstStack S;
    Queue Q;
    nullStack(&S);
    nullQueue(&Q);
    string dataInput;
    cout<<"Nhap bieu thuc trung to : ";
    getline(cin, dataInput);
    while(!dataInput.empty()){
        string Token = getInputVAlue(dataInput);
        if(operatorClassify(Token) == 0){
            enQueue(Token,&Q);
        }else {
            if(operatorClassify(Token) == 1){
                while (!emptyStackCheck(S)){
                    if(operatorPriority(topIndexValue(S))>operatorPriority(Token)){
                        enQueue(topIndexValue(S),&Q);
                        Pop(&S);
                    }else {
                        break;
                    }
                }   
                Push(Token,&S);
            } else {
                if(Token == "("){
                    Push(Token, &S);
                } else if( Token == ")"){
                    while (!emptyStackCheck(S)){
                        if(topIndexValue(S)!="("){
                            enQueue(topIndexValue(S),&Q);
                            Pop(&S);
                        } else break;
                    }
                    Pop(&S);
                }
            }
        }
    }
    while (!emptyStackCheck(S))
    {
        enQueue(topIndexValue(S),&Q);
        Pop(&S);
    }
    cout<<"Bieu thuc hau to : ";
    float RESULT = 0;
    secondStack U;
    nullStackf(&U);
    while (!emptyQueueCheck(Q))
    {
        string temp = getFrontValue(Q);
        deQueue(&Q);
        cout<<" "<<temp;
        if(operatorClassify(temp)==0){
            Pushf(stof(temp),&U);
        }else{
            float firstNum = topIndexValuef(U);
            Popf(&U);
            float secondNum = topIndexValuef(U);
            Popf(&U);
            RESULT = Caculate(temp,firstNum,secondNum);
            Pushf(RESULT,&U);
        }
    }
    printf("\n");
    cout<<"\nResult: "<<RESULT<<endl;

}
int main(){
    while(1){
    InfixtoPostfixAndCal();
    }
}


