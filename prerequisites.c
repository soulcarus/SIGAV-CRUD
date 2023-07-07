#include <stdlib.h>
#include <stdio.h>

FILE *file;

int main(){
    // Criação dos arquivos utilizados
    FILE *usuariosFile = fopen("usuarios.txt", "a");
    if (usuariosFile == NULL)
    {
        printf("Erro na criação do arquivo usuarios.txt\n");
        exit(1);
    }
    fclose(usuariosFile);

    FILE *eventosFile = fopen("eventos.txt", "a");
    if (eventosFile == NULL)
    {
        printf("Erro na criação do arquivo eventos.txt\n");
        exit(1);
    }
    fclose(eventosFile);

    FILE *eventosUsuarioFile = fopen("eventos_usuario.txt", "a");
    if (eventosUsuarioFile == NULL)
    {
        printf("Erro na criação do arquivo eventos_usuario.txt\n");
        exit(1);
    }
    fclose(eventosUsuarioFile);

    return 0;
}