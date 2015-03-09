#ifndef _DISPLAYCFGBOX_H
#define _DISPLAYCFGBOX_H

#include <QGroupBox>
#include <QGridLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>

#include "ControlWindow.h"

class ControlWindow;

class DisplayCfgBox : public QGroupBox {
private:
	QWidget		*m_parent;
	QGridLayout *m_layout;
	QCheckBox	*m_borderBox;
	QLineEdit	*m_squareSizeEdit;
	QPushButton	*m_updateButton;
public:
	DisplayCfgBox(ControlWindow *parent, QString& beginText);

	bool GetBorderState() { return m_borderBox->isChecked(); }
	unsigned int GetSquareSize() { return m_squareSizeEdit->text().toUInt(); }
};

#endif // _DISPLAYCFGBOX_H
