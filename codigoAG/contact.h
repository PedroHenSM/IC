#ifndef __CONTACT_H__
    #define __CONTACT_H__

    #include "forest.h"

    #define CONTACT_LIST_BUFFER_SIZE 1000

    typedef struct contact_s {
        int cnt1;
        int cnt2;
    } contact_t;

    typedef struct contact_list_s {
        int size;
        int length;
        contact_t* list;
    } contact_list_t;

    contact_list_t* contact_lookup(forest_t*);
    int contact_lookup_total(forest_t*);
    void contact_list_destroy(contact_list_t*);
    double contact_lookup_violation(forest_t*);
    double contact_lookup_cost(forest_t*);
    void contact_write_remaining(contact_list_t *c_list, char pContactFile[], forest_t *pForest);
#endif
