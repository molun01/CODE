#pragma once

#define A 2
#define B 6
#define C 5

typedef struct
{
	int x, y;
}Point;
Point point[] = 
{ 
	{8,8},{9,9},{7,10},{8,6},{8,8},{11,13},{8,10},{7,10},{9,11},{8,7},{6,12},{7,8},{13,10},{7,8},{7,8},{9,10},{7,9},{9,10},
	{8,10},{8,7},{8,11},{9,9},{8,10},{9,14},{10,11},{12,13},{12,15},{13,16},{7,9},{7,12},{8,9},{8,8},{12,14},{13,15},{10,10},
	{12,15},{8,9},{12,12},{10,11},{7,7}
};

//0:空地,1:墻,3:目的地,4:箱子,5:人
int Maps[][16][16] =
{
	{
	   {0,0,1,1,1,0,0,0},{0,0,1,3,1,0,0,0},{0,0,1,0,1,1,1,1},{1,1,1,4,0,4,3,1},
	   {1,3,0,4,5,1,1,1},{1,1,1,1,4,1,0,0},{0,0,0,1,3,1,0,0},{0,0,0,1,1,1,0,0}
	},
	{
		{1,1,1,1,1,0,0,0,0},{1,0,0,0,1,0,0,0,0},{1,0,4,4,1,0,1,1,1},{1,5,4,0,1,0,1,3,1},
		{1,1,1,0,1,1,1,3,1},{0,1,1,0,0,0,0,3,1},{0,1,0,0,0,1,0,0,1},{0,1,0,0,0,1,1,1,1},{0,1,1,1,1,1,0,0,0}
	},
	{
		{0,1,1,1,1,1,1,1,0,0},{0,1,0,0,0,0,0,1,1,1},{1,1,4,1,1,1,0,0,0,1},{1,5,0,0,4,0,0,4,0,1},
		{1,0,3,3,1,0,4,0,1,1},{1,1,3,3,1,0,0,0,1,0},{0,1,1,1,1,1,1,1,1,0}
	},
	{
		{0,1,1,1,1,0},{1,1,0,0,1,0},{1,5,0,4,1,0},{1,1,0,0,1,1},{1,1,4,4,0,1},{1,3,4,0,0,1},
		{1,3,3,7,3,1},{1,1,1,1,1,1}
	},
	{
		{0,1,1,1,1,1,0,0},{0,1,0,5,1,1,1,0},{0,1,0,4,0,0,1,0},{1,1,1,0,1,0,1,1},{1,3,1,0,1,0,0,1},
		{1,3,4,0,0,1,0,1},{1,3,0,0,0,4,0,1},{1,1,1,1,1,1,1,1}
	},
	{
		{0,0,0,1,1,1,1,1,1,1,0,0,0},{1,1,1,1,0,0,0,0,0,1,0,0,0},{1,0,0,0,3,1,1,1,0,1,0,0,0},
		{1,0,1,0,1,0,0,0,0,1,1,0,0},{1,0,1,0,4,0,4,1,3,0,1,0,0},{1,0,1,0,0,7,0,0,1,0,1,0,0},{1,0,3,1,4,0,4,0,1,0,1,0,0},
		{1,1,0,0,0,0,1,0,1,0,1,1,1},{0,1,0,1,1,1,3,0,0,0,0,5,1},{0,1,0,0,0,0,0,1,1,0,0,0,1},{0,1,1,1,1,1,1,1,1,1,1,1,1}
	},
	{
		{0,0,0,1,1,1,1,1,1,1},{0,0,1,1,0,0,1,0,5,1},{0,0,1,0,0,0,1,4,0,1},{0,0,1,4,0,0,4,0,0,1},
		{0,0,1,0,4,1,1,0,0,1},{1,1,1,0,4,0,1,0,1,1},{1,3,3,3,3,3,0,0,1,0},{1,1,1,1,1,1,1,1,1,0}
	},
	{
		 {0,0,0,1,1,1,1,1,1,0},{0,1,1,1,0,0,0,0,1,0},{1,1,3,0,4,1,1,0,1,1},{1,3,3,4,0,4,0,0,5,1},
		 {1,3,3,0,4,0,4,0,1,1},{1,1,1,1,1,1,0,0,1,0},{0,0,0,0,0,1,1,1,1,0}
	},
	{
		{0,1,1,1,1,1,1,1,1,1,0},{0,1,0,0,1,1,0,0,0,1,0},{0,1,0,0,0,4,0,0,0,1,0},{0,1,4,0,1,1,1,0,4,1,0},
		{0,1,0,1,3,3,3,1,0,1,0},{1,1,0,1,3,3,3,1,0,1,1},{1,0,4,0,0,4,0,0,4,0,1},{1,0,0,0,0,0,1,0,0,5,1},{1,1,1,1,1,1,1,1,1,1,1}
	},
	{
		{1,1,1,1,1,1,1},{1,3,3,4,3,3,1},{1,3,3,1,3,3,1},{1,0,4,4,4,0,1},{1,0,0,4,0,0,1},{1,0,4,4,4,0,1},
		{1,0,0,1,0,5,1},{1,1,1,1,1,1,1}
	},
	{
		{0,1,1,1,1,0,0,1,1,1,1,1},{1,1,0,0,1,0,0,1,0,0,0,1},{1,0,4,0,1,1,1,1,4,0,0,1},{1,0,0,4,3,3,3,3,0,4,0,1},
		{1,1,0,0,0,0,1,0,5,0,1,1},{0,1,1,1,1,1,1,1,1,1,1,0}
	},
	{
		{0,0,1,1,1,1,1,0},{1,1,1,0,0,5,1,0},{1,0,0,4,3,0,1,1},{1,0,0,3,4,3,0,1},{1,1,1,0,7,4,0,1},{0,0,1,0,0,0,1,1},
		{0,0,1,1,1,1,1,0}
	},
	{
		{0,0,1,1,1,1,1,1,1,0},{0,1,1,0,0,0,0,0,1,1},{0,1,0,4,0,0,4,3,0,1},{1,1,0,0,1,1,3,4,0,1},{1,0,0,4,5,1,4,3,0,1},
		{1,0,0,0,1,1,3,4,1,1},{1,1,1,4,1,0,4,3,0,1},{0,1,0,0,3,0,1,1,0,1},{0,1,0,0,0,0,1,0,0,1},{0,1,1,3,0,1,1,0,1,1},{0,0,1,1,3,1,0,0,1,0},
		{0,0,0,1,0,0,0,1,1,0},{0,0,0,1,1,1,1,1,0,0}
	},
	{
		{1,1,1,1,1,1,1,1},{1,0,0,1,0,0,0,1},{1,0,4,3,3,4,0,1},{1,5,4,3,7,0,1,1},{1,0,4,3,3,4,0,1},
		{1,0,0,1,0,0,0,1},{1,1,1,1,1,1,1,1}
	},
	{
		{0,1,1,1,1,1,1,0},{1,1,0,0,0,0,1,1},{1,0,4,0,4,4,0,1},{1,3,3,3,3,3,3,1},{1,0,4,4,0,4,0,1},
		{1,1,1,0,5,1,1,1},{0,0,1,1,1,1,0,0}
	},
	{
		{0,0,1,1,1,1,1,1,1,1},{0,0,1,0,0,0,0,1,1,1},{0,0,1,0,4,0,0,0,0,1},{1,1,1,0,4,0,1,1,0,1},{1,3,3,3,0,4,0,0,0,1},
		{1,3,3,3,4,1,4,0,1,1},{1,1,1,1,0,1,0,4,0,1},{0,0,0,1,0,0,0,5,0,1},{0,0,0,1,1,1,1,1,1,1}
	},
	{
		{1,1,1,1,1,1,0,0,0},{1,0,0,0,0,1,0,0,0},{1,0,4,4,4,1,1,0,0},{1,0,0,1,3,3,1,1,1},{1,1,0,0,3,3,4,0,1},
		{0,1,0,0,5,0,0,0,1},{0,1,1,1,1,1,1,1,1}
	},
	{
		{0,0,1,1,1,1,1,1,1,1},{0,0,1,0,0,0,1,3,0,1},{0,1,1,0,0,4,3,3,3,1},{0,1,0,0,4,0,1,7,3,1},
		{1,1,0,1,1,4,1,0,1,1},{1,0,0,0,4,0,0,4,0,1},{1,0,0,0,1,0,0,0,0,1},{1,1,1,1,1,1,1,5,0,1},{0,0,0,0,0,0,1,1,1,1}
	},
	{
		{0,1,1,1,1,1,1,1,0,0},{0,1,3,3,3,3,0,1,0,0},{1,1,1,3,3,3,4,1,1,1},{1,0,0,4,1,4,0,4,0,1},
		{1,0,4,4,0,0,1,4,0,1},{1,0,0,0,0,1,0,0,0,1},{1,1,1,1,0,5,0,1,1,1},{0,0,0,1,1,1,1,1,0,0}
	},
	{
		{1,1,1,1,1,1,1},{1,3,3,4,3,3,1},{1,3,3,1,3,3,1},{1,0,4,4,4,0,1},{1,0,0,4,0,0,1},{1,0,4,4,4,0,1},
		{1,0,0,1,5,0,1},{1,1,1,1,1,1,1}
	},
	{
		{0,0,0,1,1,1,1,1,1,0,0},{0,0,0,1,0,3,3,3,1,0,0},{1,1,1,1,3,3,3,3,1,0,0},{1,0,0,1,1,1,4,0,1,1,1},
		{1,0,4,0,4,0,0,4,4,0,1},{1,5,0,4,0,4,0,0,0,0,1},{1,0,0,0,1,1,1,0,0,0,1},{1,1,1,1,1,0,1,1,1,1,1}
	},
	{
		{1,1,1,1,1,1,1,1,0},{1,0,0,0,0,0,0,1,0},{1,0,1,4,4,0,0,1,0},{1,0,3,3,3,1,0,1,0},{1,1,3,3,3,4,0,1,1},
		{0,1,0,1,1,0,4,0,1},{0,1,4,0,0,4,0,0,1},{0,1,0,0,1,0,0,5,1},{0,1,1,1,1,1,1,1,1}
	},
	{
		{0,0,1,1,1,1,1,0,0,0},{1,1,1,0,0,0,1,1,1,1},{1,0,0,0,4,0,0,4,0,1},{1,0,4,0,5,4,0,0,0,1},{1,1,1,4,4,1,1,1,1,1},
		{0,0,1,0,0,3,3,1,0,0},{0,0,1,3,3,3,3,1,0,0},{0,0,1,1,1,1,1,1,0,0}
	},
	{
		{1,1,1,1,1,1,0,0,0,1,1,1,1,1},{1,0,0,0,0,1,1,1,0,1,0,0,0,1},{1,0,0,4,0,4,0,1,0,1,3,3,3,1},
		{1,0,1,0,0,4,0,1,1,1,0,0,3,1},{1,0,0,4,4,4,0,0,0,4,0,5,3,1},{1,1,1,0,0,4,0,0,4,1,0,0,3,1},{0,0,1,0,0,4,1,4,0,1,3,3,3,1},
		{0,0,1,1,0,0,0,0,0,1,0,0,3,1},{0,0,0,1,1,1,1,1,1,1,1,1,1,1}
	},
	{
		{0,0,0,0,0,1,1,1,1,1,1},{0,1,1,1,1,1,3,0,0,0,1},{0,1,0,0,1,3,3,1,1,0,1},{0,1,0,0,4,3,3,0,0,0,1},
		{0,1,0,0,1,0,3,1,0,1,1},{1,1,1,0,1,1,4,1,0,0,1},{1,0,4,0,0,0,0,4,4,0,1},{1,0,1,4,1,0,0,1,0,0,1},{1,5,0,0,1,1,1,1,1,1,1},
		{1,1,1,1,1,0,0,0,0,0,0}
	},
	{
		{0,1,1,1,1,1,1,1,1,1,0,0,0},{0,1,0,0,0,1,1,0,0,1,1,1,1},{0,1,0,4,0,0,0,0,0,0,0,0,1},{0,1,1,4,1,1,1,0,1,1,0,0,1},
		{0,1,0,0,1,1,0,7,0,1,0,1,1},{0,1,0,4,3,3,3,3,3,3,0,1,0},{1,1,0,1,1,1,0,3,0,1,0,1,0},{1,0,0,0,0,0,4,1,1,1,4,1,0},
		{1,0,0,0,1,0,0,0,0,4,5,1,0},{1,1,1,1,1,4,1,0,1,1,1,1,0},{0,0,0,0,1,0,0,0,1,0,0,0,0},{0,0,0,0,1,1,1,1,1,0,0,0,0}
	},
	{
		{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},{0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,1,0,1,0,1,0,1,0,1},
		{0,0,0,0,0,0,1,0,0,4,0,4,1,0,1},{1,1,1,1,1,1,1,0,0,0,4,0,0,0,1},{1,3,3,1,0,0,1,1,0,4,0,4,1,0,1},{1,3,3,0,0,0,1,1,0,4,0,4,0,0,1},
		{1,3,3,1,0,0,1,1,0,1,1,1,1,1,1},{1,3,3,1,0,1,0,4,0,4,0,1,0,0,0},{1,3,3,0,0,0,0,0,4,0,0,1,0,0,0},{1,0,0,1,1,1,5,0,0,1,1,1,0,0,0},
		{1,1,1,1,0,1,1,1,1,1,0,0,0,0,0}
	},
	{
		{0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},{1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0},{1,0,0,4,0,4,0,1,0,1,1,1,1,1,1,1},
		{1,0,0,0,4,0,0,1,0,1,7,3,7,3,7,1},{1,1,0,4,0,4,0,1,1,1,3,7,3,7,3,1},{0,1,4,0,4,0,0,1,0,0,7,3,7,3,7,1},{0,1,5,4,0,4,0,0,0,0,3,7,3,7,1,1},
		{0,1,4,0,4,0,0,1,0,0,7,3,7,3,7,1},{1,1,0,4,0,4,0,1,1,1,3,7,3,7,3,1},{1,0,0,0,4,0,0,1,0,1,7,3,7,3,7,1},
		{1,0,0,4,0,4,0,1,0,1,1,1,1,1,1,1},{1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0},{0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0}
	},
	{
		{1,1,1,1,1,1,1,1,0},{1,3,3,3,3,3,3,1,0},{1,0,0,4,0,1,0,1,1},{1,0,4,0,1,0,4,0,1},{1,1,4,0,4,0,4,0,1},
		{0,1,0,0,5,0,0,0,1},{0,1,1,1,1,1,1,1,1}
	},
	{
		{0,0,1,1,1,1,1,1,1,1,1,1},{1,1,1,0,0,0,3,4,5,0,0,1},{1,0,0,0,1,1,4,1,1,0,0,1},{1,0,0,0,7,0,3,0,3,0,1,1},
		{1,1,0,4,1,1,4,1,1,0,1,0},{0,1,0,0,0,0,3,0,0,0,1,0},{0,1,1,1,1,1,1,1,1,1,1,0}
	},
	{
		 {0,0,0,1,1,1,1,1,1},{1,1,1,1,3,0,0,5,1},{1,0,0,4,4,4,0,0,1},{1,3,1,1,3,1,1,3,1},{1,0,0,0,4,0,0,0,1},
		 {1,0,0,4,3,1,0,1,1},{1,1,1,1,0,0,0,1,0},{0,0,0,1,1,1,1,1,0}
	},
	{
		 {0,1,1,1,1,1,1,0},{0,1,3,0,3,3,1,0},{0,1,3,0,4,3,1,0},{1,1,1,0,0,4,1,1},{1,0,4,0,0,4,0,1},
		 {1,0,1,4,1,1,0,1},{1,0,0,0,5,0,0,1},{1,1,1,1,1,1,1,1}
	},
	{
		{0,0,0,0,1,1,1,1,1,1,0,0,0,0},{0,0,1,1,1,0,0,0,0,1,1,1,0,0},{0,0,1,0,0,0,1,4,0,0,0,1,1,1},{0,0,1,0,0,0,4,0,0,0,4,4,0,1},
		{0,0,1,0,4,4,0,1,4,0,0,0,0,1},{0,0,1,1,0,0,0,4,0,0,0,4,0,1},{1,1,1,1,1,1,0,1,4,1,1,1,1,1},{1,3,3,5,0,1,4,0,0,1,0,0,0,0},
		{1,3,1,3,3,0,0,4,1,1,0,0,0,0},{1,3,3,3,3,4,1,0,1,0,0,0,0,0},{1,3,3,3,3,0,0,0,1,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,0,0,0,0,0}
	},
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,0,0,0,0,0,0,1,0,0,0,0,0,0,1},{1,0,4,0,1,4,0,1,0,4,1,1,4,0,1},
		{1,0,1,0,0,4,0,1,0,0,0,0,0,0,1},{1,0,0,0,1,1,4,1,4,1,1,4,4,0,1},{1,0,1,0,1,0,3,3,3,0,1,0,0,0,1},{1,0,4,0,0,3,0,1,0,3,4,0,0,0,1},
		{1,0,4,1,5,4,3,3,3,1,0,1,0,0,1},{1,0,0,0,0,3,0,1,0,3,0,0,4,0,1},{1,0,1,1,3,4,1,1,1,4,3,0,1,0,1},{1,0,1,0,4,3,3,3,3,3,0,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	},
	{
		{1,1,1,1,1,1,1,1,1,0},{1,0,0,0,1,1,0,0,1,0},{1,0,1,0,4,0,4,0,1,0},{1,0,0,7,3,1,0,0,1,0},{1,1,0,1,3,5,3,1,1,0},
		{1,1,4,1,1,1,7,1,1,1},{1,0,0,0,0,0,0,0,0,1},{1,0,0,0,1,1,0,1,0,1},{1,1,1,1,1,1,0,0,0,1},{0,0,0,0,0,1,1,1,1,1}
	},
	{
		{1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0},{1,0,4,4,0,0,0,1,1,1,0,0,0,0,0},
		{1,0,0,4,0,4,4,4,0,1,1,1,1,1,0},{1,1,0,1,1,0,3,3,3,0,0,0,0,1,1},{0,1,0,1,5,1,3,3,3,1,1,1,4,0,1},
		{0,1,0,1,0,4,3,3,3,0,0,0,0,0,1},{1,1,0,1,0,4,3,3,3,4,0,1,0,1,1},{1,0,0,1,1,1,1,1,0,1,1,1,0,1,0},
		{1,0,0,0,0,0,0,4,0,0,0,4,0,1,0},{1,1,1,1,1,1,1,1,1,1,1,0,0,1,0},{0,0,0,0,0,0,0,0,0,0,1,1,1,1,0}
	},
	{
		 {0,0,0,1,1,1,1,1,0},{0,0,0,1,0,5,0,1,0},{0,0,0,1,4,4,4,1,0},{1,1,1,1,0,0,0,1,0},{1,0,0,0,3,4,4,1,1},
		 {1,0,4,3,4,3,0,3,1},{1,0,0,1,3,1,3,1,1},{1,1,1,1,1,1,1,1,0}
	},
	{
		 {1,1,1,1,1,1,1,1,1,1,1,1},{1,3,3,3,0,1,0,0,0,0,0,1},{1,3,3,0,0,1,0,1,1,0,0,1},{1,3,3,0,0,0,0,0,1,0,0,1},
		 {1,3,3,0,0,1,0,4,1,1,0,1},{1,3,3,3,0,1,4,0,4,0,0,1},{1,1,1,1,1,1,0,0,4,4,0,1},{0,1,1,0,0,4,0,4,4,0,0,1},{0,1,5,0,4,4,4,0,0,1,0,1},
		 {0,1,1,0,4,0,1,1,0,0,0,1},{0,0,1,0,0,0,0,0,0,0,0,1},{0,0,1,1,1,1,1,1,1,1,1,1}
	},
	{
		 {1,1,1,1,1,1,1,1,1,0,0},{1,0,0,0,0,0,0,0,1,0,0},{1,0,0,4,0,4,0,4,1,0,0},{1,1,0,1,4,1,1,0,1,0,0},{0,1,0,3,3,0,3,3,1,1,0},
		 {0,1,1,3,3,0,3,3,0,1,0},{0,0,1,0,1,1,4,1,0,1,1},{0,0,1,4,0,4,0,4,0,0,1},{0,0,1,0,0,0,0,0,0,5,1},{0,0,1,1,1,1,1,1,1,1,1}
	},
	{
		{1,1,1,1,1,1,1},{1,3,0,3,0,3,1},{1,0,4,4,4,0,1},{1,3,4,5,4,3,1},{1,0,4,4,4,0,1},{1,3,0,3,0,3,1},{1,1,1,1,1,1,1}
	}
};


void GameOperate(int Map[][20], int* n, int* m, int* js, int* sum, int* data, int* sl, int* guanshu, char* ch);
void EasyGameOperate(int Map[][20], int* n, int* m, int* js, int* sum, int* data, int* sl, int* guanshu, char* ch);
void EasyMap(int Map[20][20], int* n, int* m, char* ch);
void MiddleMap(int Map[20][20], int* n, int* m, char* ch);
void DifficultyMap(int Map[][20], int* n, int* m, char* ch);
void SelectMap(int Map[][20], int* n, int* m, int guan);//, char* ch
void MenuTwo(char* ch);
void MenuOne(char* ch);
void Menu(char* ch);
void PlayGame(int Map[20][20], int* n, int* m, char* ch);
void EasyGame(char* ch);
void MiddleGame(char* ch);
void DifficultyGame(char* ch);
void Operation(char* ch);
void Introduction(char* ch);
void Gameintor(char* ch);
void Autor(char* ch);
void Select(char* ch);
void SelectGame(char* ch, int guan);
void Gotoxy(int x, int y);
void Password(char* ch);
void Hide();
void Clear();
void Color(int front, int background);
void MyTime();
int BoxData(int Map[][20], int* n, int* m);
int GroundData(int Map[][20], int* n, int* m);
int DrawMap(int Map[20][20], int* n, int* m, int* guanshu);
int GameReady();
int SelectGameReady(char* ch, int guan);

int data = 0;//步数
int* bushu = &data;
int kongge = 0;
int xianshi = 0;
int yanchi = 0;