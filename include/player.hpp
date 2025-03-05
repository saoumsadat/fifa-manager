#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "person.hpp"

class Player : public Person {
private:
  double salary = 50, price = 0;
  std::string team = "None", type;

public:
  Player(const std::string& name, int age, std::string type);
  void update_info() override;
  void update_info(std::string title, std::string info);
  void update_info(double salary);
  void display_info() override;
};

#endif