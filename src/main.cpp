#include <fstream>
#include <iostream>
#include <string>

#include "../include/escalonador.hpp"
#include "../include/fila.hpp"
#include "../include/procedimento.hpp"

std::ifstream CarregaArquivo(char *nomeArquivo) {
  std::ifstream arquivo(nomeArquivo);
  if (!arquivo.is_open()) {
    std::cout << "Arquivo não foi aberto com sucesso" << std::endl;
    return std::ifstream(); // retorna arquivo vazio
  }
  return arquivo;
}

int PreencheProcedimento(Procedimento &procedimentos, char *nomeArquivo,
                         int &num_pacientes, std::ifstream &arquivo) {
  if (!arquivo.is_open()) { // verificando se o arquivo foi aberto com sucesso,
                            // caso não retorna uma mensagem de erro e para o
                            // programa
    std::cout << "Arquivo não foi aberto com sucesso" << std::endl;
    return -1;
  } else {
    std::cout << "Arquivo aberto com sucesso" << std::endl;
  }

  // agora vou inserir as informações referentes ao TAD Procedimento

  double tempo_triagem = 0, tempo_atendimento, tempo_medidas, tempo_testes,
         tempo_exames, tempo_instrumentos;
  int numero_triagem, numero_atendimento, numero_medidas, numero_testes,
      numero_exames, numero_instrumentos;

  arquivo >> tempo_triagem >> numero_triagem;
  procedimentos.setTempoTriagem(tempo_triagem);
  procedimentos.setNumeroTriagem(numero_triagem);

  arquivo >> tempo_atendimento >> numero_atendimento;
  procedimentos.setTempoAtendimento(tempo_atendimento);
  procedimentos.setNumeroAtendimento(numero_atendimento);

  arquivo >> tempo_medidas >> numero_medidas;
  procedimentos.setTempoMedidas(tempo_medidas);
  procedimentos.setNumeroMedidas(numero_medidas);

  arquivo >> tempo_testes >> numero_testes;
  procedimentos.setTempoTestes(tempo_testes);
  procedimentos.setNumeroTestes(numero_testes);

  arquivo >> tempo_exames >> numero_exames;
  procedimentos.setTempoExames(tempo_exames);
  procedimentos.setNumeroExames(numero_exames);

  arquivo >> tempo_instrumentos >> numero_instrumentos;
  procedimentos.setTempoInstrumentos(tempo_instrumentos);
  procedimentos.setNumeroInstrumentos(numero_instrumentos);

  arquivo >> num_pacientes;

  std::cout << procedimentos.getTempoTriagem() << " "
            << procedimentos.getNumeroTriagem() << std::endl;

  std::cout << procedimentos.getTempoAtendimento() << " "
            << procedimentos.getNumeroAtendimento() << std::endl;

  std::cout << procedimentos.getTempoMedidas() << " "
            << procedimentos.getNumeroMedidas() << std::endl;

  std::cout << procedimentos.getTempoTestes() << " "
            << procedimentos.getNumeroTestes() << std::endl;

  std::cout << procedimentos.getTempoExames() << " "
            << procedimentos.getNumeroExames() << std::endl;

  std::cout << procedimentos.getTempoInstrumentos() << " "
            << procedimentos.getNumeroInstrumentos() << std::endl;

  std::cout << num_pacientes << std::endl;

  return 0;
};

void PreencheEscalonador(Escalonador &escalonador, std::ifstream &arquivo,
                         int num_pacientes) {
  int i = 0;
  while (i < num_pacientes) {
    // atributos do paciente
    Paciente paciente;
    std::string id;
    int alta, ano, mes, dia, hora, grau_de_urgencia, num_medidas_hospitalares,
        num_testes_de_laboratorio, num_exames_de_imagem, num_instrumentos;

    arquivo >> id >> alta >> ano >> mes >> dia >> hora >> grau_de_urgencia >>
        num_medidas_hospitalares >> num_testes_de_laboratorio >>
        num_exames_de_imagem >> num_instrumentos;

    paciente.setId(id);
    paciente.setAlta(alta);
    paciente.setAno(ano);
    paciente.setMes(mes);
    paciente.setDia(dia);
    paciente.setHora(hora);
    paciente.setGrau_de_urgencia(grau_de_urgencia);
    paciente.setNum_medidas_hospitalares(num_medidas_hospitalares);
    paciente.setNum_testes_de_laboratorio(num_testes_de_laboratorio);
    paciente.setNum_exames_de_imagem(num_exames_de_imagem);
    paciente.setNum_instrumentos(num_instrumentos);
    escalonador.Inserir(paciente);
    i++;
  }
}

int main(int argc, char **argv) {
  char *nomeArquivo = argv[1];
  Procedimento procedimentos;
  int num_pacientes = 0;
  std::ifstream arquivo = CarregaArquivo(nomeArquivo);
  if (!arquivo.is_open()) {
    return -1;
  }
  PreencheProcedimento(
      procedimentos, nomeArquivo, num_pacientes,
      arquivo); // lendo os dados do procedimento e o numero de pacientes

  Escalonador escalonador(num_pacientes);

  PreencheEscalonador(escalonador, arquivo, num_pacientes);

  // testando se o minheap foi aplicado corretamente
  escalonador.Imprimir();

  std::cout << "Testando a fila" << std::endl;

  // inicializando as filas
  Fila triagem(procedimentos.getNumeroTriagem());
  Fila atendimento_vermelho(procedimentos.getNumeroAtendimento());
  Fila atendimento_amarelo(procedimentos.getNumeroAtendimento());
  Fila atendimento_verde(procedimentos.getNumeroAtendimento());
  Fila medidas_vermelho(procedimentos.getNumeroMedidas());
  Fila medidas_amarelo(procedimentos.getNumeroMedidas());
  Fila medidas_verde(procedimentos.getNumeroMedidas());
  Fila testes_vermelho(procedimentos.getNumeroTestes());
  Fila testes_amarelo(procedimentos.getNumeroTestes());
  Fila testes_verde(procedimentos.getNumeroTestes());
  Fila exames_vermelho(procedimentos.getNumeroExames());
  Fila exames_amarelo(procedimentos.getNumeroExames());
  Fila exames_verde(procedimentos.getNumeroExames());
  Fila instrumentos_vermelho(procedimentos.getNumeroInstrumentos());
  Fila instrumentos_amarelo(procedimentos.getNumeroInstrumentos());
  Fila instrumentos_verde(procedimentos.getNumeroInstrumentos());

  while (!escalonador.isEmpty()) { // enquanto houver pacientes no escalonador
    if (triagem.hasSpace()) {      // se houver espaço na fila de triagem
      Paciente paciente = escalonador.Remover();
      triagem.enfileira(paciente); // insere paciente na fila de triagem
      std::cout << "Paciente inserido na fila da triagem: " << paciente.getId()
                << std::endl;
    }
    // inserir pacientes na fila de atendimento
    if (!triagem.isEmpty() &&
        (atendimento_vermelho.getSize() + atendimento_amarelo.getSize() +
         atendimento_verde.getSize()) <
            procedimentos.getNumeroAtendimento()) { // se houver pacientes na
                                                    // fila de triagem e espaço
                                                    // na fila de atendimento
      Paciente paciente_triagem =
          triagem.getFront(); // pega o paciente da frente da fila de triagem
      triagem.desenfileira(); // remove o paciente da fila de triagem
      if (paciente_triagem.getGrau_de_urgencia() == 2) {
        atendimento_vermelho.enfileira(paciente_triagem);
      } else if (paciente_triagem.getGrau_de_urgencia() == 1) {
        atendimento_amarelo.enfileira(paciente_triagem);
      } else {
        atendimento_verde.enfileira(paciente_triagem);
      }
      std::cout << "Paciente removido da fila da triagem e inserido na fila de atendimento: "
                << paciente_triagem.getId() << std::endl;
    }
    // inserir pacientes na fila das medidas hospitalares
    if ((!atendimento_vermelho.isEmpty() || !atendimento_amarelo.isEmpty() ||
         !atendimento_verde.isEmpty()) &&
        (medidas_vermelho.getSize() + medidas_amarelo.getSize() +
         medidas_verde.getSize()) <
            procedimentos.getNumeroMedidas()) { // se houver pacientes na fila
                                                // de atendimento e espaço na
                                                // fila de medidas
      Paciente paciente_atendimento;
      if (!atendimento_vermelho.isEmpty()) {
        paciente_atendimento = atendimento_vermelho.getFront();
        atendimento_vermelho.desenfileira();
        medidas_vermelho.enfileira(paciente_atendimento);
      } else if (!atendimento_amarelo.isEmpty()) {
        paciente_atendimento = atendimento_amarelo.getFront();
        atendimento_amarelo.desenfileira();
        medidas_amarelo.enfileira(paciente_atendimento);
      } else {
        paciente_atendimento = atendimento_verde.getFront();
        atendimento_verde.desenfileira();
        medidas_verde.enfileira(paciente_atendimento);
      }
      std::cout << "Paciente removido da fila de atendimento e inserido na fila de medidas: "
                << paciente_atendimento.getId() << std::endl;
    }
    // inserir pacientes na fila de testes
    if ((!medidas_vermelho.isEmpty() || !medidas_amarelo.isEmpty() ||
         !medidas_verde.isEmpty()) &&
        (testes_vermelho.getSize() + testes_amarelo.getSize() +
         testes_verde.getSize()) < procedimentos.getNumeroTestes()) {
      Paciente paciente_medidas;
      if (!medidas_vermelho.isEmpty()) {
        paciente_medidas = medidas_vermelho.getFront();
        medidas_vermelho.desenfileira();
        testes_vermelho.enfileira(paciente_medidas);
      } else if (!medidas_amarelo.isEmpty()) {
        paciente_medidas = medidas_amarelo.getFront();
        medidas_amarelo.desenfileira();
        testes_amarelo.enfileira(paciente_medidas);
      } else {
        paciente_medidas = medidas_verde.getFront();
        medidas_verde.desenfileira();
        testes_verde.enfileira(paciente_medidas);
      }
      std::cout << "Paciente removido da fila de medidas e inserido na fila de testes: "
                << paciente_medidas.getId() << std::endl;
    }
    // inserir pacientes na fila dos exames de imagem
    if((!testes_vermelho.isEmpty() || !testes_amarelo.isEmpty() || !testes_verde.isEmpty()) && (exames_vermelho.getSize() + exames_amarelo.getSize() +
         exames_verde.getSize()) <
            procedimentos.getNumeroExames()) {
              Paciente paciente_testes;
              if(!testes_vermelho.isEmpty()) {
                paciente_testes = testes_vermelho.getFront();
                testes_vermelho.desenfileira();
                exames_vermelho.enfileira(paciente_testes);
              } else if (!testes_amarelo.isEmpty()) {
                paciente_testes = testes_amarelo.getFront();
                testes_amarelo.desenfileira();
                exames_amarelo.enfileira(paciente_testes);
              } else {
                paciente_testes = testes_verde.getFront();
                testes_verde.desenfileira();
                exames_amarelo.enfileira(paciente_testes);
              }
              std::cout << "Paciente removido da fila de testes e inserido na fila de exames: " << paciente_testes.getId() << std::endl;
    }
    if((!exames_vermelho.isEmpty() || !exames_amarelo.isEmpty() || !exames_verde.isEmpty()) && (instrumentos_vermelho.getSize() + instrumentos_amarelo.getSize() + instrumentos_verde.getSize()) < procedimentos.getNumeroInstrumentos()) {
      
    }
  }

  triagem.imprime();
  // atendimento.imprime();
  // medidas.imprime();
  // testes.imprime();
  // exames.imprime();
  // instrumentos.imprime();

  arquivo.close();

  return 0;
}
