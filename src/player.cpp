#include <iostream>
#include "../include/fifa.hpp"
#include "../include/player.hpp"

// Initialize the static vector
std::vector<Player> Player::all_players;

// Initialize the static counter
int Player::players_count = 0;

bool Player::operator>(const Player &other) const
{
  return this->get_strength() > other.get_strength();
}

bool Player::operator<(const Player &other) const
{
  return this->get_strength() < other.get_strength();
}

bool Player::operator==(const Player &other) const
{
  return this->get_strength() == other.get_strength();
}

// Helper function to calculate strength based on player type
double Player::get_strength() const
{
  if (type == "Attacker")
  {
    return atk;
  }
  else if (type == "Defender")
  {
    return def;
  }
  else if (type == "Midfielder")
  {
    return (atk + def) / 2.0; // Average of atk and def for midfielders
  }
  return 0.0; // Default strength for unknown types
}

// Static function to sort players using selection sort
void Player::SortPlayers()
{
  for (size_t i = 0; i < all_players.size() - 1; ++i)
  {
    size_t max_index = i;
    for (size_t j = i + 1; j < all_players.size(); ++j)
    {
      if (all_players[j] > all_players[max_index])
      {
        max_index = j;
      }
    }
    if (max_index != i)
    {
      std::swap(all_players[i], all_players[max_index]);
    }
  }
}

void Player::LoadPlayersFromFile()
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
      // Extract the player name
      std::string name = Fifa::extractInfo<std::string>(line);

      // Use Fifa::load_player() to create a Player object
      Player player = Fifa::load_player(name);

      // Add the player to the static vector
      all_players.push_back(player);

      // Increment the counter
      players_count++;
    }
  }

  file.close();
}

Player::Player(const std::string &name, int age)
    : Person(name, age)
{
  this->goals = 0;
  this->type = "Unknown";
  this->national_team = "None";
  this->club_team = "None";
  this->atk = 0;
  this->def = 0;
}

// national_team, club_team, type [nationality handled by parent -> 1 argument]
void Player::set_info(std::string title, std::string info)
{

  if (title == "national_team")
  {
    this->national_team = info;
  }
  else if (title == "club_team")
  {
    this->club_team = info;
  }
  else if (title == "type")
  {
    this->type = info;
  }
  else
  {
    // std::cout << "Unknown title" ;
  }
}

// price, goals
void Player::set_info(std::string title, int num)
{

  if (title == "goals")
  {
    this->goals = num;
  }
  else
  {
    std::cout << "Unknown title" << std::endl;
  }
}

// atk, def
void Player::set_info(std::string title, double num)
{

  if (title == "atk")
  {
    this->atk = num;
  }
  else if (title == "def")
  {
    this->def = num;
  }
  else
  {
    std::cout << "Unknown title" << std::endl;
  }
}

std::string Player::get_type() const
{
  return this->type;
}
std::string Player::get_national_team() const
{
  return this->national_team;
}
std::string Player::get_club_team() const
{
  return this->club_team;
}
int Player::get_goals() const
{
  return this->goals;
}
double Player::get_atk() const
{
  return this->atk;
}
double Player::get_def() const
{
  return this->def;
}

void Player::display_info()
{
  Person::display_info(); // Call base class method first
  std::cout << "Type: " << this->type << std::endl;
  std::cout << "National Team: " << this->national_team << std::endl;
  std::cout << "Club Team: " << this->club_team << std::endl;
  std::cout << "Goals: " << this->goals << std::endl;
  std::cout << "Attacking Power: " << this->atk << std::endl;
  std::cout << "Defending Power: " << this->def << std::endl;
}
