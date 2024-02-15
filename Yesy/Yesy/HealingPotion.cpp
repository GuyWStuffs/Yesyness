#include "Item.cpp"

class HealingPotion : public Item
{
public:
    int AmountToHeal;
    HealingPotion(int id, string name, string namePlural, int amountToHeal)
    {
        ID = id;
        Name = name;
        NamePlural = namePlural;
        AmountToHeal = amountToHeal;
    }
    HealingPotion() = default;
};

