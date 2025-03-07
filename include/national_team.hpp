#include "team.hpp"
#include <iostream>
#include "player.hpp"

class NationalTeam : public Team {
private:
  int world_cup_won;
  std::vector<Player> reserve;

public:
  NationalTeam(std::string team_name);

  void set_world_cup(int new_world_cup_count);
  void add_to_res(Player p);

  //overriding getclassname from display
  std::string GetClassName() const override;
};