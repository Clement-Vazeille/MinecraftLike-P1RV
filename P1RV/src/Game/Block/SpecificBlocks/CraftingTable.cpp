#include "CraftingTable.h"

CraftingTable::CraftingTable() : CraftingTable(0,0,0)
{
}

CraftingTable::CraftingTable(int i, int j, int k) : Block(i,j,k)
{
	textures.at(0) = "Assets/Block/crafting_Table_side.png";  //arrière
	textures.at(1) = "Assets/Block/crafting_Table_front.png"; //devant
	textures.at(2) = "Assets/Block/crafting_Table_front.png"; //gauche
	textures.at(3) = "Assets/Block/crafting_Table_side.png";  //droit
	textures.at(4) = "Assets/Block/crafting_Table_top.png";   //bas
	textures.at(5) = "Assets/Block/crafting_Table_top.png";   //haut
}

CraftingTable::CraftingTable(const Vector3I& p) : CraftingTable(p.getX(), p.getY(), p.getZ())
{
}
