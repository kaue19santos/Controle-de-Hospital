#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "paciente.hpp"

class Escalonador {
private:
//metodos para transformar o escalonador em um MinHeap
  int GetAncestral(int posicao);
  int GetSucessorEsq(int posicao);
  int GetSucessorDir(int posicao); 

  int num_pacientes;
  int tamanho;
  Paciente *pacientes; //array

  //Funções necessárias para implementar o Heapify

  void HeapifyPorBaixo(int posicao);
  void HeapifyPorCima(int posicao);

public:
  Escalonador(int num_pacientes); // Aloca a memória do array, função inicializa() do enunciado
  ~Escalonador(); // Libera a memória do array, função finaliza() do enunciado
  void setNumPacientes(int numero);
  int getNumPacientes() {
    return num_pacientes;
  }

  void Inserir(Paciente paciente);

  Paciente Remover();

  //Retorna true caso o heap esteja vazio, false caso contrário.
  bool Vazio();

  //testando o minHeap
  void Imprimir();

  bool isEmpty();
};

#endif