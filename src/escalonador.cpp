#include "../include/escalonador.hpp"
#include <iostream>

Escalonador::Escalonador(int num_pacientes) : num_pacientes(num_pacientes) {
  pacientes = new Paciente[num_pacientes];
  tamanho = 0;
};

Escalonador::~Escalonador() {
  delete[] pacientes; // Libera a memória do array.
};

void Escalonador::Inserir(Paciente paciente) {
  pacientes[tamanho] = paciente;
  int atual = tamanho;
  tamanho++;
  HeapifyPorCima(atual);
};

Paciente Escalonador::Remover() {
  Paciente raiz = pacientes[0];
  for (int i = 0; i < tamanho; i++) {
    pacientes[i] = pacientes[i + 1];
  }
  tamanho = tamanho - 1;
  HeapifyPorBaixo(0);
  return raiz;
};

bool Escalonador::Vazio() {
  if (tamanho == 0) {
    return true;
  } else {
    return false;
  }
};

int Escalonador::GetAncestral(int posicao) { return (posicao - 1) / 2; };

int Escalonador::GetSucessorEsq(int posicao) { return 2 * posicao + 1; };

int Escalonador::GetSucessorDir(int posicao) { return 2 * posicao + 2; };

void Escalonador::HeapifyPorBaixo(int posicao) {
  int menor = posicao;
  int esquerda = GetSucessorEsq(posicao);
  int direita = GetSucessorDir(posicao);

  // Comparar com o sucessor esquerdo
  if (esquerda < tamanho &&
      (pacientes[esquerda].getAno() < pacientes[menor].getAno() ||
       (pacientes[esquerda].getAno() == pacientes[menor].getAno() &&
        pacientes[esquerda].getMes() < pacientes[menor].getMes()) ||
       (pacientes[esquerda].getAno() == pacientes[menor].getAno() &&
        pacientes[esquerda].getMes() == pacientes[menor].getMes() &&
        pacientes[esquerda].getDia() < pacientes[menor].getDia()) ||
       (pacientes[esquerda].getAno() == pacientes[menor].getAno() &&
        pacientes[esquerda].getMes() == pacientes[menor].getMes() &&
        pacientes[esquerda].getDia() == pacientes[menor].getDia() &&
        pacientes[esquerda].getHora() < pacientes[menor].getHora()) ||
       (pacientes[esquerda].getAno() == pacientes[menor].getAno() &&
        pacientes[esquerda].getMes() == pacientes[menor].getMes() &&
        pacientes[esquerda].getDia() == pacientes[menor].getDia() &&
        pacientes[esquerda].getHora() == pacientes[menor].getHora() &&
        pacientes[esquerda].getId() < pacientes[menor].getId()))) {
    menor = esquerda;
  }

  // Comparar com o sucessor direito
  if (direita < tamanho &&
      (pacientes[direita].getAno() < pacientes[menor].getAno() ||
       (pacientes[direita].getAno() == pacientes[menor].getAno() &&
        pacientes[direita].getMes() < pacientes[menor].getMes()) ||
       (pacientes[direita].getAno() == pacientes[menor].getAno() &&
        pacientes[direita].getMes() == pacientes[menor].getMes() &&
        pacientes[direita].getDia() < pacientes[menor].getDia()) ||
       (pacientes[direita].getAno() == pacientes[menor].getAno() &&
        pacientes[direita].getMes() == pacientes[menor].getMes() &&
        pacientes[direita].getDia() == pacientes[menor].getDia() &&
        pacientes[direita].getHora() < pacientes[menor].getHora()) ||
       (pacientes[direita].getAno() == pacientes[menor].getAno() &&
        pacientes[direita].getMes() == pacientes[menor].getMes() &&
        pacientes[direita].getDia() == pacientes[menor].getDia() &&
        pacientes[direita].getHora() == pacientes[menor].getHora() &&
        pacientes[direita].getId() < pacientes[menor].getId()))) {
    menor = direita;
  }

  // Se o menor não for o atual, troca e continua
  if (menor != posicao) {
    Paciente temporario = pacientes[posicao];
    pacientes[posicao] = pacientes[menor];
    pacientes[menor] = temporario;
    HeapifyPorBaixo(menor);
  }
}

void Escalonador::HeapifyPorCima(int posicao) {
  while (posicao > 0) {
    int ancestral = GetAncestral(posicao);
    if (pacientes[ancestral].getAno() > pacientes[posicao].getAno() ||
        (pacientes[ancestral].getAno() == pacientes[posicao].getAno() &&
         pacientes[ancestral].getMes() > pacientes[posicao].getMes()) ||
        (pacientes[ancestral].getAno() == pacientes[posicao].getAno() &&
         pacientes[ancestral].getMes() == pacientes[posicao].getMes() &&
         pacientes[ancestral].getDia() > pacientes[posicao].getDia()) ||
        (pacientes[ancestral].getAno() == pacientes[posicao].getAno() &&
         pacientes[ancestral].getMes() == pacientes[posicao].getMes() &&
         pacientes[ancestral].getDia() == pacientes[posicao].getDia() &&
         pacientes[ancestral].getHora() > pacientes[posicao].getHora()) ||
        (pacientes[ancestral].getAno() == pacientes[posicao].getAno() &&
         pacientes[ancestral].getMes() == pacientes[posicao].getMes() &&
         pacientes[ancestral].getDia() == pacientes[posicao].getDia() &&
         pacientes[ancestral].getHora() == pacientes[posicao].getHora() &&
         pacientes[ancestral].getId() > pacientes[posicao].getId())) {
      // Troca
      Paciente temporario = pacientes[posicao];
      pacientes[posicao] = pacientes[ancestral];
      pacientes[ancestral] = temporario;
      posicao = ancestral;
    } else {
      break;
    }
  }
}

void Escalonador::setNumPacientes(int numero) { num_pacientes = numero; };

void Escalonador::Imprimir() {
  int i = 0;
  while (i < tamanho) {
    std::cout << pacientes[i].getId() << " " << pacientes[i].getAlta() << " "
              << pacientes[i].getAno() << " " << pacientes[i].getMes() << " "
              << pacientes[i].getDia() << " " << pacientes[i].getHora() << " "
              << pacientes[i].getGrau_de_urgencia() << " "
              << pacientes[i].getNum_medidas_hospitalares() << " "
              << pacientes[i].getNum_testes_de_laboratorio() << " "
              << pacientes[i].getNum_exames_de_imagem() << " "
              << pacientes[i].getNum_instrumentos() << " " << std::endl;
    i++;
  }
}

bool Escalonador::isEmpty() {
  if (tamanho == 0) {
    return true;
  } else {
    return false;
  }
}
