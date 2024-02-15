#include "Item.cpp"
#include "Quest.cpp"
#include "Monster.cpp"
#include <iostream>

using namespace std;

class Location
{
public:
    int ID;
    string Name;
    string Description;
    Item* ItemRequiredToEnter;
    Quest* QuestAvailableHere;
    Monster* MonsterLivingHere;
    Location* LocationToNorth = nullptr;
    Location* LocationToEast = nullptr;
    Location* LocationToSouth = nullptr;
    Location* LocationToWest = nullptr;

    //Constructor
    Location(int iD, string name, string description,
        Item* itemRequiredToEnter = nullptr, Quest* questAvailableHere = nullptr,
        Monster* monsterLivingHere = nullptr
    )
    {
        ID = iD;
        Name = name;
        Description = description;
        ItemRequiredToEnter = itemRequiredToEnter;
    };
    Location() = default;
};