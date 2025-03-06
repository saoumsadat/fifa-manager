#include "../include/player.hpp"
#include "../include/person.hpp"
#include <iostream>

Player::Player(const std::string& name, int age)
  : Person(name, age) {
    this->salary = 50;
    this->price = 0;
    this->type = "Unknown";
    this->national_team = "None";
    this->club_team = "None";
    this->atk = 0;
    this->def = 0;
  }


void Player::update_info() {
  // Default update behavior, if necessary
}

void Player::update_info(std::string title, std::string info) {
  // if (title == "team") {
  //   team = info;
  // } else if (title == "type") {
  //   type = info;
  // }
}

void Player::update_info(double new_salary) {
  salary = new_salary;
}

void Player::display_info() {
  // Person::display_info();  // Call base class method
  // std::cout << "Team: " << team << std::endl;
  // std::cout << "Salary: $" << salary << std::endl;
  // std::cout << "Type: " << type << std::endl;
}