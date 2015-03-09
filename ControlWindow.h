#ifndef _CONTROLWINDOW_H
#define _CONTROLWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>

#include "GameMap.h"
#include "DisplayCfgBox.h"
#include "DisplayWindow.h"

class DisplayCfgBox;

class ControlWindow : public QWidget {
	Q_OBJECT

private:
	/* Window is fixed size 150x180 */
	static const int				c_fixedWidth = 200;
	static const int				c_fixedHeight = 240;
	static const int				c_beginXPos = 100;
	static const int				c_beginYPos = 200;

	static const int				c_timeInterval = 100;
	static const unsigned int	c_beginSquareSize = 4;

	GameMap				*m_map;
	DisplayWindow		*m_display;
	bool					m_playing;
	QTimer				*m_timer;

	QVBoxLayout			*m_layout;
	QPushButton			*m_loadButton;
	DisplayCfgBox		*m_displayCfgBox;
	QPushButton			*m_updateButton;
	QPushButton			*m_nextButton;
	QPushButton			*m_playPauseButton;

	void InitMap();

public:
	ControlWindow();
	~ControlWindow();

	void closeEvent(QCloseEvent *event);

public slots:
	void LoadButtonClicked();
	void NextButtonClicked();
	void PlayPauseButtonClicked();
	void TimerTimeout();
	void DisplayCfgUpdated();
};

#endif // _CONTROLWINDOW_H
