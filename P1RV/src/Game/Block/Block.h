#pragma once
#include <glm/glm.hpp>
#include <array>
#include <string>
#include "../Maths/Vector3I.h"
using namespace std;

//Classe repr�sentant un block indivuduel, il contient ses textures et sa position, en g�n�ral on utilise des classes qui h�ritent de block et qui ont des textures d�j� d�finies lors de l'initialisation
//Ces classes filles sont d�finies dans le Dossier SpecificBlocks
class Block
{
protected:
    Vector3I position;
    array<string,6> textures;
    //les textures sont rang�es dans l'ordre arri�re avant gauche droite dessous dessus
public:
    Block();
    Block(int i, int j, int k);
    Block(const Vector3I& p);

    Vector3I getPosition(void);
    string getTexturei(int i);
};

