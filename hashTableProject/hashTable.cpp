#include <iostream>
#include <iomanip>
#include <fstream>
#include "newNode.h"
#include <cstring>
#include <vector>

using namespace std;

void rehash(int &bucketSize,Node* *ptr);
int randomInt(int maxValue);
void hashFunction(int userId,float userGPA,string firstName,string lastName,int bucketSize, Node* *ptr);

void hashPrint(Node* *hash,int bucketSize);
bool quit();
void hashDelete(int deletedId,Node* hash[],int bucketSize);


int main(){
  bool loop = true;
  string input;
  Node* head=NULL;

  string userInput;
  string inputFirst;
  string inputLast;
  int inputId=0;
  int inputDeleteId=0;
  float inputGPA=0;
  //random generation
  vector<string>firstName;
  vector<string>lastName;
  float randomGpa=0;
  int currentId = 100000;
  int firstNameIndex = 0;
  int lastNameIndex = 0;
  srand(time(NULL));
  cout<<setprecision(3)<<showpoint;
  ////////////////////
  //reading files
  ifstream fileInput;
  string filename = "firstNames.txt";

  fileInput.open(filename);
  if(!fileInput.is_open()){
    cout<<"NO"<<endl;
  }
  while(fileInput){
    string line;

    getline(fileInput,line);
    //cout<<"Name: "<<line<<endl;
    firstName.push_back(line);
      }
  fileInput.close();
  filename = "lastNames.txt";

  fileInput.open(filename);
  if(!fileInput.is_open()){
    cout<<"NO"<<endl;
  }
  while(fileInput){
    string line;
    
    getline(fileInput,line);
    //cout<<"N: "<<line<<endl;
    lastName.push_back(line);
  }
  for(int i=0; i<firstName.size();i++){
    cout<<firstName[i]<<","<<lastName[i]<<endl;

  }
  //////////////////////////////////////////


  
  //hash stuff
  int bucketSize=100;
  Node* hash[bucketSize];
  //Node* current;

  Node* *ptr=hash;
  //current = hash;
  //intializes hash
  for(int i=0;i<bucketSize;i++){
    hash[i] = NULL;
  }
  /////////////////////////////////////////////////////////
  while(loop == true){
    cin>>userInput;
    if(userInput == "ADD"){
      string userInput2;
      cout<<"Do you want to add a student manually or randomly"<<endl;
      cout<<"Type MANUAL or RANDOM"<<endl;
      cin>>userInput2;
      if(userInput2 == "MANUAL"){
	
	cout<<"Whats the students first name"<<endl;
	cin>>inputFirst;
	cout<<"Whats the students last name"<<endl;
	cin>>inputLast;
	cout<<"Whats the students Id"<<endl;
	cin>>inputId;
	cout<<"Whats the students GPA"<<endl;
	cin>>inputGPA;
	hashFunction(inputId,inputGPA,inputFirst,inputLast,bucketSize,ptr);
      }
      else if(userInput2 == "RANDOM"){
	cout<<"How many students would you like to randomly add"<<endl;
	int students;
	cin>>students;
	for(int i=0;i<students;i++){
	  firstNameIndex=0;
	  lastNameIndex=0;
	  randomGpa=0;
	  // srand(time(NULL));
	  float randomNumber = (float)randomInt(4);
	  randomGpa = (float)(rand()) / (float)(RAND_MAX);
	  randomGpa = randomGpa+randomNumber;
	  if(randomGpa <1){
	    randomGpa = randomGpa+1;
	  } 
	  currentId = currentId+1;
	  firstNameIndex = randomInt(20);
	  lastNameIndex = randomInt(20);;
	  hashFunction(currentId,randomGpa,firstName[firstNameIndex],lastName[lastNameIndex],bucketSize,ptr);
	}
      }
    }
    else if(userInput == "PRINT"){
      hashPrint(ptr,bucketSize);
    }
    else if(userInput == "QUIT"){
      loop = quit();
    }
    else if(userInput == "DELETE"){
      cout<<"enter the id of the person you would like to delete"<<endl;
      cin>>inputDeleteId;
      hashDelete(inputDeleteId,hash,bucketSize);
    }
    else{
      cout<<"This command word does not exist please try again"<<endl;
    }
  }
}
/////////////////////////////////////////////////////////////////////////////

void hashFunction(int userId,float userGPA,string firstName,string lastName,int bucketSize, Node* *hash){
  int value=0;
  Node* head = NULL;
  Node* current= NULL;
  value = userId % bucketSize;//figures out which bucket we will put into
  cout<<value<<endl;
  
  if(hash[value] == NULL){//nothing in the bucket
    hash[value] = new Node(new Student(userId,userGPA,firstName,lastName));
  }
  else{//if there is another item in the bucket
    head = hash[value];
    current = hash[value];
    int count = 1;
    while(current->getNext()!=NULL){
      current = current->getNext();
      count = count+1;
    }
    cout<<"Count: "<<count<<endl;
    if(count >= 2){
      current->setNext(new Node(new Student(userId,userGPA,firstName,lastName)));
      cout<<"hello"<<endl;
      rehash(bucketSize,hash);
    }
    else{
      current->setNext(new Node(new Student(userId,userGPA,firstName,lastName)));
      current = current->getNext();
      // cout<<current->getStudent()->getFirstName()<<endl;
    }
    
  }

}
void rehash(int &bucketSize,Node* *ptr){
  vector<Node*> temp;
  int counter=0;
  Node* current=NULL;
 
  for(int i=0;i<bucketSize;i++){
    if(ptr[i] != NULL){
      current = ptr[i];

      while(current->getNext()!=NULL){
	temp.push_back(current);
	current = current->getNext();
	
      }
      
      temp.push_back(current);
      counter=counter+1;
    }
  }
  
  cout<<bucketSize<<endl;
  bucketSize=bucketSize*2;
  cout<<"debug: "<<ptr[1]->getStudent()->getId()<<endl;
  Node* newHash[bucketSize];
  for(int i=0;i<bucketSize;i++){
    newHash[i] = NULL;
  }


  
  cout<<bucketSize<<endl;
  cout<<"initial size: "<<sizeof(ptr)<<endl;
  ptr=newHash;
  cout<<"initial size: "<<sizeof(ptr)<<endl;
  cout<<"debug: "<<ptr[1]->getStudent()->getId()<<endl;
}
int randomInt(int maxValue){
  //srand(time(NULL));
  int randomNumber = (rand()%maxValue);
  return randomNumber;
}
void hashPrint(Node* *hash,int bucketSize){
  int count = 0;
  Node* current= NULL;
  for(int i=0;i<bucketSize;i++){
    if(hash[i]!=NULL){
      current = hash[i];
      
      while(current->getNext()!=NULL){
	cout<<i<<","<<current->getStudent()->getId()<<", "<<current->getStudent()->getFirstName()<<","<<current->getStudent()->getLastName()<<", "<<current->getStudent()->getGPA()<<endl;
	current = current->getNext();
      }
      cout<<i<<","<<current->getStudent()->getId()<<", "<<current->getStudent \
()->getFirstName()<<","<<current->getStudent()->getLastName()<<", "<<current->getStudent()->getGPA()<<endl;
    }
  }

}
void hashDelete(int deletedId,Node* hash[],int bucketSize){

  int value = 0;
  value = deletedId % bucketSize;
  if(hash[value] == NULL){
    cout<<"This value does not exist"<<endl; 
    }
  else{
    if(hash[value]->getNext() == NULL){
      hash[value] = NULL;
    }
    else{
      hash[value] = hash[value]->getNext();
    }
  }

}

bool quit(){//quits the game
  cout<<"Goodbye"<<endl;
  return false;
}













 
