#include "Item.cpp"
class QuestCompletionItem
{
public:
    Item* Details;
    int Quantity;

    QuestCompletionItem(Item* details, int quantity)
    {
        Details = details;
        Quantity = quantity;
    }
};