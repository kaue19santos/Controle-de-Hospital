import matplotlib.pyplot as plt

# Dados ajustados
n_values = [10, 25, 50, 100]
times = [2.01, 1.25625, 5.025, 20.1]  # Ajustado para n^2

# Plotando os dados
plt.plot(n_values, times, label="Tempo de Execução (ms)", marker='o')

# Ajustando o título e os eixos
plt.title("Tempo de Execução vs Número de Pacientes (Modelo Quadrático)")
plt.xlabel("Número de Pacientes")
plt.ylabel("Tempo de Execução (ms)")

# Exibindo o gráfico
plt.legend()
plt.grid(True)
plt.show()
