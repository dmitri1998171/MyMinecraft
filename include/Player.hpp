#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "header.hpp"

class Player {
    private:
        float x, y, z;
        float dx, dy, dz;
        float height;
        float speed;

    public:
        Player();
        void update();
        void move();
        void lookAround();
        void collision();
        float getX();
        float getY();
        float getZ();
};

#endif