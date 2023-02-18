#include "../../include/Map.hpp"
#include "../../include/dependencies/Perlin_Noise.hpp"

Map::Map() {
	currentChunk.x = 0;
	currentChunk.z = 0;
}

struct block_t ***Map::allocateChunk() {
	struct block_t ***chunk;
	chunk = new struct block_t **[fieldSize];

    for (int x = 0; x < fieldSize; x++) {
        chunk[x] = new struct block_t *[WORLD_HEIGHT];

        for (int y = 0; y < WORLD_HEIGHT; y++) {
            chunk[x][y] = new struct block_t [fieldSize];

			for (int z = 0; z < fieldSize; z++) {
				chunk[x][y][z].exist = false;
			}
			
        }
    }

	return chunk;
}

struct block_t *** Map::createFlatChunk() {
// memory allocation
	struct block_t ***chunk = allocateChunk();

// creating the chunk
	for (int i = 0; i < fieldSize; i++) {
		for (int j = 0; j < FLAT_WORLD_DEPTH; j++) {
			for (int k = 0; k < fieldSize; k++) {
				chunk[i][j][k].exist = true;

				if(j == 0)			// bedrock
					chunk[i][j][k].type = BEDROCK;
				else if(j > 3)  // grass
					chunk[i][j][k].type = GRASS_SIDE;
				else			// dirt
					chunk[i][j][k].type = DIRT;
			}
		}
	}

	return chunk;
}

struct block_t ***Map::createClassicChunk() {
	const siv::PerlinNoise::seed_type seed = rand() % 1000000;
	const siv::PerlinNoise perlin{ seed };

// memory allocation
	struct block_t ***chunk = allocateChunk();

// creating the chunk
	for (int x = 0; x < fieldSize; x++) {
		for (int z = 0; z < fieldSize; z++) {
			const int noise = perlin.octave2D_01((x * 0.01), (z * 0.01), 4) * PERLIN_NOISE_SCALE;
		
			for (int y = 0; y < noise; y++) {
				chunk[x][y][z].exist = true;

				if(y == 0)				 // bedrock
					chunk[x][y][z].type = BEDROCK;
				else if(y == noise - 1)  // grass
					chunk[x][y][z].type = GRASS_SIDE;
				else					 // dirt
					chunk[x][y][z].type = DIRT;
			}
		}
	}

	return chunk;
}

void Map::makeABlock(int side_index, int top_index, int bottom_index, float pos) {
   // Activate a texture.
   glBindTexture(GL_TEXTURE_2D, side_index);
    // Front
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-pos, -pos, pos);
		glTexCoord2f(0, 1); glVertex3f(-pos,  pos, pos);
		glTexCoord2f(1, 1); glVertex3f( pos,  pos, pos);
		glTexCoord2f(1, 0); glVertex3f( pos, -pos, pos);
	glEnd();

    // Back
    glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-pos, -pos, -pos);
		glTexCoord2f(0, 1); glVertex3f(-pos,  pos, -pos);
		glTexCoord2f(1, 1); glVertex3f( pos,  pos, -pos);
		glTexCoord2f(1, 0); glVertex3f( pos, -pos, -pos);
	glEnd();

    // Left
    glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-pos, -pos, -pos);
		glTexCoord2f(1, 0); glVertex3f(-pos, -pos,  pos);
		glTexCoord2f(1, 1); glVertex3f(-pos,  pos,  pos);
		glTexCoord2f(0, 1); glVertex3f(-pos,  pos, -pos);
	glEnd();

    // Right
    glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(pos, -pos, -pos);
		glTexCoord2f(1, 0); glVertex3f(pos, -pos,  pos);
		glTexCoord2f(1, 1); glVertex3f(pos,  pos,  pos);
		glTexCoord2f(0, 1); glVertex3f(pos,  pos, -pos);
	glEnd();

   	glBindTexture(GL_TEXTURE_2D, top_index);

    // Top
    glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f( pos, pos, -pos);
		glTexCoord2f(1, 0); glVertex3f( pos, pos,  pos);
		glTexCoord2f(1, 1); glVertex3f(-pos, pos,  pos);
		glTexCoord2f(0, 1); glVertex3f(-pos, pos, -pos);
	glEnd();

   	glBindTexture(GL_TEXTURE_2D, bottom_index);

    // Bottom
    glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f( pos, -pos, -pos);
		glTexCoord2f(1, 0); glVertex3f( pos, -pos,  pos);
		glTexCoord2f(1, 1); glVertex3f(-pos, -pos,  pos);
		glTexCoord2f(0, 1); glVertex3f(-pos, -pos, -pos);
	glEnd();
}

void Map::expand() {
	// _map.push_back(createClassicChunk());
	_map.push_back(createFlatChunk());
}

void Map::draw() {
	for (int i = 0; i < _map.size(); i++) {
		glPushMatrix();

// currentChunk.x умножается на i и мешает !!! без currentChunk.x чанк генерится по диаг.


			glTranslatef(i * fieldSize * pos * currentChunk.x, 0, i * fieldSize * pos * currentChunk.z);
			drawChunk(_map[i]);
		glPopMatrix();
	}
}

void Map::drawChunk(struct block_t ***chunk) {
	for (int i = 0; i < fieldSize; i++) {
		for (int j = 0; j < WORLD_HEIGHT; j++) {
			for (int k = 0; k < fieldSize; k++) {
				if(chunk[i][j][k].exist == true) {
                    glPushMatrix();
						glTranslatef(i, j, k);

						if(chunk[i][j][k].type == BEDROCK)
							makeABlock(texture[BEDROCK], texture[BEDROCK], texture[BEDROCK]);	// bedrock
						else if(chunk[i][j][k].type == GRASS_SIDE)
							makeABlock(texture[GRASS_SIDE], texture[GRASS_TOP], texture[DIRT]);	// grass
						else
							makeABlock(texture[DIRT], texture[DIRT], texture[DIRT]);			// dirt
                    glPopMatrix();
                }
			}
		}
	}
}

void Map::checkCurrentPosition(int x, int z) {
	if(x > _map.size() * fieldSize * pos) {
		incCurrentChunk_x();
		expand();
	}

	if(z > _map.size() * fieldSize * pos) {
		incCurrentChunk_z();
		expand();
	}
}

void Map::setCurrentChunk(int x, int z) {
	currentChunk.x = x;
	currentChunk.z = z;
}

struct curr_chunk_t Map::getCurrentChunk() {
	return currentChunk;
}

void Map::incCurrentChunk_x(){
	currentChunk.x++;
}

void Map::incCurrentChunk_z(){
	currentChunk.z++;
}

Map _map;

