#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H
#include "Block.h"
#include "Contact.h"
#include "DrawableNanotube.h"
#include "Graph.h"
#include <vector>

namespace Library
{

class SuperBlock
{
    public:
        typedef enum {
            SUPERBLOCK = 0,
            BLOCK = 1,
            CONTACTS = 2,
            NONE = 3
        } VISUALIZATION;

        SuperBlock(Contact *c, std::vector<DrawableNanotube*> *nano, int superIndex, double graphCriticalDistance);
        virtual ~SuperBlock();

        void ConfigureGraph(Graph::ATTRACTOR att, Graph::ANCHOR anc, Graph::GRAPH_TYPE g_type,
                            Graph::HEURISTIC heu, Graph::COLOR_ORDER c_order,
                            Graph::COLOR_CHOICE c_choice, Graph::GRAPH_ORDER g_order,
                            Graph::SOLUTION sol);

        void SetSuperblock(unsigned int cpid);
        void SetSuperblockGraph(DrawableSpheres *attractor, DrawableSpheres *anchor, DrawableSpheres *mControlPointSpheres);
        void SetSuperblockGraphColor();
        void SetOverlapPoints(VISUALIZATION vis);
        unsigned int GetBlocksSize() { return mBlocks.size(); };
        unsigned int GetAddCpidSize() { return mAdditionalCpids.size(); };
        bool IsGraphComputed() {return (mGraph ? true : false); };
        void DrawGraph(bool mDrawAttractors);
        void SolveSuperBlock();
        void ClearSuperblock();
        unsigned int ClearSuperblockGraph();
        void UpdateAttractorSphereIndex();
        void UpdateAnchorSphereIndex(unsigned int anchorUpdate);
        unsigned int ResetSuperblockGraph();
        void DisplayGraphInfo();
        glm::vec3 GetSuperblockCenter();
        void AddEdge();
        void RemoveEdge();

        double GetAllDisplacements();
        unsigned int GetControlPointColor(int i);
        glm::vec2 GetGraphNode(int vert, int neighbour);
        int GetGraphType();
        int GraphAttractors();
        int GraphAnchors();
        int GraphColorOrder();
        int GraphListOrder();
        int GraphHeuristic();
        int GraphColorChoice();
        int GraphSolution();
        unsigned int GetGraphSize();
        unsigned int GetGraphNeighbourSize(int vert);
        unsigned int GetGraphEdges();
        unsigned int GetGraphMaxColor();
        int GetGraphColorPermutationIndex();
        int GetGraphColorTotalPermutation();
        double GetOrderMatrixConditioning(unsigned int component);
        int GetTotalComponents();
        std::vector<glm::vec4> GetContactsSize() { return mSegmentsInContact; };

        int SuperblockContactLookUp();

        void SaveSuperblock(std::string mFilePath);
        bool LoadSuperblock(std::string mFilePath, int &line, DrawableSpheres *attractor, DrawableSpheres *anchor, DrawableSpheres *mControlPointSpheres);

        int GetAddCpid(int i);
        Block* GetBlock(int i);
        glm::vec3 GetColor();

    protected:

    private:
        Contact *contacts;
        std::vector<DrawableNanotube*> *mDrawNano;

        int segmentsPerCNT;
        Graph *mGraph;
        double mGraphCriticalDistance;

        // apenas ids adicionais que nao pertencem a outros blocos
        std::vector<Block*> mBlocks;
        std::vector<unsigned int> mAdditionalCpids;
        std::vector<unsigned int> mAllCpids;

        Graph::ATTRACTOR mAttractorType;
        Graph::ANCHOR mAnchorType;
        Graph::GRAPH_TYPE mGraphType;
        Graph::HEURISTIC mColoringHeuristic;
        Graph::COLOR_ORDER mColorOrder;
        Graph::COLOR_CHOICE mColoringChoice;
        Graph::GRAPH_ORDER mGraphOrdination;
        Graph::SOLUTION mOrderSolution;

        int mSuperblockIndex;

        std::vector<glm::vec4> mSegmentsInContact; /// cpid1, cpid2, dist antes, diste depois do deslocamento

        void FillVector(std::vector<unsigned int>&vec, unsigned int id);
        bool contains(const std::vector<unsigned int>&a, const unsigned int b);

        int GetCNT(unsigned int id);
        int GetIndex(unsigned int id);
        unsigned int GetControlPointID(int cnt, int ind);
};
}

#endif // SUPERBLOCK_H
