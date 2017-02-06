// Patrick Aben paben001@ucr.edu 861101855
// Partner: Apollo Truong

// Lab 3: Composite and Streategy Patterns


#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

// Composite Pattern
///////////////////////////////////////////////////////////////
class Base {
 public:
 /* Constructors */
 Base() { };
 /* Pure Virtual Functions */
 virtual double evaluate() = 0;
};

// Op is a leaf node containing a value
class Op: public Base{
private:
  double number;
public:
  Op(double val)
  {
    number = val;
  }
  double evaluate()
  {
    return number;
  }
};


// nodes used to do operations on the op class values
class Mult: public Base{
private:
  Base* v1;
  Base* v2;
public:
  Mult(Base* a, Base* b)
  {
    v1 = a;
    v2 = b;
  }
  double evaluate()
  {
    return (v1->evaluate() * v2->evaluate());
  }
};

class Div: public Base{
private:
  Base* v1;
  Base* v2;
public:
  Div(Base* a, Base* b)
  {
    v1 = a;
    v2 = b;
  }
  double evaluate()
  {
    return (v1->evaluate() / v2-> evaluate());
  }
};

class Add: public Base{
private:
  Base* v1;
  Base* v2;
public:
  Add(Base* a, Base* b)
  {
    v1 = a;
    v2 = b;
  }
  double evaluate()
  {
    return (v1->evaluate() + v2-> evaluate());
  }
};

class Sub: public Base{
private:
  Base* v1;
  Base* v2;
public:
  Sub(Base* a, Base* b)
  {
    v1 = a;
    v2 = b;
  }
  double evaluate()
  {
    return (v1->evaluate() - v2->evaluate());
  }
};

class Sqr: public Base{
private:
  Base* v;
public:
  Sqr(Base* a)
  {
    v = a;
  }
  double evaluate()
  {
    return (v->evaluate() * v-> evaluate());
  }
};
///////////////////////////////////////////////////////////////

// Strategy Pattern
///////////////////////////////////////////////////////////////

class Container;

class Sort{
public:
  /* Constructors */
  Sort(){};
  /* Pure Virtual Functions */
  virtual void sort(Container* container) = 0;
};

class Container {
protected:
  Sort* sort_function;
public:
  /* Constructors */
  Container() : sort_function(NULL){};
  Container(Sort* function) : sort_function(function) {};
  /* Non Virtual Functions */
  void set_sort_function(Sort* sort_function);
  // set the type of sorting algorithm
  /* Pure Virtual Functions */
  // push the top pointer of the tree into container
  virtual void add_element(Base* element) = 0;
  // iterate through trees and output values
  virtual void print() = 0;
  // calls on the previously set sorting-algorithm. Checks if
  // sort_function is not null, throw exception if otherwise
  virtual void sort() = 0;
  /* Essentially the only functions needed to sort */
  //switch tree locations
  virtual void swap(int i, int j) = 0;
  // get top ptr of tree at index i
  virtual Base* at(int i) = 0;
  // return container size
  virtual int size() = 0;
};



class VectorContainer : public Container{
protected:
  vector<Base*> lest;
public:
  VectorContainer() {};
  VectorContainer(Sort* func){
    this->set_sort_function(func);
  };
  void set_sort_function(Sort* sort_function){
    this->sort_function = sort_function;
  }
  virtual void add_element(Base* element){
    lest.push_back(element);
  }

  virtual void print(){
    for(int i = 0; i < lest.size(); i++){
      cout << lest.at(i)->evaluate() << endl;
    }
  }

  virtual void sort(){
    if(sort_function == NULL){
      cout << "You didn't choose a sort function, friend." << endl;
    }
    else{
      sort_function->sort(this);
    }
  }

  virtual void swap(int i, int j){
    vector <Base*>::iterator first = lest.begin();
    vector <Base*>::iterator second = lest.begin();
    int tempi = 0;
    while(tempi < i){
      ++first;
      ++tempi;
    }
    int tempj = 0;
    while(tempj < j){
      ++second;
      ++tempj;
    }
    std::swap (*first, *second);
  }

  virtual Base* at(int i){
    vector <Base*>::iterator here = lest.begin();
    int temp = 0;
    while(temp < i){
      ++here;
      ++temp;
    }
    return *here;
  }

  virtual int size(){
    return lest.size();
  }

};

class ListContainer : public Container{
private:
  int max;
protected:
  list<Base*> lest;
  Sort* sort_function;
public:
  ListContainer()  { };
  ListContainer(Sort* func){
    this->set_sort_function(func);
  }

  void set_sort_function(Sort* sort_function){
    this->sort_function = sort_function;
  }

  virtual void add_element(Base* element){
    lest.push_back(element);
    max++;
  }

  virtual void print(){
    for(list<Base*>::iterator itr=lest.begin(); itr != lest.end(); ++itr){
      Base* temp = *itr;
      cout << temp->evaluate() << endl;
    }
  }

  virtual void sort(){
    if(sort_function == NULL){
      cout << "sort_function hasnt been selected";
    }
    else{
        sort_function->sort(this);
    }
  }

  virtual void swap(int i, int j){
    if(i >= max || j >= max){
      cout << "ERROR: cannot swap " << i << " and " << j << endl;
      return;
    }

    list<Base*>::iterator itr_i = lest.begin();
    for(int c = 0; c < i; c++){
      itr_i++;
    }

    list<Base*>::iterator itr_j = lest.begin();
    for(int c = 0; c < j; c++){
      itr_j++;
    }

    Base* temp_i = *itr_i;
    Base* temp_j = *itr_j;
    Base* temp_swap;

    temp_swap = temp_j;
    temp_j = temp_i;
    temp_i = temp_swap;

    *itr_i = temp_i;
    *itr_j = temp_j;
  }

  virtual Base* at(int i){
    list <Base*>::iterator itr = lest.begin();
    for(int k = 0; k < i; k++){
      itr++;
    }
    return *itr;
  }

  virtual int size(){
    return max;
  }

};

class Bubblesort : public Sort{
public:
  Bubblesort() { };
  virtual void sort(Container* container){
    int size = container->size();
    for(int i = 0; i < size-1 ; i++){
      for(int j = 0; j < size-1 ; j++){
        if(container->at(j)->evaluate() > container->at(j+1)->evaluate()){
          container->swap(j,j+1);
        }
      }
    }
  }
};


class Selectionsort : public Sort
{
  public:
    Selectionsort() {};

    void sort(Container* container)
    {
      int i;
      int j;
      int min;
      int n = container->size();

      for(i = n - 1; i > 0; i--){
        min = 0;
        for(j = 1; j <= i; j++){
          if(container->at(j)->evaluate() > container->at(min)->evaluate()){
            min = j;
          }
        }
        container->swap(min, i);
      }

    }
};





int main(){
  Op* op7 = new Op(7);
  Op* op4 = new Op(4);
  Op* op3 = new Op(3);
  Op* op2 = new Op(2);
  Mult* A = new Mult(op7, op4);
  Add* B = new Add(op3, A);
  Sub* C = new Sub(B, op2);
  Sqr* D = new Sqr(C);

  VectorContainer* container = new VectorContainer();
  container->add_element(A);
  container->add_element(B);
  container->add_element(C);
  container->add_element(D);

  cout << "Container Before Sort: " << endl;
  container->print();

  cout << "Container After Sort: " << endl;

  container->set_sort_function(new Bubblesort());

  container->sort();
  container->print();

  return 0;
};
