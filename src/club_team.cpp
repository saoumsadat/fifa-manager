#include <iostream>
#include "../include/club_team.hpp"

ClubTeam::ClubTeam(std::string team_name) : Team(team_name) {}

void ClubTeam::set_ucl(int new_ucl_count)
{
  this->ucl = new_ucl_count;
}

void ClubTeam::add_to_transfer_list(Player p)
{
  this->transfer_list.push_back(p);
}

void ClubTeam::set_funds(int new_funds)
{
  this->funds = new_funds;
}

bool ClubTeam::remove_from_transfer_list(Player p)
{
  for (auto it = transfer_list.begin(); it != transfer_list.end(); ++it)
  {
    if (it->get_name() == p.get_name())
    {
      transfer_list.erase(it);
      return true;  //success
    }
  }
  return false; //failure
}

std::string ClubTeam::GetClassName() const
{
  return "Club";
}

int ClubTeam::get_ucl() const
{
  return this->ucl;
}

std::vector<Player> ClubTeam::get_transfer_list() const
{
  return this->transfer_list;
}

int ClubTeam::get_funds() const
{
  return this->funds;
}