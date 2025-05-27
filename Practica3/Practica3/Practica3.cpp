#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

const int NUM_HILOS = 5;
const int ITERACIONES = 1000;

int contador = 0;           // Variable compartida
std::mutex mtx;             // Mutex para proteger la sección crítica

void incrementar() {
    for (int i = 0; i < ITERACIONES; ++i) {
        mtx.lock();         // Entrar a la sección crítica
        contador++;         // Modificar la variable compartida
        mtx.unlock();       // Salir de la sección crítica
    }
}

int main() {
    std::vector<std::thread> hilos;

    // Crear los hilos
    for (int i = 0; i < NUM_HILOS; ++i) {
        hilos.emplace_back(incrementar);
    }

    // Esperar a que todos los hilos terminen
    for (auto& hilo : hilos) {
        hilo.join();
    }

    std::cout << "Valor final del contador: " << contador << std::endl;

    return 0;
}
