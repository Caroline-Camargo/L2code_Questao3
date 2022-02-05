#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<time.h>

#define plusone 1
#define minusone -1

int main (){

    int num, i, teste, temp, cont, teste1, teste2, op;
    char varsaida[50]="";
    char abc[] = "\n \n";

    time_t inicio_t1, fim_t1,inicio_t2, fim_t2;
    double diff_t1,diff_t2;

    //Criando arquivo de entrada
    FILE *entrada;
    
    //Preenchendo arquivo de entrada de acordo com a escolha do usuário
    i=0;
    printf("\nEscolha uma opcao:");
    while (i==0) {
        printf("\n1. Trabalhar com as constantes ja presentes no arquivo de entrada");
        printf("\n2. Digitar novas constantes no arquivo de entrada  ");
        scanf("\n%d", &op);
        if (op==1){
            entrada = fopen ("algoc.in", "r");
            if (entrada==NULL){
                printf ("ERRO AO ABRIR ARQUIVO");
                return 1;
            }
            i=1;
            cont=0;
            rewind(entrada);

            //Validação do arquivo de entrada
            while (fscanf(entrada, "%d", &num) != EOF) {
                if (num<-32768 || num>32768) {
                    printf("\nERRO DE LEITURA");
                    printf("\nTodas constantes do documento de entrada devem ser inteiros  entre -32768 e 32767");
                    return 1;
                }
                if (num == 0){
                    cont++;
                }
            }
            if (num != 0){
                printf("\nERRO DE LEITURA");
                printf("\nO ultimo numero do documento de entrada deve ser zero");
                return 1;
            }
            if (cont>1){
                printf("\nERRO DE LEITURA");
                printf("\nAs constantes do documento de entrada devem ser inteiros diferentes de zero");
                return 1;
            }
            
        } else if (op==2){
            entrada = fopen ("algoc.in", "w+");
            if (entrada==NULL){
                printf ("ERRO AO ABRIR ARQUIVO");
                return 1;
            }
            i=1;
            printf("\n\nQuantas constantes voce deseja avaliar?:  ");
            scanf("%d", &cont);
            for (i=1; i<=cont; i++) {
                printf("\nDigite a constante %d  ", i);
                scanf("%d", &temp);
                if (temp>-32768 && temp<32768 && temp!=0){
                    fprintf(entrada, "%d\n", temp);
                } else{
                    printf("\nDigite uma constante que seja maior que -32768, menor que 32768 e que seja diferente de 0");
                    i--;
                }
            }
            temp=0;
            fprintf(entrada, "%d", temp);
    
        } else{
            i=0;
            printf("\nEscolha uma opcao entre as disponiveis (1 ou 2)");
        }
    }
    

    //Criando arquivo de saída
    FILE *saida;
    saida = fopen ("algoc.out", "w");
    if (saida==NULL){
        printf ("ERRO AO ABRIR ARQUIVO");
        return 1;
    }

    //Lendo arquivo de entrada e preenchendo arquivo de saída
    rewind(entrada);
    num = 1;
    while (fscanf(entrada, "%d", &num) != EOF) {
        if (num==0){
            return 1;
        }
        fprintf (saida,"Constant %i",num);
        if (num>0){
            teste = plusone;
            fprintf (saida,"\nPlusone");
        } else{
            teste = minusone;
            fprintf (saida,"\nMinusone");
        }

        if (num>1){

            /* Inicio do programa é sempre igual com num > 0, pois   1+1 = 2
                                                                     1*2 = 2
            Logo, a escolha será feita através do tempo, em qual executa mais rápido */
                                                        
            teste1 = teste;
            teste2 = teste;

            time(&inicio_t1);
            teste1 = teste1*2;
            time(&fim_t1); 
            diff_t1 = difftime(inicio_t1, fim_t1);

            time(&inicio_t2);
            teste2 = teste2+1;
            time(&fim_t2); 
            diff_t2 = difftime(inicio_t2, fim_t2);

            if(diff_t1<=diff_t2){
                teste = teste*2;
                fprintf (saida,"\nDup");
            }
            else {
                teste = teste+1;
                fprintf (saida,"\nInc");
            }

            while (teste!=num){
                //dois dups é melhor que um inc + 1 dup
                if (teste*4<=num){
                    teste = (teste*2)*2;
                    fprintf (saida,"\nDup\nDup");
                }

                //Um inc + um dup é melhor um dup
                else if ((teste+1)*2 <= num){
                    teste = (teste+1)*2;
                    fprintf (saida,"\nInc\nDup");
                }

                //um dup é melhor que um inc
                else if (teste*2 <= num){
                    teste = teste*2;
                    fprintf (saida,"\nDup");
                }
                else{
                    teste = teste+1;
                    fprintf (saida,"\nInc");
                }
            }
        }

        if (num<1){
            teste = teste*2;
            fprintf (saida,"\nDup");
            while (teste != num){
                
                //dois dups é melhor que um inc + 1 dup
                if (teste*4>=num){
                    teste = (teste*2)*2;
                    fprintf (saida,"\nDup\nDup");
                }
                
                //Um dup + inc é melhor que um dup
                else if ((teste*2)+1 >= num){
                    teste = (teste*2)+1;
                    fprintf (saida,"\nDup\nInc");
                }
               
                //um dup é melhor que um inc
                else if (teste*2 >= num){
                    teste = teste*2;
                    fprintf (saida,"\nDup");
                }
                else{
                    teste = teste+1;
                    fprintf (saida,"\nInc");
                }
            }     
        }

        fprintf(saida, "%s", &abc);
    }

    fclose(entrada);
    fclose(saida);

}