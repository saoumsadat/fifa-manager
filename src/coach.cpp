#include "../include/coach.hpp"
#include <iostream>

Coach::Coach(const std::string& name, int age) : Person(name, age) {
  this->team = "None";
}

void Coach::set_info(std::string team) {
  this->team = team;
}

void Coach::set_info(double tactics) {
  this->tactics = tactics;
}

std::string Coach::get_team() const {
  return this->team;
}
double Coach::get_tactics() const {
  return this->tactics;
}

void Coach::display_info() {
  Person::display_info();  // Call base class method first
  std::cout << "Team: " << this->team << std::endl;
  std::cout << "Tactical Power: " << this->tactics << std::endl;
}