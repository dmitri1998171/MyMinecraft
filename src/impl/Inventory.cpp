#include "../../include/Inventory.hpp"
#include "../../include/UI.hpp"

Inventory inventory;

Inventory::Inventory() {
    selector = 0;

    for (int i = 0; i < INV_CELLS_COUNT; i++) {
		inventory[i].type = -1;
		inventory[i].size = 1;
    }
}

void Inventory::addToInventory(int x, int y, int z) {
    for (int i = 0; i < INV_CELLS_COUNT; i++) {
        if(inventory[i].type == chunk[x][y][z].type) {      // if dropped block equal to the current block
            if(inventory[i].size < STACK_OF_BLOCKS) {
                inventory[i].size++;
                break;
            }
        }

        if(inventory[i].type == -1) {                       // if current cell is empty
            inventory[i].type = chunk[x][y][z].type;
            break;
        }
	}
}

void Inventory::drawInventoryBlocks() {
    for (int i = 0; i < INV_CELLS_COUNT; i++) {
		if(inventory[i].type != -1)
            if(inventory[i].size > 0)
			    drawTexture(&texture[inventory[i].type], TEXTURE_SIZE, TEXTURE_SIZE, INV_POS_X + 7 + (invWidth / 9) * i, INV_POS_Y + 8, 1);  

        if(inventory[i].size > 1) {
            renderBitmapString(BLOCKS_COUNTER_POS_X * i, BLOCKS_COUNTER_POS_Y, 1, GLUT_BITMAP_HELVETICA_12, itoa(inventory[i].size, new char[10], 10));
        }
	}
}

void Inventory::drawInventory() {
    drawTexture(&ui[INVENTORY], invWidth, invHeight, INV_POS_X, INV_POS_Y, 0.9);		// Inventory
	drawInventoryBlocks();
	drawTexture(&ui[INV_SELECTOR], INV_SEL_SIZE, INV_SEL_SIZE, INV_POS_X + (invWidth / 9) * selector, INV_POS_Y - 5, 1); // Inventory selector
}

int Inventory::deleteFromInventory() {
    if(inventory[selector].size > 0) {
        inventory[selector].size--;

        return inventory[selector].type;
    }

    inventory[selector].type = -1;
    inventory[selector].size = 1;
    return -1;
}

void Inventory::changeSelect(int direction) {
    if(direction > 0) 
		selector++;
	else 
		selector--;
	
	if(selector > 8)
		selector = 0;

	if(selector < 0)
		selector = 8;
}

void Inventory::setSelect(int selector) {
    this->selector = selector;
}

int Inventory::getSelect() {
    return inventory[selector].type;
}

void Inventory::calcCellBlocks() {

}
