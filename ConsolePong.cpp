#include <iostream>
#include <thread>
#include <conio.h>
#include <iomanip>

// set the map size
const int MAP_WIDTH = 60;
const int MAP_HEIGHT = 15;

// set the paddles size
const int PADDLE1_LENGTH = 5;
const int PADDLE2_LENGTH = 5;

// set the initial position and velocity of the ball
const int BALL_INIT_POSITION_ROW = 3;
const int BALL_INIT_POSITION_COLUMN = 3;
const int BALL_INIT_ROW_VELOCITY = 1;
const int BALL_INIT_COLUMN_VELOCITY = 1;

/*
Start menu
*/
void startMenu() {
    system("cls");

    std::cout << "************************************************************" << "\n";
    std::cout << "*                                                          *" << "\n";
    std::cout << "*                                                          *" << "\n";
    std::cout << "*                                                          *" << "\n";
    std::cout << "*                                                          *" << "\n";
    std::cout << "*                                                          *" << "\n";
    std::cout << "*                                                          *" << "\n";
    std::cout << "*                        PONG GAME                         *" << "\n";
    std::cout << "*                                                          *" << "\n";
    std::cout << "*                                                          *" << "\n";
    std::cout << "*                                                          *" << "\n";
    std::cout << "*                                                          *" << "\n";
    std::cout << "*                                                          *" << "\n";
    std::cout << "*                                                          *" << "\n";
    std::cout << "*                                                          *" << "\n";
    std::cout << "************************************************************" << "\n";
}

/*
Controls the movement of paddles
*/
void paddlesMove(char (&map)[MAP_HEIGHT][MAP_WIDTH], int &Paddle1TopPos, int &Paddle1BottomPos, int &Paddle2TopPos, int &Paddle2BottomPos, bool &inGame, char &moveKey, unsigned &player1Score, unsigned &player2Score) {
    
    //draws the paddle1 in its initial position
    for(int i = Paddle1TopPos; i <= Paddle1BottomPos; i++) {
        map[i][1] = '[';
        map[i][2] = ']';
    }
    //draws the paddle2 in its initial position
    for(int i = Paddle2TopPos; i <= Paddle2BottomPos; i++) {
        map[i][MAP_WIDTH - 3] = '[';
        map[i][MAP_WIDTH - 2] = ']';
    }
    

    while(inGame) {
        moveKey = getch();

        if(moveKey == 's') { //downward movement
            if(Paddle1BottomPos == MAP_HEIGHT - 2) {
                for(int i = Paddle1TopPos; i <= Paddle1BottomPos; i++) {
                    map[i][1] = '[';
                    map[i][2] = ']';
                }
                continue;
            }
            map[Paddle1TopPos][1] = ' ';
            map[Paddle1TopPos][2] = ' ';
            Paddle1TopPos += 1;
            Paddle1BottomPos = Paddle1TopPos + (PADDLE1_LENGTH - 1);
        } else if(moveKey == 'w') { //upward movement
            if(Paddle1TopPos == 1) {
                for(int i = Paddle1TopPos; i <= Paddle1BottomPos; i++) {
                    map[i][1] = '[';
                    map[i][2] = ']';
                }
                continue;
            }
            map[Paddle1BottomPos][1] = ' ';
            map[Paddle1BottomPos][2] = ' ';
            Paddle1TopPos -= 1;
            Paddle1BottomPos = Paddle1TopPos + (PADDLE1_LENGTH - 1);
        } else if(moveKey == 'j') { //downward movement
            if(Paddle2BottomPos == MAP_HEIGHT - 2) {
                for(int i = Paddle2TopPos; i <= Paddle2BottomPos; i++) {
                    map[i][MAP_WIDTH - 3] = '[';
                    map[i][MAP_WIDTH - 2] = ']';
                }
                continue;
            }
            map[Paddle2TopPos][MAP_WIDTH - 3] = ' ';
            map[Paddle2TopPos][MAP_WIDTH - 2] = ' ';
            Paddle2TopPos += 1;
            Paddle2BottomPos = Paddle2TopPos + (PADDLE2_LENGTH - 1);
        } else if(moveKey == 'k') { //upward movement
            if(Paddle2TopPos == 1) {
                for(int i = Paddle2TopPos; i <= Paddle2BottomPos; i++) {
                    map[i][MAP_WIDTH - 3] = '[';
                    map[i][MAP_WIDTH - 2] = ']';
                }
                continue;
            }
            map[Paddle2BottomPos][MAP_WIDTH - 3] = ' ';
            map[Paddle2BottomPos][MAP_WIDTH - 2] = ' ';
            Paddle2TopPos -= 1;
            Paddle2BottomPos = Paddle2TopPos + (PADDLE2_LENGTH - 1);
        } else if(moveKey == 'r') { //reset scores
            player1Score = 0;
            player2Score = 0;
        }

        for(int i = Paddle1TopPos; i <= Paddle1BottomPos; i++) {
            map[i][1] = '[';
            map[i][2] = ']';
        }
        for(int i = Paddle2TopPos; i <= Paddle2BottomPos; i++) {
            map[i][MAP_WIDTH - 3] = '[';
            map[i][MAP_WIDTH - 2] = ']';
        }

    }

}

/*
Changes the velocity of the ball
*/
void ballVelocityChange(char (&map)[MAP_HEIGHT][MAP_WIDTH], int &ballPos_row, int &ballPos_column, int &ballVel_row, int &ballVel_column, int &Paddle1TopPos, int &Paddle1BottomPos, int &Paddle2TopPos, int &Paddle2BottomPos, bool &inGame, unsigned &player1Score, unsigned &player2Score) {
    //PADDLE1
    //contact with paddle1 on the right side and ends
    if( (ballPos_column == 3) && (map[ballPos_row][2] == ']') ) {
        ballVel_column = -ballVel_column;
    } else if( (ballPos_column == 1) && ( (map[ballPos_row + 1][1] == '[') || (map[ballPos_row - 1][1] == '[') ) ) {
        ballVel_row = -ballVel_row;
    } else if( (ballPos_column == 2) && ( (map[ballPos_row + 1][2] == ']') || (map[ballPos_row - 1][2] == ']') ) ) {
        ballVel_row = -ballVel_row;
    }
    //contact with paddle1 in corners
    if( (ballVel_row < 0) && (ballVel_column < 0) && (ballPos_row - 1 == Paddle1BottomPos) && (ballPos_column == 3) ) {
        ballVel_column = -ballVel_column;
        ballVel_row = -ballVel_row;
    }
    else if( (ballVel_row > 0) && (ballVel_column < 0) && (ballPos_row + 1 == Paddle1TopPos) && (ballPos_column == 3) ) {
        ballVel_column = -ballVel_column;
        ballVel_row = -ballVel_row;
    }
    //special case of corners contact
    else if( (ballVel_row > 0) && (ballPos_row == MAP_HEIGHT - 2) && (ballVel_column < 0) && (ballPos_row - 1 == Paddle1BottomPos) && (ballPos_column == 3) ) {
        ballVel_column = -ballVel_column;
    }
    else if( (ballVel_row < 0) && (ballPos_row == 1) && (ballVel_column < 0) && (ballPos_row + 1 == Paddle1TopPos) && (ballPos_column == 3) ) {
        ballVel_column = -ballVel_column;
    }

    //PADDLE2
    //contact with paddle2 on the left side and ends
    if( (ballPos_column == (MAP_WIDTH - 4)) && (map[ballPos_row][MAP_WIDTH - 3] == '[') ) {
        ballVel_column = -ballVel_column;
    } else if( (ballPos_column == (MAP_WIDTH - 3)) && ( (map[ballPos_row + 1][MAP_WIDTH - 3] == '[') || (map[ballPos_row - 1][MAP_WIDTH - 3] == '[') ) ) {
        ballVel_row = -ballVel_row;
    } else if( (ballPos_column == (MAP_WIDTH - 2)) && ( (map[ballPos_row + 1][MAP_WIDTH - 2] == ']') || (map[ballPos_row - 1][MAP_WIDTH - 2] == ']') ) ) {
        ballVel_row = -ballVel_row;
    }
    //contact with paddle2 in corners
    if( (ballVel_row < 0) && (ballVel_column > 0) && (ballPos_row - 1 == Paddle2BottomPos) && (ballPos_column == MAP_WIDTH - 4) ) {
        ballVel_column = -ballVel_column;
        ballVel_row = -ballVel_row;
    }
    else if( (ballVel_row > 0) && (ballVel_column > 0) && (ballPos_row + 1 == Paddle2TopPos) && (ballPos_column == MAP_WIDTH - 4) ) {
        ballVel_column = -ballVel_column;
        ballVel_row = -ballVel_row;
    }
    //special case of corners contact
    else if( (ballVel_row > 0) && (ballPos_row == MAP_HEIGHT - 2) && (ballVel_column > 0) && (ballPos_row - 1 == Paddle2BottomPos) && (ballPos_column == MAP_WIDTH - 4) ) {
        ballVel_column = -ballVel_column;
    }
    else if( (ballVel_row < 0) && (ballPos_row == 1) && (ballVel_column < 0) && (ballPos_row + 1 == Paddle2TopPos) && (ballPos_column == MAP_WIDTH - 4) ) {
        ballVel_column = -ballVel_column;
    }

    //ball contact with map boundaries
    if((ballPos_row == 1) || ballPos_row == (MAP_HEIGHT - 2)) {
        ballVel_row = -ballVel_row;
    }
    if(ballPos_column == 1) { // player 2 scores;
        player2Score++;

        std::this_thread::sleep_for(std::chrono::seconds(1));
        ballPos_column = 4;
        ballPos_row = Paddle1TopPos + 3;
    } else if(ballPos_column == (MAP_WIDTH - 2)) { // player 1 scores
        player1Score++;

        std::this_thread::sleep_for(std::chrono::seconds(1));
        ballPos_column =  MAP_WIDTH - 5;
        ballPos_row = Paddle2TopPos + 3;
    }

    //end game by overlapping paddles with ball
    if( (ballPos_column == 1 || ballPos_column == 2) && (ballPos_row <= Paddle1BottomPos && ballPos_row >= Paddle1TopPos) ) { // player 2 scores
        player2Score++;

        std::this_thread::sleep_for(std::chrono::seconds(1));
        ballPos_column = 4;
        ballPos_row = Paddle1TopPos + 3;
    }
    if( (ballPos_column == MAP_WIDTH - 3 || ballPos_column == MAP_WIDTH - 2) && (ballPos_row <= Paddle2BottomPos && ballPos_row >= Paddle2TopPos) ) { // player 1 scores
        player1Score++;

        std::this_thread::sleep_for(std::chrono::seconds(1));
        ballPos_column =  MAP_WIDTH - 5;
        ballPos_row = Paddle2TopPos + 3;
    }
}

/*
Assign boundaries to map
*/
void mapRender(char (&map)[MAP_HEIGHT][MAP_WIDTH]) {
    for(int i = 0; i < MAP_HEIGHT; i++) {
        for(int j = 0; j < MAP_WIDTH; j++) {      
            //boundaries assignation
            if(j == 0 || j == MAP_WIDTH - 1) {
                map[i][j] = '|';
            } else if( (i == 0 && (j != 0 || i != MAP_WIDTH - 1)) || (i == MAP_HEIGHT - 1 && (j != 0 || i != MAP_WIDTH - 1)) ) {
                map[i][j] = '-';
            //space assignaion
            } else {
                map[i][j] = ' ';
            }
        }
    }
}

/*
Draws the map and updates ball position
*/
void ballPosition(char (&map)[MAP_HEIGHT][MAP_WIDTH], int &ballPos_row, int &ballPos_column, int &ballVel_row, int &ballVel_column, int &Paddle1TopPos, int &Paddle1BottomPos, int &Paddle2TopPos, int &Paddle2BottomPos, bool &inGame, unsigned &player1Score, unsigned &player2Score) {

    int i = 0;
    int j = 0;

    // show score
    std::cout << "Player 1: " << std::setw(MAP_WIDTH - 22) << std::setiosflags(std::ios::left) << player1Score << "Player 2: " << player2Score;

    map[ballPos_row][ballPos_column] = '*';
    for(i = 0; i < MAP_HEIGHT; i++) {
        std::cout << "\n";
        for(j = 0; j < MAP_WIDTH; j++) {
            std::cout << map[i][j];
        }
    }
    map[ballPos_row][ballPos_column] = ' ';

    ballPos_row += ballVel_row;
    ballPos_column += ballVel_column;
    ballVelocityChange(map, ballPos_row, ballPos_column, ballVel_row, ballVel_column, Paddle1TopPos, Paddle1BottomPos, Paddle2TopPos, Paddle2BottomPos, inGame, player1Score, player2Score);

    //frame timer
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
}


int main()
{
    // Constants to control initial state of the game
    const int PADDLE1_INIT_POSITION_TOP = 1;
    const int PADDLE1_INIT_POSITION_BOTTOM = PADDLE1_INIT_POSITION_TOP + (PADDLE1_LENGTH - 1);
    const int PADDLE2_INIT_POSITION_TOP = 1;
    const int PADDLE2_INIT_POSITION_BOTTOM = PADDLE2_INIT_POSITION_TOP + (PADDLE2_LENGTH - 1);

    // variable initialization
    int Paddle1TopPos = PADDLE1_INIT_POSITION_TOP;
    int Paddle1BottomPos = PADDLE1_INIT_POSITION_BOTTOM;
    int Paddle2TopPos = PADDLE2_INIT_POSITION_TOP;
    int Paddle2BottomPos = PADDLE2_INIT_POSITION_BOTTOM;

    int ballPos_row = BALL_INIT_POSITION_ROW; 
    int ballPos_column = BALL_INIT_POSITION_COLUMN;

    int ballVel_row = BALL_INIT_ROW_VELOCITY;
    int ballVel_column = BALL_INIT_COLUMN_VELOCITY;

    char map[MAP_HEIGHT][MAP_WIDTH];

    bool inGame = true;
    char moveKey;

    // bool player1Win = false;
    // bool player2Win = false;

    unsigned player1Score = 0;
    unsigned player2Score = 0;

    startMenu();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    //game stuff
    system("cls");
    mapRender(map);

    // arguments passed using a lambda
    std::thread PaddlesThread([&map, &Paddle1TopPos, &Paddle1BottomPos, &Paddle2TopPos, &Paddle2BottomPos, &inGame, &moveKey, &player1Score, &player2Score]() {
        paddlesMove(map, Paddle1TopPos, Paddle1BottomPos, Paddle2TopPos, Paddle2BottomPos, inGame, moveKey, player1Score, player2Score);
    });

    while(inGame) {
        ballPosition(map, ballPos_row, ballPos_column, ballVel_row, ballVel_column, Paddle1TopPos, Paddle1BottomPos, Paddle2TopPos, Paddle2BottomPos, inGame, player1Score, player2Score);
        system("cls");
    }

    system("pause");
    exit(1);

    return 0;
}