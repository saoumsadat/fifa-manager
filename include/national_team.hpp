#include "team.hpp"
#include <iostream>
#include "player.hpp"

class NationalTeam : public Team {
private:
  std::vector<Player> reserve;
public:
  NationalTeam(std::string team_name);
  void recruit(Player new_player);  //recruit from intranational clubs
  void reserve_to_sub(std::string name);  
  void sub_to_squad(Player new_player);
  void remove_from_reserve(std::string name); //player not elligible anymore
  void remove_from_squad(std::string name);
  void remove_from_sub(std::string name);
};