#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Arena.h"

int createBackground(VertexArray& rVA, IntRect arena)
{
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERTS_QUAD = 4;

	int worldWidth = arena.width / TILE_SIZE;
	int worldHeight = arena.height / TILE_SIZE;

	rVA.setPrimitiveType(Quads);
	rVA.resize(worldWidth * worldHeight * VERTS_QUAD);

	int currentVert = 0;
	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++) 
		{
			rVA[currentVert + 0].position = Vector2f(w * TILE_SIZE, h*TILE_SIZE);
			rVA[currentVert + 1].position = Vector2f((w * TILE_SIZE)+TILE_SIZE, h*TILE_SIZE);
			rVA[currentVert + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h*TILE_SIZE)+TILE_SIZE);
			rVA[currentVert + 3].position = Vector2f(w * TILE_SIZE, (h*TILE_SIZE) + TILE_SIZE);
			
			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1)
			{
				rVA[currentVert + 0].texCoords = Vector2f(0, 0 + TILE_TYPES*TILE_SIZE);
				rVA[currentVert + 1].texCoords = Vector2f(TILE_SIZE, 0 + TILE_TYPES*TILE_SIZE);
				rVA[currentVert + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES*TILE_SIZE);
				rVA[currentVert + 3].texCoords = Vector2f(0, TILE_SIZE + TILE_TYPES*TILE_SIZE);
			}
			else
			{
				srand((int)time(0) + h*w - h);
				int mOrg = (rand() % TILE_TYPES);
				int verticalOffset = mOrg *TILE_SIZE;

				rVA[currentVert + 0].texCoords = Vector2f(0, 0 + verticalOffset);
				rVA[currentVert + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
				rVA[currentVert + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[currentVert + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
			}
			currentVert = currentVert + VERTS_QUAD;
		}
	}
	return TILE_SIZE;
}