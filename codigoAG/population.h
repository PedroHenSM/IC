#ifndef __POPULATION_H__
    #define __POPULATION_H__

    #include "contact.h"
    #include "forest.h"

    typedef struct solution_s {
        int size;
        int length;
        double violation;
        double cost;
        point_t* points;
    } solution_t;

    typedef struct population_s {
    	int size;
        contact_list_t* contacts;
        solution_t* solutions;
        int* map;
        point_t* buffer;
    } population_t;

    population_t* population_build(int, contact_list_t*, forest_t*);
    void population_init(population_t*, forest_t*);
    double population_calc_cost(solution_t*);
    double population_calc_violation(population_t*, solution_t*, forest_t*);
    int population_pick(population_t*, int, int*);
    void population_update_forest(population_t*, forest_t*);
    void population_print(population_t*);
    void population_print_best(population_t*);
    void population_destroy(population_t*);
    int population_best_index(population_t* pPopulation);
    void solution_update_forest(solution_t pSolution, forest_t* pForest);
#endif
