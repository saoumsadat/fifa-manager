#include "../include/player.hpp"
#include "../include/person.hpp"
#include <iostream>

Player::Player(const std::string& name, int age)
  : Person(name, age) {
    this->salary = 50;
    this->price = 0;
    this->goals = 0;
    this->type = "Unknown";
    this->national_team = "None";
    this->club_team = "None";
    this->atk = 0;
    this->def = 0;
  }

//national_team, club_team, type, nationality
void Player::set_info(std::string title, std::string info) {
  if (title == "national_team") {
    this->national_team = info;
  } else if (title == "club_team") {
    this->club_team = info;
  } else if (title == type) {
    this->type = info;
  } else if (title == "nationality"){
    this->nationality = info;
  } else {
    std::cout << "Unknown title" << std::endl;
  }
}

//salary, price, goals
void Player::set_info(std::string title, int num) {
  if (title == "salary") {
    this->salary = num;
  } else if (title == "price") {
    this->price = num;
  } else if (title == "goals") {
    this->goals = num;
  } else {
    std::cout << "Unknown title" << std::endl;
  }
}

//atk, def
void Player::set_info(std::string title, double num) {
  if (title == "atk") {
    this->atk = num;
  } else if (title == "def") {
    this->def = num;
  } else {
    std::cout << "Unknown title" << std::endl;
  }
}

void Player::display_info() {
  // Person::display_info();  // Call base class method
  // std::cout << "Team: " << team << std::endl;
  // std::cout << "Salary: $" << salary << std::endl;
  // std::cout << "Type: " << type << std::endl;
}