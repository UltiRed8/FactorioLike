#pragma once
#include "Element.h"
#include "Colors.h"
#include <string>
#include <map>
#include "Item.h"

using namespace std;

enum NodeRarity
{
    NR_NONE, NR_COMMUN = 30, NR_RARE = 45, NR_EPIC = 70, NR_LEGENDARY = 100
};

class RessourceNode : public Element {
    NodeRarity rarity;
    Ressource type;
    string toolIDToCollect;
    bool isAvailable;

public:
    Ressource GetType() const {
        return type;
    }
    string GetStringNodeRarity() const {
        if (rarity == NR_NONE) return "Aucune";
        else if (rarity == NR_COMMUN) return "Commun";
        else if (rarity == NR_RARE) return "Rare";
        else if (rarity == NR_EPIC) return "Epic";
        else if (rarity == NR_LEGENDARY) return "Légendaire";
        else return "";
    }
    string GetToolsIDToCollect() const
    {
        return toolIDToCollect;
    }
    bool GetIsAvailable() const
    {
        return isAvailable;
    }

    NodeRarity GetRarity() const
    {
        return rarity;
    }

private:
    void UpdateSign();

public:
    RessourceNode(const NodeRarity& _rarity, const string& _type);
};