#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QSignalMapper>
#include <vector>

#include "game.h"

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();
private slots:
	void buttonPushed(int it); 
private:
	void show_popup();
	void end_game(int x);

	std::vector<QPushButton*> buttons;
	QGridLayout* gameLayout;
	QSignalMapper* mapper;
	Game* game;
	bool first;
};