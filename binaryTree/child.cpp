#include <iostream>
#include "child.h"
#include <cstring>

using namespace std;

Child::Child(int inputValue){
  value = inputValue;
}

Child::~Child(){

}

void Child::setRoot(int inputValue){
  value = inputValue;

}

int Child::getRoot(){
  return value;

}

