#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <locale.h>
#include <conio.h>

double total = 0.00; // * Vari�vel Global para facilidade de acesso em outras fun��es e calculos finais * //

    typedef struct qtd // STRUCT * Cont�m o conte�do do estoque, quantidade vendida e valor dos produtos, est� denominada "qtd_produtos" * //
    {
        int estoque[12];
        int qtd_vendida[12];
        float valor_produtos[12];
    } qtd_produtos;

void bemvindo(char email[], char senha[], char usuario[], qtd_produtos *pont_prod) // * Fun��o para a tela inicial de escolha LOGIN ou CADASTRO * //
{
    system("cls"); // * Comando para limpar a tela * //
    int escolha; // * Vari�vel para indicar escolha * //
    system("color 2"); // * Comando para colocar COR ao texto * //

    printf("\t\t\t\t Bem vindo ao sistema de login do bar da UMJ!\n");
    printf("\n\nPara fazer login DIGITE 1, para fazer seu cadastro DIGITE 2\n");
    scanf("%d", &escolha);

    // * Abertura de arquivos para leitura * //
    FILE *pont_email;
    FILE *pont_senha;
    FILE *pont_usuario;

    if(escolha == 1) // * Codi��o para acesso ao LOGIN * //
    {
        pont_email = fopen("email.txt","r"); // * Leitura do TXT com email armazenado a partir da fun��o CADASTRO * //
        fgets(email, "%s", pont_email); // * Lendo do arquivo e atribuindo o conte�do contido la dentro a variavel email * //
        fclose(pont_email); // * Fechamando do arquivo usuario * //

        pont_senha = fopen("senha.txt","r"); // *Leitura do TXT com senha armazenado a partir da fun��o VERIFICASENHA * //
        fgets(senha, "%s", pont_senha); // * Lendo do arquivo e atribuindo o conte�do contido la dentro a variavel senha * //
        fclose(pont_senha); // * Fechamando do arquivo usuario * //

        char x; // * Vari�vel Auxiliar para fazer a troca do caracter na tabela ASCII e devolver para a senha * //

        long int verificador_ascii = 7; // * Vari�vel utilizada para rotacionar o caracter na tabela ASCII * //
        // * DESCRIPTOGRAFANDO *//
        for(int i = 0; senha[i] != '\0'; i++) // * For utilizado para percorrer indice por indice no array e substituir o caracter para cifrar * //
        {
            x = senha[i]; // * Var�avel x ( aux ) recebendo o ind�ce na posi��o i da senha * //
                if(x >= '!' && x <= 'z') // * Verificando se x est� entre '!' && 'z' conforme a tabela ASCII * //
                {
                    x = x - verificador_ascii; // * x ( aux ) recebendo - 7, voltando sua posi��o original da senha conforme a tabela ASCII * //
                    if(x < '!') // * Verificando se tem algum caracter fora dos intervalos determinados na 1� condi��o * //
                    {
                        x = x + 'z' - '!' + 1; // * Se sim, x recebe + o valor de 'z' da tabela ASCII - o valor de '!' + 1, para ajustar e se encaixar nos intervalos entre '!' && '\r' * //
                    }
                    senha[i] = x; // * Senha recebendo seu caracter original, conforme seu n�mero na tabela ASCII * //
                }
            senha[i] = x; // * Senha recebendo seu caracter original, conforme seu n�mero na tabela ASCII * //
        }
        pont_usuario = fopen("usuario.txt","r"); // * Abertura de arquivo para armazenar o nome do usuario e mandar por parametro nas fun��es * //
        fgets(usuario, "%s", pont_usuario);  // * Lendo do arquivo e atribuindo o conte�do contido la dentro a variavel usuario * //
        fclose(pont_usuario); // * Fechamando do arquivo usuario * //

        sleep(3);
        login(email,senha,usuario,pont_prod); // * Chamada de fun��o LOGIN, contendo os parametros declarados * //
    }
    else if(escolha == 2) // * Condi��o para acesso ao cadastro * //
    {
        cadastro(email,senha,usuario,pont_prod); // * Chamada de fun��o CADASTRO, contendo os parametros declarados * //
    }
    else // * ELSE criado para tratamento de erro, caso o usuario tenha digitado algo que esteja fora do esperado * //
    {
        printf("* Op��o (%d) indispon�vel, tente novamente. *\n", escolha);
        sleep(1);
        setbuf(stdin, NULL);
        bemvindo(email, senha, usuario, pont_prod); // * Recurs�o da fun��o para solicitar uma escolha v�lida * //
    }

}
void login (char email[], char senha[], char usuario[], qtd_produtos *pont_prod) // * Fun��o para o sistema de LOGIN * //
{
    system("cls"); // * Comando para limpar a tela * //

    printf("\t\t\t\t\t----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t  LOGIN ADMIN\n");
    printf("\t\t\t\t\t----------------------------------------------\n");

    system("color 0a"); // * Comando para colocar COR ao texto * //
    char new_senha[255]; // * Vari�vel criada para armazenar a senha de LOGIN * //
    char new_email[256]; // * Vari�vel criada para armazenar o email de LOGIN * //
    int compara; // * Vari�vel criada para receber o retorno INT da fun��o STRCMP e comparar se as senhas correspondem * //
    int compara2; // * Vari�vel criada para receber o retorno INT da fun��o STRCMP e comparar se os emails correspondem * //
    int tamanho = 0; // * Vari�vel criada para encrementar dentro do While da senha, para percorrer o array * //
    int contador; // * Contador criado para contar quantas letras tem a string new_email * //

    printf("\n\n\t\t\t\t\tDigite seu email: ");
    setbuf(stdin, NULL); // * Comando utilizado para limpar a m�moria de informa��o de outras vari�vel e garatir uma leitura em um SCANF sem lixo de m�moria * //
    fgets(new_email, 40, stdin);
    printf("\n\n\t\t\t\t\tDigite sua senha: ");

    contador = strlen(new_email); // * Vari�vel Contador recebendo a quantidade de caracteres contidos no email * //

    for(int i = 0; i < contador; i++) // * For para tirar o '\n' do final da string e substituir por final de string representado por '\0' * //
    {
        if(new_email[i] == '\n') // * Quando encontrar o '\n' ele ir� ser substituido pelo '\0' * //
        {
            new_email[i] = '\0';
        }
    }
    do // * Do utilizado para garantir que rode ao menos 1x * //
    {
        new_senha[tamanho] = getch(); // * A fun��o "getch" l� um caracter do usuario e n�o mostra na tela, est� atribuindo o caracter a Vari�vel new_senha *//
        if(new_senha[tamanho] != '\r' && new_senha[tamanho] != '\b' && new_senha[tamanho] != '\t') // * Verificando se o caracter na posi��o tamanho de new_senha � diferente de
        {                                                                                          // '\r' (return), '\b' (backspace) e '\t' (tab) * //
            printf("%c", '*'); // * Se for diferente, printa '*' * //
        }
        if(new_senha[tamanho] == '\b' || new_senha[tamanho] == '\t') // * Verificando se new_senha for igual a '\b' ou new_senha igual a '\t' *//
        {
            tamanho--; // * Decrementar o tamanho para que o array n�o seja percorrido com um caracter n�o valido, assim � compensada a posi��o * //
            if(tamanho < 0) // * Se o tamanho for < 0, a senha n�o pode andar para tr�s no array e ser negativa * //
            {
                tamanho++; // * Ent�o tamanho++ � encrementado para compensar e n�o deixar ficar negativo * //
                printf("%c", ' '); // * � printado na tela um ' ', para que n�o ande sem conter caracteres novos * //
            }
            tamanho--; // * decremento para equilibrar o valor de tamanho, pois, � encremetado quando chega no while * //

            printf("%c", '\b');
            printf("%c", ' '); //  Se new_senha == '\b' (backSpace) ou new_senha == '\t' (tab), a sacada � uma impress�o do \b para substituir o carater apagando ele, em seguida da um espa�o e retornar para posi��o * //
            printf("%c", '\b');
        }
    }
    while(new_senha[tamanho++] != '\r'); // * Condi��o de para do While, quando new_senha receber '\r' (return) * //

    tamanho--; // * tamanho � decrementado para voltar 1 posi��o dentro do array de new_senha * //
    new_senha[tamanho] = '\0'; // * new_senha na posi��o de tamanho atual, recebe '\0' (final de string) * //

        compara = strcmp(senha,new_senha); // * compara recebendo um valor int, de compara��o da fun��o STRCMP, retornando 0 as strings s�o iguais * //
        compara2 = strcmp(email,new_email); // * compara recebendo um valor int, de compara��o da fun��o STRCMP, retornando 0 as strings s�o iguais * //

        if(compara == 0 && compara2 == 0) // * Condi��o caso as strings sejam igual * //
        {
            printf("\n\n\n\t\t\t\t\t\tLOGIN EFETUADO COM SUCESSO!!!!\n");
            sleep(3); // * Comando utilizado para pausar a tela por 3 segundos * /
            menuAdmin(email,senha,usuario,pont_prod); // * Chamada da fun��o menuAdmin * //
        }
        else // * ELSE criado para tratamento de erro, caso o usuario tenha digitado algo que esteja fora do esperado * //
        {
            system("color 0c"); // * Fun��o utilizador para da COR ao texto * //
            printf("\n\n\n\t\t\t\t\t\t  E-mail ou senha incorretos!\n");
            printf("\n\n\n\n\t\t\t\t\t\t       TENTE NOVAMENTE!\n");
            sleep(2);
            login(email,senha,usuario,pont_prod); // * Recurs�o da fun��o LOGIN * //
        }
}
int verifica_senha (char senha[], char new_senha[]) // * Fun��o para verifica��o da igualdade das senhas * //
{
    system("cls"); // * Comando para limpar a tela * //
    int tamanho = 0; // * Vari�vel criada para encrementar dentro do While da senha, para percorrer o array * //
    int compara_senha1; // * Vari�vel criada para receber o retorno INT da fun��o STRCMP e comparar se as senhas correspondem * //
    char new_senha2[80]; // * Vari�vel criada para armazenar a senha de CADASTRO * //

    printf("\nCrie uma senha: \n");
    do // * Do utilizado para garantir que rode ao menos 1x * //
    {
        setbuf(stdin, NULL);
        senha[tamanho] = getch(); // * A fun��o "getch" l� um caracter do usuario e n�o mostra na tela, est� atribuindo o caracter a Vari�vel senha *//
        if(senha[tamanho] !='\r' && senha[tamanho] != '\b' && senha[tamanho] != '\t') // * Verificando se o caracter na posi��o tamanho de senha � diferente * //
        {                                                                             // '\r' (return), '\b' (backspace) e '\t' (tab) * //
            printf("%c", '*'); // * Se for diferente, printa '*' * //
        }
        if(senha[tamanho] == '\b' || senha[tamanho] == '\t')  // * Verificando se new_senha for igual a '\b' ou new_senha igual a '\t' *//
        {
            tamanho--; // * Decrementar o tamanho para que o array n�o seja percorrido com um caracter n�o valido, assim � compensada a posi��o * //
            if(tamanho < 0) // * Se o tamanho for < 0, a senha n�o pode andar para tr�s no array e ser negativa * //
            {
                tamanho++;  // * Ent�o tamanho++ � encrementado para compensar e n�o deixar ficar negativo * //
                printf("%c", ' '); // * � printado na tela um ' ', para que n�o ande sem conter caracteres novos * //
            }
            tamanho--; // * decremento para equilibrar o valor de tamanho, pois, � encremetado quando chega no while * //
            printf("%c", '\b');
            printf("%c", ' '); //  Se senha == '\b' (backSpace) ou senha == '\t' (tab), a sacada � uma impress�o do \b para substituir o carater apagando ele, em seguida da um espa�o e retornar para posi��o * //
            printf("%c", '\b');
        }
    }
    while(senha[tamanho++]!='\r');

    tamanho--;
    senha[tamanho]='\0';

    tamanho = 0;

    printf("\nConfirme sua senha: \n");

    do // * Do utilizado para garantir que rode ao menos 1x * //
    {
        setbuf(stdin, NULL);
        new_senha2[tamanho] = getch();
        if(new_senha2[tamanho] !='\r' && new_senha2[tamanho] != '\b' && new_senha2[tamanho] != '\t')
        {
            printf("%c", '*');
        }
        if(new_senha2[tamanho] == '\b' || new_senha2[tamanho] == '\t')
        {
            tamanho--;
            if(tamanho < 0)
            {
                tamanho++;
                printf("%c", ' ');
            }
            tamanho--;
            printf("%c", '\b');
            printf("%c",' ');
            printf("%c", '\b');
        }
    }
    while(new_senha2[tamanho++]!='\r');

    tamanho--;
    new_senha2[tamanho]='\0';
    FILE* pont_senha;

    if(senha[0] == '\0') // * Condi��o para verificar se a senha est� em branco * //
    {
        printf("\nSua senha n�o pode ser em branco!\n");
        sleep(2);
        verifica_senha(senha, new_senha); // * Recurs�o para fun��o verifica_senha * //
    }
    compara_senha1 = strcmp(senha, new_senha2);

    if(compara_senha1 == 0) // * Condi��o verificando se as strings da senha s�o iguais * //
    {
        char x; // * Vari�vel Auxiliar para fazer a troca do caracter na tabela ASCII e devolver para a senha * //

        long int verificador_ascii = 7; // * Vari�vel utilizada para rotacionar o caracter na tabela ASCII * //
        // * CRIPTOGRAFANDO * //
        for(int i = 0; senha[i] != '\0'; i++) // * For utilizado para percorrer indice por indice no array e substituir o caracter para cifrar * //
        {
            x = senha[i]; // * Var�avel x ( aux ) recebendo o ind�ce na posi��o i da senha * //
                if(x >= '!' && x <= 'z') // * Verificando se x est� entre '!' && 'z' conforme a tabela ASCII * //
                {
                    x = x + verificador_ascii;  // * x ( aux ) recebendo + 7, mudando sua posi��o conforme a tabela ASCII * //
                        if(x > 'z') // * Verificando se tem algum caracter fora dos intervalos determinados na 1� condi��o * //
                        {
                            x = x - 'z' + '!' - 1; // * Se sim, x  recebe - o valor de 'z' da tabela ASCII + o valor de '!' - 1, para ajustar e se encaixar nos intervalos entre '!' && '\r' * //
                        }
                    senha[i] = x; // * Senha recebendo seu caracter original, conforme seu n�mero na tabela ASCII * //
                }
        }
        printf("\n\t\t\t\t\t\tCadastro efetuado com sucesso!!! \n");
        sleep(2);
        pont_senha = fopen("senha.txt","w"); // * Abertura do arquivo do tipo W, para armazenar e substutir o cont�udo contido l� dentro para o atual * //
        fprintf(pont_senha, "%s",senha);
        fclose(pont_senha);
        // * DESCRIPTOGRAFANDO * //
        for(int i = 0; senha[i] != '\0'; i++) // * For utilizado para percorrer indice por indice no array e substituir o caracter para cifrar * //
        {
            x = senha[i]; // * Var�avel x ( aux ) recebendo o ind�ce na posi��o i da senha * //
                if(x >= '!' && x <= 'z') // * Verificando se x est� entre '!' && 'z' conforme a tabela ASCII * //
                {
                    x = x - verificador_ascii; // * x ( aux ) recebendo - 7, mudando sua posi��o e retornando a posi��o original conforme a tabela ASCII * //
                    if(x < '!') // * Verificando se tem algum caracter fora dos intervalos determinados na 1� condi��o * //
                    {
                        x = x + 'z' - '!' + 1; // * Se sim, x  recebe + o valor de 'z' da tabela ASCII - o valor de '!' + 1, para ajustar e se encaixar nos intervalos entre '!' && '\r' * //
                    }
                    senha[i] = x; // * Senha recebendo seu caracter original, conforme seu n�mero na tabela ASCII * //
                }
            senha[i] = x; // * Senha recebendo seu caracter original, conforme seu n�mero na tabela ASCII * //
        }
        return 1; // * Retonando 1 para cadastro, para confirmar a igualdade das senhas * //
    }
    else // * Caso as senhas sejam diferentes * //
    {
        printf("\nSenhas nao correspondem.\n");
        sleep(2);
        verifica_senha(senha, new_senha); // * Recurs�o da fun��o verificar_senha, para serem inseridas novamente * //
    }
}
void cadastro (char email[], char senha[], char usuario[], qtd_produtos *pont_prod) // * Fun��o para o cadastro do usuario administrador do bar * //
{
    system("cls"); // * Comando para limpar a tela * //
    int tam; // * Vari�vel criada para receber a quantidade de caracteres contidos em usuario * //
    int tam2; // * Vari�vel criada para receber a quantidade de caracteres contidos em email * //
    char new_senha2[80]; // * Vari�vel criada para armazenar a new_senha2 de CADASTRO * //

    printf("\t\t\t\t\t****** CADASTRO DE USUARIO ADMIN ******\n");
    system("color 0a"); // * Comando para colocar COR ao texto * //
    printf("\nDigite seu nome: \n");
    setbuf(stdin, NULL); // * Comando utilizado para limpar a m�moria de informa��o de outras vari�vel e garatir uma leitura em um SCANF sem lixo de m�moria * //
    fgets(usuario, 40, stdin);
    tam = strlen(usuario);   // * Vari�vel tam recebendo a quantidade de caracteres contidos no usuario * //
    for(int i = 0; i < tam; i++) // * For percorrendo cada posi��o do usuario para tratamentos de erro * //
    {
        if(usuario[0] < 'a' && islower(usuario[0])) // * Condi��o para impedir que o nome inicialize com algum s�mbolo sem ser letra e verificar se � uma letra minuscula* //
        {
            printf("Seu nome precisa ter pelo menos 1 letra.\n");
            sleep(2);
            cadastro(email, senha, usuario, pont_prod); // * Recurs�o da fun��o CADASTRO * //
        }
        if(usuario[i] == '1' || usuario[i] == '2' || usuario[i] == '3' || usuario[i] == '4' || usuario[i] == '5' || usuario[i] == '6' ||
           usuario[i] == '7' ||usuario[i] == '8' || usuario[i] == '9' || usuario[i] == '0') // * Condi��o para que n�o seja permitido nenhum tipo de n�mero no nome de usuario * //
        {
            printf("Seu nome n�o pode conter numeros.\n");
            sleep(2);
            cadastro(email, senha, usuario, pont_prod); // * Recurs�o da fun��o CADASTRO * //
        }
        if(usuario[0] == '\n') // * Condi��o para que o usuario n�o tente por um nome em branco * //
        {
            printf("Seu nome precisa ter pelo menos 1 letra.\n");
            sleep(2);
            cadastro(email, senha, usuario, pont_prod); // * Recurs�o da fun��o CADASTRO * //
        }
        if(usuario[i] == '@' || usuario[i] == '[' || usuario[i] == ']' || usuario[i] == '_' || usuario[i] == '=') // * Condi��o para impedir que esses caracteres sejam implementados no nome de usuario * //
        {
            printf("Numeros ou caracteres especiais nao sao validos\n");
            sleep(2);
            cadastro(email, senha, usuario, pont_prod); // * Recurs�o da fun��o CADASTRO * //
        }
        if(tam <= 3) // * Condi��o para que s� permita no minimo um nome com 3 letras * //
        {
            printf("Seu nome precisa conter no minimo 3 letras e caracteres especiais n�o s�o permitidos.\n");
            sleep(2);
            cadastro(email, senha, usuario, pont_prod); // * Recurs�o da fun��o CADASTRO * //
        }
        if(!(usuario[i] < 'a' && usuario[i] < '0')) // * Condi��o onde limito os caracteres permitidos, para permitir somenta a passagem de letras conforme a tabela ASCII * //
        {
            continue;
        }
        else if(usuario[i] == ' ') // * Condi��o para permitir o ' ' no usuario * //
        {
            continue;
        }
        else if(usuario[i] == '\n') // * Condi��o para por o final de string '\0' quando for identificado o '\n' no usuario e encerrar o for * //
            {
                usuario[i] = '\0';
                break;
            }
        else
        {
            printf("Numeros ou caracteres especiais nao sao validos\n");
            sleep(2);
            cadastro(email, senha, usuario, pont_prod); // * Recurs�o da fun��o CADASTRO * //
        }
    }
    FILE *pont_usuario;  // * Abertura de arquivo para subscrever do usuario * //

    pont_usuario = fopen("usuario.txt","w"); // * Abrindo o arquivo txt para o usuario * //
    fprintf(pont_usuario,"%s",usuario); // * Printando dentro do arquivo o conte�do contido em usuario * //
    fclose(pont_usuario); // * Fechamento de arquivo do usuario * //

    printf("\nDigite um email: *obs: seu dominio �: @umj.com*\n");

    fgets(email, 40, stdin);
    fflush(stdin);

    tam2 = strlen(email); // * Vari�vel tam2 recebendo a quantidade de caracteres contidos no usuario * //

        for(int i = 0; i < tam ; i++) // * For para percorrer cada posi��o do email para tratamento de erro * //
        {
            if(email[0] < 'a') // * Condi��o para impedir que o nome inicialize com algum s�mbolo sem ser letra e verificar se � uma letra minuscula* //
            {
                printf("Seu endere�o de email precisa comecar com uma letra. Tente novamente.\n");
                sleep(2);
                cadastro(email, senha, usuario, pont_prod); // * Recurs�o da fun��o CADASTRO * //
            }
            if (email[i] == '@') // * condi��o para que n�o permita passar o caracter '@', pois, j� existe um dominio fixo pr�-criado * //
            {
                printf("Voc� j� tem um dominio fixo, n�o � necessario colocar.\n");
                sleep(2);
                cadastro(email, senha, usuario, pont_prod); // * Recurs�o da fun��o CADASTRO * //
            }
            if(!(email[i] < 'a' && email[i] < '0')) // * Condi��o onde limito os caracteres permitidos, para permitir somenta a passagem de letras conforme a tabela ASCII * //
            {
                continue;
            }
            else if(email[i] == '.' || email[i] == '-' || email[i] == '_') // * Condi��o para permitir apenas os caracteres especiais '.', '-' e '_' * //
            {
                continue;
            }
            else if(email[i] == '\n') // * Condi��o para por o final de string '\0' quando for identificado o '\n' no email e encerrar o for * //
            {
                email[i] = '\0';
                break;
            }
            else
            {
                printf("Nao utilize caracteres especial, permitido somente '.', '-', '_'.\n");
                sleep(2);
                cadastro(email, senha, usuario, pont_prod); // * Recurs�o da fun��o CADASTRO * //
            }
        }
        email[tam2 - 1] = '\0'; // * Atribuindo o final de string a email * //

        strcat(email, "@umj.com"); // * Concatenando o dominio criado "@umj.com" ao email * //

        FILE* pont_email; // * Abertura de arquivo para subscrever do email * //

        pont_email = fopen("email.txt","w"); // * Abrindo o arquivo txt para o email * //
        fprintf(pont_email,"%s",email); // * Printando dentro do arquivo o conte�do contido em email * //
        fclose(pont_email); // * Fechamento de arquivo do usuario * //

        printf("\nSeu email �: %s\n\n", email);
        printf("\n\t\t\t\t\tVoce sera redirecionado para criar sua senha\n");
        sleep(3);

        int retorno = verifica_senha(senha, new_senha2); // * Vari�vel retorno recebendo o valor que ser� retornado da fun��o verifica_senha, para confirmar se as senhas s�o iguais ou diferentes * //
        if(retorno == 1) // * Condi��o caso as senhas sejam iguais * //
        {
            login(email, senha, usuario, pont_prod); // * Chamada da fun��o LOGIN * //
        }
}
int main()
{
    setlocale(LC_ALL,"Portuguese"); // * Comando utilizado para trazer o programa para nossa linguagem, e identificar acentos, � e tals * //
    system("mode con:cols=114 lines=30"); // * Comando para inicializar o console com os parametros pre determinados e ter um tamanho especifico * //
    qtd_produtos pont_prod; // * declarando para a strucy um pont_prod que ser� passado seu endere�o de memoria, para acesso via ponteiro nas outras fun��es * //

    char a[80];
    char b[80];
    char c[80];

    bemvindo(a, b, c, &pont_prod);
    //cadastro(a, b, c, &pont_prod);
    //menuAdmin(a, b, c, &pont_prod);

    return 0;
}
void menuAdmin(char email[], char senha[], char usuario[], qtd_produtos *pont_prod)
{
    setbuf(stdin, NULL); // * Comando utilizado para limpar a m�moria de informa��o de outras vari�vel e garatir uma leitura em um SCANF sem lixo de m�moria * //
    int k = 0; // * Vari�vel utilizada para percorrer os arrays das strings na leitura dos arquivos * //
    int count = 0; // * Vari�vel utilizada para receber a quantidade de caracteres contidas em uma variavel e aplicar a ela o final de string '\0' * //

    FILE *pont_qtd_vendidas; // * Abertura de arquivo para leitura * //
    pont_qtd_vendidas = fopen("qtd_vendidas.txt","r"); // * Abrindo o arquivo txt para o qtd_vendida receber os valores * //
    while(!feof(pont_qtd_vendidas)) // * While com condi��o de parada quando identificar o EOF ( Fim do arquivo ) * //
    {
        fscanf(pont_qtd_vendidas,"%d", &pont_prod->qtd_vendida[k]); // * V�riavel qtd_vendida, recebendo os valores do arquivo qtd_vendidas.txt * //
        k++; // * k++ encrementando para percorrer os indices do array * //
    }
    fclose(pont_qtd_vendidas); // * Fechamento de arquivo do pont_qtd_vendidas * //

    FILE *pont_estoque; // * Abertura de arquivo para leitura * //
    k = 0; // * Zerando o K para usar o mesmo nas outras aberturas do arquivo * //

    pont_estoque = fopen("estoque.txt","r"); // * Abrindo o arquivo txt para o estoque receber os valores * //
    while(!feof(pont_estoque)) // * While com condi��o de parada quando identificar o EOF ( Fim do arquivo ) * //
    {
        fscanf(pont_estoque,"%d", &pont_prod->estoque[k]); // * Vari�vel estoque, recebendo os valores do arquivo estoque.txt * //
        k++; // * k++ encrementando para percorrer os indices do array * //
    }
    fclose(pont_estoque); // * Fechamento de arquivo do pont_estoque * //

    FILE *pont_arq; // * Abertura de arquivo para leitura * //

    char cardapio[11][50];
    k = 0; // * Zerando o K para usar o mesmo nas outras aberturas do arquivo * //

    pont_arq = fopen("cardapio.txt","r"); // * Abrindo o arquivo txt para o cardapio receber os produtos * //
    while(!feof(pont_arq)) // * While com condi��o de parada quando identificar o EOF ( Fim do arquivo ) * //
    {
        fgets(cardapio[k],50,pont_arq); // * Vari�vel cardapio, recebendo os produtos do arquivo cardapio.txt * //
        count = strlen(cardapio[k]); // * Vari�vel count recebendo a quantidade de caracteres contida em cardapio * //
        cardapio[k][count - 1] = '\0'; // * Colocando o '\0' (final de string) no cardapio * //
        k++; // * k++ encrementando para percorrer os indices do array * //
    }

    fclose(pont_arq); // * Fechamento de arquivo do pont_arq * //

    FILE* pont_valor; // * Abertura de arquivo para leitura * //

    k = 0; // * Zerando o K para usar o mesmo nas outras aberturas do arquivo * //
    pont_valor = fopen("valor_produtos.txt","r"); // * Abrindo o arquivo txt para o valor_produtos receber os valores * //
    while(!feof(pont_valor)) // * While com condi��o de parada quando identificar o EOF ( Fim do arquivo ) * //
    {
        fscanf(pont_valor,"%f", &pont_prod->valor_produtos[k]); // * V�riavel valor_produtos, recebendo os valores do arquivo valor_produtos.txt * //
        k++; // * k++ encrementando para percorrer os indices do array * //
    }
    fclose(pont_valor); // * Fechamento de arquivo do pont_valor * //

    system("cls"); // * Comando para limpar a tela * //
    int opcoes = -1; // * Vari�vel utilizada para receber a op��o do menuAdmin * //
    char saida; // * Vari�vel utilizada para saber se o Admin deseja encerrar seu expediente * //

    printf("\t\t\t\t############### AREA ADMINISTRATIVA ###############\n\n");

    printf("Ol�, %s!\nBem vindo a sua administra��o. \n\n", usuario);
    printf("1.Adicionar quantidades do estoque\n2.Consultar estoque atual de produtos\n3.Consultar Valores dos Produtos\n\n5.Abrir bar\n\n0.Fechar Bar\n\n\nDigite o que deseja: ");
    setbuf(stdin, NULL); // * Comando utilizado para limpar a m�moria de informa��o de outras vari�vel e garatir uma leitura em um SCANF sem lixo de m�moria * //
    scanf("%d", &opcoes);
    fflush(stdin);

    switch(opcoes)
    {
        case 0: // * Case 0: Op��o para encerrar o expediente * //
            printf("Deseja realmente encerrar o expediente?. Confirma? [s,n]\n");
            scanf("%s", &saida);
            if(saida == 'n') // * Condi��o caso o Admin n�o queira encerrar seu expediente * //
            {
            menuAdmin(email, senha, usuario, pont_prod); // * Recurs�o da fun��o MenuAdmin caso o Admin n�o deseja encerrar * //
            }
            else if(saida == 's') // * Condi��o caso o Admin deseje encerrar o expediente * //
            {
                printf("\nTOTAL VENDIDO NO DIA: R$ %.2lf\n", total);
                system("pause"); // * Comando para pausar a tela e s� encerrar quando for pressionada qualquer tecla * //
                exit(0); // * Fechamento do programa * //
            }
            else // * Qualquer op��o diferente das duas a cima * //
            {
            printf("*Opcao indisponivel*\n");
            sleep(3);
            system("cls"); // * Comando para pausar a tela e s� encerrar quando for pressionada qualquer tecla * //
            menuAdmin(email, senha, usuario, pont_prod); // * Recurs�o da fun��o MenuAdmin * //
            }
        break;
        case 1:
            system("cls");
            printf("\t\t\t\t\t CONTROLE DE ESTOQUE\n");
            for(int i = 0; i < 11; ++i)
            {
                printf("\nDigite a quantidade inicial de:");
                printf("\n%s:", cardapio[i]);
                int num;
                char failnum;
                setbuf(stdin, NULL);
                if(pont_prod->estoque[i] < 0)
                {
                    system("cls");
                    printf("OPERACAO INVALIDA\n");
                    for(int j = 0; j < i; j++)
                    {
                        printf("\n.%s: %d", cardapio[j],pont_prod->estoque[j]);
                    }
                    i--;
                }
                else if(scanf("%d%c", &num, &failnum) != 2 || failnum != '\n')
                {
                    system("cls");
                    printf("OPERACAO INVALIDA\n");
                    for(int j = 0; j < i; j++)
                    {
                        printf("\n.%s: %d", cardapio[j],pont_prod->estoque[j]);
                    }
                    i--;
                }
                else
                {
                    pont_prod->estoque[i] = num;
                }
            }
            pont_estoque = fopen("estoque.txt","w");

            for(int i = 0; i < 11; i++)
            {
                fprintf(pont_estoque,"%d\n", pont_prod->estoque[i]);
            }
            fclose(pont_estoque);
            printf("\t\t\t\t\tVoce sera redirecionado de volta ao menu!\n");
            sleep(2);
            menuAdmin(email, senha, usuario, pont_prod); // * Recurs�o da fun��o MenuAdmin * //
        break;
        case 2:
            printf("\n* ESTOQUE ATUAL *\n");
            system("cls");
            for(int i = 0; i < 11; ++i)
            {
                printf(".%s:(%d)\n", cardapio[i], pont_prod->estoque[i]);
            }
            printf("Tecle ENTER para continuar: ");
            setbuf(stdin, NULL);
            scanf("%c", &opcoes);
            if(opcoes == 10)
            {
                printf("\n\t\t\t\t\tDirecionando de volta para o menu... Aguarde!\n");
                sleep(2);
                menuAdmin(email, senha, usuario, pont_prod);
            }
        break;
        case 3:
            system("cls");
            printf("\n\t\t\t\t\t\tValores atual\n\n");
            for(int i = 0; i < 11; i++)
            {
                printf("%s\nR$%.2f\n\n", cardapio[i], pont_prod->valor_produtos[i]);
            }
            char escolha;
            printf("\nDeseja fazer alguma alteracao no valor de algum produto? [s,n]\n");
            scanf("%s", &escolha);
            escolha = tolower(escolha);
            if(escolha == 'n')
            {
                printf("\n\t\t\t\t\tVoce sera direcionado ao menu novamente\n");
                sleep(3);
                setbuf(stdin, NULL);
                menuAdmin(email, senha, usuario, pont_prod);
            }
            else if(escolha == 's')
            {
                float new_valor;
                int numero = -1;
                int num;
                float num_f;
                char failnum;
                system("cls");
                printf("Lista de produtos\n");
                for(int i = 0; i < 11; i++)
                {
                    printf("[%d] %s\n", i + 1, cardapio[i]);
                }
                printf("\nEscolha qual item voce deseja fazer a alteracao de acordo com seu numero:\n");
                 if((scanf("%d%c", &num, &failnum) != 2 || failnum != '\n'))
                {
                    printf("OPERACAO INVALIDA\n");
                    sleep(2);
                    setbuf(stdin, NULL);
                    menuAdmin(email,senha,usuario,pont_prod);
                }
                if(num <= 0)
                {
                    printf("OPERACAO INVALIDA\n");
                    sleep(2);
                    setbuf(stdin, NULL);
                    menuAdmin(email,senha,usuario,pont_prod);
                }
                else
                {
                    numero = num;
                }
                printf("%s\nValor atual: R$ %.2f\n", cardapio[numero - 1], pont_prod->valor_produtos[numero - 1]);
                printf("\nDigite o novo valor\nR$ ");
                setbuf(stdin, NULL);
                 if((scanf("%f%c", &num_f, &failnum) != 2 || failnum != '\n'))
                {
                    printf("OPERACAO INVALIDA\n");
                    sleep(1);
                    setbuf(stdin, NULL);
                    menuAdmin(email,senha,usuario,pont_prod);
                }
                if(num_f <0)
                {
                    printf("OPERACAO INVALIDA\n");
                    sleep(2);
                    setbuf(stdin, NULL);
                    menuAdmin(email,senha,usuario,pont_prod);
                }
                if(num_f == 0)
                {
                    printf("Voc� n�o pode ter o valor de nenhum produto zerado, n�o se vende de gra�a!\n");
                    sleep(2);
                    setbuf(stdin, NULL);
                    menuAdmin(email,senha,usuario,pont_prod);
                }
                else
                {
                    new_valor = num_f;
                }
                pont_prod->valor_produtos[numero - 1] = new_valor;

                pont_valor = fopen("valor_produtos.txt","w");

                for(int i = 0; i < 11; i++)
                {
                    fprintf(pont_valor,"%.2f\n", pont_prod->valor_produtos[i]);
                }
                fclose(pont_valor);
                pont_valor = fopen("valor_produtos.txt","r");
                    for(int i = 0; i < 11; i++)
                {
                    fscanf(pont_valor,"%f", &pont_prod->valor_produtos[i]);
                }
                fclose(pont_valor);
                printf("\nValor alterado com sucesso, consulte novamente a tabela de valores.");
                sleep(3);
                menuAdmin(email, senha, usuario, pont_prod);
            }
            else
            {
            printf("*Opcao indisponivel*\n");
            sleep(3);
            system("cls");
            menuAdmin(email, senha, usuario, pont_prod);
            }
        break;
        case 5:
            system("cls");
            area_cliente(email, senha, usuario, pont_prod, cardapio);
        break;

        default:
            printf("* Opcao (%d) indisponivel, tente novamente *\n", opcoes);
            sleep(1);
            menuAdmin(email, senha, usuario, pont_prod);
        break;
    }
}
int area_cliente(char email[], char senha[], char usuario[], qtd_produtos *pont_prod, char cardapio[15][50])
{
    system("cls");

    int k = 0;
    int count = 0;
    char mesas[15][50];

    FILE *pont_mesas;
    pont_mesas = fopen("mesas.txt","r");
        while(!feof(pont_mesas))
        {
            fgets(mesas[k],50,pont_mesas);
            count = strlen(mesas[k]);
            mesas[k][count - 1] = '\0';
            k++;
        }
    fclose(pont_mesas);

    FILE *pont_arq;
    setbuf(stdin, NULL);
        pont_arq = fopen("estoque.txt","w");
        for(int i = 0; i < 11; i++)
        {
            fprintf(pont_arq,"%d\n", pont_prod->estoque[i]);
        }
    fclose(pont_arq);

        pont_arq = fopen("estoque.txt","r");
        for(int i = 0; i < 11; i++)
        {
            fscanf(pont_arq, "%d", &pont_prod->estoque[i]);
        }
    fclose(pont_arq);

    int escolha = -1;
    int escolha_mesa;
    printf("\t\t\t   ############### Seja bem vindo ao Boteco UMJ ###############\n");
    printf("1.Escolher sua mesa\n2.Faca seu Pedido\n3.Consultar valores\n4.Encerrar comanda\n\n\n0.Area Administrativa\n\nDigite o que deseja: ");
    scanf("%d", &escolha);
    char continuar;

    switch(escolha)
    {
        case 0:
            printf("\n\t\t\t\t\tRedirecionando para a tela de login...");
            sleep(2);
            login(email, senha, usuario, pont_prod);
        case 1:
                system("cls");
                printf("Escolha sua mesa: \n");
                for(int i = 0; i < 15; i++)
                {
                    printf("%s\n", mesas[i]);
                }
                scanf("%d", &escolha_mesa);
                printf("Mesa escolhida com sucesso!!!\n");
                sleep(2);
                area_cliente(email, senha, usuario, pont_prod, cardapio);

        case 2:
            if(escolha_mesa == -1)
            {
                printf("Voc� n�o pode fazer um pedido, sem estar em uma mesa.\n");
                sleep(2);
                area_cliente(email, senha, usuario, pont_prod, cardapio);
            }
            system("cls");
            printf("\nEscolha o produto e depois a quantidade.\n");
              for(int i = 0; i < 11; ++i)
              {
                    printf("%d.%s\n", i+1, cardapio[i]);
              }
                printf("12.Finalizar\n");
                pedido(email, senha, usuario, pont_prod, cardapio);
        break;
        case 3:
            system("cls");
            printf("\nCardapio\n");
            int tamanho = 0;

            for(int i = 0; i < 11; i++)
            {
                tamanho = strlen(cardapio[i]);
            }
            for(int i = 0; i < 11; ++i)
            {
                printf(".%s - R$ %.2f\n\n", cardapio[i], pont_prod->valor_produtos[i]);
            }
            setbuf(stdin, NULL);
            system("pause");
            area_cliente(email, senha, usuario, pont_prod, cardapio);
        break;
        case 4:
            system("cls");
            fechar_comanda(email, senha, usuario, pont_prod, cardapio);
        break;
        default:
            printf("* Op��o (%d) indispon�vel, tente novamente *\n", escolha);
            sleep(2);
            area_cliente(email, senha, usuario, pont_prod, cardapio);
        break;
  }
return 0;
}
int pedido(char email[],char senha[], char usuario[], qtd_produtos *pont_prod, char cardapio[15][50])
{
    char escolha;
    int produto = -1;
    int num;
    char failnum;

    setbuf(stdin, NULL);
    printf("Digite qual item voc� deseja:\n");
     if((scanf("%d%c", &num, &failnum) != 2 || failnum != '\n'))
    {
        printf("OPERACAO INVALIDA\n");
        pedido(email, senha, usuario, pont_prod, cardapio);
    }
    else
    {
        produto = num;
    }

    if(produto == 0 || produto < 0)
    {
        printf("Op��o invalida.\n");
        pedido(email, senha, usuario, pont_prod, cardapio);
    }
            setbuf(stdin, NULL);
            printf("Quantas unidades de %s ?\n", cardapio[produto - 1]);
            if((scanf("%d%c", &num, &failnum) != 2 || failnum != '\n'))
            {
                printf("OPERACAO INVALIDA\n");
                pedido(email, senha, usuario, pont_prod, cardapio);
            }
            if(num < 0)
            {
                printf("OPERACAO INVALIDA\n");
                pedido(email, senha, usuario, pont_prod, cardapio);
            }
            pont_prod->qtd_vendida[produto - 1] = num;

            if(pont_prod->qtd_vendida[produto - 1] == 0)
            {
                printf("Pedido invalido, n�o � possivel vender 0 produtos.\n");
                pedido(email, senha, usuario, pont_prod, cardapio);
            }
            if(pont_prod->qtd_vendida[produto - 1] > pont_prod->estoque[produto - 1])
            {
                printf("* Infelizmente essa quantidade de %s esta indisponivel, quantidade atual (%d), digite novamente. *\n",cardapio[produto - 1], pont_prod->estoque[produto - 1]);
                pedido(email, senha, usuario, pont_prod, cardapio);
            }
            else if(pont_prod->qtd_vendida[produto - 1] <= pont_prod->estoque[produto - 1])
            {
                pont_prod->estoque[produto - 1] -= pont_prod->qtd_vendida[produto - 1];
                printf("DESEJA FAZER OUTRO PEDIDO? S,N\n");
                setbuf(stdin, NULL);
                scanf("%c", &escolha);
                escolha = tolower(escolha);
                if(escolha == 's')
                {
                    pedido(email, senha, usuario, pont_prod, cardapio);
                }
                else if(escolha == 'n')
                {
                    printf("\n\t\t\t\tAgrade�emos a prefer�ncia, at� a pr�xima ! \n");
                    sleep(2);
                    area_cliente(email, senha, usuario, pont_prod, cardapio);
                }
                else
                {
                    printf("Op��o invalida, retornando para o menu com seus pedidos atuais salvos...\n");
                    sleep(3);
                    area_cliente(email, senha, usuario, pont_prod, cardapio);
                }
            }
            else
            {
                printf("* Op��o (%d) indispon�vel, tente novamente. *\n", produto);
                pedido(email, senha, usuario, pont_prod, cardapio);
            }
return 0;
}
void fechar_comanda(char email[], char senha[], char usuario[], qtd_produtos *pont_prod, char cardapio[15][50])
{
    system("cls");
    double valor = 0.00;
    char continuar;

    printf("Seu pedido foi:\n");
    for(int i = 0; i < 11; i++)
    {
        if(pont_prod->qtd_vendida[i] <= 0)
        {
            continue;
        }
        valor += pont_prod->qtd_vendida[i] * pont_prod->valor_produtos[i];
        total += pont_prod->qtd_vendida[i] * pont_prod->valor_produtos[i];
        printf("%d %s\n", pont_prod->qtd_vendida[i], cardapio[i]);
        pont_prod->qtd_vendida[i] = 0;
    }
    printf("\nPedido finalizado com sucesso ! \nTotal = R$ %.2f", valor);
    printf("\nDigite ENTER para continuar: ");
    setbuf(stdin, NULL);
    scanf("%c", &continuar);
        if(continuar == 10)
        {
            area_cliente(email, senha, usuario, pont_prod, cardapio);
        }
}
