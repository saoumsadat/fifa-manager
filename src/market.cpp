#include <iostream>
#include "../include/market.hpp"

void Market::list_players() {
  ifstream file("../data/market.txt");
  if (!file.is_open()) {
    cerr << "Error opening market file!" << endl;
    return;
  }

  string line;
  string player_name;
  int player_price;

  while (getline(file, line)) {
    if (line.find("Name:") != string::npos) {
      // Extract player name using extractInfo
      player_name = Fifa::extractInfo<string>(line);
    } else if (line.find("Price:") != string::npos) {
      // Extract player price using extractInfo
      player_price = Fifa::extractInfo<int>(line);

      // Display player name and price
      cout << player_name << " - " << player_price << endl;
    }
  }

  file.close();
}

void Market::search_player(const string& player_name) {
  ifstream file("../data/market.txt");
  if (!file.is_open()) {
    cerr << "Error opening market file!" << endl;
    return;
  }

  string line;
  string current_name;
  int current_price;
  bool player_found = false;

  while (getline(file, line)) {
    if (line.find("Name:") != string::npos) {
      // Extract player name using extractInfo
      current_name = Fifa::extractInfo<string>(line);

      // Check if the current name matches the search name
      if (current_name == player_name) {
        player_found = true;

        // Read the next line to get the price
        if (getline(file, line)) {
          if (line.find("Price:") != string::npos) {
            // Extract player price using extractInfo
            current_price = Fifa::extractInfo<int>(line);

            // Display player name and price
            cout << current_name << " - " << current_price << endl;
          }
        }
        break; // Exit the loop once the player is found
      }
    }
  }

  if (!player_found) {
    cout << "Player '" << player_name << "' not found in the market." << endl;
  }

  file.close();
}

void Market::buy_player() {

}

void Market::sell_player(ClubTeam& club, const string& player_name) {

}