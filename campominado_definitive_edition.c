#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char campo_de_verificacao, campo_de_visualizacao;//Um char para a matriz que será visivel e uma de fundo para a verificação de dados
}coordenadas;//Define uma struct de nome coordenadas

void menu()
{
    int i;
    printf("\t\t\t\t\t****************\n\t\t\t\t\t**CAMPO MINADO**\n\t\t\t\t\t****************\n\n");

    for(i = 0; i < 97; i++)
        printf("*");

    printf("\n*COMANDOS");
    for(i = 0; i < 11; i++)
        printf("\t");
        printf("*");
    printf("\n*");
    for(i = 0; i < 12; i++)
        printf("\t");
        printf("*");
    printf("\n*Novo: para iniciar um novo jogo");
    for(i = 0; i < 8; i++)
        printf("\t");
        printf("*");
    printf("\n*Jogar x y: para escolher a posicao x y do campo");
    for(i = 0; i < 6; i++)
        printf("\t");
        printf("*");
    printf("\n*Salvar (nome do arquivo sem espacos): para salvar um jogo em andamento");
    for(i = 0; i < 4; i++)
        printf("\t");
        printf("*");
    printf("\n*Abrir (nome do arquivo): para iniciar um jogo ja salvo");
    for(i = 0; i < 6; i++)
        printf("\t");
        printf("*");
    printf("\n*Sair: para sair do jogo");
    for(i = 0; i < 9; i++)
        printf("\t");
        printf("*");
    printf("\n*Resposta: para mostrar a localizacao das bombas do jogo em andamento");
    for(i = 0; i < 4; i++)
        printf("\t");
        printf("*");
    printf("\n*Menu: para chamar o menu do jogo");
    for(i = 0; i < 8; i++)
        printf("\t");
        printf("*");
    printf("\n*Letras maisculas e minusculas sao irrelevantes nos comandos, com excecao para (nome do arquivo)");
    printf("*");
    printf("\n*Para uma melhor experiencia jogue em full screen");
    for(i = 0; i < 6; i++)
        printf("\t");
        printf("*");
    printf("\n");
    for(i = 0; i < 97; i++)
        printf("*");
    printf("\n\n");
}

void resposta(coordenadas **campo, int Linha, int Coluna)
{
    int i, j, l;

    printf("\n");
    //Gera o numero que representa as colunas do campo
    for(l = 0; l < Coluna; l++)
        printf("%6d", l);
    printf("\n\n");
    //Imprime a matriz verificacao que é o campo de resposta
    for(i = 0; i < Linha; i++)
    {
        printf("%2d", i);//Numero de Linhas do cammpo
        for(j = 0; j < Coluna; j++)
            printf("%4c  ", campo[i][j].campo_de_verificacao);
        printf("\n");
    }
    printf("\n\n");
}

void revela_bombas(coordenadas **campo, int Linha, int Coluna)
{
    int i, j, l;

    printf("\n");
    //Gera o numero que representa as colunas do campo
    for(l = 0; l < Coluna; l++)
        printf("%6d", l);
    printf("\n\n");

    for(i = 0; i < Linha; i++)
        {
            printf("%2d", i);//Numero de Linhas do cammpo
            for(j = 0; j < Coluna; j++)
            {
                if(campo[i][j].campo_de_verificacao == '*')//Copia o local das bombas da matriz campo de verificacao para a matriz campo de visualizacao
                    campo[i][j].campo_de_visualizacao = '*';
                printf("%4c  ", campo[i][j].campo_de_visualizacao); //Imprime o estado atual do mapa porém com o local de todas as bombas
            }
            printf("\n");
        }
    printf("\n");
}

void revela_vizinhos(coordenadas **campo, int Linha, int Coluna, int p1, int p2)
{
    int i, j;

    if(campo[p1][p2].campo_de_visualizacao == '.')//Se o ponto for um ponto ainda não escolhido/alterado
        campo[p1][p2].campo_de_visualizacao = campo[p1][p2].campo_de_verificacao;//Armazena a informação do ponto do campo de verificaçao para o ponto do campo de visualizacao

    //Laço que roda ao redor do ponto
    for(i = p1 -1; i <= p1+1; i++)
        for(j = p2 -1; j <= p2+1; j++)
            {
                //Se o ponto existe, é diferente do caracterer 0 no campo de verificacao e ainda não foi escolhido/alterado no campo de visualizacao
                if(i < Linha && i >= 0 && j < Coluna && j >= 0 && (int) campo[i][j].campo_de_verificacao != 48 && campo[i][j].campo_de_visualizacao == '.')
                    campo[i][j].campo_de_visualizacao = campo[i][j].campo_de_verificacao;//Armazena a informação do ponto do campo de verificaçao para o ponto do campo de visualizacao
                //Se o ponto existe, é igual ao caracterer 0 no campo de verificacao e ainda não foi escolhido/alterado no campo de visualizacao
                if(i < Linha && i >= 0 && j < Coluna && j >= 0 && (int)campo[i][j].campo_de_verificacao == 48 && campo[i][j].campo_de_visualizacao == '.')
                    revela_vizinhos(campo, Linha, Coluna, i, j);//Chama a funcao novamente porém nesse novo ponto == 0
            }

}

void revela_mapa(coordenadas **campo, int Linha, int Coluna)
{
    int i, j, l;

    printf("\n");

    //Gera o numero que representa as colunas do campo
    for(l = 0; l < Coluna; l++)
            printf("%6d", l);
        printf("\n\n");

    for(i = 0; i < Linha; i++)
    {
        printf("%2d", i);//Numero de Linhas do cammpo
        for(j = 0; j < Coluna; j++)
            printf("%4c  ", campo[i][j].campo_de_visualizacao);//Estado atual do espaço i j do campo de visualização
        printf("\n");
    }
    printf("\n");
}

void reajusta_espacos_escolhidos(coordenadas **campo, int Linha, int Coluna, int Flag[])
{
    int i, j;

    Flag[0] = 0;//Zera flag para começar a contar

    for(i = 0; i < Linha; i++)
        for(j = 0; j < Coluna; j++)
            if(campo[i][j].campo_de_visualizacao != '.')//Se for um espaço diferente de '.'(simbiliza ainda não escolhido)
                Flag[0] = Flag[0] + 1;//Incrementa 1 para o contador

}

void jogar(coordenadas **campo, int Linha, int Coluna, int Bomba, int p1, int p2, int Flag[])
{

    //Verifica se o ponnto solicitado existe ou já foi escolhido antes
    if((p1 >= Linha || p1 < 0) || (p2 >= Coluna || p2 < 0) || (((int)(campo[p1][p2].campo_de_visualizacao) >= 48) && ((int)(campo[p1][p2].campo_de_visualizacao) <= 58)))
    {
        printf("Jogada invalida!\n");
    }
    else if(campo[p1][p2].campo_de_verificacao == '*')//Caso o lugar seja uma bomba
    {
        revela_bombas(campo, Linha, Coluna);//Revela o mapa até então e o local das bombas
        printf("      yyyyyyyyyy.     +yyyyy:     :yyy+     -yyyo .yyyyyyyyyyyy`         \n"       "    yyNM+///////`   oymMs/hMdy/   oMMMmy+ -yhMMMd -MMMN////////          \n"       "  yyMM//          oyNMs/. -/hMdy/ oMMMMMmydMMMMMd -MMMN                  \n"       " `MMMM`   syyyyy. hMMM/     sMMMo oMMMh/sMd/oMMMd -MMMNyyyyyyyy`         \n"       " `MMMM`   :/mMMM- hMMMdyyyyymMMMo oMMMy ./- :MMMd -MMMN////////          \n"       "  :/MMhy`   mMMM- hMMMs:::::hMMMo oMMMy     :MMMd -MMMN                  \n"       "    :/NMhhhhNMMM- hMMM/     sMMMo oMMMy     :MMMd -MMMNyhhhhhhy`         \n"       "      ::::::::::` -:::.     -:::. .:::-     `:::: `::::::::::::          \n"       "    osssssssss`   +sss-     :sss: :sssssssssss+ .ssssssssssso            \n"       "  ssMMo+++++NMys. hMMM/     sMMMo oMMMd+++++++/ -MMMN+++++oMMss`         \n"       " `MMMM`     mMMM- hMMM/     sMMMo oMMMy         -MMMm     `MMMM`         \n"       " `MMMM`     mMMM- hMMMhs- /sdMMMo oMMMmsssssss+ -MMMm   `ssMMMM`         \n"       " `MMMM`     mMMM- /+mMMMhsdMMMh+- oMMMd+++++++/ -MMMNssssMM++++       \n"       " `MMMM`     mMMM-   :+dMMMMMh+-   oMMMy         -MMMN+oMMMMss      \n"       "  ++MMssssssNMs+`     :+dMy+-     oMMMmsssssss+ -MMMm `+oMMMMss`\n"       "    ++++++++++`         :+-       -+++++++++++/ `+++/    ++++++`\n");
        printf("\n\n");
        Flag[0] = -1;//Coloca Flag em -1 para simbolizar fim de jogo
    }
    else if((int)campo[p1][p2].campo_de_verificacao != 48)//Se o ponto escolhido é diferente do caracterer 0
    {
        campo[p1][p2].campo_de_visualizacao = campo[p1][p2].campo_de_verificacao;//Armazena esse ponto na matriz de visualizacao
        revela_mapa(campo, Linha, Coluna);//Função para mostrar o mapa em estado atual
        reajusta_espacos_escolhidos(campo, Linha, Coluna, Flag);//Função para contar os espaços já escolhidos

        if(Flag[0] == ((Linha*Coluna) - Bomba))//Se Flag é igual ao numero maximo de espaços possiveis de escolher o jogo termina e você ganhou
        {
            printf("              -::/:-:-..////////////////oshmmmhs+-`     ...-----://:--+s----------/--dmmmmmmmmh///////:.\n""                       -///////////+shmmmmmmmh-::-.     ..----+so+/++o/--------------ommmmmmmmy/////////-`  \n""                      -//////////ymmmmmmmmmmN/-----`    .----so-sooos/--------------//mmmmmmmmm///:-::///:` \n""                    .://:-..////yMNmmmmmmmmmN:----..    ----:h:/y--+:s+-------------::dmmmmmmmNs//:    `.--`\n""                    --.`  `:////+NNmmmmmmmmmN+s:--..`  `----oh+-oooo-+s---------------hmmmmmmmmd///-        \n""                          -////:+NNNmmmmmmmmm+-----..  `---:h+y+:::/os:---------------hmmmmmmmmd``-:.       \n""                         .//:.` +MNmmmmmmmmmmy-------` .--./o++/////:-------------/o--dmmmmmmmmm`           \n""                        `:-`    .NNmmmmmmmmmmm:--+----.-------:::///////++++o+++++//+ymmmmmmmmmm`           \n""                        ``      :NNmmmmmmmmmmNh:-//::/+ssyhddmmmmmmddddhhhhhhhhhdddmddmmmmmmmmmmo           \n""                               /NMNNmmmmmmmmmNmmmmmmdhyysoo+//:::-------------:/o++:-----://+yydy.          \n""                              +NNMNNmmmmmmmdhhyssooos+/-....................:/+o+//:-........::+-..         \n""                            `oNNNMMMNmhyo/::----/osyhhyyo/-....-.-...-...-:+yyyhyyssyy+-......//../`        \n""                      ```.:smNNNhosy/o---....-oyo/ossyyhhso+:.-::-...-/-://y+sooooo-.:yh-.....++./:.`       \n""                   -+hmmmmNNNNNy-../-+.......+y. /oohyos:/---..-..........-..sosy+o+  ++......o:-s:..       \n""                  odmmNNNNNNNNN/:+-:/+.........  :ooso/o` ...............-.` :ooo//.  ........:-/o+-.`      \n""                  ````.-/shmNNh.+/+-+o..........---:/+/-.`....................-:/:::/...........o:o-.`      \n""                          `.----+:/+:o..........-:///:::/:...................---------:::::::--./++/..      \n""                              `-::/+/-.........--......--................................--------+o-.       \n""                              ..-://+.....--:::--::--.........................................:+++/.`       \n""                              `...+/+.-:::---.::-----:/-.............................-:---....:y+:.`        \n""                               `..+/+--+.....::.......-/:.............................---:::--//-.`         \n""                                 .-/+/:/.....+-.........::......-:/:-://-...................--o...          \n""                                  `.://::...-o-..........:-....-://////:-............--......./.``          \n""                           ````````//--.+--:-/:.........../-.....---:--...--------:-.-::-.....`             \n""                          `.-/....://---/o/--:+...........-/-------------------.-o/-...-::-..`              \n""                          `.+....:-.`    ./.`.+............+```         ```````.::.......-/:.               \n""                         `.-/...-:.`     -`   +-...........s:::----:------------..........:+  `             \n""                         `./-.../..`    `-    +-...........+............................-:/`  `             \n""                         `.:..../..     :     +-...........+---.......................--/:` `..`  ``        \n""                         `.....-:..    `-     /:.........../``.::----...............--//o..--```  ``        \n""                         `.....::..    -.     -+.........../`  `-  ``-///:--......-:/+s::-:-.``...  `       \n""                       `..-....:-.`   `+.`    :/...........-:   -     .++++++o+o++ooss+.`   `..  .-         \n""                      `..:....-:...-://o++//:-+-.-..........:.  ..     :+++++++oso+++++++-    `-  :         \n""                     `../---:/s/+++++oo++oooos:..://:--------/..:/-----:o++++++++os++++++o.    -` : `       \n""                   `-+::o+ooooo+o++++++++++o+:-...--///::::------..........--:o+++so++++++/    .- :         \n""                 .+hmmy+++oo+oo+++++++++++o/:-................................-o++ss++++++o    ....         \n""               .odmhy+++oo+oo++++++++++++o//:..................................o++ss++++++o    : .          \n""               +dmhso+++o++o+++++++++++++++:::-...............................-:o++os++++++o    -            \n""               .smmso++++o++o++++++++++++++o+:/::-..........--..........-----::///+++oo+++++++                 \n""               .mmdoo++++o++o+++++++++++++++o+::::-.....----::-....----::::////:-../+os+++++++:      .          \n""               sNd+o++++o++o+++++++++++++++oys:://::::::://+/----::://////::-......-ooo++++++o`   `  :          \n""               -md+oo+++o++o+++++++++++++++ss/s:/://///+++///:/++o+::::-............:oos++++++/   `.  :          \n"  "               sd++o++++s++o++++++++++++++ss::o:////++////::////:-...............--/o+oo+++++o`   :  `o/`        \n""               .h++s++++oo+s++++++++++++++sy/:/o://////////:::-................--://++oo++++++:   `-  +mmh.       \n" "               /+++o++++s++s+++++++++++++oy/::/o:///////::-....----.......---::///-..oos+++++/    :`/ymmmmh`      \n""               `o++o+++++s++s+++++++++++++ss/:::o////////:-----:::-.----::://+//-.....yo++++++```:sdmmmmmmmmy      \n""               -+++s++++oy+oo++++++++++++oy+::::/o///////:://///:::::///++//:-.....--+ys++oos+odNNNmmmmmmmmmm:     \n""               ++++o+++osy+oo++++++++++++sy/:::///+/////++++++////+o++/:-......---:/+/+ssyssssoodmmmmmmmmmmmmh`    \n""               ++++++++osho+o++++++++++++sh///://///o///////////+/+:------:::::://++:/:o-soo+++++mmmmmmmmmNmmm+    \n""               ++++++++sshsos++++++++++++sy//////////o::///////////:::////:////++//////yo++++++++ommmmmmmmmNmmm-   \n""               :+++++++ssyysy++++++++oooosyo////////:+/://////////://:////:/++//////:/ooss++++++++yNmmmmmmmNmmmd`\n\n");
            printf("/sssso   `ossss/  ``/ssssssssssss.`   sssss:     `ossss/               `sssss:     `ossss/   :ssssssssssssss/  ossss/``   `ossss/ \n"":oooo+`  `+oooo: `+oooo:``````ooooo: `ooooo:     `+oooo:               `ooooo:     `+oooo:    ````/oooo+````` `ooooooo+`  `+oooo: \n"":oooo+   `+oooo: `ooooo:     `+oooo: `ooooo:     `+oooo:               `ooooo:     `+oooo:        /oooo+      `oooooooo++.`+oooo: \n"".-:ooo::::ooo:-. `ooooo:     `+oooo: `ooooo:     `+oooo:               `ooooo: -::.`+oooo:        /oooo+      `oooooooooo/:ooooo: \n""  `//oooooo//`   `ooooo:     `+oooo: `ooooo:     `+oooo:               `ooooo/.+oo:.+oooo:        /oooo+      `ooooo+/oooooooooo: \n""    / ssss/      `ossss:     `ossss: `ossss:     `ossss:               `osssssssossssssss:        /oooo+      `ossss: /sssssssss: \n""     +ssss+      `ossss:     `ossss/ `ossss:     `ossss/               `osssssso`-sssssss/        /sssso      `ossss:   -sssssss/ \n""     /oooo/         :oooooooooooo`      :oooooooooooo`                 `ooooo:     `+oooo:   :oooooooooooooo:  ooooo:     `+oooo: \n""     ......         `............       `............                   .....`      .....`   `..............`  .....`      .....` \n");
            Flag[0] = -1;//Coloca Flag em -1 para simbolizar fim de jogo
        }
    }
    else//Entrar aqui significa que o ponto escolhido é igual ao caracterer 0
    {
        revela_vizinhos(campo, Linha, Coluna, p1, p2);//Função recursiva para abrir espaços vizinhos
        revela_mapa(campo, Linha, Coluna);//Função para mostrar o mapa em estado atual
        reajusta_espacos_escolhidos(campo, Linha, Coluna, Flag);//Função para contar os espaços já escolhidos

        if(Flag[0] == ((Linha*Coluna) - Bomba))//Se Flag é igual ao numero maximo de espaços possiveis de escolher o jogo termina e você ganhou
        {
            printf("              -::/:-:-..////////////////oshmmmhs+-`     ...-----://:--+s----------/--dmmmmmmmmh///////:.\n""                       -///////////+shmmmmmmmh-::-.     ..----+so+/++o/--------------ommmmmmmmy/////////-`  \n""                      -//////////ymmmmmmmmmmN/-----`    .----so-sooos/--------------//mmmmmmmmm///:-::///:` \n""                    .://:-..////yMNmmmmmmmmmN:----..    ----:h:/y--+:s+-------------::dmmmmmmmNs//:    `.--`\n""                    --.`  `:////+NNmmmmmmmmmN+s:--..`  `----oh+-oooo-+s---------------hmmmmmmmmd///-        \n""                          -////:+NNNmmmmmmmmm+-----..  `---:h+y+:::/os:---------------hmmmmmmmmd``-:.       \n""                         .//:.` +MNmmmmmmmmmmy-------` .--./o++/////:-------------/o--dmmmmmmmmm`           \n""                        `:-`    .NNmmmmmmmmmmm:--+----.-------:::///////++++o+++++//+ymmmmmmmmmm`           \n""                        ``      :NNmmmmmmmmmmNh:-//::/+ssyhddmmmmmmddddhhhhhhhhhdddmddmmmmmmmmmmo           \n""                               /NMNNmmmmmmmmmNmmmmmmdhyysoo+//:::-------------:/o++:-----://+yydy.          \n""                              +NNMNNmmmmmmmdhhyssooos+/-....................:/+o+//:-........::+-..         \n""                            `oNNNMMMNmhyo/::----/osyhhyyo/-....-.-...-...-:+yyyhyyssyy+-......//../`        \n""                      ```.:smNNNhosy/o---....-oyo/ossyyhhso+:.-::-...-/-://y+sooooo-.:yh-.....++./:.`       \n""                   -+hmmmmNNNNNy-../-+.......+y. /oohyos:/---..-..........-..sosy+o+  ++......o:-s:..       \n""                  odmmNNNNNNNNN/:+-:/+.........  :ooso/o` ...............-.` :ooo//.  ........:-/o+-.`      \n""                  ````.-/shmNNh.+/+-+o..........---:/+/-.`....................-:/:::/...........o:o-.`      \n""                          `.----+:/+:o..........-:///:::/:...................---------:::::::--./++/..      \n""                              `-::/+/-.........--......--................................--------+o-.       \n""                              ..-://+.....--:::--::--.........................................:+++/.`       \n""                              `...+/+.-:::---.::-----:/-.............................-:---....:y+:.`        \n""                               `..+/+--+.....::.......-/:.............................---:::--//-.`         \n""                                 .-/+/:/.....+-.........::......-:/:-://-...................--o...          \n""                                  `.://::...-o-..........:-....-://////:-............--......./.``          \n""                           ````````//--.+--:-/:.........../-.....---:--...--------:-.-::-.....`             \n""                          `.-/....://---/o/--:+...........-/-------------------.-o/-...-::-..`              \n""                          `.+....:-.`    ./.`.+............+```         ```````.::.......-/:.               \n""                         `.-/...-:.`     -`   +-...........s:::----:------------..........:+  `             \n""                         `./-.../..`    `-    +-...........+............................-:/`  `             \n""                         `.:..../..     :     +-...........+---.......................--/:` `..`  ``        \n""                         `.....-:..    `-     /:.........../``.::----...............--//o..--```  ``        \n""                         `.....::..    -.     -+.........../`  `-  ``-///:--......-:/+s::-:-.``...  `       \n""                       `..-....:-.`   `+.`    :/...........-:   -     .++++++o+o++ooss+.`   `..  .-         \n""                      `..:....-:...-://o++//:-+-.-..........:.  ..     :+++++++oso+++++++-    `-  :         \n""                     `../---:/s/+++++oo++oooos:..://:--------/..:/-----:o++++++++os++++++o.    -` : `       \n""                   `-+::o+ooooo+o++++++++++o+:-...--///::::------..........--:o+++so++++++/    .- :         \n""                 .+hmmy+++oo+oo+++++++++++o/:-................................-o++ss++++++o    ....         \n""               .odmhy+++oo+oo++++++++++++o//:..................................o++ss++++++o    : .          \n""               +dmhso+++o++o+++++++++++++++:::-...............................-:o++os++++++o    -            \n""               .smmso++++o++o++++++++++++++o+:/::-..........--..........-----::///+++oo+++++++                 \n""               .mmdoo++++o++o+++++++++++++++o+::::-.....----::-....----::::////:-../+os+++++++:      .          \n""               sNd+o++++o++o+++++++++++++++oys:://::::::://+/----::://////::-......-ooo++++++o`   `  :          \n""               -md+oo+++o++o+++++++++++++++ss/s:/://///+++///:/++o+::::-............:oos++++++/   `.  :          \n"  "               sd++o++++s++o++++++++++++++ss::o:////++////::////:-...............--/o+oo+++++o`   :  `o/`        \n""               .h++s++++oo+s++++++++++++++sy/:/o://////////:::-................--://++oo++++++:   `-  +mmh.       \n" "               /+++o++++s++s+++++++++++++oy/::/o:///////::-....----.......---::///-..oos+++++/    :`/ymmmmh`      \n""               `o++o+++++s++s+++++++++++++ss/:::o////////:-----:::-.----::://+//-.....yo++++++```:sdmmmmmmmmy      \n""               -+++s++++oy+oo++++++++++++oy+::::/o///////:://///:::::///++//:-.....--+ys++oos+odNNNmmmmmmmmmm:     \n""               ++++o+++osy+oo++++++++++++sy/:::///+/////++++++////+o++/:-......---:/+/+ssyssssoodmmmmmmmmmmmmh`    \n""               ++++++++osho+o++++++++++++sh///://///o///////////+/+:------:::::://++:/:o-soo+++++mmmmmmmmmNmmm+    \n""               ++++++++sshsos++++++++++++sy//////////o::///////////:::////:////++//////yo++++++++ommmmmmmmmNmmm-   \n""               :+++++++ssyysy++++++++oooosyo////////:+/://////////://:////:/++//////:/ooss++++++++yNmmmmmmmNmmmd`\n\n");
            printf("/sssso   `ossss/  ``/ssssssssssss.`   sssss:     `ossss/               `sssss:     `ossss/   :ssssssssssssss/  ossss/``   `ossss/ \n"":oooo+`  `+oooo: `+oooo:``````ooooo: `ooooo:     `+oooo:               `ooooo:     `+oooo:    ````/oooo+````` `ooooooo+`  `+oooo: \n"":oooo+   `+oooo: `ooooo:     `+oooo: `ooooo:     `+oooo:               `ooooo:     `+oooo:        /oooo+      `oooooooo++.`+oooo: \n"".-:ooo::::ooo:-. `ooooo:     `+oooo: `ooooo:     `+oooo:               `ooooo: -::.`+oooo:        /oooo+      `oooooooooo/:ooooo: \n""  `//oooooo//`   `ooooo:     `+oooo: `ooooo:     `+oooo:               `ooooo/.+oo:.+oooo:        /oooo+      `ooooo+/oooooooooo: \n""    / ssss/      `ossss:     `ossss: `ossss:     `ossss:               `osssssssossssssss:        /oooo+      `ossss: /sssssssss: \n""     +ssss+      `ossss:     `ossss/ `ossss:     `ossss/               `osssssso`-sssssss/        /sssso      `ossss:   -sssssss/ \n""     /oooo/         :oooooooooooo`      :oooooooooooo`                 `ooooo:     `+oooo:   :oooooooooooooo:  ooooo:     `+oooo: \n""     ......         `............       `............                   .....`      .....`   `..............`  .....`      .....` \n");

            printf("\n\n");
            Flag[0] = -1;//Coloca Flag em -1 para simbolizar fim de jogo
        }
    }
}

void preenche_campo(coordenadas **campo, int Linha, int Coluna, int Bomba)
{
    int i, j, x, y, k = 0, i2, j2;
    //x e y--> Variaveis para armazenar uma linha e coluuna aleatoria
    //k--> Variavel servirá para contar quantidade de bombas ao redor para montar a matriz de verificação

    //Preenche as duas matrizes com o caractere '.'

    for(i = 0; i < Linha; i++)
        for(j = 0; j < Coluna; j++)
        {
            campo[i][j].campo_de_verificacao = '.';
            campo[i][j].campo_de_visualizacao = '.';
        }

    for(i = 0; i < Bomba; i++)
        {
            //Gera um numero aleatorio entre 0 e Linha-1, e 0 e Coluna-1
            x = rand() % Linha;
            y = rand() % Coluna;
            if(campo[x][y].campo_de_verificacao == '.')//Verifica se esse espaço na matriz de verificação está "vazio"
                campo[x][y].campo_de_verificacao = '*'; //Armazena o caractere '*' que representa uma bomba
            else//Caso já exista uma bomba no local gerado aleatoriamente decrementa em 1 o contador do laço para não ocorrer de armazenar uma qunatidade menor que o solicitado
                i--;
        }

    for(i = 0; i < Linha; i++)
        for(j = 0; j < Coluna; j++)
        {
            if(campo[i][j].campo_de_verificacao == '.')//Se a posição for um espaço vazio
            {
                for(i2 = i-1; i2 <= i+1; i2++)//roda em volta dessa posição i j
                    for(j2 = j-1; j2 <= j+1; j2++)
                        if(i2 < Linha && j2 < Coluna && i2 >= 0 && j2 >= 0)//Se a posição e i2 j2 que está em volta da i j existir
                            if(campo[i2][j2].campo_de_verificacao == '*')//Se a posição i2 j2 for uma bomba
                                k++;//incrementa 1 para o contador de bombas
                campo[i][j].campo_de_verificacao =  48 + k;//Armazena o caractere 48 + k(48 é o decimal do caracterer 0) a quantidade de bombas ao redor no ponto i j
                k = 0;//Zera a quantidade de bombas para a proxima verificação
            }
        }
}

int main()
{
    coordenadas **campo = NULL;
    //campo-> ponteiro de ponteiro da struct com as variaveis para o tabuleiro

    char comando[10], salvar[15];
    int i, j, ponto_x_escolhido, ponto_y_escolhido, Bomba, Coluna, Linha, Flag[1], INTERRUPTOR = 0;
    //Flag->Vetor para contar quantos espaços vazios o jogador já escolheu
    //ponto_x_escolhido e ponto_y_escolhido-> Variaveis para determinar a posição em coordenadas x y que o jogador escolheu do campo
    //Bomba, Linha e Coluna-> Variaveis para armazenar a quantidade de bombas, linhas e colunas solicitadas pelo jogador
    //INTERRUPTOR-> Variavel para determinar se existe um jogo em andamento
    //Aloca_ou_realoca-> Variavel para determinar se é necessario alocar ou realocar a memoria para um novo jogo, quando é igual a 0 é preciso alocar e quando igual a 1 realocar
    //salvar--> Vetor para armazenar o nome do jogo salvo

    FILE *f;
    //f-> Ponteiro do tipo FILE para abrir e salvar jogos

    //Função para gerar um numero aleatorio de acordo com a data do relogio do computador
    srand(time(NULL));

    menu();//Função que chama o menu do jogo

    do
    {
        fflush(stdin);//Limpa o buffer do teclado, para evitar muitas mensagens caso um comando invalido
        scanf("%s", comando);//Solicita um comando do jogador
        strlwr(comando);//Função que torna todas as letras da string em minusculas

        if(strcmp(comando, "novo") == 0)//Caso o comando seja novo, irá perguntar numero de linhas, bombas, e colunas, para uma serie de verificações
        {
            if(campo != NULL)
            {
                for(i = 0; i < Coluna; i++)
                    free(campo[i]);
                free(campo);
            }

            printf("Numero de linhas: "); scanf("%d", &Linha);
            printf("Numero de colunas: "); scanf("%d", &Coluna);
            printf("Numero de bombas: "); scanf("%d", &Bomba);

            if(Bomba < Linha*Coluna && Bomba > 0 && Linha > 0 && Coluna > 0)//Verifica se é possivel criar um jogo com as especificações solicitadas
            {

                campo = (coordenadas**)malloc(Linha*sizeof(coordenadas*));//Aloca N(numero de linhas) ponteiros que apontam para a struct coordenadas

                for(i = 0; i < Linha; i++)
                    campo[i] = (coordenadas*)malloc(Coluna*sizeof(coordenadas));//Aloca N(numero de colunas) structs para o ponteiro


                if(campo != NULL)// Verifica se foi alocado a memoria com sucesso
                {
                    preenche_campo(campo, Linha, Coluna, Bomba);//preenche as matrizes com os caracteres '.' e '*'
                    //matriz resposta
                    //resposta(campo, Linha, Coluna);
                    revela_mapa(campo, Linha, Coluna);//revela o mapa do jogo em sua forma inicial

                    INTERRUPTOR = 1; //Marca que um jogo foi iniciado
                }
                else//Caso não consiga alocar ou realocar memoria a memoria com sucesso
                    printf("ERRO DE ALOCACAO DE MEMORIA!!!\n");
            }
            else
            {
                printf("Numero de bombas, linhas ou colunas impossivel\n");
            }
        }
        else if(strcmp(comando, "jogar") == 0)
        {
            if(INTERRUPTOR == 1) //Se o jogo está iniciado vc pode escolher um espaço para jogar
            {
                scanf("%d %d", &ponto_x_escolhido, &ponto_y_escolhido);

                jogar(campo, Linha, Coluna, Bomba, ponto_x_escolhido, ponto_y_escolhido, Flag);//Função para analisar o ponto escolhido e como proceder

                if(Flag[0] == -1 || Flag[0] == ((Coluna*Linha) - Bomba))//Verifica se o jogo acabou, caso Flag[0] == -1 significa que o jogador escolheu uma bomba, caso Flag[0] == ((Coluna*Linha) - Bomba) significa que todos os espaços sem bomba foram escolhidos
                {
                    INTERRUPTOR = 0;//Marca que o jogo terminou
                }
            }
            else//caso INTERRUPTOR for igual a 0
                printf("Nao ha jogo em andamento\n");

        }
        else if(strcmp(comando, "salvar") == 0)
        {
            if(INTERRUPTOR == 1)
            {
                scanf("%s", salvar);//Armazena o nome do arquivo salvo

                strcat(salvar, ".txt");//Coloca ao fim do nome do save .txt que será o tipo de arquivo usado para salvar
                if(strlen(salvar) < 15)
                {
                    f = fopen(salvar, "w");//Abre o arquivo em que quer salvar o jogo, caso seja um ja existente o save anterior é perdido

                    if(f != NULL)//Se o ponteiro não apontar para NULL significa que abriu o arquivo
                    {
                        fprintf(f, "%d ", Linha);//Copia para arquivo o numero de linhas
                        fprintf(f, "%d ", Coluna);//Copia para arquivo o numero de colunas
                        fprintf(f, "%d ", Bomba);//Copia para arquivo o numero de bombas
                        fprintf(f, "%d ", Flag[0]);//Copia para arquivo o numero de lugares já escolhidos

                        for(i = 0; i < Linha; i++)
                        {
                            for(j = 0; j < Coluna; j++)
                            {
                                fprintf(f, "%c ", campo[i][j].campo_de_visualizacao);//Copia para arquivo o conteudo da linha i e coluna j do campo minado, campo que o jogador vê
                            }
                        }
                        for(i = 0; i < Linha; i++)
                        {
                            for(j = 0; j < Coluna; j++)
                            {
                                fprintf(f, "%c ", campo[i][j].campo_de_verificacao);//Copia para arquivo o conteudo da linha i e coluna j do campo minado, campo que serve para verificação de conteudo
                            }
                        }
                            fclose(f);//Fecha o arquivo para evitar possiveis problemas de alteração de dados
                            printf("Jogo salvo com sucesso\n");
                    }
                    else if(f == NULL) //Caso o ponteiro aponte para um lugar nulo
                    {
                        printf("Nao foi possivel salvar\n");
                    }
                }
                else
                {
                    printf("Nome de arquivo muito grande\n");
                }
            }
            else//Caso não tenha um jogo iniciado ainda
            {
                printf("Nao existe jogo em andamento para salvar\n");
            }

        }
        else if(strcmp(comando, "abrir") == 0)
        {
            scanf("%s", salvar);//Identifica o save que quer carregar
            strcat(salvar, ".txt");//Adiciona ao final do nome .txt para abrir o arquivo txt de nome da variavel "salvar"

            if(strlen(salvar) < 15)
            {
                f = fopen(salvar, "r");//Abre o arquivo escolhido em forma de leitura

                if(f != NULL)//Se o ponteiro apontar corretamente para o arquivo será diferente de NULL
                {
                    if(campo != NULL)//Caso tenha espaco alocado, desaloca
                    {
                        for(i = 0; i < Coluna; i++)
                            free(campo[i]);
                        free(campo);
                    }

                    fscanf(f, "%d ", &Linha);//Lê o arquivo e registra o conteudo para a sua variavel correspondente
                    fscanf(f, "%d ", &Coluna);
                    fscanf(f, "%d ", &Bomba);
                    fscanf(f, "%d ", &Flag[0]);

                    campo = (coordenadas**)malloc(Linha*sizeof(coordenadas*));//Aloca N(numero de linhas) ponteiros que apontam para a struct coordenadas

                    for(i = 0; i < Linha; i++)
                        campo[i] = (coordenadas*)malloc(Coluna*sizeof(coordenadas));//Aloca N(numero de colunas) structs para o ponteiro

                    if(campo != NULL)//Verifica se foi alocado a memoria com sucesso antes de registrar os caracteres dos campos
                    {
                        for(i = 0; i < Linha; i++)
                        {
                            for(j = 0; j < Coluna; j++)
                            {
                                fscanf(f, "%c ", &campo[i][j].campo_de_visualizacao);//Lê o arquivo e registra o conteudo para a sua variavel na struct correspondente
                            }
                        }
                        for(i = 0; i < Linha; i++)
                        {
                            for(j = 0; j < Coluna; j++)
                            {
                                fscanf(f, "%c ", &campo[i][j].campo_de_verificacao);//Lê o arquivo e registra o conteudo para a sua variavel na struct correspondente
                            }
                        }

                        fclose(f);//Fecha o arquivo para evitar possiveis problemas de alteração de dados

                        revela_mapa(campo, Linha, Coluna);//Revela o mapa como estava quando foi salvo

                        INTERRUPTOR = 1;//Marca que foi iniciado um jogo
                    }
                    else//Caso não seja alocado ou realocado a memoria com sucesso
                    {
                        printf("ERRO DE ALOCACAO!!!!\n");
                        INTERRUPTOR = 0;//Marca que não foi iniciado um jogo
                        fclose(f);//Fecha o arquivo para evitar possiveis problemas de alteração de dados
                    }
                }
                else
                {
                    printf("Esse save nao existe\n");
                }
            }
            else
            {
                printf("Nome de arquivo muito grande\n");
            }
        }
        else if(strcmp(comando, "resposta") == 0)
        {
            if(INTERRUPTOR != 0)//Só é possivel mostrar a respostar caso existe algum jogo em andamento
                resposta(campo, Linha, Coluna);//Função que mostra a resposta do jogo atual para o jogador
            else
                printf("Nao ha jogo em andamento\n");
        }
        else if(strcmp(comando, "menu") == 0)
        {
            menu();//Função para abrir o menu de comando do jogo
        }
        else if(strcmp(comando, "sair") == 0)
        {
            //Desaloca a memoria antes de finalizar o jogo
            if(campo != NULL)
            {
                for(i = 0; i < Coluna; i++)
                {
                    free(campo[i]);//Primeito desaloca cada ponteiro de coluna
                }
                free(campo);//Desaloca ponteiro de ponteiro
            }
        }
        else//Caso sejá solicitado um comando invalido
        {
            printf("Comando invalido!\n");
        }
    }while(strcmp(comando, "sair"));//Enquanto o comando solicitado for diferente de "sair" o jogo continua

    return 0;
}
