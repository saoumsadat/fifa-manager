#ifndef COACH_HPP
#define COACH_HPP

#include "person.hpp"

class Coach : public Person {
private:
  int salary, age;
  double tactics;
  std::string team;

public:
  Coach() : Person("", 0) {}  // Default constructor
  Coach(const std::string& name, int age);
  void set_info(std::string team);
  void set_info(int salary);
  void set_info(double tactics);
};

#endif