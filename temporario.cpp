#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "../include/escalonador.hpp"
#include "../include/fila.hpp"
#include "../include/procedimento.hpp"

std::ifstream CarregaArquivo(char *nomeArquivo) {
  std::ifstream arquivo(nomeArquivo);
  if (!arquivo.is_open()) {
    std::cout << "Falha ao abrir o arquivo!" << std::endl;
    return std::ifstream(); // retorna arquivo vazio
  }
  return arquivo;
}

int PreencheProcedimento(Procedimento &procedimentos, char *nomeArquivo,
                         int &num_pacientes, std::ifstream &arquivo) {
  if (!arquivo.is_open()) { // verificando se o arquivo foi aberto com sucesso,
                            // caso não retorna uma mensagem de erro e para o
                            // programa
    return -1;
  } else {
  }

  // agora vou inserir as informações referentes ao TAD Procedimento

  float tempo_triagem = 0, tempo_atendimento, tempo_medidas, tempo_testes,
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
    if (paciente.getAlta() == 1) {
      paciente.setNum_medidas_hospitalares(0);
      paciente.setNum_testes_de_laboratorio(0);
      paciente.setNum_exames_de_imagem(0);
      paciente.setNum_instrumentos(0);
    } else {
      paciente.setNum_medidas_hospitalares(num_medidas_hospitalares);
      paciente.setNum_testes_de_laboratorio(num_testes_de_laboratorio);
      paciente.setNum_exames_de_imagem(num_exames_de_imagem);
      paciente.setNum_instrumentos(num_instrumentos);
    }
    escalonador.Inserir(paciente);
    i++;
  }
}

void imprimirHorario(int idPaciente, int dia, int mes, int ano, int horaChegada,
                     float tempoEmHoras, float tempo_atendido,
                     float tempo_ocioso) {
  std::cout << idPaciente << " ";

  // Estrutura para armazenar a hora de chegada
  struct tm chegada = {};
  chegada.tm_year = ano - 1900;  // Ano desde 1900
  chegada.tm_mon = mes - 1;      // Mês começa de 0
  chegada.tm_mday = dia;         // Dia do mês
  chegada.tm_hour = horaChegada; // Hora
  chegada.tm_min = 0;            // Minuto

  // Converter para time_t para manipulação
  time_t tChegada = mktime(&chegada);

  // Estrutura para armazenar a hora de saída
  time_t tSaida =
      tChegada +
      static_cast<int>(
          tempoEmHoras *
          3600); // Adiciona tempo em segundos (3600 segundos em uma hora)
  struct tm *saida = localtime(&tSaida);

  // Formatando e imprimindo os horários
  char bufferChegada[80], bufferSaida[80];
  strftime(bufferChegada, sizeof(bufferChegada), "%a %b %d %H:%M:%S %Y",
           &chegada);
  strftime(bufferSaida, sizeof(bufferSaida), "%a %b %d %H:%M:%S %Y", saida);

  std::cout << bufferChegada << " " << bufferSaida << " ";
  std::cout << std::fixed << std::setprecision(2) << tempoEmHoras << " ";
  std::cout << std::fixed << std::setprecision(2) << tempo_atendido << " ";
  std::cout << std::fixed << std::setprecision(2) << tempo_ocioso << std::endl;
}

int main(int argc, char **argv) {
  char *nomeArquivo = argv[1];
  Procedimento procedimentos;
  int num_pacientes = 0;
  float hora_atual = 0;
  std::ifstream arquivo = CarregaArquivo(nomeArquivo);
  if (!arquivo.is_open()) {
    return -1;
  }
  PreencheProcedimento(
      procedimentos, nomeArquivo, num_pacientes,
      arquivo); // lendo os dados do procedimento e o numero de pacientes

  Escalonador escalonador(num_pacientes);

  PreencheEscalonador(escalonador, arquivo, num_pacientes);

  escalonador.organizaPorHora();
  escalonador.organizaPorID();

  escalonador.Imprimir();

  // atribuindo o tempo atendido final aos pacientes
  for (int i = 0; i < num_pacientes; i++) {
    float tempo_atendido_final = 0;
    Paciente &paciente = escalonador.getPaciente(i);
    tempo_atendido_final =
        ((procedimentos.getTempoTriagem()) +
         (procedimentos.getTempoAtendimento()) +
         (paciente.getNum_medidas_hospitalares() *
          procedimentos.getTempoMedidas()) +
         (paciente.getNum_testes_de_laboratorio() *
          procedimentos.getTempoTestes()) +
         (paciente.getNum_exames_de_imagem() * procedimentos.getTempoExames()) +
         (paciente.getNum_instrumentos() *
          procedimentos.getTempoInstrumentos()));
    paciente.setTempo_Atendido_Final(tempo_atendido_final);
    std::cout << paciente.getId() << std::endl;
    std::cout << paciente.getTempo_atendido_final() << std::endl;
  }
  // inicializando as filas
  Fila triagem(num_pacientes);
  Fila triagem_em_uso(procedimentos.getNumeroTriagem());
  Fila atendimento(num_pacientes);
  Fila atendimento_vermelho(procedimentos.getNumeroAtendimento());
  Fila atendimento_amarelo(procedimentos.getNumeroAtendimento());
  Fila atendimento_verde(procedimentos.getNumeroAtendimento());
  Fila atendimento_em_uso(procedimentos.getNumeroAtendimento());
  atendimento_em_uso.setPodeRedimensionar(false);
  Fila medidas_vermelho(procedimentos.getNumeroMedidas());
  Fila medidas_amarelo(procedimentos.getNumeroMedidas());
  Fila medidas_verde(procedimentos.getNumeroMedidas());
  Fila medidas_em_uso(procedimentos.getNumeroMedidas());
  medidas_em_uso.setPodeRedimensionar(false);
  Fila testes_vermelho(procedimentos.getNumeroTestes());
  Fila testes_amarelo(procedimentos.getNumeroTestes());
  Fila testes_verde(procedimentos.getNumeroTestes());
  Fila testes_em_uso(procedimentos.getNumeroTestes());
  testes_em_uso.setPodeRedimensionar(false);
  Fila exames_vermelho(procedimentos.getNumeroExames());
  Fila exames_amarelo(procedimentos.getNumeroExames());
  Fila exames_verde(procedimentos.getNumeroExames());
  Fila exames_em_uso(procedimentos.getNumeroExames());
  exames_em_uso.setPodeRedimensionar(false);
  Fila instrumentos_vermelho(procedimentos.getNumeroInstrumentos());
  Fila instrumentos_amarelo(procedimentos.getNumeroInstrumentos());
  Fila instrumentos_verde(procedimentos.getNumeroInstrumentos());
  Fila instrumentos_em_uso(procedimentos.getNumeroInstrumentos());
  instrumentos_em_uso.setPodeRedimensionar(false);
  Fila pacientes_pos_alta(num_pacientes);

  // passando todos do escalonador para a fila de triagem
  for (int i = 0; i < num_pacientes; i++) {
    Paciente paciente = escalonador.getPaciente(i);
    triagem.enfileira(paciente); // insere paciente na fila de triagem
  }

  while (!triagem.isEmpty()) { // enquanto houver pacientes na fila de triagem
    if (triagem_em_uso.isEmpty()) { // atualiza a hora pra frente se necessário
      Paciente menor = encontrarPacienteComMenorTempoTriagem(triagem);
      hora_atual =
          menor.somaDoTempo(); // atualiza a hora atual para a hora do paciente
                               // de menor hora na fila de triagem
    }
    std::cout << "Hora antes da triagem: " << hora_atual << std::endl;
    if (triagem_em_uso.hasSpace()) { // enchendo as salas de triagem
      while (triagem_em_uso.hasSpace() && !triagem.isEmpty() &&
             triagem.getFront().somaDoTempo() <=
                 (hora_atual + procedimentos.getTempoTriagem())) {
        Paciente paciente_triagem =
            triagem.getFront(); // pega o paciente da frente da fila de triagem
        triagem_em_uso.enfileira(
            paciente_triagem);  // insere paciente na fila de triagem em uso
        triagem.desenfileira(); // remove o paciente da fila de triagem
        std::cout << "Paciente entrou na sala de triagem: "
                  << paciente_triagem.getId() << std::endl;
      }
    }
    if (!triagem_em_uso.isEmpty()) { // triando os pacientes
      for (int i = 0; i < triagem_em_uso.getSize(); i++) {
        Paciente &paciente_na_triagem = triagem_em_uso.getPaciente(i);
        paciente_na_triagem.setTempo_atendido(procedimentos.getTempoTriagem());
        atendimento.enfileira(paciente_na_triagem);
        std::cout << "Paciente triado e entrou na sala de atendimento: " << paciente_na_triagem.getId() << std::endl;
      }
      while (!triagem_em_uso.isEmpty()) {
        triagem_em_uso.desenfileira();
      }
      hora_atual = hora_atual + procedimentos.getTempoTriagem();
      std::cout << "Hora atual " << hora_atual << std::endl;
      for (int i = 0; i < triagem_em_uso.getSize(); i++) {
        if (hora_atual > triagem_em_uso.getPaciente(i).somaDoTempo()) {
          hora_atual = triagem_em_uso.getPaciente(i).somaDoTempo();
        }
      }
    }
    for (int i = 0; i < triagem.getSize(); i++) {
      Paciente &paciente = triagem.getPaciente(i);
      if ((paciente.somaDoTempo() + 0.0001) < hora_atual) {
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        paciente.setTempo_ocioso(tempo_ocioso);
      } else {
        break;
      }
    }
  }

  for (int i = 0; i < atendimento.getSize(); i++) {
    Paciente atual = atendimento.getPaciente(i);
    std::cout << atual.getId() << ", HA: " << atual.somaDoTempo() << ", TA: " << atual.getTempo_atendido() << ", TO: " << atual.getTempo_ocioso() << ", Total: " << (atual.getTempo_ocioso() + atual.getTempo_atendido()) << std::endl;
  }

  // separando os pacientes pelo grau de urgência
  while (!atendimento.isEmpty()) {
    if (!atendimento.isEmpty()) {
      Paciente paciente = atendimento.getFront();
      if (paciente.getGrau_de_urgencia() == 2) {
        atendimento_vermelho.enfileira(paciente);
      } else if (paciente.getGrau_de_urgencia() == 1) {
        atendimento_amarelo.enfileira(paciente);
      } else {
        atendimento_verde.enfileira(paciente);
      }
      atendimento
          .desenfileira(); // Remova o elemento apenas depois de enfileirar
    }
  }

  atendimento_vermelho.imprime();
  std::cout << "\n" << std::endl;
  atendimento_amarelo.imprime();
  std::cout << "\n" << std::endl;
  atendimento_verde.imprime();
  std::cout << "\n" << std::endl;

  while (
      (!atendimento_vermelho.isEmpty() || !atendimento_amarelo.isEmpty() ||
       !atendimento_verde
            .isEmpty())) { // enquanto houver pacientes na fila de atendimento
    if (atendimento_em_uso
            .isEmpty()) { // atualiza a hora pra frente se necessário
      Paciente menor = encontrarPacienteComMenorTempo(
          atendimento_vermelho, atendimento_amarelo, atendimento_verde);
      hora_atual = menor.somaDoTempo();
    }
    std::cout << "Hora atual: " << hora_atual << std::endl;
    if (atendimento_em_uso.hasSpace()) { // preenchendo sala de atendimento
      Paciente paciente_atendimento;
      while (!atendimento_vermelho.isEmpty() &&
             atendimento_vermelho.getFront().somaDoTempo() <= hora_atual &&
             atendimento_em_uso.hasSpace()) {
        paciente_atendimento = atendimento_vermelho.getFront();
        atendimento_em_uso.enfileira(paciente_atendimento);
        atendimento_vermelho.desenfileira();
        std::cout << "Paciente entrou na sala de atendimento " << paciente_atendimento.getId() << std::endl;
      }

      while (!atendimento_amarelo.isEmpty() && atendimento_em_uso.hasSpace() &&
             atendimento_amarelo.getFront().somaDoTempo() <= hora_atual) {
        paciente_atendimento = atendimento_amarelo.getFront();
        atendimento_em_uso.enfileira(paciente_atendimento);
        atendimento_amarelo.desenfileira();
        std::cout << "Paciente entrou na sala de atendimento " << paciente_atendimento.getId() << std::endl;
      }

      while (!atendimento_verde.isEmpty() &&
             atendimento_verde.getFront().somaDoTempo() <= hora_atual &&
             atendimento_em_uso.hasSpace()) {
        paciente_atendimento = atendimento_verde.getFront();
        atendimento_em_uso.enfileira(paciente_atendimento);
        atendimento_verde.desenfileira();
        std::cout << "Paciente entrou na sala de atendimento " << paciente_atendimento.getId() << std::endl;
      }
    }

    if (!atendimento_em_uso.isEmpty()) { // atendendo os pacientes
    for (int i = 0; i < atendimento_em_uso.getSize(); i++) {
      Paciente &paciente = atendimento_em_uso.getPaciente(i);
      paciente.setTempo_atendido(procedimentos.getTempoAtendimento());
    }
    hora_atual = hora_atual + procedimentos.getTempoAtendimento();
    for (int i = 0; i < atendimento_em_uso.getSize(); i++) {
        if (hora_atual > atendimento_em_uso.getPaciente(i).somaDoTempo()) {
          hora_atual = atendimento_em_uso.getPaciente(i).somaDoTempo();
        }
      }
    std::cout << "Hora atual após atendimento: " << hora_atual <<std::endl;
      while (!atendimento_em_uso.isEmpty()) {
        Paciente paciente = atendimento_em_uso.getFront();
        if (paciente.getAlta() == 1) {
        pacientes_pos_alta.enfileira(paciente);
        atendimento_em_uso.desenfileira();
        std::cout << "Paciente atendido: " << paciente.getId() << std::endl;
      } else {
        if (paciente.getGrau_de_urgencia() == 2) {
          medidas_vermelho.enfileira(paciente);
          atendimento_em_uso.desenfileira();
          std::cout << "Paciente atendido: " << paciente.getId() << std::endl;
        } else if (paciente.getGrau_de_urgencia() == 1) {
          medidas_amarelo.enfileira(paciente);
          atendimento_em_uso.desenfileira();
          std::cout << "Paciente atendido: " << paciente.getId() << std::endl;
        } else {
          medidas_verde.enfileira(paciente);
          atendimento_em_uso.desenfileira();
          std::cout << "Paciente atendido: " << paciente.getId() << std::endl;
        }
      }
      }
    } 
    // atualizar tempo ocioso dos pacientes que estão esperando na fila de
    // atendimento
    for (int i = 0; i < atendimento_vermelho.getSize(); i++) {
      Paciente &paciente = atendimento_vermelho.getPaciente(i);
      if (paciente.somaDoTempo() < hora_atual) {
        std::cout << "Soma do tempo: " << paciente.somaDoTempo() << std::endl;
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        std::cout << "Tempo ocioso: " << tempo_ocioso << std::endl;
        paciente.setTempo_ocioso(tempo_ocioso);
        std::cout << "Tempo ocioso total do paciente " << paciente.getId() << ": " << paciente.getTempo_ocioso() << std::endl;
      } else {
        break;
      }
    }
    for (int i = 0; i < atendimento_amarelo.getSize(); i++) {
      Paciente &paciente = atendimento_amarelo.getPaciente(i);
      if (paciente.somaDoTempo() < hora_atual) {
        std::cout << "Soma do tempo: " << paciente.somaDoTempo() << std::endl;
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        std::cout << "Tempo ocioso: " << tempo_ocioso << std::endl;
        paciente.setTempo_ocioso(tempo_ocioso);
        std::cout << "Tempo ocioso total do paciente " << paciente.getId() << ": " << paciente.getTempo_ocioso() << std::endl;
      } else {
        break;
      }
    }
    for (int i = 0; i < atendimento_verde.getSize(); i++) {
      Paciente &paciente = atendimento_verde.getPaciente(i);
      if (paciente.somaDoTempo() < hora_atual) {
        std::cout << "Soma do tempo: " << paciente.somaDoTempo() << std::endl;
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        std::cout << "Tempo ocioso: " << tempo_ocioso << std::endl;
        paciente.setTempo_ocioso(tempo_ocioso);
        std::cout << "Tempo ocioso total do paciente " << paciente.getId() << ": " << paciente.getTempo_ocioso() << std::endl;
      } else {
        break;
      }
    }
  }

  medidas_vermelho.imprime();
  std::cout << "\n" << std::endl;
  medidas_amarelo.imprime();
  std::cout << "\n" << std::endl;
  medidas_verde.imprime();
  std::cout << "\n" << std::endl;
  pacientes_pos_alta.imprime();
  std::cout << "\n" << std::endl;

  for (int i = 0; i < medidas_vermelho.getSize(); i++) {
    Paciente atual = medidas_vermelho.getPaciente(i);
    std::cout << atual.getId() << ", HA: " << atual.somaDoTempo() << ", TA: " << atual.getTempo_atendido() << ", TO: " << atual.getTempo_ocioso() << ", Total: " << (atual.getTempo_ocioso() + atual.getTempo_atendido()) << std::endl;
  }
  for (int i = 0; i < medidas_amarelo.getSize(); i++) {
    Paciente atual = medidas_amarelo.getPaciente(i);
    std::cout << atual.getId() << ", HA: " << atual.somaDoTempo() << ", TA: " << atual.getTempo_atendido() << ", TO: " << atual.getTempo_ocioso() << ", Total: " << (atual.getTempo_ocioso() + atual.getTempo_atendido()) << std::endl;
  }
  for (int i = 0; i < medidas_verde.getSize(); i++) {
    Paciente atual = medidas_verde.getPaciente(i);
    std::cout << atual.getId() << ", HA: " << atual.somaDoTempo() << ", TA: " << atual.getTempo_atendido() << ", TO: " << atual.getTempo_ocioso() << ", Total: " << (atual.getTempo_ocioso() + atual.getTempo_atendido()) << std::endl;
  }

  for (int i = 0; i < pacientes_pos_alta.getSize(); i++) {
    Paciente atual = pacientes_pos_alta.getPaciente(i);
    std::cout << atual.getId() << ", HA: " << atual.somaDoTempo() << ", TA: " << atual.getTempo_atendido() << ", TO: " << atual.getTempo_ocioso() << ", Total: " << (atual.getTempo_ocioso() + atual.getTempo_atendido()) << std::endl;
  }

  while ((!medidas_vermelho.isEmpty() || !medidas_amarelo.isEmpty() ||
          !medidas_verde.isEmpty() ||
          !medidas_em_uso
               .isEmpty())) { // enquanto houver pacientes na fila de medidas
    if (medidas_em_uso.isEmpty()) { // atualiza a hora pra frente se necessário
      Paciente menor = encontrarPacienteComMenorTempo(
          medidas_vermelho, medidas_amarelo, medidas_verde);
      hora_atual = menor.somaDoTempo();
    }

    if (medidas_em_uso.hasSpace()) { // preenchendo sala de medidas
      Paciente paciente_medidas;
      while (!medidas_vermelho.isEmpty() &&
             medidas_vermelho.getFront().somaDoTempo() <=
                 (hora_atual + 0.0001) &&
             medidas_em_uso.hasSpace()) {
        paciente_medidas = medidas_vermelho.getFront();
        medidas_em_uso.enfileira(paciente_medidas);
        medidas_vermelho.desenfileira();
      }
      while (!medidas_amarelo.isEmpty() && medidas_em_uso.hasSpace() &&
             medidas_amarelo.getFront().somaDoTempo() <= hora_atual) {
        paciente_medidas = medidas_amarelo.getFront();
        medidas_em_uso.enfileira(paciente_medidas);
        medidas_amarelo.desenfileira();
      }
      while (!medidas_verde.isEmpty() &&
             medidas_verde.getFront().somaDoTempo() <= (hora_atual + 0.0001) &&
             medidas_em_uso.hasSpace()) {
        paciente_medidas = medidas_verde.getFront();
        medidas_em_uso.enfileira(paciente_medidas);
        medidas_verde.desenfileira();
      }
    }

    if (!medidas_em_uso.isEmpty()) {
      for (int i = 0; i < medidas_em_uso.getSize(); i++) {
        Paciente &paciente = medidas_em_uso.getPaciente(i);
        if (paciente.getNum_medidas_hospitalares() > 0) {
          paciente.decrementaMedidas();
        }
        paciente.setTempo_atendido(procedimentos.getTempoMedidas());
      }
      hora_atual = hora_atual + procedimentos.getTempoMedidas();
      for (int i = 0; i < medidas_em_uso.getSize();) {
        Paciente &paciente = medidas_em_uso.getPaciente(i);
        if (paciente.getNum_medidas_hospitalares() == 0) {
          if (paciente.getGrau_de_urgencia() == 2) {
            testes_vermelho.enfileira(paciente);
            medidas_em_uso.desenfileiraPelaPosicao(i);
          } else if (paciente.getGrau_de_urgencia() == 1) {
            testes_amarelo.enfileira(paciente);
            medidas_em_uso.desenfileiraPelaPosicao(i);
          } else {
            testes_verde.enfileira(paciente);
            medidas_em_uso.desenfileiraPelaPosicao(i);
          }
        } else {
          i++;
        }
      }
    }
    // atualizar tempo ocioso dos pacientes que estão esperando na fila de
    // medidas
    for (int i = 0; i < medidas_vermelho.getSize(); i++) {
      Paciente &paciente = medidas_vermelho.getPaciente(i);
      if (paciente.somaDoTempo() < hora_atual) {
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        paciente.setTempo_ocioso(tempo_ocioso);
      } else {
        break;
      }
    }
    for (int i = 0; i < medidas_amarelo.getSize(); i++) {
      Paciente &paciente = medidas_amarelo.getPaciente(i);
      if (paciente.somaDoTempo() < hora_atual) {
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        paciente.setTempo_ocioso(tempo_ocioso);
      } else {
        break;
      }
    }
    for (int i = 0; i < medidas_verde.getSize(); i++) {
      Paciente &paciente = medidas_verde.getPaciente(i);
      if (paciente.somaDoTempo() < hora_atual) {
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        paciente.setTempo_ocioso(tempo_ocioso);
      } else {
        break;
      }
    }
  }

  while ((!testes_vermelho.isEmpty() || !testes_amarelo.isEmpty() ||
          !testes_verde.isEmpty() ||
          !testes_em_uso
               .isEmpty())) { // enquanto houver pacientes na fila de testes
    if (testes_em_uso.isEmpty()) { // atualiza a hora pra frente se necessário
      Paciente menor = encontrarPacienteComMenorTempo(
          testes_vermelho, testes_amarelo, testes_verde);
      hora_atual = menor.somaDoTempo();
    }

    if (testes_em_uso.hasSpace()) { // preenchendo sala de testes
      Paciente paciente_testes;
      while (!testes_vermelho.isEmpty() &&
             testes_vermelho.getFront().somaDoTempo() <=
                 (hora_atual + 0.0001) &&
             testes_em_uso.hasSpace()) {
        paciente_testes = testes_vermelho.getFront();
        testes_em_uso.enfileira(paciente_testes);
        testes_vermelho.desenfileira();
      }
      while (!testes_amarelo.isEmpty() && testes_em_uso.hasSpace() &&
             testes_amarelo.getFront().somaDoTempo() <= (hora_atual + 0.0001)) {
        paciente_testes = testes_amarelo.getFront();
        testes_em_uso.enfileira(paciente_testes);
        testes_amarelo.desenfileira();
      }
      while (!testes_verde.isEmpty() &&
             testes_verde.getFront().somaDoTempo() <= (hora_atual + 0.0001) &&
             testes_em_uso.hasSpace()) {
        paciente_testes = testes_verde.getFront();
        testes_em_uso.enfileira(paciente_testes);
        testes_verde.desenfileira();
      }
    }

    if (!testes_em_uso.isEmpty()) {
      for (int i = 0; i < testes_em_uso.getSize(); i++) {
        Paciente &paciente = testes_em_uso.getPaciente(i);
        if (paciente.getNum_testes_de_laboratorio() > 0) {
          paciente.decrementaTestes();
        }
        paciente.setTempo_atendido(procedimentos.getTempoTestes());
      }
      hora_atual = hora_atual + procedimentos.getTempoTestes();
      for (int i = 0; i < testes_em_uso.getSize();) {
        Paciente &paciente = testes_em_uso.getPaciente(i);
        if (paciente.getNum_testes_de_laboratorio() == 0) {
          if (paciente.getGrau_de_urgencia() == 2) {
            exames_vermelho.enfileira(paciente);
            testes_em_uso.desenfileiraPelaPosicao(i);
          } else if (paciente.getGrau_de_urgencia() == 1) {
            exames_amarelo.enfileira(paciente);
            testes_em_uso.desenfileiraPelaPosicao(i);
          } else {
            exames_verde.enfileira(paciente);
            testes_em_uso.desenfileiraPelaPosicao(i);
          }
        } else {
          i++;
        }
      }
    }
    // atualizar tempo ocioso dos pacientes que estão esperando na fila de
    // testes
    for (int i = 0; i < testes_vermelho.getSize(); i++) {
      Paciente &paciente = testes_vermelho.getPaciente(i);
      if ((paciente.somaDoTempo() + 0.0001) < hora_atual) {
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        paciente.setTempo_ocioso(tempo_ocioso);
      } else {
        break;
      }
    }
    for (int i = 0; i < testes_amarelo.getSize(); i++) {
      Paciente &paciente = testes_amarelo.getPaciente(i);
      if (paciente.somaDoTempo() < hora_atual) {
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        paciente.setTempo_ocioso(tempo_ocioso);
      } else {
        break;
      }
    }
    for (int i = 0; i < testes_verde.getSize(); i++) {
      Paciente &paciente = testes_verde.getPaciente(i);
      if (paciente.somaDoTempo() < hora_atual) {
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        paciente.setTempo_ocioso(tempo_ocioso);
      } else {
        break;
      }
    }
  }

  while ((!exames_vermelho.isEmpty() || !exames_amarelo.isEmpty() ||
          !exames_verde.isEmpty() ||
          !exames_em_uso
               .isEmpty())) { // enquanto houver pacientes na fila de exames
    if (exames_em_uso.isEmpty()) { // atualiza a hora pra frente se necessário
      Paciente menor = encontrarPacienteComMenorTempo(
          exames_vermelho, exames_amarelo, exames_verde);
      hora_atual = menor.somaDoTempo();
    }
    if (exames_em_uso.hasSpace()) { // preenchendo sala de exames
      Paciente paciente_exames;
      while (!exames_vermelho.isEmpty() &&
             exames_vermelho.getFront().somaDoTempo() <=
                 (hora_atual + procedimentos.getTempoExames()) &&
             exames_em_uso.hasSpace()) {
        paciente_exames = exames_vermelho.getFront();
        exames_em_uso.enfileira(paciente_exames);
        exames_vermelho.desenfileira();
      }
      while (!exames_amarelo.isEmpty() && exames_em_uso.hasSpace() &&
             exames_amarelo.getFront().somaDoTempo() <=
                 (hora_atual + 0.0001 + procedimentos.getTempoExames())) {
        paciente_exames = exames_amarelo.getFront();
        exames_em_uso.enfileira(paciente_exames);
        exames_amarelo.desenfileira();
      }
      while (!exames_verde.isEmpty() &&
             exames_verde.getFront().somaDoTempo() <=
                 (hora_atual + 0.0001 + procedimentos.getTempoExames()) &&
             exames_em_uso.hasSpace()) {
        paciente_exames = exames_verde.getFront();
        exames_em_uso.enfileira(paciente_exames);
        exames_verde.desenfileira();
      }
    }

    if (!exames_em_uso.isEmpty()) {
      for (int i = 0; i < exames_em_uso.getSize(); i++) {
        Paciente &paciente = exames_em_uso.getPaciente(i);
        if (paciente.getNum_exames_de_imagem() > 0) {
          paciente.decrementaExames();
        }
        paciente.setTempo_atendido(procedimentos.getTempoExames());
      }
      hora_atual = hora_atual + procedimentos.getTempoExames();
      for (int i = 0; i < exames_em_uso.getSize(); i++) {
        if (hora_atual > exames_em_uso.getPaciente(i).somaDoTempo()) {
          hora_atual = exames_em_uso.getPaciente(i).somaDoTempo();
        }
      }
      for (int i = 0; i < exames_em_uso.getSize();) {
        Paciente &paciente = exames_em_uso.getPaciente(i);
        if (paciente.getNum_exames_de_imagem() == 0) {
          if (paciente.getGrau_de_urgencia() == 2) {
            instrumentos_vermelho.enfileira(paciente);
            exames_em_uso.desenfileiraPelaPosicao(i);
          } else if (paciente.getGrau_de_urgencia() == 1) {
            instrumentos_amarelo.enfileira(paciente);
            exames_em_uso.desenfileiraPelaPosicao(i);
          } else {
            instrumentos_verde.enfileira(paciente);
            exames_em_uso.desenfileiraPelaPosicao(i);
          }
        } else {
          i++;
        }
      }
    }
    float menor_tempo_de_saida =
        exames_em_uso.getPaciente(0).somaDoTempo() +
        (exames_em_uso.getPaciente(0).getNum_exames_de_imagem() *
         procedimentos.getTempoExames());
    for (int i = 1; i < exames_em_uso.getSize(); i++) {
      Paciente &paciente = exames_em_uso.getPaciente(i);
      float tempo_saida_atual =
          (paciente.somaDoTempo() + (paciente.getNum_exames_de_imagem() *
                                     procedimentos.getTempoExames()));
      if (tempo_saida_atual < menor_tempo_de_saida) {
        hora_atual = exames_em_uso.getPaciente(i)
                         .somaDoTempo(); // Atualiza a hora com o menor tempo de
                                         // saída encontrado
        menor_tempo_de_saida = tempo_saida_atual;
      }
    }
    // atualizar tempo ocioso dos pacientes que estão esperando na fila de
    // exames
    for (int i = 0; i < exames_vermelho.getSize(); i++) {
      Paciente &paciente = exames_vermelho.getPaciente(i);
      if ((paciente.somaDoTempo() + 0.0001) < hora_atual) {
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        paciente.setTempo_ocioso(tempo_ocioso);
      } else {
        break;
      }
    }
    for (int i = 0; i < exames_amarelo.getSize(); i++) {
      Paciente &paciente = exames_amarelo.getPaciente(i);
      if ((paciente.somaDoTempo() + 0.0001) < hora_atual) {
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        paciente.setTempo_ocioso(tempo_ocioso);
      } else {
        break;
      }
    }
    for (int i = 0; i < exames_verde.getSize(); i++) {
      Paciente &paciente = exames_verde.getPaciente(i);
      if ((paciente.somaDoTempo() + 0.0001) < hora_atual) {
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        paciente.setTempo_ocioso(tempo_ocioso);
      } else {
        break;
      }
    }
  }

  while (
      (!instrumentos_vermelho.isEmpty() || !instrumentos_amarelo.isEmpty() ||
       !instrumentos_verde.isEmpty() ||
       !instrumentos_em_uso
            .isEmpty())) { // enquanto houver pacientes na fila de instrumentos
    if (instrumentos_em_uso
            .isEmpty()) { // atualiza a hora pra frente se necessário
      Paciente menor = encontrarPacienteComMenorTempo(
          instrumentos_vermelho, instrumentos_amarelo, instrumentos_verde);
      hora_atual = menor.somaDoTempo();
    }
    if (instrumentos_em_uso.hasSpace()) { // preenchendo sala de instrumentos
      Paciente paciente_instrumentos;
      while (!instrumentos_vermelho.isEmpty() &&
             instrumentos_vermelho.getFront().somaDoTempo() <=
                 (hora_atual + procedimentos.getTempoInstrumentos()) &&
             instrumentos_em_uso.hasSpace()) {
        paciente_instrumentos = instrumentos_vermelho.getFront();
        instrumentos_em_uso.enfileira(paciente_instrumentos);
        instrumentos_vermelho.desenfileira();
      }
      while (!instrumentos_amarelo.isEmpty() &&
             instrumentos_em_uso.hasSpace() &&
             instrumentos_amarelo.getFront().somaDoTempo() <=
                 (hora_atual + 0.0001 + procedimentos.getTempoInstrumentos())) {
        paciente_instrumentos = instrumentos_amarelo.getFront();
        instrumentos_em_uso.enfileira(paciente_instrumentos);
        instrumentos_amarelo.desenfileira();
      }
      while (!instrumentos_verde.isEmpty() &&
             instrumentos_verde.getFront().somaDoTempo() <=
                 (hora_atual + 0.0001 + procedimentos.getTempoInstrumentos()) &&
             instrumentos_em_uso.hasSpace()) {
        paciente_instrumentos = instrumentos_verde.getFront();
        instrumentos_em_uso.enfileira(paciente_instrumentos);
        instrumentos_verde.desenfileira();
      }
    }
    if (!instrumentos_em_uso.isEmpty()) { // atendendo os pacientes
      for (int i = 0; i < instrumentos_em_uso.getSize(); i++) {
        Paciente &paciente = instrumentos_em_uso.getPaciente(i);
        if (paciente.getNum_instrumentos() > 0) {
          paciente.decrementaInstrumentos();
        }
        paciente.setTempo_atendido(procedimentos.getTempoInstrumentos());
      }
      hora_atual = hora_atual + procedimentos.getTempoInstrumentos();
      for (int i = 0; i < instrumentos_em_uso.getSize(); i++) {
        if (hora_atual > instrumentos_em_uso.getPaciente(i).somaDoTempo()) {
          hora_atual = instrumentos_em_uso.getPaciente(i).somaDoTempo();
        }
      }
      for (int i = 0; i < instrumentos_em_uso.getSize();) {
        Paciente &paciente = instrumentos_em_uso.getPaciente(i);
        if (paciente.getNum_instrumentos() == 0) {
          if (paciente.getGrau_de_urgencia() == 2) {
            pacientes_pos_alta.enfileira(paciente);
            instrumentos_em_uso.desenfileiraPelaPosicao(i);
          } else if (paciente.getGrau_de_urgencia() == 1) {
            pacientes_pos_alta.enfileira(paciente);
            instrumentos_em_uso.desenfileiraPelaPosicao(i);
          } else {
            pacientes_pos_alta.enfileira(paciente);
            instrumentos_em_uso.desenfileiraPelaPosicao(i);
          }
        } else {
          i++;
        }
      }
    }
    float menor_tempo_de_saida =
        instrumentos_em_uso.getPaciente(0).somaDoTempo() +
        (instrumentos_em_uso.getPaciente(0).getNum_instrumentos() *
         procedimentos.getTempoInstrumentos());
    for (int i = 1; i < instrumentos_em_uso.getSize(); i++) {
      Paciente &paciente = instrumentos_em_uso.getPaciente(i);
      float tempo_saida_atual =
          (paciente.somaDoTempo() + (paciente.getNum_instrumentos() *
                                     procedimentos.getTempoInstrumentos()));
      if (tempo_saida_atual < menor_tempo_de_saida) {
        hora_atual = instrumentos_em_uso.getPaciente(i)
                         .somaDoTempo(); // Atualiza a hora com o menor tempo de
                                         // saída encontrado
        menor_tempo_de_saida = tempo_saida_atual;
      }
    }
    // atualizar tempo ocioso dos pacientes que estão esperando na fila de
    // instrumentos
    for (int i = 0; i < instrumentos_vermelho.getSize(); i++) {
      Paciente &paciente = instrumentos_vermelho.getPaciente(i);
      if ((paciente.somaDoTempo() + 0.0001) < hora_atual) {
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        paciente.setTempo_ocioso(tempo_ocioso);
      } else {
        break;
      }
    }
    for (int i = 0; i < instrumentos_amarelo.getSize(); i++) {
      Paciente &paciente = instrumentos_amarelo.getPaciente(i);
      if ((paciente.somaDoTempo() + 0.0001) < hora_atual) {
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        paciente.setTempo_ocioso(tempo_ocioso);
      } else {
        break;
      }
    }
    for (int i = 0; i < instrumentos_verde.getSize(); i++) {
      Paciente &paciente = instrumentos_verde.getPaciente(i);
      if ((paciente.somaDoTempo() + 0.0001) < hora_atual) {
        float tempo_ocioso = hora_atual - paciente.somaDoTempo();
        paciente.setTempo_ocioso(tempo_ocioso);
      } else {
        break;
      }
    }
  }

  pacientes_pos_alta.OrdenaPorID();

  for (int i = 0; i < pacientes_pos_alta.getSize(); i++) {
    int idSemZeros = std::stoi(pacientes_pos_alta.getPaciente(i).getId());
    int dia = pacientes_pos_alta.getPaciente(i).getDia();
    int mes = pacientes_pos_alta.getPaciente(i).getMes();
    int ano = pacientes_pos_alta.getPaciente(i).getAno();
    int hora = pacientes_pos_alta.getPaciente(i).getHora();
    float tempoTotal =
        (pacientes_pos_alta.getPaciente(i).getTempo_atendido_final() +
         pacientes_pos_alta.getPaciente(i).getTempo_ocioso());
    float tempo_atendido =
        pacientes_pos_alta.getPaciente(i).getTempo_atendido_final();
    float tempo_ocioso = pacientes_pos_alta.getPaciente(i).getTempo_ocioso();
    imprimirHorario(idSemZeros, dia, mes, ano, hora, tempoTotal, tempo_atendido,
                    tempo_ocioso);
  }

  arquivo.close();

  return 0;
}