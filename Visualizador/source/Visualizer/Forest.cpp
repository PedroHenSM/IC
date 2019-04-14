#include "Forest.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define PrecumputedPoints 500

namespace Library
{
Forest::Forest(DrawableSpheres *attractor, DrawableSpheres *anchor, DrawableSpheres *control, int exec, double graphCriticalDistance) :
    mContacts(NULL),
    mAttractorSpheres(attractor),
    mAnchorSpheres(anchor),
    mControlPointSpheres(control),
    segmentsPerCNT(0),
    mGraphCriticalDistance(graphCriticalDistance)
    //mOrderSolutionName("")
{
    //ctor
    ConfigureGraph(Graph::MIDPOINT, Graph::SUPERBLOCK, Graph::ULTRA_CONNECTED,
                   Graph::FIRST_FIT, Graph::BEST, Graph::CLOSEST_CNT_INDEX,
                   Graph::CNT_HIGHEST_CONNECTION, Graph::DIRECT);

    execution = (EXECUTION)exec;
}

Forest::~Forest()
{
    //dtor
    ClearForest();
}

void Forest::ConfigureGraph(Graph::ATTRACTOR att, Graph::ANCHOR anc, Graph::GRAPH_TYPE g_type,
                            Graph::HEURISTIC heu, Graph::COLOR_ORDER c_order,
                            Graph::COLOR_CHOICE c_choice, Graph::GRAPH_ORDER g_order,
                            Graph::SOLUTION sol)
{
    mAttractorType = att;
    mAnchorType = anc;
    mGraphType = g_type;
    mColoringHeuristic = heu;
    mColorOrder = c_order;
    mColoringChoice = c_choice;
    mGraphOrdination = g_order;
    mOrderSolution = sol;
}

std::string Forest::GetSolutionMethod()
{
    std::string solution("");

    switch(mOrderSolution)
    {
        case Graph::ORIGINAL: solution.append("ori_"); break;
        case Graph::ORIGINAL_MAX: solution.append("omx_"); break;
        case Graph::ORIGINAL_MIN: solution.append("omn_"); break;
        case Graph::CRITICAL: solution.append("cri_"); break;
        case Graph::DIRECT: solution.append("dir_"); break;
        case Graph::HYPOTENUSE: solution.append("hyp_"); break;
    }

    return solution;
}

void Forest::ClearForest()
{
    ClearSuperblocks();
    mDrawNano->clear();
}

std::vector<DrawableNanotube*>
    Forest::ReadData(std::string mFilePathAttributes,
                     std::string filePathControlPoints,
                     Renderer* visualizer,
                     OrbitCamera* mCamera,
                     NanotubeMaterial *mSolidMaterial)
{
    mDrawNano = new std::vector<DrawableNanotube*>;

    mFilePathControlPoints = filePathControlPoints;
    std::cout<<"ReadData "<<std::endl;
    std::cout<<mFilePathAttributes<<std::endl;
    std::cout<<mFilePathControlPoints<<std::endl;
    /// Lendo atributos do CNTs (raio)
    std::ifstream inputFileAtt(mFilePathAttributes);
    std::vector<double> mRadiusOutData; // salvando valores antes de criar o DrawableNanotube

    std::string buffer = "";
    std::getline(inputFileAtt, buffer);
    std::stringstream ss(buffer);
    ss >> seed;

    //std::cout<<"buffer:  ."<<buffer<<"."<<std::endl;
    //int nada;std::cin>>nada;

    for(int i = 0; i < 14; i++)
    {
        std::getline(inputFileAtt, buffer);
        //std::cout<<buffer<<std::endl;
        //int nada;std::cin>>nada;
    }
    int cont = 0;
    while(!inputFileAtt.eof())
    {
        std::string buffer = "";
        std::getline(inputFileAtt, buffer);
        if(buffer[0] == '#') continue;
        std::getline(inputFileAtt, buffer); //diamOut

        //std::cout<<"buffer diam:  ."<<buffer<<". "<<cont<<std::endl;
        cont++;

        std::stringstream ss(buffer);
        double diameter;
        ss >> diameter;
        mRadiusOutData.push_back(diameter/2.0);
        for(int i = 0; i < 7; i++)
        {
            std::getline(inputFileAtt, buffer);
        }
    }
    //std::cin>>nada;

    inputFileAtt.close();

    /// Lendo posição dos pontos dos CNTs
    std::ifstream inputFile(mFilePathControlPoints);
    int cnt_counter = 0;
    while(!inputFile.eof())
    {
        std::string buffer = "";
        std::getline(inputFile, buffer);

        if(buffer[0] == 'p')
        {
            // Create a new catmull-rom interpolator
            CatmullRom *interp = new CatmullRom(PrecumputedPoints);

            buffer = "";
            std::getline(inputFile, buffer);
            std::getline(inputFile, buffer);
            std::stringstream ss(buffer);

            int seg;
            ss >> seg;
            ss.clear();

            for(int i = 0; i < seg+1; i++)
            {
                buffer = "";
                std::getline(inputFile, buffer);
                ss.str(buffer);
                double x, y, z__ = 0.0;
                ss >> x >> y ;
                // Push the first
                if(i == 0)
                {
                    interp->PushControlPoint(x, y-20, z__);
                }
                interp->PushControlPoint(x, y, z__);
                if(i == seg) interp->InterpolateLastPoint();
                ///std::cout << "X: " << x << " Y: " << y <<" Z: "<<z__<<std::endl;
            }

            DrawableNanotube *dNanotube = new DrawableNanotube(*visualizer,
                *mCamera, interp, mSolidMaterial, mRadiusOutData[cnt_counter]);

            if(execution != RUN_SCRIPT) dNanotube->Initialize();

            mDrawNano->push_back(dNanotube);
            cnt_counter++;
            ss.clear();
        }
        //break;
    }
    inputFile.close();
    mRadiusOutData.clear();
    segmentsPerCNT = (*mDrawNano)[0]->mInterpolator->ControlPointsNumber();

    mContacts = new Contact(mDrawNano, mFilePathControlPoints);
    /// A montagem do grafo deve respeitar a distância usada na busca por contatos
    mContacts->SetContactDistance(mGraphCriticalDistance);

    SetControlPointSpheres();

    return (*mDrawNano);
}

glm::vec3 Forest::GetInitialCameraFocus()
{
    Vertex cam_pos(0.0, 0.0, 0.0);
    Vertex min_pos( INT_MAX,  0.0,  0.0);
    Vertex max_pos(-INT_MAX, -INT_MAX, 0.0);
    for(unsigned int i = 0; i < mDrawNano->size(); i++)
    {
        DrawableNanotube* dCNT = (*mDrawNano)[i];
        int totalPoints = dCNT->mInterpolator->ControlPoints().size();
        Vertex start_pos = dCNT->mInterpolator->ControlPoints()[1];
        Vertex end_pos   = dCNT->mInterpolator->ControlPoints()[totalPoints-2];

        if(min_pos.x > start_pos.x) min_pos.x = start_pos.x;
        if(min_pos.y > start_pos.y) min_pos.y = start_pos.y;
        if(max_pos.x < end_pos.x) max_pos.x = end_pos.x;
        if(max_pos.y < end_pos.y) max_pos.y = end_pos.y;
    }
    Vertex center = max_pos + min_pos;
    Transform mTransform = (*mDrawNano)[0]->GetTransform();
    glm::vec3 camera = glm::vec3(center[0]/2.0, center[1]/2.0, center[2]/2.0);
    glm::vec3 focus = glm::vec3(vec4(camera, 1.0) * mTransform.LocalToWorldMatrix());

    return focus;
}

glm::vec3 Forest::GetContactCameraFocus(int mContactIterator)
{
    Transform mTransform = (*mDrawNano)[0]->GetTransform();
    glm::vec3 center = mContacts->GetContactCenter(mContactIterator);
    glm::vec3 focus = vec3(vec4(center, 1.0) * mTransform.LocalToWorldMatrix());

    return focus;
}

glm::vec3 Forest::GetSuperblockCameraFocus(unsigned int super)
{
    if(CheckSuperBlocks(super, super+1))
    {
        glm::vec3 center = mSuperBlocks[super]->GetSuperblockCenter();
        Transform mTransform = (*mDrawNano)[0]->GetTransform();
        glm::vec3 camera = glm::vec3(center[0], center[1], center[2]);
        glm::vec3 focus = glm::vec3(vec4(camera, 1.0) * mTransform.LocalToWorldMatrix());
        return focus;
    }
    return glm::vec3(0.0);
}

double Forest::GetRadius(int cnt)
{
    if(0 <= cnt && cnt < (int)mDrawNano->size())
    {
        return (*mDrawNano)[cnt]->Radius();
    }
    return 0.0;
}

void Forest::ContactLookUp(DrawableSpheres *mIntersectionSpheres)
{
    if(mContacts && mDrawNano->size() > 0)
    {
        mContacts->ContactLookUp(mIntersectionSpheres);
    }
}

void Forest::SetSuperBlocks()
{
    for(DrawableNanotube *dn : (*mDrawNano))
    {
        dn->ClearOverlapPoints();
    }
    if(mSuperBlocks.size() == 0)
    {
        int superIndex = 0;
        for(unsigned int cpid = 0; cpid < mContacts->GetTotalControlPoints(); cpid++)
        {
            mContacts->SetAnchor(cpid, false);
            if(mContacts->GetContactsSize(cpid) == 0) continue;
            if(mContacts->WasAddedToBlock(cpid)) continue;

            SuperBlock *super = new SuperBlock(mContacts, mDrawNano, superIndex, mGraphCriticalDistance);
            super->SetSuperblock(cpid);
            //super->SetOverlapPoints();
            mSuperBlocks.push_back(super);
            superIndex++;
        }
    }
}

void Forest::ClearSuperblocks()
{
    for(DrawableNanotube *dn : (*mDrawNano))
    {
        dn->ClearOverlapPoints();
    }
    for(SuperBlock *super : mSuperBlocks)
    {
        super->ClearSuperblock();
    }
    mSuperBlocks.clear();
    for(unsigned int cpid = 0; cpid < mContacts->GetTotalControlPoints(); cpid++)
    {
        mContacts->SetAnchor(cpid, false);
        mContacts->SetAddedToBlock(cpid, false);
    }
}

bool Forest::SetSuperBlocksGraphs(unsigned int start, unsigned int end)
{
    if(CheckSuperBlocks(start, end) == false) return false;
    for(unsigned int s = start; s < end; s++)
    {
        std::cout<<s<<"/"<<end-1<<":  SetSuperBlocksGraphs ----------- "<<std::endl;
        mSuperBlocks[s]->ConfigureGraph(mAttractorType, mAnchorType, mGraphType, mColoringHeuristic,
                                        mColorOrder, mColoringChoice, mGraphOrdination, mOrderSolution);
        mSuperBlocks[s]->SetSuperblockGraph(mAttractorSpheres, mAnchorSpheres, mControlPointSpheres);
    }
    return true;
}

bool Forest::SetSuperBlocksGraphsColors(unsigned int start, unsigned int end)
{
    //std::cout<<"SetSuperBlocksGraphs"<<std::endl;
    if(CheckSuperBlocks(start, end) == false) return false;
    for(unsigned int s = start; s < end; s++)
    {
        mSuperBlocks[s]->SetSuperblockGraphColor();
    }
    return true;
}

bool Forest::CheckSuperBlocks(unsigned int start, unsigned int end)
{
    if(mSuperBlocks.size() == 0)
    {
        std::cout<<"No superblocks. Aborting."<<std::endl;
        return false;
    }
    if(start < 0 || start > mSuperBlocks.size())
    {
        std::cout<<"Start index illegal. Aborting. start: "<<start<<"  mSuperBlocks: "<<mSuperBlocks.size()<<std::endl;
        return false;
    }
    if(end < 0 || end > mSuperBlocks.size())
    {
        std::cout<<"End index illegal. Aborting. end: "<<end<<"  mSuperBlocks: "<<mSuperBlocks.size()<<std::endl;
        return false;
    }
    if(start >= end)
    {
        std::cout<<"Start index after end index. Aborting. start: "<<start<<"  end: "<<end<<std::endl;
        return false;
    }
    return true;
}

void Forest::AddEdgeOnSuperblock(unsigned int s_iterator)
{
    if(CheckSuperBlocks(s_iterator, s_iterator+1))
    {
        mSuperBlocks[s_iterator]->AddEdge();
    }
}

void Forest::RemoveEdgeOnSuperblock(unsigned int s_iterator)
{
    if(CheckSuperBlocks(s_iterator, s_iterator+1))
    {
        mSuperBlocks[s_iterator]->RemoveEdge();
    }
}

void Forest::ClearSuperblockGraph(unsigned int s_iterator)
{
    if(CheckSuperBlocks(s_iterator, s_iterator+1))
    {
        unsigned int anchorUpdate = mSuperBlocks[s_iterator]->ClearSuperblockGraph();
        if(anchorUpdate > 0)
        {
            for(unsigned int i = s_iterator+1; i < mSuperBlocks.size(); i++)
            {
                mSuperBlocks[i]->UpdateAttractorSphereIndex();
                mSuperBlocks[i]->UpdateAnchorSphereIndex(anchorUpdate);
            }
        }
    }
}

void Forest::ResetSuperblockGraph(unsigned int s_iterator)
{
    if(CheckSuperBlocks(s_iterator, s_iterator+1))
    {
        unsigned int anchorUpdate = mSuperBlocks[s_iterator]->ResetSuperblockGraph();
        if(anchorUpdate != 0)
        {
            for(int i = s_iterator+1; i < (int)mSuperBlocks.size(); i++)
            {
                mSuperBlocks[i]->UpdateAnchorSphereIndex(anchorUpdate);
            }
        }
    }
}

int Forest::GetSuperblockContacts(unsigned int s_iterator)
{
    if(CheckSuperBlocks(s_iterator, s_iterator+1))
    {
        return mSuperBlocks[s_iterator]->SuperblockContactLookUp();
    }
    return -1;
}

int Forest::GetBlocksSize(unsigned int s_iterator)
{
    if(CheckSuperBlocks(s_iterator, s_iterator+1))
    {
        return mSuperBlocks[s_iterator]->GetBlocksSize();
    }
    return -1;
}

unsigned int Forest::GetGraphSize(unsigned int s_iterator)
{
    if(CheckSuperBlocks(s_iterator, s_iterator+1))
    {
        return mSuperBlocks[s_iterator]->GetGraphSize();
    }
    return 0;
}

unsigned int Forest::GetGraphEdges(unsigned int s_iterator)
{
    if(CheckSuperBlocks(s_iterator, s_iterator+1))
    {
        return mSuperBlocks[s_iterator]->GetGraphEdges();
    }
    return 0;
}
unsigned int Forest::GetGraphMaxColor(unsigned int s_iterator)
{
    if(CheckSuperBlocks(s_iterator, s_iterator+1))
    {
        return mSuperBlocks[s_iterator]->GetGraphMaxColor();
    }
    return 0;
}
int Forest::GetGraphColorPermutationIndex(unsigned int s_iterator)
{
    if(CheckSuperBlocks(s_iterator, s_iterator+1))
    {
        return mSuperBlocks[s_iterator]->GetGraphColorPermutationIndex();
    }
    return -1;
}
int Forest::GetGraphColorTotalPermutation(unsigned int s_iterator)
{
    if(CheckSuperBlocks(s_iterator, s_iterator+1))
    {
        return mSuperBlocks[s_iterator]->GetGraphColorTotalPermutation();
    }
    return -1;
}
double Forest::GetOrderMatrixConditioning(unsigned int s_iterator, unsigned int component)
{
    if(CheckSuperBlocks(s_iterator, s_iterator+1))
    {
        return mSuperBlocks[s_iterator]->GetOrderMatrixConditioning(component);
    }
    return -1;
}
int Forest::GetTotalComponents(unsigned int s_iterator)
{
    if(CheckSuperBlocks(s_iterator, s_iterator+1))
    {
        return mSuperBlocks[s_iterator]->GetTotalComponents();
    }
    return -1;
}
std::vector<glm::vec4> Forest::GetContactsSize(unsigned int s_iterator)
{
    if(CheckSuperBlocks(s_iterator, s_iterator+1))
    {
        return mSuperBlocks[s_iterator]->GetContactsSize();
    }
    std::vector<glm::vec4> empty_vec;
    return empty_vec;
}

void Forest::DisplayGraphInfo(unsigned int s_iterator)
{
    if(CheckSuperBlocks(s_iterator, s_iterator+1))
    {
        mSuperBlocks[s_iterator]->DisplayGraphInfo();
    }
}

bool Forest::IsSuperblockGraphComputed(unsigned int start, unsigned int end)
{
    //std::cout<<"IsSuperblockGraphComputed"<<std::endl;
    if(CheckSuperBlocks(start, end) == false) return false;
    for(unsigned int s = start; s < end; s++)
    {
        if(!mSuperBlocks[s]->IsGraphComputed())
            return false;
    }
    return true;

}

void Forest::SolveForest(unsigned int start, unsigned int end)
{
    bool verbose = false;
    if(CheckSuperBlocks(start, end) == false) return;
    for(unsigned int s = start; s < end; s++)
    {
        std::cout<<s<<"/"<<end-1<<":  SolveSuperBlock ----------- "<<std::endl;
        mSuperBlocks[s]->SolveSuperBlock();
        if(verbose)
            std::cout<<s<<":  Displ. sum:  "<<mSuperBlocks[s]->GetAllDisplacements()<<"\n";
    }

    ///SaveSolvedForest(filename);
}

void Forest::SaveSolvedForest(std::string filename)
{
    std::ofstream outputFile(filename, outputFile.app);

    for(unsigned int i = 0; i < mDrawNano->size(); i++)
    {
        outputFile<<"p\n"<<i<<"\n"<<segmentsPerCNT-3<<"\n";
        for(int j = 1; j < segmentsPerCNT-1; j++)
        {
            Vertex pos = (*mDrawNano)[i]->mInterpolator->ControlPoints()[j];
            outputFile<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<"\n";
        }
    }
    outputFile.close();

    for(SuperBlock *super : mSuperBlocks)
    {
        super->SaveSuperblock(filename);
    }
}

std::vector<DrawableNanotube*>
    Forest::LoadSolvedForest(std::string mFilePathAttributes,
                     std::string filePathControlPoints,
                     Renderer* visualizer,
                     OrbitCamera* mCamera,
                     NanotubeMaterial *mSolidMaterial)
{
    mDrawNano = new std::vector<DrawableNanotube*>;
    mFilePathControlPoints = filePathControlPoints;
    /// Lendo atributos do CNTs (raio)
    std::ifstream inputFileAtt(mFilePathAttributes);
    std::vector<double> mRadiusOutData; // salvando valores antes de criar o DrawableNanotube

    /*while(!inputFileAtt.eof())
    {
        std::string buffer = "";
        std::getline(inputFileAtt, buffer);
        std::stringstream ss(buffer);
        double diameter;
        ss >> diameter;
        std::cout<<diameter<<std::endl;
        int nada;std::cin>>nada;
        mRadiusOutData.push_back(diameter/2.0);
    }

    inputFileAtt.close();*/

    std::string buffer = "";
    std::getline(inputFileAtt, buffer);
    std::stringstream ss(buffer);
    ss >> seed;
    for(int i = 0; i < 14; i++)
    {
        std::getline(inputFileAtt, buffer);
    }

    while(!inputFileAtt.eof())
    {
        std::string buffer = "";
        std::getline(inputFileAtt, buffer);
        if(buffer[0] == '#') continue;
        std::getline(inputFileAtt, buffer); //diamOut
        std::stringstream ss(buffer);
        double diameter;
        ss >> diameter;
        mRadiusOutData.push_back(diameter/2.0);
        for(int i = 0; i < 7; i++)
        {
            std::getline(inputFileAtt, buffer);
            ///std::cout<<buffer<<std::endl;
        }
    }
    inputFileAtt.close();

    /// Lendo posição dos pontos dos CNTs
    std::ifstream inputFile(mFilePathControlPoints);

    int cnt_counter = 0;
    int line = 0;
    std::string buffer2 = "";
    std::getline(inputFile, buffer2); line++;
    while(!inputFile.eof())
    {
        std::string buffer = "";
        std::getline(inputFile, buffer); line++;

        if(buffer[0] == 's') break;

        if(buffer[0] == 'p')
        {
            // Create a new catmull-rom interpolator
            CatmullRom *interp = new CatmullRom(PrecumputedPoints);

            buffer = "";
            std::getline(inputFile, buffer); line++;
            std::getline(inputFile, buffer); line++;
            std::stringstream ss(buffer);

            int seg;
            ss >> seg;
            ss.clear();

            for(int i = 0; i < seg+1; i++)
            {
                buffer = "";
                std::getline(inputFile, buffer); line++;
                ss.str(buffer);
                double x, y, z;
                ss >> x >> y >> z;
                // Push the first
                if(i == 0)
                {
                    interp->PushControlPoint(x, y-20, z);
                }
                interp->PushControlPoint(x, y, z);
                mPointsRead.push_back(glm::vec3(x, y, z));
                if(i == seg) interp->InterpolateLastPoint();
                ss.clear();
            }

            DrawableNanotube *dNanotube = new DrawableNanotube(*visualizer,
                *mCamera, interp, mSolidMaterial, mRadiusOutData[cnt_counter]);
            dNanotube->Initialize();
            (*mDrawNano).push_back(dNanotube);
            cnt_counter++;
        }
        //break;
    }
    inputFile.close();
    mRadiusOutData.clear();
    segmentsPerCNT = (*mDrawNano)[0]->mInterpolator->ControlPointsNumber();
    mContacts = new Contact(mDrawNano, mFilePathControlPoints);

    SetControlPointSpheres();

    int cont = 0;
    bool end_of_file = false;
    do
    {
        SuperBlock *super = new SuperBlock(mContacts, mDrawNano, cont, mGraphCriticalDistance);
        end_of_file = super->LoadSuperblock(filePathControlPoints, line, mAttractorSpheres, mAnchorSpheres, mControlPointSpheres);
        mSuperBlocks.push_back(super);
        cont++;
        //if(cont == 2) break;

    } while(end_of_file == false);

    mSuperBlocks.pop_back();

    return (*mDrawNano);
}

void Forest::ComparePoints()
{
    for(int i = 0; i < mDrawNano->size(); i++)
    {
        std::vector<Vertex> positions = mDrawNano->at(i)->mInterpolator->ControlPoints();
        for(int j = 0; j < segmentsPerCNT-2; j++)
        {
            int index = i*mDrawNano->size()+j;
            if(index >= mPointsRead.size()) break;

            glm::vec3 pos1 = mPointsRead.at(index);
            glm::vec3 pos2 = glm::vec3(positions.at(j+1).x, positions.at(j+1).y, positions.at(j+1).z);
            pos1 = glm::abs(pos1-pos2);
            if(pos1.x > 1e-6 || pos1.y > 1e-6 || pos1.z > 1e-6)
            {
                std::cout<<"ERROR "<<i<<"  "<<j<<std::endl;
                std::cout<<"pos1 "<<pos1.x<<" "<<pos1.y<<" "<<pos1.z<<std::endl;
                std::cout<<"pos2 "<<pos2.x<<" "<<pos2.y<<" "<<pos2.z<<std::endl;
                int nada; std::cin>>nada;
            }
        }
    }
}

void Forest::SetControlPointSpheres()
{
    for(unsigned int i = 0; i < (*mDrawNano).size(); i++)
    {
        DrawableNanotube* dCNT = (*mDrawNano)[i];
        int totalPoints = dCNT->mInterpolator->ControlPoints().size();
        for(int j = 1; j < totalPoints-1; j++)
        {
            Vertex pos = dCNT->mInterpolator->ControlPoints()[j];
            mControlPointSpheres->PushSphere(vec3(pos.x, pos.y, pos.z), vec3(1.0), 1.5);
        }
    }
}

void Forest::SetVisualization(SuperBlock::VISUALIZATION vis)
{
    if(mSuperBlocks.size() == 0)
    {
        std::cout<<"No superblocks"<<std::endl;
        return;
    }

    for(DrawableNanotube *dn : (*mDrawNano))
    {
        dn->ClearOverlapPoints();
    }

    for(SuperBlock *super : mSuperBlocks)
    {
        super->SetOverlapPoints(vis);
    }
}

void Forest::DrawSuperblocksGraphs(bool mDrawAttractors)
{
    if(mSuperBlocks.size() == 0) return;

    for(SuperBlock *super : mSuperBlocks)
    {
        if(super->IsGraphComputed())
            super->DrawGraph(mDrawAttractors);
    }
}

void Forest::DrawContacts()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    for(unsigned int i = 0; i < mContacts->GetTotalContacts(); i++)
    {
        glBegin(GL_LINE_STRIP);
        Vertex cont1 = mContacts->GetContact1(i);
        Vertex cont2 = mContacts->GetContact2(i);
        glVertex3f(cont1.x, cont1.y, cont1.z);
        glVertex3f(cont2.x, cont2.y, cont2.z);
        glEnd();
    }

}

unsigned int Forest::GetControlPointID(int cnt, int ind)
{
    return cnt * segmentsPerCNT + ind -1;
}

int Forest::GetCNT(unsigned int id)
{
    return (id+1)/segmentsPerCNT;
}

int Forest::GetIndex(unsigned int id)
{
    return (id+1)%segmentsPerCNT;
}

}

