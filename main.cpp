#include <QApplication>

#include "ControlWindow.h"
#include "DisplayWindow.h"
#include "GameMap.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);

	/* Create main window */
	ControlWindow win;
	win.setWindowTitle("Game of life");
	win.show();

	return app.exec();
}
