#ifndef CONTACT_H
#define CONTACT_H
#include "DrawableNanotube.h"
#include "DrawableSpheres.h"

namespace Library
{


class Contact
{
    public:
        Contact(std::vector<DrawableNanotube*> *cnts, std::string controlPointsFilePath);
        virtual ~Contact();

        void Configure(double crit, double distance, bool dupli);

        void ContactLookUp(DrawableSpheres *mIntersectionSpheres);
        void SetContactDistance(double dist) { mContactDistance = dist; };
        double GetContactDistance() { return mContactDistance; };
        void IncludeDuplicates(bool duplicates) { mDuplicates = duplicates; };
        unsigned int GetTotalContacts() { return mIndices.size(); };
        unsigned int GetTotalControlPoints() { return controlPointsContacts.size(); };
        int GetSegmentsPerCNT() { return segmentsPerCNT; };
        double GetCriticalDistance() { return mCriticalDistance; };
        void SetCriticalDistance(double critical) { mCriticalDistance = critical; };
        bool IsAnchor(unsigned int cpid);
        void SetAnchor(unsigned int cpid, bool isAnchor);
        bool WasAddedToBlock(unsigned int cpid);
        void SetAddedToBlock(unsigned int cpid, bool added);
        int GetContactsSize(unsigned int cpid);
        glm::uvec4 GetControlPointContact(unsigned int cpid, int i);
        void GetContactRatio(int cnt1, int ind1, int cnt2, int ind2, double &ratio1, double &ratio2);
        void PrintContacts(unsigned int cpid);
        void PrintContact(int mContactIterator);

        bool ContactExists(int cnt1, int ind1, int cnt2, int ind2);

        glm::uvec4 GetContactIndices(int i);
        glm::vec3 GetContactCenter(int i);
        Vertex GetContact1(int i);
        Vertex GetContact2(int i);

        void SaveContactList(std::string filename);

        double DistFromSegments(Vertex pos_m2, Vertex pos_m1,Vertex pos_m2_1,
                                Vertex pos_m1_1,Vertex &pt1, Vertex &pt2);
    protected:

    private:
        typedef struct
        {
            unsigned int id;
            bool added = false; // para saber se o contato foi adicionado a um bloco
            bool isAnchor = false;
            std::vector<glm::uvec4> contacts;
        } cpList;

        std::vector<DrawableNanotube*> *mDrawNano;
        int segmentsPerCNT;
        int mTotalContacts;
        bool mDuplicates;        // Contar contatos duplos ou nao
        double mContactDistance; // distancia usada para busca de contatos

        std::vector<cpList> controlPointsContacts;

        /// para visualização dos contatos
        std::vector<glm::uvec4> mIndices;    // lista com o índice dos pontos em contato
        std::vector<Vertex> mContactCNT1;    // lista com a posição do ponto em cnt1 que esta mais proximo de cnt2
        std::vector<Vertex> mContactCNT2;    // lista com a posição do ponto em cnt2 que esta mais proximo de cnt1

        double mCriticalDistance = 0.30; // Distancia critica

        std::string mFilePathControlPoints;

        void ClearContacts();
        double GetContactPointRatio(Vertex pt1, unsigned int cpid1);
        double DotVector(Vertex v1, Vertex v2);
        double SegmentCyllinderIntersection(unsigned int cpid1, Vertex pt1, Vertex pt2, Vertex &vert);

        int GetCNT(unsigned int id);
        int GetIndex(unsigned int id);
        unsigned int GetControlPointID(int cnt, int ind);

        void ResetContacts();

};
}
#endif // CONTACT_H
