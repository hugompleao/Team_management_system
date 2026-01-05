/* 
    Título do Projeto: Equipas de futebol.
    Descrição: Programa de gestão de equipas de futebol desenvolvido em linguagem C.
    Autor: Hugo Bacalhau
    Curso: CET TPSI 0525
    Email: hugo.bacalhau.t0121748@edu.atec.pt 
    Data: 03 de julho 2025 | 22:00h
*/ 
 
#include<stdio.h>
#include<stdlib.h>
#include<conio.h> 
#include<windows.h>
#include<string.h>

void simbolo(int num, char caracter)
{
    for(int i = 0; i <= num; i++)
    {
        printf("%c", caracter);
    }
    printf("\n");
}

void corSairPrograma(){
    system("color 09");
    Sleep(1000);
    system("color 07");
    system("cls");
}

void corErro(){
    //Fundo preto com letras vermelhas
    system("color 04");
    Beep(750,300);
    Sleep(1500);
    //Reset à cor 
    system("color 07");
    system("cls");
}

void abrirFicheiroEquipaTxt(char *nomeEquipa){
    char caminho[200], comando[200];

    //cria o caminho do ficheiro concatenado
    strcpy(caminho, "C:\\Equipas\\");
    strcat(caminho, nomeEquipa);
    strcat(caminho, ".txt");

    //printf("Abrir o ficheiro: %s\n", caminho); - Teste para saber se era o caminho correto

    FILE *ficheiroEquipa = fopen(caminho, "r");
    
    // erro
    if (ficheiroEquipa == NULL){
        printf("ERRO ! Ficheiro nao encontrado\n");
        corErro();
        return;
    }
    fclose(ficheiroEquipa);

    //igual ao strcpy e strcat mas de forma mais breve
    snprintf(comando, sizeof(comando), "start notepad \"%s\"", caminho);

    // executa o comando no terminal do windows e abre o ficheiro automaticamente no bloco de notas.
    system(comando);
}

int nomesValidos(const char *nome){
    //valida se os nomes dos jogadores foram atribuidos
     for (int i = 0; nome[i] != '\0'; i++) {
        if (nome[i] != ' ' && nome[i] != '\t') {
            return 1; // Tem algum caractere que não é espaço
        }
    }
    return 0; // so espaços ou vazio
}

void verEquipas(){
    FILE *ficheiro = fopen("C:\\Equipas\\equipas.txt", "r");

    //menu apresentação
    simbolo(50, '*');
    printf("\t\tVer Equipas Existentes \n");
    simbolo(50, '-');

    char linhaTexto[100]; 

    //erro caso o ficheiro esteja vazio
    if(ficheiro == NULL){
        printf("ERRO ! Nao ha equipas registadas.\n");
        corErro();
        return;
    }

    //leitura do ficheiro equipas.txt
    while(fgets(linhaTexto, sizeof(linhaTexto), ficheiro)){
        linhaTexto[strcspn(linhaTexto, "\n")] = '\0';
        
        if (strncmp(linhaTexto, "Equipa:", 7) == 0) {
            printf("- %s\n", linhaTexto + 8); 
        }
    }
   
    simbolo(50, '-');
    printf("Prima qualquer tecla para voltar ao menu: ");
    getch();
    fclose(ficheiro);
    system("cls");

}

void pesquisarEquipas(){
    FILE *ficheiro = fopen("C:\\Equipas\\equipas.txt", "r");

    //menu apresentação
    simbolo(50, '*');
    printf("\t\tPesquisar Equipas\n");
    simbolo(50, '-');

    char linhaTexto[100], equipas[100][100];
    int totalEquipas = 0;
    int opcao, op; //op - para não entrar em conflito com opcao

    //leitura do ficheiro .txt
    while(fgets(linhaTexto, sizeof(linhaTexto), ficheiro)){

        if (strncmp(linhaTexto, "Equipa:", 7) == 0){
            linhaTexto[strcspn(linhaTexto, "\n")] = 0; // remove '\n'
            strcpy(equipas[totalEquipas], linhaTexto + 8);
            totalEquipas++;
        }
    }

    //erro caso nao haja equipas no ficheiro
    if(totalEquipas == 0){
        printf("ERRO ! Nenhuma equipa encontrada.");
        Beep(750,300);
        Sleep(2000);
        return;
    }

    //para enumerar as equipas aquando a apresentaçao no CMD
    for (int i = 0; i < totalEquipas; i++) {
        printf("%d - %s\n", i + 1, equipas[i]);
    }

    fclose(ficheiro); //Fechar o ficheiro pois ja foi lido

    simbolo(50, '-');
    printf("Selecione o numero da equipa que pretende visualizar: ");
    scanf("%d", &opcao);
    getche();

    //erro
    if (opcao < 1 || opcao > totalEquipas) {
        printf("ERRO ! Opcao invalida.\n");
        corErro();
        return;
    }
    system("cls");

    //menu de opção para apresentar no CMD ou no proprio .txt
    simbolo(50, '*');
    printf("\t\tPesquisar Equipas\n");
    simbolo(50, '-');

    printf("1 - Vizualizar equipa no CMD.\n");
    printf("2 - Vizualizar equipa no ficheiro de texto.\n");
    simbolo(50, '-');
    printf("Introduza o numero da opcao de vizualizacao: ");
    scanf("%d", &op);
    getche();

    //erro
    if (op < 1 || op > 2) {
        printf("ERRO ! Opcao invalida.\n");
        corErro();
        return;
    }
    system("cls");

    if (op == 2)
    {
        abrirFicheiroEquipaTxt(equipas[opcao -1]);
        simbolo(50, '-');
        printf("Prima qualquer tecla para voltar ao menu: ");
        getch();
        fclose(ficheiro);
        system("cls");
        return;
    }

    system("cls");

    //Reabrir o ficheiro para so ser lida a equipa escolhida 
    ficheiro = fopen("C:\\Equipas\\equipas.txt", "r"); 

    int ver = 0;

    simbolo(50, '*');
    printf("\t\tEquipa do %s\n", equipas[opcao - 1]);
    simbolo(50, '-');

     while (fgets(linhaTexto, sizeof(linhaTexto), ficheiro)) {
        if (strncmp(linhaTexto, "-----------------------", 23) == 0) {
            ver = 0;
        }
        if (ver) {
            printf("%s", linhaTexto);
        }
        if (strncmp(linhaTexto, "Equipa:", 7) == 0 && strstr(linhaTexto, equipas[opcao - 1])) {
            ver = 1;
            printf("%s", linhaTexto); // imprime também a linha Equipa
        }
    }
    printf("\nPrima qualquer tecla para voltar ao menu: ");
    getch();
    fclose(ficheiro);
    system("cls");
}
    
void adicionarEquipa(){
    FILE *ficheiro = fopen("C:\\Equipas\\equipas.txt", "a");

    //menu apresentação
    simbolo(50, '*');
    printf("\t\tAdicionar Equipa\n");
    simbolo(50, '-');

    char nomeEquipa[50], nomeFicheiroEquipa[20], nomeTreinador[50], nomeJogador[50], caminho[100];;
    int guardaRedes = 1; //guarda redes = 1 para fazer os 11 jogadores
    int defesas, medios, avancados, totalJogadores;

    if(ficheiro == NULL){
        printf("\nERRO ! Nao foi possivel abrir o ficheiro.\n");
        corErro();
        return;
    }

    //Nome equipa
    do{
        printf("Introduza o nome da equipa que pretende adicionar: ");
        fgets(nomeEquipa, sizeof(nomeEquipa), stdin);
        nomeEquipa[strcspn(nomeEquipa, "\n")] = '\0';

        //verificação do nome
        if(!nomesValidos(nomeEquipa))
        {
            printf("ERRO ! Os elementos da equipa devem conter nomes.\n");
            corErro();
            system("cls");
        }
    }while(!nomesValidos(nomeEquipa));
    
    //criar .txt para a equipa
    strcpy(caminho, "C:\\Equipas\\");
    strcat(caminho, nomeEquipa);
    strcat(caminho, ".txt");

    //abrir o ficheiro destinado à equipa
    FILE *ficheiroEquipa = fopen(caminho, "w");

    //escreve nos ficheiros
    fprintf(ficheiro, "Equipa: %s\n", nomeEquipa);
    fprintf(ficheiroEquipa, "Equipa: %s\n", nomeEquipa);
    printf("Nome da equipa registado: %s\n\n", nomeJogador);

    //Treinador
    do{
        printf("Introduza o nome do treinador: ");
        fgets(nomeTreinador, sizeof(nomeTreinador), stdin);
        nomeTreinador[strcspn(nomeTreinador, "\n")] = '\0';

        if(!nomesValidos(nomeTreinador))
        {
            printf("ERRO ! Os elementos da equipa devem conter nomes.\n");
            corErro();
            system("cls");
        }
    }while(!nomesValidos(nomeTreinador));

    fprintf(ficheiro, "Treinador: %s\n", nomeTreinador);
    fprintf(ficheiroEquipa, "Treinador: %s\n", nomeTreinador);
    printf("Treinador registado !\n\n", nomeJogador);


    //Formação tatica
    do{
        printf("Escolha a formacao tatica da sua equipa (ex: 4-3-3): ");
        scanf("%d-%d-%d", &defesas, &medios, &avancados);
        getchar();

        totalJogadores = guardaRedes + defesas + medios + avancados; //= 11 


        if(totalJogadores != 11)
        {
            printf("ERRO ! A sua equipa deve conter 11 jogadores.\n");
            corErro();
            system("cls");
        }
    }while(totalJogadores != 11);

    fprintf(ficheiro, "Formacao Tatica: %d-%d-%d\n\n",  defesas, medios, avancados);
    fprintf(ficheiroEquipa, "Formacao Tatica: %d-%d-%d\n\n",  defesas, medios, avancados);
    printf("Formacao Tatica registada !\n\n", nomeJogador);

    //Guarda Redes
    do{
        printf("Introduza o nome do Guarda Redes: ");
        fgets(nomeJogador, sizeof(nomeJogador), stdin);
        nomeJogador[strcspn(nomeJogador, "\n")] = '\0';
        
        if(!nomesValidos(nomeJogador))
        {
            printf("ERRO ! Os elementos da equipa devem conter nomes.\n");
            corErro();
            system("cls");
        }
    }while (!nomesValidos(nomeJogador));
    
    fprintf(ficheiro,"Guarda Redes: %s\n\n", nomeJogador);
    fprintf(ficheiroEquipa,"Guarda Redes: %s\n\n", nomeJogador);
    printf("Guarda Redes registado !\n\n", nomeJogador);


    //Defesas
    for(int i = 0; i < defesas; i++)
    {
        do{
            printf("Introduza o nome do Defesa: ");
            fgets(nomeJogador, sizeof(nomeJogador), stdin);
            nomeJogador[strcspn(nomeJogador, "\n")] = '\0';

            if(!nomesValidos(nomeJogador))
            {
                printf("ERRO ! Os elementos da equipa devem conter nomes.\n");
                corErro();
                system("cls");
            }
        }while(!nomesValidos(nomeJogador));

        fprintf(ficheiro,"Defesa: %s\n\n", nomeJogador);
        fprintf(ficheiroEquipa,"Defesa: %s\n\n", nomeJogador);
        printf("Defesa registado !\n\n", nomeJogador);
    }

    //Medios
    for(int i = 0; i < medios; i++)
    {
        do{
            printf("Introduza o nome do Medio: ");
            fgets(nomeJogador, sizeof(nomeJogador), stdin);
            nomeJogador[strcspn(nomeJogador, "\n")] = '\0';

            if(!nomesValidos(nomeJogador))
            {
                printf("ERRO ! Os elementos da equipa devem conter nomes.\n");
                corErro();
                system("cls");
            }
        }while(!nomesValidos(nomeJogador));

        fprintf(ficheiro, "Medio: %s\n\n", nomeJogador);
        fprintf(ficheiroEquipa, "Medio: %s\n\n", nomeJogador);
        printf("Medio registado !\n\n", nomeJogador);
    }
    
    //Avançados
    for(int i = 0; i < avancados; i++)
    {
        do{
            printf("Introduza o nome do Avancado: ");
            fgets(nomeJogador, sizeof(nomeJogador), stdin);
            nomeJogador[strcspn(nomeJogador, "\n")] = '\0';
             if(!nomesValidos(nomeJogador))
            {
                printf("ERRO ! Os elementos da equipa devem conter nomes.\n");
                corErro();
                system("cls");
            }
        }while(!nomesValidos(nomeJogador));

        fprintf(ficheiro, "Avancado: %s\n\n", nomeJogador);
        fprintf(ficheiroEquipa, "Avancado: %s\n\n", nomeJogador);
        printf("Avancado registado !\n\n", nomeJogador);  
    }

    fprintf(ficheiro, "-----------------------\n");
    fprintf(ficheiroEquipa, "-----------------------\n");

    fclose(ficheiro);
    fclose(ficheiroEquipa);

    system("cls");
    printf("\nEquipa criada com sucesso !\n");
    Sleep(2000);
    system("cls");
}

void editarEquipa() {
    FILE *ficheiro = fopen("C:\\Equipas\\equipas.txt", "r");

    char nomeEquipa[50], nomeTreinador[50], nomeJogador[50], caminho[100];
    int guardaRedes = 1;
    int defesas, medios, avancados, totalJogadores;
    char linhaTexto[200], equipas[100][100];
    int totalEquipas = 0;
    int opcao;

    simbolo(50, '*');
    printf("\t\t   Editar Equipas\n");
    simbolo(50, '-');

    // Ler as equipas existentes
    while (fgets(linhaTexto, sizeof(linhaTexto), ficheiro)) {
        if (strncmp(linhaTexto, "Equipa:", 7) == 0) {
            linhaTexto[strcspn(linhaTexto, "\n")] = 0;
            sscanf(linhaTexto, "Equipa: %[^\n]", equipas[totalEquipas]);
            totalEquipas++;
        }
    }
    fclose(ficheiro);

    if (totalEquipas == 0) {
        printf("ERRO ! Nenhuma equipa encontrada.\n");
        corErro();
        return;
    }

    // Mostrar equipas
    for (int i = 0; i < totalEquipas; i++) {
        printf("%d - %s\n", i + 1, equipas[i]);
    }

    simbolo(50, '-');
    printf("Selecione a equipa que pretende editar: ");
    scanf("%d", &opcao);
    getchar();

    if (opcao < 1 || opcao > totalEquipas) {
        printf("ERRO ! Opcao invalida.\n");
        corErro();
        return;
    }

    // Obter o nome da equipa selecionada
    strcpy(nomeEquipa, equipas[opcao - 1]);

    // Remover a equipa antiga do ficheiro equipas.txt e o ficheiro individual da equipa
    ficheiro = fopen("C:\\Equipas\\equipas.txt", "r");

    //ficheiro temporario para armazenar os dados introduzidos temporariamente 
    FILE *ficheiroTemporario = fopen("C:\\Equipas\\temporario.txt", "w");

    int ignorar = 0;

    while (fgets(linhaTexto, sizeof(linhaTexto), ficheiro)) {
        if (strncmp(linhaTexto, "Equipa:", 7) == 0) {
            char nomeEquipaLinha[100];
            sscanf(linhaTexto, "Equipa: %[^\n]", nomeEquipaLinha);
            ignorar = (strcmp(nomeEquipaLinha, nomeEquipa) == 0);
        }
        if (!ignorar) fputs(linhaTexto, ficheiroTemporario);
    }
    fclose(ficheiro);
    fclose(ficheiroTemporario);

    remove("C:\\Equipas\\equipas.txt");
    rename("C:\\Equipas\\temporario.txt", "C:\\Equipas\\equipas.txt");

    sprintf(caminho, "C:\\Equipas\\%s.txt", nomeEquipa);
    remove(caminho);

    // Pede novos dados e escrever
    system("cls");

    FILE *ficheiroEquipas = fopen("C:\\Equipas\\equipas.txt", "a");
    FILE *ficheiroEquipa = fopen(caminho, "w");

    fprintf(ficheiro, "Equipa: %s\n", nomeEquipa);
    fprintf(ficheiroEquipa, "Equipa: %s\n", nomeEquipa);

    //Treinador
    do{
        printf("Introduza o nome do treinador: ");
        fgets(nomeTreinador, sizeof(nomeTreinador), stdin);
        nomeTreinador[strcspn(nomeTreinador, "\n")] = '\0';

        if(!nomesValidos(nomeTreinador))
        {
            printf("ERRO ! Os elementos da equipa devem conter nomes.\n");
            corErro();
            system("cls");
        }
    }while(!nomesValidos(nomeTreinador));

    fprintf(ficheiro, "Treinador: %s\n", nomeTreinador);
    fprintf(ficheiroEquipa, "Treinador: %s\n", nomeTreinador);
    printf("Treinador registado !\n\n", nomeJogador);


    //Formação tatica
    do{
        printf("Escolha a formacao tatica da sua equipa (ex: 4-3-3): ");
        scanf("%d-%d-%d", &defesas, &medios, &avancados);
        getchar();

        totalJogadores = guardaRedes + defesas + medios + avancados; //= 11 


        if(totalJogadores != 11)
        {
            printf("ERRO ! A sua equipa deve conter 11 jogadores.\n");
            corErro();
            system("cls");
        }
    }while(totalJogadores != 11);

    fprintf(ficheiro, "Formacao Tatica: %d-%d-%d\n\n",  defesas, medios, avancados);
    fprintf(ficheiroEquipa, "Formacao Tatica: %d-%d-%d\n\n",  defesas, medios, avancados);
    printf("Formacao Tatica registada !\n\n", nomeJogador);

    //Guarda Redes
    do{
        printf("Introduza o nome do Guarda Redes: ");
        fgets(nomeJogador, sizeof(nomeJogador), stdin);
        nomeJogador[strcspn(nomeJogador, "\n")] = '\0';
        
        if(!nomesValidos(nomeJogador))
        {
            printf("ERRO ! Os elementos da equipa devem conter nomes.\n");
            corErro();
            system("cls");
        }
    }while (!nomesValidos(nomeJogador));
    
    fprintf(ficheiro,"Guarda Redes: %s\n\n", nomeJogador);
    fprintf(ficheiroEquipa,"Guarda Redes: %s\n\n", nomeJogador);
    printf("Guarda Redes registado !\n\n", nomeJogador);


    //Defesas
    for(int i = 0; i < defesas; i++)
    {
        do{
            printf("Introduza o nome do Defesa: ");
            fgets(nomeJogador, sizeof(nomeJogador), stdin);
            nomeJogador[strcspn(nomeJogador, "\n")] = '\0';

            if(!nomesValidos(nomeJogador))
            {
                printf("ERRO ! Os elementos da equipa devem conter nomes.\n");
                corErro();
                system("cls");
            }
        }while(!nomesValidos(nomeJogador));

        fprintf(ficheiro,"Defesa: %s\n\n", nomeJogador);
        fprintf(ficheiroEquipa,"Defesa: %s\n\n", nomeJogador);
        printf("Defesa registado !\n\n", nomeJogador);
    }

    //Medios
    for(int i = 0; i < medios; i++)
    {
        do{
            printf("Introduza o nome do Medio: ");
            fgets(nomeJogador, sizeof(nomeJogador), stdin);
            nomeJogador[strcspn(nomeJogador, "\n")] = '\0';

            if(!nomesValidos(nomeJogador))
            {
                printf("ERRO ! Os elementos da equipa devem conter nomes.\n");
                corErro();
                system("cls");
            }
        }while(!nomesValidos(nomeJogador));

        fprintf(ficheiro, "Medio: %s\n\n", nomeJogador);
        fprintf(ficheiroEquipa, "Medio: %s\n\n", nomeJogador);
        printf("Medio registado !\n\n", nomeJogador);
    }
    
    //Avançados
    for(int i = 0; i < avancados; i++)
    {
        do{
            printf("Introduza o nome do Avancado: ");
            fgets(nomeJogador, sizeof(nomeJogador), stdin);
            nomeJogador[strcspn(nomeJogador, "\n")] = '\0';
             if(!nomesValidos(nomeJogador))
            {
                printf("ERRO ! Os elementos da equipa devem conter nomes.\n");
                corErro();
                system("cls");
            }
        }while(!nomesValidos(nomeJogador));

        fprintf(ficheiro, "Avancado: %s\n\n", nomeJogador);
        fprintf(ficheiroEquipa, "Avancado: %s\n\n", nomeJogador);
        printf("Avancado registado !\n\n", nomeJogador);  
    }

    fprintf(ficheiro, "-----------------------\n");
    fprintf(ficheiroEquipa, "-----------------------\n");

    fclose(ficheiro);
    fclose(ficheiroEquipa);

    system("cls");
    printf("Equipa editada com sucesso!\n");
    Sleep(2000);;
    system("cls");
}

void apagarEquipa(){
    //abrir ficheiro equipas.txt
    FILE *ficheiro = fopen("C:\\Equipas\\equipas.txt", "r");

    char linhaTexto[100], equipas[100][100];
    int totalEquipas = 0;
    int opcao;

    //menu apresentação
    simbolo(50, '*');
    printf("\t\tApagar Equipas \n");
    simbolo(50, '-');

    while(fgets(linhaTexto, sizeof(linhaTexto), ficheiro)){

        if (strncmp(linhaTexto, "Equipa:", 7) == 0){
            sscanf(linhaTexto, "Equipa: %[^\n]", equipas[totalEquipas]);
            totalEquipas++;
        }
    }
    fclose(ficheiro);

    if(totalEquipas == 0){
        printf("ERRO ! Nenhuma equipa encontrada.\n");
        corErro();
        return;
    }

    // Mostrar equipas
    for (int i = 0; i < totalEquipas; i++) {
        printf("%d - %s\n", i + 1, equipas[i]);
    }

    simbolo(50, '-');
    printf("Selecione a equipa que pretende apagar: ");
    scanf("%d", &opcao);
    getchar();
    system("cls");

    if (opcao < 1 || opcao > totalEquipas) { 
        printf("ERRO ! Opcao invalida.\n");
        corErro();
        return;
    }

    //Sleep
    system("cls");

    ficheiro = fopen("C:\\Equipas\\equipas.txt", "r");
    FILE *ficheiroTemporario = fopen("C:\\Equipas\\temporario.txt", "w");

    int ignorar = 0;

    while (fgets(linhaTexto, sizeof(linhaTexto), ficheiro)) {
        // se for uma linha que começa uma nova equipa
        if (strncmp(linhaTexto, "Equipa:", 7) == 0) {
            char nomeEquipa[100];
            sscanf(linhaTexto, "Equipa: %[^\n]", nomeEquipa);

            if (strcmp(nomeEquipa, equipas[opcao - 1]) == 0)
                ignorar = 1;
            else
                ignorar = 0;
        }
        if (!ignorar)
            fputs(linhaTexto, ficheiroTemporario);
    }

    fclose(ficheiro);
    fclose(ficheiroTemporario);

    // Substituir ficheiro equipas.txt
    remove("C:\\Equipas\\equipas.txt");
    rename("C:\\Equipas\\temporario.txt", "C:\\Equipas\\equipas.txt");
    
    //Elimina o ficheiro destinado à equipa
    char caminho[100];

    sprintf(caminho, "C:\\Equipas\\%s.txt", equipas[opcao - 1]);
    remove(caminho);

    system("cls");
    printf("Equipa apagada com sucesso!\n");
    printf("Pressione qualquer tecla para voltar ao menu");
    getchar();
    system("cls");
} 

int main(){

int opcao;

    do{
        simbolo(50, '*');
        printf("\tEquipas de Futebol | Menu Principal \n");
        simbolo(50, '-');
        printf("\t1 - Ver equipas\n");
        printf("\t2 - Pesquisar equipa\n");
        printf("\t3 - Adicionar equipa\n");
        printf("\t4 - Editar Equipa\n");
        printf("\t5 - Apagar equipa\n");
        printf("\t0 - Sair\n");
        simbolo(50, '-');
        printf("Escolha o que pretende desempenhar: ");
        opcao = getche();
        system("cls");

        switch (opcao)
        {
        case '1':
            verEquipas();
            break;

        case '2':
            pesquisarEquipas();
            break;

        case '3':
            adicionarEquipa();
            break;

        case '4':
            editarEquipa();
            break;

        case '5':
            apagarEquipa();
            break;

        case '0':
            printf("Saiu do programa !");
            corSairPrograma();    
            return 0;

        default:
            printf("ERRO ! Opcao invalida.\n");
            corErro();
            break;
        }
    } while (opcao != 0);
}
