#pragma once
#include <glm/glm.hpp>
#include <array>
#include <string>
#include "../Maths/Vector3I.h"
using namespace std;

//Classe représentant un block indivuduel, il contient ses textures et sa position, en général on utilise des classes qui héritent de block et qui ont des textures déjà définies lors de l'initialisation
//Ces classes filles sont définies dans le Dossier SpecificBlocks
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

