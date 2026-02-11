#pragma once

#include <QObject>
#include <QtWidgets/QMainWindow>
#include <QMenuBar>
#include <QMenu>

class PhotoEditorQT;

class Bar : public QObject
{
	Q_OBJECT

public:

	Bar(PhotoEditorQT* parent = nullptr);

	~Bar();

private slots:
	void on_action_triggered();


private:
	PhotoEditorQT* m_mainWindow;//save

	QMenuBar* mBar;
	QMenu* fileMenu;
	QMenu* helpMenu;
	QAction* openAction;
	QAction* exitAction;
	QAction* aboutAction;




};




