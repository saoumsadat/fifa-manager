#ifndef CLUB_TEAM_HPP
#define CLUB_TEAM_HPP

#include <iostream>
#include "../include/team.hpp"

class ClubTeam : public Team {
private:
  int ucl;
  std::vector<Player> transfer_list;
  int funds;

public:
  // Constructor
  ClubTeam(std::string team_name);

  // Setters
  void set_ucl(int new_ucl_count); 
  void add_to_transfer_list(Player p); 
  void set_funds(int new_funds);
  bool remove_from_transfer_list(Player p);

  //from display
  std::string GetClassName() const override;

  // Getters
  int get_ucl() const; 
  std::vector<Player> get_transfer_list() const; 
  int get_funds() const; 

};

#endif