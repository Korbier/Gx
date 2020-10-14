#pragma once

#include <vector>
#include <list>

#include "SDL.h"
#include "display/map/Map.h"

struct Node {
	Map* map;
	bool visited;
	bool obstacle;
	float g; //Global score
	float f; //Local score
	int x;
	int y;
	std::vector<Node*> neighbours;
	Node* parent;
};

class Pathfinder {
public:
	Pathfinder(Map* map);
	void init();
	void reset();
	Node* find( SDL_Point start, SDL_Point end );
	static inline float h(Node* a, Node* b) { return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y)); }
private:
	Map* map;
	Node* grid;
};
