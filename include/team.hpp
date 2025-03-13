#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include <vector>
#include "../include/display.hpp"
#include "../include/player.hpp"
#include "../include/coach.hpp"

// Forward declarations
class Player;
class Coach;

class Team : public Display {
protected:
  std::string name;
  Coach assigned_coach;
  Player squad[11];
  std::vector<Player> sub;
public:
  Team(std::string name);
  
  bool check_player_exist(const Player &player) const;

  void set_coach(Coach new_coach);
  void add_to_squad(Player p, int i);
  void add_to_sub(Player p);
  void swap_player(Player& squad_player, Player& sub_player);

  std::string get_name() const;
  Coach get_coach() const;
  const Player* get_squad() const;
  const std::vector<Player>& get_sub() const;

  void display_players() const;

  //overriding from display
  std::string GetClassName() const override;

};

#endif