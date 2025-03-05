class Player:
    def __init__(self, name):
        self.name = name
        self.salary = 0
        self.stats = {"Attacking": 0.0,"Midfield": 0.0, "Defending":0.0}  # Dictionary: {"goals": 10, "assists": 5, ...}
        self.bio = {} # Dictionary: {"age": 25, "nationality": "Brazil", ...}
        self.price = 0 
        self.team = None  # The team the player belongs to

    def update_stats(self, new_stats):
        """Update player statistics."""
        for key, value in new_stats.items():
            if key in self.stats:
                self.stats[key] = value
        #update price
        
        #update salary


    def transfer(self, new_team):
        """Transfer player to a new team."""
        if self.team is not None:
            self.team.remove_player(self)
        new_team.add_player(self)
        self.team = new_team
        print(f"{self.name} has been transferred to {new_team.name}.")

    def __str__(self):
        return f"Player: {self.name}, Team: {self.team.name if self.team else 'None'}, Price: ${self.price}"
    



class Team:
    def __init__(self, name, tactics, bio):
        self.name = name
        self.tactics = tactics
        self.bio = bio
        self.players = []

    def add_player(self, player):
        """Add a player to the team."""
        self.players.append(player)
        player.team = self
        print(f"{player.name} has been added to {self.name}.")

    def remove_player(self, player):
        """Remove a player from the team."""
        if player in self.players:
            self.players.remove(player)
            player.team = None
            print(f"{player.name} has been removed from {self.name}.")
        else:
            print(f"{player.name} is not in {self.name}.")

    def set_tactics(self, tactics):
        """Update team tactics."""
        self.tactics = tactics
        print(f"{self.name} tactics updated to {tactics}.")

    def __str__(self):
        return f"Team: {self.name}, Players: {len(self.players)}"
    
    
class NationalTeam(Team):
    def __init__(self, name, tactics, bio):
        super().__init__(name, tactics, bio)
        self.candidates = []  # Players eligible for selection
        # self.selection_method = "Performance-based"  # Default selection method

    def select_player(self, player):
        """Select a player from candidates to the national team."""
        if player in self.candidates:
            self.add_player(player)
            self.candidates.remove(player)
            print(f"{player.name} has been selected for {self.name}.")
        else:
            print(f"{player.name} is not a candidate for {self.name}.")

    # def organize_tournament(self):
    #     """Organize intra-national tournaments to find new candidates."""
    #     print(f"Organizing intra-national tournament for {self.name}...")
    #     # Simulate finding new candidates (for simplicity, add some players)
    #     new_candidates = [
    #         Player("Candidate 1", 50000, {"goals": 2}, {"age": 22}, 1000000),
    #         Player("Candidate 2", 60000, {"goals": 3}, {"age": 23}, 1500000),
    #     ]
    #     self.candidates.extend(new_candidates)
    #     print(f"Found {len(new_candidates)} new candidates for {self.name}.")

class ClubTeam(Team):
    def __init__(self, name, tactics, bio, funds):
        super().__init__(name, tactics, bio)
        self.funds = funds
        self.transfer_budget = funds * 0.9  # Allocate 90% of funds for transfers

    # def purchase_player(self, player, seller):
    #     """Purchase a player from another team."""
    #     if self.funds >= player.price:
    #         self.funds -= player.price
    #         seller.funds += player.price
    #         player.transfer(self)
    #         print(f"{self.name} has purchased {player.name} for ${player.price}.")
    #     else:
    #         print(f"{self.name} does not have enough funds to purchase {player.name}.")

    # def sell_player(self, player, buyer):
    #     """Sell a player to another team."""
    #     if player in self.players:
    #         buyer.purchase_player(player, self)
    #     else:
    #         print(f"{player.name} is not in {self.name}.")

    def manage_funds(self, amount):
        """Update club funds."""
        self.funds += amount
        print(f"{self.name} funds updated. New balance: ${self.funds}.")


class FIFAManager:
    def __init__(self):
        self.previous_records = {}  # Dictionary to store historical data
        self.teams = []  # List of all teams
        self.players = []  # List of all players

    def hold_match(self, team1, team2):
        """Simulate a match between two teams."""
        print(f"Match between {team1.name} and {team2.name} is starting...")
        # Simulate match outcome (for simplicity, random winner)
        import random
        winner = random.choice([team1, team2])
        print(f"{winner.name} wins the match!")

    def measure_performance(self, entity):
        """Measure performance of a player or team."""
        if isinstance(entity, Player):
            print(f"Performance of {entity.name}: {entity.stats}")
        elif isinstance(entity, Team):
            print(f"Performance of {entity.name}: {len(entity.players)} players, Tactics: {entity.tactics}")

    def update_records(self, event):
        """Update historical records."""
        self.previous_records[len(self.previous_records) + 1] = event
        print(f"Record updated: {event}")

    def organize_tournament(self, teams):
        """Organize a tournament."""
        print(f"Organizing tournament with {len(teams)} teams...")
        winner = random.choice(teams)
        print(f"{winner.name} wins the tournament!")
        self.update_records(f"Tournament won by {winner.name}")



# class Transaction:
#     def __init__(self):
#         self.market = []  # List of players available for transfer
#         self.transactions = []  # List of completed transactions

#     def search_player(self, criteria):
#         """Search for players in the market based on criteria."""
#         results = [player for player in self.market if all(player.bio.get(key) == value for key, value in criteria.items())]
#         print(f"Search results: {[player.name for player in results]}")
#         return results

#     def transfer_player(self, player, buyer, seller):
#         """Handle player transfer between teams."""
#         if player in seller.players:
#             buyer.purchase_player(player, seller)
#             self.transactions.append((player.name, seller.name, buyer.name))
#         else:
#             print(f"{player.name} is not in {seller.name}.")

#     def update_market(self, players):
#         """Update the market with new players."""
#         self.market.extend(players)
#         print(f"Market updated with {len(players)} new players.")


