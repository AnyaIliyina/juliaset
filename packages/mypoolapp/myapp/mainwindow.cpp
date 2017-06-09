#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);
}

void MainWindow::on_okButton_clicked()
{
	auto x = m_ui->lineEdit->text().toDouble();
	auto y = m_ui->lineEdit_2->text().toDouble();
	m_ui->openGLWidget->setC(x, y);
}

MainWindow::~MainWindow()
{
}
