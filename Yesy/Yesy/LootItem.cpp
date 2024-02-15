#include "Item.cpp"
class LootItem
{
public:
    Item* Details;
    int DropPercentage;
    bool IsDefaultItem;

    LootItem(Item* details, int dropPercentage, bool isDefaultItem)
    {
        Details = details;
        DropPercentage = dropPercentage;
        IsDefaultItem = isDefaultItem;
    };
    LootItem() = default;
};