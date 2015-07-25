#include "Entity.h"
#include <stdlib.h>


Entity::Entity()
{
}


void Entity::Create(int count_in)
{
	count = count_in;
	xpos = (int*) malloc(count * sizeof(int));
	ypos = (int*) malloc(count * sizeof(int));
	type = (unsigned char*) malloc(count);
}

void Entity::Destroy()
{
	free(xpos);
	free(ypos);
	free(type);
}

void Entity::Init(int pos, int x_pos, int y_pos, unsigned char type_input)
{
	xpos[pos] = x_pos;
	ypos[pos] = y_pos;
	type[pos] = type_input;
}


