#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
            //int vContact = 0;
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
							double initialDistance = lDistance;

							lDistance -= (pForest->nanotubes[i].radiusOut + pForest->nanotubes[x].radiusOut);
                            //printf("lDistance: %lf\n",lDistance);
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
                                //printf("%d\t%d\n",lContacts->list[lContacts->length].cnt1,lContacts->list[lContacts->length].cnt2);
								//printf("%f\t%f\t%f\n",pForest->nanotubes[i].points[j].x,pForest->nanotubes[i].points[j].y,pForest->nanotubes[i].points[j].z);
								printf("Contato numero %i: %i.%i-%i.%i -> %f (%f) \n",lContacts->length,i,j+1,x,y+1, initialDistance, lDistance);
								printf("seg1\t%f\t%f\t%f\n",pForest->nanotubes[i].points[j].x,pForest->nanotubes[i].points[j].y,pForest->nanotubes[i].points[j].z);
								printf("seg2\t%f\t%f\t%f\n",pForest->nanotubes[x].points[y].x,pForest->nanotubes[x].points[y].y,pForest->nanotubes[x].points[y].z);
								printf("CNT %d of radius %f, CNT %d of radius %f, radii sum %f\n\n", i, pForest->nanotubes[i].radiusOut, x, pForest->nanotubes[x].radiusOut, pForest->nanotubes[i].radiusOut+pForest->nanotubes[x].radiusOut);

								++lContacts->length;
								//printf("Contatos: %i\n",lContacts->length);

							}
							/*if(lDistance <= pForest->distance + 0.000005){
                                vContact++;
							}*/
						}
					}
				}
			}
         //printf("Contatos Visualizador: %i\n",vContact);
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
                    //printf("lDistance: %lf\n",lDistance);
                    if(lDistance <= pForest->distance) {
                        numContacts++;
                        //printf("Contatos: %i\n",numContacts);
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

/// LILI
void contact_write_remaining(contact_list_t *pContactList, char pContactFile[], forest_t *pForest)
{
    FILE* lFile = fopen(pContactFile, "a");
	if (lFile != NULL)
	{
		fprintf(lFile,"# cnt1.ind1 cnt2.ind2 radius1 radius2 distance (distance-radius1-radius2)\n");
		fprintf(lFile,"Number of Contacts: %d\n", pContactList->length);
		for (int i = 0; i < pContactList->length; ++i)
		{
            int cnt1 = pContactList->list[i].cnt1 / pForest->growthSteps;
            int ind1 = pContactList->list[i].cnt1  % pForest->growthSteps;
            int cnt2 = pContactList->list[i].cnt2 / pForest->growthSteps;
            int ind2 = pContactList->list[i].cnt2  % pForest->growthSteps;
            double lDistance = point_compute_distance(
								pForest->nanotubes[cnt1].points[ind1],
								pForest->nanotubes[cnt2].points[ind2],
								pForest->nanotubes[cnt1].points[ind1 - 1],
								pForest->nanotubes[cnt2].points[ind2 - 1]
							);
            double initialDistance = lDistance;

            lDistance -= (pForest->nanotubes[cnt1].radiusOut + pForest->nanotubes[cnt2].radiusOut);

            fprintf(lFile, "%d %d %d %d %.8f %.8f %.8f %.8f\n", cnt1, ind1, cnt2, ind2,
                    pForest->nanotubes[cnt1].radiusOut, pForest->nanotubes[cnt2].radiusOut,
                    initialDistance, lDistance);
		}
		fclose(lFile);
    }
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
