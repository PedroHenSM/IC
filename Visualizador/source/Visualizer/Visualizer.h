#pragma once

#include "Forest.h"
#include "Renderer.h"
#include "DrawableNanotube.h"
#include "NanotubeMaterial.h"
#include "OrbitCamera.h"
#include "DrawableSpheres.h"
#include "Text2D.h"

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <list>

#define PrecumputedPoints 500

namespace Library
{
    class Visualizer : public Renderer
    {
    public:
        Visualizer(std::string windowName, char **args);
        ~Visualizer();

        void Run();
		void Exit();
		void Initialize();
		void Update(const RendererTime& rendererTime);
		void Draw(const RendererTime& rendererTime);
		void Resize(int width, int height);
        void Input(int key, int scanCode, int action, int mod);

    private:

        typedef enum exec{
            LOAD = 0,
            RUN_SCRIPT = 1,
            MANUAL = 2
        } EXECUTION;

        EXECUTION execution;

        std::string mFilePathAttributes;    /// Path to the CNT attributes
        std::string mFilePathControlPoints; /// Path to the control points
        std::string mDirectoryPath;    /// Path to this directory

        bool mDragging;
        bool mZooming;
        bool mPanning;

        bool mDrawContactLine;
        bool mDrawSplineContactLine;
        bool mDrawGraph;
        bool mDrawAttractors;

        GLfloat mCameraScale[3];

        // Classes
        Forest *mForest;
        OrbitCamera* mCamera;
        NanotubeMaterial *mSolidMaterial;
        DrawableSpheres *mControlPointsSpheres;
        DrawableSpheres *mIntersectionSpheres;      // esferas que marcam onde houve interseção
        DrawableSpheres *mAnchorSpheres;
        DrawableSpheres *mAttractorSpheres;

        SuperBlock::VISUALIZATION vis;
        int mSuperblockIterator;

        /// CNTs info
        std::vector<DrawableNanotube*> mDrawNano;  // lista de cnts para buscar a matriz de transformacao e posição dos pontos de controle
        int mSegmentsPerCNT;
        double mDistance;                            // distancia usada para busca de contatos
        double mIncrement;                           // incremento na distancia de captura
        double mCriticalDistance = 0.3;       // Distancia critica
        double mGraphCriticalDistance = 0.3;       // Distancia critica para o grafo
        bool mSolveWholeForest;
        unsigned int mSuperStart;
        unsigned int mSuperBreak;

        /// Contacts
        int mContactIterator;                // para mudar o foco da camera ao visualizar contatos
        bool mDuplicates;                     // Para adicionar ou nao contatos repetidos
        bool mNeedContactUpdate;

        /// Graph
        bool mPushAwayCNTs;
        Graph::ATTRACTOR mAttractorType;
        Graph::ANCHOR mAnchorType;
        Graph::GRAPH_TYPE mGraphType;
        Graph::HEURISTIC mColoringHeuristic;
        Graph::COLOR_ORDER mColorOrder;
        Graph::COLOR_CHOICE mColoringChoice;
        Graph::GRAPH_ORDER mGraphOrdination;
        Graph::SOLUTION mOrderSolution;

        clock_t mStartTime;
        clock_t mEndTime;

        std::vector<double> mInitialCNTDistortion;
        std::string mForestSeed;
        std::string mForestDensity;
        std::string mForestStdDev;

        bool FileExists(const std::string& name);
        void ReadData();
        void ClearSpheres(DrawableSpheres *spheres);
        void SetControlPointSpheres(unsigned int super_start,unsigned int super_break);
        void DisplayMenu();
        void SaveVisualizer();
        void LoadVisualizer();
        bool IsSolvedForestFile();
        bool IsScript(std::string scriptPath);
        void ScriptReader();
        int SetAttributteFilename(char **args, int i);
        int SetControlPointsFilename(char **args, int i);
        void SaveConfiguration(char **args, int &i);
        void SetGraphConfig(char **args, int &i);
        void RunScript();
        void SaveForestData();
        double GetDiedralAngle(int cnt, int ind, double &cosine);

        void CompareContacts(std::string remainingContacts);

        std::string GetForestSolutionFilename(std::string base);

        unsigned int GetControlPointID(int cnt, int ind);
        int GetCNT(unsigned int id);
        int GetIndex(unsigned int id);

    };
}
