#include "../include/procedimento.hpp"

Procedimento::Procedimento() : estado_triagem(1), estado_atendimento(1), estado_medidas_hospitalares(1), estado_testes_laboratorio(1), estado_exames_imagem(1), estado_instrumentos(1) {}

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

int Procedimento::getEstadoTriagem() const {
    return estado_triagem;
}

void Procedimento::alternarEstadoTriagem() {
    if (estado_triagem == 0) {
        estado_triagem = 1;
    } else {
        estado_triagem = 0;
    }
}

int Procedimento::getEstadoAtendimento() const {
    return estado_atendimento;
}

void Procedimento::alternarEstadoAtendimento() {
    if (estado_atendimento == 0) {
        estado_atendimento = 1;
    } else {
        estado_atendimento = 0;
    }
}

int Procedimento::getEstadoMedidas() const {
    return estado_medidas_hospitalares;
}

void Procedimento::alternarEstadoMedidas() {
    if (estado_medidas_hospitalares == 0) {
        estado_medidas_hospitalares = 1;
    } else {
        estado_medidas_hospitalares = 0;
    }
}

int Procedimento::getEstadoTestes() const {
    return estado_testes_laboratorio;
}

void Procedimento::alternarEstadoTestes() {
    if (estado_testes_laboratorio == 0) {
        estado_testes_laboratorio = 1;
    } else {
        estado_testes_laboratorio = 0;
    }
}

int Procedimento::getEstadoExames() const {
    return estado_exames_imagem;
}

void Procedimento::alternarEstadoExames() {
    if (estado_exames_imagem == 0) {
        estado_exames_imagem = 1;
    } else {
        estado_exames_imagem = 0;
    }
}

int Procedimento::getEstadoInstrumentos() const {
    return estado_instrumentos;
}

void Procedimento::alternarEstadoInstrumentos() {
    if (estado_instrumentos == 0) {
        estado_instrumentos = 1;
    } else {
        estado_instrumentos = 0;
    }
}