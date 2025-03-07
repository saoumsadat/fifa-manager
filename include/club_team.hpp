#ifndef CLUB_TEAM_HPP
#define CLUB_TEAM_HPP

#include <iostream>
#include "team.hpp"

class ClubTeam : public Team {
private:
  int ucl_won; // Number of UEFA Champions League titles won
  std::vector<Player> transfer_list; // List of players on the transfer list
  int funds; // Financial funds available for transfers

public:
  // Constructor
  ClubTeam(std::string team_name);

  // Setters
  void set_ucl(int new_ucl_count); // Set the number of UCL titles
  void add_to_transfer_list(Player p); // Add a player to the transfer list
  void set_funds(int new_funds); // Set the available funds

  //from display
  std::string GetClassName() const override;


  // Getters
  // int get_ucl(); // Get the number of UCL titles
  // std::vector<Player> get_transfer_list(); // Get the transfer list
  // int get_funds(); // Get the available funds
};

#endif