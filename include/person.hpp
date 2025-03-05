#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include <map>

class Person {
protected:
  std::string name;
  int age;
public:
  Person(std::string name, int age);
  virtual void update_info() = 0;  //pure virtual function as Name, age cannot be overriden
  virtual void display_info();
  virtual ~Person() {}
};

#endif