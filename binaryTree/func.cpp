#include <iostream>
#include <queue>
#include<vector>
#include "Tree.h"

using namespace std;
void sort(vector<int> &inputVector,int length){

  vector<int> sorted;

  int realLength=length;
  int largest=0;
  int count=0;
  int temp[length];
  int pos=0;
  
  
  while(count<realLength){//while we still need to go through numbers in array
    for(int i=0;i<realLength;i++){//for them all
      if(inputVector[i]>largest){//if somethings bigger then the largest found switch em
	largest=inputVector[i];
	pos=i;
      }
    }
    inputVector[pos]=0;//delte from old array
    sorted.push_back(largest);//add to new array
    largest=0;
    count=count+1;
    //sort again fro next largest until out of numbers
  }
  for(int i=0;i<realLength;i++){//reassign to array
    inputVector[i]=sorted[i];

  }
  cout<<"SORTED"<<endl;
}

void printTree(vector<int>sorted,int trueLength,int index, int level){

   if (index >= trueLength){//if there is nothing in the array passed
        return;
  }
  printTree(sorted, trueLength, 2 * index + 2, level + 1);//prints teh right side of the tree
    for (int i = 0; i < level; i++){
      cout << "   ";//prints teh correct number of spaces for the given node based on its level
    }
    cout << sorted[index] << endl;//prints the current node
    printTree(sorted, trueLength, 2 * index + 1, level + 1);//prints the left side of the tree
}

void buildTree(queue<int> input,Tree* head,Tree* &current){

  while(head==NULL){
    head = new Tree(new Child(input.front()));
    input.pop();
    current = head;
  }
  if(current->getChild()->getRoot() > (input.front())){
    while(current->getRight() != NULL){
      current = current->getRight();
      buildTree(input,head,current);
    }
    current->setRight(new Tree(new Child(input.front())));
    input.pop();
		      

  }

    else if(current->getChild()->getRoot() < (input.front())){
    while(head->getLeft() != NULL){
      current = current->getLeft();
      buildTree(input,head,current);
    }
    current->setRight(new Tree(new Child(input.front())));
    input.pop();


  }
  cout<<"it is done"<<endl;
}
