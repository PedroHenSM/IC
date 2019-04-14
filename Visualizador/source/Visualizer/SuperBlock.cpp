#include "SuperBlock.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cstring>


namespace Library
{
SuperBlock::SuperBlock(Contact *c,
                       std::vector<DrawableNanotube*> *nano,
                       int superIndex,
                       double graphCriticalDistance) :
     contacts(c),
     mDrawNano(nano),
     segmentsPerCNT(0),
     mGraph(NULL),
     mGraphCriticalDistance(graphCriticalDistance),
     mSuperblockIndex(superIndex)
{
    //ctor
    if(contacts != NULL)
        segmentsPerCNT = contacts->GetSegmentsPerCNT();

    ConfigureGraph(Graph::MIDPOINT, Graph::SUPERBLOCK, Graph::ULTRA_CONNECTED,
                   Graph::FIRST_FIT, Graph::BEST, Graph::CLOSEST_CNT_INDEX,
                   Graph::CNT_HIGHEST_CONNECTION, Graph::DIRECT);
}

void SuperBlock::ConfigureGraph(Graph::ATTRACTOR att, Graph::ANCHOR anc, Graph::GRAPH_TYPE g_type,
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

SuperBlock::~SuperBlock()
{
    //dtor
    mBlocks.clear();
    mAdditionalCpids.clear();
    //graph->~Graph()
}

void SuperBlock::SetSuperblock(unsigned int cpid)
{
    bool verbose = false;
    if(verbose) std::cout<<"SetSuperblock"<<std::endl;

    mAllCpids.clear();
    mAdditionalCpids.clear();

    mAllCpids.push_back(cpid);
    FillVector(mAllCpids, cpid);
    sort(mAllCpids.begin(), mAllCpids.end());

    if(verbose)
    {
        std::cout<<"mAllCpids"<<std::endl;
        for(unsigned int i = 0; i < mAllCpids.size(); i++)
        {
            std::cout<<GetCNT(mAllCpids[i])<<"."<<GetIndex(mAllCpids[i])<<"\t";
        }
        std::cout<<std::endl;
        std::cout<<"Blocks"<<std::endl;
    }
    /// Adicionando blocos do superbloco
    for(unsigned int i = 0 ; i < mAllCpids.size(); i++)
    {
        if(contacts->GetContactsSize(mAllCpids[i]) == 0) continue;
        if(contacts->WasAddedToBlock(mAllCpids[i])) continue;

        Block *block = new Block(contacts);
        block->SetBlock(mAllCpids[i]);
        mBlocks.push_back(block);
    }
    if(verbose) std::cout<<std::endl;
    /// salvando os cpids adicionais
    for(unsigned int i = 0 ; i < mAllCpids.size(); i++)
    {
        for(Block *block : mBlocks)
        {
            unsigned int j = 0;
            for(; j < block->GetContentSize(); j++)
            {
                if(block->GetContentControlPointID(j) == mAllCpids[i])
                {
                    break;
                }
            }
            if(j >= block->GetContentSize())
            {
                if(!contains(mAdditionalCpids, mAllCpids[i]))
                    mAdditionalCpids.push_back(mAllCpids[i]);
            }
        }

    }
    if(verbose)
    {
        std::cout<<"mAdditionalCpids"<<std::endl;
        for(unsigned int j = 0 ; j < mAdditionalCpids.size(); j++)
        {
            int add_cpid = mAdditionalCpids[j];
            std::cout<<GetCNT(add_cpid)<<"."<<GetIndex(add_cpid)<<"\t";
        }
        std::cout<<std::endl;
    }

    for(unsigned int cpid : mAllCpids)
    {
        int cont_size = contacts->GetContactsSize(cpid);
        for(int j = 0; j < cont_size; j++)
        {
            glm::vec4 elem(0.0);
            glm::uvec4 contact = contacts->GetControlPointContact(cpid, j);

            unsigned int k = 0;
            for( ;k < mSegmentsInContact.size(); k++)
            {
                if(mSegmentsInContact[k].x == GetControlPointID(contact.z, contact.w))
                    break;
            }
            if(k < mSegmentsInContact.size()) continue;

            Vertex pos1   = (*mDrawNano)[contact.x]->mInterpolator->ControlPoints()[contact.y];
            Vertex pos1_1 = (*mDrawNano)[contact.x]->mInterpolator->ControlPoints()[contact.y-1];
            Vertex pos2   = (*mDrawNano)[contact.z]->mInterpolator->ControlPoints()[contact.w];
            Vertex pos2_1 = (*mDrawNano)[contact.z]->mInterpolator->ControlPoints()[contact.w-1];
            Vertex pt1, pt2;
            double dist = contacts->DistFromSegments(pos2, pos1, pos2_1, pos1_1, pt1, pt2);

            elem.x = cpid;
            elem.y = GetControlPointID(contact.z, contact.w);
            elem.z = dist;
            elem.w = 0.0;

            mSegmentsInContact.push_back(elem);
        }
    }
}

void SuperBlock::ClearSuperblock()
{
    for(Block *block : mBlocks)
        block->ClearBlock();
    mBlocks.clear();
    mAdditionalCpids.clear();
    mAllCpids.clear();
    ClearSuperblockGraph();
}

unsigned int SuperBlock::ClearSuperblockGraph()
{
    unsigned int anchorUpdate = 0;
    if(mGraph)
    {
        anchorUpdate = mGraph->ClearGraph();
    }
    mGraph = NULL;
    return anchorUpdate;
}
void SuperBlock::UpdateAttractorSphereIndex()
{
    if(mGraph)
    {
        mGraph->UpdateAttractorSphereIndex();
    }
}
void SuperBlock::UpdateAnchorSphereIndex(unsigned int anchorUpdate)
{
    if(mGraph)
    {
        mGraph->UpdateAnchorSphereIndex(anchorUpdate);
    }
}
unsigned int SuperBlock::ResetSuperblockGraph()
{
    if(mGraph)
        return mGraph->ResetGraph();

    return 0;
}
void SuperBlock::DisplayGraphInfo()
{
    if(mGraph)
        mGraph->DisplayGraphInfo();
}

void SuperBlock::SetSuperblockGraph(DrawableSpheres *attractor, DrawableSpheres *anchor, DrawableSpheres *mControlPointSpheres)
{
    //std::cout<<"SetSuperblockGraph"<<std::endl;
    if(!mGraph)
    {
        mGraph = new Graph(contacts, mDrawNano, &mAllCpids, attractor, anchor, mControlPointSpheres);
        mGraph->ConfigureGraph(mGraphCriticalDistance ,mAttractorType, mAnchorType, mGraphType, mColoringHeuristic,
                               mColorOrder, mColoringChoice, mGraphOrdination, mOrderSolution);
    }
    if(!mGraph->IsGraphSolved()) // para quando carregamos a floresta resolvida
    {
        mGraph->SetGraph();
    }
    if(mGraph->GetAdjacencyListSize() == 0)
    {
        ClearSuperblockGraph();
    }
}

void SuperBlock::SetSuperblockGraphColor()
{
    //std::cout<<"SetSuperblockGraph"<<std::endl;
    if(!mGraph)
    {
        std::cout<<"No graph"<<std::endl;
        return;
    }
    mGraph->SetControlPointColor();
}

void SuperBlock::SolveSuperBlock()
{
    if(IsGraphComputed() == false)
    {
        std::cout<<"No graph on superblock"<<std::endl;
        return;
    }
    mGraph->SolveGraph();

    for(unsigned int i = 0; i < mSegmentsInContact.size(); i++)
    {
        int cnt1 = GetCNT(mSegmentsInContact[i].x);
        int ind1 = GetIndex(mSegmentsInContact[i].x);
        int cnt2 = GetCNT(mSegmentsInContact[i].y);
        int ind2 = GetIndex(mSegmentsInContact[i].y);
        Vertex pos1   = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints()[ind1];
        Vertex pos1_1 = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints()[ind1-1];
        Vertex pos2   = (*mDrawNano)[cnt2]->mInterpolator->ControlPoints()[ind2];
        Vertex pos2_1 = (*mDrawNano)[cnt2]->mInterpolator->ControlPoints()[ind2-1];
        Vertex pt1, pt2;
        double dist = contacts->DistFromSegments(pos2, pos1, pos2_1, pos1_1, pt1, pt2);
        mSegmentsInContact[i].w = dist;
    }
}

void SuperBlock::DrawGraph(bool mDrawAttractors)
{
    if(!IsGraphComputed())
    {
        ///std::cout<<"No graph computed to draw"<<std::endl;
        return;
    }
    mGraph->DrawGraph(mDrawAttractors);
}

void SuperBlock::FillVector(std::vector<unsigned int>&vec, unsigned int id)
{
    for(int i = 0; i < contacts->GetContactsSize(id); i++)
    {
        glm::uvec4 contact_ind = contacts->GetControlPointContact(id, i);
        int id0 = GetControlPointID(contact_ind.x, contact_ind.y);
        int id1 = GetControlPointID(contact_ind.z, contact_ind.w);

        if(!contains(vec, id0))
        {
            vec.push_back(id0);
            FillVector(vec, id0);
        }
        if(!contains(vec, id1))
        {
            vec.push_back(id1);
            FillVector(vec, id1);
        }

        /// JOGANDO PONTOS ADJACENTES NA LISTA
        if(!contains(vec, id0+1))
        {
            vec.push_back(id0+1);
            FillVector(vec, id0+1);
        }
        if(!contains(vec, id0-1))
        {
            vec.push_back(id0-1);
            FillVector(vec, id0-1);
        }
        if(!contains(vec, id1+1))
        {
            vec.push_back(id1+1);
            FillVector(vec, id1+1);
        }
        if(!contains(vec, id1-1))
        {
            vec.push_back(id1-1);
            FillVector(vec, id1-1);
        }

    }
}

void SuperBlock::SetOverlapPoints(VISUALIZATION vis)
{
    switch(vis)
    {
        case BLOCK :
        {
            for(Block *block : mBlocks)
            {
                for(unsigned int i = 0; i < block->GetContentSize(); i++)
                {
                    unsigned int cpid = block->GetContentControlPointID(i);
                    int cnt = GetCNT(cpid);
                    int ind = GetIndex(cpid);
                    (*mDrawNano)[cnt]->NeedUpdate(true);
                    (*mDrawNano)[cnt]->AddOverlapPoint(ind, block->GetColor());
                }
            }
        }
        break;
        case SUPERBLOCK :
        {
            for(Block *block : mBlocks)
            {
                // pintando as pontos que não fazem contato mas que fazem parte do superbloco
                for(unsigned int i = 0; i < GetAddCpidSize(); i++)
                {
                    unsigned int cnt = GetCNT(GetAddCpid(i));
                    unsigned int ind = GetIndex(GetAddCpid(i));
                    (*mDrawNano)[cnt]->NeedUpdate(true);
                    (*mDrawNano)[cnt]->AddOverlapPoint(ind, GetColor());
                }
                for(unsigned int i = 0; i < block->GetContentSize(); i++)
                {
                    unsigned int cpid = block->GetContentControlPointID(i);
                    int cnt = GetCNT(cpid);
                    int ind = GetIndex(cpid);
                    (*mDrawNano)[cnt]->NeedUpdate(true);
                    (*mDrawNano)[cnt]->AddOverlapPoint(ind, block->GetColor());
                }
            }
        }
        break;
        case CONTACTS :
        {
            for(unsigned int cpid = 0; cpid < contacts->GetTotalControlPoints(); cpid++)
            {
                if(contacts->GetContactsSize(cpid) > 0)
                {
                    int cnt = GetCNT(cpid);
                    int ind = GetIndex(cpid);
                    /// por default a cor eh vermelho
                    (*mDrawNano)[cnt]->AddOverlapPoint(ind);
                }
            }
        }
        break;
        default : break;
    }

}

bool SuperBlock::contains(const std::vector<unsigned int>&a, const unsigned int b)
{
    for(unsigned int i : a)
    {
        if(i == b) return true;
    }
    return false;
}

Block* SuperBlock::GetBlock(int i)
{
    if(i >= 0 && i < (int)mBlocks.size())
        return mBlocks[i];
    return NULL;
}

glm::vec3 SuperBlock::GetSuperblockCenter()
{
    glm::vec3 center(0.0);
    for(unsigned int cpid : mAllCpids)
    {
        int cnt = GetCNT(cpid);
        int ind = GetIndex(cpid);
        Vertex pos = (*mDrawNano)[cnt]->mInterpolator->ControlPoints()[ind];
        center.x += pos.x;
        center.y += pos.y;
    }
    center.x = center.x/mAllCpids.size();
    center.y = center.y/mAllCpids.size();
    center.z = 0.0;
    return center;
}

int SuperBlock::GetAddCpid(int i)
{
    if(i >= 0 && i < (int)mAdditionalCpids.size())
    {
        return mAdditionalCpids[i];
    }
    return -1;
}

glm::vec3 SuperBlock::GetColor()
{
    glm::vec3 color(0.0);
    if(mBlocks.size() > 0)
    {
        return mBlocks[0]->GetColor();
    }
    return color;
}

void SuperBlock::AddEdge()
{
    if(IsGraphComputed())
    {
        int cnt1, ind1, cnt2, ind2;
        for(unsigned int i = 0; i < mGraph->GetAdjacencyListSize(); i++)
        {
            unsigned int cpid = mGraph->GetVertexContent(i)[0];
            std::cout<<GetCNT(cpid)<<"."<<GetIndex(cpid)<<"\t";
        }
        std::cout<<std::endl;
        std::cout<<"Type cnt1 ind1 cnt2 ind2 to add edge"<<std::endl;
        std::cin>>cnt1>>ind1>>cnt2>>ind2;
        /*cnt1 = 5;
        ind1 = 23;
        cnt2 = 6;
        ind2 = 23;*/
        mGraph->AddNewEdge(GetControlPointID(cnt1, ind1),GetControlPointID(cnt2, ind2));
    }
    else
    {
        std::cout<<"Superblock's Graph not computed. Press G"<<std::endl;
    }
}

void SuperBlock::RemoveEdge()
{
    if(IsGraphComputed())
    {
        int cnt1, ind1, cnt2, ind2;
        for(unsigned int i = 0; i < mGraph->GetAdjacencyListSize(); i++)
        {
            unsigned int cpid = mGraph->GetVertexContent(i)[0];
            std::cout<<GetCNT(cpid)<<"."<<GetIndex(cpid)<<"\t";
        }
        std::cout<<std::endl;
        std::cout<<"Type cnt1 ind1 cnt2 ind2 to remove edge"<<std::endl;
        std::cin>>cnt1>>ind1>>cnt2>>ind2;
        mGraph->RemoveEdge(GetControlPointID(cnt1, ind1),GetControlPointID(cnt2, ind2));
    }
    else
    {
        std::cout<<"Superblock's Graph not computed. Press G"<<std::endl;
    }
}

double SuperBlock::GetAllDisplacements()
{
    if(IsGraphComputed())
    {
        return mGraph->GetAllDisplacements();
    }
    return 0.0;
}

unsigned int SuperBlock::GetControlPointColor(int i)
{
    if(IsGraphComputed())
    {
        return mGraph->GetControlPointColor(i);
    }
    return 0;
}
glm::vec2 SuperBlock::GetGraphNode(int vert, int neighbour)
{
    if(IsGraphComputed())
    {
        return mGraph->GetGraphCPID(vert, neighbour);
    }
    return glm::vec2(-1.0, -1.0);
}

int SuperBlock::GetGraphType()
{
    if(IsGraphComputed())
    {
        return mGraph->GetGraphType();
    }
    return -1;
}
int SuperBlock::GraphAttractors()
{
    if(IsGraphComputed())
    {
        return mGraph->GraphAttractors();
    }
    return -1;
}
int SuperBlock::GraphAnchors()
{
    if(IsGraphComputed())
    {
        return mGraph->GraphAnchors();
    }
    return -1;
}
int SuperBlock::GraphColorOrder()
{
    if(IsGraphComputed())
    {
        return mGraph->GraphColorOrder();
    }
    return -1;
}
int SuperBlock::GraphListOrder()
{
    if(IsGraphComputed())
    {
        return mGraph->GraphListOrder();
    }
    return -1;
}
int SuperBlock::GraphHeuristic()
{
    if(IsGraphComputed())
    {
        return mGraph->GraphHeuristic();
    }
    return -1;
}
int SuperBlock::GraphColorChoice()
{
    if(IsGraphComputed())
    {
        return mGraph->GraphColorChoice();
    }
    return -1;
}
int SuperBlock::GraphSolution()
{
    if(IsGraphComputed())
    {
        return mGraph->GraphSolution();
    }
    return -1;
}
unsigned int SuperBlock::GetGraphSize()
{
    if(IsGraphComputed())
    {
        return mGraph->GetAdjacencyListSize();
    }
    return 0;
}
unsigned int SuperBlock::GetGraphEdges()
{
    if(IsGraphComputed())
    {
        return mGraph->GetGraphEdges();
    }
    return 0;
}
unsigned int SuperBlock::GetGraphMaxColor()
{
    if(IsGraphComputed())
    {
        return mGraph->GetGraphMaxColor();
    }
    return 0;
}
int SuperBlock::GetGraphColorPermutationIndex()
{
    if(IsGraphComputed())
    {
        return mGraph->GetGraphColorPermutationIndex();
    }
    return 0;
}
int SuperBlock::GetGraphColorTotalPermutation()
{
    if(IsGraphComputed())
    {
        return mGraph->GetGraphColorTotalPermutation();
    }
    return 0;
}
double SuperBlock::GetOrderMatrixConditioning(unsigned int component)
{
    if(IsGraphComputed())
    {
        return mGraph->GetOrderMatrixConditioning(component);
    }
    return 0;
}
int SuperBlock::GetTotalComponents()
{
    if(IsGraphComputed())
    {
        return mGraph->GetTotalComponents();
    }
    return 0;
}
unsigned int SuperBlock::GetGraphNeighbourSize(int vert)
{
    if(IsGraphComputed())
    {
        return mGraph->GetVertexNeighbourSize(vert);
    }
    return 0;
}

int SuperBlock::SuperblockContactLookUp()
{
    int cont = 0;
    for(unsigned int i = 0; i < mAllCpids.size()-1; i++)
    {
        int cnt1 = GetCNT(mAllCpids[i]);
        int ind1 = GetIndex(mAllCpids[i]);
        Vertex pos1   = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints()[ind1];
        Vertex pos1_1 = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints()[ind1-1];
        if(ind1 == segmentsPerCNT-1) continue;

        for(unsigned int j = i; j < mAllCpids.size(); j++)
        {
            int cnt2 = GetCNT(mAllCpids[j]);
            if(cnt1 == cnt2) continue;

            int ind2 = GetIndex(mAllCpids[j]);
            if(ind2 == segmentsPerCNT-1) continue;

            Vertex pos2   = (*mDrawNano)[cnt2]->mInterpolator->ControlPoints()[ind2];
            Vertex pos2_1 = (*mDrawNano)[cnt2]->mInterpolator->ControlPoints()[ind2-1];
            Vertex pt1, pt2;
            double dist = contacts->DistFromSegments(pos2, pos1, pos2_1, pos1_1, pt1, pt2);
            dist = dist - (*mDrawNano)[cnt1]->Radius() - (*mDrawNano)[cnt2]->Radius();

            double mContactDistance = contacts->GetContactDistance();
            if(FEQUAL(dist - mContactDistance, 0.0) == 1 || dist <= mContactDistance)
            {
                cont++;
                //std::cout<<cnt1<<"."<<ind1<<"-"<<cnt2<<"."<<ind2<<"\t\t";
                /*std::cout<<cnt1<<"."<<ind1<<"-"<<cnt2<<"."<<ind2<<"\t";
                std::cout<<"contato!";
                std::cout<<std::endl;*/
            }
        }
    }
    return cont;
}

void SuperBlock::SaveSuperblock(std::string mFilePath)
{
    std::ofstream outputFile(mFilePath, outputFile.app);
    outputFile<<"s\t"<<mSuperblockIndex<<"\n";
    for(unsigned int add : mAdditionalCpids)
    {
        outputFile<<add<<" ";
    }
    outputFile<<"\n";
    for(unsigned int all : mAllCpids)
    {
        outputFile<<all<<" ";
    }
    outputFile<<"\n";
    outputFile.close();

    for(Block *b : mBlocks)
    {
        b->SaveBlock(mFilePath);
    }

    if(IsGraphComputed())
        mGraph->SaveGraph(mFilePath);
}

bool SuperBlock::LoadSuperblock(std::string mFilePath, int &line, DrawableSpheres *attractor, DrawableSpheres *anchor, DrawableSpheres *mControlPointSpheres)
{
    std::ifstream inputFile(mFilePath);
    bool verbose = false;
    if(verbose) std::cout<<"LoadSuperblock inicio  "<<line<<std::endl;
    for (int i = 0; i < line; i++)
    {
        std::string buffer = "";
        std::getline(inputFile, buffer);
    }

    while(!inputFile.eof())
    {
        std::string buffer = "";
        std::getline(inputFile, buffer);
        line++;
        if(verbose) std::cout<<line<<":  "<<buffer<<std::endl;
        //int nada; std::cin>>nada;
        if(buffer[0] == 's') continue;

        if(buffer[0] == 'b') break;

        std::vector<unsigned int> vec;

        char *token = strtok((char*) buffer.c_str()," ");
        while (token != NULL)
        {
            std::stringstream ss(token);

            unsigned int cpid;
            ss >> cpid;
            ss.clear();

            vec.push_back(cpid);

            token = strtok(NULL," ");
        }

        if(mAdditionalCpids.size() == 0)
        {
            mAdditionalCpids = vec;
        }
        else
        {
            mAllCpids = vec;
        }
        vec.clear();
    }
    if(verbose)
    {
        std::cout<<"mAdditionalCpids"<<std::endl;
        for(unsigned int c : mAdditionalCpids) std::cout<<c<<" ";
        std::cout<<std::endl;
        std::cout<<"mAllCpids"<<std::endl;
        for(unsigned int c : mAllCpids) std::cout<<c<<" ";
        std::cout<<std::endl;
    }

    inputFile.close();
    ///int nada; std::cin>>nada;

    bool end_of_blocks = false;
    bool end_of_file = false;
    do
    {
        Block *block = new Block(contacts);
        end_of_file = block->LoadBlock(mFilePath, line, end_of_blocks);
        mBlocks.push_back(block);
        ///int nada; std::cin>>nada;
        if(end_of_blocks) break;

    } while(end_of_file == false);

    if(end_of_file == false && end_of_blocks == true)
    {
        if(!IsGraphComputed())
        {
            mGraph = new Graph(contacts, mDrawNano, &mAllCpids, attractor, anchor, mControlPointSpheres);
        }
        end_of_file = mGraph->LoadGraph(mFilePath, line);
        ///int nada; std::cin>>nada;
    }

    if(verbose)
    {
        if(end_of_file) std::cout<<"Super eof true "<<std::endl;
        else    std::cout<<"Super eof false"<<std::endl;
    }

    return end_of_file;
}

unsigned int SuperBlock::GetControlPointID(int cnt, int ind)
{
    return cnt * segmentsPerCNT + ind -1;
}

int SuperBlock::GetCNT(unsigned int id)
{
    return (id+1)/segmentsPerCNT;
}

int SuperBlock::GetIndex(unsigned int id)
{
    return (id+1)%segmentsPerCNT;
}


}
