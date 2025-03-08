#ifndef COACH_HPP
#define COACH_HPP

#include "../include/person.hpp"

class Coach : public Person {
private:
  int age;
  double tactics;
  std::string team;

public:
  Coach() : Person("", 0) {}  // Default constructor
  Coach(const std::string& name, int age);

  //no need to bring back parents set_info as both have 1 parameter

  void set_info(std::string team);
  void set_info(double tactics);

  std::string get_team() const;
  double get_tactics() const;

  void display_info() override;
  
};

#endif