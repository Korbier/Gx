#pragma once

#include "display/map/Map.h"

class JpsGrid
{

public:

    JpsGrid(Map* map) {
        this->map = map;
        this->width = map->getWidth();
        this->height = map->getHeight();
    }

    inline bool operator()(unsigned x, unsigned y) const // coordinates must be unsigned; method must be const
    {

        if (x >= 0 && y >= 0 && x < width && y < height) {
            return !map->getTileAt(x, y)->getReference()->isSolid();
        }

        return false;

    }

private:
    Map* map;
    unsigned width, height;

};