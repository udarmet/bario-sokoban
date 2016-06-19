#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "matrix.h"
#include "Map.h"

void printMap(Map* map);

void printIntArray(int* array, int length);

void printIntMatrix(int** matrix, int width, int height);

void freeInt(void* elem);

int main(int argc, char* argv[])
{
	int *array, **matrix;
	int none = -1;
	int i;

	printf("\nArray tests\n\n");

	array = create_array(10, sizeof(int), &none);
	printIntArray(array, 10);

	for (i = 0; i < 10; i++)
		array[i] = i;
	printIntArray(array, 10);

	resize_array(&array, 10, 6, sizeof(int), &none, &freeInt);
	printIntArray(array, 6);

	resize_array(&array, 6, 10, sizeof(int), NULL, &freeInt);
	printIntArray(array, 10);

	printf("\nMatrix tests\n\n");

	matrix = create_matrix(4, 4, sizeof(int), &none);
	printIntMatrix(matrix, 4, 4);

	for (i = 0; i < 16; i++)
		matrix[i%4][i/4] = i;
	printIntMatrix(matrix, 4, 4);

	resize_matrix(&matrix, 4, 4, 6, 3, sizeof(int), &none, freeInt);
	printIntMatrix(matrix, 6, 3);

	resize_matrix(&matrix, 6, 3, 2, 5, sizeof(int), NULL, freeInt);
	printIntMatrix(matrix, 2, 5);

	destroy_array(array, 10, sizeof(int), NULL);
	destroy_matrix(matrix, 2, 5, sizeof(int), NULL);

	/*
	Map* m = createMap();
	Tile f = {TILE_FLOOR, TILE_NONE}, w = {TILE_WALL, TILE_NONE};
	int x, y;

	setMapSize(m, 4, 4);
	for (x = 0; x < m->width; x++)
	{
		for (y = 0; y < m->height; y++)
		{
			setMapTile(m, x, y, 0, &f);
		}
	}
	setMapTile(m, 2, 2, 0, &w);
	setMapTile(m, 2, 3, 1, &w);
	printMap(m);

	setMapSize(m, 5, 3);
	printMap(m);*/
	return 0;
}

void printMap(Map* map)
{
	int x, y, z;
	for (y = 0; y < map->height; y++)
	{
		for (x = 0; x < map->width; x++)
		{
			char c = '?';
			for (z = 0; z < map->tiles[x][y].altitude; z++)
			{
				Tile* t = getMapTile(map, x, y, z);
				switch (t->geometry)
				{
				case TILE_FLOOR:
					c = '.';
					break;
				case TILE_WALL:
					c = '#';
					break;
				case TILE_SLOPE:
					c = '/';
					break;
				default:
					break;
				}
			}
			printf("%c", c);
		}
		printf("\n");
	}
	printf("\n");
}

void printIntArray(int* array, int length)
{
	int i;
	printf("%p\t{", array);
	for (i = 0; i < length; i++)
	{
		printf("%d", array[i]);
		if (i < length - 1)
			printf(", ");
	}
	printf("}\n");
}

void printIntMatrix(int** matrix, int width, int height)
{
	int i, j;
	printf("%p\n", matrix);
	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

void freeInt(void* elem)
{
	printf("free(%d)\n", *((int*)elem));
}
