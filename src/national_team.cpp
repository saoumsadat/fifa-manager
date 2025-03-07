#include <iostream>
#include "../include/national_team.hpp"

NationalTeam::NationalTeam(std::string team_name) : Team(team_name) {}

void NationalTeam::set_world_cup(int new_world_cup_count) {
  this->world_cup = new_world_cup_count;
}

void NationalTeam::add_to_res(Player p) {
  this->reserve.push_back(p);
}

std::string NationalTeam::GetClassName() const {
  return "National";
}

int NationalTeam::get_world_cup() const {
  return this->world_cup;
}

const std::vector<Player>& NationalTeam::get_reserve() const {
  return this->reserve;
}