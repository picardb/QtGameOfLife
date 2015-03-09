#ifndef _DISPLAYWINDOW_H
#define _DISPLAYWINDOW_H

#include <QWidget>
#include <QCloseEvent>

#include "GameMap.h"

class DisplayWindow : public QWidget {
private:
	static const int	c_beginXPos = 320;
	static const int	c_beginYPos = 200;

	GameMap			*m_map;
	unsigned int	m_squareSize;

	void UpdateDisplay();
protected:
	void closeEvent(QCloseEvent *event);
	void paintEvent(QPaintEvent *);

public:
	DisplayWindow(QWidget *parent, GameMap *map, unsigned int size);

	void SetSquareSize(unsigned int size);
};

#endif // _DISPLAYWINDOW_H
