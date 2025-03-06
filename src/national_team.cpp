#include <iostream>
#include <team.hpp>
#include "../include/national_team.hpp"
#include "player.hpp"

NationalTeam::NationalTeam(std::string team_name) : Team(team_name) {}

void NationalTeam::add_to_res(Player p) {
  this->reserve.push_back(p);
}

void NationalTeam::recruit(Player new_player) {

}

void NationalTeam::reserve_to_sub(std::string name) {

}

void NationalTeam::sub_to_squad(Player new_player) {

}

void NationalTeam::remove_from_reserve(std::string name) {

}

void NationalTeam::remove_from_squad(std::string name) {

}

void NationalTeam::remove_from_sub(std::string name) {

}