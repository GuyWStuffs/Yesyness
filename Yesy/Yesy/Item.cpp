#include <iostream>
using namespace std;
class Item
{
public:
    int ID = {};
    string Name;
    string NamePlural;
    Item(int iD, string name, string namePlural)
    {
        ID = iD;
        Name = name;
        NamePlural = namePlural;
    }
    Item() = default;
};