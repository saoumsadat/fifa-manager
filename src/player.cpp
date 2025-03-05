#include "../include/player.hpp"
#include "../include/person.hpp"
#include <iostream>

Player::Player(const std::string& name, int age, std::string type)
  : Person(name, age), type(type) {}


void Player::update_info() {
  // Default update behavior, if necessary
}

void Player::update_info(std::string title, std::string info) {
  if (title == "team") {
    team = info;
  } else if (title == "type") {
    type = info;
  }
}

void Player::update_info(double new_salary) {
  salary = new_salary;
}

void Player::display_info() {
  Person::display_info();  // Call base class method
  std::cout << "Team: " << team << std::endl;
  std::cout << "Salary: $" << salary << std::endl;
  std::cout << "Type: " << type << std::endl;
}