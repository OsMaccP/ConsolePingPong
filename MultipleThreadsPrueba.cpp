#include <iostream>
#include <thread>
#include <conio.h>

bool seguir = false;

void imprimirLin() {
    using namespace std::literals::chrono_literals;
    
    while(!seguir) {
        std::cout << "-----------\n\n";
        std::this_thread::sleep_for(1s);
    }
}

void imprimirLet() {
    char a;

    for(int i = 0; !seguir; i++) {
        a = getch();
        std::cout << a;

        if(a == 's') {
            seguir = true;
        }
    }

}

int main()
{
    std::thread hilo1(imprimirLin);
    std::thread hilo2(imprimirLet);

    hilo1.join();
    hilo2.join(); //.join espera a que la ejecución del hilo termine para continuar con el programa

    std::cout << "El programa ha terminado!" << std::endl;
    

    return 0;
}