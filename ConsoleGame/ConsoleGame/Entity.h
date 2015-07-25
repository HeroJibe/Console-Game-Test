#pragma once
class Entity
{
public:
	Entity();
	void Destroy();
	void Create(int count);
	void Init(int pos, int x_pos, int y_pos, unsigned char type_input);

	int count;
	int *xpos;
	int *ypos;
	unsigned char *type;
};

