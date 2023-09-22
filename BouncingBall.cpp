//FALTA RESOLVER PROBLEMA DE SINCRONICIDAD DE HILOS DE EJECUCIÓN
#include <iostream>
#include <thread>
#include <conio.h>

const int PADDLE1_LENGTH = 3;
const int PADDLE2_LENGTH = 3;
const int PADDLE1_INIT_POSITION_TOP = 1;
const int PADDLE1_INIT_POSITION_BOTTOM = PADDLE1_INIT_POSITION_TOP + (PADDLE1_LENGTH - 1); //suma ya que la matríz del mapa es similar a un sistema coordenado rotado -45°
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

const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 7;
char map[MAP_HEIGHT][MAP_WIDTH];

//i y j para renderizar mapa
int i = 0;
int j = 0;


/*
Función que controla el movimiento del paddle 1
*/
void paddle1Move() {
    bool inGame = true;
    char moveKey;
    
    //dibuja paddle1 en su posición inicial antes de que se introdezca algún caracter
    for(int i = Paddle1TopPos; i <= Paddle1BottomPos; i++) {
        map[i][1] = '[';
        map[i][2] = ']';
    }
    

    while(inGame) {
        moveKey = getch();

        if(moveKey == 's') { //movimiento hacia abajo
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
        }
        if(moveKey == 'w') { //movimiento hacia arriba
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
        }

        for(int i = Paddle1TopPos; i <= Paddle1BottomPos; i++) {
            map[i][1] = '[';
            map[i][2] = ']';
        }

    }

}

/*
Función que controla el movimiento del paddle 2
*/
void paddle2Move() {
    bool inGame = true;
    char moveKey;
    
    //dibuja paddle1 en su posición inicial antes de que se introdezca algún caracter
    for(int i = Paddle2TopPos; i <= Paddle2BottomPos; i++) {
        map[i][MAP_WIDTH - 3] = '[';
        map[i][MAP_WIDTH - 2] = ']';
    }
    

    while(inGame) {
        moveKey = getch();

        if(moveKey == 'j') { //movimiento hacia abajo
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
        }
        if(moveKey == 'k') { //movimiento hacia arriba
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

        for(int i = Paddle2TopPos; i <= Paddle2BottomPos; i++) {
            map[i][MAP_WIDTH - 3] = '[';
            map[i][MAP_WIDTH - 2] = ']';
        }

    }

}

/*
Cambia la velocidad de la pelota cuando se requiere
*/
void ballVelocityChange() { //faltaba cuando la pelota se acercaba a los paddles por las esquinas
    //paddle1
    //contacto con el paddle1 cara interior
    if( (ballPos_column == 3) && (map[ballPos_row][2] == ']') ) {
        ballVel_column = -ballVel_column;
    }
    if( (ballPos_column == 1) && ( (map[ballPos_row + 1][1] == '[') || (map[ballPos_row - 1][1] == '[') ) ) {
            ballVel_row = -ballVel_row;
    }
    if( (ballPos_column == 2) && ( (map[ballPos_row + 1][2] == ']') || (map[ballPos_row - 1][2] == ']') ) ) {
            ballVel_row = -ballVel_row;
    }
    //contacto por las esquinas de los paddles funciona salvo por caso especial
    if( (ballVel_row < 0) && (ballVel_column < 0) && (ballPos_row - 1 == Paddle1BottomPos) && (ballPos_column == 3) ) {
        ballVel_column = -ballVel_column;
        ballVel_row = -ballVel_row;
    }
    if( (ballVel_row > 0) && (ballVel_column < 0) && (ballPos_row + 1 == Paddle1TopPos) && (ballPos_column == 3) ) {
        ballVel_column = -ballVel_column;
        ballVel_row = -ballVel_row;
    }
    //caso especial: pelota llega a techo o piso y además se sitúa en esquina de paddel superior o inferior, respectivamente
    if( (ballVel_row > 0) && (ballPos_row == MAP_HEIGHT - 2) && (ballVel_column < 0) && (ballPos_row - 1 == Paddle1BottomPos) && (ballPos_column == 3) ) {
        ballVel_column = -ballVel_column;
        // ballVel_row = -ballVel_row; //no se invierte velocidad en filas ya que eso lo hará el contacto con el piso
    }
    if( (ballVel_row < 0) && (ballPos_row == 1) && (ballVel_column < 0) && (ballPos_row + 1 == Paddle1TopPos) && (ballPos_column == 3) ) {
        ballVel_column = -ballVel_column;
        // ballVel_row = -ballVel_row; //no se invierte velocidad en filas ya que eso lo hará el contacto con el techo 
    }

    //paddle2
    //contacto con el paddle2 cara interior
    if( (ballPos_column == (MAP_WIDTH - 4)) && (map[ballPos_row][MAP_WIDTH - 3] == '[') ) {
        ballVel_column = -ballVel_column;
    }
    if( (ballPos_column == (MAP_WIDTH - 3)) && ( (map[ballPos_row + 1][MAP_WIDTH - 3] == '[') || (map[ballPos_row - 1][MAP_WIDTH - 3] == '[') ) ) {
            ballVel_row = -ballVel_row;
    }
    if( (ballPos_column == (MAP_WIDTH - 2)) && ( (map[ballPos_row + 1][MAP_WIDTH - 2] == ']') || (map[ballPos_row - 1][MAP_WIDTH - 2] == ']') ) ) {
            ballVel_row = -ballVel_row;
    }
    //contacto por las esquinas de los paddles funciona salvo por caso especial
    if( (ballVel_row < 0) && (ballVel_column > 0) && (ballPos_row - 1 == Paddle1BottomPos) && (ballPos_column == MAP_WIDTH - 4) ) {
        ballVel_column = -ballVel_column;
        ballVel_row = -ballVel_row;
    }
    if( (ballVel_row > 0) && (ballVel_column > 0) && (ballPos_row + 1 == Paddle1TopPos) && (ballPos_column == MAP_WIDTH - 4) ) {
        ballVel_column = -ballVel_column;
        ballVel_row = -ballVel_row;
    }
    //caso especial: pelota llega a techo o piso y además se sitúa en esquina de paddel superior o inferior, respectivamente
    if( (ballVel_row > 0) && (ballPos_row == MAP_HEIGHT - 2) && (ballVel_column > 0) && (ballPos_row - 1 == Paddle1BottomPos) && (ballPos_column == MAP_WIDTH - 4) ) {
        ballVel_column = -ballVel_column;
        // ballVel_row = -ballVel_row; //no se invierte velocidad en filas ya que eso lo hará el contacto con el piso
    }
    if( (ballVel_row < 0) && (ballPos_row == 1) && (ballVel_column < 0) && (ballPos_row + 1 == Paddle1TopPos) && (ballPos_column == MAP_WIDTH - 4) ) {
        ballVel_column = -ballVel_column;
        // ballVel_row = -ballVel_row; //no se invierte velocidad en filas ya que eso lo hará el contacto con el techo 
    }

    //contacto de pelota con paredes del mapa - Se calcula al final para no alterar la lógica del contacto con los paddles
    if((ballPos_column == 1) || ballPos_column == (MAP_WIDTH - 2)) {
        ballVel_column = -ballVel_column;
    }
    if((ballPos_row == 1) || ballPos_row == (MAP_HEIGHT - 2)) {
        ballVel_row = -ballVel_row;
    }

}

/*
Solo carga los bordes de mapa y dibuja a la pelota en su posición incial
*/
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

/*
Dibuja todo el mapa dado por mapRender() y actualiza la posición de la pelota
*/
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

    //ballVelocityChange(); //si cambio la velocidad aquí el programa se cierra
    map[ballPos_row][ballPos_column] = ' ';
    ballPos_row += ballVel_row;
    ballPos_column += ballVel_column;
    ballVelocityChange(); //si cambio la velocidad aquí el programa se detiene

    //frame timer
    std::this_thread::sleep_for(0.05s); //como le pongo el tiempo como variable
}


int main()
{
    mapRender();

    //puedo poner ambos paddles en una sola función pero intentaré solucionar el problema de sincronicidad entre los paddles para moverse
    std::thread Paddle1Thread(paddle1Move);
    std::thread Paddle2Thread(paddle2Move);

    while(1) {
        ballPosition();
        system("cls");
    }
    
    system("pause");
    return 0;
}