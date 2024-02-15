#pragma once
#include "LivingCreature.cpp"
#include "Location.cpp"
#include "InventoryItem.cpp"
#include "PlayerQuest.cpp"
#include "Weapon.cpp"
#include "GameEngine.cpp"
#include "RandomNumberGenerator.cpp"
#include "Source.cpp"
#include <iostream>
#include <vector>

using namespace std;

class Player : public LivingCreature
{
public:
    string Name;
    int Gold;
    int ExperiencePoints;
    int Level;
    Location* CurrentLocation;
    vector<InventoryItem>* Inventory;
    vector<PlayerQuest>* Quests;
    Weapon CurrentWeapon;
    vector<Weapon>* Weapons = nullptr;
    //vector<Weapon> Weapons = new List<Weapon>();
    Player(string name, int currentHitPoints,
        int maximumHitPoints, int gold, int experiencePoints,
        int level)
    {
        Name = name;
        Gold = gold;
        ExperiencePoints = experiencePoints;
        Level = level;
        Inventory = nullptr;
        Quests = nullptr;
    }

    Player() = default;
    void MoveTo(Location* loc)
    {
        //Check to make sure player has any required items
        if (loc -> ItemRequiredToEnter != nullptr)
        {
            //Check for the item
            bool playerHasRequiredItem = false;
            for(InventoryItem ii : this -> Inventory)
            {
                if (ii.Details -> ID == loc -> ItemRequiredToEnter -> ID)
                {
                    playerHasRequiredItem = true;
                    break;
                }
            }
            if (!playerHasRequiredItem)
            {
                cout << "You must have a " + loc -> ItemRequiredToEnter -> Name +" to enter this location.\n";
                return;
            }
        }
        CurrentHitPoints = MaximumHitPoints;
        CurrentLocation = loc;
        GameEngine::QuestProcessor(this, loc);
        GameEngine::MonsterProcessor(this, loc);
    }
    void MoveNorth()
    {
        if (CurrentLocation -> LocationToNorth != nullptr)
        {
            MoveTo(CurrentLocation -> LocationToNorth);
            Source.DisplayCurrentLocation();
        }
        else
        {
            cout << "You cannot move north.\n";
        }
    }
    void MoveEast()
    {
        if (CurrentLocation -> LocationToEast != nullptr)
        {
            MoveTo(CurrentLocation -> LocationToEast);
            Source::DisplayCurrentLocation();
        }
        else
        {
            cout << "You cannot move east.\n";
        }
    }
    void MoveSouth()
    {
        if (CurrentLocation -> LocationToSouth != nullptr)
        {
            MoveTo(CurrentLocation -> LocationToSouth);
            Source::DisplayCurrentLocation();
        }
        else
        {
            cout << "You cannot move south.\n";
        }
    }
    void MoveWest()
    {
        if (CurrentLocation -> LocationToWest != nullptr)
        {
            MoveTo(CurrentLocation -> LocationToWest);
            Source::DisplayCurrentLocation();
        }
        else
        {
            cout << "You cannot move west.\n";
        }
    }
    // ////////////////////////////////////////////
    // Quest Work
    // ////////////////////////////////////////////
    bool HasThisQuest(Quest* quest)
    {
        for(PlayerQuest playerQuest : Quests)
        {
            if (playerQuest.Details -> ID == quest -> ID)
            {
                return true;
            }
        }

        return false;
    }

    bool CompletedThisQuest(Quest* quest)
    {
        for(PlayerQuest playerQuest : Quests)
        {
            if (playerQuest.Details -> ID == quest -> ID)
            {
                return playerQuest.IsCompleted;
            }
        }

        return false;
    }

    bool HasAllQuestCompletionItems(Quest* quest)
    {
        // See if the player has all the items needed to complete the quest here
        for(QuestCompletionItem qci : quest -> QuestCompletionItems)
        {
            bool foundItemInPlayersInventory = false;

            // Check each item in the player's inventory, to see if they have it, and enough of it
            for(InventoryItem ii : Inventory)
            {
                if (ii.Details -> ID == qci.Details -> ID) // The player has the item in their inventory
                {
                    foundItemInPlayersInventory = true;

                    if (ii.Quantity < qci.Quantity) // The player does not have enough of this item to complete the quest
                    {
                        return false;
                    }
                }
            }

            // The player does not have any of this quest completion item in their inventory
            if (!foundItemInPlayersInventory)
            {
                return false;
            }
        }

        // If we got here, then the player must have all the required items, and enough of them, to complete the quest.
        return true;
    }

    void RemoveQuestCompletionItems(Quest* quest)
    {
        for(QuestCompletionItem qci : quest -> QuestCompletionItems)
        {
            for(InventoryItem ii : Inventory)
            {
                if (ii.Details -> ID == qci.Details -> ID)
                {
                    // Subtract the quantity from the player's inventory that was needed to complete the quest
                    ii.Quantity -= qci.Quantity;
                    break;
                }
            }
        }
    }


    void AddItemToInventory(Item* itemToAdd)
    {
        for(InventoryItem ii : Inventory)
        {
            if (ii.Details -> ID == itemToAdd -> ID)
            {
                // They have the item in their inventory, so increase the quantity by one
                ii.Quantity++;

                return; // We added the item, and are done, so get out of this function
            }
        }

        // They didn't have the item, so add it to their inventory, with a quantity of 1
        Inventory -> push_back(InventoryItem(itemToAdd, 1));
    }

    void MarkQuestCompleted(Quest* quest)
    {
        // Find the quest in the player's quest list
        for(PlayerQuest pq : Quests)
        {
            if (pq.Details -> ID == quest -> ID)
            {
                // Mark it as completed
                pq.IsCompleted = true;

                return; // We found the quest, and marked it complete, so get out of this function
            }
        }
    }
    // ////////////////////Weapon work
    void UseWeapon(Weapon weapon)
    {
        Monster* _currentMonster = GameEngine::_currentMonster;
        Weapon currentWeapon = weapon;
        string fightMessage = "";

        // Determine the amount of damage to do to the monster
        int damageToMonster = RandomNumberGenerator::NumberBetween(currentWeapon.MinimumDamage, currentWeapon.MaximumDamage);

        // Apply the damage to the monster's CurrentHitPoints
        _currentMonster -> CurrentHitPoints -= damageToMonster;

        // Display message
        fightMessage += "You hit the " + _currentMonster -> Name + (" for " + damageToMonster) + " points.\n";
        cout << fightMessage;

        // Check if the monster is dead
        if (_currentMonster -> CurrentHitPoints <= 0)
        {
            // Monster is dead
            fightMessage += "\n";
            fightMessage += "You defeated the " + _currentMonster -> Name + "\n";

            // Give player experience points for killing the monster
            ExperiencePoints += _currentMonster -> RewardExperiencePoints;
            string thingy = " experience points\n";
            fightMessage += "You receive " + _currentMonster -> RewardExperiencePoints + thingy;

            // Give player gold for killing the monster 
            Gold += _currentMonster -> RewardGold;
            thingy = " gold\n";
            fightMessage += "You receive " + _currentMonster -> RewardGold + thingy;


            // Get random loot items from the monster
            vector<InventoryItem> lootedItems;

            // Add items to the lootedItems list, comparing a random number to the drop percentage
            for(LootItem lootItem : _currentMonster -> LootTable)
            {
                if (RandomNumberGenerator::NumberBetween(1, 100) <= lootItem.DropPercentage)
                {
                    lootedItems.push_back(InventoryItem(lootItem.Details, 1));
                }
            }

            // If no items were randomly selected, then add the default loot item(s).
            if (lootedItems.Count == 0)
            {
                for(LootItem lootItem : _currentMonster -> LootTable)
                {
                    if (lootItem.IsDefaultItem)
                    {
                        lootedItems.push_back(InventoryItem(lootItem.Details, 1));
                    }
                }
            }

            // Add the looted items to the player's inventory
            for(InventoryItem inventoryItem : lootedItems)
            {
                AddItemToInventory(inventoryItem.Details);

                if (inventoryItem.Quantity == 1)
                {
                    fightMessage += "You loot " + inventoryItem.Quantity + (" " + inventoryItem.Details -> Name) + "\n";
                }
                else
                {
                    fightMessage += "You loot " + inventoryItem.Quantity + (" " + inventoryItem.Details -> NamePlural) + "\n";
                }
            }



            // Add a blank line to the messages box, just for appearance.
            fightMessage += "\n";
            cout << fightMessage;

            // Move player to current location (to heal player and create a new monster to fight)
            MoveTo(CurrentLocation);
        }
        else
        {
            // Monster is still alive

            // Determine the amount of damage the monster does to the player
            int damageToPlayer = RandomNumberGenerator::NumberBetween(0, _currentMonster -> MaximumDamage);

            // Display message
            fightMessage += "The " + _currentMonster -> Name + " did " + (damageToPlayer + " points of damage.\n");

            // Subtract damage from player
            CurrentHitPoints -= damageToPlayer;

            cout << fightMessage;

            if (CurrentHitPoints <= 0)
            {
                // Display message
                fightMessage += "The " + _currentMonster -> Name + " killed you.\n";
                cout << fightMessage;

                // Move player to "Home"
                MoveTo(World::LocationByID(World::LOCATION_ID_HOME));
            }
        }
    } //UserWeapon
    void UpdateWeapons()
    {
        Weapons -> Clear();
        for(InventoryItem inventoryItem : this -> Inventory)
        {
            if (inventoryItem.Details is Weapon)
            {
                if (inventoryItem.Quantity > 0)
                {
                    Weapons -> push_back((Weapon*)inventoryItem.Details);
                }
            }
        }
    }
}; // class Player