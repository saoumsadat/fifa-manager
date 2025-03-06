#include "team.hpp"
#include <iostream>
#include "player.hpp"

class NationalTeam : public Team {
private:
  std::vector<Player> reserve;
public:
  NationalTeam(std::string team_name);
  void add_to_res(Player p);
};