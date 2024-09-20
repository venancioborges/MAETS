
#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <string.h>


#define MAX_JOGOS 50
#define MAX_USUARIOS 20
#define MAX_NOME 50
#define MAX_EMAIL 80
#define MAX_COMPRAS 100

struct jogo {
    int id;
    char nome[MAX_NOME + 1];
    float preco;
};

struct usuario {
    char username[MAX_NOME + 1];
    char password[MAX_NOME + 1];
    char email[MAX_EMAIL];
    int compras[MAX_COMPRAS]; 
    int qtd_compras;
};

int validar_email(const char *email, struct usuario usuarios[], int qtd_usuarios);

void cadastrar(struct usuario usuarios[], int *qtd_usuarios);

void listar_usuarios(struct usuario usuarios[], int qtd_usuarios);

void cadastrar_jogo(struct jogo jogos[], int *qtd_jogos);

void listar_jogos(struct jogo jogos[], int qtd_jogos);

void salvar_usuarios(const char *nome_arquivo, struct usuario usuarios[], int qtd_usuarios);

int carregar_usuarios(const char *nome_arquivo, struct usuario usuarios[]);

void salvar_jogos(const char *nome_arquivo, struct jogo jogos[], int qtd_jogos);

int carregar_jogos(const char *nome_arquivo, struct jogo jogos[]);

void comprar_jogo(struct usuario usuarios[], int qtd_usuarios, struct jogo jogos[], int qtd_jogos);

void editar_senha(struct usuario usuarios[], int qtd_usuarios);

int login_usuario(struct usuario usuarios[], int qtd_usuarios);

void meus_jogos(struct usuario usuarios[], int qtd_usuarios, struct jogo jogos[], int qtd_jogos);

void excluir_jogo(struct jogo jogos[], int *qtd_jogos);

void excluir_usuario(struct usuario usuarios[], int *qtd_usuarios);

void menu();int buscar_jogo_recursivo(struct jogo jogos[], int esquerda, int direita, int id);

#endif
