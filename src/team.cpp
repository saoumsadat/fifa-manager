#include <iostream>
#include "../include/team.hpp"

Team::Team(std::string name) : name(name)
{
  this->assigned_coach = Coach();
}

void Team::set_coach(Coach new_coach)
{
  this->assigned_coach = new_coach;
}

void Team::add_to_squad(Player p, int i)
{
  if (i >= 0 && i < 11) // Ensure the index is valid
  {                        
    this->squad[i] = p; // Place the player in the squad
  }
  else
  {
    std::cerr << "Invalid squad index!" << std::endl;
  }
}

void Team::add_to_sub(Player p)
{
  this->sub.push_back(p);
}

void Team::swap_player(Player &squad_player, Player &sub_player)
{
  // Step 1: Find the squad player in the squad array
  int squad_index = -1;
  for (int i = 0; i < 11; ++i)
  {
    if (squad[i].get_name() == squad_player.get_name())
    {
      squad_index = i; // Found the squad player
      break;
    }
  }

  // Step 2: Find the substitute player in the sub vector
  int sub_index = -1;
  for (size_t i = 0; i < sub.size(); ++i)
  {
    if (sub[i].get_name() == sub_player.get_name())
    {
      sub_index = i; // Found the substitute player
      break;
    }
  }

  // Step 3: Swap their positions
  if (squad_index != -1 && sub_index != -1)
  {
    // Swap the squad player with the substitute player
    Player temp = squad[squad_index];
    squad[squad_index] = sub[sub_index];
    sub[sub_index] = temp;

    std::cout << "Swapped " << squad_player.get_name() << " (squad) with "
              << sub_player.get_name() << " (sub)." << std::endl;
  }
  else
  {
    std::cerr << "Error: One or both players not found in squad or sub!" << std::endl;
  }
}

std::string Team::get_name() const
{
  return this->name;
}

Coach Team::get_coach() const
{
  return this->assigned_coach;
}

// Get the squad array
const Player *Team::get_squad() const
{
  return this->squad; // Returns a pointer to the first element of the array
}

// Get the substitutes vector
const std::vector<Player> &Team::get_sub() const
{
  return this->sub; // Returns a reference to the vector
}

std::string Team::GetClassName() const
{
  return "Team";
}

void Team::display_players() const
{
  // Display squad players
  std::cout << "Squad Players:" << std::endl;
  for (int i = 0; i < 11; ++i)
  {
    if (this->squad[i].get_name() != "NoName")
    { // Check for default name
      std::cout << this->squad[i].get_name() << std::endl;
    }
    else
    {
      std::cout << "(Empty)" << std::endl; // Handle empty slots
    }
  }

  // Display substitute players
  std::cout << "\nSub Players:" << std::endl;
  if (this->sub.empty())
  {
    std::cout << "(No substitutes)" << std::endl;
  }
  else
  {
    for (const Player &player : this->sub)
    {
      std::cout << player.get_name() << std::endl;
    }
  }
}