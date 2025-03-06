#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>

class Person {
protected:
  std::string name;
  int age;
public:
  Person(std::string name, int age);
  std::string get_name();
  int Person::get_age();
  virtual void display_info();
  virtual ~Person() {}
};

#endif