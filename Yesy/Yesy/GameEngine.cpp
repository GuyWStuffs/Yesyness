#pragma once
#include "World.cpp"
#include "PlayerQuest.cpp"
#include "Player.cpp"
#include <iostream>

using namespace std;

class GameEngine
{
public:
    static string Version = "0.0.5";
    static Monster* _currentMonster;

    static void Initialize()
    {
        cout << "Hello, world!\n";
        cout << "Initializing Game Engine Version " + Version + "\n";
        cout << "\n\nWelcome to the World of " << World::WorldName << "\n";
        cout << "\n";
    }

    static void DebugInfo()
    {
        World::ListLocations();
        World::ListItems();
        World::ListMonsters();
        World::ListQuests();
        if (_currentMonster != nullptr)
        {
            cout << "Current Monster:" << _currentMonster -> Name;
        }
        else
        {
            cout << "No current monster./n";
        }
    }

    static void QuestProcessor(Player* _player, Location* newLocation)
    {
        string questMessage;
        // Does the location have a quest?
        if (newLocation -> QuestAvailableHere != nullptr)
        {
            // See if the player already has the quest, and if they've completed it
            bool playerAlreadyHasQuest = _player -> HasThisQuest(newLocation -> QuestAvailableHere);
            bool playerAlreadyCompletedQuest = _player -> CompletedThisQuest(newLocation -> QuestAvailableHere);
    
            // See if the player already has the quest
            if (playerAlreadyHasQuest)
            {
                // If the player has not completed the quest yet
                if (!playerAlreadyCompletedQuest)
                {
                    // See if the player has all the items needed to complete the quest
                    bool playerHasAllItemsToCompleteQuest = _player -> HasAllQuestCompletionItems(newLocation -> QuestAvailableHere);
    
                    // The player has all items required to complete the quest
                    if (playerHasAllItemsToCompleteQuest)
                    {
                        // Display message
                        questMessage = "\n";
                        questMessage += "You complete the '" + newLocation -> QuestAvailableHere -> Name + "' quest.\n";
    
                        // Remove quest items from inventory
                        _player -> RemoveQuestCompletionItems(newLocation -> QuestAvailableHere);
    
                        // Give quest rewards
                        questMessage += "You receive: \n";
                        questMessage += newLocation -> QuestAvailableHere -> RewardExperiencePoints + " experience points\n";
                        questMessage += newLocation -> QuestAvailableHere -> RewardGold + " gold\n";
                        questMessage += newLocation -> QuestAvailableHere -> RewardItem -> Name + "\n";
                        questMessage += "\n";
                        cout << questMessage;
    
                        _player -> ExperiencePoints += newLocation -> QuestAvailableHere -> RewardExperiencePoints;
                        _player -> Gold += newLocation -> QuestAvailableHere -> RewardGold;
    
                        // Add the reward item to the player's inventory
                        _player -> AddItemToInventory(newLocation -> QuestAvailableHere -> RewardItem);
    
                        // Mark the quest as completed
                        _player -> MarkQuestCompleted(newLocation -> QuestAvailableHere);
                    }
                }
            }
            else
            {
                // The player does not already have the quest
    
                // Display the messages
                questMessage = "You receive the " + newLocation -> QuestAvailableHere -> Name + " quest.\n";
                questMessage += newLocation -> QuestAvailableHere -> Description + "\n";
                questMessage += "To complete it, return with:\n";
                for(QuestCompletionItem qci : newLocation -> QuestAvailableHere -> QuestCompletionItems)
                {
                    if (qci.Quantity == 1)
                    {
                        questMessage += qci.Quantity + " " + qci.Details -> Name + "\n";
                    }
                    else
                    {
                        questMessage += qci.Quantity + " " + qci.Details -> NamePlural + "\n";
                    }
                }
                questMessage += "\n";
                cout << questMessage;
    
                // Add the quest to the player's quest list
                _player -> Quests -> push_back(PlayerQuest(newLocation -> QuestAvailableHere, false));
            }
        }
    
    } //QuestProcessor

    static void MonsterProcessor(Player* _player, Location* newLocation)
    {
        string monsterMessage = "";
        if (newLocation -> MonsterLivingHere != nullptr)
        {
            monsterMessage += "You see a " + newLocation -> MonsterLivingHere -> Name + "\n";
            cout << monsterMessage;
            //Make a new monster
            Monster* standardMonster = World::MonsterByID(newLocation -> MonsterLivingHere -> ID);
            _currentMonster = new Monster(standardMonster -> ID, standardMonster -> Name, standardMonster -> MaximumDamage, standardMonster -> RewardExperiencePoints,
                standardMonster -> RewardGold, standardMonster -> CurrentHitPoints, standardMonster -> MaximumHitPoints);
            for(LootItem lootItem : standardMonster -> LootTable)
            {
                _currentMonster -> LootTable.push_back(lootItem);
            }
        }
        else
        {
            _currentMonster = nullptr;
        }
    }//MonsterProcessor
};