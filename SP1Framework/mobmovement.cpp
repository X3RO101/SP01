#include "mobmovement.h"

void mobmovement(char map[40][101], int i)
{
	if (monster[i].alive == true)
	{
		if (monster[i].location.X > g_sChar.m_cLocation.X)
		{
			if ((collision(map, monster[i].location.Y, (monster[i].location.X - 1)) != true))
			{
				monster[6].location.X = monster[i].location.X - 1;
				monster[6].location.Y = monster[i].location.Y;
				if (monstercollides(i, monster) != true && touchend(map, monster[6].location.Y, monster[6].location.X) != true)
				{
					monster[i].location.X--;
					if (touchplayer(map, monster[i].location.Y, monster[i].location.X))
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
						if (touchplayer(map, monster[i].location.Y, monster[i].location.X))
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
						if (touchplayer(map, monster[i].location.Y, monster[i].location.X))
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
					if (touchplayer(map, monster[i].location.Y, monster[i].location.X))
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
						if (touchplayer(map, monster[i].location.Y, monster[i].location.X))
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
						if (touchplayer(map, monster[i].location.Y, monster[i].location.X))
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
					if (touchplayer(map, monster[i].location.Y, monster[i].location.X))
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
						if (touchplayer(map, monster[i].location.Y, monster[i].location.X))
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
						if (touchplayer(map, monster[i].location.Y, monster[i].location.X))
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
					if (touchplayer(map, monster[i].location.Y, monster[i].location.X))
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
						if (touchplayer(map, monster[i].location.Y, monster[i].location.X))
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
						if (touchplayer(map, monster[i].location.Y, monster[i].location.X))
						{
							g_eGameState = S_COMBAT;
						}
					}
				}
			}
		}
	}
}