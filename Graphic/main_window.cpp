#include "main_window.h"

MainWindow::MainWindow(){
	gameLayout = new QGridLayout;
	mapper = new QSignalMapper(this);
	//add all nine buttons
	int it = 1;
	buttons.push_back(NULL);
	for(int i=1; i<4; i++){
		for(int j=0; j<3; j++){
			QPushButton* b = new QPushButton(" ");
			buttons.push_back(b);
			gameLayout->addWidget(buttons[it], i-1, j, 1, 1);
			connect( buttons[it], SIGNAL( clicked() ), mapper, SLOT( map() ) );
			mapper->setMapping( buttons[it], it );
			it++;
		}
	}
	connect( mapper, SIGNAL( mapped(int) ), this, SLOT(buttonPushed(int) ) );
	setLayout(gameLayout);
	show_popup() ;
	game = new Game();
	if(first) buttons[game->move()]->setText("O");
}
MainWindow::~MainWindow(){
	for(int i=1; i<10; i++)
		delete buttons[i];
	delete gameLayout;
	delete mapper;
	delete game;
}
void MainWindow::buttonPushed(int it){
	if( !game->is_error(it) ){
		buttons[it]->setText("X");
		game->player_move(it);
		int x = game->check_win();
		if(x!=0) end_game(x);
		buttons[game->move()]->setText("O");
		x = game->check_win();
		if(x!=0) end_game(x);
	}
}
void MainWindow::show_popup(){
	// Create message box
	QMessageBox msgBox;
	msgBox.setWindowTitle("Tic Tac Toe");
	msgBox.setText("Would you like to go first?");
	msgBox.setInformativeText(" ");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);
	int userAnswer = msgBox.exec();
	if(userAnswer == QMessageBox::Yes) first = false;
	else if(userAnswer == QMessageBox::No) first = true;
}
void MainWindow::end_game(int x){
	// Create message box
	QMessageBox msgBox;
	msgBox.setWindowTitle("Tic Tac Toe");
	if(x==1) msgBox.setText("TIE!!!");
	else if(x==-1){ 
		msgBox.setText("YOU WIN!!!"); 
		msgBox.setInformativeText("Congratulations!");
	}
	else if(x==-2){ 
		msgBox.setText("You lost");
		msgBox.setInformativeText("Better luck next time!");
	}
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	int userAnswer = msgBox.exec();
	if(userAnswer == QMessageBox::Ok){close();}
}