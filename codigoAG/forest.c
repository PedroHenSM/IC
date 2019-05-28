#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "forest.h"

forest_t* forest_create(double pDistance) {
    // Allocate memory for the forest.
    forest_t* lNewForest = (forest_t*) malloc(sizeof(forest_t));

    // Set a default value for everything inside the forest.
    lNewForest->seed = 0;
    lNewForest->totalCNTs = 0;
    lNewForest->spacing = 0.0;
    lNewForest->growthSteps = 0;
    lNewForest->minX = 0.0;
    lNewForest->maxX = 0.0;
    lNewForest->sigma = 0.0;
    lNewForest->density = 0;
    lNewForest->diamInn = 0;
    lNewForest->diamOut = 0;
    lNewForest->growthRate = 0;
    lNewForest->growthAngle = 0;
    lNewForest->captureDist = 0;
    lNewForest->vdWStiffness = 0.0;

    // Make sure the pointer is safe to use.
    lNewForest->nanotubes = NULL;
    lNewForest->buffer = NULL;

    lNewForest->distance = pDistance;

    // Return the newly usable forest.
    return lNewForest;
}

void forest_print(forest_t* pForest) {
    printf("#seed: %d\n", pForest->seed);
    printf("#totalCNTs: %d\n", pForest->totalCNTs);
    printf("#spacing: %lf\n", pForest->spacing);
    printf("#growthSteps: %d\n", pForest->growthSteps);
    printf("#minX: %lf\n", pForest->minX);
    printf("#maxX: %lf\n", pForest->maxX);
    printf("#sigma: %lf\n", pForest->sigma);
    printf("#density: %d\n", pForest->density);
    printf("#diamInn: %d\n", pForest->diamInn);
    printf("#diamOut: %d\n", pForest->diamOut);
    printf("#growthRate: %d\n", pForest->growthRate);
    printf("#growthAngle: %d\n", pForest->growthAngle);
    printf("#captureDist: %d\n", pForest->captureDist);
    printf("#vdWStiffness: %f\n", pForest->vdWStiffness);
    printf("\n");

    for (int i = 0; i < pForest->totalCNTs; ++i) {
        printf("#cnt: %i\n", i);
        printf("#diamInn: %f\n", pForest->nanotubes[i].diamInn);
        printf("#diamOut: %f\n", pForest->nanotubes[i].diamOut);
        printf("#growthRate: %f\n", pForest->nanotubes[i].growthRate);
        printf("#growthAngle: %f\n", pForest->nanotubes[i].growthAngle);
        printf("#secondInertia: %f\n", pForest->nanotubes[i].secondInertia);
        printf("#sectionArea: %f\n", pForest->nanotubes[i].sectionArea);
        printf("#dof: %d\n", pForest->nanotubes[i].dof);
        printf("#maxSegm: %d\n", pForest->nanotubes[i].maxSegm);
        printf("#segLength: %f\n", pForest->nanotubes[i].segLength);
        printf("#points:\n");

        for (int lCurrentPoint = 0; lCurrentPoint < pForest->nanotubes[i].size; ++lCurrentPoint) {
            printf("\t%i: %f %f %f\n", lCurrentPoint,
                pForest->nanotubes[i].points[lCurrentPoint].x,
                pForest->nanotubes[i].points[lCurrentPoint].y,
                pForest->nanotubes[i].points[lCurrentPoint].z
            );
        }

        printf("\n");
    }
}

void forest_read_attributes(forest_t* pForest, char pAttributesFile[]) {
    // Try to open the file as read only.
    FILE* lFile = fopen(pAttributesFile, "r");

    // Check if we were able to open the file.
    if (lFile != NULL) {
        // Temporary pointer to store data.
        char lReadBuffer[FOREST_READ_BUFFER_SIZE];
        char* lRead;

        // Read forest data.
        lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
        if (lRead != NULL) pForest->seed = atoi(lReadBuffer);
        lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
        if (lRead != NULL) pForest->totalCNTs = atoi(lReadBuffer);
        lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
        if (lRead != NULL) pForest->spacing = atof(lReadBuffer);
        lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
        if (lRead != NULL) pForest->growthSteps = atoi(lReadBuffer);
        lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
        if (lRead != NULL) pForest->minX = atof(lReadBuffer);
        lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
        if (lRead != NULL) pForest->maxX = atof(lReadBuffer);
        lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
        if (lRead != NULL) pForest->sigma = atof(lReadBuffer);
        lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
        if (lRead != NULL) pForest->density = atoi(lReadBuffer);
        lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
        if (lRead != NULL) pForest->diamInn = atoi(lReadBuffer);
        lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
        if (lRead != NULL) pForest->diamOut = atoi(lReadBuffer);
        lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
        if (lRead != NULL) pForest->growthRate = atoi(lReadBuffer);
        lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
        if (lRead != NULL) pForest->growthAngle = atoi(lReadBuffer);
        lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
        if (lRead != NULL) pForest->captureDist = atoi(lReadBuffer);
        lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
        if (lRead != NULL) pForest->vdWStiffness = atof(lReadBuffer);

        // Ignore an empty line.
        fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);

        /**
         * Allocate a contiguous memory block, so all nanotube data is
         * sequentially stored in memory.
         */
        pForest->buffer = (point_t*) malloc(
            // Total amount of nanotubes multiplied by the amount of points.
            sizeof(point_t) * pForest->totalCNTs * pForest->growthSteps
        );

        /**
         * Now we allocate memory to all nanotube structures. As the point field
         * is a pointer, we set it using our contiguous block, so we don't
         * spend a lot of time allocating and moving memory around.
         */
        pForest->nanotubes = (nanotube_t*) malloc(sizeof(nanotube_t) * pForest->totalCNTs);

        // This is the memory index, so we don't use invalid memory.
        int lIndex = 0;
        // Just a counter to store current nanotube index.
        int i = 0;

        // Now, lets loop through the file until we reach the end.
        while (i < pForest->totalCNTs) {
            // If the file is corrupt, the end could be reached before the counter.
            if (feof(lFile)) break;

            // Ignore the nanotube index from file.
            fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);

            // Read current nanotube information.
            lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
            if (lRead != NULL) pForest->nanotubes[i].diamInn = atof(lReadBuffer);
            lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
            if (lRead != NULL) pForest->nanotubes[i].diamOut = atof(lReadBuffer);
            lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
            if (lRead != NULL) pForest->nanotubes[i].growthRate = atof(lReadBuffer);
            lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
            if (lRead != NULL) pForest->nanotubes[i].growthAngle = atof(lReadBuffer);
            lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
            if (lRead != NULL) pForest->nanotubes[i].secondInertia = atof(lReadBuffer);
            lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
            if (lRead != NULL) pForest->nanotubes[i].sectionArea = atof(lReadBuffer);
            lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
            if (lRead != NULL) pForest->nanotubes[i].dof = atoi(lReadBuffer);
            lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
            if (lRead != NULL) pForest->nanotubes[i].maxSegm = atoi(lReadBuffer);
            lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
            if (lRead != NULL) pForest->nanotubes[i].segLength = atof(lReadBuffer);

            // Compute some utility values.
            if (pForest->diamOut != 0) pForest->nanotubes[i].radiusOut = pForest->nanotubes[i].diamOut / 2.0;

            /**
             * This is the most crucial part to understand how the memory is allocated.
             */
            pForest->nanotubes[i].points = &pForest->buffer[lIndex];
            // Shift the index, so we have an empty memory block to use.
            lIndex += pForest->growthSteps;

            // Next one, please.
            ++i;
        }

        // We don't need the attribute file anymore.
        fclose(lFile);
    }
}

void forest_read_simulation(forest_t* pForest, char pSimulationFile[]) {
    // Try to open the file as read only.
    FILE* lFile = fopen(pSimulationFile, "r");

    // Check if we were able to open the file.
    if (lFile != NULL) {
        // Temporary pointer to store data.
        char lReadBuffer[FOREST_READ_BUFFER_SIZE];
        char* lRead;
        lRead = fgets(lReadBuffer,FOREST_READ_BUFFER_SIZE,lFile);
        // Ignore info before reach the p
        while(lRead[0] != '\n'){
            lRead = fgets(lReadBuffer,FOREST_READ_BUFFER_SIZE,lFile);
        }
        // Just a counter to store current nanotube index.
        int i = 0;

        // Now, lets loop through the file until we reach the end.
        while (i < pForest->totalCNTs) {
            // If the file is corrupt, the end could be reached before the counter.
            if (feof(lFile)) break;

            // Ignore the nanotube index from file.
            fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
            // Ignore the next line, because I don't know what it is.
            fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile); /**Nao eh necessario, caso o while acima seja utilizado**/
            // Now, read the amount of points this nanotube has.
            lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
            if (lRead != NULL) pForest->nanotubes[i].size = atoi(lReadBuffer) + 1;

            // Loop and read all data points.
            for (int j = 0; j < pForest->nanotubes[i].size; ++j) {
                // Read point coordinates.
                lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);

                // Did we read anything?
                if (lRead != NULL) {
                    pForest->nanotubes[i].points[j].id = (i * pForest->growthSteps) + j;
                    // Ok, tokenize the string and store the coordinate.
                    char* lToken = strtok(lRead, " ");
                    pForest->nanotubes[i].points[j].x = atof(lToken);
                    lToken = strtok(NULL, " ");
                    pForest->nanotubes[i].points[j].y = atof(lToken);
                    pForest->nanotubes[i].points[j].z = 0;
                    //printf("nanotubes[i].points[j].z = %f\n",pForest->nanotubes[i].points[j].z);
                }
            }

            // I don't have the complete specification of this file, so ignore a few more lines.
            for (int j = 1; j < pForest->nanotubes[i].size; ++j) {
                fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
            }

            // Next one, please.
            ++i;
        }

        // We don't need the simulation file anymore.
        fclose(lFile);
    }
}

void forest_read_solution(forest_t* pForest, char pSolutionFile[]) {
/**
    Solution da LILI, nao necessita do ultimo for dessa funcao.
    Solution impresso pela funcao forest_write_simulation necessita do ultimo for
**/
    // Try to open the file as read only.
    FILE* lFile = fopen(pSolutionFile, "r");

    // Check if we were able to open the file.
    if (lFile != NULL) {
        // Temporary pointer to store data.
        char lReadBuffer[FOREST_READ_BUFFER_SIZE];
        char* lRead;

        // Just a counter to store current nanotube index.
        int i = 0;

        // Ignore the first line, because I don't know what it is
        fgets(lReadBuffer,FOREST_READ_BUFFER_SIZE,lFile);

        // Now, lets loop through the file until we reach the end.
        printf("pForest->totalCNTS: %i\n",pForest->totalCNTs);
        while (i < pForest->totalCNTs) {
            // If the file is corrupt, the end could be reached before the counter.
            if (feof(lFile)) break;


            // Ignore the nanotube index from file.
            fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
            // Ignore the next line, because I don't know what it is.
            fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);

            // Now, read the amount of points this nanotube has.
            lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
            if (lRead != NULL) pForest->nanotubes[i].size = atoi(lReadBuffer) + 1;

            //testing
            //printf("p\n%d\n30\n", i);
            // end testing

            // Loop and read all data points.
            for (int j = 0; j < pForest->nanotubes[i].size; ++j) {
                // Read point coordinates.
                lRead = fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
                // Did we read anything?
                if (lRead != NULL) {
                    pForest->nanotubes[i].points[j].id = (i * pForest->growthSteps) + j;
                    // Ok, tokenize the string and store the coordinate.
                    char* lToken = strtok(lRead, " ");
                    pForest->nanotubes[i].points[j].x = atof(lToken);
                    lToken = strtok(NULL, " ");
                    pForest->nanotubes[i].points[j].y = atof(lToken);
                    lToken = strtok(NULL, " ");
                    pForest->nanotubes[i].points[j].z = atof(lToken);
                    // printf("nanotubes[i].points[j].z = %f\n",pForest->nanotubes[i].points[j].z);
                    // printf("%g %g %g\n", pForest->nanotubes[i].points[j].x,pForest->nanotubes[i].points[j].y, pForest->nanotubes[i].points[j].z);
                    // pForest->nanotubes[i].points[j].z = 0;  // testing
                }
            }

            // I don't have the complete specification of this file, so ignore a few more lines.
            // 0.0 0.0 0.0 Lines wrote on forest_write_simulation

            /*for (int j = 1; j < pForest->nanotubes[i].size; ++j) {
                fgets(lReadBuffer, FOREST_READ_BUFFER_SIZE, lFile);
            }*/

            // Next one, please.
            ++i;
        }

        // We don't need the simulation file anymore.
        fclose(lFile);
    }
    else{
        printf("Arquivo solution não encontrado! \n");
        exit(1);
    }
}

void forest_write_attributes(forest_t* pForest, char pAttributesFile[]) {
	FILE* lFile = fopen(pAttributesFile, "w");

	if (lFile != NULL) {
		fprintf(lFile, "%d\t\t#seed\n", pForest->seed);
		fprintf(lFile, "%d\t\t#totalCNTs\n", pForest->totalCNTs);
		fprintf(lFile, "%lf\t\t#spacing in micrometers\n", pForest->spacing);
		fprintf(lFile, "%d\t\t#growthSteps\n", pForest->growthSteps);
		fprintf(lFile, "%lf\t\t#minX\n", pForest->minX);
		fprintf(lFile, "%lf\t\t#maxX\n", pForest->maxX);
		fprintf(lFile, "%lf\t\t#sigma\n", pForest->sigma);
		fprintf(lFile, "%d\t\t#density\n", pForest->density);
		fprintf(lFile, "%d\t\t#diamInn\n", pForest->diamInn);
		fprintf(lFile, "%d\t\t#diamOut\n", pForest->diamOut);
		fprintf(lFile, "%d\t\t#growthRate\n", pForest->growthRate);
		fprintf(lFile, "%d\t\t#growthAngle\n", pForest->growthAngle);
		fprintf(lFile, "%d\t\t#captureDist\n", pForest->captureDist);
		fprintf(lFile, "%e\t\t#vdWStiffness\n\n", pForest->vdWStiffness);

		for (int i = 0; i < pForest->totalCNTs; ++i) {
			fprintf(lFile, "#cnt %i\n", i);
			fprintf(lFile, "%lf\t\t#diamInn\n", pForest->nanotubes[i].diamInn);
			fprintf(lFile, "%lf\t\t#diamOut\n", pForest->nanotubes[i].diamOut);
			fprintf(lFile, "%lf\t\t#growthRate\n", pForest->nanotubes[i].growthRate);
	        fprintf(lFile, "%lf\t\t#growthAngle\n", pForest->nanotubes[i].growthAngle);
	        fprintf(lFile, "%lf\t\t#second inertia\n", pForest->nanotubes[i].secondInertia);
	        fprintf(lFile, "%lf\t\t#section area\n", pForest->nanotubes[i].sectionArea);
	        fprintf(lFile, "%d\t\t#DOF\n", pForest->nanotubes[i].dof);
	        fprintf(lFile, "%d\t\t#MAX_SEGM\n", pForest->nanotubes[i].maxSegm);
	        fprintf(lFile, "%lf\t\t#segLength\n", pForest->nanotubes[i].segLength);
		}

		fclose(lFile);
	}
}

void forest_write_simulation(forest_t* pForest, char pSimulationFile[]) { /// Na verdade é o solution !
	FILE* lFile = fopen(pSimulationFile, "w");

	if (lFile != NULL) {
		int lCounter = 0;
		fprintf(lFile,"first line\n");
		for (int i = 0; i < pForest->totalCNTs; ++i) {
			//fprintf(lFile, "p\t\t#cnt %d\n", i);

			fprintf(lFile,"p\n");
			fprintf(lFile,"%d\n",i);
			//fprintf(lFile, "1\n");
			fprintf(lFile, "%d\n", pForest->nanotubes[i].size - 1);

			for (int j = 0; j < pForest->nanotubes[i].size; ++j) {
				//fprintf(lFile, "%lf %lf %d\n", pForest->nanotubes[i].points[j].x, pForest->nanotubes[i].points[j].y, lCounter++);
				//fprintf(lFile, "%lf %lf %lf %d\n", pForest->nanotubes[i].points[j].x, pForest->nanotubes[i].points[j].y, pForest->nanotubes[i].points[j].z, lCounter++);
				fprintf(lFile, "%lf %lf %lf\n", pForest->nanotubes[i].points[j].x, pForest->nanotubes[i].points[j].y, pForest->nanotubes[i].points[j].z);
			}

            // NOTE (pedro#1#): Essa impressao eh necessaria?
			/*for (int j = 1; j < pForest->nanotubes[i].size; ++j) {
				fprintf(lFile, "0.0 0.0 0.0\n");
			}*/
		}

		fclose(lFile);
	}
}

void forest_destroy(forest_t* pForest) {
    // Free all memory used by the nanotubes.
    if (pForest->nanotubes != NULL) free(pForest->nanotubes);
    // And free all memory used by all points.
    if (pForest->buffer != NULL) free(pForest->buffer);
}
