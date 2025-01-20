#include "../include/fila.hpp"
#include <iostream>
#include <limits>


Fila::Fila(int c) {
  pacientes = new Paciente[c];
  front = 0;
  size = 0;
  capacity = c;
  pode_redimensionar = true;
}

Fila::~Fila() {
  delete[] pacientes; // Libera a memória do array.
}

void Fila::enfileira(Paciente& paciente) {
    if (size == capacity) {
        if (pode_redimensionar) {
            // Redimensiona a capacidade da fila, dobrando o tamanho
            capacity *= 2;
            Paciente* nova_fila = new Paciente[capacity];
            for (int i = 0; i < size; i++) {
                nova_fila[i] = pacientes[(front + i) % size];
            }
            delete[] pacientes;
            pacientes = nova_fila;
            front = 0; // Resetamos o front para o início do novo array
        }
    }

    // Adiciona o novo paciente no final da fila
    int fim = (front + size) % capacity;
    pacientes[fim] = paciente;
    size++;
}

void Fila::desenfileira() {
  // passa todos os elementos para a frente
  for (int i = 1; i < size; i++) {
    pacientes[i - 1] = pacientes[i];
  }
  size--;
}

void Fila::desenfileiraPelaPosicao(int posicao) {
  // passa todos os elementos para a frente
  for (int i = posicao; i < size; i++) {
    pacientes[i] = pacientes[i + 1];
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

int Fila::getSize() const {
  return size;
}

bool Fila::mesmaDataHora(const Paciente& paciente1, const Paciente& paciente2) const {
  if (paciente1.getAno() == paciente2.getAno() &&
      paciente1.getMes() == paciente2.getMes() &&
      paciente1.getDia() == paciente2.getDia() &&
      paciente1.getHora() == paciente2.getHora()) {
    return true;
  } else {
    return false;
  }
}

void Fila::OrdenaPorGrauDeUrgencia() {
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (this->mesmaDataHora(pacientes[i],pacientes[j]) &&
                pacientes[i].getGrau_de_urgencia() < pacientes[j].getGrau_de_urgencia()) {
                Paciente temporario = pacientes[i];
                pacientes[i] = pacientes[j];
                pacientes[j] = temporario;
            }
    }
  }
}

Paciente& Fila::getPaciente(int i) const {
    return pacientes[i];
}

int Fila::getHoraFront() { return pacientes[0].getHora(); }

void Fila::setPodeRedimensionar(bool permissao) {
  pode_redimensionar = permissao;
};

Paciente encontrarPacienteComMenorTempo(const Fila& vermelho, const Fila& amarelo, const Fila& verde) {
    float menorTempo = std::numeric_limits<float>::max();
    Paciente pacienteMenorTempo;

    // Verifica cada fila para encontrar o paciente com menor somaDoTempo
    for (int i = 0; i < vermelho.getSize(); i++) {
        Paciente p = vermelho.getPaciente(i);
        if (p.somaDoTempo() < menorTempo) {
            menorTempo = p.somaDoTempo();
            pacienteMenorTempo = p;
        }
    }

    for (int i = 0; i < amarelo.getSize(); i++) {
        Paciente p = amarelo.getPaciente(i);
        if (p.somaDoTempo() < menorTempo) {
            menorTempo = p.somaDoTempo();
            pacienteMenorTempo = p;
        }
    }

    for (int i = 0; i < verde.getSize(); i++) {
        Paciente p = verde.getPaciente(i);
        if (p.somaDoTempo() < menorTempo) {
            menorTempo = p.somaDoTempo();
            pacienteMenorTempo = p;
        }
    }

    return pacienteMenorTempo;
}

bool compararPorID(const Paciente& p1, const Paciente& p2) {
    int id1 = std::stoi(p1.getId());
    int id2 = std::stoi(p2.getId());
    return id1 < id2;
}

// Função para fundir duas sublistas ordenadas
void merge(Paciente arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Criar subarrays temporários
    Paciente L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Mesclar os subarrays
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compararPorID(L[i], R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar elementos restantes, se houver
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Função principal de Merge Sort
void mergeSort(Paciente arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursivamente dividir e ordenar
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Mesclar os dois subarrays
        merge(arr, left, mid, right);
    }
}

void Fila::OrdenaPorID() {
    mergeSort(pacientes, 0, size - 1);
}

bool compararPorHora(const Paciente& p1, const Paciente& p2) {
    int hora1 = p1.getHora();
    int hora2 = p2.getHora();
    if (hora1 == hora2) {
        return compararPorID(p1, p2); // Se as horas forem iguais, compara pelo ID
    }
    return hora1 < hora2; // Caso contrário, compara apenas pela hora
}

// Função para fundir duas sublistas ordenadas
void mergeHora(Paciente arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Criar subarrays temporários
    Paciente L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Mesclar os subarrays
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compararPorHora(L[i], R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar elementos restantes, se houver
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Função principal de Merge Sort
void mergeSortHora(Paciente arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursivamente dividir e ordenar
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Mesclar os dois subarrays
        merge(arr, left, mid, right);
    }
}

void Fila::OrdenaPorHora() {
    mergeSort(pacientes, 0, size - 1);
}

Paciente encontrarPacienteComMenorTempoTriagem(const Fila& triagem) {
    float menorTempo = std::numeric_limits<float>::max();
    Paciente pacienteMenorTempo;

    // Verifica a fila da triagem para encontrar o paciente com menor somaDoTempo
    for (int i = 0; i < triagem.getSize(); i++) {
        Paciente p = triagem.getPaciente(i);
        if (p.somaDoTempo() < menorTempo) {
            menorTempo = p.somaDoTempo();
            pacienteMenorTempo = p;
        }
    }
    return pacienteMenorTempo;
}

void Fila::organizaPorHora() {
    for (int i = 1; i < size; i++) {
        int j = i;
        while (j > 0 && pacientes[j].getHora() < pacientes[j - 1].getHora()) {
            // Trocar pacientes[j] e pacientes[j - 1]
            Paciente temp = pacientes[j];
            pacientes[j] = pacientes[j - 1];
            pacientes[j - 1] = temp;
            j--;
        }
    }
}