#include "jogo.h"

int main() {
    struct jogo jogos[MAX_JOGOS];
    struct usuario usuarios[MAX_USUARIOS];
    int qtd_jogos = carregar_jogos("jogos.txt", jogos); 
    int qtd_usuarios = carregar_usuarios("usuarios.txt", usuarios);
   
    int opcao;
    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar(usuarios, &qtd_usuarios);
                salvar_usuarios("usuarios.txt", usuarios, qtd_usuarios); 
                break;
            case 2:
                login_usuario(usuarios, qtd_usuarios);
                break;
            case 3:
                listar_usuarios(usuarios, qtd_usuarios);
                break;
            case 4:
                cadastrar_jogo(jogos, &qtd_jogos);
                salvar_jogos("jogos.txt", jogos, qtd_jogos); 
                break;
            case 5:
                listar_jogos(jogos, qtd_jogos);
                break;
            case 6:
                meus_jogos(usuarios, qtd_usuarios, jogos, qtd_jogos);
                break;
            case 7:
                excluir_jogo(jogos, &qtd_jogos);
                salvar_jogos("jogos.txt", jogos, qtd_jogos); 
                break;
            case 8:
                comprar_jogo(usuarios, qtd_usuarios, jogos, qtd_jogos);
                break;
            case 9:
                editar_senha(usuarios, qtd_usuarios);
                salvar_usuarios("usuarios.txt", usuarios, qtd_usuarios); 
                break;

            case 10:
                excluir_usuario(usuarios, &qtd_usuarios);
                salvar_usuarios("usuarios.txt", usuarios, qtd_usuarios);
                break;

            case 0:
                salvar_usuarios("usuarios.txt", usuarios, qtd_usuarios);
                salvar_jogos("jogos.txt", jogos, qtd_jogos);
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}