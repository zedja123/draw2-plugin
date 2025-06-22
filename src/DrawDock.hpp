//
// Created by HichTala on 21/06/25.
//

#ifndef DRAW_DOCK_H
#define DRAW_DOCK_H

#include <QDockWidget>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QIcon>
#include <QStyle>

class DrawDock : public QWidget {
	Q_OBJECT

public:
	explicit DrawDock(QWidget *parent = nullptr);
	~DrawDock() override;

private:
	QWidget *parent = nullptr;
	QPushButton *start_button = new QPushButton();
	QPushButton *settings_button = new QPushButton();

private slots:
	void StartButtonClicked() const;
	void SettingsButtonClicked();
};

#endif //DRAW_DOCK_H
