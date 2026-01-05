# Projeto de Gestão de Equipas de Futebol

**Autor:** Hugo Bacalhau  
**Curso:** CET TPSI 0525  
**Data:** 03 de julho 2025

Este projeto consiste num programa desenvolvido em linguagem C para a gestão de equipas de futebol. O sistema permite criar, visualizar, editar e apagar equipas, bem como gerir os seus dados.

## Estrutura do Projeto

O código fonte foi reorganizado para uma melhor estrutura:

- `src/`: Contém o código fonte do programa (`equipas.c`).
- `bin/` (opcional): Local recomendado para o executável compilado.

## Como Compilar e Executar

Para compilar o projeto, utilize um compilador C como o GCC.

**No terminal:**

```bash
gcc src/equipas.c -o equipas.exe
./equipas.exe
```

## Estratégia de Branches (Git Flow Simplificado)

Para trabalhar neste projeto e enviar as alterações para o GitHub, recomenda-se a seguinte estratégia de branches:

1.  **main**: Branch principal. Contém apenas o código estável e funcional (produção).
2.  **develop** (opcional): Branch de integração para novas funcionalidades antes de irem para a `main`.
3.  **Branches de Funcionalidade (Feature Branches)**:
    - Sempre que quiseres adicionar uma nova funcionalidade ou corrigir um bug, cria um novo branch a partir da `main` (ou `develop`).
    - Nomenclatura sugerida: `feature/nome-da-funcionalidade` ou `fix/nome-da-correcao`.

### Exemplo de Fluxo de Trabalho:

1.  **Criar um branch para uma nova funcionalidade (ex: adicionar jogadores):**
    ```bash
    git checkout -b feature/adicionar-jogadores
    ```

2.  **Fazer alterações e commits:**
    ```bash
    git add .
    git commit -m "Implementar estrutura de jogadores"
    ```

3.  **Voltar à main e atualizar (se houver alterações remotas):**
    ```bash
    git checkout main
    git pull origin main
    ```

4.  **Fundir a funcionalidade na main (Merge):**
    ```bash
    git merge feature/adicionar-jogadores
    ```
    *(Ou melhor: fazer o push da feature branch e abrir um Pull Request no GitHub)*

5.  **Enviar para o GitHub:**
    ```bash
    git push origin main
    ```
