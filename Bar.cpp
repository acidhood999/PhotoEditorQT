#pragma once
#include "Bar.h"
#include "PhotoEditorQT.h" // Добавь это здесь!
#include <QFileDialog>
#include <QMessageBox>


Bar::Bar(PhotoEditorQT* mainWin) : QObject(mainWin), m_mainWindow(mainWin)
{

	mBar = mainWin->menuBar();
	fileMenu = mBar->addMenu("File");
	helpMenu = mBar->addMenu("Reference");

	openAction = fileMenu->addAction("Open photo");
	exitAction = fileMenu->addAction("Exit");

	aboutAction = helpMenu->addAction("About the program");

	connect(openAction, &QAction::triggered, this, &Bar::on_action_triggered);

	connect(exitAction, &QAction::triggered, mainWin, &QWidget::close);

	connect(aboutAction, &QAction::triggered, mainWin, [mainWin]() {
		QMessageBox::about(mainWin, "About the program", "Qt!");
		});
}

Bar::~Bar()
{
}

void Bar::on_action_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(m_mainWindow, "Select an image", "", "Image (*.jpg *.png)");


	m_mainWindow->setImage(fileName);

}