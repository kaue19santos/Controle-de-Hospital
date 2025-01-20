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
        float tempo_ocioso;
        float tempo_atendido;
        float tempo_atendido_final;

    public:  
        Paciente();

        void setId(std::string _id);
        const std::string getId() const;

        void setAlta(int _alta);
        int getAlta();

        void setAno(int _ano);
        int getAno() const;

        void setMes(int _mes);
        int getMes() const;

        void setDia(int _dia);
        int getDia() const;

        void setHora(int _hora);
        int getHora() const;

        void setGrau_de_urgencia(int _grau_de_urgencia);
        int getGrau_de_urgencia() const;

        void setNum_medidas_hospitalares(int _num_medidas_hospitalares);
        int getNum_medidas_hospitalares();
        void decrementaMedidas();

        void setNum_testes_de_laboratorio(int _num_testes_de_laboratorio);
        int getNum_testes_de_laboratorio();
        void decrementaTestes();

        void setNum_exames_de_imagem(int _num_exames_de_imagem);
        int getNum_exames_de_imagem();
        void decrementaExames();

        void setNum_instrumentos(int _num_instrumentos);
        int getNum_instrumentos();
        void decrementaInstrumentos();

        void setEstado_atual(int _estado_atual);
        int getEstado_atual();

        void setTempo_ocioso(float _tempo_ocioso);
        float getTempo_ocioso();

        void setTempo_atendido(float _tempo_atendido);
        float getTempo_atendido();

        float somaDoTempo(); // somar a hora atual + tempo ocioso + tempo atendido

        float getTempo_atendido_final() const;
        void setTempo_Atendido_Final(float tempo_atendido_final_);
}; 

#endif
