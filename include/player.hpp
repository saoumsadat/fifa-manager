#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "person.hpp"

class Player : public Person {
private:
  int salary;
  int price;
  double atk, def;
  std::string national_team, club_team, type;

public:
  Player() : Person("", 0) {}  // Default constructor
  Player(const std::string& name, int age);
  void update_info() override;
  void update_info(std::string title, std::string info);
  void update_info(double salary);
  void display_info() override;
};

#endif