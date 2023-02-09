#ifndef MAP_HPP
#define MAP_HPP

#include "header.hpp"

struct block_t {
    bool exist;     
    GLuint type;    // texture of the block
};

struct curr_chunk_t {
    int x;
    int z;
};

class Map {
    private:
        vector<struct block_t ***> _map;
        curr_chunk_t currentChunk;

        struct block_t ***allocateChunk();
        struct block_t ***createFlatChunk();
        struct block_t ***createClassicChunk();
        
    public:
        Map();
        void makeABlock(int side_index, int top_index, int bottom_index, float pos = 0.5);
        void expand();
        void draw();
        void drawChunk(struct block_t ***chunk);
        void checkCurrentPosition(int x, int z);
        void setCurrentChunk(int x, int z);
        struct curr_chunk_t getCurrentChunk();
        void incCurrentChunk_x();
        void incCurrentChunk_z();

};

#endif