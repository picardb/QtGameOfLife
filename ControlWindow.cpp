#include "ControlWindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

ControlWindow::ControlWindow() :
	QWidget(), m_playing(false)
{
	/* Create timer */
	m_timer = new QTimer();
	m_timer->setInterval(c_timeInterval);
	m_timer->stop();

	/* Create game map */
	m_map = new GameMap(101, 101);
	InitMap();

	/* Set layout */
	m_layout = new QVBoxLayout();

	m_loadButton = new QPushButton("Load pattern");
	m_layout->addWidget(m_loadButton);
	m_displayCfgBox = new DisplayCfgBox(this, QString().setNum(c_beginSquareSize));
	m_layout->addWidget(m_displayCfgBox);
	m_nextButton = new QPushButton("Next");
	m_layout->addWidget(m_nextButton);
	m_playPauseButton = new QPushButton("Play");
	m_layout->addWidget(m_playPauseButton);
	setLayout(m_layout);

	/* Set geometry */
	setFixedWidth(c_fixedWidth);
	setFixedHeight(c_fixedHeight);
	move(c_beginXPos, c_beginYPos);

	/* Create display window */
	m_display = new DisplayWindow(this, m_map, c_beginSquareSize);
	m_display->show();
	m_display->update();

	QObject::connect(m_loadButton, SIGNAL(clicked()), this, SLOT(LoadButtonClicked()));
	QObject::connect(m_nextButton, SIGNAL(clicked()), this, SLOT(NextButtonClicked()));
	QObject::connect(m_playPauseButton, SIGNAL(clicked()), this, SLOT(PlayPauseButtonClicked()));
	QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(TimerTimeout()));
}

ControlWindow::~ControlWindow() {
	delete m_display;
	delete m_map;
	delete m_timer;
}

void ControlWindow::InitMap() {
	m_map->SetVal(49, 49, true);
	m_map->SetVal(49, 50, true);
	m_map->SetVal(49, 51, true);
	m_map->SetVal(50, 49, true);
	m_map->SetVal(50, 51, true);
	m_map->SetVal(51, 49, true);
	m_map->SetVal(51, 51, true);
}

void ControlWindow::closeEvent(QCloseEvent *event) {
	m_display->close();
	event->accept();
}

/* SLOTS */
void ControlWindow::LoadButtonClicked() {
	QString		fileName;
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::ExistingFile);
	if(dialog.exec()) {
		fileName = dialog.selectedFiles()[0];
	}

	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::warning(this, "File error", "Error when opening the file");
		return;
	}

	GameMap *newMap(0);
	/* Get map size on  first line */
	if(!file.atEnd()) {
		unsigned int newRowsNb(0), newColsNb(0);
		QTextStream lineStream(file.readLine());
		lineStream >> newRowsNb >> newColsNb;
		if((newRowsNb != 0) && (newColsNb != 0)) {
			newMap = new GameMap(newRowsNb, newColsNb);
		}
		else {
			QMessageBox::warning(this, "File error", "Error. Format incorrect");
		}
	}

	/* Get each point of the pattern */
	if(newMap) {
		while(!file.atEnd()) {
			unsigned int coordX(0), coordY(0);
			QTextStream lineStream(file.readLine());
			lineStream >> coordX >> coordY;
			newMap->SetVal(coordX, coordY, true);
		}

		/* Update map pointer */
		delete m_map;
		m_map = newMap;

		/* Delete old display and create a new one */
		delete m_display;
		unsigned int squareSize = m_displayCfgBox->GetSquareSize();
		m_display = new DisplayWindow(this, m_map, squareSize);
		m_display->show();
		m_display->update();
	}

	file.close();
}

void ControlWindow::NextButtonClicked() {
	m_map->Next();
	m_display->update();
}

void ControlWindow::PlayPauseButtonClicked() {
	m_playing = !m_playing;

	if(m_playing) {
		m_playPauseButton->setText("Pause");
		m_nextButton->setDisabled(true);
		m_loadButton->setDisabled(true);
		m_timer->start();
	}
	else {
		m_playPauseButton->setText("Play");
		m_nextButton->setEnabled(true);
		m_loadButton->setEnabled(true);
		m_timer->stop();
	}
}

void ControlWindow::TimerTimeout() {
	m_map->Next();
	m_display->update();
}

void ControlWindow::DisplayCfgUpdated() {
	bool border = m_displayCfgBox->GetBorderState();
	m_map->SetBorder(border);
	unsigned int newSize = m_displayCfgBox->GetSquareSize();
	m_display->SetSquareSize(newSize);
}
