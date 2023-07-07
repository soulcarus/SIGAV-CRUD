#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10000

typedef struct evento
{
    char nome[MAX_SIZE];
    char data[MAX_SIZE];
    int capacidade;
    float valor;
    char local[MAX_SIZE];
} evento;

typedef struct usuario
{
    char nome[MAX_SIZE];
    char login[MAX_SIZE];
    char senha[MAX_SIZE];
    char email[MAX_SIZE];
    char telefone[MAX_SIZE];
} usuario;

FILE *file;

// Verifica se um login já existe no arquivo "usuarios.txt"
int verificarLogin(char *login)
{
    file = fopen("usuarios.txt", "r");
    if (file == NULL)
    {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }

    char linha[MAX_SIZE];
    while (fgets(linha, sizeof(linha), file))
    {
        // Extrair o login da linha
        char loginExistente[MAX_SIZE];
        sscanf(linha, "%s", loginExistente);

        // Comparar o login fornecido com o login existente
        if (strcmp(login, loginExistente) == 0)
        {
            fclose(file);
            return 1; // Login já existe
        }
    }

    fclose(file);
    return 0; // Login não existe
}

// Realiza o cadastro de um usuário
void cadastro(char *nome, char *login, char *senha, char *email, char *telefone)
{
    // Verifica se o login já existe
    if (verificarLogin(login))
    {
        printf("Login já existe!\n");
        return;
    }

    usuario novo;

    strcpy(novo.nome, nome);
    strcpy(novo.login, login);
    strcpy(novo.senha, senha);
    strcpy(novo.email, email);
    strcpy(novo.telefone, telefone);

    file = fopen("usuarios.txt", "a");
    if (file == NULL)
    {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }
    fprintf(file, "%s %s %s %s %s\n", novo.login, novo.senha, novo.nome, novo.email, novo.telefone);

    fclose(file);
}

// Verifica se as credenciais (login e senha) são válidas
int verificar_credenciais(char *login, char *senha)
{
    file = fopen("usuarios.txt", "r");
    if (file == NULL)
    {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }

    usuario aux;
    usuario novo;

    strcpy(novo.login, login);
    strcpy(novo.senha, senha);

    while (fscanf(file, "%s %s %s %s %s\n", aux.login, aux.senha, aux.nome, aux.email, aux.telefone) != EOF)
    {
        if (strcmp(novo.login, aux.login) == 0 && strcmp(novo.senha, aux.senha) == 0)
        {
            fclose(file);
            return 1; // Credenciais válidas
        }
    }

    fclose(file);
    return 0; // Credenciais inválidas
}

// Realiza o login de um usuário
int realizarLogin(char *login, char *senha)
{
    if (verificar_credenciais(login, senha))
    {
        printf("Login bem-sucedido\n");
        return 1; // Login válido
    }
    else
    {
        printf("Credenciais inválidas\n");
        return 0; // Login inválido
    }
}

void participar_evento(int num_evento)
{
    evento eventos[MAX_SIZE];
    int num_eventos = 0;

    file = fopen("eventos.txt", "r");
    if (file == NULL)
    {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }

    while (fscanf(file, "%s %s %d %f %s\n", eventos[num_eventos].nome, eventos[num_eventos].data, &eventos[num_eventos].capacidade, &eventos[num_eventos].valor, &eventos[num_eventos].local) != EOF)
        num_eventos += 1;

    fclose(file);

    if (num_evento < 1 || num_evento > num_eventos)
        printf("Número de evento inválido!\n");
    else
    {
        file = fopen("eventos.txt", "w");
        if (file == NULL)
        {
            printf("Erro na abertura do arquivo\n");
            exit(1);
        }

        for (int i = 0; i < num_eventos; i++)
            if (i != num_evento - 1)
                fprintf(file, "%s %s %d %.2f %s\n", eventos[i].nome, eventos[i].data, eventos[i].capacidade, eventos[i].valor, eventos[i].local);
            else
                fprintf(file, "%s %s %d %.2f %s\n", eventos[i].nome, eventos[i].data, eventos[i].capacidade - 1, eventos[i].valor, eventos[i].local);

        fclose(file);
    }
}

int *ler_eventos_usuario(char *login, int *num_eventos)
{
    // Abra o arquivo de eventos do usuário para leitura
    FILE *file = fopen("eventos_usuario.txt", "r");
    if (file == NULL)
    {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }

    // Crie um array para armazenar os números dos eventos
    int *eventos = malloc(MAX_SIZE * sizeof(int));
    *num_eventos = 0;

    // Converta o login de char * para char []
    char login_str[MAX_SIZE];
    strcpy(login_str, login);

    // Leia cada linha do arquivo
    char linha[MAX_SIZE];
    while (fgets(linha, sizeof(linha), file))
    {
        // Extraia o login e os números dos eventos da linha
        char *token = strtok(linha, " ");
        if (strcmp(token, login_str) == 0)
        {
            token = strtok(NULL, " ");
            while (token != NULL)
            {
                int num_evento = atoi(token);
                eventos[*num_eventos] = num_evento;
                (*num_eventos)++;
                token = strtok(NULL, " ");
            }
            break;
        }
    }

    // Feche o arquivo
    fclose(file);

    return eventos;
}

// Adiciona um evento à lista de eventos do usuário
void adicionar_evento_usuario(char *login, int num_evento)
{
    // Crie um arquivo temporário para armazenar as alterações
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        printf("Erro na criação do arquivo temporário\n");
        exit(1);
    }

    // Abra o arquivo de eventos do usuário para leitura
    FILE *file = fopen("eventos_usuario.txt", "r");
    if (file == NULL)
    {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }

    // Verifique se o login já existe no arquivo
    char linha[MAX_SIZE];
    int existe = 0;
    while (fgets(linha, MAX_SIZE, file) != NULL)
    {
        // Extraia o login da linha
        char *login_lido = strtok(linha, " \n");

        if (strcmp(login_lido, login) == 0)
        {
            // Adicione o novo número do evento à linha existente
            fprintf(temp, "%s %d\n", linha, num_evento);
            existe = 1;
        }
        else
        {
            // Copie a linha para o arquivo temporário
            fprintf(temp, "%s", linha);
        }
    }

    // Feche os arquivos
    fclose(file);
    fclose(temp);

    // Substitua o arquivo de eventos do usuário pelo arquivo temporário
    remove("eventos_usuario.txt");
    rename("temp.txt", "eventos_usuario.txt");

    // Se o login não existir no arquivo, adicione-o
    if (!existe)
    {
        // Abra o arquivo de eventos do usuário para gravação
        file = fopen("eventos_usuario.txt", "a");
        if (file == NULL)
        {
            printf("Erro na abertura do arquivo\n");
            exit(1);
        }

        // Adicione o login do usuário e o número do evento ao arquivo
        fprintf(file, "%s %d\n", login, num_evento);

        // Feche o arquivo
        fclose(file);
    }
}

// Adiciona um novo evento à lista de eventos
void adicionar_evento(char *nome, char *data, int capacidade, float valor, char *local)
{
    evento novo;

    strcpy(novo.nome, nome);
    strcpy(novo.data, data);
    novo.capacidade = capacidade;
    novo.valor = valor;
    strcpy(novo.local, local);

    file = fopen("eventos.txt", "a");
    if (file == NULL)
    {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }

    fprintf(file, "%s %s %d %.2f %s\n", novo.nome, novo.data, novo.capacidade, novo.valor, novo.local);

    fclose(file);
}

// Atualiza um evento existente na lista de eventos
void atualizar_evento(int num_evento, char *nome, char *data, int capacidade, float valor, char *local)
{
    evento eventos[MAX_SIZE];
    int num_eventos = 0;

    file = fopen("eventos.txt", "r");
    if (file == NULL)
    {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }

    while (fscanf(file, "%s %s %d %f %s\n", eventos[num_eventos].nome, eventos[num_eventos].data, &eventos[num_eventos].capacidade, &eventos[num_eventos].valor, &eventos[num_eventos].local) != EOF)
        num_eventos += 1;

    fclose(file);

    if (num_evento < 1 || num_evento > num_eventos)
        printf("Número de evento inválido!\n");
    else
    {
        evento *atualizar = &eventos[num_evento - 1];

        strcpy(atualizar->nome, nome);

        strcpy(atualizar->data, data);

        atualizar->capacidade = capacidade;

        atualizar->valor = valor;

        strcpy(atualizar->local, local);

        file = fopen("eventos.txt", "w");
        if (file == NULL)
        {
            printf("Erro na abertura do arquivo\n");
            exit(1);
        }

        for (int i = 0; i < num_eventos; i++)
            fprintf(file, "%s %s %d %.2f %s\n", eventos[i].nome, eventos[i].data, eventos[i].capacidade, eventos[i].valor, eventos[i].local);

        fclose(file);
    }
}

void remover_evento(int num_evento)
{
    evento eventos[MAX_SIZE];
    int num_eventos = 0;

    file = fopen("eventos.txt", "r");
    if (file == NULL)
    {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }

    while (fscanf(file, "%s %s %d %f\n", eventos[num_eventos].nome, eventos[num_eventos].data, &eventos[num_eventos].capacidade, &eventos[num_eventos].valor) != EOF)
        num_eventos += 1;

    fclose(file);

    if (num_evento < 1 || num_evento > num_eventos)
        printf("Número de evento inválido!\n");
    else
    {
        for (int i = num_evento - 1; i < num_eventos - 1; i++)
            eventos[i] = eventos[i + 1];

        num_eventos -= 1;

        file = fopen("eventos.txt", "w");
        if (file == NULL)
        {
            printf("Erro na abertura do arquivo\n");
            exit(1);
        }

        for (int i = 0; i < num_eventos; i++)
            fprintf(file, "oi%s %s %d %.2f\n", eventos[i].nome, eventos[i].data, eventos[i].capacidade, eventos[i].valor);

        fclose(file);
    }
}

int main(int argc, char *argv[])
{
    char *action = argv[1];

    if (strcmp(action, "login") == 0)
    {
        char *login = argv[2];
        char *senha = argv[3];

        realizarLogin(login, senha);
    }
    else if (strcmp(action, "cadastrar") == 0)
    {
        char *login = argv[2];
        char *senha = argv[3];
        char *nome = argv[4];
        char *email = argv[5];
        char *telefone = argv[6];

        cadastro(nome, login, senha, email, telefone);
    }
    else if (strcmp(action, "participar") == 0)
    {
        char *num_evento_str = argv[3];
        char *login = argv[2];

        int num_evento = atoi(num_evento_str);

        adicionar_evento_usuario(login, num_evento);
    }
    else if (strcmp(action, "adicionar") == 0)
    {
        char *nome = argv[2];
        char *data = argv[3];
        char *capacidade_str = argv[4];
        char *valor_str = argv[5];
        char *local = argv[6];

        int capacidade = atoi(capacidade_str);
        float valor = atof(valor_str);

        adicionar_evento(nome, data, capacidade, valor, local);
    }
    else if (strcmp(action, "editar") == 0)
    {
        char *num_evento_str = argv[2];
        char *nome = argv[3];
        char *data = argv[4];
        char *capacidade_str = argv[5];
        char *valor_str = argv[6];
        char *local = argv[7];

        int num_evento = atoi(num_evento_str);
        int capacidade = atoi(capacidade_str);
        float valor = atof(valor_str);

        atualizar_evento(num_evento, nome, data, capacidade, valor, local);
    }
    else if (strcmp(action, "remover") == 0)
    {
        char *num_evento_str = argv[2];

        int num_evento = atoi(num_evento_str);

        remover_evento(num_evento);
    }
    else
    {
        printf("Ação inválida\n");
    }

    return 0;
}
