#include "mobmovement.h"

void mobmovement(char map[40][101], int i) // checks if the mob can move, and also checks whether the mob encounters the player
{
	if (monster[i].alive == true) // checks if the mob is alive
	{
		if (monster[i].location.X > g_sChar.m_cLocation.X) // checks the position of the mob from the player
		{
			if ((collision(map, monster[i].location.Y, (monster[i].location.X - 1)) != true))
			{
				monster[6].location.X = monster[i].location.X - 1;
				monster[6].location.Y = monster[i].location.Y;
				if (monstercollides(i, monster) != true && touchend(map, monster[6].location.Y, monster[6].location.X) != true) //prevents mob from touching other mobs
				{
					monster[i].location.X--;
					if (touchplayer(monster, g_sChar, i)) // if the mob encounters the player, engage in combat
					{
						g_eGameState = S_COMBAT;
					}
				}
			} 
			else if (monster[i].location.Y > g_sChar.m_cLocation.Y) // if mob can't go first way, will try another way
			{
				if ((collision(map, (monster[i].location.Y - 1), monster[i].location.X) != true))
				{
					monster[6].location.X = monster[i].location.X;
					monster[6].location.Y = monster[i].location.Y - 1;
					if (monstercollides(i, monster) != true && touchend(map, monster[6].location.Y, monster[6].location.X) != true)
					{
						monster[i].location.Y--;
						if (touchplayer(monster, g_sChar, i))
						{
							g_eGameState = S_COMBAT;
						}
					}
				}
			}
			else if (monster[i].location.Y < g_sChar.m_cLocation.Y)
			{
				if ((collision(map, (monster[i].location.Y + 1), monster[i].location.X) != true))
				{
					monster[6].location.X = monster[i].location.X;
					monster[6].location.Y = monster[i].location.Y + 1;
					if (monstercollides(i, monster) != true && touchend(map, monster[6].location.Y, monster[6].location.X) != true)
					{
						monster[i].location.Y++;
						if (touchplayer(monster, g_sChar, i))
						{
							g_eGameState = S_COMBAT;
						}
					}
				}
			}
		}
		else if (monster[i].location.X < g_sChar.m_cLocation.X)
		{
			if ((collision(map, monster[i].location.Y, (monster[i].location.X + 1)) != true))
			{
				monster[6].location.X = monster[i].location.X + 1;
				monster[6].location.Y = monster[i].location.Y;
				if (monstercollides(i, monster) != true && touchend(map, monster[6].location.Y, monster[6].location.X) != true)
				{
					monster[i].location.X++;
					if (touchplayer(monster, g_sChar, i))
					{
						g_eGameState = S_COMBAT;
					}
				}
			}
			else if (monster[i].location.Y > g_sChar.m_cLocation.Y)
			{
				if ((collision(map, (monster[i].location.Y - 1), monster[i].location.X) != true))
				{
					monster[6].location.X = monster[i].location.X;
					monster[6].location.Y = monster[i].location.Y - 1;
					if (monstercollides(i, monster) != true && touchend(map, monster[6].location.Y, monster[6].location.X) != true)
					{
						monster[i].location.Y--;
						if (touchplayer(monster, g_sChar, i))
						{
							g_eGameState = S_COMBAT;
						}
					}
				}
			}
			else if (monster[i].location.Y < g_sChar.m_cLocation.Y)
			{
				if ((collision(map, (monster[i].location.Y + 1), monster[i].location.X) != true))
				{
					monster[6].location.X = monster[i].location.X;
					monster[6].location.Y = monster[i].location.Y + 1;
					if (monstercollides(i, monster) != true && touchend(map, monster[6].location.Y, monster[6].location.X) != true)
					{
						monster[i].location.Y++;
						if (touchplayer(monster, g_sChar, i))
						{
							g_eGameState = S_COMBAT;
						}
					}
				}
			}
		}
		else if (monster[i].location.Y < g_sChar.m_cLocation.Y)
		{
			if ((collision(map, (monster[i].location.Y + 1), monster[i].location.X) != true))
			{
				monster[6].location.X = monster[i].location.X;
				monster[6].location.Y = monster[i].location.Y + 1;
				if (monstercollides(i, monster) != true && touchend(map, monster[6].location.Y, monster[6].location.X) != true)
				{
					monster[i].location.Y++;
					if (touchplayer(monster, g_sChar, i))
					{
						g_eGameState = S_COMBAT;
					}
				}
			}
			else if (monster[i].location.X > g_sChar.m_cLocation.X)
			{
				if ((collision(map, monster[i].location.Y, (monster[i].location.X - 1)) != true))
				{
					monster[6].location.X = monster[i].location.X - 1;
					monster[6].location.Y = monster[i].location.Y;
					if (monstercollides(i, monster) != true && touchend(map, monster[6].location.Y, monster[6].location.X) != true)
					{
						monster[i].location.X--;
						if (touchplayer(monster, g_sChar, i))
						{
							g_eGameState = S_COMBAT;
						}
					}
				}
			}
			else if (monster[i].location.Y < g_sChar.m_cLocation.Y)
			{
				if (((collision(map, monster[i].location.Y, (monster[i].location.X + 1)) != true)))
				{
					monster[6].location.X = monster[i].location.X + 1;
					monster[6].location.Y = monster[i].location.Y;
					if (monstercollides(i, monster) != true && touchend(map, monster[6].location.Y, monster[6].location.X) != true)
					{
						monster[i].location.X++;
						if (touchplayer(monster, g_sChar, i))
						{
							g_eGameState = S_COMBAT;
						}
					}
				}
			}
		}
		else if (monster[i].location.Y > g_sChar.m_cLocation.Y)
		{
			if ((collision(map, (monster[i].location.Y - 1), monster[i].location.X) != true))
			{
				monster[6].location.X = monster[i].location.X;
				monster[6].location.Y = monster[i].location.Y - 1;
				if (monstercollides(i, monster) != true && touchend(map, monster[6].location.Y, monster[6].location.X) != true)
				{
					monster[i].location.Y--;
					if (touchplayer(monster, g_sChar, i))
					{
						g_eGameState = S_COMBAT;
					}
				}
			}
			else if (monster[i].location.X > g_sChar.m_cLocation.X)
			{
				if ((collision(map, monster[i].location.Y, (monster[i].location.X - 1)) != true))
				{
					monster[6].location.X = monster[i].location.X - 1;
					monster[6].location.Y = monster[i].location.Y;
					if (monstercollides(i, monster) != true && touchend(map, monster[6].location.Y, monster[6].location.X) != true)
					{
						monster[i].location.X--;
						if (touchplayer(monster, g_sChar, i))
						{
							g_eGameState = S_COMBAT;
						}
					}
				}
			}
			else if (monster[i].location.Y < g_sChar.m_cLocation.Y)
			{
				if ((collision(map, monster[i].location.Y, (monster[i].location.X + 1)) != true))
				{
					monster[6].location.X = monster[i].location.X + 1;
					monster[6].location.Y = monster[i].location.Y;
					if (monstercollides(i, monster) != true && touchend(map, monster[6].location.Y, monster[6].location.X) != true)
					{
						monster[i].location.X++;
						if (touchplayer(monster, g_sChar, i))
						{
							g_eGameState = S_COMBAT;
						}
					}
				}
			}
		}
	}
}