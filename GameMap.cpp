#include "GameMap.h"

/***************************************************/
/* Constructor													*/
/***************************************************/
GameMap::GameMap(const unsigned int& rowsNb, const unsigned int& colsNb) :
	m_rowsNb(rowsNb), m_colsNb(colsNb), m_connectedBorder(true)
{
	/* Create and initialize data array */
	m_mapArray = new bool[m_rowsNb * m_colsNb];
	for(int i=0 ; i < (int)(m_rowsNb * m_colsNb) ; i++) {
		m_mapArray[i] = false;
	}
}

/***************************************************/
/* Destructor													*/
/***************************************************/
GameMap::~GameMap() {
	delete m_mapArray;
}

/***************************************************/
/* GetVal														*/
/***************************************************/
bool GameMap::GetVal(int x, int y) const {
	if(x < 0 || x >= (int)m_rowsNb) {
		return false;
	}
	if(y < 0 || y >= (int)m_colsNb) {
		return false;
	}

	return m_mapArray[(x * m_colsNb) + y];
}

/***************************************************/
/* Next															*/
/* Computes the next step in the game of life.		*/
/***************************************************/
void GameMap::Next() {
	/* Create next map */
	bool	nextMap[m_rowsNb * m_colsNb];
	for(int i = 0 ; i < (int)m_rowsNb ; i++) {
		for(int j = 0 ; j < (int)m_colsNb ; j++) {
			bool currentState = GetVal(i, j);
			int aliveNeighbours = GetAliveNeighbours(i, j);

			if(currentState == false) {
				if(aliveNeighbours == 3) {
					nextMap[(i * m_colsNb) + j] = true;
				}
				else {
					nextMap[(i * m_colsNb) + j] = false;
				}
			}
			else
			{
				if(aliveNeighbours != 2 && aliveNeighbours != 3) {
					nextMap[(i * m_colsNb) + j] = false;
				}
				else {
					nextMap[(i * m_colsNb) + j] = true;
				}
			}
		}
	}

	/* Update map */
	for(int i = 0 ; i < (int)m_rowsNb ; i++) {
		for(int j = 0 ; j < (int)m_colsNb ; j++) {
			SetVal(i, j, nextMap[(i * m_colsNb) + j]);
		}
	}
}

/***************************************************/
/* AdjustCoord													*/
/* Adjust the coordinates when they go out of map	*/
/* space.														*/
/***************************************************/
void GameMap::AdjustCoord(int& x, int& y) {
	if(x < 0) {
		x = (int)m_rowsNb - 1;
	}
	if(x >= (int)m_rowsNb) {
		x = 0;
	}
	if(y < 0) {
		y = (int)m_colsNb - 1;
	}
	if(y >= (int)m_colsNb) {
		y = 0;
	}
}

/***************************************************/
/* GetAliveNeighbours										*/
/* Returns the number of "alive" neighbours of a	*/
/* point of the map. Used to compute the next step.*/
/***************************************************/
int GameMap::GetAliveNeighbours(int x, int y) {
	int aliveNeighbours = 0;

	/* Add all 9 squares centered on (x, y) */
	for(int xOffset = -1 ; xOffset <= 1 ; xOffset++) {
		for(int yOffset = -1 ; yOffset <= 1 ; yOffset++) {
			int xIdx = x + xOffset;
			int yIdx = y + yOffset;
			if(m_connectedBorder) {
				AdjustCoord(xIdx, yIdx);
			}
			if(GetVal(xIdx, yIdx)) {
				aliveNeighbours++;
			}
		}
	}

	/* Remove (x, y) square val */
	if(GetVal(x, y)) {
		aliveNeighbours--;
	}

	return aliveNeighbours;
}
