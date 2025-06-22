//
// Created by HichTala on 22/06/25.
//

#ifndef SETTINGSPOPUP_HPP
#define SETTINGSPOPUP_HPP

#include "DrawDock.hpp"

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>

class SettingsDialog : public QDialog {
	Q_OBJECT

public:
	explicit SettingsDialog(QWidget *parent = nullptr);

private:
	QLineEdit *deck_list = new QLineEdit();
	QPushButton *browse_button = new QPushButton("Browse");
	QPushButton *ok_button = new QPushButton("&OK");
	QPushButton *cancel_button = new QPushButton("&Cancel");

private slots:
	void BrowseButtonClicked();
	void OkButtonClicked();
	void CancelButtonClicked();
};

#endif //SETTINGSPOPUP_HPP
