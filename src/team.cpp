#include <iostream>
#include "../include/team.hpp"

Team::Team(std::string name) : name(name) {
  this->assigned_coach = Coach();
}

void Team::set_coach(Coach new_coach) {
  this->assigned_coach = new_coach;
}

void Team::add_to_squad(Player p, int i) {
  if (i >= 0 && i <  11) this->squad[i] = p;
}

void Team::add_to_sub(Player p) {
  this->sub.push_back(p);
}

std::string Team::get_name() const {
  return this->name;
}

Coach Team::get_coach() const{
  return this->assigned_coach;
}

// Get the squad array
const Player* Team::get_squad() const {
  return this->squad; // Returns a pointer to the first element of the array
}

// Get the substitutes vector
const std::vector<Player>& Team::get_sub() const {
  return this->sub; // Returns a reference to the vector
}

std::string Team::GetClassName() const {
  return "Team";
}