#include "../include/coach.hpp"
#include <iostream>

Coach::Coach(const std::string& name, int age)
  : Person(name, age) {
    this->team = "None";
  }

void Coach::set_info(std::string team) {
  this->team = team;
}

void Coach::set_info(int salary){
  this->salary;
}

void Coach::set_info(double tactics){
  this->tactics;
}