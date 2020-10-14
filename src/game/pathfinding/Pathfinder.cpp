#include "pathfinder.h"

Pathfinder::Pathfinder(Map* map)
{
	this->map  = map;
	this->grid = nullptr;
}

void Pathfinder::init()
{

	this->grid = new Node[this->map->getWidth() * this->map->getHeight()];

	for (int y = 0; y < this->map->getHeight(); y++) {
		for (int x = 0; x < this->map->getWidth(); x++)
		{
			int index = y * this->map->getWidth() + x;
			this->grid[index].x = x;
			this->grid[index].y = y;
			this->grid[index].obstacle = this->map->getTileAt(x, y)->getReference()->isSolid();
			this->grid[index].visited = false;
			this->grid[index].parent = nullptr;
		}
	}

	for (int y = 0; y < this->map->getHeight(); y++) {
		for (int x = 0; x < this->map->getWidth(); x++)
		{
			int index = y * this->map->getWidth() + x;
			if (x > 0)                          this->grid[index].neighbours.push_back(&this->grid[y * this->map->getWidth() + (x - 1)]);
			if (x < this->map->getWidth() - 1)  this->grid[index].neighbours.push_back(&this->grid[y * this->map->getWidth() + (x + 1)]);
			if (y > 0)                          this->grid[index].neighbours.push_back(&this->grid[(y - 1) * this->map->getWidth() + x]);
			if (y < this->map->getHeight() - 1) this->grid[index].neighbours.push_back(&this->grid[(y + 1) * this->map->getWidth() + x]);
		}
	}

}

void Pathfinder::reset()
{
	for (int y = 0; y < this->map->getHeight(); y++) {
		for (int x = 0; x < this->map->getWidth(); x++) {
			int index = y * this->map->getWidth() + x;
			this->grid[index].visited = false;
			this->grid[index].parent = nullptr;
			this->grid[index].f = INFINITY;
			this->grid[index].g = INFINITY;
		}
	}
}

Node* Pathfinder::find(SDL_Point pStart, SDL_Point pGoal)
{
	Node* start = &this->grid[pStart.y * this->map->getWidth() + pStart.x];
	Node* goal  = &this->grid[pGoal.y * this->map->getWidth() + pGoal.x];

	Node* curr = start;
	start->f = 0.0f;
	start->g = h(start, goal);

	std::list<Node*> notTestedNodes;
	notTestedNodes.push_back(start);

	// If the list contains nodes, there may still be better paths
		// It will also stop when we reach the target - while there may still be a better path
	while (!notTestedNodes.empty() && curr != goal)
	{
		
		// Ascending order sort so the lowest is first
		notTestedNodes.sort([](const Node* a, const Node* b) { return a->g < b->g; });

		// Front of the list is potentilay the lowest distance node
		// Also remove the already visited ones that may end up in the list
		while (!notTestedNodes.empty() && notTestedNodes.front()->visited) {
			notTestedNodes.pop_front(); // the only spot where already visted nodes are removed !!!!!
		}

		// End the algorithm if the list is empty
		if (notTestedNodes.empty())
			break;

		curr = notTestedNodes.front();
		curr->visited = true;

		// Check each of the current node neighbours
		for (auto neighbour : curr->neighbours)
		{
			// If node was not visited before and is not an obstacle
			if (!neighbour->visited && !neighbour->obstacle) {
				notTestedNodes.push_back(neighbour);
			}

			// Potential lowest parent distance
			float possiblyLowerGoal = curr->f + h(curr, neighbour);

			// If choosing to path through this node is lower distance then what
			// the neighbour currently has set, update the neighbour to use this node
			// as the path source, and set it's distance scores as necessary
			if (possiblyLowerGoal < neighbour->f)
			{
				neighbour->parent = curr;
				neighbour->f = possiblyLowerGoal;

				// The best path length to the neighbour being tested has changed, so
				// update the neighbour's score. The heuristic is used to globally bias
				// the path algorith, so it knows if it's getting better or worse. At some
				// point the algorithm will realise this path is worse and abbandon it, and then go,
				// and search along the next best path
				neighbour->g = neighbour->f + h(neighbour, goal);
			}
		}

	}

	return goal;

}
