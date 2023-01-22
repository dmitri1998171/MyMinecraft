#ifndef INV_HPP
#define INV_HPP

#include "header.hpp"

struct cell_t {
    int type;
    int size;
};

class Inventory {
    private:
        int selector;	// current selected object from inventory
        struct cell_t inventory[INV_CELLS_COUNT];

    public:
        Inventory();
        void addToInventory(int x, int y, int z);
        void drawInventoryBlocks();
        void drawInventory();
        int deleteFromInventory();
        void changeSelect(int direction);
        void setSelect(int selector);
        int getSelect();
        void calcCellBlocks();
};

#endif