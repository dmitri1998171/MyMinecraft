#include "../../include/header.hpp"
#include "../../include/UI.hpp"
#include "../../include/world.hpp"
#include "../../include/Button.hpp"
#include "../../include/dependencies/Perlin_Noise.hpp"

void makeABlock(int side_index, int top_index, int bottom_index, float pos) {
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

void createFlatWorld() {
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
}

void createClassicWorld() {
	// const siv::PerlinNoise::seed_type seed = 123456;
	const siv::PerlinNoise::seed_type seed = rand() % 1000000;
	const siv::PerlinNoise perlin{ seed };

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
}