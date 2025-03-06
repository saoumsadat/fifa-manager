#include <iostream>
#include "../include/team.hpp"

Team::Team(std::string name) : name(name) {}

void Team::set_rank(int new_rank) {
  this->rank = new_rank;
}
void Team::set_world_cup(int new_world_cup_count) {
  this->world_cup_won = new_world_cup_count;
}

void Team::set_coach(Coach new_coach) {
  this->assigned_coach = new_coach;
}