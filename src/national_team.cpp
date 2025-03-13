#include <iostream>
#include "../include/national_team.hpp"

int NationalTeam::national_teams_count = 0;
std::vector<NationalTeam> NationalTeam::all_national_teams;

// Operator overloading as member functions
bool NationalTeam::operator>(const NationalTeam &other) const
{
  return this->world_cup > other.world_cup;
}

bool NationalTeam::operator<(const NationalTeam &other) const
{
  return this->world_cup < other.world_cup;
}

bool NationalTeam::operator==(const NationalTeam &other) const
{
  return this->world_cup == other.world_cup;
}

// Static function to sort national teams using selection sort
void NationalTeam::SortNationalTeams()
{
  for (size_t i = 0; i < all_national_teams.size() - 1; ++i)
  {
    size_t max_index = i;
    for (size_t j = i + 1; j < all_national_teams.size(); ++j)
    {
      if (all_national_teams[j] > all_national_teams[max_index])
      {
        max_index = j;
      }
    }
    if (max_index != i)
    {
      std::swap(all_national_teams[i], all_national_teams[max_index]);
    }
  }
}

void NationalTeam::LoadNationalTeamsFromFile()
{
  std::string filename = "../data/national_teams.txt";
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "Failed to open file: " << filename << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line))
  {
    if (line.find("Name: ") != std::string::npos)
    {
      // Use Fifa::extractInfo to extract the team name
      std::string name = Fifa::extractInfo<std::string>(line);

      // Assuming Fifa::load_national_team_data() returns a NationalTeam object
      NationalTeam team = Fifa::load_national_team_data(name);

      // Add the team to the static vector
      all_national_teams.push_back(team);

      // increase counter
      NationalTeam::national_teams_count++;
    }
  }

  file.close();
}

NationalTeam::NationalTeam(std::string team_name) : Team(team_name)
{
  this->world_cup = 0;
}

void NationalTeam::set_world_cup(int new_world_cup_count)
{
  this->world_cup = new_world_cup_count;
}

void NationalTeam::add_to_res(Player p)
{
  this->reserve.push_back(p);
}

std::string NationalTeam::GetClassName() const
{
  return "National";
}

int NationalTeam::get_world_cup() const
{
  return this->world_cup;
}

const std::vector<Player> &NationalTeam::get_reserve() const
{
  return this->reserve;
}