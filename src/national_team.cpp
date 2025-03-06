#include <iostream>
#include <team.hpp>
#include "../include/national_team.hpp"
#include "player.hpp"

NationalTeam::NationalTeam(std::string team_name) : Team(team_name) {}

void NationalTeam::recruit(Player new_player) {
    // Empty method body
}

void NationalTeam::reserve_to_sub(std::string name) {
    // Empty method body
}

void NationalTeam::sub_to_squad(Player new_player) {
    // Empty method body
}

void NationalTeam::remove_from_reserve(std::string name) {
    // Empty method body
}

void NationalTeam::remove_from_squad(std::string name) {
    // Empty method body
}

void NationalTeam::remove_from_sub(std::string name) {
    // Empty method body
}