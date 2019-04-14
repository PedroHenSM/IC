#ifndef GRAPH_H
#define GRAPH_H

#include "Contact.h"
#include <gsl/gsl_matrix.h>

namespace Library
{
class Graph
{
    public:

        typedef enum att{
            MIDPOINT = 0,
            ONEPOINT = 1,
            EXTREMES = 2
        } ATTRACTOR;

        typedef enum anc{
            SUPERBLOCK = 0,
            GRAPH = 1
        } ANCHOR;

        typedef enum type{
            CONTACTS = 0,
            CONNECTED = 1,
            ULTRA_CONNECTED = 2,
            SIMPLE_CONNECTED = 3,
            CONTACT_TO_POINT = 4
        } GRAPH_TYPE;

        typedef enum c_order{
            INITIAL = 0,    // Sem permutação de cores
            BEST = 1,       // Permutação de cores para uma HEURISTIC
            VERY_BEST = 2   // Testa todas as HEURISTIC e permutações de cores
        } COLOR_ORDER;

        typedef enum g_order{
            INCREASE = 0,    // Ordem crescente
            UP_DOWN = 1,     // Cada CNT fica em ordem crescente e decrescente alternadamente
            CNT_HIGHEST_CONNECTION = 2   // CNT com mais conexões deve tender a ficar próximo a Z = 0
        } GRAPH_ORDER;

        typedef enum greedy{
            FIRST_FIT = 0,
            DFS = 1, // Depth First Search
            LDO = 2, // Largest Degree Order
            SDO = 3, // Saturation Degree Order
            IDO = 4, // Incidence Degree Order
            DFS_LDO = 5,  // Largest Degree Order comecando pelo vertice de maior grau
            BFS = 6  // Breadth First Search
        } HEURISTIC;

        typedef enum choice{
            MIN_INDEX = 0,
            LAST_INDEX = 1,
            CLOSEST_CNT_INDEX = 2
        }COLOR_CHOICE;

        typedef enum solution{
            ORIGINAL = 0, // raios dos CNTs no vetor B da matriz de ordem
            ORIGINAL_MAX = 1, // raios dos CNTs no vetor B da matriz de ordem. Maior raio da cor intermediária é escolhido
            ORIGINAL_MIN = 2, // raios dos CNTs no vetor B da matriz de ordem. Menor raio da cor intermediária é escolhido
            CRITICAL = 3, // Apenas a distância critica. Sem raios
            DIRECT = 4, // sem sistema linear
            HYPOTENUSE = 5 // criando pontos extras e calculando a hhipotenusa
        } SOLUTION;

        Graph(Contact *c,
             std::vector<DrawableNanotube*> *nano,
             std::vector<unsigned int> *SuperCpids,
             DrawableSpheres *attractor,
             DrawableSpheres *anchor,
             DrawableSpheres *controlPointSpheres);
        virtual ~Graph();

        void SetGraph();
        void DrawGraph(bool mDrawAtt);
        void SolveGraph();
        void SetDisplacement();
        bool IsGraphSolved();
        unsigned int ClearGraph();
        void UpdateAttractorSphereIndex();
        void UpdateAnchorSphereIndex(unsigned int anchorUpdate);
        unsigned int ResetGraph();
        bool NeedToPushAway() { return mPushAway; };

        void PrintAdjacencyList() { PrintGraph(&mAdjacencyList); };
        bool AddNewEdge(unsigned int cpid1, unsigned int cpid2);
        bool RemoveEdge(unsigned int cpid1, unsigned int cpid2);

        glm::vec3 GetAttractorPosition(int att);
        unsigned int GetAdjacencyListSize() { return mAdjacencyList.size(); };
        unsigned int GetAttractorsSize() { return mAttractors.size(); };
        unsigned int GetGraphEdges();
        unsigned int GetGraphMaxColor();

        int GetGraphColorPermutationIndex() { return mPermutationIndex; }; /// se o grafo não foi computado, o valor será 0
        int GetGraphColorTotalPermutation() { return mPermutationTotal; }; /// se o grafo não foi computado, o valor será 0
        double GetOrderMatrixConditioning(unsigned int component);
        int GetTotalComponents() { return mTotalComponents; };

        unsigned int GetVertexNeighbourSize(int v);
        glm::vec2 GetVertexContent(int v, int n = 0);

        void SetControlPointColor();
        void DisplayGraphInfo();

        void ConfigureGraph(double mGraphCriticalDistance, ATTRACTOR att, ANCHOR anc, GRAPH_TYPE g_type, HEURISTIC heu,
                           COLOR_ORDER c_order, COLOR_CHOICE c_choice, GRAPH_ORDER g_order,
                           SOLUTION sol);

        double GetAllDisplacements();
        unsigned int GetControlPointColor(int i);
        glm::vec2 GetGraphCPID(int vert, int neighbour);
        int GetGraphType();
        int GraphAttractors();
        int GraphAnchors();
        int GraphColorOrder();
        int GraphListOrder();
        int GraphHeuristic();
        int GraphColorChoice();
        int GraphSolution();

        void SaveGraph(std::string mFilePath);
        bool LoadGraph(std::string mFilePath, int &line);

    protected:

    private:
        typedef struct node{
            int cnt;
            int ind;
            double weight;
        } GraphNode;

        typedef struct gList
        {
            std::vector<GraphNode*> mGraphNode;
            int mNodeColor;
        } GraphList;

        /// Dados de entrada do construtor
        Contact *mContacts;
        std::vector<DrawableNanotube*> *mDrawNano;
        std::vector<unsigned int> *mAllCpids;
        DrawableSpheres *mAttractorSpheres;
        DrawableSpheres *mAnchorSpheres;
        DrawableSpheres *mControlPointSpheres;

        bool mAddAnchors;
        bool mConsiderAnchors;
        bool mNeedGraphUpdate;
        bool mPushAway;
        double mAttractorZ;
        unsigned int mAttractorSphereIndex;
        unsigned int mAnchorSphereIndex;
        glm::vec3 mAttractorColor;
        glm::vec3 mAnchorColor;
        glm::vec3 mGraphColor;
        int segmentsPerCNT;


        std::vector<std::vector<glm::vec2>> mAdjacencyList;
        std::vector<glm::vec3> mAttractors;
        std::vector<unsigned int> mAnchors;
        std::vector<unsigned int> mGraphColoring;


        ATTRACTOR mAttractorType;
        ANCHOR mAnchorType;
        GRAPH_TYPE mGraphType;
        HEURISTIC mColoringHeuristic;
        COLOR_ORDER mColorOrder;
        COLOR_CHOICE mColoringChoice;
        GRAPH_ORDER mGraphOrdination;
        SOLUTION mOrderSolution;

        int mTotalCnts;
        double mCriticalDistance;
        int mPermutationIndex = 0;
        int mPermutationTotal = 0;
        std::vector<double> mOrderMatrixConditioning;
        int mTotalComponents = 0;

        gsl_vector *mControlPointDisplacement;

        std::vector<unsigned int> mColorOrdination;
        std::vector<glm::vec4> mNanListHyp;
        std::vector<glm::vec2> mNanListDir;

        void RemoveIsolatedVertices();
        void SetAttractors();
        void SetAnchors();
        void GraphOrdination();

        void FreeAdjacencyList(std::vector<std::vector<glm::vec2>> *adj_list);
        int SearchInList(unsigned int cpid, std::vector<std::vector<glm::vec2>> *adj_list);
        int SearchInNeighbours(int vert, unsigned int cpid, std::vector<std::vector<glm::vec2>> *adj_list);
        void AddVertex(unsigned int cpid);
        bool AddEdge(unsigned int cpid1, unsigned int cpid2);
        void ResetControlPointColors();
        void UpdateGraph();
        void GetGraphComponentsUtil(std::vector<int> *visited, int v, int component);
        std::vector<int> GetGraphComponents(int &component);
        std::vector<std::vector<glm::vec2>> GetConnectedComponent(int component, std::vector<int> *visited);


        void GetConnectedComponentDistances(std::vector<std::vector<glm::vec2>> *ConnectedComponent,
                                  std::vector<unsigned int> *color_order,
                                  std::vector<double> *max_distance,
                                  std::vector<double> *min_distance);
        glm::vec4 GetMinMaxRadiusByColor(std::vector<std::vector<glm::vec2>> *ConnectedComponent , unsigned int color);
        double GetValueForNonConsecutivePlanes(unsigned int colorOrder1, unsigned int colorOrder2, double val,
                                             std::vector<unsigned int> *color_order,
                                             std::vector<std::vector<glm::vec2>> *ConnectedComponent);

        double GetValueForConsecutivePlanes(int indNeg, int indPos, unsigned int colorOrder1, unsigned int colorOrder2,
                                            std::vector<unsigned int> *color_order,
                                            std::vector<std::vector<glm::vec2>> *ConnectedComponent);
        Vertex GetRadiusProjectionOnEdge(int cnt, unsigned int cpid1, unsigned int cpid2);

        double GetMinDistanceBetweenColors(unsigned int color1, unsigned int color2);
        void DirectPushZCoordinate();
        void DirectHypotenuse();
        void DirectHypotenuseWithEpsilon();

        void ResetGraphWeights();
        void SetWeights();
        void SetWeightsAsVertexDegree();
        void SetComponentWeights(std::vector<std::vector<glm::vec2>> *ConnectedComponent,
                                 std::vector<unsigned int> *color_order, double &conditioning);
        gsl_vector* GetComponentWeights(std::vector<std::vector<glm::vec2>> *ConnectedComponent,
                                        std::vector<unsigned int> *color_order, double &conditioning);
        std::vector<unsigned int> SetColorOrder();
        std::vector<unsigned int> SetMinimalColoringHeuristic();
        std::vector<unsigned int> GraphColoringGreedy();
        void VertexColoring(int v, std::vector<unsigned int> *colors, bool verbose, int last_color);
        int GetColor(int v, std::vector<unsigned int> *colors, std::vector<std::vector<glm::vec2>> *adj_list, int last_color);
        bool CheckColor(unsigned int c, int v, std::vector<unsigned int> *colors,
                        std::vector<std::vector<glm::vec2>> *adj_list);
        unsigned int GetTotalGraphColors(std::vector<unsigned int> *colors);
        std::vector<unsigned int> GetInitialColorOrder();
        std::vector<unsigned int> GetBestColorOrder(int &totalContacts);
        void ComponentContactLookUp(std::vector<std::vector<glm::vec2>> *ConnectedComponent,
                                   std::vector<unsigned int> *color_order,
                                   int &total_contacts, double &contactsLenght, double &distortion);

        std::vector<glm::vec2> GetEdges(std::vector<unsigned int> *color_order,
                                        std::vector<std::vector<glm::vec2>> *ConnectedComponent);
        gsl_matrix* GetOrderMatrix(std::vector<unsigned int> *color_order,
                                   std::vector<std::vector<glm::vec2>> *ConnectedComponent);
        gsl_vector* ComputeBvectorOrderMatrix(gsl_matrix *edgeMatrix,
                                              std::vector<unsigned int> *color_order,
                                              std::vector<std::vector<glm::vec2>> *ConnectedComponent);

        void PrintGraph(std::vector<std::vector<glm::vec2>> *adj_list);
        int GetCNT(unsigned int id);
        int GetIndex(unsigned int id);
        unsigned int GetControlPointID(int cnt, int ind);
};
}

#endif // GRAPH_H
