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
    cout << "0. Go back" << endl;
    cout << "\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
    {
      national_team->get_coach().display_info();
    }
    else if (choice == 2)
    {

      const Player *squad = national_team->get_squad();
      for (int i = 0; i < 11; i++)
      {
        cout << squad[i].get_name() << endl;
      }
    }
    else if (choice == 0)
    {
      break;
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
    cout << "0. Go back" << endl;
    cout << "\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
    {
      club_team->get_coach().display_info();
    }
    else if (choice == 2)
    {

      const Player *squad = club_team->get_squad();
      for (int i = 0; i < 11; i++)
      {
        cout << squad[i].get_name() << endl;
      }
    }
    else if (choice == 0)
    {
      break;
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

      Market::search_player(player_name);
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

Team* get_new_team_obj(const std::string& team_type) {
  std::string team_name;

  // Prompt for team name
  std::cout << "Enter " << team_type << " name: ";
  std::cin >> team_name;

  // Create the team object based on the team type
  Team* team = Fifa::create_team_obj(team_name, team_type);
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
      Team* new_team = get_new_team_obj("national_team");
      NationalTeam* new_national_team = dynamic_cast<NationalTeam*>(new_team);
      cout << new_national_team->get_name() << endl;
      Fifa::write_national_team(*new_national_team);
    }
    if (choice == 4)
    {
      Team* new_team = get_new_team_obj("club_team");
      ClubTeam* new_club_team = dynamic_cast<ClubTeam*>(new_team);
      cout << new_club_team->get_name() << endl;
      Fifa::write_club_team(*new_club_team);
    }
  }
}

void edit_mode()
{
  int choice;
  cout << "\n1. Edit a Player" << endl;
  cout << "2. Edit a Coach" << endl;
  cout << "3. Edit a NationalTeam" << endl;
  cout << "4. Edit a ClubTeam" << endl;
  cout << "0. Go Back" << endl;
  cout << "Enter choice: ";
  cin >> choice;

  while (true)
  {
    if (choice == 0)
      break;
    if (choice == 1)
    {
     
    }
    if (choice == 2)
    {
  
    }
    if (choice == 3)
    {
  
    }
    if (choice == 4)
    {
  
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
  }
  return 0;
}
