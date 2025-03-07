#ifndef NATIONAL_TEAM_HPP
#define NATIONAL_TEAM_HPP

#include <iostream>
#include "team.hpp"

class NationalTeam : public Team {
private:
  int world_cup;
  std::vector<Player> reserve;

public:
  NationalTeam(std::string team_name);

  void set_world_cup(int new_world_cup_count);
  void add_to_res(Player p);

  int get_world_cup() const;
  const std::vector<Player>& get_reserve() const; 

  //overriding getclassname from display
  std::string GetClassName() const override;

};

#endif