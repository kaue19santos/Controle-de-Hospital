#ifndef FILA_HPP
#define FILA_HPP

#include "paciente.hpp"

class Fila {
    private:
        Paciente* pacientes; //elementos
        int front; // posicao do primeiro elemento na fila de espera
        int size; // tamanho atual
        int capacity; // capacidade máxima da fila
        bool pode_redimensionar; // verifica se a fila tem um limite máximo
    public:
        Fila(int c); // construtor, c é a capacidade da fila
        ~Fila(); // Libera a memória do array.
        void enfileira(Paciente& paciente);
        void desenfileira(); //deletar primeiro elemento da fila
        void desenfileiraPelaPosicao(int posicao); 
        void imprime(); // funcao para imprimir a fila, util enquanto desenvolvo o código para testar se a fila está apresentando o comportamento esperado
        Paciente getFront(); // retorna o primeiro elemento da fila
        bool hasSpace(); // verifica se há espaço na fila
        bool isEmpty(); // verifica se a fila está vazia
        int getSize() const; // retorna o tamanho atual da fila
        bool mesmaDataHora(const Paciente& paciente1, const Paciente& paciente2) const; // verifica se dois pacientes possuem a mesma data e hora de chegada
        void OrdenaPorGrauDeUrgencia(); // ordena a fila por grau de urgência
        Paciente& getPaciente(int i) const; // pega paciente pela posição na fila
        int getHoraFront(); // pega a hora do primeiro elemento na fila
        void setPodeRedimensionar(bool permissao); // fala se a fila tem tamanho estático ou não
        void OrdenaPorID(); // Função para ordenar a fila por ID
        void OrdenaPorHora(); //Função para ordenar a fila por hora
        void organizaPorHora(); //Função para organizar a fila por hora
};

Paciente encontrarPacienteComMenorTempo(const Fila& vermelho, const Fila& amarelo, const Fila& verde);
Paciente encontrarPacienteComMenorTempoTriagem(const Fila& triagem);


#endif