#include <stdio.h>
#include <stdlib.h>

#include "contact.h"
#include "forest.h"
#include "point.h"

contact_list_t* contact_lookup(forest_t* pForest) {
    contact_list_t* lContacts = (contact_list_t*) malloc(sizeof(contact_list_t));
    int i,j,x,y;
    if (lContacts != NULL) {
    	lContacts->list = (contact_t*) malloc(sizeof(contact_t) * CONTACT_LIST_BUFFER_SIZE);

    	if (lContacts->list != NULL) {
			lContacts->size = CONTACT_LIST_BUFFER_SIZE;
			lContacts->length = 0;

			for (i = 0; i < pForest->totalCNTs; ++i) {
				for (j = 1; j < pForest->nanotubes[i].size; ++j) {
					for (x = i + 1; x < pForest->totalCNTs; ++x) {
						for (y = 1; y < pForest->nanotubes[x].size; ++y) {
							double lDistance = point_compute_distance(
								pForest->nanotubes[i].points[j],
								pForest->nanotubes[x].points[y],
								pForest->nanotubes[i].points[j - 1],
								pForest->nanotubes[x].points[y - 1]
							);

							lDistance -= (pForest->nanotubes[i].radiusOut + pForest->nanotubes[x].radiusOut);
                            //printf("Testando distancias\n");
							if(lDistance <= pForest->distance) {
								if (lContacts->length >= lContacts->size) {
									contact_t* lNewBuffer = (contact_t*) realloc(lContacts->list, sizeof(contact_t) * (lContacts->size << 1));

									if (lNewBuffer != NULL) {
										lContacts->list = lNewBuffer;
										lContacts->size <<= 1;
									} else {
										printf("Not enough memory for: contact_lookup::realloc.\n"); exit(1);
									}
								}

								lContacts->list[lContacts->length].cnt1 = pForest->nanotubes[i].points[j].id;
								lContacts->list[lContacts->length].cnt2 = pForest->nanotubes[x].points[y].id;

								++lContacts->length;
							}
						}
					}
				}
			}
        } else {
        	printf("Not enough memory for: contact_lookup::list.\n"); exit(1);
        }
    } else {
    	printf("Not enough memory for: contact_lookup.\n"); exit(1);
    }
    return lContacts;
}

double contact_lookup_violation(forest_t* pForest) {
    double violation=0;
    for (int i = 0; i < pForest->totalCNTs-1; ++i) {
        for (int j = 1; j < pForest->nanotubes[i].size; ++j) {
            for (int x = i + 1; x < pForest->totalCNTs; ++x) {
                for (int y = 1; y < pForest->nanotubes[x].size; ++y) {
                    double lDistance = point_compute_distance(
                        pForest->nanotubes[i].points[j],
                        pForest->nanotubes[x].points[y],
                        pForest->nanotubes[i].points[j - 1],
                        pForest->nanotubes[x].points[y - 1]
                    );

                    lDistance -= (pForest->nanotubes[i].radiusOut + pForest->nanotubes[x].radiusOut);
                    if(lDistance <= pForest->distance) {
                        violation += fabs(lDistance);
                    }
                }
            }
        }
    }
    return violation;
}

int contact_lookup_total(forest_t *pForest){
    int numContacts = 0;
    for (int i = 0; i < pForest->totalCNTs-1; ++i) {
        for (int j = 1; j < pForest->nanotubes[i].size; ++j) {
            for (int x = i + 1; x < pForest->totalCNTs; ++x) {
                for (int y = 1; y < pForest->nanotubes[x].size; ++y) {
                    double lDistance = point_compute_distance(
                        pForest->nanotubes[i].points[j],
                        pForest->nanotubes[x].points[y],
                        pForest->nanotubes[i].points[j - 1],
                        pForest->nanotubes[x].points[y - 1]
                    );

                    lDistance -= (pForest->nanotubes[i].radiusOut + pForest->nanotubes[x].radiusOut);
                    if(lDistance <= pForest->distance) {
                        numContacts++;
                    }
                }
            }
        }
    }
    return numContacts;
}

void contact_list_destroy(contact_list_t* pContactList) {
    // Free all memory used by the contacts.
    if (pContactList->list != NULL) free(pContactList->list);
}


/*double contact_lookup_violation(forest_t* pForest) {
    double violation=0;
    for (int i = 0; i < pForest->totalCNTs; ++i) {
        for (int j = 1; j < pForest->nanotubes[i].size; ++j) {
            for (int x = i + 1; x < pForest->totalCNTs; ++x) {
                for (int y = 1; y < pForest->nanotubes[x].size; ++y) {
                    double lDistance = point_compute_distance(
                        pForest->nanotubes[i].points[j],
                        pForest->nanotubes[x].points[y],
                        pForest->nanotubes[i].points[j - 1],
                        pForest->nanotubes[x].points[y - 1]
                    );

                    lDistance -= (pForest->nanotubes[i].radiusOut + pForest->nanotubes[x].radiusOut);
                    if(lDistance <= pForest->distance) {
                        //printf("lDistance: %e\n",fabs(lDistance));
                        violation += fabs(lDistance);
                    }
                }
            }
        }
    }
    printf("ViolationFuncao: %e\n",violation);
    return violation;
}*/
