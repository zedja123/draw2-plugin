//
// Created by HichTala on 22/06/25.
//

#include "SettingsDialog.hpp"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
	setWindowTitle("Draw 2 Settings");

	auto *layout = new QVBoxLayout(this);
	auto *label = new QLabel("Select Deck List to use (leave empty if none)", this);
	layout->addWidget(label);

	auto *browse_layout = new QHBoxLayout();
	browse_layout->addWidget(this->deck_list);
	browse_layout->addWidget(this->browse_button);

	this->ok_button->setProperty("class", "QPushButton");
	this->cancel_button->setProperty("class", "QPushButton");

	auto *buttons_layout = new QHBoxLayout();
	buttons_layout->addStretch();
	buttons_layout->addWidget(this->cancel_button);
	buttons_layout->addWidget(this->ok_button);

	layout->addLayout(browse_layout);
	layout->addLayout(buttons_layout);

	setLayout(layout);
	connect(browse_button, SIGNAL(clicked()), SLOT(BrowseButtonClicked()));
	connect(ok_button, SIGNAL(clicked()), SLOT(OkButtonClicked()));
	connect(cancel_button, SIGNAL(clicked()), SLOT(CancelButtonClicked()));

	resize(400, 50);
}

void SettingsDialog::BrowseButtonClicked()
{
	QString filePath = QFileDialog::getOpenFileName(this, "Select Deck List File");
	if (!filePath.isEmpty()) {
		this->deck_list->setText(filePath);
	}
}

void SettingsDialog::OkButtonClicked()
{
	this->close();
}

void SettingsDialog::CancelButtonClicked()
{
	this->close();
}
