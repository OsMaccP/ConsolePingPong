#include <iostream>
#include <thread>

int Paddle1TopPos = 2;
int Paddle1BottomPos = 4;
int paddle2TopPos = 2;
int paddle2BottomPos = 4;

const int BALL_INIT_POSITION_ROW = 5;
const int BALL_INIT_POSITION_COLUMN = 5;
int ballPos_row = BALL_INIT_POSITION_ROW; 
int ballPos_column = BALL_INIT_POSITION_COLUMN;

int ballVel_row = 1;
int ballVel_column = 1;    

const int MAP_WIDTH = 40;
const int MAP_HEIGHT = 20;
char map[MAP_HEIGHT][MAP_WIDTH];

int i = 0;
int j = 0;

void ballVelocityChange() {
    if((ballPos_column == 1) || ballPos_column == (MAP_WIDTH - 2)) {
        ballVel_column = -ballVel_column;
    }
    if((ballPos_row == 1) || ballPos_row == (MAP_HEIGHT - 2)) {
        ballVel_row = -ballVel_row;
    }
}

void mapRender() {
    for(i = 0; i < MAP_HEIGHT; i++) {
        std::cout << "\n";
        for(j = 0; j < MAP_WIDTH; j++) {      
            //boundaries assignation
            if(j == 0 || j == MAP_WIDTH - 1) {
                map[i][j] = '|';
                std::cout << map[i][j];
            } else if( (i == 0 && (j != 0 || i != MAP_WIDTH - 1)) || (i == MAP_HEIGHT - 1 && (j != 0 || i != MAP_WIDTH - 1)) ) {
                map[i][j] = '-';
                std::cout << map[i][j];
            } else {
                map[i][j] = ' '; //space assignation
                std::cout << map[i][j];
            }
        }
    }
}

void ballPosition() {

    using namespace std::literals::chrono_literals;

    i = 0;
    j = 0;
    //renderizar aparte para poder manipular posición de la pelota y editar el mapa ya dibujado antes de renderizar
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
    std::this_thread::sleep_for(0.008s);
}


int main()
{
    mapRender();

    while(1) {
        ballPosition();
        system("cls");
    }
    
    system("pause");
    return 0;
}