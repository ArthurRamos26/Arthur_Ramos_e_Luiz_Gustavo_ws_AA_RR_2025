# Arthur_Ramos_e_Luiz_Gustavo_ws_AA_RR_2025
Este trabalho foi desenvolvido para a disciplina de Análise de Algoritmos da Universidade Federal do Estado de Roraima (UFRR), com o objetivo de estudar diferentes abordagens para a resolução do problema clássico do Caixeiro Viajante (TSP).

Objetivo

Comparar o desempenho entre:

Um algoritmo de força bruta (complexidade fatorial)

Um algoritmo otimizado utilizando programação dinâmica (Held-Karp)


## Algoritmos Implementados

### Força Bruta
A abordagem de Força Bruta funciona testando exaustivamente todas as permutações possíveis de rotas entre as cidades. Embora essa estratégia tenha a vantagem de garantir que a solução encontrada seja a melhor possível (a solução ótima), ela esbarra em uma barreira física de desempenho: sua complexidade é $O(n!)$. O crescimento fatorial faz com que o tempo de execução exploda rapidamente, tornando o algoritmo inviável na prática quando adicionamos apenas algumas cidades a mais.

### Held-Karp (Programação Dinâmica)
O algoritmo de Held-Karp resolve o problema de uma maneira bem mais inteligente. Ele utiliza programação dinâmica e a técnica de memorização (*memoization*) para armazenar distâncias de subconjuntos que já foram calculados, gerenciando isso através de máscaras de bits (*bitmasks*). Com uma complexidade reduzida para $O(n^2 \cdot 2^n)$, ele se torna exponencialmente mais rápido que a força bruta. O grande diferencial aqui é que o algoritmo consegue resolver o problema para um número maior de cidades em frações de segundo, e tudo isso sem abrir mão de encontrar a rota exata e perfeita.

---

**Explorando Outras Abordagens**
Outras abordagens bem difundidas são a de branch and bound (n!) e a de nearest neighbour(n²) onde mesmo o nearest neighbour até tem o custo menor que o held-karp porém ele perde na precisão por esse motivo foi escolhido o held-karp pois tem-se o custo menor que o branch and bound e a precisão melhor que a do nearest-neighbour

## Como Executar
```bash
gcc Forca_Bruta.c -o forca_bruta
gcc otimizado.c -o held_karp
Após compilar basta executar:
./forca_bruta
./held_karp
```
### Comparação de Tempo de Execução: PCV Inicial vs Held-Karp Otimizado

| Cidades | PCV Inicial / Força Bruta (s) | Held-Karp Otimizado (s) |
| :---: | :--- | :--- |
| **3** | 0.000001 | 0.000001 |
| **4** | 0.000001 | 0.000001 |
| **5** | 0.000003 | 0.000003 |
| **6** | 0.000020 | 0.000009 |
| **7** | 0.000179 | 0.000021 |
| **8** | 0.001515 | 0.000048 |
| **9** | 0.016363 | 0.000119 |
| **10** | 0.192707 | 0.000288 |
| **11** | 1.778299 | 0.000611 |
| **12** | > tempo limite | 0.001623 |
| **13** | > tempo limite | 0.003631 |
| **14** | > tempo limite | 0.008838 |
| **15** | > tempo limite | 0.018493 |
| **16** | > tempo limite | 0.039881 |
| **17** | > tempo limite | 0.090558 |
| **18** | > tempo limite | 0.174450 |


Aonde o tempo limite foi posto como qualquer valor acima de 10 cidades pois exigiria alto valor computacional e de tempo pois haveria a necessidade de calcular 3.628.800 rotas conforme o aumento exponencial

---

### Representação gráfica do força-bruta:

![image alt](https://github.com/ArthurRamos26/Arthur_Ramos_e_Luiz_Gustavo_ws_AA_RR_2025/blob/185838b47c85e683bf86fee19691107e6c6bb7d4/trueforcabruta.jpg)
