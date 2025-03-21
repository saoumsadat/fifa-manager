#include <iostream>
#include <algorithm> // For std::find
#include <limits>    // For std::numeric_limits
#include <vector>    // For std::vector
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

void NationalTeam::display_reserves() const
{
  if (this->reserve.empty())
  {
    std::cout << "Reserve List is empty!" << std::endl;
    return;
  }

  std::cout << "Reserve List: " << ":\n";
  for (const Player &player : this->reserve)
  {
    std::cout << player.get_name() << "\n";
  }
}

void NationalTeam::fetch_players()
{
  std::string filename = "../data/players.txt";
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
      // Extract the player's name
      std::string name = Fifa::extractInfo<std::string>(line);

      // Load the player object using Fifa::load_player
      Player player = Fifa::load_player(name);

      // Check if the player's nationality matches the national team's name
      if (player.get_nationality() == this->get_name())
      {
        // Add the player to the reserve vector
        this->reserve.push_back(player);
        cout << "Player " << player.get_name() << " has been added to the Reserve List" << endl;
      }
    }
  }

  file.close();
}

Player NationalTeam::add_without_selection(Player &player)
{
  // Check if the player exists in the reserve vector
  int reserve_index = -1;
  for (size_t i = 0; i < this->reserve.size(); ++i)
  {
    if (this->reserve[i] == player)
    {
      reserve_index = i;
      break;
    }
  }

  if (reserve_index == -1)
  {
    std::cerr << "Error: Player is not in the reserves!" << std::endl;
    return Player(); // Return an empty player in case of error
  }

  // Search squad for "NoName" player
  for (int i = 0; i < 11; ++i)
  {
    if (this->squad[i].get_name() == "NoName")
    {
      // Replace the "NoName" player with the player
      this->squad[i] = player;

      // Update national team status
      this->squad[i].set_info("national_team", this->get_name()); // Player now in squad

      // Remove the player from the reserve vector
      this->reserve.erase(this->reserve.begin() + reserve_index);

      cout << player.get_name() << " added without selection from Reserve List" << endl;

      // Return the added player
      return this->squad[i];
    }
  }

  // If no "NoName" player is found in the squad, add the player to the sub
  this->sub.push_back(player);

  // Update national team status
  this->sub.back().set_info("national_team", this->get_name()); // Player now in sub

  // Remove the player from the reserve vector
  this->reserve.erase(this->reserve.begin() + reserve_index);

  cout << player.get_name() << " added without selection from Reserve List" << endl;

  // Return the added player
  return this->sub.back();
}

std::tuple<Player, Player> NationalTeam::selection_process(Player &player)
{
  // Find the index of the player in the reserve vector
  int reserve_index = -1;
  for (size_t i = 0; i < this->reserve.size(); ++i)
  {
    if (this->reserve[i] == player)
    {
      reserve_index = i;
      break;
    }
  }

  // Check if the player is in the reserves
  if (reserve_index == -1)
  {
    std::cerr << "Error: Player is not in the reserves!" << std::endl;
    return std::make_tuple(Player(), Player()); // Return empty players in case of error
  }

  // Calculate the player's strength
  double res_player_strength = player.get_strength();

  // Find the player with the least strength of the same type in the squad or sub
  int weakest_index = -1;
  double least_strength = std::numeric_limits<double>::max();
  bool is_in_squad = true; // Flag to track if the weakest player is in squad or sub

  // Check squad (fixed size of 11)
  for (int i = 0; i < 11; ++i)
  {
    if (this->squad[i].get_type() == player.get_type())
    {
      if (this->squad[i].get_strength() < least_strength)
      {
        weakest_index = i;
        least_strength = this->squad[i].get_strength();
      }
    }
  }

  // Check sub (sub is a vector)
  for (size_t i = 0; i < this->sub.size(); ++i)
  {
    if (this->sub[i].get_type() == player.get_type() && this->sub[i].get_strength() < least_strength)
    {
      weakest_index = i;
      least_strength = this->sub[i].get_strength();
      is_in_squad = false; // Weakest player is in sub
    }
  }

  // If no player of the same type is found, player is eligible
  if (weakest_index == -1)
  {
    // Check for a "NoName" player in the squad
    for (int i = 0; i < 11; ++i)
    {
      if (this->squad[i].get_name() == "NoName")
      {
        // Replace the "NoName" player with the player passed to the function
        this->squad[i] = player;

        // Update national team status
        this->squad[i].set_info("national_team", this->get_name()); // Player now in squad

        // Remove the player from the reserve vector
        this->reserve.erase(this->reserve.begin() + reserve_index);

        // Print the addition message
        std::cout << "Selection passed: " << this->squad[i].get_name() << " added" << std::endl;

        // Return the recruited player and an empty player
        return std::make_tuple(this->squad[i], Player());
      }
    }

    // If no "NoName" player is found in the squad, add the player to the sub
    this->sub.push_back(player);

    // Update national team status
    this->sub.back().set_info("national_team", this->get_name()); // Player now in sub

    // Remove the player from the reserve vector
    this->reserve.erase(this->reserve.begin() + reserve_index);

    // Print the addition message
    std::cout << "Selection passed: " << this->sub.back().get_name() << " added" << std::endl;

    // Return the recruited player and an empty player
    return std::make_tuple(this->sub.back(), Player());
  }
  // If the least player's strength is greater than the reserve player's strength, player is not eligible
  else if (least_strength >= res_player_strength)
  {
    std::cerr << "Error: No suitable player to replace in the squad or sub!" << std::endl;
    return std::make_tuple(Player(), Player()); // Return empty players in case of error
  }

  // Swap the weakest player with the reserve player
  if (is_in_squad)
  {
    // Swap squad[weakest_index] with reserve[reserve_index]
    std::swap(this->squad[weakest_index], this->reserve[reserve_index]);

    // Update national team status
    this->squad[weakest_index].set_info("national_team", this->get_name()); // Reserve player now in squad
    this->reserve[reserve_index].set_info("national_team", "None");         // Weakest player now in reserves
  }
  else
  {
    // Swap sub[weakest_index] with reserve[reserve_index]
    std::swap(this->sub[weakest_index], this->reserve[reserve_index]);

    // Update national team status
    this->sub[weakest_index].set_info("national_team", this->get_name()); // Reserve player now in sub
    this->reserve[reserve_index].set_info("national_team", "None");       // Weakest player now in reserves
  }

  // Print the replacement message
  std::cout << "Selection passed: Replaced " << this->squad[weakest_index].get_name() << " with " << this->reserve[reserve_index].get_name() << std::endl;

  // Return both players in a tuple
  return std::make_tuple(this->squad[weakest_index], this->reserve[reserve_index]);
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