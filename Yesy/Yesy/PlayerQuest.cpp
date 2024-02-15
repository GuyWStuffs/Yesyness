#include "Quest.cpp"
class PlayerQuest
{
public:
    Quest* Details;
    bool IsCompleted;

    PlayerQuest(Quest* details, bool isCompleted)
    {
        Details = details;
        IsCompleted = isCompleted;
    }
};