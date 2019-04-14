#ifndef FOREST_H
#define FOREST_H
#include "DrawableNanotube.h"
#include "OrbitCamera.h"
#include "Contact.h"
#include "SuperBlock.h"

namespace Library
{

class Forest
{
    public:
        Forest(DrawableSpheres *attractor, DrawableSpheres *anchor, DrawableSpheres *control, int exec, double graphCriticalDistance);
        virtual ~Forest();
        void ClearForest();
        std::vector<DrawableNanotube*> ReadData(std::string mFilePathAttributes,
                                                std::string filePathControlPoints,
                                                Renderer* visualizer,
                                                OrbitCamera* mCamera,
                                                NanotubeMaterial *mSolidMaterial);
        std::vector<DrawableNanotube*> LoadSolvedForest(std::string mFilePathAttributes,
                                                 std::string filePathControlPoints,
                                                 Renderer* visualizer,
                                                 OrbitCamera* mCamera,
                                                 NanotubeMaterial *mSolidMaterial);

        void ConfigureGraph(Graph::ATTRACTOR att, Graph::ANCHOR anc, Graph::GRAPH_TYPE g_type,
                            Graph::HEURISTIC heu, Graph::COLOR_ORDER c_order,
                            Graph::COLOR_CHOICE c_choice, Graph::GRAPH_ORDER g_order,
                            Graph::SOLUTION sol);

        std::string GetSolutionMethod();

        glm::vec3 GetInitialCameraFocus();
        glm::vec3 GetContactCameraFocus(int mContactIterator);
        glm::vec3 GetSuperblockCameraFocus(unsigned int super);
        void ContactLookUp(DrawableSpheres *mIntersectionSpheres);
        double GetRadius(int cnt);
        unsigned int GetTotalNanotubes() { return mDrawNano->size(); };
        unsigned int GetSuperBlocksSize() { return mSuperBlocks.size(); };

        void SetSuperBlocks();
        void ClearSuperblocks();
        bool SetSuperBlocksGraphs(unsigned int start, unsigned int end);
        bool SetSuperBlocksGraphsColors(unsigned int start, unsigned int end);
        bool IsSuperblockGraphComputed(unsigned int start, unsigned int end);
        void SetVisualization(SuperBlock::VISUALIZATION vis);
        void DrawSuperblocksGraphs(bool mDrawAttractors);
        void DrawContacts();
        void SolveForest(unsigned int start, unsigned int end);
        void SaveSolvedForest(std::string filename);

        void ComparePoints();

        void AddEdgeOnSuperblock(unsigned int s_iterator);
        void RemoveEdgeOnSuperblock(unsigned int s_iterator);
        void ClearSuperblockGraph(unsigned int s_iterator);
        void ResetSuperblockGraph(unsigned int s_iterator);
        void DisplayGraphInfo(unsigned int s_iterator);
        int GetSuperblockContacts(unsigned int s_iterator);

        int GetBlocksSize(unsigned int s_iterator);
        unsigned int GetGraphSize(unsigned int s_iterator);
        unsigned int GetGraphEdges(unsigned int s_iterator);
        unsigned int GetGraphMaxColor(unsigned int s_iterator);
        int GetGraphColorPermutationIndex(unsigned int s_iterator);
        int GetGraphColorTotalPermutation(unsigned int s_iterator);
        double GetOrderMatrixConditioning(unsigned int s_iterator, unsigned int component);
        int GetTotalComponents(unsigned int s_iterator);
        std::vector<glm::vec4> GetContactsSize(unsigned int s_iterator);

        int GetCNT(unsigned int id);
        int GetIndex(unsigned int id);
        unsigned int GetControlPointID(int cnt, int ind);

        Contact *mContacts;

    protected:

    private:
        typedef enum exec{
            LOAD = 0,
            RUN_SCRIPT = 1,
            MANUAL = 2
        } EXECUTION;

        DrawableSpheres *mAttractorSpheres;
        DrawableSpheres *mAnchorSpheres;
        DrawableSpheres *mControlPointSpheres;
        int segmentsPerCNT;

        std::vector<DrawableNanotube*> *mDrawNano; // cada CNT da floresta
        std::vector<SuperBlock*> mSuperBlocks;
        std::string mFilePathControlPoints;
        std::vector<glm::vec3> mPointsRead;

        double mGraphCriticalDistance;
        Graph::ATTRACTOR mAttractorType;
        Graph::ANCHOR mAnchorType;
        Graph::GRAPH_TYPE mGraphType;
        Graph::HEURISTIC mColoringHeuristic;
        Graph::COLOR_ORDER mColorOrder;
        Graph::COLOR_CHOICE mColoringChoice;
        Graph::GRAPH_ORDER mGraphOrdination;
        Graph::SOLUTION mOrderSolution;

        int seed;
        EXECUTION execution;

        void SetControlPointSpheres();

        bool CheckSuperBlocks(unsigned int start, unsigned int end);
        bool IsSolvedForestFile(std::string filePathControlPoints);
};
}
#endif // FOREST_H
