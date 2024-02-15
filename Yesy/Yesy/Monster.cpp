#include "LivingCreature.cpp"
#include "LootItem.cpp"
#include <iostream>
#include <vector>

using namespace std;

class Monster : public LivingCreature
{
public:
    int ID;
    string Name;
    int MaximumDamage;
    int RewardExperiencePoints;
    int RewardGold;
    vector<LootItem> LootTable;

    Monster(int iD, string name, int maximumDamage,
        int rewardExperiencePoints, int rewardGold,
        int currentHitPoints, int maximumHitPoints)
    {
        ID = iD;
        Name = name;
        MaximumDamage = maximumDamage;
        RewardExperiencePoints = rewardExperiencePoints;
        RewardGold = rewardGold;
        CurrentHitPoints = currentHitPoints;
        MaximumDamage = maximumHitPoints;
        //LootTable = new List<LootItem>();
    }
    Monster() = default;
};