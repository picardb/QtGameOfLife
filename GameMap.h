#ifndef _GAMEMAP_H
#define _GAMEMAP_H

class GameMap {
private:
	unsigned int	m_rowsNb;
	unsigned int	m_colsNb;
	bool				m_connectedBorder;
	bool				*m_mapArray;

	void	AdjustCoord(int& x, int& y);
	int	GetAliveNeighbours(int x, int y);
public:
	GameMap(const unsigned int& rowsNb, const unsigned int& colsNb);
	~GameMap();

	void	SetVal(const int& x, const int& y, const bool& val) { m_mapArray[(x * m_colsNb) + y] = val; }
	bool	GetVal(int x, int y) const;
	void	SetBorder(bool border) { m_connectedBorder = border; }
	int	GetRowsNb() const { return m_rowsNb; }
	int	GetColsNb() const { return m_colsNb; }

	void	Next();
};

#endif // _GAMEMAP_H
