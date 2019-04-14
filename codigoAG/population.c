#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "forest.h"
#include "point.h"
#include "population.h"

int population_contains_in_solution(solution_t* pSolution, int pCntId) {
    for (int i = 0; i < pSolution->length; ++i) {
        if (pSolution->points[i].id == pCntId) {
            return i;
        }
    }

    return -1;
}

int population_add_to_solution(solution_t* pSolution, int pCntId, forest_t* pForest) {
   if (pSolution->length >= pSolution->size) {
        point_t* lNewBuffer = (point_t*) realloc(pSolution->points, pSolution->size << 1);

        if (lNewBuffer != NULL) {
            pSolution->points = lNewBuffer;
            pSolution->size <<= 1;
        } else {
            printf("Not enought memory for: population_add_to_solution.\n"); exit(1);
        }
    }

    int lCntIdx = pCntId / pForest->growthSteps;
    int lPointIdx = pCntId % pForest->growthSteps;

    pSolution->points[pSolution->length] = pForest->nanotubes[lCntIdx].points[lPointIdx];

    return pSolution->length++;
}

void population_add_random(population_t* pPopulation, forest_t* pForest, double pMax) {
    double randDiv = (RAND_MAX / pMax);
    double half = pMax / 2;

    for (int i = 1; i < pPopulation->size; ++i) {
    	for (int j = 0; j < pPopulation->solutions[i].length; ++j) {
    		pPopulation->solutions[i].points[j].z += (rand() / randDiv) - half;
    	}
    }
}

void population_set_trivial(population_t* pPopulation, forest_t* pForest) {
	double lPlan[pForest->totalCNTs];
	int half = pForest->totalCNTs >> 1;
	lPlan[half] = 0.0;

	for (int i = half - 1; i >= 0; --i) {
		lPlan[i] = lPlan[i + 1] - (pForest->nanotubes[i].diamOut / 2.0) - (pForest->nanotubes[i + 1].diamOut / 2.0) - (pForest->distance * 2);
	}

	for (int i = half + 1; i < pForest->totalCNTs; ++i) {
		lPlan[i] = lPlan[i - 1] + (pForest->nanotubes[i].diamOut / 2.0) + (pForest->nanotubes[i - 1].diamOut / 2.0) + (pForest->distance * 2);
	}

    for (int i = 1; i < pPopulation->size; ++i) {
    	for (int j = 0; j < pPopulation->solutions[i].length; ++j) {
    		pPopulation->solutions[i].points[j].z = lPlan[pPopulation->solutions[i].points[j].id / pForest->growthSteps];
    	}
    }
}

population_t* population_build(int pSize, contact_list_t* pContacts, forest_t* pForest) {
    population_t* lPopulation = (population_t*) malloc(sizeof(population_t));

    lPopulation->contacts = pContacts;
    lPopulation->map = (int*) malloc(sizeof(int) * (pContacts->length << 2));

    solution_t lSolution;
    lSolution.size = pContacts->length << 2;
    lSolution.length = 0;
    lSolution.points = (point_t*) malloc(sizeof(point_t) * (pContacts->length << 2));

    int lIdx = 0;
    for (int c = 0; c < pContacts->length; ++c) {
        int idx = population_contains_in_solution(&lSolution, pContacts->list[c].cnt1 - 1);
        if (idx == -1) idx = population_add_to_solution(&lSolution, pContacts->list[c].cnt1 - 1, pForest);
        lPopulation->map[lIdx++] = idx;

        idx = population_contains_in_solution(&lSolution, pContacts->list[c].cnt1);
        if (idx == -1) idx = population_add_to_solution(&lSolution, pContacts->list[c].cnt1, pForest);
        lPopulation->map[lIdx++] = idx;

        idx = population_contains_in_solution(&lSolution, pContacts->list[c].cnt2 - 1);
        if (idx == -1) idx = population_add_to_solution(&lSolution, pContacts->list[c].cnt2 - 1, pForest);
        lPopulation->map[lIdx++] = idx;

        idx = population_contains_in_solution(&lSolution, pContacts->list[c].cnt2);
        if (idx == -1) idx = population_add_to_solution(&lSolution, pContacts->list[c].cnt2, pForest);
        lPopulation->map[lIdx++] = idx;
    }

    lIdx = 0;
    lPopulation->buffer = (point_t*) malloc(sizeof(point_t) * lSolution.length * pSize);
    lPopulation->solutions = (solution_t*) malloc(sizeof(solution_t) * pSize);
    lPopulation->size = pSize;

    for (int i = 0; i < lPopulation->size; ++i) {
        lPopulation->solutions[i].size = lSolution.length;
        lPopulation->solutions[i].length = lSolution.length;
        lPopulation->solutions[i].points = &lPopulation->buffer[lIdx];
        memcpy(lPopulation->solutions[i].points, lSolution.points, sizeof(point_t) * lSolution.length);
        lIdx += lSolution.length;
    }

    population_add_random(lPopulation, pForest, pForest->distance);

    //population_set_trivial(lPopulation, pForest);
    //population_add_random(lPopulation, pForest, pForest->distance * 10);

    free(lSolution.points);

    return lPopulation;
}

void population_init(population_t* pPopulation, forest_t* pForest) {
    for (int i = 0; i < pPopulation->size; ++i) {
    	//pPopulation->solutions[i].violation = population_calc_violation(pPopulation, &pPopulation->solutions[i], pForest);
    	solution_update_forest((pPopulation->solutions[i]),pForest);
    	pPopulation->solutions[i].violation = contact_lookup_violation(pForest);
    	pPopulation->solutions[i].cost = population_calc_cost(&pPopulation->solutions[i]);
    }
}

double population_calc_cost(solution_t* pSolution) {
	double cost = 0.0;

	for (int p = 0; p < pSolution->length; ++p) {
		if (pSolution->points[p].z < 0) {
			cost += -pSolution->points[p].z;
		} else {
			cost += pSolution->points[p].z;
		}
	}

	return cost;
}

double population_calc_violation(population_t* pPopulation, solution_t* pSolution, forest_t* pForest) {
	double fit = 0.0;

	int lIdx = 0;
	for (int c = 0; c < pPopulation->contacts->length; ++c) {
		point_t lPoint1 = pSolution->points[pPopulation->map[lIdx+1]];
		point_t lPoint3 = pSolution->points[pPopulation->map[lIdx+3]];

		double lDist = point_compute_distance(
			lPoint1,
			lPoint3,
			pSolution->points[pPopulation->map[lIdx]],
			pSolution->points[pPopulation->map[lIdx+2]]
		);

		lIdx += 4;

		lDist -= (pForest->nanotubes[lPoint1.id / pForest->growthSteps].radiusOut + pForest->nanotubes[lPoint3.id / pForest->growthSteps].radiusOut);

		if (lDist <= pForest->distance) {
			if (lDist < 0) {
				fit += -lDist;
			} else {
				fit += lDist;
			}
		}
	}

	return fit;
}

int population_pick(population_t* pPopulation, int solution, int* ch) {
	int lReturn;
	int found = 1;

	while (1) {
		lReturn = rand() % pPopulation->size;

		if (lReturn != solution) {
			int a = 0;

			while (ch[a] != -1) {
				if (lReturn == ch[a]) {
					found = 0;
					break;
				}

				++a;
			}

			if (found == 1) {
				break;
			} else {
				found = 1;
			}
		}
	}

	return lReturn;
}

void population_update_forest(population_t* pPopulation, forest_t* pForest) {
    //for (int i = 0; i < pPopulation->size; ++i) {
    int i = population_best_index(pPopulation);
    	for (int j = 0; j < pPopulation->solutions[i].length; ++j) {
    		int lCntId = pPopulation->solutions[i].points[j].id;
    	    int lCntIdx = lCntId / pForest->growthSteps;
    	    int lPointIdx = lCntId % pForest->growthSteps;

    	    pForest->nanotubes[lCntIdx].points[lPointIdx] = pPopulation->solutions[i].points[j];
    	}
	//}
}

void solution_update_forest(solution_t pSolution, forest_t* pForest) {
    	for (int j = 0; j < pSolution.length; ++j) {
    		int lCntId = pSolution.points[j].id;
    	    int lCntIdx = lCntId / pForest->growthSteps;
    	    int lPointIdx = lCntId % pForest->growthSteps;

    	    pForest->nanotubes[lCntIdx].points[lPointIdx] = pSolution.points[j];
    	}
	//}
}

void population_print(population_t* pPopulation) {
	for (int i = 0; i < pPopulation->size; ++i) {
		printf("Solution %d (%lf):\n", i, pPopulation->solutions[i].violation);
		for (int j = 0; j < pPopulation->solutions[i].length; ++j) {
			printf("\t%d: %f %f %f\n", j, pPopulation->solutions[i].points[j].x, pPopulation->solutions[i].points[j].y, pPopulation->solutions[i].points[j].z);
		}
		printf("\n\n");
	}
}

void population_print_best(population_t* pPopulation) {
	int idxBest = 0;

	for (int i = 1; i < pPopulation->size; ++i) {
		if (pPopulation->solutions[i].violation < pPopulation->solutions[idxBest].violation) {
			idxBest = i;
		} else if (pPopulation->solutions[i].violation == pPopulation->solutions[idxBest].violation && pPopulation->solutions[i].cost < pPopulation->solutions[idxBest].cost) {
			idxBest = i;
		}
	}
    //pPopulation->solutions[i].violation == pPopulation->solutions[idxBest].violation &&
	printf("Solution %d (V: %e - C: %e)\n", idxBest, pPopulation->solutions[idxBest].violation, pPopulation->solutions[idxBest].cost);
}

int population_best_index(population_t* pPopulation) {
	int idxBest = 0;

	for (int i = 1; i < pPopulation->size; ++i) {
		if (pPopulation->solutions[i].violation < pPopulation->solutions[idxBest].violation) {
			idxBest = i;
		} else if (pPopulation->solutions[i].violation == pPopulation->solutions[idxBest].violation && pPopulation->solutions[i].cost < pPopulation->solutions[idxBest].cost) {
			idxBest = i;
		}
	}
	return idxBest;
}

void retorno_teste_populacao(double v){
    //double
    v=15;
    printf("O VALOR DE V: %e\n",v);
    return v;
}


void population_destroy(population_t* pPopulation) {
    if (pPopulation->map != NULL) free(pPopulation->map);
    if (pPopulation->buffer != NULL) free(pPopulation->buffer);
    if (pPopulation->solutions != NULL) free(pPopulation->solutions);
}
