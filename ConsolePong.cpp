#include <iostream>
#include <thread>
#include <conio.h>

const int PADDLE1_LENGTH = 3;
const int PADDLE2_LENGTH = 3;
const int PADDLE1_INIT_POSITION_TOP = 1;
const int PADDLE1_INIT_POSITION_BOTTOM = PADDLE1_INIT_POSITION_TOP + (PADDLE1_LENGTH - 1);
const int PADDLE2_INIT_POSITION_TOP = 1;
const int PADDLE2_INIT_POSITION_BOTTOM = PADDLE2_INIT_POSITION_TOP + (PADDLE2_LENGTH - 1);
int Paddle1TopPos = PADDLE1_INIT_POSITION_TOP;
int Paddle1BottomPos = PADDLE1_INIT_POSITION_BOTTOM;
int Paddle2TopPos = PADDLE2_INIT_POSITION_TOP;
int Paddle2BottomPos = PADDLE2_INIT_POSITION_BOTTOM;

const int BALL_INIT_POSITION_ROW = 3;
const int BALL_INIT_POSITION_COLUMN = 3;
int ballPos_row = BALL_INIT_POSITION_ROW; 
int ballPos_column = BALL_INIT_POSITION_COLUMN;

int ballVel_row = 1;
int ballVel_column = 1;    

const int MAP_WIDTH = 20; //20 minimum frequency
const int MAP_HEIGHT = 9; //9 minimum frequency
char map[MAP_HEIGHT][MAP_WIDTH];

bool inGame = true;
char moveKey;

bool player1Win = false;
bool player2Win = false;

//map render
int i = 0;
int j = 0;

/*
Controls the movement of paddles
*/
void paddlesMove() {
    
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
void ballVelocityChange() {
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
    if(ballPos_column == 1) {
        inGame = false;
        player2Win = true;
    } else if(ballPos_column == (MAP_WIDTH - 2)) {
        inGame = false;
        player1Win = true;
    }
    if((ballPos_row == 1) || ballPos_row == (MAP_HEIGHT - 2)) {
        ballVel_row = -ballVel_row;
    }

    //end game by overlapping paddles with ball
    if( (ballPos_column == 1 || ballPos_column == 2) && (ballPos_row <= Paddle1BottomPos && ballPos_row >= Paddle1TopPos) ) {
        inGame = false;
        player2Win = true;
    }
    if( (ballPos_column == MAP_WIDTH - 3 || ballPos_column == MAP_WIDTH - 2) && (ballPos_row <= Paddle2BottomPos && ballPos_row >= Paddle2TopPos) ) {
        inGame = false;
        player1Win = true;
    }
}

/*
Assign boundaries to map
*/
void mapRender() {
    for(i = 0; i < MAP_HEIGHT; i++) {
        for(j = 0; j < MAP_WIDTH; j++) {      
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
void ballPosition() {
    i = 0;
    j = 0;

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
    ballVelocityChange();

    //frame timer
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


int main()
{
    system("cls");
    mapRender();

    std::thread PaddlesThread(paddlesMove);

    while(inGame) {
        ballPosition();
        system("cls");
    }

    system("cls");
    std::cout << "\n";
    if(player1Win) {
        std::cout << "Player1 win!" << std::endl;
    } else if(player2Win) {
        std::cout << "Player2 win!" << std::endl;
    }

    system("pause");
    exit(1);

    return 0;
}