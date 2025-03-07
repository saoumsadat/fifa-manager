#include <iostream>
#include <team.hpp>
#include "../include/national_team.hpp"
#include "player.hpp"

NationalTeam::NationalTeam(std::string team_name) : Team(team_name) {}

void NationalTeam::set_world_cup(int new_world_cup_count) {
  this->world_cup_won = new_world_cup_count;
}

void NationalTeam::add_to_res(Player p) {
  this->reserve.push_back(p);
}

std::string NationalTeam::GetClassName() const {
  return "National";
}