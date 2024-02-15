#include "Item.cpp"
class InventoryItem
{
public:
    Item* Details;
    int Quantity;
    InventoryItem(Item* details, int quantity)
    {
        Details = details;
        Quantity = quantity;
    }
    InventoryItem() = default;
};