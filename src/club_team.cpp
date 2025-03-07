#include <iostream>
#include <team.hpp>
#include "../include/club_team.hpp"
#include "player.hpp"

ClubTeam::ClubTeam(std::string team_name) : Team(team_name) {}

void ClubTeam::set_ucl(int new_ucl_count) {
  this->ucl_won = new_ucl_count;
}

void ClubTeam::add_to_transfer_list(Player p) {
  this->transfer_list.push_back(p);
}

void ClubTeam::set_funds(int new_funds) {
  this->funds = new_funds;
}

std::string ClubTeam::GetClassName() const {
  return "Club";
}