#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include <vector>
#include "player.hpp"
#include "display.hpp"
#include "coach.hpp"
#include "fifa.hpp"

class Team : public Display {
protected:
  std::string name;
  Coach assigned_coach;
  Player squad[11];
  std::vector<Player> sub;
public:
  Team(std::string name);
  
  void set_coach(Coach new_coach);
  void add_to_squad(Player p, int i);
  void add_to_sub(Player p);

  std::string get_name() const;
  Coach get_coach() const;
  const Player* get_squad() const;
  const std::vector<Player>& get_sub() const;

  //overriding from display
  std::string GetClassName() const override;

};

#endif