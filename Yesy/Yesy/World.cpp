#include "World.h"
#include "Item.cpp"
#include "Monster.cpp"
#include "Quest.cpp"
#include "Location.cpp"
#include "Weapon.cpp"
#include "HealingPotion.cpp"
#include <iostream>
#include <vector>

using namespace std;
//using namespace N;

class World
{
public:
    //static const string WorldName;
    const string* WorldName = new string("Bjork");

    static vector<Item> Items;
    static vector<Monster> Monsters;
    static vector<Quest> Quests;
    static vector<Location*> Locations;



    static const int ITEM_ID_RUSTY_SWORD = 1;
    static const int ITEM_ID_RAT_TAIL = 2;
    static const int ITEM_ID_PIECE_OF_FUR = 3;
    static const int ITEM_ID_SNAKE_FANG = 4;
    static const int ITEM_ID_SNAKESKIN = 5;
    static const int ITEM_ID_CLUB = 6;
    static const int ITEM_ID_HEALING_POTION = 7;
    static const int ITEM_ID_SPIDER_FANG = 8;
    static const int ITEM_ID_SPIDER_SILK = 9;
    static const int ITEM_ID_ADVENTURER_PASS = 10;

    static const int MONSTER_ID_RAT = 1;
    static const int MONSTER_ID_SNAKE = 2;
    static const int MONSTER_ID_GIANT_SPIDER = 3;

    static const int QUEST_ID_CLEAR_ALCHEMIST_GARDEN = 1;
    static const int QUEST_ID_CLEAR_FARMERS_FIELD = 2;

    static const int LOCATION_ID_HOME = 1;
    static const int LOCATION_ID_TOWN_SQUARE = 2;
    static const int LOCATION_ID_GUARD_POST = 3;
    static const int LOCATION_ID_ALCHEMIST_HUT = 4;
    static const int LOCATION_ID_ALCHEMISTS_GARDEN = 5;
    static const int LOCATION_ID_FARMHOUSE = 6;
    static const int LOCATION_ID_FARM_FIELD = 7;
    static const int LOCATION_ID_BRIDGE = 8;
    static const int LOCATION_ID_SPIDER_FIELD = 9;

    World()
    {
        PopulateItems();
        PopulateMonsters();
        PopulateQuests();
        PopulateLocations();
    }

private:
    static void PopulateItems()
    {
        Items.push_back(Weapon(ITEM_ID_RUSTY_SWORD, "Rusty sword", "Rusty swords", 0, 5));
        Items.push_back(Item(ITEM_ID_RAT_TAIL, "Rat tail", "Rat tails"));
        Items.push_back(Item(ITEM_ID_PIECE_OF_FUR, "Piece of fur", "Pieces of fur"));
        Items.push_back(Item(ITEM_ID_SNAKE_FANG, "Snake fang", "Snake fangs"));
        Items.push_back(Item(ITEM_ID_SNAKESKIN, "Snakeskin", "Snakeskins"));
        Items.push_back(Weapon(ITEM_ID_CLUB, "Club", "Clubs", 3, 10));
        Items.push_back(HealingPotion(ITEM_ID_HEALING_POTION, "Healing potion", "Healing potions", 5));
        Items.push_back(Item(ITEM_ID_SPIDER_FANG, "Spider fang", "Spider fangs"));
        Items.push_back(Item(ITEM_ID_SPIDER_SILK, "Spider silk", "Spider silks"));
        Items.push_back(Item(ITEM_ID_ADVENTURER_PASS, "Adventurer pass", "Adventurer passes"));
    }

    static void PopulateMonsters()
    {
        Monster rat = Monster(MONSTER_ID_RAT, "Rat", 5, 3, 10, 3, 3);
        rat.LootTable.push_back(LootItem(ItemByID(ITEM_ID_RAT_TAIL), 75, false));
        rat.LootTable.push_back(LootItem(ItemByID(ITEM_ID_PIECE_OF_FUR), 75, true));

        Monster snake = Monster(MONSTER_ID_SNAKE, "Snake", 5, 3, 10, 3, 3);
        snake.LootTable.push_back(LootItem(ItemByID(ITEM_ID_SNAKE_FANG), 75, false));
        snake.LootTable.push_back(LootItem(ItemByID(ITEM_ID_SNAKESKIN), 75, true));
        //snake.LootTable.push_back( LootItem(ItemByID(ITEM_ID_CLUB), 75, true));

        Monster giantSpider = Monster(MONSTER_ID_GIANT_SPIDER, "Giant spider", 20, 5, 40, 10, 10);
        giantSpider.LootTable.push_back(LootItem(ItemByID(ITEM_ID_SPIDER_FANG), 75, true));
        giantSpider.LootTable.push_back(LootItem(ItemByID(ITEM_ID_SPIDER_SILK), 25, false));

        Monsters.push_back(rat);
        Monsters.push_back(snake);
        Monsters.push_back(giantSpider);
    }

    static void PopulateQuests()
    {
        Quest clearAlchemistGarden =
            Quest(
                QUEST_ID_CLEAR_ALCHEMIST_GARDEN,
                "Clear the alchemist's garden",
                "Kill rats in the alchemist's garden and bring back 3 rat tails. \nYou will receive a healing potion and 10 gold pieces.", 20, 10);

        clearAlchemistGarden.QuestCompletionItems.push_back(QuestCompletionItem(ItemByID(ITEM_ID_RAT_TAIL), 3));

        clearAlchemistGarden.RewardItem = ItemByID(ITEM_ID_HEALING_POTION);

        Quest clearFarmersField =
            Quest(
                QUEST_ID_CLEAR_FARMERS_FIELD,
                "Clear the farmer's field",
                "Kill snakes in the farmer's field and bring back 3 snake fangs. \nYou will receive an adventurer's pass and 20 gold pieces.", 20, 20);

        clearFarmersField.QuestCompletionItems.push_back(QuestCompletionItem(ItemByID(ITEM_ID_SNAKE_FANG), 3));

        clearFarmersField.RewardItem = ItemByID(ITEM_ID_ADVENTURER_PASS);

        Quests.push_back(clearAlchemistGarden);
        Quests.push_back(clearFarmersField);
    }

    static void PopulateLocations()
    {
        // Create each location
        Location* home = new Location(LOCATION_ID_HOME, "Home", "Your house. You really need to clean up the place.");

        Location* townSquare = new Location(LOCATION_ID_TOWN_SQUARE, "Town square", "You see a fountain.");

        Location* alchemistHut = new Location(LOCATION_ID_ALCHEMIST_HUT, "Alchemist's hut", "There are many strange plants on the shelves.");
        alchemistHut -> QuestAvailableHere = QuestByID(QUEST_ID_CLEAR_ALCHEMIST_GARDEN);

        Location* alchemistsGarden = new Location(LOCATION_ID_ALCHEMISTS_GARDEN, "Alchemist's garden", "Many plants are growing here.");
        alchemistsGarden -> MonsterLivingHere = MonsterByID(MONSTER_ID_RAT);

        Location* farmhouse = new Location(LOCATION_ID_FARMHOUSE, "Farmhouse", "There is a small farmhouse, with a farmer in front.");
        farmhouse -> QuestAvailableHere = QuestByID(QUEST_ID_CLEAR_FARMERS_FIELD);

        Location* farmersField = new Location(LOCATION_ID_FARM_FIELD, "Farmer's field", "You see rows of vegetables growing here.");
        farmersField -> MonsterLivingHere = MonsterByID(MONSTER_ID_SNAKE);

        Location* guardPost = new Location(LOCATION_ID_GUARD_POST, "Guard post", "There is a large, tough-looking guard here.", ItemByID(ITEM_ID_ADVENTURER_PASS));

        Location* bridge = new Location(LOCATION_ID_BRIDGE, "Bridge", "A stone bridge crosses a wide river.");

        Location* spiderField = new Location(LOCATION_ID_SPIDER_FIELD, "Forest", "You see spider webs covering covering the trees in this forest.");
        spiderField -> MonsterLivingHere = MonsterByID(MONSTER_ID_GIANT_SPIDER);

        // Link the locations together
        home -> LocationToNorth = townSquare;

        townSquare -> LocationToNorth = alchemistHut;
        townSquare -> LocationToSouth = home;
        townSquare -> LocationToEast = guardPost;
        townSquare -> LocationToWest = farmhouse;

        farmhouse -> LocationToEast = townSquare;
        farmhouse -> LocationToWest = farmersField;

        farmersField -> LocationToEast = farmhouse;

        alchemistHut -> LocationToSouth = townSquare;
        alchemistHut -> LocationToNorth = alchemistsGarden;

        alchemistsGarden -> LocationToSouth = alchemistHut;

        guardPost -> LocationToEast = bridge;
        guardPost -> LocationToWest = townSquare;

        bridge -> LocationToWest = guardPost;
        bridge -> LocationToEast = spiderField;

        spiderField -> LocationToWest = bridge;

        // Add the locations to the static list
        Locations.push_back(home);
        Locations.push_back(townSquare);
        Locations.push_back(guardPost);
        Locations.push_back(alchemistHut);
        Locations.push_back(alchemistsGarden);
        Locations.push_back(farmhouse);
        Locations.push_back(farmersField);
        Locations.push_back(bridge);
        Locations.push_back(spiderField);
    }

public:
    static Item* ItemByID(int id)
    {
        for(Item item : Items)
        {
            if (item.ID == id)
            {
                return &item;
            }
        }

        return;
    }

    static Monster* MonsterByID(int id)
    {
        for(Monster monster : Monsters)
        {
            if (monster.ID == id)
            {
                return &monster;
            }
        }

        return;
    }

    static Quest* QuestByID(int id)
    {
        for(Quest quest : Quests)
        {
            if (quest.ID == id)
            {
                return &quest;
            }
        }

        return;
    }

    static Location* LocationByID(int id)
    {
        for(Location* location : Locations)
        {
            if (location -> ID == id)
            {
                return location;
            }
        }

        return;
    }

    static void ListLocations()
    {
        cout << "These are locations in the World:\n";
        for(Location* location : Locations)
        {
            cout << "\t" + location -> Name + "\n";
        }
    }

    static void ListItems()
    {
        cout << "These are items in the World:\n";
        for(Item item : Items)
        {
            cout << "\t" + item.Name + "\n";
        }
    }

    static void ListQuests()
    {
        cout << "These are quests in the World:\n";
        for(Quest item : Quests)
        {
            cout << "\t" + item.Name + "\n";
        }
    }

    static void ListMonsters()
    {
        cout << "These are monsters in the World:\n";
        for(Monster item : Monsters)
        {
            cout << "\t" + item.Name + "\n";
        }
    }

};

