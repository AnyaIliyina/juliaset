#pragma once 
#include <QMainWindow>
namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
public:

	explicit MainWindow(QWidget *parent = 0);

	~MainWindow();

protected:
	Ui::MainWindow* m_ui;
};


