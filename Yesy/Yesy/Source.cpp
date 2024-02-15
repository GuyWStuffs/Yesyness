#pragma once
#include "Player.cpp"
#include "GameEngine.cpp"
#include "World.cpp"
#include <iostream>


using namespace std;

static Player _player("Fred the Fearless", 10, 10, 20, 0, 1);

class Source
{
public:
    static void ParseInput(string input)
    {
        if (input.find("help"))
        {
            cout << "Help is coming later... stay tuned.\n";
        }
        else if (input.find("look"))
        //else if (input.Contains("look"))
        {
            DisplayCurrentLocation();
        }
        else if (input.find("north") || input == "n")
        {
            _player.MoveNorth();
        }
        else if (input.find("east") || input == "e")
        {
            _player.MoveEast();
        }
        else if (input.find("south") || input == "s")
        {
            _player.MoveSouth();
        }
        else if (input.find("west") || input == "w")
        {
            _player.MoveWest();
        }
        else if (input.find("debug"))
        {
            GameEngine::DebugInfo();
        }
        else if (input == "inventory" || input == "i")
        {
            cout << "\nCurrent Inventory:\n";
            for(InventoryItem invItem : _player.Inventory)
            {
                cout << "\t" << invItem.Details -> Name << " : " << invItem.Quantity << "\n";
            }
        }
        else if (input == "stats")
        {
            cout << "\nStats for " << _player.Name << "\n";
            cout << "\tCurrent HP: \t" << _player.CurrentHitPoints << "\n";
            cout << "\tMaximum HP: \t" << _player.MaximumHitPoints << "\n";
            cout << "\tXP:\t\t" << _player.ExperiencePoints << "\n";
            cout << "\tLevel:\t\t" << _player.Level << "\n";
            cout << "\tGold:\t\t" << _player.Gold << "\n";
        }
        else if (input == "quests")
        {
            if (_player.Quests.Count == 0)
            {
                cout << "You do not have any quests.\n";
            }
            else
            {
                for(PlayerQuest playerQuest : _player.Quests)
                {
                    cout << playerQuest.Details -> Name << ": " <<
                        playerQuest.IsCompleted ? "Completed\n" : "Incomplete\n";
                }
            }
        }
        else if (input.find("attack") || input == "a")
        {
            if (_player.CurrentLocation.MonsterLivingHere == nullptr)
            {
                cout << "There is nothing here to attack.\n";
            }
            else
            {
                if (_player.CurrentWeapon == nullptr)
                {
                    cout << "You are not equipped with a weapon.";
                }
                else
                {
                    _player.UseWeapon(_player.CurrentWeapon);
                }
            }
        }
        else if (input.StartsWith("equip "))
        {
            _player.UpdateWeapons();
            string inputWeaponName = input.Substring(6).Trim();
            if (string.IsNullOrEmpty(inputWeaponName))
            {
                cout << "You must enter the name of the weapon to equip.";
            }
            else
            {
                Weapon weaponToEquip = _player.Weapons.SingleOrDefault(x = > x.Name.ToLower() == inputWeaponName
                    || x.NamePlural.ToLower() == inputWeaponName);
                if (weaponToEquip == nullptr)
                {
                    cout << "You do not have the weapon " << inputWeaponName << "\n";
                }
                else
                {
                    _player.CurrentWeapon = weaponToEquip;
                    cout << "You equip your " << _player.CurrentWeapon.Name << "\n";
                }
            }
        }
        else if (input == "weapons")
        {
            _player.UpdateWeapons();
            cout << "List of Weapons:\n";
            for(Weapon w : _player.Weapons)
            {
                cout << "\t" << w.Name << "\n";
            }
        }
        else
        {
            cout << "I don't understand. Sorry!\n";
        }
    }//ParseInput
    static void DisplayCurrentLocation()
    {
        cout << "\nYou are at: " << _player.CurrentLocation.Name << "\n";
        if (_player.CurrentLocation.Description != "")
        {
            cout << "\t" << _player.CurrentLocation.Description << "\n\n";
        }
    }
};

void main()
{
    GameEngine::Initialize();
    _player.MoveTo(World::LocationByID(World::LOCATION_ID_HOME));
    InventoryItem sword = InventoryItem(World::ItemByID(World::ITEM_ID_RUSTY_SWORD), 1);
    InventoryItem club = InventoryItem(World::ItemByID(World::ITEM_ID_CLUB), 1);
    _player.Inventory->push_back(sword);
    //_player.Inventory.Add(club);
    //InventoryItem aPass = new InventoryItem(World.ItemByID(World.ITEM_ID_ADVENTURER_PASS), 1);
    //_player.Inventory.Add(aPass);
    while (true)
    {
        cout << "> \n";
        string userInput;
        cin >> userInput;
        if (string.IsNullOrWhiteSpace(userInput))
        {
            continue;
        }
        string cleanedInput = userInput.ToLower();
        if (cleanedInput == "exit")
        {
            break;
        }
        ParseInput(cleanedInput);
    } //while
}; //Main