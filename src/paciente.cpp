#include "../include/paciente.hpp"

// Construtor que inicializa os atributos com valor 0
Paciente::Paciente() 
    : 
      estado_atual(1),
      tempo_ocioso(0), 
      tempo_atendido(0) { }

void Paciente::setId(std::string _id) { this->id = _id; }
const std::string Paciente::getId() const { return id; }

void Paciente::setAlta(int _alta) { this->alta = _alta; }
int Paciente::getAlta() { return alta; }

void Paciente::setAno(int _ano) { this->ano = _ano; }
int Paciente::getAno() const { return ano; }

void Paciente::setMes(int _mes) { this->mes = _mes; }
int Paciente::getMes() const { return mes; }

void Paciente::setDia(int _dia) { this->dia = _dia; }
int Paciente::getDia() const { return dia; }

void Paciente::setHora(int _hora) { this->hora = _hora; }
int Paciente::getHora() const { return hora; }

void Paciente::setGrau_de_urgencia(int _grau_de_urgencia) { this->grau_de_urgencia = _grau_de_urgencia; }
int Paciente::getGrau_de_urgencia() const { return grau_de_urgencia; }

void Paciente::setNum_medidas_hospitalares(int _num_medidas_hospitalares) { this->num_medidas_hospitalares = _num_medidas_hospitalares; }
int Paciente::getNum_medidas_hospitalares() { return num_medidas_hospitalares; }
void Paciente::decrementaMedidas() {
  num_medidas_hospitalares--;
}

void Paciente::setNum_testes_de_laboratorio(int _num_testes_de_laboratorio) { this->num_testes_de_laboratorio = _num_testes_de_laboratorio; }
int Paciente::getNum_testes_de_laboratorio() { return num_testes_de_laboratorio; }
void Paciente::decrementaTestes() {
  num_testes_de_laboratorio--;
}

void Paciente::setNum_exames_de_imagem(int _num_exames_de_imagem) { this->num_exames_de_imagem = _num_exames_de_imagem; }
int Paciente::getNum_exames_de_imagem() { return num_exames_de_imagem; }
void Paciente::decrementaExames() {
  num_exames_de_imagem--;
}

void Paciente::setNum_instrumentos(int _num_instrumentos) { this->num_instrumentos = _num_instrumentos; }
int Paciente::getNum_instrumentos() { return num_instrumentos; }
void Paciente::decrementaInstrumentos() {
  num_instrumentos--;
}

void Paciente::setEstado_atual(int _estado_atual) { this->estado_atual = _estado_atual; }
int Paciente::getEstado_atual() { return estado_atual; }

void Paciente::setTempo_ocioso(float _tempo_ocioso) { this->tempo_ocioso += _tempo_ocioso; }
float Paciente::getTempo_ocioso() { return tempo_ocioso; }

void Paciente::setTempo_atendido(float _tempo_atendido) { this->tempo_atendido = _tempo_atendido + getTempo_atendido(); }
float Paciente::getTempo_atendido() { return tempo_atendido; }

float Paciente::somaDoTempo() { return (hora + tempo_ocioso + tempo_atendido); } // somar a hora atual + tempo ocioso + tempo atendido

float Paciente::getTempo_atendido_final() const {
  return tempo_atendido_final;
}
void Paciente::setTempo_Atendido_Final(float tempo_atendido_final_) {
  this->tempo_atendido_final = tempo_atendido_final_;
}