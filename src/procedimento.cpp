#include "../include/procedimento.hpp"

Procedimento::Procedimento() : estado_triagem(0), tempo_ocioso_triagem(0), tempo_utilizado_triagem(0), estado_atendimento(0), tempo_ocioso_atendimento(0), tempo_utilizado_atendimento(0), estado_medidas_hospitalares(0), tempo_ocioso_medidas_hospitalares(0), tempo_utilizado_medidas_hospitalares(0), estado_testes_laboratorio(0), tempo_ocioso_testes_laboratorio(0), tempo_utilizado_testes_laboratorio(0), estado_exames_imagem(0), tempo_ocioso_exames_imagem(0), tempo_utilizado_exames_imagem(0), estado_instrumentos(0), tempo_ocioso_instrumentos(0), tempo_utilizado_instrumentos(0) {}

void Procedimento::setTempoTriagem(double tempo) {
    tempo_triagem = tempo;
}

void Procedimento::setNumeroTriagem(int numero) {
    numero_triagem = numero;
}

void Procedimento::setTempoAtendimento(double tempo) {
    tempo_atendimento = tempo;
}

void Procedimento::setNumeroAtendimento(int numero) {
    numero_atendimento = numero;
}

void Procedimento::setTempoMedidas(double tempo) {
    tempo_medidas_hospitalares = tempo;
}

void Procedimento::setNumeroMedidas(int numero) {
    numero_medidas_hospitalares = numero;
}

void Procedimento::setTempoTestes(double tempo) {
    tempo_testes_laboratorio = tempo;
}

void Procedimento::setNumeroTestes(int numero) {
    numero_testes_laboratorio = numero;
}

void Procedimento::setTempoExames(double tempo) {
    tempo_exames_imagem = tempo;
}

void Procedimento::setNumeroExames(int numero) {
    numero_exames_imagem = numero;
}

void Procedimento::setTempoInstrumentos(double tempo) {
    tempo_instrumentos = tempo;
}

void Procedimento::setNumeroInstrumentos(int numero) {
    numero_instrumentos = numero;
}

double Procedimento::getTempoTriagem() const {
    return tempo_triagem;
}

int Procedimento::getNumeroTriagem() const {
    return numero_triagem;
}

double Procedimento::getTempoAtendimento() const {
    return tempo_atendimento;
}

int Procedimento::getNumeroAtendimento() const {
    return numero_atendimento;
}

double Procedimento::getTempoMedidas() const {
    return tempo_medidas_hospitalares;
}

int Procedimento::getNumeroMedidas() const {
    return numero_medidas_hospitalares;
}

double Procedimento::getTempoTestes() const {
    return tempo_testes_laboratorio;
}

int Procedimento::getNumeroTestes() const {
    return numero_testes_laboratorio;
}

double Procedimento::getTempoExames() const {
    return tempo_exames_imagem;
}

int Procedimento::getNumeroExames() const {
    return numero_exames_imagem;
}

double Procedimento::getTempoInstrumentos() const {
    return tempo_instrumentos;
}

int Procedimento::getNumeroInstrumentos() const {
    return numero_instrumentos;
}
