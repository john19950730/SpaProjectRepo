
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "GUIWrapper.h"
#include <iostream>
#include <QFileDialog>
#include <QtGui>
#include <QTextStream>

#include <list>

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	wrapper = new GUIWrapper();
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::btnLoad_clicked() {

	QString src_name = QFileDialog::getOpenFileName(this,
		tr("Open Source file"), ".", tr("txt Files (*.txt)"));

	QFile file;
	file.setFileName(src_name);
	if (!file.open(QIODevice::ReadOnly))
		return;
	QString m_fileContents = file.readAll();
	ui->txtCodeEditor->document()->setPlainText(m_fileContents);	
	wrapper->parse(src_name.toStdString());
	wrapper->parseFromCode(ui->txtCodeEditor->toPlainText().toStdString());
}

void MainWindow::btnRun_clicked() {
	std::list<std::string> results;
	wrapper->evaluate(ui->txtQuery->toPlainText().toStdString(),results);
	//wrapper->parseFromCode(ui->txtCodeEditor->toPlainText().toStdString());
	//std::cout << ui->txtCodeEditor->toPlainText().toStdString();
	QString result_str;

	for (auto const& result : results) {

		result_str += QString(result.c_str());
	}
	ui->txtResult->document()->setPlainText(result_str);

}
