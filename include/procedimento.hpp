#ifndef PROCEDIMENTO_HPP
#define PROCEDIMENTO_HPP

class Procedimento {
private:
  double tempo_triagem;
  int numero_triagem;
  int estado_triagem; // 0 para ocioso e 1 para livre
  int tempo_ocioso_triagem;
  int tempo_utilizado_triagem;
  double tempo_atendimento;
  int numero_atendimento;
  int estado_atendimento; // 0 para ocioso e 1 para livre
  int tempo_ocioso_atendimento;
  int tempo_utilizado_atendimento;
  double tempo_medidas_hospitalares;
  int numero_medidas_hospitalares;
  int estado_medidas_hospitalares; // 0 para ocioso e 1 para livre
  int tempo_ocioso_medidas_hospitalares;
  int tempo_utilizado_medidas_hospitalares;
  double tempo_testes_laboratorio;
  int numero_testes_laboratorio;
  int estado_testes_laboratorio; // 0 para ocioso e 1 para livre
  int tempo_ocioso_testes_laboratorio;
  int tempo_utilizado_testes_laboratorio;
  double tempo_exames_imagem;
  int numero_exames_imagem;
  int estado_exames_imagem; // 0 para ocioso e 1 para livre
  int tempo_ocioso_exames_imagem;
  int tempo_utilizado_exames_imagem;
  double tempo_instrumentos;
  int numero_instrumentos;
  int estado_instrumentos; // 0 para ocioso e 1 para livre
  int tempo_ocioso_instrumentos;
  int tempo_utilizado_instrumentos;

public:
  Procedimento();
  void setTempoTriagem(double tempo);
  void setNumeroTriagem(int numero);

  void setTempoAtendimento(double tempo);
  void setNumeroAtendimento(int numero);

  void setTempoMedidas(double tempo);
  void setNumeroMedidas(int numero);

  void setTempoTestes(double tempo);
  void setNumeroTestes(int numero);

  void setTempoExames(double tempo);
  void setNumeroExames(int numero);

  void setTempoInstrumentos(double tempo);
  void setNumeroInstrumentos(int numero);

  double getTempoTriagem() const;
int getNumeroTriagem() const;

double getTempoAtendimento() const;
int getNumeroAtendimento() const;

double getTempoMedidas() const;
int getNumeroMedidas() const;

double getTempoTestes() const;
int getNumeroTestes() const;

double getTempoExames() const;
int getNumeroExames() const;

double getTempoInstrumentos() const;
int getNumeroInstrumentos() const;
};

#endif