#pragma once

#define FLOAT double

#include <glm/glm.hpp>
#include <cstdio>

typedef enum NextHex
{
    NextHex_Up = 0,
    NextHex_Right = 1,
    NextHex_End = 2
}NextHex;

class gcgOutNANOTUBE
{
public:
    gcgOutNANOTUBE(char* filename, int indexN, int indexM, int rings);
    gcgOutNANOTUBE(char* filename, int indexN, int indexM, FLOAT length);

    FLOAT Lenght() const;
    FLOAT BaseHeight() const;
    FLOAT PerRingHeight() const;

    void AddRing();

    int RingsForLenght(FLOAT lenght) const;


private:
    FLOAT mLenght;
    FLOAT mBaseHeight;
    FLOAT mPerRingHeight;

    glm::vec2 mN;
    glm::vec2 mM;
    glm::vec2 mC;

    glm::vec2 mEnd;

    FLOAT mMin;
    FLOAT mMax;

    static FLOAT sA0;

    static glm::vec2 sBaseHexagon[6];

    glm::mat2 mMat;

    void PrintFace(glm::vec2 offset, FILE* f, int from, int to);
    void CheckFace(glm::vec2 offset, FILE* f, int from, int to);
    void ProjectCilinder(glm::vec2 pos, glm::vec3 &finalPosition);
};
