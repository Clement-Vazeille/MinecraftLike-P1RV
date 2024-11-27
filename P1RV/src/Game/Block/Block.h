#pragma once
#include <glm/glm.hpp>
#include <array>
#include <string>
#include "../Maths/Vector3I.h"
using namespace std;

class Block
{
protected:
    Vector3I position;
    array<string,6> textures;
    //les textures sont rangées dans l'ordre arrière avant gauche droite dessous dessus
public:
    Block();
    Block(int i, int j, int k);
    Block(const Vector3I& p);

    Vector3I getPosition(void);
    string getTexturei(int i);
};

