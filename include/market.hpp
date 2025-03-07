#include <iostream>
#include <vector>
#include "player.hpp"
#include "club_team.hpp"

using namespace std;

namespace market {

void browse_players();
void buy_player();
void search_player(const string& player_name);
void sell_player(ClubTeam& club, const string& player_name);

}
  