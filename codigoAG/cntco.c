#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#include "contact.h"
#include "forest.h"
#include "population.h"

int main(int argc, char* argv[]) {
	char* lSolutionFile = NULL;
	char* lAttributeFile = NULL;
	char* lSimulationFile = NULL;
	double lDistance = 0.3;
	int lPopulationSize = 50;
	int read_solution = 1; /// 1;
	// CR ∈ [ 0 , 1 ] is called the crossover probability.
	double CR = 0.5; // 0.2
	// Let F ∈[0, 2] be called the differential weight.
	double F = 0.5; // 0.4
    double maxSec = 30;
    double bound[2]={-50,50};
	int lMaxRun = 10000;    /// 10000 | 1k da menos contatos que 10k (5x7) 300it =4contacts | 400it = 5contacts menos ostensivo
                            /// ostensivo 300it = 4 contacts | 400it = ? realizar teste
	int density = 5; // teste com 15 | 10 |10
    int seed  = 1479650829; /// Seed 1479660410 densidade 5 com 10k iteracoes num contatos # visualizador
	int c;
    while ((c = getopt(argc, argv, "d:s:c:r:")) != -1) {
        printf("Entrou leitura de parametro\n");
    	switch (c) {
			case 'd': density = atoi(optarg); break;
    		case 's': seed = atoi(optarg); break;
    		case 'c': lDistance = atof(optarg); break;
    		// case 'r': read_solution = atoi(optarg); break;
    		//case 'p': lPopulationSize = atoi(optarg); break;
    		//case 'c': CR = atof(optarg); break;
    		//case 'f': F = atof(optarg); break;
    		//case 'r': lMaxRun = atoi(optarg); break;
			default: abort();
    	}
    }
    char directory[300];
    char callingDirectory[300];
    strcpy(callingDirectory, argv[0]);
    printf("callingDirectory:\t%s\n",callingDirectory);
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
        strcat(cwd, "/");
    } else {
        perror("getcwd() error");
        return 1;
    }
    strcpy(directory, cwd);
    char *s;
    if (argc > 1){ // running code from terminal (for forest_solvers.sh)
        s = strstr(directory, "bin/Debug/");
    }
    else{
        s = strstr(directory, "bin/Debug/cntOptimizaton");
    }
    // If executing from .../codigoAG/ shouldn't enter the if bock below
    // If executing from ../codigoAG/bin/Debug should enter the if block below
    if (!strcmp(callingDirectory, "./cntOptimizaton")){ // running from .../codigoAG/bin/Debug/, must enter the if block
        if (argc > 1){
            if (s != NULL)                     // if successful then s now points at "hassasin"
            {
                //printf("Found string at index = %d\n", s - directory);
                strncpy (s,directory,s - directory);
                directory[s-directory] = '\0';
            }
            else
            {
                printf("Current Drectory: %s\n", directory);
                printf("String not found\n");  // `strstr` returns NULL if search string not found
                return -1;
            }
        }
    }


    printf("Current Directory: %s\n", directory);
    //  exit(1);
    char nameAtr[300],nameSim[300],nameSol[300], aux[300];
    /*sprintf(nameAtr,"/home/pedrohen/Documentos/Nanotubos/projetoCNT/data/attributes/forest_attributes_%i_%i_10.txt",seed,density);
    sprintf(nameSim,"/home/pedrohen/Documentos/Nanotubos/projetoCNT/data/simulation/forest_simulation_%i_30_%i_10.txt",seed,density);
    sprintf(nameSol,"/home/pedrohen/Documentos/Nanotubos/projetoCNT/data/solution/forest_solution_%i_hyp_%.1f_30_%i_10.txt",seed,lDistance,density);
    */
    sprintf(nameAtr,"forests/attributes/forest_attributes_%i_%i_10.txt",seed,density);
    sprintf(nameSim,"forests/simulation/forest_simulation_%i_30_%i_10.txt",seed,density);
    sprintf(nameSol,"forests/originalSolution/forest_solution_%i_dir_%.1f_30_%i_10.txt",seed,lDistance,density);  // read Lili's solution

    strcpy(aux, directory);
    strcat(aux, nameAtr);
    strcpy(nameAtr, aux);

    strcpy(aux, directory);
    strcat(aux, nameSim);
    strcpy(nameSim, aux);

    strcpy(aux, directory);
    strcat(aux, nameSol);
    strcpy(nameSol, aux);

    printf("nameAtr:\t%s\n", nameAtr);
    printf("nameSim:\t%s\n", nameSim);
    printf("nameSol:\t%s\n", nameSol);

    //sprintf(nameSol,"/home/pedrohen/Documentos/Nanotubos/gcgtube/build/Release/forest_solution_%i_hyp_%.1f_30_%i_10.txt",seed,lDistance,density);
    ///LILI
    lAttributeFile = nameAtr;
    lSimulationFile = nameSim;
    if(read_solution){
        lSolutionFile = nameSol;
    }
    //lSolutionFile = NULL;
    //lAttributeFile = "/home/pedro/Área de Trabalho/Diversos/CNT/projetoCNT/data/attributes/forest_attributes_1_10_10.txt";
    //lSimulationFile = "/home/pedro/Área de Trabalho/Diversos/CNT/projetoCNT/data/simulation/forest_simulation_1_30_10_10.txt";
	srand(seed);
    forest_t* lForest = forest_create(lDistance);

    if (lSolutionFile == NULL) {
    	if (lAttributeFile != NULL && lSimulationFile != NULL) {
            printf("Leu floresta original!\n");
    		forest_read_attributes(lForest, lAttributeFile);
    		forest_read_simulation(lForest, lSimulationFile);
    		//abort();
    	} else {
    		printf("No data file supplied.\n"); abort();
    	}
    } else {
        printf("Leu solucao inicial!\n");
    	forest_read_attributes(lForest,lAttributeFile);
        forest_read_solution(lForest,lSolutionFile);
    	//abort();
    }

    contact_list_t* lContacts = contact_lookup(lForest);
    printf("NumContatos: %i\n",lContacts->length);
    char testName[300];
    // sprintf(testName,"/home/pedrohen/Documentos/Nanotubos/gcgtube/forests/solution/forest_solution_%i_de_%.1f_30_%i_10_inicial.txt",seed,lDistance,density);
    sprintf(testName,"forests/solution/forest_solution_%i_leuSolution_%.1f_30_%i_10.txt",seed,lDistance,density);

    strcpy(aux, directory);
    strcat(aux, testName);
    strcpy(testName, aux);
    printf("testName:\t%s\n", testName);
    forest_write_simulation(lForest,testName);

    ///abort();  /// OPS
    int initialNumContacts = contact_lookup_total(lForest);
    printf("InitialNumContacts: %i\n", initialNumContacts);
    printf("lDistance: %.1f\n",lDistance);
    population_t* lPopulation = population_build(lPopulationSize, lContacts, lForest);
    population_init(lPopulation, lForest); // Inicializa violacao e custo da populacao
    //population_update_forest(lPopulation, lForest);

    /// Read Lili's solution, generate a txt with infos and quit
    if (read_solution){
        int idxBest = population_best_index(lPopulation);
        char myFileName[300];
        sprintf(myFileName,"forests/solutionLili/forest_solution_%i_originalInfos_%.1f_30_%i_10.txt",seed,lDistance,density);
        strcpy(aux, directory);
        strcat(aux, myFileName);
        strcpy(myFileName, aux);
        printf("myFileName: %s\n",myFileName);
        FILE* myfile = fopen(myFileName, "w");
        fprintf(myfile, "Read Solution\t%i\n", read_solution);
        // no need to print final number of contacts because population wasn't evolved
        fprintf(myfile, "InitialNumContacts\t%i\nFinalNumContacts\t%i\n",initialNumContacts, initialNumContacts);
        fprintf(myfile, "lDistance\t%.2f\n",lDistance);
        fprintf(myfile, "Final Solution: Solution\t%i\t%e\t%e\n", idxBest, lPopulation->solutions[idxBest].violation, lPopulation->solutions[idxBest].cost);
        contact_write_remaining(lContacts, myfile, lForest);
        fclose(myfile);
        printf("Data generated. Exiting\n");
        exit(2);
    }
    printf("lPopulationSize: %i\n",lPopulation->size);
	solution_t lSolution;
	lSolution.size = lPopulation->solutions[0].size;
	printf("lSolutionSize: %i\n",lSolution.size);
	lSolution.length = lPopulation->solutions[0].length;
	printf("lSolutionLength: %i\n",lSolution.length);
	lSolution.points = malloc(sizeof(point_t) * lPopulation->solutions[0].length);
    //printf("Exit aqui\n");

    /*
    char testName[300];
    sprintf(testName,"/home/pedrohen/Documentos/Nanotubos/gcgtube/forests/solution/forest_solution_teste_%i_de_%.1f_30_%i_10.txt",seed,lDistance,density);
    forest_write_simulation(lForest,testName);
    exit(5);
    */

	int imprimiu =0;
	//int imprimiu1=0; // Imprimir informacoes tempo original
	int idxBest = 0;
    time_t start,end;
    double elapsed; // seconds
    int terminate =1;
    char endereco[300];
    sprintf(endereco,"Tempos/forest_%i_%i_%.1f_%i.txt",read_solution,seed,lDistance,density);

    strcpy(aux, directory);
    strcat(aux, endereco);
    strcpy(endereco, aux);
    printf("endereco:\t%s\n", endereco);

    FILE* file = fopen(endereco,"w");
    fprintf(file,"InitialNumContacts: %i\n",initialNumContacts);
    int lRun=0;
    while (++lRun < lMaxRun) {
		printf("Run %d with ", lRun);
    //printf("abriu\n\n");
    start = time(NULL);
    //while(terminate){
        end = time(NULL);
        elapsed = difftime(end,start);
        if(elapsed >= maxSec ){ // Max time
            terminate = 0;
        }
        /*else if(elapsed == 35.0 && imprimiu1 == 0){ // Original time
            printf("Gerando txt!\n");
            population_update_forest(lPopulation,lForest);
            //contact_list_destroy(lContacts);
            //free(lContacts);
            //lContacts = contact_lookup(lForest);
            char name1[300];
            char name2[300];
            sprintf(name1,"/home/pedro/Área de Trabalho/Diversos/CNT/projetoCNT/Resultados/forest_attributes_%i_t_%.1f_%i_10.txt",seed,lDistance,density);
            sprintf(name2,"/home/pedro/Área de Trabalho/Diversos/CNT/projetoCNT/Resultados/forest_solution_%i_t_%.1f_30_%i_10.txt",seed,lDistance,density);
            forest_write_attributes(lForest,name1);
            forest_write_simulation(lForest,name2);
            idxBest = population_best_index(lPopulation);
            fprintf(file,"Tempo de Execucao Original: %f\n",elapsed);
            //printf("Solution %d (V: %lf - C: %lf)\n", idxBest, pPopulation->solutions[idxBest].violation, pPopulation->solutions[idxBest].cost);
            fprintf(file,"Numero de contatos: %i\n",lContacts->length);
            fprintf(file,"Solution Tempo Original: %i (V: %lf - C: %lf)\n",idxBest,lPopulation->solutions[idxBest].violation,lPopulation->solutions[idxBest].cost);
            fprintf(file,"lSolution.Violation: %lf\n",lSolution.violation);
            imprimiu1=1;
        }
        //if(lSolution.violation == 0 && imprimiu == 0){
        if(lPopulation->solutions[population_best_index(lPopulation)].violation == 0 && imprimiu ==0){
            population_update_forest(lPopulation,lForest);
            //contact_list_destroy(lContacts);
            //free(lContacts);
            //lContacts = contact_lookup(lForest);
            char name1[300];
            char name2[300];
            sprintf(name1,"/home/pedro/Área de Trabalho/Diversos/CNT/projetoCNT/Resultados/forest_attributes_%i_v_%.1f_%i_10.txt",seed,lDistance,density);
            sprintf(name2,"/home/pedro/Área de Trabalho/Diversos/CNT/projetoCNT/Resultados/forest_solution_%i_v_%.1f_30_%i_10.txt",seed,lDistance,density);
            forest_write_attributes(lForest,name1);
            forest_write_simulation(lForest,name2);
            idxBest = population_best_index(lPopulation);
            fprintf(file,"Tempo de execucao para zerar contatos: %f\n",elapsed);
            fprintf(file,"Numero de contatos: %i\n",lContacts->length);
            fprintf(file,"Solution Tempo Zerar Contatos: %i (V: %lf - C: %lf)\n",idxBest,lPopulation->solutions[idxBest].violation,lPopulation->solutions[idxBest].cost);
            fprintf(file,"lSolution.Violation: %lf\n",lSolution.violation);
            imprimiu = 1;
            //abort();
        }*/
		population_print_best(lPopulation);
		// Necessario atualizar floresta?!
		//population_update_forest(lPopulation,lForest);
		printf("Rodando solucao S:%i C:%.1f D:%i\n ",seed,lDistance,density);
		printf("Elapsed time: %.2f\n",elapsed);
		int ch[] = {-1, -1, -1, -1};

		// For each agent x in the population do:
		for (int i = 0; i < lPopulation->size; ++i) {
			memcpy(lSolution.points, lPopulation->solutions[i].points, sizeof(point_t) * lPopulation->solutions[i].length);

			// Pick three agents a, b, and c from the population at random, they must be distinct from each other as well as from agent x.
			for (int a = 0; a < 3; ++a) {
				ch[a] = population_pick(lPopulation, i, ch);
			}

			// Pick a random index R ∈ { 1 , … , n } (n being the dimensionality of the problem to be optimized).
			if(lSolution.length == 0){
                printf("Solucionada!\n");
                /*char name4[300];
                sprintf(name4,"/home/pedrohen/Documentos/Nanotubos/projetoCNT/Resultados/forest_solution_%i_%i_fullt_%.1f_30_%i_10.txt",read_solution,seed,lDistance,density);
                forest_write_simulation(lForest,name4);*/
                char testName[300];
                sprintf(testName,"forests/solution/forest_solution_%i_de_%.1f_30_%i_10.txt",seed,lDistance,density);

                strcpy(aux, directory);
                strcat(aux, testName);
                strcpy(testName, aux);
                printf("testName:\t%s\n", testName);

                forest_write_simulation(lForest,testName);
                exit(1);
			}
			int R = rand() % lSolution.length;

			// Compute the agent's potentially new position y = [ y 1 , … , y n ]. y =[y_{1}, ,y_{n}] as follows:
			for (int j = 0; j < lSolution.length; ++j) {
				// For each i ∈ { 1 , … , n }, pick a uniformly distributed number r i ≡ U ( 0 , 1 )
				double Ri = (double) rand() / (double) RAND_MAX;

				// If Ri < CR or i = R then set Yi = Ai + F * (Bi − Ci) otherwise set y i = Xi
				if (Ri < CR || j == R) {
					lSolution.points[j].z = lPopulation->solutions[ch[0]].points[j].z + F * (
						lPopulation->solutions[ch[1]].points[j].z - lPopulation->solutions[ch[2]].points[j].z
					);
				}
				if(lSolution.points[j].z < bound[0]){
                    lSolution.points[j].z = bound[0];
				}
				else if(lSolution.points[j].z > bound[1]){
                    lSolution.points[j].z = bound[1];
				}
			}

			// If f ( y ) < f ( x ) then replace the agent in the population with the improved candidate solution, that is, replace x with y in the population.
			/// Metododo 1 ( menos ostensivo )
			lSolution.violation = population_calc_violation(lPopulation, &lSolution, lForest);


            //solution_update_forest(lSolution, lForest);
            //double b = contact_lookup_violation(lForest);
            //lSolution.violation = contact_lookup_violation(lForest);
            //printf("lSolutionViolation : %e\n",lSolution.violation);

            /// Metodo 2 ( ostensivo )
            //solution_update_forest(lSolution, lForest);
            //lSolution.violation = contact_lookup_violation(lForest);

            //printf("\t%d: %lf (%lf) > \n", i, lPopulation->solutions[i].violation, lPopulation->solutions[i].cost);
			if (lSolution.violation < lPopulation->solutions[i].violation) {
				memcpy(lPopulation->solutions[i].points, lSolution.points, sizeof(point_t) * lPopulation->solutions[i].length);
				lPopulation->solutions[i].violation = lSolution.violation;
				lPopulation->solutions[i].cost = population_calc_cost(&lSolution);
			} else if (lSolution.violation == lPopulation->solutions[i].violation) {
				lSolution.cost = population_calc_cost(&lSolution);
                //printf("If1 dentro\n");
                //printf("lSolutionCost: %lf \nlPopulationCost: %lf",lSolution.cost,lPopulation->solutions[i].cost);
				if (lSolution.cost <= lPopulation->solutions[i].cost) {
					memcpy(lPopulation->solutions[i].points, lSolution.points, sizeof(point_t) * lPopulation->solutions[i].length);
					lPopulation->solutions[i].violation = lSolution.violation;
					lPopulation->solutions[i].cost = lSolution.cost;
					//printf("If dentro\n");
					//exit(1);
				}
			}

			//printf("%lf (%lf)\n", lPopulation->solutions[i].violation, lPopulation->solutions[i].cost);
		}

		//printf("\n");
	}


    /*char testName[300];
    sprintf(testName,"/home/pedrohen/Documentos/Nanotubos/gcgtube/forests/solution/forest_solution_%i_de_%.1f_30_%i_10.txt",seed,lDistance,density);
    forest_write_simulation(lForest,testName);
    exit(5);*/
	population_update_forest(lPopulation, lForest);
    // population_print_best(lPopulation);

    /*
    contact_list_destroy(lContacts);
    free(lContacts);
    printf(" CONTATOS APÒS EVOLUIR POPULACAO\n");
    lContacts = contact_lookup(lForest);
    */
    lContacts = contact_lookup(lForest); // updates lContacts for printing remaining contacts
	idxBest = population_best_index(lPopulation);
    //lSolution.violation = population_calc_violation(lPopulation, &lSolution, lForest);
    //printf("lSolution.violation: %lf\n",lSolution.violation);



    printf("Read Solution: %i\n", read_solution);
    printf("InitialNumContacts: %i\nFinalNumContatcs: %i\n",initialNumContacts,contact_lookup_total(lForest));
    printf("lDistance: %.2f\n",lDistance);
    printf("Final Solution: Solution %i (V: %e - C: %e)\n", idxBest, lPopulation->solutions[idxBest].violation, lPopulation->solutions[idxBest].cost);
	fprintf(file, "Tempo final de execucao: %f\n",elapsed);
	fprintf(file,"Numero Final de contatos: %i\n",contact_lookup_total(lForest));
    fprintf(file,"Solution Tempo Final: %i (V: %e - C: %e)\n",idxBest,lPopulation->solutions[idxBest].violation,lPopulation->solutions[idxBest].cost);

	fclose(file);


    /// LILI
    char remaining[200];
    sprintf(remaining,"forests/solution/forest_remaining_%i_de_%.1f_30_%i_10.txt",seed,lDistance,density);
    strcpy(aux, directory);
    strcat(aux, remaining);
    strcpy(remaining, aux);
    printf("remaining:\t%s\n", remaining);
    FILE* arq = fopen(remaining, "w");
    fprintf(arq, "Read Solution\t%i\n", read_solution);
    fprintf(arq, "InitialNumContacts\t%i\nFinalNumContacts\t%i\n",initialNumContacts,contact_lookup_total(lForest));
    fprintf(arq, "lDistance\t%.2f\n",lDistance);
    fprintf(arq, "Final Solution: Solution\t%i\t%e\t%e\n", idxBest, lPopulation->solutions[idxBest].violation, lPopulation->solutions[idxBest].cost);
    fclose(arq);
    contact_write_remaining(lContacts, remaining, lForest);
    /// LILI end

    /// Just for tests
    /*
    FILE* arq = fopen(remaining, "a");
    if (arq == NULL){
        printf("Nao foi possivel encontrar o arquivo\n");
        abort();
    }
    else{
        fprintf(arq,"Solution Tempo Final: %i (V: %e - C: %e)\n",idxBest,lPopulation->solutions[idxBest].violation,lPopulation->solutions[idxBest].cost);
    }
    */
    fclose(arq);
    /// End just for tests


	free(lSolution.points);

    //population_update_forest(lPopulation,lForest);

    char name1[300];
    char name2[300];
    /*sprintf(name1,"/home/pedrohen/Documentos/Nanotubos/projetoCNT/Resultados/forest_attributes_%i_%i_fullt_%.1f_%i_10.txt",read_solution,seed,lDistance,density);
    sprintf(name2,"/home/pedrohen/Documentos/Nanotubos/projetoCNT/Resultados/forest_solution_%i_%i_fullt_%.1f_30_%i_10.txt",read_solution,seed,lDistance,density);
    */

    //sprintf(nameSim,"/home/pedrohen/Documentos/Nanotubos/gcgtube/forests/simulation/forest_simulation_%i_30_%i_10.txt",seed,density);
    sprintf(name2,"forests/solution/forest_solution_%i_de_%.1f_30_%i_10.txt",seed,lDistance,density);

    strcpy(aux, directory);
    strcat(aux, name2);
    strcpy(name2, aux);
    printf("name2:\t%s\n", name2);
    //forest_write_attributes(lForest,name1);
    forest_write_simulation(lForest,name2);

    population_destroy(lPopulation);
    free(lPopulation);

    contact_list_destroy(lContacts);
    free(lContacts);

    forest_destroy(lForest);
    free(lForest);

    return EXIT_SUCCESS;
}
