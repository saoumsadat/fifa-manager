#ifndef MARKET_HPP
#define MARKET_HPP

#include <iostream>
#include <vector>
#include "../include/fifa.hpp"

using namespace std;

namespace Market {

  void list_players();
  tuple<Player, int> search_player(const string &player_name);
  void buy_player(ClubTeam& club, Player& player);
  void sell_player(ClubTeam& club, Player& player, int price);

}

#endif