#include "../../include/Inventory.hpp"
#include "../../include/UI.hpp"

Inventory inventory;

Inventory::Inventory() {
    selector = 0;

    for (int i = 0; i < INV_CELLS_CAP; i++)
		inventory[i] = -1;
	
	inventory[0] = GRASS_SIDE;
}

void Inventory::addToInventory(int x, int y, int z) {
    for (int i = 0; i < INV_CELLS_CAP; i++) {
		if(inventory[i] != -1)
			inventory[i] = chunk[x][y][z].type;
	}
}

void Inventory::drawInventoryBlocks() {
    for (int i = 0; i < INV_CELLS_CAP; i++) {
		if(inventory[i] != -1)
			drawTexture(&texture[inventory[i]], TEXTURE_SIZE, TEXTURE_SIZE, INV_POS_X + 7 + (invWidth / 9) * selector, INV_POS_Y + 8, 1);  
	}
}

void Inventory::drawInventory() {
    drawTexture(&ui[INVENTORY], invWidth, invHeight, INV_POS_X, INV_POS_Y, 0.9);		// Inventory
	// drawTexture(&ui[INV_SELECTOR], INV_SEL_SIZE, INV_SEL_SIZE, INV_POS_X + (invWidth / 9) * selector, INV_POS_Y - 5, 1); // Inventory selector
	drawInventoryBlocks();
}

void Inventory::deleteBlock() {

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

void Inventory::calcCellBlocks() {

}
