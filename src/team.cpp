#include <iostream>
#include "../include/team.hpp"

Team::Team(std::string name) : name(name) {}

void Team::set_world_cup(int new_world_cup_count) {
  this->world_cup_won = new_world_cup_count;
}

void Team::set_coach(Coach new_coach) {
  this->assigned_coach = new_coach;
}

void Team::add_to_squad(Player p, int i) {
  this->squad[i] = p;
}

void Team::add_to_sub(Player p) {
  this->sub.push_back(p);
}

Coach Team::get_coach() {
  return this->assigned_coach;
}