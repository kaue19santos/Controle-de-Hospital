#include "../include/fila.hpp"
#include <iostream>

Fila::Fila(int c) {
  pacientes = new Paciente[c];
  front = 0;
  size = 0;
  capacity = c;
}

Fila::~Fila() {
  delete[] pacientes; // Libera a memória do array.
}

void Fila::enfileira(Paciente paciente) {
  // adiciona elemento na fila
  pacientes[front + size] = paciente;
  size++;
}

void Fila::desenfileira() {
  // passa todos os elementos para a frente
  for (int i = 1; i < size; i++) {
    pacientes[i - 1] = pacientes[i];
  }
  size--;
}

void Fila::imprime() {
  if (size == 0) { // verifica se a fila está vazia
    return;
  }

  for (int i = 0; i < size; i++) {
    std::cout << pacientes[i].getId() << " <- ";
  }
}

Paciente Fila::getFront() { 
    return pacientes[front]; 
    }

bool Fila::hasSpace() {
  if (size == capacity) {
    return false;
  } else {
    return true;
  }
}

bool Fila::isEmpty() {
  if (size == 0) {
    return true;
  } else {
    return false;
  }
}

int Fila::getSize() {
  return size;
}