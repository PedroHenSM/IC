#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
//#include <string.h>

#include "contact.h"
#include "forest.h"
#include "population.h"

int main(int argc, char* argv[]) {
	char* lSolutionFile = NULL;
	char* lAttributeFile = NULL;
	char* lSimulationFile = NULL;
	double lDistance = 0.3;
	int lPopulationSize = 50;
	int read_solution = 0;
	// CR ∈ [ 0 , 1 ] is called the crossover probability.
	double CR = 0.8;
	// Let F ∈[0, 2] be called the differential weight.
	double F = 0.7;
    double maxSec = 30;
    double bound[2]={-50,50};
	int lMaxRun = 50000;
	int density = 5; // teste com 15 | 10 |10
    int seed  = 1; // teste com 1 | 1480577315 | 1
	int c;
    /*
        while ((c = getopt(argc, argv, "l:s:a:d:p:c:f:r:")) != -1) {
    	switch (c) {
			case 'l': lSolutionFile = optarg; break;
    		case 's': lSimulationFile = optarg; break;
    		case 'a': lAttributeFile = optarg; break;
    		case 'd': lDistance = atof(optarg); break;
    		case 'p': lPopulationSize = atoi(optarg); break;
    		case 'c': CR = atof(optarg); break;
    		case 'f': F = atof(optarg); break;
    		case 'r': lMaxRun = atoi(optarg); break;
			default: abort();
    	}
    }
    */
    while ((c = getopt(argc, argv, "d:s:c:r:")) != -1) {
        //printf("Entrou leitura de parametro\n");
    	switch (c) {
			case 'd': density = atoi(optarg); break;
    		case 's': seed = atoi(optarg); break;
    		case 'c': lDistance = atof(optarg); break;
    		case 'r': read_solution = atoi(optarg); break;
    		//case 'p': lPopulationSize = atoi(optarg); break;
    		//case 'c': CR = atof(optarg); break;
    		//case 'f': F = atof(optarg); break;
    		//case 'r': lMaxRun = atoi(optarg); break;
			default: abort();
    	}
    }
    char nameAtr[300],nameSim[300],nameSol[300];
    sprintf(nameAtr,"/home/pedro/Documentos/GIT/projetoCNT/data/attributes/forest_attributes_%i_%i_10.txt",seed,density);
    sprintf(nameSim,"/home/pedro/Documentos/GIT/projetoCNT/data/simulation/forest_simulation_%i_30_%i_10.txt",seed,density);
    sprintf(nameSol,"/home/pedro/Documentos/GIT/projetoCNT/data/solution/forest_solution_%i_hyp_%.1f_30_%i_10.txt",seed,lDistance,density);
    //sprintf(nameSol,"/home/pedro/Área de Trabalho/Diversos/CNT/contactscnt/Floresta25/solution/forest_solution_%i_hyp_%.1f_30_%i_10.txt",seed,lDistance,density);
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
    int numContatosInicial = contact_lookup_total(lForest);
    printf("NumContatosInicial: %i\n",numContatosInicial);
    population_t* lPopulation = population_build(lPopulationSize, lContacts, lForest);
    population_init(lPopulation, lForest); // Inicializa violacao e custo da populacao
    printf("lPopulationSize: %i\n",lPopulation->size);
	solution_t lSolution;
	lSolution.size = lPopulation->solutions[0].size;
	printf("lSolutionSize: %i\n",lSolution.size);
	lSolution.length = lPopulation->solutions[0].length;
	printf("lSolutionLength: %i\n",lSolution.length);
	lSolution.points = malloc(sizeof(point_t) * lPopulation->solutions[0].length);


	int imprimiu =0;
	//int imprimiu1=0; // Imprimir informacoes tempo original
	int idxBest = 0;
    time_t start,end;
    double elapsed; // seconds
    int terminate =1;
    char endereco[300];
    sprintf(endereco,"/home/pedro/Documentos/GIT/projetoCNT/Tempos/forest_%i_%i_%.1f_%i.txt",read_solution,seed,lDistance,density);
    FILE* file = fopen(endereco,"w");
    fprintf(file,"Num Inicial Contatos: %i\n",numContatosInicial);
    int lRun=0;
    while (++lRun <= lMaxRun) {
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
                char name4[300];
                sprintf(name4,"/home/pedro/Documentos/GIT/projetoCNT/Resultados/forest_solution_%i_%i_fullt_%.1f_30_%i_10.txt",read_solution,seed,lDistance,density);
                forest_write_simulation(lForest,name4);
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
			//lSolution.violation = population_calc_violation(lPopulation, &lSolution, lForest);
            double a=population_calc_violation(lPopulation,&lSolution,lForest);
            /*
            solution_update_forest(lSolution, lForest);
            double b = contact_lookup_violation(lForest);
            if(fabs(a-b) >= 1e-6){
                printf("deu ruim\n");
            }
            lSolution.violation = contact_lookup_violation(lForest);
            printf("lSolutionViolation : %e\n",lSolution.violation);
            */
            lSolution.violation = a;
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

	population_update_forest(lPopulation, lForest);
    population_print_best(lPopulation);


    /*contact_list_destroy(lContacts);
    free(lContacts);

    lContacts = contact_lookup(lForest);*/
	idxBest = population_best_index(lPopulation);
    //lSolution.violation = population_calc_violation(lPopulation, &lSolution, lForest);
    //printf("lSolution.violation: %lf\n",lSolution.violation);




    printf("NumContatosInicial: %i\nNumContatosFinal: %i\n",numContatosInicial,contact_lookup_total(lForest));
	fprintf(file, "Tempo final de execucao: %f\n",elapsed);
	fprintf(file,"Numero Final de contatos: %i\n",contact_lookup_total(lForest));
    fprintf(file,"Solution Tempo Final: %i (V: %e - C: %e)\n",idxBest,lPopulation->solutions[idxBest].violation,lPopulation->solutions[idxBest].cost);

	fclose(file);

	free(lSolution.points);

    //population_update_forest(lPopulation,lForest);

    char name1[300];
    char name2[300];
    sprintf(name1,"/home/pedro/Documentos/GIT/projetoCNT/Resultados/forest_attributes_%i_%i_fullt_%.1f_%i_10.txt",read_solution,seed,lDistance,density);
    sprintf(name2,"/home/pedro/Documentos/GIT/projetoCNT/Resultados/forest_solution_%i_%i_fullt_%.1f_30_%i_10.txt",read_solution,seed,lDistance,density);
    forest_write_attributes(lForest,name1);
    forest_write_simulation(lForest,name2);


    population_destroy(lPopulation);
    free(lPopulation);

    contact_list_destroy(lContacts);
    free(lContacts);

    forest_destroy(lForest);
    free(lForest);

    return EXIT_SUCCESS;
}
