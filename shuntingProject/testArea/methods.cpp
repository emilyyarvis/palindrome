#include <iostream>
#include<stack>
#include "newNode.h"
#include "Tree.h"
#include <queue>
using namespace std;
void createTree(queue<char> inputQueue);
void printTree(Tree* head);

void checkOperator(char input[],int length,int &operatorCount){
  for(int i=0;i<length;i++){
    if(input[i] =='*'||input[i]=='-'||input[i]=='+'||input[i]=='/'||input[i]=='^'){
      operatorCount++;
    }
  }
  
}
bool checkOperatorIndividual(char input){
  if(input=='*'||input=='-'||input=='+'||input=='/'||input=='^'||input==')'||input=='('){
  return true;
}
 else{
   return false;
 }
}

bool checkOperandIndividual(char input){
  if((input!='*'&&input!='-'&&input!='+'&&input!='/'&&input!='^')&&input!=' '){
    return true;
  }
  else{
    return false;
  }
  
}
bool checkSpace(char input){
  if(input ==' '){
    return true;
  }
  else{
    return false;
  }
}

void buildStack(Node* head){


}

void buildQueue(Node* head){


}
void buildLinkedList(char input[],int length,Node* &head){
  Node* current=NULL;
  //  current = head;                                                                                                
  int LLCount=0;
  for (int i=0;i<length;i++){
    if(checkSpace(input[i])!=true){
      LLCount++;
           if(head==NULL){
        head= new Node(new Student(input[i]));
      }
      else{
        current = head;
        while(current->getNext()!=NULL){
          current = current->getNext();
        }
        current->setNext(new Node(new Student(input[i])));
      }
    }
  }
  //print                                                                                                            
  current=head;
  cout<<endl;
  for (int i=0;i<LLCount;i++){
    cout<<current->getStudent()->getValue()<<endl;
    current=current->getNext();
 }
}

void builTree(Tree* head){


}
void readInfix(char input[],int inputLength,int trueLength){
  char before;
  char temp;
  queue<char>output;
  queue<char>print;
  stack<char>operators;
  cout<<"num"<<trueLength<<endl;
  
  for(int i=0;i<inputLength;i++){
    if(checkOperatorIndividual(input[i])==true){
      if(operators.empty()==true){
	operators.push(input[i]);
      }
      else{
	char popped = ' ';
	if(input[i] == '*' || input[i] == '/'){
	  cout<<"M or D"<<endl;
	  if(operators.top() == '*' || operators.top() == '/'){
	    cout<<"1"<<endl;
	    
	     popped=operators.top();
	     output.push(popped);
	     operators.pop();
	     operators.push(input[i]);
	    
	  }
	  else if(operators.top() == '+' || operators.top() == '-'){
	    cout<<"2"<<endl;
	    operators.push(input[i]);
	  }
	 }
	else if(input[i]=='+' || input[i] == '-'){
	  cout<<" A or S"<<endl;
	  if(operators.top() == '*' || operators.top() == '/'){
	    cout<<"3"<<endl;
	    popped=operators.top();
	    output.push(popped);
	    operators.pop();
	    operators.push(input[i]);
          }
          else if(operators.top() == '+' || operators.top()=='-'){
	    cout<<"4"<<endl;

	     popped=operators.top();
             output.push(popped);
             operators.pop();
	     operators.push(input[i]);
          }
	}
      }
    }
    else if(checkOperandIndividual(input[i])==true){
      cout<<"variable"<<endl;
      output.push(input[i]);
    }
    else if(checkSpace(input[i]) ==true){
      //cout<<"space"<<endl;
    }

  }
  while(operators.empty()!=true){
    output.push(operators.top());
    operators.pop();

  }
  print = output;
  cout<<"hello"<<endl;
  for(int i=0;i<trueLength;i++){
    cout<<print.front()<<endl;
    //cout<<"test"<<endl;
    print.pop();
  }

  createTree(output);

}


void createTree(queue<char> inputQueue){
  queue<Tree*> sort;
  queue<Tree*> print;
  if(sort.empty()){


  }
  
  while(!inputQueue.empty()){
    if(checkOperandIndividual(inputQueue.front())==true){

      Tree* t = new Tree(new Child(inputQueue.front()));

      sort.push(t);
      inputQueue.pop();
    }
    else if(checkOperatorIndividual(inputQueue.front())==true){
      Tree* t =	new Tree(new Child(inputQueue.front()));
      inputQueue.pop();

      while(!sort.empty()){
	if(t->getLeft()==NULL){
	  t->setLeft(sort.front());
	  sort.pop();
	}
	else if(t->getRight()==NULL){
	  t->setRight(sort.front());
	  sort.pop();
	}

      }
      sort.push(t);
    }
    
  }

  
  print=sort;
  cout<<"NEW"<<endl;
  while(!print.empty()){
    cout<<print.front()->getChild()->getRoot()<<endl;
    print.pop();
  }

  cout<<"NAH NAH"<<endl;
  printTree(sort.front());
}
void printTree(Tree* head){

  if(head->getLeft()!=NULL){
    printTree(head->getLeft());

  }
  if(head->getRight()!=NULL){
    printTree(head->getRight());
  }

  cout<<head->getChild()->getRoot()<<endl;


}

  
