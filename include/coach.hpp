#ifndef COACH_HPP
#define COACH_HPP

#include "../include/person.hpp"

class Coach : public Person {
private:
  int age;
  double tactics;
  std::string team;

public:
  Coach() : Person("NotAssigned", 0) {}  // Default constructor
  Coach(const std::string& name, int age);

  // Bring the set_info(int) method from the Person class into scope
  using Person::set_info;

  void set_info(std::string team);
  void set_info(double tactics);

  std::string get_team() const;
  double get_tactics() const;

  void display_info() override;
  friend void register_mode();
};

#endif