#include <QPainter>

#include "DisplayWindow.h"

DisplayWindow::DisplayWindow(QWidget *parent, GameMap *map, unsigned int squareSize) :
	QWidget(parent, Qt::Dialog), m_map(map), m_squareSize(squareSize)
{
	/* Set geometry */
	setFixedHeight(squareSize * m_map->GetRowsNb());
	setFixedWidth(squareSize * m_map->GetColsNb());
	move(c_beginXPos, c_beginYPos);

	setWindowTitle("Display");
}

void DisplayWindow::UpdateDisplay() {
	QPainter p(this);
	for(int i=0 ; i < m_map->GetRowsNb() ; i++) {
		for(int j=0 ; j < m_map->GetColsNb() ; j++) {
			if(m_map->GetVal(i, j)) {
				p.fillRect(j * m_squareSize, i * m_squareSize, m_squareSize, m_squareSize, Qt::black);
			}
		}
	}
}

void DisplayWindow::SetSquareSize(unsigned int size) {
	m_squareSize = size;
	setFixedHeight(size * m_map->GetRowsNb());
	setFixedWidth(size * m_map->GetColsNb());
	UpdateDisplay();
}

void DisplayWindow::closeEvent(QCloseEvent *event) {
	event->ignore();
}

void DisplayWindow::paintEvent(QPaintEvent *) {
	UpdateDisplay();
}
