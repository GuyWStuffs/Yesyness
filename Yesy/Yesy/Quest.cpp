#include "Item.cpp"
#include "QuestCompletionItem.cpp"
#include <iostream>
#include <vector>

using namespace std;

class Quest
{
public:
    int ID;
    string Name;
    string Description;
    int RewardExperiencePoints;
    int RewardGold;
    Item* RewardItem;
    vector<QuestCompletionItem> QuestCompletionItems;

    Quest(int iD, string name, string description,
        int rewardExperiencePoints, int rewardGold)
    {
        ID = iD;
        Name = name;
        Description = description;
        RewardExperiencePoints = rewardExperiencePoints;
        RewardGold = rewardGold;
        //QuestCompletionItems = new vector<QuestCompletionItem>;
    }
    Quest() = default;
};