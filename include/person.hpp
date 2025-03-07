#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include "fifa.hpp"

class Person {
protected:
  std::string name, nationality;
  int age, salary;
public:
  Person(std::string name, int age);

  std::string get_name() const;
  std::string get_nationality() const;
  int get_age() const;
  int get_salary() const;
  
  void set_info(int salary);
  void set_info(std::string nationality);

  virtual void display_info();
};

#endif