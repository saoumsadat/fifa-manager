#include <iostream>
#include "../include/club_team.hpp"

// Initialize the static vector
std::vector<ClubTeam> ClubTeam::all_club_teams;

// Initialize the static counter
int ClubTeam::club_teams_count = 0;

// Operator overloading as member functions
bool ClubTeam::operator>(const ClubTeam &other) const
{
  return this->ucl > other.ucl;
}

bool ClubTeam::operator<(const ClubTeam &other) const
{
  return this->ucl < other.ucl;
}

bool ClubTeam::operator==(const ClubTeam &other) const
{
  return this->ucl == other.ucl;
}

// Static function to sort club teams using selection sort
void ClubTeam::SortClubTeams()
{
  for (size_t i = 0; i < all_club_teams.size() - 1; ++i)
  {
    size_t max_index = i;
    for (size_t j = i + 1; j < all_club_teams.size(); ++j)
    {
      if (all_club_teams[j] > all_club_teams[max_index])
      {
        max_index = j;
      }
    }
    if (max_index != i)
    {
      std::swap(all_club_teams[i], all_club_teams[max_index]);
    }
  }
}

void ClubTeam::LoadClubTeamsFromFile()
{
  std::string filename = "../data/club_teams.txt";
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

      // Assuming Fifa::load_club_team_data() returns a ClubTeam object
      ClubTeam team = Fifa::load_club_team_data(name);

      // Add the team to the static vector
      all_club_teams.push_back(team);

      // Increment the counter
      club_teams_count++;
    }
  }

  file.close();
}

ClubTeam::ClubTeam(std::string team_name) : Team(team_name) {}

bool ClubTeam::check_player_exist(const Player &player) const
{
  // Check squad
  for (const Player &squadPlayer : squad)
  {
    if (squadPlayer.get_name() == player.get_name())
    {
      return true; // Player found in squad
    }
  }

  // Check substitutes
  for (const Player &subPlayer : sub)
  {
    if (subPlayer.get_name() == player.get_name())
    {
      return true; // Player found in substitutes
    }
  }

  return false; // Player not found
}

void ClubTeam::set_ucl(int new_ucl_count)
{
  this->ucl = new_ucl_count;
}

void ClubTeam::add_to_transfer_list(Player p)
{
  // Check if the player exists in the squad or substitutes
  if (check_player_exist(p))
  {
    this->transfer_list.push_back(p); // Add to transfer list
  }
  else
  {
    std::cout << "Player " << p.get_name() << " is not part of the squad or substitutes." << std::endl;
  }
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
      return true; // success
    }
  }
  return false; // failure
}

bool ClubTeam::remove_player(const Player &player)
{
  // Check squad
  for (int i = 0; i < 11; ++i)
  {
    if (squad[i].get_name() == player.get_name())
    {
      // Remove from squad and replace with a default-constructed Player
      squad[i] = Player(); // Use default constructor

      // Add the first substitute to the squad (if available)
      if (!sub.empty())
      {
        squad[i] = sub[0];      // Move the first substitute to the squad
        sub.erase(sub.begin()); // Remove the substitute from the sub list
      }

      return true; // Player found and removed
    }
  }

  // Check substitutes
  for (auto it = sub.begin(); it != sub.end(); ++it)
  {
    if (it->get_name() == player.get_name())
    {
      sub.erase(it); // Remove from substitutes
      return true;   // Player found and removed
    }
  }

  return false; // Player not found
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

void ClubTeam::display_transfer_list() const
{
  if (transfer_list.empty())
  {
    std::cout << "Transfer list is empty!" << std::endl;
    return;
  }

  std::cout << "Transfer List: " << ":\n";
  for (const Player &player : transfer_list)
  {
    std::cout << player.get_name() << "\n";
  }
}

int ClubTeam::get_funds() const
{
  return this->funds;
}
