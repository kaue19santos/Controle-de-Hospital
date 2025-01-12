#ifndef FILA_HPP
#define FILA_HPP

#include "paciente.hpp"

class Fila {
    private:
        Paciente* pacientes; //elementos
        int front; // posicao do primeiro elemento na fila de espera
        int size; // tamanho atual
        int capacity; // capacidade máxima da fila
    public:
        Fila(int c); // construtor, c é a capacidade da fila
        ~Fila(); // Libera a memória do array.
        void enfileira(Paciente paciente);
        void desenfileira(); //deletar primeiro elemento da fila
        void imprime(); // funcao para imprimir a fila, util enquanto desenvolvo o código para testar se a fila está apresentando o comportamento esperado
        Paciente getFront(); // retorna o primeiro elemento da fila
        bool hasSpace(); // verifica se há espaço na fila
        bool isEmpty(); // verifica se a fila está vazia
        int getSize(); // retorna o tamanho atual da fila
};

#endif