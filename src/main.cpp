#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <memory>
#include "../include/fifa.hpp"
#include "../include/market.hpp"

using namespace std;
using namespace Fifa;
using namespace Market;

void national_coach_mode(unique_ptr<Team> &team_ptr)
{

  NationalTeam *national_team = dynamic_cast<NationalTeam *>(team_ptr.get());

  int choice;
  while (true)
  {
    cout << "\n1. National Coach Details" << endl;
    cout << "2. Display Players" << endl;
    cout << "3. Swap Players (squad <-> sub)" << endl;
    cout << "4. Recruit Player from Reserves" << endl;
    cout << "0. Go back" << endl;
    cout << "\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
    {
      national_team->get_coach().display_info();
    }
    else if (choice == 2)
    {
      national_team->display_players();
    }
    else if (choice == 0)
    {
      break;
    }
    else if (choice == 3)
    {
      string squad_player_name, sub_player_name;
      cout << "Enter Squad Player to swap: ";
      cin >> squad_player_name;
      cout << "Enter Sub Player to swap: ";
      cin >> sub_player_name;

      Player squad_player = Fifa::load_player(squad_player_name);
      Player sub_player = Fifa::load_player(sub_player_name);

      national_team->swap_player(squad_player, sub_player);
    }
    else if (choice == 4)
    {
    }
    else
    {
      cout << "Invalid choice" << endl;
    }
  }
}

void club_coach_mode(unique_ptr<Team> &team_ptr)
{

  ClubTeam *club_team = dynamic_cast<ClubTeam *>(team_ptr.get());

  int choice;
  while (true)
  {
    cout << "\n1. Club Coach Details" << endl;
    cout << "2. Display Players" << endl;
    cout << "3. Swap Players (squad <-> sub)" << endl;
    cout << "4. Add Player to Transfer List" << endl;
    cout << "5. Remove Player from Transfer List" << endl;
    cout << "0. Save and exit" << endl;
    cout << "-1. Go back" << endl;
    cout << "\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
    {
      club_team->get_coach().display_info();
    }
    else if (choice == 2)
    {
      club_team->display_players();
    }
    else if (choice == 3)
    {
      string squad_player_name, sub_player_name;
      cout << "Enter Squad Player to swap: ";
      cin >> squad_player_name;
      cout << "Enter Sub Player to swap: ";
      cin >> sub_player_name;

      Player squad_player = Fifa::load_player(squad_player_name);
      Player sub_player = Fifa::load_player(sub_player_name);

      club_team->swap_player(squad_player, sub_player);
    }
    else if (choice == 4)
    {
      string player_name;
      cout << "Enter Player Name: ";
      cin >> player_name;
      Player player = Fifa::load_player(player_name);
      club_team->add_to_transfer_list(player);
    }
    else if (choice == 5)
    {
      string player_name;
      cout << "Enter Player Name: ";
      cin >> player_name;
      Player player = Fifa::load_player(player_name);
      club_team->remove_from_transfer_list(player);
    }
    else if (choice == -1)
    {
      break;
    }
    else if (choice == 0)
    {
      Fifa::update_club_team(*club_team);
    }
    else
    {
      cout << "Invalid choice" << endl;
    }
  }
}

void coach_mode()
{
  string team_name;
  cout << "\nEnter Team Name:" << endl;
  cin >> team_name;

  std::unique_ptr<Team> loaded_team = check_return_team_type(team_name);

  string loaded_team_cls = loaded_team->GetClassName();

  int choice;

  if (loaded_team_cls == "National")
  {
    national_coach_mode(loaded_team);
  }
  else if (loaded_team_cls == "Club")
  {
    club_coach_mode(loaded_team);
  }
}

void market_mode()
{
  int choice;
  while (true)
  {
    cout << "\n1. List Available Players" << endl;
    cout << "2. Search Player by Name" << endl;
    cout << "3. Buy Player" << endl;
    cout << "4. Sell Player" << endl;
    cout << "0. Go Back" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 0)
      break;
    if (choice == 1)
    {
      Market::list_players();
    }
    if (choice == 2)
    {
      string player_name;
      cout << "Enter Player Name" << endl;
      cin >> player_name;

      auto [found_player, price] = Market::search_player(player_name);

      if (price == -1)
      {
        cout << "Player not found" << endl;
        continue;
      }

      cout << found_player.get_name() << " - " << price << endl;
    }
    if (choice == 3)
    {
      string club_team_name, player_name;
      cout << "Enter ClubTeam name: ";
      cin >> club_team_name;
      cout << "Enter Player name: ";
      cin >> player_name;

      ClubTeam club_team = Fifa::load_club_team_data(club_team_name);
      Player player = Fifa::load_player(player_name);

      Market::buy_player(club_team, player);
    }
    if (choice == 4)
    {
      string club_team_name, player_name;
      int price;
      cout << "Enter ClubTeam name: ";
      cin >> club_team_name;
      cout << "Enter Player name: ";
      cin >> player_name;
      cout << "Enter Price: ";
      cin >> price;

      ClubTeam club_team = Fifa::load_club_team_data(club_team_name);
      Player player = Fifa::load_player(player_name);

      Market::sell_player(club_team, player, price);
    }
  }
}

Player get_new_player_obj()
{
  std::string name, nationality, national_team, club_team, type;
  int age, goals, salary;
  double atk, def;

  // Collecting player details
  cout << "Enter player name: ";
  cin >> name;

  cout << "Enter player age: ";
  cin >> age;

  cout << "Enter player nationality: ";
  cin >> nationality;

  cout << "Enter player type (e.g., Forward, Midfielder): ";
  cin >> type;

  cout << "Enter attack rating (0.0 - 100.0): ";
  cin >> atk;

  cout << "Enter defense rating (0.0 - 100.0): ";
  cin >> def;

  Player new_player = Fifa::create_player_obj(name, age, nationality, type, atk, def);
  return new_player;
}

Coach get_new_coach_obj()
{
  std::string name, team, nationality;
  int age;
  double tactics;

  cout << "Enter coach name: ";
  cin >> name;

  cout << "Enter coach age: ";
  cin >> age;

  cout << "Enter coach nationality: ";
  cin >> nationality;

  cout << "Enter coach team: ";
  cin >> team;

  cout << "Enter coach tactics rating (0.0 - 100.0): ";
  cin >> tactics;

  Coach new_coach = Fifa::create_coach_obj(name, age, nationality, team, tactics);
  return new_coach;
}

Team *get_new_team_obj(const std::string &team_type)
{
  std::string team_name;

  // Prompt for team name
  std::cout << "Enter " << team_type << " name: ";
  std::cin >> team_name;

  // Create the team object based on the team type
  Team *team = Fifa::create_team_obj(team_name, team_type);
  return team;
}

void register_mode()
{
  int choice;
  while (true)
  {
    cout << "\n1. Register a Player" << endl;
    cout << "2. Register a Coach" << endl;
    cout << "3. Register a NationalTeam" << endl;
    cout << "4. Register a ClubTeam" << endl;
    cout << "0. Go Back" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 0)
      break;
    if (choice == 1)
    {
      Player new_player = get_new_player_obj();
      Fifa::write_player(new_player);
    }
    if (choice == 2)
    {
      Coach new_coach = get_new_coach_obj();
      Fifa::write_coach(new_coach);
    }
    if (choice == 3)
    {
      Team *new_team = get_new_team_obj("national_team");
      NationalTeam *new_national_team = dynamic_cast<NationalTeam *>(new_team);
      cout << new_national_team->get_name() << endl;
      Fifa::write_national_team(*new_national_team);
    }
    if (choice == 4)
    {
      Team *new_team = get_new_team_obj("club_team");
      ClubTeam *new_club_team = dynamic_cast<ClubTeam *>(new_team);
      cout << new_club_team->get_name() << endl;
      Fifa::write_club_team(*new_club_team);
    }
  }
}

void edit_player(const std::string &player_name)
{
  // Load the player object (assuming Fifa::load_player exists)
  Player player = Fifa::load_player(player_name);

  if (player.get_name().empty())
  {
    std::cerr << "Player not found!" << std::endl;
    return;
  }

  while (true)
  {
    std::cout << "\nEditing Player: " << player_name << std::endl;
    std::cout << "1. Edit Salary" << std::endl;
    std::cout << "2. Edit Type" << std::endl;
    std::cout << "3. Edit Goals" << std::endl;
    std::cout << "4. Edit Attack Rating" << std::endl;
    std::cout << "5. Edit Defense Rating" << std::endl;
    std::cout << "0. Save and Exit" << std::endl;
    std::cout << "-1. Exit without saving" << std::endl;
    std::cout << "Enter choice: ";
    int choice;
    std::cin >> choice;

    if (choice == -1)
    {
      break;
    }

    if (choice == 0)
    {
      // Save and exit
      Fifa::update_player(player);
      std::cout << "Player updated successfully!" << std::endl;
      break;
    }

    switch (choice)
    {
    case 1:
    {
      int salary;
      std::cout << "Enter new salary: ";
      std::cin >> salary;
      player.set_info(salary);
      break;
    }
    case 2:
    {
      std::string type;
      std::cout << "Enter new type: ";
      std::cin >> type;
      player.set_info("type", type);
      break;
    }
    case 3:
    {
      int goals;
      std::cout << "Enter new goals: ";
      std::cin >> goals;
      player.set_info("goals", goals);
      break;
    }
    case 4:
    {
      double atk;
      std::cout << "Enter new attack rating: ";
      std::cin >> atk;
      player.set_info("atk", atk);
      break;
    }
    case 5:
    {
      double def;
      std::cout << "Enter new defense rating: ";
      std::cin >> def;
      player.set_info("def", def);
      break;
    }
    default:
      std::cout << "Invalid choice. Please try again." << std::endl;
    }
  }
}

void edit_coach(const std::string &coach_name)
{
  // Load the coach object (assuming Fifa::load_coach exists)
  Coach coach = Fifa::load_coach(coach_name);

  if (coach.get_name().empty())
  {
    std::cerr << "Coach not found!" << std::endl;
    return;
  }

  while (true)
  {
    std::cout << "\nEditing Coach: " << coach_name << std::endl;
    std::cout << "1. Edit Salary" << std::endl;
    std::cout << "2. Edit Team" << std::endl;
    std::cout << "3. Edit Tactics Rating" << std::endl;
    std::cout << "0. Save and Exit" << std::endl;
    std::cout << "-1. Exit without saving" << std::endl;
    std::cout << "Enter choice: ";
    int choice;
    std::cin >> choice;

    if (choice == -1)
    {
      break;
    }

    if (choice == 0)
    {
      // Save and exit
      Fifa::update_coach(coach);
      std::cout << "Coach updated successfully!" << std::endl;
      break;
    }

    switch (choice)
    {
    case 1:
    {
      int salary;
      std::cout << "Enter new salary: ";
      std::cin >> salary;
      coach.set_info(salary);
      break;
    }
    case 2:
    {
      std::string team;
      std::cout << "Enter new team: ";
      std::cin >> team;
      coach.set_info(team);
      break;
    }
    case 3:
    {
      double tactics;
      std::cout << "Enter new tactics rating: ";
      std::cin >> tactics;
      coach.set_info(tactics);
      break;
    }
    default:
      std::cout << "Invalid choice. Please try again." << std::endl;
    }
  }
}

void edit_national_team(const std::string &national_team_name)
{
  // Load the national team object (assuming Fifa::load_national_team exists)
  NationalTeam national_team = Fifa::load_national_team_data(national_team_name);

  if (national_team.get_name().empty())
  {
    std::cerr << "National Team not found!" << std::endl;
    return;
  }

  while (true)
  {
    std::cout << "\nEditing National Team: " << national_team_name << std::endl;
    std::cout << "1. Edit Coach" << std::endl;
    std::cout << "2. Edit World Cup Count" << std::endl;
    std::cout << "0. Save and Exit" << std::endl;
    std::cout << "-1. Exit without saving" << std::endl;
    std::cout << "Enter choice: ";
    int choice;
    std::cin >> choice;

    if (choice == -1)
    {
      break;
    }

    if (choice == 0)
    {
      // Save and exit
      Fifa::update_national_team(national_team);
      std::cout << "National Team updated successfully!" << std::endl;
      break;
    }

    switch (choice)
    {
    case 1:
    {
      std::string coach_name;
      std::cout << "Enter new coach name: ";
      std::cin >> coach_name;
      Coach new_coach = Fifa::load_coach(coach_name);
      if (new_coach.get_team() != "None")
      {
        cout << "Failed. Coach is already assigned to a different team" << endl;
        continue;
      }

      if (new_coach.get_name().empty())
      {
        std::cerr << "Coach not found!" << std::endl;
      }
      else
      {
        // Update the coach's team status
        new_coach.set_info(national_team_name); // Set the coach's team to the national team
        Fifa::update_coach(new_coach);          // Save the updated coach

        // Update the national team's coach
        national_team.set_coach(new_coach);
      }
      break;
    }
    case 2:
    {
      int world_cup;
      std::cout << "Enter new World Cup count: ";
      std::cin >> world_cup;
      national_team.set_world_cup(world_cup);
      break;
    }
    default:
      std::cout << "Invalid choice. Please try again." << std::endl;
    }
  }
}

void edit_club_team(const std::string &club_team_name)
{
  // Load the club team object (assuming Fifa::load_club_team exists)
  ClubTeam club_team = Fifa::load_club_team_data(club_team_name);

  if (club_team.get_name().empty())
  {
    std::cerr << "Club Team not found!" << std::endl;
    return;
  }

  while (true)
  {
    std::cout << "\nEditing Club Team: " << club_team_name << std::endl;
    std::cout << "1. Edit Coach" << std::endl;
    std::cout << "2. Edit UCL Count" << std::endl;
    std::cout << "3. Edit Funds" << std::endl;
    std::cout << "0. Save and Exit" << std::endl;
    std::cout << "-1. Exit without saving" << std::endl;
    std::cout << "Enter choice: ";
    int choice;
    std::cin >> choice;

    if (choice == -1)
    {
      break;
    }

    if (choice == 0)
    {
      // Save and exit
      Fifa::update_club_team(club_team);
      std::cout << "Club Team updated successfully!" << std::endl;
      break;
    }

    switch (choice)
    {
    case 1:
    {
      std::string coach_name;
      std::cout << "Enter new coach name: ";
      std::cin >> coach_name;
      Coach new_coach = Fifa::load_coach(coach_name);
      if (new_coach.get_team() != "None")
      {
        cout << "Failed. Coach is already assigned to a different team" << endl;
        continue;
      }

      if (new_coach.get_name().empty())
      {
        std::cerr << "Coach not found!" << std::endl;
      }
      else
      {
        // Update the coach's team status
        new_coach.set_info(club_team_name); // Set the coach's team to the club team
        Fifa::update_coach(new_coach);      // Save the updated coach

        // Update the club team's coach
        club_team.set_coach(new_coach);
      }
      break;
    }
    case 2:
    {
      int ucl;
      std::cout << "Enter new UCL count: ";
      std::cin >> ucl;
      club_team.set_ucl(ucl);
      break;
    }
    case 3:
    {
      int funds;
      std::cout << "Enter new funds: ";
      std::cin >> funds;
      club_team.set_funds(funds);
      break;
    }
    default:
      std::cout << "Invalid choice. Please try again." << std::endl;
    }
  }
}

void edit_mode()
{
  int choice;
  while (true)
  {
    cout << "\n1. Edit a Player" << endl;
    cout << "2. Edit a Coach" << endl;
    cout << "3. Edit a NationalTeam" << endl;
    cout << "4. Edit a ClubTeam" << endl;
    cout << "0. Go Back" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    if (choice == 0)
      break;
    if (choice == 1)
    {
      string player_to_edit_name;
      cout << "Enter Player Name: ";
      cin >> player_to_edit_name;
      edit_player(player_to_edit_name);
    }
    if (choice == 2)
    {
      string coach_to_edit_name;
      cout << "Enter Coach Name: ";
      cin >> coach_to_edit_name;
      edit_coach(coach_to_edit_name);
    }
    if (choice == 3)
    {
      string national_team_to_edit_name;
      cout << "Enter NationalTeam Name: ";
      cin >> national_team_to_edit_name;
      edit_national_team(national_team_to_edit_name);
    }
    if (choice == 4)
    {
      string club_team_to_edit_name;
      cout << "Enter ClubTeam Name: ";
      cin >> club_team_to_edit_name;
      edit_club_team(club_team_to_edit_name);
    }
  }
}

void rank_mode()
{
  
  while (true)
  {
    cout << "\n1. Rank Players" << endl;
    cout << "2. Rank Coaches" << endl;
    cout << "3. Rank National Teams" << endl;
    cout << "4. Rank Club Teams" << endl;
    cout << "0. Go Back" << endl;
    cout << "Enter choice: ";
    int choice;
    cin >> choice;

    if (choice == 0)
    {
      break;
    }
    if (choice == 1)
    {
      //load first
      Player::LoadPlayersFromFile();
      Player::SortPlayers();

      // Display players with serial numbers
      std::cout << "Player Rankings:\n";
      for (size_t i = 0; i < Player::players_count; ++i) {
          std::cout << (i + 1) << ". " << Player::all_players[i].get_name() << std::endl;
      }
    }
    if (choice == 2)
    {
      //load first
      Coach::LoadCoachesFromFile();
      Coach::SortCoaches();

      // Display coaches with serial numbers
      std::cout << "Coach Rankings:\n";
      for (size_t i = 0; i < Coach::coaches_count; ++i) {
          std::cout << (i + 1) << ". " << Coach::all_coaches[i].get_name() << std::endl;
      }
    }
    if (choice == 3)
    {

      //load first
      NationalTeam::LoadNationalTeamsFromFile();
      NationalTeam::SortNationalTeams();

      // Display teams with serial numbers
      std::cout << "National Team Rankings:\n";
      for (size_t i = 0; i < NationalTeam::national_teams_count; ++i)
      {
        std::cout << (i + 1) << ". " << NationalTeam::all_national_teams[i].get_name() << std::endl;
      }
    }
    if (choice == 4)
    {
      //load first
      ClubTeam::LoadClubTeamsFromFile();      
      ClubTeam::SortClubTeams();

      // Display teams with serial numbers
      std::cout << "Club Team Rankings:\n";
      for (size_t i = 0; i < ClubTeam::club_teams_count; ++i)
      {
        std::cout << (i + 1) << ". " << ClubTeam::all_club_teams[i].get_name() << std::endl;
      }
    }
  }
}

int main()
{
  int option;
  while (true)
  {
    cout << "\n1. Enter Coach Mode" << endl;
    cout << "2. Enter Market" << endl;
    cout << "3. Register" << endl;
    cout << "4. Edit Info" << endl;
    cout << "5. See Ranking" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter choice: ";
    cin >> option;

    if (option == 0)
      break;
    if (option == 1)
      coach_mode();
    if (option == 2)
      market_mode();
    if (option == 3)
      register_mode();
    if (option == 4)
      edit_mode();
    if (option == 5)
      rank_mode();
  }
  return 0;
}
