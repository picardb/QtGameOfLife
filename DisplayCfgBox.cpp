#include "DisplayCfgBox.h"

#include <QLabel>

DisplayCfgBox::DisplayCfgBox(ControlWindow *parent, QString& beginText) :
	m_parent(parent)
{
	m_layout = new QGridLayout();

	QLabel *checkboxLabel = new QLabel("Borders connected");
	m_layout->addWidget(checkboxLabel, 0, 0);
	m_borderBox = new QCheckBox();
	m_borderBox->setChecked(true);
	m_layout->addWidget(m_borderBox, 0, 1);
	QLabel *label = new QLabel("Square size");
	m_layout->addWidget(label, 1, 0);
	m_squareSizeEdit = new QLineEdit(beginText);
	m_squareSizeEdit->setMaxLength(2);
	m_squareSizeEdit->setFixedWidth(30);
	m_layout->addWidget(m_squareSizeEdit, 1, 1);
	m_updateButton = new QPushButton("Update");
	m_layout->addWidget(m_updateButton, 2, 0, 1, 2);

	setTitle("Display config");
	setLayout(m_layout);

	QObject::connect(m_updateButton, SIGNAL(clicked()), m_parent, SLOT(DisplayCfgUpdated()));
}
