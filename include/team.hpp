#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include <vector>
#include "player.hpp"
#include "coach.hpp"

class Team {
protected:
  std::string name;
  Coach assigned_coach;
  Player squad[11];
  std::vector<Player> sub;
  int rank;
  int world_cup_won;
  double overall_atk, overall_def;
public:
  Team(std::string name);
  void set_world_cup(int new_world_cup_count);
  void set_coach(Coach new_coach);
  void add_to_squad(Player p, int i);
  void add_to_sub(Player p);

  Coach get_coach();
};

#endif