# Projeto Acadêmico CCO085 — Problema 07: Mergesort paralelo

Programação Paralela · IESB 2026/2 · Prof. Rodrigo Gonçalves

Paralelização do mergesort sequencial de referência (`baselines_sequenciais_CCO085/07_mergesort.cpp`)
em memória compartilhada (OpenMP) e memória distribuída (MPI).

## Estrutura

```
projeto_mergesort/
├── sequencial/    baseline do professor (cópia sem alteração de lógica)
├── openmp/        versão OpenMP              (Marco 2 — a fazer)
├── mpi/           versão MPI                 (Marco 2 — a fazer)
├── scripts/       coleta de tempos em CSV e geração de gráficos
├── resultados/    CSVs gerados pelos scripts
├── graficos/      gráficos de tempo, speedup e eficiência
├── Makefile
└── AUTORES.md     frente de cada integrante
```

## Rodando do zero

Requisitos: `g++` com OpenMP e OpenMPI (`mpicxx`, `mpirun`). No laboratório já existem;
em casa, use o contêiner da disciplina (`ambiente_pp/`, `docker compose run --rm pp-lab`).

```bash
cd projeto_mergesort
make                          # compila tudo para bin/
./bin/mergesort_seq 20000000  # baseline: n=20000000  ordenado=SIM  tempo=...
```

## Validação de corretude

O baseline imprime `ordenado=SIM`. As versões paralelas devem imprimir o mesmo, para a
mesma entrada (semente fixa 12345), com qualquer número de threads/processos.

## Perfilamento

```bash
make perfil
./bin/mergesort_seq_pg 20000000
gprof ./bin/mergesort_seq_pg gmon.out | head -20
```
