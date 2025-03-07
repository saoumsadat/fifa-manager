#include <iostream>
#include "../include/player.hpp"

Player::Player(const std::string& name, int age)
  : Person(name, age) {
    this->goals = 0;
    this->type = "Unknown";
    this->national_team = "None";
    this->club_team = "None";
    this->atk = 0;
    this->def = 0;
  }

//national_team, club_team, type [nationality handled by parent -> 1 argument]
void Player::set_info(std::string title, std::string info) {
  
  if (title == "national_team") {
    this->national_team = info;
  } else if (title == "club_team") {
    this->club_team = info;
  } else if (title == "type") {
    this->type = info;
  } else {
    // std::cout << "Unknown title" ;
  }
}

//price, goals
void Player::set_info(std::string title, int num) {
  
  if (title == "goals") {
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
  Person::display_info();  // Call base class method first
  std::cout << "Type: " << this->type << std::endl;
  std::cout << "National Team: " << this->national_team << std::endl;
  std::cout << "Club Team: " << this->club_team << std::endl;
  std::cout << "Goals: " << this->goals << std::endl;
  std::cout << "Attacking Power: " << this->atk << std::endl;
  std::cout << "Defending Power: " << this->def << std::endl;
}