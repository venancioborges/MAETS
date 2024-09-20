#include "jogo.h"

int validar_email(const char *email, struct usuario usuarios[], int qtd_usuarios) {
    if (strchr(email, '@') == NULL) {
        printf("E-mail invalido: deve conter o caractere '@'.\n");
        return 0;
    }
    if (strlen(email) >= MAX_EMAIL) {
        printf("E-mail invalido: deve ter menos de 80 caracteres.\n");
        return 0;
    }
    for (int i = 0; i < qtd_usuarios; i++) {
        if (strcmp(email, usuarios[i].email) == 0) {
            printf("E-mail ja cadastrado.\n");
            return 0;
        }
    }
    return 1;
}

void cadastrar(struct usuario usuarios[], int *qtd_usuarios) {
    if (*qtd_usuarios < MAX_USUARIOS) {
        struct usuario novo_usuario = {0}; 
        printf("Informe o nome de usuario: ");
        scanf("%s", novo_usuario.username);
        printf("Informe a senha: ");
        scanf("%s", novo_usuario.password);

        char email[MAX_EMAIL];
        printf("Informe o e-mail: ");
        scanf("%s", email);

        if (validar_email(email, usuarios, *qtd_usuarios)) {
            strcpy(novo_usuario.email, email);
            usuarios[*qtd_usuarios] = novo_usuario;
            (*qtd_usuarios)++;
            printf("Cadastrado com sucesso!\n");
        }
    } else {
        printf("Limite de usuarios alcançado!\n");
    }
}


int login_usuario(struct usuario usuarios[], int qtd_usuarios) {
    char username[MAX_NOME + 1];
    char password[MAX_NOME + 1];

    printf("Digite o nome de usuario: ");
    scanf("%s", username);
    printf("Digite a senha: ");
    scanf("%s", password);

    for (int i = 0; i < qtd_usuarios; i++) {
        if (strcmp(username, usuarios[i].username) == 0 && strcmp(password, usuarios[i].password) == 0) {
            printf("Login bem-sucedido!\n");
            return 1;
        }
    }

    printf("Nome de usuario ou senha incorretos!\n");
    return 0;
}



void listar_usuarios(struct usuario usuarios[], int qtd_usuarios) {
    for (int i = 0; i < qtd_usuarios; i++) {
        printf("Usuario: %s, E-mail: %s\n", usuarios[i].username, usuarios[i].email);
    }
}

void cadastrar_jogo(struct jogo jogos[], int *qtd_jogos) {
    if (*qtd_jogos < MAX_JOGOS) {
        struct jogo novo_jogo;
        printf("Informe o ID do jogo: ");
        scanf("%d", &novo_jogo.id);
        printf("Informe o nome do jogo: ");
        scanf(" %[^\n]%*c", novo_jogo.nome);
        printf("Informe o preco do jogo: ");
        scanf("%f", &novo_jogo.preco);

        jogos[*qtd_jogos] = novo_jogo;
        (*qtd_jogos)++;
        printf("Jogo cadastrado com sucesso!\n");
    } else {
        printf("Limite de jogos alcançado!\n");
    }
}

void comprar_jogo(struct usuario usuarios[], int qtd_usuarios, struct jogo jogos[], int qtd_jogos) {
    char username[MAX_NOME + 1];
    printf("Digite o nome de usuario: ");
    scanf("%s", username);

    struct usuario *usuario_logado = NULL;
    for (int i = 0; i < qtd_usuarios; i++) {
        if (strcmp(username, usuarios[i].username) == 0) {
            usuario_logado = &usuarios[i];
            break;
        }
    }

    if (usuario_logado == NULL) {
        printf("Usuario nao encontrado!\n");
        return;
    }

    int id_jogo;
    printf("Digite o ID do jogo que deseja comprar: ");
    scanf("%d", &id_jogo);

    int index_jogo = buscar_jogo_recursivo(jogos, 0, qtd_jogos - 1, id_jogo);
    if (index_jogo == -1) {
        printf("Jogo com ID %d nao encontrado.\n", id_jogo);
        return;
    }

    if (usuario_logado->qtd_compras < MAX_COMPRAS) {
        usuario_logado->compras[usuario_logado->qtd_compras++] = jogos[index_jogo].id;
        printf("Compra realizada com sucesso!\n");
    } else {
        printf("Limite de compras do usuario alcançado!\n");
    }
}

void editar_senha(struct usuario usuarios[], int qtd_usuarios) {
    char username[MAX_NOME + 1];
    char senha_atual[MAX_NOME + 1];
    char nova_senha[MAX_NOME + 1];

    printf("Digite o nome de usuario: ");
    scanf("%s", username);
    printf("Digite a senha atual: ");
    scanf("%s", senha_atual);

    struct usuario *usuario_logado = NULL;
    for (int i = 0; i < qtd_usuarios; i++) {
        if (strcmp(username, usuarios[i].username) == 0 && strcmp(senha_atual, usuarios[i].password) == 0) {
            usuario_logado = &usuarios[i];
            break;
        }
    }

    if (usuario_logado == NULL) {
        printf("Nome de usuario ou senha atual incorretos!\n");
        return;
    }

    printf("Digite a nova senha: ");
    scanf("%s", nova_senha);
    strcpy(usuario_logado->password, nova_senha);
    printf("Senha alterada com sucesso!\n");
}


void listar_jogos(struct jogo jogos[], int qtd_jogos) {
    for (int i = 0; i < qtd_jogos; i++) {
        printf("Jogo ID: %d, Nome: %s, Preco: %.2f\n", jogos[i].id, jogos[i].nome, jogos[i].preco);
    }
}

void meus_jogos(struct usuario usuarios[], int qtd_usuarios, struct jogo jogos[], int qtd_jogos) {
    char username[MAX_NOME + 1];
    printf("Digite o nome de usuario: ");
    scanf("%s", username);

    struct usuario *usuario_logado = NULL;
    for (int i = 0; i < qtd_usuarios; i++) {
        if (strcmp(username, usuarios[i].username) == 0) {
            usuario_logado = &usuarios[i];
            break;
        }
    }

    if (usuario_logado == NULL) {
        printf("Usuario nao encontrado!\n");
        return;
    }

    if (usuario_logado->qtd_compras == 0) {
        printf("Nenhum jogo comprado ainda.\n");
        return;
    }

    printf("Jogos comprados:\n");
    for (int i = 0; i < usuario_logado->qtd_compras; i++) {
        int id_jogo = usuario_logado->compras[i];
        for (int j = 0; j < qtd_jogos; j++) {
            if (jogos[j].id == id_jogo) {
                printf("Nome: %s, Preco: %.2f\n", jogos[j].nome, jogos[j].preco);
                break;
            }
        }
    }
}

void excluir_jogo(struct jogo jogos[], int *qtd_jogos) {
    int id;
    printf("Informe o ID do jogo a ser excluido: ");
    scanf("%d", &id);

    int index = -1;
    for (int i = 0; i < *qtd_jogos; i++) {
        if (jogos[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Jogo com ID %d nao encontrado.\n", id);
        return;
    }

    for (int i = index; i < *qtd_jogos - 1; i++) {
        jogos[i] = jogos[i + 1];
    }

    (*qtd_jogos)--;
    printf("Jogo excluido com sucesso!\n");
}




void excluir_usuario(struct usuario usuarios[], int *qtd_usuarios) {
    char username[MAX_NOME + 1];
    printf("Informe o nome de usuario a ser excluido: ");
    scanf("%s", username);

    int index = -1;
    for (int i = 0; i < *qtd_usuarios; i++) {
        if (strcmp(usuarios[i].username, username) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Usuario com nome %s nao encontrado.\n", username);
        return;
    }

   
    for (int i = index; i < *qtd_usuarios - 1; i++) {
        usuarios[i] = usuarios[i + 1];
    }

    (*qtd_usuarios)--;
    printf("Usuario excluido com sucesso!\n");
}







void salvar_usuarios(const char *nome_arquivo, struct usuario usuarios[], int qtd_usuarios) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os usuarios.\n");
        return;
    }

    for (int i = 0; i < qtd_usuarios; i++) {
        fprintf(arquivo, "%s %s %s\n", usuarios[i].username, usuarios[i].password, usuarios[i].email);
    }

    fclose(arquivo);
    printf("Usuarios salvos com sucesso!\n");
}

int carregar_usuarios(const char *nome_arquivo, struct usuario usuarios[]) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para carregar os usuarios.\n");
        return 0;
    }

    int qtd_usuarios = 0;
    while (fscanf(arquivo, "%s %s %s", usuarios[qtd_usuarios].username, usuarios[qtd_usuarios].password, usuarios[qtd_usuarios].email) == 3) {
        qtd_usuarios++;
        if (qtd_usuarios >= MAX_USUARIOS) {
            break; 
        }
    }

    fclose(arquivo);
    printf("Usuarios carregados com sucesso: %d usuarios.\n", qtd_usuarios);
    return qtd_usuarios;
}

void salvar_jogos(const char *nome_arquivo, struct jogo jogos[], int qtd_jogos) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os jogos.\n");
        return;
    }

    for (int i = 0; i < qtd_jogos; i++) {
        fprintf(arquivo, "%d %s %.2f\n", jogos[i].id, jogos[i].nome, jogos[i].preco);
    }

    fclose(arquivo);
    printf("Jogos salvos com sucesso!\n");
}

int buscar_jogo_recursivo(struct jogo jogos[], int esquerda, int direita, int id) {
    if (esquerda > direita) {
        return -1;
    }

    int meio = esquerda + (direita - esquerda) / 2;

    if (jogos[meio].id == id) {
        return meio; 
    }

    if (jogos[meio].id > id) {
        return buscar_jogo_recursivo(jogos, esquerda, meio - 1, id); 
    } else {
        return buscar_jogo_recursivo(jogos, meio + 1, direita, id);
    }
}


int carregar_jogos(const char *nome_arquivo, struct jogo jogos[]) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para carregar os jogos.\n");
        return 0;
    }

    int qtd_jogos = 0;
    while (fscanf(arquivo, "%d %s %f", &jogos[qtd_jogos].id, jogos[qtd_jogos].nome, &jogos[qtd_jogos].preco) == 3) {
        qtd_jogos++;
        if (qtd_jogos >= MAX_JOGOS) {
            break; 
        }
    }

    fclose(arquivo);
    printf("Jogos carregados com sucesso: %d jogos.\n", qtd_jogos);
    return qtd_jogos;
}


void menu() {
    printf("=== Bem-vindo a MAETS ===\n");
    printf("1 - Cadastrar\n");
    printf("2 - Login\n");
    printf("3 - Listar Usuarios\n");
    printf("4 - Cadastrar Jogos\n");
    printf("5 - Listar Jogos\n");
    printf("6 - Meus Jogos\n");
    printf("7 - Excluir Jogos\n");
    printf("8 - Comprar Jogos\n");
    printf("9 - Editar Senha\n");
    printf("10 - Excluir Usuario\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}
