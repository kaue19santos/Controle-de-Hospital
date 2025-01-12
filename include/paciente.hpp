#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include <string>

class Paciente {
    private:
        std::string id;
        int alta;
        int ano;
        int mes;
        int dia;
        int hora;
        int grau_de_urgencia;
        int num_medidas_hospitalares;
        int num_testes_de_laboratorio;
        int num_exames_de_imagem;
        int num_instrumentos;
        int estado_atual;
        int tempo_ocioso;
        int tempo_atendido;

    public:  
        Paciente();

        void setId(std::string _id);
        std::string getId();

        void setAlta(int _alta);
        int getAlta();

        void setAno(int _ano);
        int getAno();

        void setMes(int _mes);
        int getMes();

        void setDia(int _dia);
        int getDia();

        void setHora(int _hora);
        int getHora();

        void setGrau_de_urgencia(int _grau_de_urgencia);
        int getGrau_de_urgencia();

        void setNum_medidas_hospitalares(int _num_medidas_hospitalares);
        int getNum_medidas_hospitalares();

        void setNum_testes_de_laboratorio(int _num_testes_de_laboratorio);
        int getNum_testes_de_laboratorio();

        void setNum_exames_de_imagem(int _num_exames_de_imagem);
        int getNum_exames_de_imagem();

        void setNum_instrumentos(int _num_instrumentos);
        int getNum_instrumentos();

        void setEstado_atual(int _estado_atual);
        int getEstado_atual();

        void setTempo_ocioso(int _tempo_ocioso);
        int getTempo_ocioso();

        void setTempo_atendido(int _tempo_atendido);
        int getTempo_atendido();
}; 

#endif
