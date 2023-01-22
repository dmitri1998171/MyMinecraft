#ifndef INV_HPP
#define INV_HPP

#include "header.hpp"

class Inventory {
    private:
        int selector;	// current selected object from inventory
        GLuint inventory[INV_CELLS_CAP];

    public:
        Inventory();
        void addToInventory(int x, int y, int z);
        void drawInventoryBlocks();
        void drawInventory();
        void deleteBlock();
        void changeSelect(int direction);
        void setSelect(int selector);
        void calcCellBlocks();
};

#endif