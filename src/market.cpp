#include <iostream>
#include "../include/market.hpp"

void Market::list_players()
{
  ifstream file("../data/market.txt");
  if (!file.is_open())
  {
    cerr << "Error opening market file!" << endl;
    return;
  }

  string line;
  string player_name;
  int player_price;

  while (getline(file, line))
  {
    if (line.find("Name:") != string::npos)
    {
      // Extract player name using extractInfo
      player_name = Fifa::extractInfo<string>(line);
    }
    else if (line.find("Price:") != string::npos)
    {
      // Extract player price using extractInfo
      player_price = Fifa::extractInfo<int>(line);

      // Display player name and price
      cout << player_name << " - " << player_price << endl;
    }
  }

  file.close();
}

tuple<Player, int> Market::search_player(const string &player_name)
{
  ifstream file("../data/market.txt");
  if (!file.is_open())
  {
    cerr << "Error opening market file!" << endl;
    return make_tuple(Player(), -1); // Return an empty player and invalid price
  }

  string line;
  string current_name;
  int current_price;
  Player player_obj; // Assuming Player is the class for the player object

  while (getline(file, line))
  {
    if (line.find("Name:") != string::npos)
    {
      // Extract player name using extractInfo
      current_name = Fifa::extractInfo<string>(line);

      // Check if the current name matches the search name
      if (current_name == player_name)
      {
        // Read the next line to get the price
        if (getline(file, line))
        {
          if (line.find("Price:") != string::npos)
          {
            // Extract player price using extractInfo
            current_price = Fifa::extractInfo<int>(line);

            // Assuming you have a function to create a Player object
            player_obj = Fifa::load_player(current_name);

            file.close();
            return make_tuple(player_obj, current_price); // Return player and price
          }
        }
      }
    }
  }

  file.close();
  return make_tuple(Player(), -1); // Return an empty player and invalid price if not found
}

void Market::buy_player(ClubTeam &club, Player &player)
{
  // Fetch the player's price from the market
  auto [found_player, price] = Market::search_player(player.get_name());

  if (price == -1)
  {
    std::cerr << "Player not found in the market!" << std::endl;
    return;
  }

  // Check if the club has enough funds
  if (club.get_funds() < price)
  {
    std::cerr << "Insufficient funds to buy " << player.get_name() << "!" << std::endl;
    return;
  }

  // Deduct the price from the club's funds
  club.set_funds(club.get_funds() - price);

  // Update the player's team status
  player.set_info("club_team", club.get_name());

  // Check if there's a "NoName" player in the squad
  bool added_to_squad = false;
  for (int i = 0; i < 11; ++i)
  {
    if (club.get_squad()[i].get_name() == "NoName")
    {
      // Place the new player in the squad at this index
      club.add_to_squad(player, i);
      added_to_squad = true;
      break;
    }
  }

  // If no "NoName" player was found, add the player to substitutes
  if (!added_to_squad)
  {
    club.add_to_sub(player);
  }

  // Remove the player from the market file
  Fifa::remove_player_from_market(player.get_name());

  std::cout << "Player " << player.get_name() << " has been bought by " << club.get_name() << " for " << price << "!" << std::endl;

  // Updating
  Fifa::update_club_team(club);
  Fifa::update_player(player);
}

void Market::sell_player(ClubTeam &club, Player &player, int price)
{

  // remove from transfer list
  bool is_removed_from_transfer_list = club.remove_from_transfer_list(player);

  if (!is_removed_from_transfer_list)
  {
    cout << "Player not found in transfer list" << endl;
    return;
  }

  // Remove from squad or substitutes
  bool is_removed_from_team = club.remove_player(player);

  if (!is_removed_from_team)
  {
    cout << "Player not found in squad or substitutes" << endl;
    return;
  }

  // change player status
  player.set_info("club_team", "None");

  // add price to fund
  club.set_funds(club.get_funds() + price);

  // saving to market.txt
  Fifa::add_player_to_market(player.get_name(), price);

  std::cout << "Player " << player.get_name() << " has been sold by " << club.get_name() << " for " << price << "!" << std::endl;

  // updating
  Fifa::update_club_team(club);
  Fifa::update_player(player);
}