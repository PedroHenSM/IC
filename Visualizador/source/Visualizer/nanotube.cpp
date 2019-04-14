#include "nanotube.h"

#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // M_PI

FLOAT gcgOutNANOTUBE::sA0 = 1.41;

glm::vec2 gcgOutNANOTUBE::sBaseHexagon[6] = {{               0.0,      0.0},
                                            { sqrt(3.0)*sA0*0.5, -sA0*0.5},
                                            {     sqrt(3.0)*sA0,      0.0},
                                            {     sqrt(3.0)*sA0,      sA0},
                                            { sqrt(3.0)*sA0*0.5,  sA0*1.5},
                                            {               0.0,      sA0}};

gcgOutNANOTUBE::gcgOutNANOTUBE(char* filename, int indexN, int indexM, FLOAT length) : mMin(0), mMax(0)
{
    FILE *f;
    if(!strcmp(filename, ""))
    {
        f = stdout;
    }
    else
    {
        f = fopen(filename, "w");
    }


    // Basis of graphene sheet
    mM = glm::vec2(sA0 *  sqrt(3) * 0.5, 1.5*sA0);
    mN = glm::vec2(sA0 *  sqrt(3), 0.0);

    // Final point of the line segment
    mEnd = glm::vec2(mM[0] * (indexN + indexN + indexM), indexM * mM[1]);


    // Centroid of the first hexagon
    mC = glm::vec2(sqrt(3.0) * sA0 * 0.5, sA0 * 0.5);

    // Calculate the angle between the x-axis and the line from the origin to the end point
    FLOAT lineAngle = atan2(mEnd[1], mEnd[0]);

    // Matrix that align the line with x-axis
    FLOAT c = cos(-lineAngle), s = sin(-lineAngle);
    mMat = glm::mat2(c, -s, s, c);

    // Update the base hexagon orientation
    for(int i = 0; i < 6; i++)
    {
        sBaseHexagon[i] = mMat * sBaseHexagon[i];
    }

    // Apply the rotation to all vectors
    {
        glm::vec2 vAux;

        // The centroid
        mC = mMat * mC;

        mM = mMat * mM;

        mN = mMat * mN;

        mEnd = mMat * mEnd;
    }

    NextHex nextHexReference[indexN+indexM];



    // Current position
    glm::vec2 offset(0);

    // Number of rings printed
    int l = 1;

    // Number of faces printed
    int faces = 1;


    while(faces < indexM+indexN)
    {
        // Calculate the next possible offsets
        glm::vec2 c1, c2;
        c1 = mC + mN;
        c2 = mC + mM;

        // Get the closest to the line

        // If C1 is closer to the line, update the offset using its data
        // set the reference to the previous hexagon
        // and print the vertex accordingly, without repeating vertices
        if(abs(c1[1]) < abs(c2[1]))
        {
            offset += mN;
            mC = c1;

            if(faces+1 != indexM+indexN )
                CheckFace(offset, f, 1, 4);
            else
            {
                CheckFace(offset, f, 1, 1);
                CheckFace(offset, f, 4, 4);
            }
            nextHexReference[faces-1] = NextHex_Right;
        }
        // Else use C2 data
        else
        {
            offset += mM;
            mC = c2;

            if(faces+1 != indexM+indexN )
                CheckFace(offset, f, 2, 5);
            else
                CheckFace(offset, f, 4, 5);

            nextHexReference[faces-1] = NextHex_Up;
        }

        faces++;
    }
    // The last hexagon in the ring
    nextHexReference[indexM+indexN-1] = NextHex_End;

    // Calculate the number of ring
    FLOAT baseHeight = mMax - mMin;
    // h = bHeight + (l-1) * slope -> l = ((h - bHeight) / slope) +1
    int rings = floor(((length - baseHeight) / mMax) + 1);
    fprintf(stdout, "Rings: %d\n", rings);



    //------------------------------------------
    // OFF header
    //------------------------------------------
    fprintf(f, "OFF\n");
    fprintf(f, "%d %d 0\n", 2*(indexM+indexN)*(rings+1), (indexM+indexN)*rings);


    //------------------------------------------
    // XYZ Header
    //------------------------------------------
    //fprintf(f, "%d \n\n", (2*(indexM+indexN))*(rings+1));

    offset = glm::vec2( 0, -mMin);
    faces = 1;
    // Print the first hexagon
    PrintFace(offset, f, 0, 5);

    //---------------------------------------------------------------------------------
    // Print the first ring and store only the basic data depending on the next hexagon
    //---------------------------------------------------------------------------------
    while(faces < indexM+indexN)
    {
        // Calculate the next possible offsets
        glm::vec2 c1, c2;
        c1 = mC + mN;
        c2 = mC + mM;

        // Get the closest to the line

        // If C1 is closer to the line, update the offset using its data
        // set the reference to the previous hexagon
        // and print the vertex accordingly, without repeating vertices
        if(abs(c1[1]) < abs(c2[1]))
        {
            offset += mN;
            mC = c1;

            if(faces+1 != indexM+indexN )
                PrintFace(offset, f, 1, 4);
            else
            {
                PrintFace(offset, f, 1, 1);
                PrintFace(offset, f, 4, 4);
            }
            nextHexReference[faces-1] = NextHex_Right;
        }
        // Else use C2 data
        else
        {
            offset += mM;
            mC = c2;

            if(faces+1 != indexM+indexN )
                PrintFace(offset, f, 2, 5);
            else
                PrintFace(offset, f, 4, 5);

            nextHexReference[faces-1] = NextHex_Up;
        }

        faces++;
    }
    // The last hexagon in the ring
    nextHexReference[indexM+indexN-1] = NextHex_End;

    //---------------------------------------------------------------------------------
    // Since the other rings depends on the first, build it later using the reference
    // built during the creation of the first ring
    //---------------------------------------------------------------------------------
    while(l < rings)
    {
        glm::vec2 vAux(-l*(sqrt(3)*sA0*0.5), l*(sA0*1.5));
        offset = mMat * vAux;


        if(nextHexReference[0] == NextHex_Right)
        {
            PrintFace(offset, f, 3, 5);
            offset += mN;
        }
        else
        {
            PrintFace(offset, f, 4, 5);
            offset += mM;
        }
        faces = 1;


        while(faces < indexM+indexN)
        {
            int to = (nextHexReference[faces-1] == NextHex_Right) ? 4 : 5;
            if(nextHexReference[faces] == NextHex_Up || nextHexReference[faces] == NextHex_End)
            {
                PrintFace(offset, f, 4, to);
                offset += mM;
            }
            else
            {
                PrintFace(offset, f, 3, to);
                offset += mN;
            }

            faces++;
        }
        l++;
    }


    // List of indices of the top line of the ring
    int topIndex[2*(indexM+indexN)];
    int j = 0;

    //------------------------------------------------------------------
    // Print the indices
    //------------------------------------------------------------------
    faces = 0;
    int lastFaceIndex = 0;

    // For the first row, print and store the index of the line above to use for the next rings
    while(faces < indexN+indexM)
    {
        int index[6];
        if(faces == 0)
        {
            for(int i = 0; i < 6; i ++)
                index[i] = i;
            lastFaceIndex = 5;
        }
        else
        {
            if(nextHexReference[faces-1] == NextHex_Right)
            {
                index[0] = lastFaceIndex - 3;
                index[1] = 5 + (faces-1)*4 + 1;
                if(nextHexReference[faces] == NextHex_End)
                {
                    index[2] = 0;
                    index[3] = 5;
                    index[4] = index[1] + 1;
                }
                else
                {
                    index[2] = index[1] + 1;
                    index[3] = index[2] + 1;
                    index[4] = index[3] + 1;
                }
                index[5] = lastFaceIndex - 2;

                lastFaceIndex = index[4] + 1;
            }
            else
            {
                index[0] = lastFaceIndex - 1;
                index[1] = lastFaceIndex - 2;
                if(nextHexReference[faces] == NextHex_End)
                {
                    index[2] = 0;
                    index[3] = 5;
                    index[4] = 5 + (faces-1)*4 + 1;
                }
                else
                {
                    index[2] = 5 + (faces-1)*4 + 1;
                    index[3] = index[2] + 1;
                    index[4] = index[3] + 1;
                }
                index[5] = index[4] + 1;

                lastFaceIndex = index[5];
            }
        }

        fprintf(f, "6 %d %d %d %d %d %d\n", index[0], index[1], index[2], index[3], index[4], index[5]);
        faces++;

        topIndex[j]   = index[5];
        topIndex[j+1] = index[4];
        topIndex[j+2] = index[3];
        j += 2;
    }

    // Print the rest of the nanotube indices
    l = 1;
    lastFaceIndex = 3 + (indexM+indexN-1)*4;
    while(l < rings)
    {
        faces = 0;
        j = 0;
        int index[6];
        int t3 = 0;
        int t0 = topIndex[2*(indexM+indexN)-1];
        int indexJM1 = topIndex[2*(indexM+indexN)-1];

        while(faces < indexM + indexN)
        {
            if(faces == 0 || nextHexReference[faces-1] == NextHex_Right)
                index[0] = indexJM1;
            else
                index[0] = index[4]; // Use the fourth index of the previous hexagon

            index[1] = topIndex[j];



            if(nextHexReference[faces] == NextHex_End)
                index[2] = t0;
            else
                index[2] = topIndex[j+1];

            t3 = index[3];
            if(nextHexReference[faces] == NextHex_Up)
                index[3] = topIndex[j+2];
            else if (nextHexReference[faces] == NextHex_Right)
                index[3] = ++lastFaceIndex;
            else
                index[3] = topIndex[0];

            index[4] = ++lastFaceIndex;

            if(nextHexReference[faces-1] == NextHex_Up || faces == 0)
                index[5] = ++lastFaceIndex;
            else
                index[5] = t3;

            fprintf(f, "6 %d %d %d %d %d %d\n", index[0], index[1], index[2], index[3], index[4], index[5]);
            faces++;

            topIndex[j] = index[5];
            indexJM1 = topIndex[j+1];
            topIndex[j+1] = index[4];
            j += 2;

        }
        l++;
    }

    // Close the file output
    if(strcmp(filename, ""))
    {
        fclose(f);
    }
}

void gcgOutNANOTUBE::PrintFace(glm::vec2 offset, FILE* f, int from, int to)
{
    static glm::vec2 vAux;
    static glm::vec3 pos;


    for(int i = from; i <= to; i++)
    {
        vAux = glm::vec2(sBaseHexagon[i%6][0] + offset[0], sBaseHexagon[i%6][1]+ offset[1]);
        ProjectCilinder(vAux, pos);
        fprintf(f, "%.6f %.6f %.6f\n", pos[0], pos[1], pos[2]);
        //fprintf(f, "%.6f %.6f 0.000000\n", sBaseHexagon[i%6][0] + offset[0], sBaseHexagon[i%6][1] + offset[1]);
    }
}

#ifndef MIN
#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#endif // MIN

#ifndef MAX
#define MAX(a, b) ((a) > (b)) ? (a) : (b)
#endif // MAX

void gcgOutNANOTUBE::CheckFace(glm::vec2 offset, FILE* f, int from, int to)
{
    for(int i = from; i <= to; i++)
    {
        mMin = MIN(mMin, sBaseHexagon[i%6][1]+ offset[1]);
        mMax = MAX(mMin, sBaseHexagon[i%6][1]+ offset[1]);
    }
}

void gcgOutNANOTUBE::ProjectCilinder(glm::vec2 pos, glm::vec3& finalPosition)
{
    FLOAT perimeter = mEnd[0];
    FLOAT radius = 0.5 * perimeter / M_PI;

    float angle = 2 * M_PI * pos[0] / perimeter;

    finalPosition = glm::vec3(sin(angle) * radius, pos[1], cos(angle)*radius);
}
