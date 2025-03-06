#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "person.hpp"

class Player : public Person {
private:
  int salary, price, goals;
  double atk, def;
  std::string national_team, club_team, type, nationality;

public:
  Player() : Person("", 0) {}  // Default constructor
  Player(const std::string& name, int age);

  void set_info(std::string title, std::string info); //national_team, club_team, type, nationality
  void set_info(std::string title, int num);  //salary, price, goals
  void set_info(std::string title, double num);  //atk, def

  void display_info() override;
};

#endif