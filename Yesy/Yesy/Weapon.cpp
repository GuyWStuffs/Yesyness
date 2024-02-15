#include "Item.cpp"

class Weapon : public Item
{
public:
    int MaximumDamage;
    int MinimumDamage;
    Weapon(int id, string name, string namePlural, int minimumDamage, int maximumDamage)
    {
        MaximumDamage = maximumDamage;
        MinimumDamage = minimumDamage;
    }
    Weapon() = default;
};