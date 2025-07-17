#include "Character.h"

Character :: Character(Vector2 startPos): position(startPos) {}

Character :: ~Character(){}

Vector2 Character :: getPosition(){
    return position;
}