#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>

class Person {
protected:
  std::string name, nationality;
  int age, salary;
public:
  Person(std::string name, int age);

  std::string get_name();
  std::string get_nationality();
  int get_age();
  int get_salary();
  
  void set_info(int salary);
  void set_info(std::string nationality);

  virtual void display_info();

};

#endif