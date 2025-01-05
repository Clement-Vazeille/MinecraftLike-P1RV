#pragma once
#include <glm/glm.hpp>
#include <array>
#include <string>
#include "../Maths/Vector3I.h"
using namespace std;

//Classe representant un block indivuduel, il contient ses textures et sa position, en general on utilise des classes qui heritent de block et qui ont des textures deja definies lors de l'initialisation
//Ces classes filles sont definies dans le Dossier SpecificBlocks
class Block
{
protected:
    Vector3I position;
    array<string,6> textures;
    //les textures sont rangees dans l'ordre arriere avant gauche droite dessous dessus
public:
    Block();
    Block(int i, int j, int k);
    Block(const Vector3I& p);

    Vector3I getPosition(void);
    string getTexturei(int i);
    virtual bool hasCollisions(void) const;
    virtual bool isLight(void) const;
};

