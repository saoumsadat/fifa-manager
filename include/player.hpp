#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "person.hpp"

class Player : public Person {
private:
  int goals;
  double atk, def;
  std::string national_team, club_team, type;

public:
  Player() : Person("", 0) {}  // Default constructor
  Player(const std::string& name, int age);

  using Person::set_info;  // Bring back base class methods

  void set_info(std::string title, std::string info); //national_team, club_team, type
  void set_info(std::string title, int num);  //goals
  void set_info(std::string title, double num);  //atk, def

  void display_info() override;
};

#endif