#include "Graph.h"
#include "LinearSolver.h"
#include "Laplacian.h"
#include "VisualizerCommon.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


namespace Library
{
Graph::Graph(Contact *c,
             std::vector<DrawableNanotube*> *nano,
             std::vector<unsigned int> *SuperCpids,
             DrawableSpheres *attractor,
             DrawableSpheres *anchor,
             DrawableSpheres *controlPointSpheres) :
    mContacts(c), mDrawNano(nano),
    mAllCpids(SuperCpids),
    mAttractorSpheres(attractor),
    mAnchorSpheres(anchor), mControlPointSpheres(controlPointSpheres),
    mAddAnchors(false),
    mConsiderAnchors(false),
    mNeedGraphUpdate(false),
    mPushAway(true),
    mAttractorZ(100.0),
    mAttractorSphereIndex(0),
    mAnchorSphereIndex(0),
    mAttractorType(MIDPOINT),
    mAnchorType(SUPERBLOCK),
    mGraphType(ULTRA_CONNECTED),
    mColoringHeuristic(FIRST_FIT),
    mColorOrder(BEST),
    mColoringChoice(CLOSEST_CNT_INDEX),
    mGraphOrdination(CNT_HIGHEST_CONNECTION),
    mOrderSolution(DIRECT),
    mTotalCnts(0),
    mControlPointDisplacement(NULL)
{
    //ctor
    sort((*mAllCpids).begin(), (*mAllCpids).end());

    segmentsPerCNT = 0;
    if(mContacts != NULL)
        segmentsPerCNT = mContacts->GetSegmentsPerCNT();
    //std::cout<<"Graph segmentsPerCNT "<<segmentsPerCNT<<std::endl;

    mAttractorColor.x = 0.0;
    mAttractorColor.y = 122.0/256.0;
    mAttractorColor.z = 77.0/256.0;

    mAnchorColor.x = 151.0/256.0;
    mAnchorColor.y = 189.0/256.0;
    mAnchorColor.z = 61.0/256.0;

    mGraphColor.x = 1.0;
    mGraphColor.y = 1.0;
    mGraphColor.z = 0.0f;
}

Graph::~Graph()
{
    //dtor
    FreeAdjacencyList(&mAdjacencyList);
}

void Graph::ConfigureGraph(double mGraphCriticalDistance, ATTRACTOR att, ANCHOR anc, GRAPH_TYPE g_type, HEURISTIC heu,
                           COLOR_ORDER c_order, COLOR_CHOICE c_choice, GRAPH_ORDER g_order,
                           SOLUTION sol)
{
    mCriticalDistance = mGraphCriticalDistance;
    mAttractorType = att;
    mAnchorType = anc;
    mGraphType = g_type;
    mColoringHeuristic = heu;
    mColorOrder = c_order;
    mColoringChoice = c_choice;
    mGraphOrdination = g_order;
    mOrderSolution = sol;
}

void Graph::SetGraph()
{
    std::cout<<"SetGraph"<<std::endl;
    FreeAdjacencyList(&mAdjacencyList);
    //mCriticalDistance = mContacts->GetCriticalDistance();

    /// adicionando pontos
    for(unsigned int i = 0; i < (*mAllCpids).size(); i++)
    {
        if(GetIndex((*mAllCpids)[i]) == segmentsPerCNT-1) continue;
        std::vector<glm::vec2> node;
        node.push_back(glm::vec2((*mAllCpids)[i],0.0) );
        mAdjacencyList.push_back(node);
    }

    switch(mGraphType)
    {
        case CONTACTS : // antigo grafo 100
        {
            //std::cout<<"CONTACTS"<<std::endl;
            for(std::vector<glm::vec2> node : mAdjacencyList)
            {
                int cpid1 = node[0][0];
                for(int i = 0; i < mContacts->GetContactsSize(cpid1); i++)
                {
                    glm::uvec4 contact = mContacts->GetControlPointContact(cpid1, i);

                    bool insert_pos1   = false;
                    bool insert_pos1_1 = false;
                    bool insert_pos2   = false;
                    bool insert_pos2_1 = false;

                    int cnt1 = contact.x;
                    int ind1 = contact.y;
                    int cnt2 = contact.z;
                    int ind2 = contact.w;

                    unsigned int cpid2 = GetControlPointID(cnt2, ind2);

                    double ratio1, ratio2;
                    mContacts->GetContactRatio(cnt1, ind1, cnt2, ind2, ratio1, ratio2);

                    if(FEQUAL(ratio1, 1.0) || !FEQUAL(ratio1, 0.0) )
                    {
                        insert_pos1 = true;
                    }
                    if(FEQUAL(ratio1, 0.0) || !FEQUAL(ratio1, 1.0) )
                    {
                        insert_pos1_1 = true;
                    }
                    if(FEQUAL(ratio2, 1.0) || !FEQUAL(ratio2, 0.0) )
                    {
                        insert_pos2 = true;
                    }
                    if(FEQUAL(ratio2, 0.0) || !FEQUAL(ratio2, 1.0) )
                    {
                        insert_pos2_1 = true;
                    }


                    if(insert_pos1 && insert_pos2_1)
                    {
                        AddEdge(cpid1, cpid2-1);
                    }
                    if(insert_pos1 && insert_pos2)
                    {
                        AddEdge(cpid1, cpid2);
                    }
                    if(insert_pos1_1 && insert_pos2_1 && FEQUAL(ratio1, 0.0) && FEQUAL(ratio2, 0.0) )
                    {
                        AddEdge(cpid1-1, cpid2-1);
                    }
                    if(insert_pos1_1 && insert_pos2)
                    {
                        AddEdge(cpid1-1, cpid2);
                    }

                }
            }
        }
        break;
        case SIMPLE_CONNECTED : // antigo 101
        {
            for(std::vector<glm::vec2> node : mAdjacencyList)
            {
                int cpid1 = node[0][0];
                for(int i = 0; i < mContacts->GetContactsSize(cpid1); i++)
                {
                    glm::uvec4 contact = mContacts->GetControlPointContact(cpid1, i);

                    int cnt1 = contact.x;
                    int ind1 = contact.y;
                    int cnt2 = contact.z;
                    int ind2 = contact.w;

                    unsigned int cpid2 = GetControlPointID(cnt2, ind2);

                    double ratio1, ratio2;
                    mContacts->GetContactRatio(cnt1, ind1, cnt2, ind2, ratio1, ratio2);

                    bool insert_pos1   = false;
                    bool insert_pos1_1 = false;
                    bool insert_pos2   = false;
                    bool insert_pos2_1 = false;

                    if(FEQUAL(ratio1, 1.0) || !FEQUAL(ratio1, 0.0) )
                    {
                        insert_pos1 = true;
                    }
                    if(FEQUAL(ratio1, 0.0) || !FEQUAL(ratio1, 1.0) )
                    {
                        insert_pos1_1 = true;
                    }
                    if(FEQUAL(ratio2, 1.0) || !FEQUAL(ratio2, 0.0) )
                    {
                        insert_pos2 = true;
                    }
                    if(FEQUAL(ratio2, 0.0) || !FEQUAL(ratio2, 1.0) )
                    {
                        insert_pos2_1 = true;
                    }


                    if(insert_pos1 && insert_pos2_1)
                    {
                        AddEdge(cpid1, cpid2-1);
                    }
                    if(insert_pos1 && insert_pos2)
                    {
                        AddEdge(cpid1, cpid2);
                    }
                    //if(insert_pos1_1 && insert_pos2_1 ) std::cout<<"***insert_pos1_1 && insert_pos2_1  "<<cnt1<<"."<<ind1-1<<"-"<<cnt2<<"."<<ind2-1<<std::endl;

                    if(insert_pos1_1 && insert_pos2_1 && FEQUAL(ratio1, 0.0) && FEQUAL(ratio2, 0.0) )
                    {
                        AddEdge(cpid1-1, cpid2-1);
                    }
                    if(insert_pos1_1 && insert_pos2)
                    {
                        AddEdge(cpid1-1, cpid2);
                    }
                    /**
                    pos1 - pos2
                          /
                    pos1_1
                    */
                    if(insert_pos1 && insert_pos1_1 && insert_pos2)
                    {
                        if(mConsiderAnchors)
                        {
                            if(mContacts->IsAnchor(cpid2-1) == false) AddEdge(cpid1-1, cpid2-1);
                            if(mContacts->IsAnchor(cpid2+1) == false) AddEdge(cpid1  , cpid2+1);
                        }
                        else
                        {
                            AddEdge(cpid1-1, cpid2-1);
                            AddEdge(cpid1  , cpid2+1);
                        }
                    }
                    /**
                    pos1 - pos2
                         \
                           pos2_1
                    */
                    if(insert_pos2 && insert_pos2_1 && insert_pos1)
                    {
                        if(mConsiderAnchors)
                        {
                            if(mContacts->IsAnchor(cpid1-1) == false) AddEdge(cpid1-1, cpid2-1);
                            if(mContacts->IsAnchor(cpid1+1) == false) AddEdge(cpid1+1, cpid2);
                        }
                        else
                        {
                            AddEdge(cpid1-1, cpid2-1);
                            AddEdge(cpid1+1, cpid2);
                        }
                    }
                    /// pos1 - pos2
                    if(insert_pos2 && !insert_pos2_1 && insert_pos1 && !insert_pos1_1)
                    {
                        if(mConsiderAnchors)
                        {
                            if(mContacts->IsAnchor(cpid1-1) == false) AddEdge(cpid1-1, cpid2);
                            if(mContacts->IsAnchor(cpid1+1) == false) AddEdge(cpid1+1, cpid2);
                            if(mContacts->IsAnchor(cpid2-1) == false) AddEdge(cpid2-1, cpid1);
                            if(mContacts->IsAnchor(cpid2+1) == false) AddEdge(cpid2+1, cpid1);
                        }
                        else
                        {
                            AddEdge(cpid1-1, cpid2);
                            AddEdge(cpid1+1, cpid2);
                            AddEdge(cpid2-1, cpid1);
                            AddEdge(cpid2+1, cpid1);
                        }
                    }
                    /**
                    pos1
                        \
                        pos2_1
                    */
                    if(!insert_pos2 && insert_pos2_1 && insert_pos1 && !insert_pos1_1)
                    {
                        if(mConsiderAnchors)
                        {
                            if(mContacts->IsAnchor(cpid1-1) == false) AddEdge(cpid1-1, cpid2-1);
                            if(mContacts->IsAnchor(cpid1+1) == false) AddEdge(cpid1+1, cpid2-1);
                            if(mContacts->IsAnchor(cpid2-2) == false) AddEdge(cpid2-2, cpid1);
                            if(mContacts->IsAnchor(cpid2  ) == false) AddEdge(cpid2  , cpid1);
                        }
                        else
                        {
                            AddEdge(cpid1-1, cpid2-1);
                            AddEdge(cpid1+1, cpid2-1);
                            AddEdge(cpid2-2, cpid1);
                            AddEdge(cpid2  , cpid1);
                        }
                    }
                    /**
                             pos2
                           /
                     pos1_1
                    */
                    if(insert_pos2 && !insert_pos2_1 && !insert_pos1 && insert_pos1_1)
                    {
                        if(mConsiderAnchors)
                        {
                            if(mContacts->IsAnchor(cpid2-1) == false) AddEdge(cpid2-1, cpid1-1);
                            if(mContacts->IsAnchor(cpid2+1) == false) AddEdge(cpid1-1, cpid2+1);
                            if(mContacts->IsAnchor(cpid1-2) == false) AddEdge(cpid1-2, cpid2);
                            if(mContacts->IsAnchor(cpid1  ) == false) AddEdge(cpid2  , cpid1);
                        }
                        else
                        {
                            AddEdge(cpid2-1, cpid1-1);
                            AddEdge(cpid1-1, cpid2+1);
                            AddEdge(cpid1-2, cpid2);
                            AddEdge(cpid2  , cpid1);
                        }
                    }
                    /// pos1_1 - pos2_1
                    if(!insert_pos2 && insert_pos2_1 && !insert_pos1 && insert_pos1_1)
                    {
                        if(mConsiderAnchors)
                        {
                            if(mContacts->IsAnchor(cpid2  ) == false) AddEdge(cpid2  , cpid1-1);
                            if(mContacts->IsAnchor(cpid2-2) == false) AddEdge(cpid2-2, cpid1-1);
                            if(mContacts->IsAnchor(cpid1  ) == false) AddEdge(cpid2-1, cpid1);
                            if(mContacts->IsAnchor(cpid1-2) == false) AddEdge(cpid2-1, cpid1-2);
                        }
                        else
                        {
                            AddEdge(cpid2  , cpid1-1);
                            AddEdge(cpid2-2, cpid1-1);
                            AddEdge(cpid2-1, cpid1);
                            AddEdge(cpid2-1, cpid1-2);
                        }
                    }

                }
            }
        }
        break;
        case CONNECTED : // antigo 103
        {
            for(std::vector<glm::vec2> node : mAdjacencyList)
            {
                int cpid1 = node[0][0];
                for(int i = 0; i < mContacts->GetContactsSize(cpid1); i++)
                {
                    glm::uvec4 contact = mContacts->GetControlPointContact(cpid1, i);

                    int cnt1 = contact.x;
                    int ind1 = contact.y;
                    int cnt2 = contact.z;
                    int ind2 = contact.w;

                    unsigned int cpid2 = GetControlPointID(cnt2, ind2);

                    double ratio1, ratio2;
                    mContacts->GetContactRatio(cnt1, ind1, cnt2, ind2, ratio1, ratio2);

                    if(FEQUAL(ratio1, 1.0) && !FEQUAL(ratio2, 0.0) && !FEQUAL(ratio2, 1.0) )
                    {
                        AddEdge(cpid1  , cpid2);
                        AddEdge(cpid1  , cpid2-1);
                        AddEdge(cpid1-1, cpid2-1);
                        AddEdge(cpid1+1, cpid2);
                    }
                    if(FEQUAL(ratio1, 0.0) && !FEQUAL(ratio2, 0.0) && !FEQUAL(ratio2, 1.0) )
                    {
                        AddEdge(cpid1-1, cpid2);
                        AddEdge(cpid1-1, cpid2-1);
                        AddEdge(cpid1-2, cpid2-1);
                        AddEdge(cpid1  , cpid2);
                    }
                    if(FEQUAL(ratio2, 1.0) && !FEQUAL(ratio1, 0.0) && !FEQUAL(ratio1, 1.0) )
                    {
                        AddEdge(cpid2  , cpid1);
                        AddEdge(cpid2  , cpid1-1);
                        AddEdge(cpid2-1, cpid1-1);
                        AddEdge(cpid2+1, cpid1);
                    }
                    if(FEQUAL(ratio2, 0.0) && !FEQUAL(ratio1, 0.0) && !FEQUAL(ratio1, 1.0) )
                    {
                        AddEdge(cpid2-1, cpid1);
                        AddEdge(cpid2-1, cpid1-1);
                        AddEdge(cpid2-2, cpid1-1);
                        AddEdge(cpid2  , cpid1);
                    }

                    /// INTERSECAO
                    if(!FEQUAL(ratio1, 0.0) && !FEQUAL(ratio1, 1.0) && !FEQUAL(ratio2, 0.0) && !FEQUAL(ratio2, 1.0) )
                    {
                        AddEdge(cpid1  , cpid2  );
                        AddEdge(cpid1  , cpid2-1);
                        AddEdge(cpid1-1, cpid2  );
                        AddEdge(cpid1-1, cpid2-1);
                    }

                }
            }
        }
        break;
        case ULTRA_CONNECTED: // antigo 102
        {
            for(std::vector<glm::vec2> node : mAdjacencyList)
            {
                int cpid1 = node[0][0];
                for(int i = 0; i < mContacts->GetContactsSize(cpid1); i++)
                {
                    glm::uvec4 contact = mContacts->GetControlPointContact(cpid1, i);

                    int cnt1 = contact.x;
                    int ind1 = contact.y;
                    int cnt2 = contact.z;
                    int ind2 = contact.w;

                    unsigned int cpid2 = GetControlPointID(cnt2, ind2);

                    double ratio1, ratio2;
                    mContacts->GetContactRatio(cnt1, ind1, cnt2, ind2, ratio1, ratio2);

                    if(FEQUAL(ratio1, 1.0) && !FEQUAL(ratio2, 0.0) && !FEQUAL(ratio2, 1.0) )
                    {
                        AddEdge(cpid1  , cpid2);
                        AddEdge(cpid1  , cpid2-1);
                        AddEdge(cpid1-1, cpid2-1);
                        AddEdge(cpid1+1, cpid2);
                    }
                    if(FEQUAL(ratio1, 0.0) && !FEQUAL(ratio2, 0.0) && !FEQUAL(ratio2, 1.0) )
                    {
                        AddEdge(cpid1-1, cpid2);
                        AddEdge(cpid1-1, cpid2-1);
                        AddEdge(cpid1-2, cpid2-1);
                        AddEdge(cpid1  , cpid2);
                    }
                    if(FEQUAL(ratio2, 1.0) && !FEQUAL(ratio1, 0.0) && !FEQUAL(ratio1, 1.0) )
                    {
                        AddEdge(cpid2  , cpid1);
                        AddEdge(cpid2  , cpid1-1);
                        AddEdge(cpid2-1, cpid1-1);
                        AddEdge(cpid2+1, cpid1);
                    }
                    if(FEQUAL(ratio2, 0.0) && !FEQUAL(ratio1, 0.0) && !FEQUAL(ratio1, 1.0) )
                    {
                        AddEdge(cpid2-1, cpid1);
                        AddEdge(cpid2-1, cpid1-1);
                        AddEdge(cpid2-2, cpid1-1);
                        AddEdge(cpid2  , cpid1);
                    }


                    if(FEQUAL(ratio1, 1.0) && FEQUAL(ratio2, 0.0) )
                    {
                        AddEdge(cpid1  , cpid2-1);
                        AddEdge(cpid1  , cpid2-2);
                        AddEdge(cpid1  , cpid2);
                        AddEdge(cpid2-1, cpid1-1);
                        AddEdge(cpid2-1, cpid1+1);
                    }
                    if(FEQUAL(ratio1, 0.0) && FEQUAL(ratio2, 1.0) )
                    {
                        AddEdge(cpid2  , cpid1-1);
                        AddEdge(cpid2  , cpid1-2);
                        AddEdge(cpid2  , cpid1);
                        AddEdge(cpid1-1, cpid2-1);
                        AddEdge(cpid1-1, cpid2+1);
                    }

                    if(FEQUAL(ratio1, 1.0) && FEQUAL(ratio2, 1.0) )
                    {
                        AddEdge(cpid1  , cpid2);
                        AddEdge(cpid1  , cpid2-1);
                        AddEdge(cpid1  , cpid2+1);
                        AddEdge(cpid2  , cpid1-1);
                        AddEdge(cpid2  , cpid1+1);
                    }
                    if(FEQUAL(ratio1, 0.0) && FEQUAL(ratio2, 0.0) )
                    {
                        AddEdge(cpid1-1, cpid2-1);
                        AddEdge(cpid1-1, cpid2-2);
                        AddEdge(cpid1-1, cpid2);
                        AddEdge(cpid2-1, cpid1);
                        AddEdge(cpid2-1, cpid1-2);
                    }

                    /// INTERSECAO
                    if(!FEQUAL(ratio1, 0.0) && !FEQUAL(ratio1, 1.0) && !FEQUAL(ratio2, 0.0) && !FEQUAL(ratio2, 1.0) )
                    {
                        AddEdge(cpid1  , cpid2  );
                        AddEdge(cpid1  , cpid2-1);
                        AddEdge(cpid1-1, cpid2  );
                        AddEdge(cpid1-1, cpid2-1);
                    }

                }
            }
        }
        break;
        case CONTACT_TO_POINT :
        {
            for(std::vector<glm::vec2> node : mAdjacencyList)
            {
                int cpid1 = node[0][0];
                for(int i = 0; i < mContacts->GetContactsSize(cpid1); i++)
                {
                    glm::uvec4 contact = mContacts->GetControlPointContact(cpid1, i);

                    int cnt1 = contact.x;
                    int ind1 = contact.y;
                    int cnt2 = contact.z;
                    int ind2 = contact.w;

                    unsigned int cpid2 = GetControlPointID(cnt2, ind2);

                    double ratio1, ratio2;
                    mContacts->GetContactRatio(cnt1, ind1, cnt2, ind2, ratio1, ratio2);
                    // 24 contatos
                    AddEdge(cpid1  , cpid2);
                    /* 30 contatos
                    if(FEQUAL(ratio2, 1.0) && !FEQUAL(ratio1, 0.0) && !FEQUAL(ratio1, 1.0))
                    {
                        AddEdge(cpid1-1, cpid2);
                    }
                    if(FEQUAL(ratio1, 1.0) && !FEQUAL(ratio2, 0.0) && !FEQUAL(ratio2, 1.0))
                    {
                        AddEdge(cpid1  , cpid2-1);
                    }*/
                    // 2 contatos no superbloco 12
                    AddEdge(cpid1-1, cpid2);
                    AddEdge(cpid1  , cpid2-1);
                    /* 5 contatos
                    AddEdge(cpid1-1, cpid2);
                    AddEdge(cpid1+1, cpid2);
                    AddEdge(cpid1  , cpid2-1);
                    AddEdge(cpid1  , cpid2+1);*/
                }
            }
        }
        break;
        default :
        {
            std::cout<<"No graph type selected"<<std::endl;
            return;
        }
        break;
    }

    RemoveIsolatedVertices();

    if(mAdjacencyList[0].size() == 1)
    {
        std::cout<<"No graph. Recompute contacts"<<std::endl;
        FreeAdjacencyList(&mAdjacencyList);
        return;
    }

    GraphOrdination();
    SetAttractors();
    SetAnchors();
    /// Adicionando atratores ao grafo
    for(unsigned int i = 0; i < mAttractors.size(); i++)
    {
        std::vector<glm::vec2> node;
        node.push_back(glm::vec2(mContacts->GetTotalControlPoints()+i,0.0));
        mAdjacencyList.push_back(node);
    }
    for(unsigned int i = 0; i < mAdjacencyList.size()-mAttractors.size(); i++)
    {
        for(unsigned int j = 0; j < mAttractors.size(); j++)
        {
            AddEdge(mAdjacencyList[i][0][0], mContacts->GetTotalControlPoints()+j);
        }
    }

    // contando quantos CNTs estão envolvidos
    int cnt = -1;
    mTotalCnts = 0;
    for(std::vector<glm::vec2> node : mAdjacencyList)
    {
        if((unsigned int)GetCNT(node[0][0]) >= (*mDrawNano).size())
            break;
        if(cnt < GetCNT(node[0][0]))
        {
            cnt = GetCNT(node[0][0]);
            mTotalCnts++;
        }
    }

    SetWeights();
    SetControlPointColor();

    ///PrintGraph(&mAdjacencyList);
}

unsigned int Graph::ClearGraph()
{
    if(!mPushAway)
    {
        SolveGraph();
    }
    ResetControlPointColors();
    for(unsigned int i = mAttractorSphereIndex; i < mAttractorSphereIndex+2; i++)
    {
        //std::cout<<"i  "<<i<<std::endl;
        mAttractorSpheres->DeleteSphereAt(mAttractorSphereIndex);
    }
    //std::cout<<"mAttractorSpheres  "<<mAttractorSpheres->GetTotalSpheres()<<std::endl;
    for(unsigned int i = 0; i < mAnchors.size(); i++)
    {
        //std::cout<<"i  "<<i<<std::endl;
        mContacts->SetAnchor(mAnchors[i], false);
        mAnchorSpheres->DeleteSphereAt(mAnchorSphereIndex);
        //std::cout<<"mTotalSpheres "<<mAnchorSpheres->GetTotalSpheres()<<std::endl;
    }
    //std::cout<<"mAnchorSpheres  "<<mAnchorSpheres->GetTotalSpheres()<<std::endl;
    unsigned int result = mAnchors.size();

    FreeAdjacencyList(&mAdjacencyList);
    //std::cout<<"ClearGraph  "<<mAdjacencyList.size()<<std::endl;
    //int nada;std::cin>>nada;
    mAttractors.clear();
    mAnchors.clear();
    mGraphColoring.clear();
    if(mControlPointDisplacement)
    {
        gsl_vector_free(mControlPointDisplacement);
        mControlPointDisplacement = NULL;
    }

    return result;
}

void Graph::UpdateAttractorSphereIndex()
{
    mAttractorSphereIndex -= 2;
    bool verbose = false;
    if(verbose)
    {
        std::cout<<"new mAttractorSphereIndex  "<<mAttractorSphereIndex<<std::endl;
    }
}

void Graph::UpdateAnchorSphereIndex(unsigned int anchorUpdate)
{
    mAnchorSphereIndex -= anchorUpdate;
    bool verbose = false;
    if(verbose)
    {
        std::cout<<"anchorUpdate               "<<anchorUpdate<<std::endl;
        std::cout<<"new mAnchorSphereIndex     "<<mAnchorSphereIndex<<std::endl;
    }
}

void Graph::GraphOrdination()
{
    std::cout<<"GraphOrdination"<<std::endl;
    bool verbose = false;
    switch(mGraphOrdination)
    {
        case INCREASE :
        {
            sort(mAdjacencyList.begin(), mAdjacencyList.end(), list_by_cpid);
            for(unsigned int i = 0; i < mAdjacencyList.size(); i++)
            {
                sort(mAdjacencyList[i].begin()+1, mAdjacencyList[i].end(), node_by_cpid);
            }
        }
        break;
        case UP_DOWN :
        {
            sort(mAdjacencyList.begin(), mAdjacencyList.end(), list_by_cpid);
            for(unsigned int i = 0; i < mAdjacencyList.size(); i++)
            {
                sort(mAdjacencyList[i].begin()+1, mAdjacencyList[i].end(), node_by_cpid);
            }
            int cnt = -1;
            int start = 0;
            int end = 0;
            bool increase = true;
            for(unsigned int i = 0; i < mAdjacencyList.size(); i++)
            {
                if(verbose)
                {
                    std::cout<<GetCNT(mAdjacencyList[i][0][0])<<"."<<GetIndex(mAdjacencyList[i][0][0])<<std::endl;
                    std::cout<<"start "<<start<<" end "<<end<<std::endl;
                }
                if(cnt != GetCNT(mAdjacencyList[i][0][0]))
                {
                    cnt = GetCNT(mAdjacencyList[i][0][0]);
                    if(verbose) std::cout<<"cnt !=  "<<std::endl;
                    if(end != 0)
                    {
                        if(!increase)
                        {
                            sort(mAdjacencyList.begin()+start, mAdjacencyList.begin()+end+1, list_by_cpid_descent);
                        }
                        increase = !increase;
                    }
                    start = i;
                    end = i;
                }
                else
                {
                    end++;
                }
            }

            int nada; std::cin>>nada;
        }
        break;
        case CNT_HIGHEST_CONNECTION :
        {
            sort(mAdjacencyList.begin(), mAdjacencyList.end(), list_by_cpid);
            for(unsigned int i = 0; i < mAdjacencyList.size(); i++)
            {
                sort(mAdjacencyList[i].begin()+1, mAdjacencyList[i].end(), node_by_cpid);
            }
            SetWeightsAsVertexDegree();
            /// contando quem é o CNT com mais conexoes
            std::vector<glm::vec4> cnt_connections;
            int cnt = GetCNT(mAdjacencyList[0][0][0]);
            int start = 0;
            int end = -1;
            int connections = 0;
            for(unsigned int i = 0; i < mAdjacencyList.size(); i++)
            {
                if(cnt != GetCNT(mAdjacencyList[i][0][0]))
                {
                    cnt_connections.push_back(glm::vec4(cnt, connections, start, end));

                    cnt = GetCNT(mAdjacencyList[i][0][0]);
                    connections = mAdjacencyList[i].size()-mAttractors.size()-1;

                    start = i;
                    end = i;
                }
                else
                {
                    end++;
                    connections += mAdjacencyList[i].size()-mAttractors.size()-1;
                }
            }
            cnt_connections.push_back(glm::vec4(GetCNT(mAdjacencyList[mAdjacencyList.size()-1][0][0]), connections, start, end));
            sort(cnt_connections.begin(), cnt_connections.end(), cnt_by_connection);
            if(verbose)
            {
                for(glm::vec4 cntc : cnt_connections)
                {
                    std::cout<<cntc[0]<<":   "<<cntc[1]<<" ["<<cntc[2]<<", "<<cntc[3]<<"]"<<std::endl;
                }
            }

            /// ordenar de acordo com essa lista
            std::vector<std::vector<glm::vec2>> adj_list;
            int gap = 0;
            for(unsigned int k = 0; k < cnt_connections.size(); k++)
            {
                for(unsigned int i = 0; i < mAdjacencyList.size(); i++)
                {
                    if(GetCNT(mAdjacencyList[i][0][0]) == cnt_connections[k][0])
                    {
                        std::vector<glm::vec2> node;
                        for(unsigned int j = 0; j < mAdjacencyList[i].size(); j++)
                        {
                            node.push_back(mAdjacencyList[i][j]);
                        }
                        sort(node.begin()+1, node.end()-mAttractors.size(), node_by_degree_descent);
                        adj_list.push_back(node);
                        node.clear();
                    }
                }
                if(k > 0)
                {
                    gap += cnt_connections[k-1][3]-cnt_connections[k-1][2]+1;
                }
                //sort(adj_list.begin()+gap, adj_list.end(), list_by_cpid_descent);
                sort(adj_list.begin()+gap, adj_list.end()-mAttractors.size(), list_by_degree_descent);
            }
            FreeAdjacencyList(&mAdjacencyList);
            mAdjacencyList = adj_list;
            FreeAdjacencyList(&adj_list);
            if(verbose) PrintAdjacencyList();
            ResetGraphWeights();
        }
        break;
    }
    //int nada; std::cin>>nada;
}

void Graph::SetWeightsAsVertexDegree()
{
    std::cout<<"SetWeightsAsVertexDegree"<<std::endl;
    for(unsigned int i = 0; i < mAdjacencyList.size(); i++)
    {
        for(unsigned int j = 1; j < mAdjacencyList[i].size(); j++)
        {
            int vert = SearchInList(mAdjacencyList[i][j][0], &mAdjacencyList);
            if(vert != -1)
            {
                mAdjacencyList[i][j][1] = mAdjacencyList[vert].size()-1;
            }
        }
    }
}

std::vector<unsigned int> Graph::SetColorOrder()
{
    std::cout<<"SetColorOrder"<<std::endl;
    std::vector<unsigned int> color_order;

    switch(mColorOrder)
    {
        case INITIAL :
        {
            mGraphColoring = GraphColoringGreedy();
            color_order = GetInitialColorOrder();
        }
        break;
        case BEST :
        {
            int total_contacts;
            mGraphColoring = GraphColoringGreedy();
            color_order = GetBestColorOrder(total_contacts);
        }
        break;
        case VERY_BEST :
        {
            color_order = SetMinimalColoringHeuristic();
        }
        break;
    }

    return color_order;
}

void Graph::SetWeights()
{
    std::cout<<"SetWeights"<<std::endl;
    //std::vector<unsigned int> color_order = SetColorOrder();
    mColorOrdination = SetColorOrder();
    bool verbose = false;
    if(verbose)
    {
        for(unsigned int i = 0; i < mAdjacencyList.size(); i++)
        {
            std::cout<<GetCNT(mAdjacencyList[i][0][0])<<"."<<GetIndex(mAdjacencyList[i][0][0])<<"\t";
        }
        std::cout<<std::endl;
        for(unsigned int i = 0; i < mGraphColoring.size(); i++)
        {
            std::cout<<mGraphColoring[i]<<"\t";
        }
        std::cout<<std::endl;
        std::cout<<"mColorOrdination"<<std::endl;
        for(unsigned int i = 0; i < mColorOrdination.size(); i++)
        {
            std::cout<<mColorOrdination[i]<<"\t";
        }
        std::cout<<std::endl;
    }

    int component = 0;
    std::vector<int> mComponentsInds;
    mComponentsInds = GetGraphComponents(component);

    for(int i = 1; i <= component; i++)
    {
        std::vector<std::vector<glm::vec2>> ConnectedComponent = GetConnectedComponent(i, &mComponentsInds);

        std::cout<<"ConnectedComponent:  "<<i<<std::endl;
        if(verbose)
        {
            PrintGraph(&ConnectedComponent);
        }
        double conditioning = 0.0;
        SetComponentWeights(&ConnectedComponent, &mColorOrdination, conditioning);
        mOrderMatrixConditioning.push_back(conditioning);

        FreeAdjacencyList(&ConnectedComponent);
    }
    mComponentsInds.clear();
    /// sum
    for(unsigned int j = 0; j < mAdjacencyList.size(); j++)
    {
        double sum = 0.0;
        for(unsigned int k = 1; k < mAdjacencyList[j].size(); k++)
        {
            sum += mAdjacencyList[j][k][1];
        }
        mAdjacencyList[j][0][1] = sum;
    }
    ///color_order.clear();
}

void Graph::SetControlPointColor()
{
    for(unsigned int i = 0; i < mAdjacencyList.size(); i++)
    {
        glm::vec3 color;
        switch(mGraphColoring[i])
        {
        case 1: // amarelo escuro
            color[0] = 1.0; color[1] = 204.0/256.0; color[2] = 0.0;
            break;
        case 2: // laranja
            color[0] = 153.0/256.0; color[1] = 51.0/256.0; color[2] = 0.0;
            break;
        case 3: // verde
            color[0] = 0; color[1] = 0.5; color[2] = 0;
            break;
        case 4: // azul claro
            color[0] = 0; color[1] = 204.0/256.0; color[2] = 1.0;
            break;
        case 5: // vermelho escuro
            color[0] = 0.5; color[1] = 0.0; color[2] = 0.0;
            break;
        case 6: // rosa
            color[0] = 153.0/256.0; color[1] = 51.0/256.0; color[2] = 102.0/256.0;
            break;
        case 7: // roxo
            color[0] = 51.0/256.0; color[1] = 51.0/256.0; color[2] = 153.0/256.0;
            break;
        default :
            color[0] = 1.0; color[1] = 1.0; color[2] = 1.0;
            break;
        }
        int cnt = GetCNT(mAdjacencyList[i][0][0]);
        mControlPointSpheres->UpdateSphereColor(mAdjacencyList[i][0][0]-2*cnt, color);
    }
}

void Graph::SetComponentWeights(std::vector<std::vector<glm::vec2>> *ConnectedComponent,
                                  std::vector<unsigned int> *color_order, double &conditioning)
{
    std::cout<<"SetComponentWeights"<<std::endl;
    gsl_vector *weights = GetComponentWeights(ConnectedComponent, color_order, conditioning);
    bool verbose = false;
    /// apenas para os atratores no final da lista principal
    for(unsigned int j = 0; j < mAdjacencyList.size()-mAttractors.size(); j++)
    {
        /// apenas para os atratores no final da lista de adjacentes de cada vertice
        for(unsigned int k = mAdjacencyList[j].size()-mAttractors.size(); k < mAdjacencyList[j].size(); k++)
        {
            /// mesmo tamanho que o vetor de weights
            for(unsigned int m = 0; m < ConnectedComponent->size(); m++)
            {
                if((*ConnectedComponent)[m][0][0] == mAdjacencyList[j][0][0])
                {
                    if(k == mAdjacencyList[j].size()-mAttractors.size()) /// primeiro atrator
                    {
                        mAdjacencyList[j][k][1] = gsl_vector_get(weights, m); /// peso para o atrator no final da lista de adjacentes de um vértice
                        int attInd = SearchInList(mAdjacencyList[j][k][0], &mAdjacencyList); /// atrator na lista principal
                        int nodeInd = SearchInNeighbours(attInd, mAdjacencyList[j][0][0],&mAdjacencyList); /// vertice principal na lista de adjacentes do atrator
                        mAdjacencyList[attInd][nodeInd][1] = gsl_vector_get(weights, m); /// peso para o adjacente do atrator

                        if(verbose)
                        {
                            std::cout<<"m "<<m<<" j "<<j<<" k "<<k<<"  "<<GetCNT(mAdjacencyList[j][k][0])<<"."<<GetIndex(mAdjacencyList[j][k][0])<<"\t";
                            std::cout<<attInd<<" "<<nodeInd<<"  "<<GetCNT(mAdjacencyList[attInd][nodeInd][0])<<"."<<GetIndex(mAdjacencyList[attInd][nodeInd][0])<<"\t";
                            std::cout<<"      weight  "<<gsl_vector_get(weights, m)<<std::endl;
                        }
                    }
                    else /// segundo atrator
                    {
                        mAdjacencyList[j][k][1] = 1.0 - gsl_vector_get(weights, m); /// peso para o atrator no final da lista de adjacentes de um vértice
                        int attInd = SearchInList(mAdjacencyList[j][k][0], &mAdjacencyList); /// atrator na lista principal
                        int nodeInd = SearchInNeighbours(attInd, mAdjacencyList[j][0][0],&mAdjacencyList); /// vertice principal na lista de adjacentes do atrator
                        mAdjacencyList[attInd][nodeInd][1] = 1.0 - gsl_vector_get(weights, m); /// peso para o adjacente do atrator

                        if(verbose)
                        {
                            std::cout<<"m "<<m<<" j "<<j<<" k "<<k<<"  "<<GetCNT(mAdjacencyList[j][k][0])<<"."<<GetIndex(mAdjacencyList[j][k][0])<<"\t";
                            std::cout<<attInd<<" "<<nodeInd<<"  "<<GetCNT(mAdjacencyList[attInd][nodeInd][0])<<"."<<GetIndex(mAdjacencyList[attInd][nodeInd][0])<<"\t";
                            std::cout<<"1.0 - weight  "<<1.0-gsl_vector_get(weights, m)<<std::endl;
                            std::cout<<std::endl;
                        }
                    }
                    break;
                }
            }
        }
    }
}

gsl_vector* Graph::GetComponentWeights(std::vector<std::vector<glm::vec2>> *ConnectedComponent,
                                  std::vector<unsigned int> *color_order, double &conditioning)
{
    std::cout<<"GetComponentWeights"<<std::endl;
    conditioning = -1.0;
    switch(mOrderSolution)
    {
        case ORIGINAL:
        case ORIGINAL_MAX:
        case ORIGINAL_MIN:
        case CRITICAL:
        case DIRECT:
        {
            gsl_vector *weights = gsl_vector_alloc(ConnectedComponent->size());
            gsl_vector_set_all(weights, 0.5);
            return weights;
        }
        break;
        case HYPOTENUSE:
        {
            bool original = true;

            if(original == false)
            {
                gsl_vector *weights = gsl_vector_alloc(ConnectedComponent->size());
                gsl_vector_set_all(weights, 0.5);
                double critical = 0.0;
                critical = mCriticalDistance;
                //critical = mContacts->GetCriticalDistance();

                int total_colors = color_order->size();

                for(unsigned int m = 0; m < ConnectedComponent->size(); m++)
                {
                    int vert = SearchInList((*ConnectedComponent)[m][0][0], &mAdjacencyList);
                    if(vert == -1) continue;
                    if(GetCNT((*ConnectedComponent)[m][0][0]) >= (int)mDrawNano->size()) continue;
                    double val = 0.0; /// deslocamento do ponto
                    switch(total_colors)
                    {
                        case 2:
                        {
                            if(mGraphColoring[vert] == (*color_order)[0])
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[0]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[1]);
                                val = result1[0]+result2[0]+1.2*EPSILON;
                                val += critical;
                                double cateto = GetMinDistanceBetweenColors((*color_order)[0],(*color_order)[1]);
                                val = sqrt(val*val - cateto*cateto);
                                val = -val/2.0;
                            }
                            else
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[1]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[0]);
                                val = result1[0]+result2[0]+1.2*EPSILON;
                                val += critical;
                                double cateto = GetMinDistanceBetweenColors((*color_order)[1],(*color_order)[0]);
                                val = sqrt(val*val - cateto*cateto);
                                val = val/2.0;
                            }
                        }
                        break;
                        case 3:
                        {
                            if(mGraphColoring[vert] == (*color_order)[0]) //if(mGraphColoring[i] == 1)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[0]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[1]);
                                val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                                double cateto  = GetMinDistanceBetweenColors((*color_order)[0],(*color_order)[1]);
                                val = sqrt(val*val - cateto*cateto);
                                val = -val;
                            }
                            if(mGraphColoring[vert] == (*color_order)[2])//if(mGraphColoring[i] == 3)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[2]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[1]);
                                val = result1[0]+result2[0]+critical+1.2*EPSILON;
                                double cateto  = GetMinDistanceBetweenColors((*color_order)[1], (*color_order)[2]);
                                val = sqrt(val*val - cateto*cateto);
                            }
                        }
                        break;
                        case 4:
                        {
                            if(mGraphColoring[vert] == (*color_order)[0]) //if(mGraphColoring[i] == 1)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[0]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[1]);
                                glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[2]);
                                val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                                double cateto = GetMinDistanceBetweenColors((*color_order)[0], (*color_order)[1]);
                                val = sqrt(val*val - cateto*cateto);
                                val = -val;

                                double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                                double cateto2 = GetMinDistanceBetweenColors((*color_order)[1], (*color_order)[2]);
                                val2 = sqrt(val2*val2 - cateto2*cateto2);
                                val2 = -val2/2.0;

                                val += val2;
                            }
                            if(mGraphColoring[vert] == (*color_order)[1])//if(mGraphColoring[i] == 2)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[1]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[2]);
                                val = (result1[0]+result2[0]+critical+EPSILON);
                                double cateto  = GetMinDistanceBetweenColors((*color_order)[1],(*color_order)[2]);
                                val = sqrt(val*val - cateto*cateto);
                                val = -val/2.0;
                            }
                            if(mGraphColoring[vert] == (*color_order)[2])//if(mGraphColoring[i] == 3)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[2]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[3]);
                                val = (result1[0]+result2[0]+critical+EPSILON);
                                double cateto  = GetMinDistanceBetweenColors((*color_order)[2], (*color_order)[1]);
                                val = sqrt(val*val - cateto*cateto);
                                val = val/2.0;
                            }
                            if(mGraphColoring[vert] == (*color_order)[3])//if(mGraphColoring[i] == 4)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[3]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[2]);
                                glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[1]);
                                val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                                double cateto  = GetMinDistanceBetweenColors((*color_order)[2], (*color_order)[3]);
                                val = sqrt(val*val - cateto*cateto);

                                double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                                double cateto2  = GetMinDistanceBetweenColors((*color_order)[2], (*color_order)[1]);
                                val2 = sqrt(val2*val2 - cateto2*cateto2);
                                val2 = val2/2.0;

                                val += val2;
                            }

                        }
                        break;
                        case 5:
                        {
                            if(mGraphColoring[vert] == (*color_order)[0]) //if(mGraphColoring[i] == 1)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[0]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[1]);
                                glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[2]);
                                val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                                double cateto  = GetMinDistanceBetweenColors((*color_order)[0], (*color_order)[1]);
                                val = sqrt(val*val - cateto*cateto);
                                val = -val;

                                double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                                double cateto2 = GetMinDistanceBetweenColors((*color_order)[1], (*color_order)[2]);
                                val2 = sqrt(val2*val2 - cateto2*cateto2);
                                val2 = -val2;

                                val += val2;
                            }
                            if(mGraphColoring[vert] == (*color_order)[1])//if(mGraphColoring[i] == 2)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[1]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[2]);
                                val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                                double cateto  = GetMinDistanceBetweenColors((*color_order)[2], (*color_order)[1]);
                                val = sqrt(val*val - cateto*cateto);
                                val = -val;
                            }
                            if(mGraphColoring[vert] == (*color_order)[3])//if(mGraphColoring[i] == 4)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[2]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[3]);
                                val = result1[0]+result2[0]+critical+1.2*EPSILON;
                                double cateto  = GetMinDistanceBetweenColors((*color_order)[2], (*color_order)[3]);
                                val = sqrt(val*val - cateto*cateto);
                            }
                            if(mGraphColoring[vert] == (*color_order)[4])// if(mGraphColoring[i] == 5)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[4]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[3]);
                                glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[2]);
                                val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                                double cateto  = GetMinDistanceBetweenColors((*color_order)[3], (*color_order)[4]);
                                val = sqrt(val*val - cateto*cateto);

                                double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                                double cateto2 = GetMinDistanceBetweenColors((*color_order)[3], (*color_order)[2]);
                                val2 = sqrt(val2*val2 - cateto2*cateto2);

                                val += val2;
                            }
                        }
                        break;
                        case 6:
                        {
                            if(mGraphColoring[vert] == (*color_order)[0]) //if(mGraphColoring[i] == 1)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[0]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[1]);
                                glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[2]);
                                glm::vec4 result4 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[3]);
                                val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                                double cateto = GetMinDistanceBetweenColors((*color_order)[0], (*color_order)[1]);
                                val = sqrt(val*val - cateto*cateto);
                                val = -val;

                                double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                                double cateto2 = GetMinDistanceBetweenColors((*color_order)[1], (*color_order)[2]);
                                val2 = sqrt(val2*val2 - cateto2*cateto2);
                                val2 = -val2;

                                double val3 = (result3[0]+result4[0]+critical+1.2*EPSILON);
                                double cateto3 = GetMinDistanceBetweenColors((*color_order)[2], (*color_order)[3]);
                                val3 = sqrt(val3*val3 - cateto3*cateto3);
                                val3 = -val3/2.0;

                                val += val2 + val3;
                            }
                            if(mGraphColoring[vert] == (*color_order)[1]) //if(mGraphColoring[i] == 2)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[1]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[2]);
                                glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[3]);

                                val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                                double cateto = GetMinDistanceBetweenColors((*color_order)[1], (*color_order)[2]);
                                val = sqrt(val*val - cateto*cateto);
                                val = -val;

                                double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                                double cateto2 = GetMinDistanceBetweenColors((*color_order)[2], (*color_order)[3]);
                                val2 = sqrt(val2*val2 - cateto2*cateto2);
                                val2 = -val2/2.0;

                                val += val2;
                            }
                            if(mGraphColoring[vert] == (*color_order)[2])//if(mGraphColoring[i] == 3)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[2]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[3]);
                                val = (result1[0]+result2[0]+critical+EPSILON);
                                double cateto  = GetMinDistanceBetweenColors((*color_order)[2],(*color_order)[3]);
                                val = sqrt(val*val - cateto*cateto);
                                val = -val/2.0;
                            }
                            if(mGraphColoring[vert] == (*color_order)[3])//if(mGraphColoring[i] == 4)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[3]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[4]);
                                val = (result1[0]+result2[0]+critical+EPSILON);
                                double cateto  = GetMinDistanceBetweenColors((*color_order)[2], (*color_order)[1]);
                                val = sqrt(val*val - cateto*cateto);
                                val = val/2.0;
                            }
                            if(mGraphColoring[vert] == (*color_order)[4])//if(mGraphColoring[i] == 5)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[4]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[3]);
                                glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[2]);
                                val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                                double cateto  = GetMinDistanceBetweenColors((*color_order)[3], (*color_order)[4]);
                                val = sqrt(val*val - cateto*cateto);

                                double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                                double cateto2  = GetMinDistanceBetweenColors((*color_order)[3], (*color_order)[2]);
                                val2 = sqrt(val2*val2 - cateto2*cateto2);
                                val2 = val2/2.0;

                                val += val2;
                            }
                            if(mGraphColoring[vert] == (*color_order)[5]) //if(mGraphColoring[i] == 6)
                            {
                                glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[5]);
                                glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[4]);
                                glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[3]);
                                glm::vec4 result4 = GetMinMaxRadiusByColor(&mAdjacencyList, (*color_order)[2]);
                                val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                                double cateto = GetMinDistanceBetweenColors((*color_order)[5], (*color_order)[4]);
                                val = sqrt(val*val - cateto*cateto);
                                val = -val;

                                double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                                double cateto2 = GetMinDistanceBetweenColors((*color_order)[4], (*color_order)[3]);
                                val2 = sqrt(val2*val2 - cateto2*cateto2);
                                val2 = -val2;

                                double val3 = (result3[0]+result4[0]+critical+1.2*EPSILON);
                                double cateto3 = GetMinDistanceBetweenColors((*color_order)[3], (*color_order)[2]);
                                val3 = sqrt(val3*val3 - cateto3*cateto3);
                                val3 = -val3/2.0;

                                val += val2 + val3;
                            }

                        }
                        break;
                    }

                    double w = (val - mAttractors[1].z)/(mAttractors[0].z- mAttractors[1].z);
                    gsl_vector_set(weights, m, w);
                }

                return weights;
            }
            else
            {
                LinearSolver *lin = new LinearSolver();
                gsl_matrix *edgeMatrix = GetOrderMatrix(color_order, ConnectedComponent);
                gsl_vector *b_vector   = ComputeBvectorOrderMatrix(edgeMatrix, color_order, ConnectedComponent);
                //gsl_matrix *mat_ls     = lin->LeastSquareMatrix(edgeMatrix);
                //gsl_vector *b_ls       = lin->MatrixTransposeVector(edgeMatrix, b_vector);
                //gsl_vector *weights    = lin->Solve(LinearSolver::CHOLESKY, mat_ls, b_ls);
                gsl_vector *weights    = lin->Solve(LinearSolver::SVD, edgeMatrix, b_vector);
                for(unsigned int i = 0; i < weights->size; i++)
                {
                    double val = gsl_vector_get(weights, i);
                    if(val != val)
                    {
                        std::cout<<"nan in solve "<<i<<std::endl;
                        int nada; std::cin>>nada;
                        gsl_vector_set(weights, i, 0.50);
                    }
                    if(val < 0 || val > 1.0)
                    {
                        gsl_vector_set(weights, i, 0.50);
                    }
                }
                bool verbose = false;
                if(verbose)
                {
                    std::cout<<"edgeMatrix  "<<edgeMatrix->size1<<"  "<<edgeMatrix->size2<<std::endl;
                    int cnt = -1;
                    for(std::vector<glm::vec2> node : mAdjacencyList)
                    {
                        if(cnt != GetCNT(node[0][0]))
                        {
                            cnt = GetCNT(node[0][0]);
                            if(cnt < (int)mDrawNano->size())
                                std::cout<<cnt<<": "<<(*mDrawNano)[cnt]->Radius()<<std::endl;
                        }
                    }

                    for(std::vector<glm::vec2> node : mAdjacencyList)
                    {
                        std::cout<<GetCNT(node[0][0])<<"."<<GetIndex(node[0][0])<<"\t";
                    }
                    std::cout<<std::endl;
                    lin->GetMatrixConditioning(edgeMatrix);
                    lin->PrintMatrix(edgeMatrix);
                    std::cout<<"b_vector"<<std::endl;
                    lin->PrintVector(b_vector);
                    std::cout<<"weights"<<std::endl;
                    lin->PrintVector(weights);
                }
                conditioning = lin->GetMatrixConditioning(edgeMatrix);

                gsl_matrix_free(edgeMatrix);
                gsl_vector_free(b_vector);
                return weights;

            }
        }
        break;
    }
    // peso que não gera movimentação
    gsl_vector *weights = gsl_vector_alloc(ConnectedComponent->size());
    gsl_vector_set_all(weights, 0.5);

    return weights;
}

void Graph::GetConnectedComponentDistances(std::vector<std::vector<glm::vec2>> *ConnectedComponent,
                                  std::vector<unsigned int> *color_order,
                                  std::vector<double> *max_distance,
                                  std::vector<double> *min_distance)
{

    /*double att1 = 0.50, att2 = 0.50;
    if(mAttractors.size() > 0)
    {
        att1 = mAttractors[0].z;
        if(mAttractors.size() > 1)
            att2 = mAttractors[1].z;
    }*/
    double critical = 0.0;
    critical = mCriticalDistance;
    //critical = mContacts->GetCriticalDistance();

    int all_points = 2;
    if(all_points == 0)
    {
        for(unsigned int ccp = 0; ccp < ConnectedComponent->size(); ccp++)
        {
            // de acordo com a cor do ponto
            int vert1 = SearchInList((*ConnectedComponent)[ccp][0][0], &mAdjacencyList);
            if(vert1 == -1) continue;
            if(GetCNT(mAdjacencyList[vert1][0][0]) >= (int)mDrawNano->size()) continue;
            for(unsigned int ord = 0; ord < color_order->size(); ord++)
            {
                // olhar a cor do ponto
                if(mGraphColoring[vert1] == (*color_order)[ord])
                {
                    // somar os raios dos CNTs que tem cor associada aos plano a frente
                    double sum_max = (*mDrawNano)[GetCNT((*ConnectedComponent)[ccp][0][0])]->Radius();
                    double sum_min = (*mDrawNano)[GetCNT((*ConnectedComponent)[ccp][0][0])]->Radius();
                    for(unsigned int o = ord+1; o < color_order->size(); o++)
                    {
                        // procurar o CNT de maior ou menor raio para representar o plano a frente
                        glm::vec4 result = GetMinMaxRadiusByColor(ConnectedComponent , (*color_order)[o]);
                        double max_radius = result[0];
                        double min_radius = result[1];
                        int max_cnt = result[2];
                        int min_cnt = result[3];
                        if(o == color_order->size()-1)
                        {
                            // ultima cor
                            sum_max += max_radius+critical;
                            sum_min += min_radius+critical;
                        }
                        else
                        {
                            // cor intermediaria
                            sum_max += 2.0*max_radius+critical;
                            sum_min += 2.0*min_radius+critical;
                        }
                        std::cout<<GetCNT((*ConnectedComponent)[ccp][0][0])<<"."<<GetIndex((*ConnectedComponent)[ccp][0][0]);
                        std::cout<<"  Color: "<<mGraphColoring[vert1];
                        std::cout<<"  max_cnt "<<max_cnt<<"  max_radius "<<max_radius;
                        std::cout<<"  min_cnt "<<min_cnt<<"  min_radius "<<min_radius<<std::endl;
                        std::cout<<"sum_max "<<sum_max<<"  sum_min "<<sum_min<<std::endl;
                    }
                    //(*max_distance).push_back(sum_max/(att1-att2));
                    //(*min_distance).push_back(sum_min/(att1-att2));
                    (*max_distance).push_back(sum_max);
                    (*min_distance).push_back(sum_min);
                    break;
                }
            }
        }

    }
    else if(all_points == 1)
    {
        for(unsigned int ord = 0; ord < color_order->size(); ord++)
        {
            double sum_max = 0.0;
            double sum_min = 0.0;
            // somar os raios dos CNTs que tem cor associada aos plano a frente
            for(unsigned int o = ord; o < color_order->size(); o++)
            {
                // procurar o CNT de maior ou menor raio para representar o plano a frente
                glm::vec4 result = GetMinMaxRadiusByColor(ConnectedComponent , (*color_order)[o]);
                double max_radius = result[0];
                double min_radius = result[1];
                int max_cnt = result[2];
                int min_cnt = result[3];

                if(o == color_order->size()-1)
                {
                    // ultima cor
                    sum_max += max_radius+critical;
                    sum_min += min_radius+critical;
                }
                else
                {
                    if(o == 0)
                    {
                        // primeira cor
                        sum_max += max_radius;
                        sum_min += min_radius;
                    }
                    else
                    {
                        // cor intermediaria
                        sum_max += 2.0*max_radius+critical;
                        sum_min += 2.0*min_radius+critical;
                    }
                }
                std::cout<<"Color: "<<(*color_order)[ord];
                std::cout<<"  max_cnt "<<max_cnt<<"  max_radius "<<max_radius;
                std::cout<<"  min_cnt "<<min_cnt<<"  min_radius "<<min_radius;
                std::cout<<"  sum_max "<<sum_max<<"  sum_min "<<sum_min<<std::endl;
            }
            //(*max_distance).push_back(sum_max/(att1-att2));
            //(*min_distance).push_back(sum_min/(att1-att2));
            (*max_distance).push_back(sum_max);
            (*min_distance).push_back(sum_min);
        }

    }
    else if(all_points == 2)
    {
        for(unsigned int ord = 0; ord < color_order->size(); ord++)
        {
            // procurar o CNT de maior ou menor raio para representar o plano a frente
            glm::vec4 result = GetMinMaxRadiusByColor(ConnectedComponent , (*color_order)[ord]);
            double max_radius = result[0];
            double min_radius = result[1];
            //int max_cnt = result[2];
            //int min_cnt = result[3];

            //std::cout<<"Color: "<<(*color_order)[ord];
            //std::cout<<"  max_cnt "<<max_cnt<<"  max_radius "<<max_radius;
            //std::cout<<"  min_cnt "<<min_cnt<<"  min_radius "<<min_radius<<std::endl;

            (*max_distance).push_back(max_radius);
            (*min_distance).push_back(min_radius);
        }

    }

}

glm::vec4 Graph::GetMinMaxRadiusByColor(std::vector<std::vector<glm::vec2>> *ConnectedComponent, unsigned int color)
{
    // procurar o CNT de maior ou menor raio para representar o plano a frente
    double max_radius = 0.0;
    double min_radius = INT_MAX;
    int max_cnt = -1;
    int min_cnt = -1;
    // procurando cnt de maior raio com a cor que precisamos
    for(unsigned int i = 0; i < ConnectedComponent->size(); i++)
    {
        int vert = SearchInList((*ConnectedComponent)[i][0][0], &mAdjacencyList);
        if(vert == -1) continue;
        int cnt = GetCNT((*ConnectedComponent)[i][0][0]);
        if(cnt >= (int)mDrawNano->size()) continue;
        if(mGraphColoring[vert] == color)
        {
            double radius = (*mDrawNano)[cnt]->Radius();
            if(max_radius < radius)
            {
                max_radius = radius;
                max_cnt = cnt;
            }
            if(min_radius > radius)
            {
                min_radius = radius;
                min_cnt = cnt;
            }
        }
    }

    glm::vec4 result(max_radius, min_radius, max_cnt, min_cnt);

    return result;
}

void Graph::ResetGraphWeights()
{
    std::cout<<"ResetGraphWeights"<<std::endl;
    for(unsigned int i = 0; i < mAdjacencyList.size(); i++)
    {
        mAdjacencyList[i][0][1] = 0.0;
        for(unsigned int j = 1; j < mAdjacencyList[i].size(); j++)
        {
            if(GetCNT(mAdjacencyList[i][j][0]) < (int)(*mDrawNano).size())
                mAdjacencyList[i][j][1] = 0.0;
            else
                mAdjacencyList[i][j][1] = 0.5; /// desse jeito, se o grafo for resolvido os pontos ficam no mesmo lugar
        }
    }
}

unsigned int Graph::GetTotalGraphColors(std::vector<unsigned int> *colors)
{
    /// contando as cores
    unsigned int totalColors = 0;
    for(unsigned int i = 0; i < (*colors).size(); i++)
    {
        if((*colors)[i] > totalColors)
        {
            totalColors = (*colors)[i];
        }
    }
    return totalColors;
}

std::vector<unsigned int> Graph::SetMinimalColoringHeuristic()
{
    std::cout<<"SetMinimalColoringHeuristic"<<std::endl;
    std::vector<unsigned int> min_colors;
    std::vector<unsigned int> min_color_order;

    std::vector<unsigned int> colors1;
    std::vector<unsigned int> color_order;
    unsigned int total_colors1;
    unsigned int total_colors2;
    int total_contacts1;
    int total_contacts2;

    mColoringHeuristic = FIRST_FIT;
    mGraphColoring     = GraphColoringGreedy();
    total_colors1      = GetTotalGraphColors(&mGraphColoring);
    color_order        = GetBestColorOrder(total_contacts1);
    colors1 = mGraphColoring;
    mGraphColoring.clear();

    mColoringHeuristic = DFS;
    mGraphColoring     = GraphColoringGreedy();
    total_colors2      = GetTotalGraphColors(&mGraphColoring);
    min_color_order    = GetBestColorOrder(total_contacts2);
    min_colors = mGraphColoring;
    mGraphColoring.clear();

    if(total_colors1 < total_colors2)
    {
        min_colors = colors1;
    }
    else
    {
        if(total_colors1 == total_colors2)
        {
            if(total_contacts1 < total_contacts2)
            {
                min_colors = colors1;
                total_contacts2 = total_contacts1;
                min_color_order = color_order;
            }
        }
    }
    color_order.clear();
    colors1.clear();

    mColoringHeuristic = LDO;
    mGraphColoring     = GraphColoringGreedy();
    total_colors1      = GetTotalGraphColors(&mGraphColoring);
    total_colors2      = GetTotalGraphColors(&min_colors);
    color_order        = GetBestColorOrder(total_contacts1);
    colors1 = mGraphColoring;
    mGraphColoring.clear();

    if(total_colors1 < total_colors2)
    {
        min_colors = colors1;
    }
    else
    {
        if(total_colors1 == total_colors2)
        {
            if(total_contacts1 < total_contacts2)
            {
                min_colors = colors1;
                total_contacts2 = total_contacts1;
                min_color_order = color_order;
            }
        }
    }
    color_order.clear();
    colors1.clear();

    mColoringHeuristic = DFS_LDO;
    mGraphColoring     = GraphColoringGreedy();
    total_colors1      = GetTotalGraphColors(&mGraphColoring);
    total_colors2      = GetTotalGraphColors(&min_colors);
    color_order        = GetBestColorOrder(total_contacts1);
    colors1 = mGraphColoring;

    if(total_colors1 < total_colors2)
    {
        min_colors = colors1;
    }
    else
    {
        if(total_colors1 == total_colors2)
        {
            if(total_contacts1 < total_contacts2)
            {
                min_colors = colors1;
                total_contacts2 = total_contacts1;
                min_color_order = color_order;
            }
        }
    }
    color_order.clear();
    colors1.clear();

    mGraphColoring = min_colors;
    return min_color_order;
}

std::vector<unsigned int> Graph::GetInitialColorOrder()
{
    std::cout<<"GetInitialColorOrder"<<std::endl;
    std::vector<unsigned int> color_order;
    if(mGraphColoring.size() == 0)
    {
        std::cout<<"Graph not colored"<<std::endl;
        return color_order;
    }
    unsigned int totalColors = GetTotalGraphColors(&mGraphColoring);
    for(unsigned int i = 1; i <= totalColors; i++)
    {
        color_order.push_back(i);
    }

    return color_order;
}

int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

std::vector<unsigned int> Graph::GetBestColorOrder(int &totalContacts)
{
    std::cout<<"GetBestColorOrder"<<std::endl;
    std::vector<unsigned int> color_order = GetInitialColorOrder();
    std::vector<unsigned int> min_color_order = color_order;
    bool verbose = false;
    int component = 0;
    std::vector<int> mComponentsInds;
    mComponentsInds = GetGraphComponents(component);
    totalContacts = 0;
    int factorial_ = factorial(color_order.size());
    int cont = 1;
    mPermutationTotal = factorial_;

    for(int i = 1; i <= component; i++)
    {
        std::vector<std::vector<glm::vec2>> ConnectedComponent = GetConnectedComponent(i, &mComponentsInds);
        int min_contacts = INT_MAX;
        double min_distortion = DBL_MAX;
        double min_contactsLenght = DBL_MAX;

        do {
            int total_contacts;
            double distortion, contactsLenght;
            if(verbose)
            {
                std::cout<<"----------------Permutation-------------------- "<<cont<<"/"<<factorial_<<std::endl;
            }
            ComponentContactLookUp(&ConnectedComponent, &color_order, total_contacts, contactsLenght, distortion);

            std::cout<<"----------------Permutation-------------------- "<<cont<<"/"<<factorial_<<std::endl;
            if(verbose)
            {
                std::cout << "color_order:\n";
                for(int i : color_order)
                    std::cout << i <<"  ";
                std::cout<<std::endl;
                std::cout<<"total_contacts "<<total_contacts<<"  min_contacts "<<min_contacts<<std::endl;
            }
            mPermutationIndex = cont;
            cont++;
            std::cout<<"total_contacts "<<total_contacts<<"  min_contacts       "<<min_contacts<<std::endl;
            std::cout<<"distortion     "<<distortion    <<"  min_distortion     "<<min_distortion<<std::endl;
            std::cout<<"contactsLenght "<<contactsLenght<<"  min_contactsLenght "<<min_contactsLenght<<std::endl;
            /*if((total_contacts < min_contacts) ||
               (total_contacts == min_contacts && min_distortion > distortion ) ||
               (total_contacts == min_contacts && min_distortion == distortion && min_contactsLenght > contactsLenght) )*/

            //if(min_distortion > distortion) min_distortion = distortion;
            //if(min_contactsLenght > contactsLenght) min_contactsLenght = contactsLenght;
            if(total_contacts < min_contacts)
            {
                min_contacts = total_contacts;
                min_color_order.clear();
                min_color_order = color_order;
                if(distortion < min_distortion)
                {
                    min_distortion = distortion;
                }
                if(contactsLenght < min_contactsLenght)
                {
                    min_contactsLenght = contactsLenght;
                }

                if(verbose)
                {
                    std::cout << "min_color_order:\n";
                    for(int i : min_color_order)
                        std::cout << i <<"  ";
                    std::cout<<std::endl;
                    if(min_contacts == 0)
                    {
                        std::cout<<"*****************solved: "<<std::endl;
                    }
                }
                if(min_contacts == 0) break;

            }
            else
            {/*
                if(total_contacts == min_contacts)
                {
                    if(distortion < min_distortion)
                    {
                        min_distortion = distortion;
                        min_contacts = total_contacts;
                        min_color_order.clear();
                        min_color_order = color_order;
                        if(contactsLenght < min_contactsLenght)
                        {
                            min_contactsLenght = contactsLenght;
                        }

                        if(verbose)
                        {
                            std::cout << "min_distortion: "<<min_distortion<<std::endl;
                            std::cout << "min_color_order:\n";
                            for(int i : min_color_order)
                                std::cout << i <<"  ";
                            std::cout<<std::endl;
                            if(min_contacts == 0)
                            {
                                std::cout<<"*****************solved: "<<std::endl;
                            }
                        }
                    }
                    else
                    {
                        if(FEQUAL(distortion, min_distortion))
                        {
                            if(contactsLenght < min_contactsLenght)
                            {
                                min_contactsLenght = contactsLenght;
                                min_contacts = total_contacts;
                                min_color_order.clear();
                                min_color_order = color_order;
                                if(verbose)
                                {
                                    std::cout << "min_contactsLenght: "<<min_contactsLenght<<std::endl;
                                    std::cout << "min_color_order:\n";
                                    for(int i : min_color_order)
                                        std::cout << i <<"  ";
                                    std::cout<<std::endl;
                                    if(min_contacts == 0)
                                    {
                                        std::cout<<"*****************solved: "<<std::endl;
                                    }
                                }
                            }
                        }
                    }
                }
            */}
            //int nada;std::cin>>nada;

        } while ( std::next_permutation(color_order.begin(),color_order.end()) );

        totalContacts += min_contacts;
    }
    return min_color_order;
}


void Graph::ComponentContactLookUp(std::vector<std::vector<glm::vec2>> *ConnectedComponent,
                                  std::vector<unsigned int> *color_order,
                                  int &total_contacts, double &contactsLenght, double &distortion)
{
    std::cout<<"ComponentContactLookUp (testando se a coloracao mantem contatos)"<<std::endl;
    double initial_arc_length = 0.0;
    int cnt0 = -1;
    for(unsigned int i = 0; i < (*mAllCpids).size(); i++)
    {
        int cnt1 = GetCNT((*mAllCpids)[i]);
        if(cnt0 != cnt1)
        {
            initial_arc_length += (*mDrawNano)[cnt1]->mInterpolator->ArcLength();
            cnt0 = cnt1;
        }
    }

    bool prev_mPushAway = mPushAway;

    double conditioning = 0.0;
    ResetGraphWeights();
    SetComponentWeights(ConnectedComponent, color_order, conditioning);
    mColorOrdination.clear();
    mColorOrdination = (*color_order);
    mPushAway = true;
    SolveGraph();

    /// Metrics
    total_contacts = 0;      /// Tem que ser o menor
    contactsLenght = 0.0;    /// Tem que ser o maior
    distortion = 0.0;        /// Tem que ser a menor

    cnt0 = -1;
    double critical = mCriticalDistance;
    //critical = mContacts->GetCriticalDistance();

    for(unsigned int i = 0; i < (*mAllCpids).size(); i++)
    {
        unsigned int cpid1 = (*mAllCpids)[i];
        int cnt1 = GetCNT(cpid1);
        int ind1 = GetIndex(cpid1);

        if(cnt0 != cnt1)
        {
            distortion += (*mDrawNano)[cnt1]->mInterpolator->ArcLength();
            cnt0 = cnt1;
        }

        for(unsigned int j = i+1; j < (*mAllCpids).size(); j++)
        {
            unsigned int cpid2 = (*mAllCpids)[j];

            int cnt2 = GetCNT(cpid2);
            int ind2 = GetIndex(cpid2);

            if(cnt1 == cnt2) continue;
            if(ind1 == segmentsPerCNT-1) continue;
            if(ind2 == segmentsPerCNT-1) continue;

            Vertex pos_m2 = (*mDrawNano)[cnt2]->mInterpolator->ControlPoints()[ind2];
            Vertex pos_m1 = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints()[ind1];
            Vertex pos_m2_1 = (*mDrawNano)[cnt2]->mInterpolator->ControlPoints()[ind2-1];
            Vertex pos_m1_1 = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints()[ind1-1];
            Vertex pt1, pt2;

            double distance = mContacts->DistFromSegments(pos_m2, pos_m1, pos_m2_1, pos_m1_1, pt1, pt2);
            double distanceWithoutRadii = distance - (*mDrawNano)[cnt1]->Radius() - (*mDrawNano)[cnt2]->Radius();

            if(distanceWithoutRadii+EPSILON <= critical)
            {
                total_contacts++;
                contactsLenght += distance;
                ///std::cout<<cnt1<<"."<<ind1<<"-"<<cnt2<<"."<<ind2<<std::endl;
            }
        }
    }

    mPushAway = false;
    SolveGraph();
    gsl_vector_free(mControlPointDisplacement);
    mControlPointDisplacement = NULL;

    distortion = abs(initial_arc_length - distortion);

    mPushAway = prev_mPushAway;
}

bool Graph::IsGraphSolved()
{
    /*
    if(mControlPointDisplacement != NULL)
    {
        if(mControlPointDisplacement->size == 0)
        {
            return false;
        }
        return true;
    }
    return false;
    */
    return (mControlPointDisplacement ? (mControlPointDisplacement->size == 0 ? false : true) : false);
}

void Graph::SolveGraph()
{
    std::cout<<"SolveGraph"<<std::endl;
    if(IsGraphSolved() == false)
    {
        //std::cout<<"IsGraphSolved() = false"<<std::endl;
        if(mOrderSolution == DIRECT)
        {
            bool directZcoord = false;
            bool directHypotenuse = true;
            if(directZcoord)
            {
                //std::cout<<"DirectPushZCoordinate"<<std::endl;
                DirectPushZCoordinate();
            }
            else
            {
                if(directHypotenuse)
                {
                    //std::cout<<"DirectHypotenuse"<<std::endl;
                    DirectHypotenuse();
                }
            }
        }
        else
        {
            Laplacian *laplacian = new Laplacian(mDrawNano, this, segmentsPerCNT);
            mControlPointDisplacement = laplacian->Solve(LinearSolver::SVD);
        }
    }
    SetDisplacement();
    mPushAway = !mPushAway;
    //if(mPushAway) std::cout<<"SolveGraph mPushAway = true"<<std::endl;
    //else std::cout<<"SolveGraph mPushAway = false"<<std::endl;
}

void Graph::DirectPushZCoordinate()
{
    std::cout<<"DirectPushZCoordinate"<<std::endl;
    mControlPointDisplacement = gsl_vector_alloc(mAdjacencyList.size()*3);
    gsl_vector_set_zero(mControlPointDisplacement);

    double critical = 0.0;
    critical = mCriticalDistance;
    //critical = mContacts->GetCriticalDistance();

    int total_colors = 0;
    for(unsigned int i = 0; i < mGraphColoring.size(); i++)
    {
        if((int)mGraphColoring[i] > total_colors) total_colors = mGraphColoring[i];
    }
    for(unsigned int i = 0; i < mGraphColoring.size(); i++)
    {
        /// Fingir que os cnts estao extamente lado a lado para medir um dos catetos.
        switch(total_colors)
        {
            case 2 :
            {
                if(mGraphColoring[i] == mColorOrdination[0]) //if(mGraphColoring[i] == 1)
                {
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 1);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[0]);
                    double val = -(result1[0]+critical/2.0+1.2*EPSILON);
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                else
                {
                    //if(mGraphColoring[i] == mColorOrdination[1])
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    double val = result1[0]+critical/2.0+1.2*EPSILON;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
            }
            break;
            case 3 :
            {
                if(mGraphColoring[i] == mColorOrdination[0]) // if(mGraphColoring[i] == 1)
                {
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 1);
                    //glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[0]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    double val = -(result1[0]+result2[0]+critical+1.2*EPSILON);
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[2]) //if(mGraphColoring[i] == 3)
                {
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    //glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    double val = result1[0]+result2[0]+critical+1.2*EPSILON;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
            }
            break;
            case 4 :
            {
                if(mGraphColoring[i] == mColorOrdination[0]) //if(mGraphColoring[i] == 1)
                {
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 1);
                    //glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[0]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    double val = -(result1[0]+2.0*result2[0]+1.5*critical+1.2*EPSILON);
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[1]) //if(mGraphColoring[i] == 2)
                {
                    //glm::vec4 result = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    glm::vec4 result = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    double val = -(result[0]+critical/2.0+EPSILON);
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[2]) //if(mGraphColoring[i] == 3)
                {
                    //glm::vec4 result = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    glm::vec4 result = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    double val = result[0]+critical/2.0+1.2*EPSILON;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[3]) //if(mGraphColoring[i] == 4)
                {
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 4);
                    //glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    double val = result1[0]+2.0*result2[0]+1.5*critical+1.2*EPSILON;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
            }
            break;
            case 5 :
            {
                if(mGraphColoring[i] == mColorOrdination[0]) //if(mGraphColoring[i] == 1)
                {
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 1);
                    //glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    //glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[0]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    double val = -(result1[0]+2.0*result2[0]+result3[0]+2.0*critical+2.2*EPSILON);
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[1]) //if(mGraphColoring[i] == 2)
                {
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    //glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    double val = -(result1[0]+result2[0]+critical+1.2*EPSILON);
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[3]) //if(mGraphColoring[i] == 4)
                {
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    //glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 4);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    double val = result1[0]+result2[0]+critical+1.2*EPSILON;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[4]) //if(mGraphColoring[i] == 5)
                {
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 5);
                    //glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 4);
                    //glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[4]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    double val = result1[0]+2.0*result2[0]+result3[0]+2.0*critical+2.2*EPSILON;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
            }
            break;
            case 6 :
            {
                if(mGraphColoring[i] == mColorOrdination[0])//if(mGraphColoring[i] == 1)
                {
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 1);
                    //glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    //glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[0]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    double val = -(result1[0]+2.0*result2[0]+2.0*result3[0]+2.5*critical+1.2*EPSILON);
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[1])//if(mGraphColoring[i] == 2)
                {
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    //glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    double val = -(result1[0]+2.0*result2[0]+1.5*critical+EPSILON);
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[2])//if(mGraphColoring[i] == 3)
                {
                    //glm::vec4 result = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    glm::vec4 result = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    double val = -(result[0]+critical/2.0+1.2*EPSILON);
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[3])//if(mGraphColoring[i] == 4)
                {
                    //glm::vec4 result = GetMinMaxRadiusByColor(&mAdjacencyList, 4);
                    glm::vec4 result = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    double val = result[0]+critical/2.0+1.2*EPSILON;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[4])// if(mGraphColoring[i] == 5)
                {
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 5);
                    //glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 4);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[4]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    double val = result1[0]+2.0*result2[0]+1.5*critical+1.2*EPSILON;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[5])//if(mGraphColoring[i] == 6)
                {
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 6);
                    //glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 5);
                    //glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, 4);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[5]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[4]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    double val = result1[0]+2.0*result2[0]+2.0*result3[0]+2.5*critical+1.2*EPSILON;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
            }
            break;
            case 7 :
            {
                if(mGraphColoring[i] == mColorOrdination[0]) // if(mGraphColoring[i] == 1)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 1);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    glm::vec4 result4 = GetMinMaxRadiusByColor(&mAdjacencyList, 4);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[0]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    glm::vec4 result4 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    double val = -(result1[0]+2.0*result2[0]+2.0*result3[0]+result4[0]+2.5*critical+2.0*EPSILON);
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[1]) // if(mGraphColoring[i] == 2)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, 4);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    double val = -(result1[0]+2.0*result2[0]+result3[0]+1.5*critical+1.2*EPSILON);
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[2]) // if(mGraphColoring[i] == 3)
                {
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    double val = -(result1[0]+critical/2.0+1.2*EPSILON);
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[4]) // if(mGraphColoring[i] == 5)
                {
                    //glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 5);
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[4]);
                    double val = result1[0]+critical/2.0+1.2*EPSILON;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[5]) //if(mGraphColoring[i] == 6)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 6);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 5);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, 4);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[5]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[4]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    double val = result1[0]+2.0*result2[0]+result3[0]+2.0*critical+2.0*EPSILON;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[6]) //if(mGraphColoring[i] == 7)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 7);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 6);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, 5);
                    glm::vec4 result4 = GetMinMaxRadiusByColor(&mAdjacencyList, 4);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[6]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[5]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[4]);
                    glm::vec4 result4 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    double val =result1[0]+2.0*result2[0]+2.0*result3[0]+result4[0]+2.5*critical+2.0*EPSILON ;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
            }
            break;
        }

    }

}

void Graph::DirectHypotenuseWithEpsilon()
{
    std::cout<<"DirectHypotenuseWithEpsilon"<<std::endl;
    mControlPointDisplacement = gsl_vector_alloc(mAdjacencyList.size()*3);
    gsl_vector_set_zero(mControlPointDisplacement);

    double critical = 0.0;
    critical = mCriticalDistance;
    //critical = mContacts->GetCriticalDistance();
}

void Graph::DirectHypotenuse()
{
    std::cout<<"DirectHypotenuse"<<std::endl;
    mControlPointDisplacement = gsl_vector_alloc(mAdjacencyList.size()*3);
    gsl_vector_set_zero(mControlPointDisplacement);

    double critical = 0.0;
    critical = mCriticalDistance;
    //critical = mContacts->GetCriticalDistance();

    int total_colors = 0;
    for(unsigned int i = 0; i < mGraphColoring.size(); i++)
    {
        if((int)mGraphColoring[i] > total_colors) total_colors = mGraphColoring[i];
    }
    for(unsigned int i = 0; i < mGraphColoring.size(); i++)
    {
        double val = 0.0;
        switch(total_colors)
        {
            case 2 :
            {
                if(mGraphColoring[i] == mColorOrdination[0]) //if(mGraphColoring[i] == 1)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 1);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[0]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    ///std::cout<<"1 result1 "<<result1[0]<<"  "<<result1[1]<<"  "<<result1[2]<<"  "<<result1[3]<<std::endl;
                    ///std::cout<<"1 result2 "<<result2[0]<<"  "<<result2[1]<<"  "<<result2[2]<<"  "<<result2[3]<<std::endl;

                    //val = result1[0]+mContacts->GetCriticalDistance()+1.2*EPSILON;
                    //val += result2[0];

                    val = result1[0]+result2[0]+1.2*EPSILON;
                    ///std::cout<<"val "<<val<<std::endl;
                    val += critical;
                    //double cateto = GetMinDistanceBetweenColors(1,2);
                    double cateto = GetMinDistanceBetweenColors(mColorOrdination[0],mColorOrdination[1]);
                    ///std::cout<<"cateto 1  "<<cateto<<"  val "<<val<<std::endl;
                    val = sqrt(val*val - cateto*cateto);
                    val = -val/2.0;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                else
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 1);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[0]);
                    ///std::cout<<"2 result1 "<<result1[0]<<"  "<<result1[1]<<"  "<<result1[2]<<"  "<<result1[3]<<std::endl;
                    ///std::cout<<"2 result2 "<<result2[0]<<"  "<<result2[1]<<"  "<<result2[2]<<"  "<<result2[3]<<std::endl;

                    //val  = result1[0]+mContacts->GetCriticalDistance()+1.2*EPSILON;
                    //val += result2[0];
                    val = result1[0]+result2[0]+1.2*EPSILON;
                    ///std::cout<<"val "<<val<<std::endl;
                    val += critical;
                    //double cateto = GetMinDistanceBetweenColors(2,1);
                    double cateto = GetMinDistanceBetweenColors(mColorOrdination[1],mColorOrdination[0]);
                    ///std::cout<<"cateto 2  "<<cateto<<"  val "<<val<<std::endl;
                    val = sqrt(val*val - cateto*cateto);
                    val = val/2.0;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                //int nada;std::cin>>nada;
            }
            break;
            case 3 :
            {
                if(mGraphColoring[i] == mColorOrdination[0]) //if(mGraphColoring[i] == 1)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 1);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[0]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                    //double cateto  = GetMinDistanceBetweenColors(1,2);
                    double cateto  = GetMinDistanceBetweenColors(mColorOrdination[0],mColorOrdination[1]);
                    val = sqrt(val*val - cateto*cateto);
                    val = -val;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[2])//if(mGraphColoring[i] == 3)
                {
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    val = result1[0]+result2[0]+critical+1.2*EPSILON;
                    //double cateto  = GetMinDistanceBetweenColors(2,3);
                    double cateto  = GetMinDistanceBetweenColors(mColorOrdination[1], mColorOrdination[2]);
                    val = sqrt(val*val - cateto*cateto);
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
            }
            break;
            case 4 :
            {
                if(mGraphColoring[i] == mColorOrdination[0]) //if(mGraphColoring[i] == 1)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 1);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[0]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    //double val = (result1[0]+2.0*result2[0]+1.5*mContacts->GetCriticalDistance()+1.2*EPSILON);
                    val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                    //double cateto = GetMinDistanceBetweenColors(1,2);
                    double cateto = GetMinDistanceBetweenColors(mColorOrdination[0], mColorOrdination[1]);
                    val = sqrt(val*val - cateto*cateto);
                    val = -val;

                    double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                    //double cateto2 = GetMinDistanceBetweenColors(2,3);
                    double cateto2 = GetMinDistanceBetweenColors(mColorOrdination[1], mColorOrdination[2]);
                    val2 = sqrt(val2*val2 - cateto2*cateto2);
                    val2 = -val2/2.0;

                    val += val2;

                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[1])//if(mGraphColoring[i] == 2)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    val = (result1[0]+result2[0]+critical+EPSILON);
                    //double cateto  = GetMinDistanceBetweenColors(2,3);
                    double cateto  = GetMinDistanceBetweenColors(mColorOrdination[1],mColorOrdination[2]);
                    val = sqrt(val*val - cateto*cateto);
                    val = -val/2.0;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[2])//if(mGraphColoring[i] == 3)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 4);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    val = (result1[0]+result2[0]+critical+EPSILON);
                    //double cateto  = GetMinDistanceBetweenColors(3,2);
                    double cateto  = GetMinDistanceBetweenColors(mColorOrdination[2], mColorOrdination[1]);
                    val = sqrt(val*val - cateto*cateto);
                    val = val/2.0;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[3])//if(mGraphColoring[i] == 4)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 4);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    ///double val = result1[0]+2.0*result2[0]+1.5*mContacts->GetCriticalDistance()+1.2*EPSILON;
                    val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                    //double cateto  = GetMinDistanceBetweenColors(3,4);
                    double cateto  = GetMinDistanceBetweenColors(mColorOrdination[2], mColorOrdination[3]);
                    val = sqrt(val*val - cateto*cateto);

                    double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                    //double cateto2  = GetMinDistanceBetweenColors(3,2);
                    double cateto2  = GetMinDistanceBetweenColors(mColorOrdination[2], mColorOrdination[1]);
                    val2 = sqrt(val2*val2 - cateto2*cateto2);
                    val2 = val2/2.0;

                    val += val2;

                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
            }
            break;
            case 5 :
            {
                if(mGraphColoring[i] == mColorOrdination[0]) //if(mGraphColoring[i] == 1)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 1);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[0]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                    //double cateto  = GetMinDistanceBetweenColors(1,2);
                    double cateto  = GetMinDistanceBetweenColors(mColorOrdination[0], mColorOrdination[1]);
                    val = sqrt(val*val - cateto*cateto);
                    val = -val;

                    double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                    //double cateto2 = GetMinDistanceBetweenColors(2,3);
                    double cateto2 = GetMinDistanceBetweenColors(mColorOrdination[1], mColorOrdination[2]);
                    val2 = sqrt(val2*val2 - cateto2*cateto2);
                    val2 = -val2;

                    val += val2;

                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[1])//if(mGraphColoring[i] == 2)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                    //double cateto  = GetMinDistanceBetweenColors(3,2);
                    double cateto  = GetMinDistanceBetweenColors(mColorOrdination[2], mColorOrdination[1]);
                    val = sqrt(val*val - cateto*cateto);
                    val = -val;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[3])//if(mGraphColoring[i] == 4)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 4);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    val = result1[0]+result2[0]+critical+1.2*EPSILON;
                    //double cateto  = GetMinDistanceBetweenColors(3,4);
                    double cateto  = GetMinDistanceBetweenColors(mColorOrdination[2], mColorOrdination[3]);
                    val = sqrt(val*val - cateto*cateto);
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[4])// if(mGraphColoring[i] == 5)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 5);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 4);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[4]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                    //double cateto  = GetMinDistanceBetweenColors(4,5);
                    double cateto  = GetMinDistanceBetweenColors(mColorOrdination[3], mColorOrdination[4]);
                    val = sqrt(val*val - cateto*cateto);

                    double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                    //double cateto2 = GetMinDistanceBetweenColors(4,3);
                    double cateto2 = GetMinDistanceBetweenColors(mColorOrdination[3], mColorOrdination[2]);
                    val2 = sqrt(val2*val2 - cateto2*cateto2);

                    val += val2;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
            }
            break;
            case 6 :
            {
                if(mGraphColoring[i] == mColorOrdination[0]) //if(mGraphColoring[i] == 1)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 1);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[0]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    glm::vec4 result4 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    //double val = (result1[0]+2.0*result2[0]+1.5*mContacts->GetCriticalDistance()+1.2*EPSILON);
                    val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                    //double cateto = GetMinDistanceBetweenColors(1,2);
                    double cateto = GetMinDistanceBetweenColors(mColorOrdination[0], mColorOrdination[1]);
                    val = sqrt(val*val - cateto*cateto);
                    val = -val;

                    double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                    //double cateto2 = GetMinDistanceBetweenColors(2,3);
                    double cateto2 = GetMinDistanceBetweenColors(mColorOrdination[1], mColorOrdination[2]);
                    val2 = sqrt(val2*val2 - cateto2*cateto2);
                    val2 = -val2;

                    double val3 = (result3[0]+result4[0]+critical+1.2*EPSILON);
                    //double cateto2 = GetMinDistanceBetweenColors(2,3);
                    double cateto3 = GetMinDistanceBetweenColors(mColorOrdination[2], mColorOrdination[3]);
                    val3 = sqrt(val3*val3 - cateto3*cateto3);
                    val3 = -val3/2.0;

                    val += val2 + val3;

                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[1]) //if(mGraphColoring[i] == 2)
                {
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[1]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);

                    val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                    double cateto = GetMinDistanceBetweenColors(mColorOrdination[1], mColorOrdination[2]);
                    val = sqrt(val*val - cateto*cateto);
                    val = -val;

                    double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                    double cateto2 = GetMinDistanceBetweenColors(mColorOrdination[2], mColorOrdination[3]);
                    val2 = sqrt(val2*val2 - cateto2*cateto2);
                    val2 = -val2/2.0;

                    val += val2;

                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[2])//if(mGraphColoring[i] == 3)
                {
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    val = (result1[0]+result2[0]+critical+EPSILON);
                    //double cateto  = GetMinDistanceBetweenColors(2,3);
                    double cateto  = GetMinDistanceBetweenColors(mColorOrdination[2],mColorOrdination[3]);
                    val = sqrt(val*val - cateto*cateto);
                    val = -val/2.0;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[3])//if(mGraphColoring[i] == 4)
                {
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[4]);
                    val = (result1[0]+result2[0]+critical+EPSILON);
                    //double cateto  = GetMinDistanceBetweenColors(3,2);
                    double cateto  = GetMinDistanceBetweenColors(mColorOrdination[2], mColorOrdination[1]);
                    val = sqrt(val*val - cateto*cateto);
                    val = val/2.0;
                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[4])//if(mGraphColoring[i] == 5)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 4);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[4]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    ///double val = result1[0]+2.0*result2[0]+1.5*mContacts->GetCriticalDistance()+1.2*EPSILON;
                    val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                    //double cateto  = GetMinDistanceBetweenColors(3,4);
                    double cateto  = GetMinDistanceBetweenColors(mColorOrdination[3], mColorOrdination[4]);
                    val = sqrt(val*val - cateto*cateto);

                    double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                    //double cateto2  = GetMinDistanceBetweenColors(3,2);
                    double cateto2  = GetMinDistanceBetweenColors(mColorOrdination[3], mColorOrdination[2]);
                    val2 = sqrt(val2*val2 - cateto2*cateto2);
                    val2 = val2/2.0;

                    val += val2;

                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }
                if(mGraphColoring[i] == mColorOrdination[5]) //if(mGraphColoring[i] == 6)
                {
                    /*glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, 1);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, 2);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, 3);*/
                    glm::vec4 result1 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[5]);
                    glm::vec4 result2 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[4]);
                    glm::vec4 result3 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[3]);
                    glm::vec4 result4 = GetMinMaxRadiusByColor(&mAdjacencyList, mColorOrdination[2]);
                    //double val = (result1[0]+2.0*result2[0]+1.5*mContacts->GetCriticalDistance()+1.2*EPSILON);
                    val = (result1[0]+result2[0]+critical+1.2*EPSILON);
                    //double cateto = GetMinDistanceBetweenColors(1,2);
                    double cateto = GetMinDistanceBetweenColors(mColorOrdination[5], mColorOrdination[4]);
                    val = sqrt(val*val - cateto*cateto);
                    val = -val;

                    double val2 = (result2[0]+result3[0]+critical+1.2*EPSILON);
                    //double cateto2 = GetMinDistanceBetweenColors(2,3);
                    double cateto2 = GetMinDistanceBetweenColors(mColorOrdination[4], mColorOrdination[3]);
                    val2 = sqrt(val2*val2 - cateto2*cateto2);
                    val2 = -val2;

                    double val3 = (result3[0]+result4[0]+critical+1.2*EPSILON);
                    //double cateto2 = GetMinDistanceBetweenColors(2,3);
                    double cateto3 = GetMinDistanceBetweenColors(mColorOrdination[3], mColorOrdination[2]);
                    val3 = sqrt(val3*val3 - cateto3*cateto3);
                    val3 = -val3/2.0;

                    val += val2 + val3;

                    gsl_vector_set(mControlPointDisplacement, i*3+2, val);
                }

            }
            break;
        }
        if(val != val)
        {
            std::cout<<"val "<<val<<" total_colors "<<total_colors<<" mGraphColoring i = "<<i<<": "<<mGraphColoring[i]<<std::endl;
            gsl_vector_set(mControlPointDisplacement, i*3+2, 0.0);
            int cnt = GetCNT(mAdjacencyList[i][0][0]);
            int ind = GetIndex(mAdjacencyList[i][0][0]);
            mNanListDir.push_back(glm::vec2(cnt, ind));
            //int nada;std::cin>>nada;
        }
    }

}

double Graph::GetMinDistanceBetweenColors(unsigned int color1, unsigned int color2)
{
    //std::cout<<"GetMinDistanceBetweenColors"<<std::endl;
    double min_distance = INT_MAX;
    for(unsigned int i = 0; i < mAdjacencyList.size()-mAttractors.size(); i++)
    {
        if(mGraphColoring[i] == color1)
        {
            for(unsigned int j = 0; j < mAdjacencyList[i].size()-mAttractors.size(); j++)
            {
                int vert = SearchInList(mAdjacencyList[i][j][0], &mAdjacencyList);
                if(vert == -1 ) continue;
                if(GetCNT(mAdjacencyList[i][0][0]) >= (int)mDrawNano->size()) continue;
                if(GetCNT(mAdjacencyList[i][j][0]) >= (int)mDrawNano->size()) continue;
                if(mGraphColoring[vert] == color2)
                {
                    int cnt1 = GetCNT(mAdjacencyList[i][0][0]);
                    int ind1 = GetIndex(mAdjacencyList[i][0][0]);
                    int cnt2 = GetCNT(mAdjacencyList[i][j][0]);
                    int ind2 = GetIndex(mAdjacencyList[i][j][0]);
                    /*std::cout<<cnt1<<"."<<ind1<<"-"<<cnt2<<"."<<ind2<<std::endl;
                    int nada;
                    if(cnt1 < 0 || cnt1 > mDrawNano->size()) std::cin>>nada;
                    if(cnt2 < 0 || cnt2 > mDrawNano->size()) std::cin>>nada;
                    if(ind1-1 < 0 || ind1-1 >= segmentsPerCNT) std::cin>>nada;
                    if(ind2-1 < 0 || ind2-1 >= segmentsPerCNT) std::cin>>nada;
                    if(ind1 < 0 || ind1 >= segmentsPerCNT) std::cin>>nada;
                    if(ind2 < 0 || ind2 >= segmentsPerCNT) std::cin>>nada;*/
                    Vertex pos1   = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints()[ind1];
                    Vertex pos1_1 = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints()[ind1-1];
                    Vertex pos2   = (*mDrawNano)[cnt2]->mInterpolator->ControlPoints()[ind2];
                    Vertex pos2_1 = (*mDrawNano)[cnt2]->mInterpolator->ControlPoints()[ind2-1];
                    Vertex pt1, pt2;
                    double distance = mContacts->DistFromSegments(pos2, pos1, pos2_1, pos1_1, pt1, pt2);
                    if(distance < min_distance)
                    {
                        min_distance = distance;
                        //std::cout<<cnt1<<"."<<ind1<<"-"<<cnt2<<"."<<ind2<<"  "<<min_distance<<std::endl;
                    }
                }
            }
        }
    }
    return min_distance;
}

void Graph::SetDisplacement()
{
    std::cout<<"SetDisplacement"<<std::endl;
    int attSize = mAttractors.size();
    int adjSize = mAdjacencyList.size();
    int vertSize = adjSize-attSize;

    bool verbose = false;

    for(unsigned int i = 0; i < mAdjacencyList.size(); i++)
    {
        int cnt = GetCNT(mAdjacencyList[i][0][0]);
        int ind = GetIndex(mAdjacencyList[i][0][0]);

        double x = gsl_vector_get(mControlPointDisplacement, i*3);
        double y = gsl_vector_get(mControlPointDisplacement, i*3+1);
        double z = gsl_vector_get(mControlPointDisplacement, i*3+2);
        if(verbose)
        {
            std::cout<<GetCNT(mAdjacencyList[i][0][0])<<"."<<GetIndex(mAdjacencyList[i][0][0]);
            std::cout<<"\t"<<x<<"   "<<y<<"   "<<z<<std::endl;
        }
        if(x != x)
        {
            std::cout<<"x = nan "<<x<<"  "<< mControlPointDisplacement->size<<"  "<<i*3<<std::endl;
            int nada; std::cin>>nada;
        }
        if(y != y)
        {
            std::cout<<"y = nan "<<y<<"  "<< mControlPointDisplacement->size<<"  "<<i*3+1<<std::endl;
            int nada; std::cin>>nada;
        }
        if(z != z)
        {
            std::cout<<"z = nan "<<z<<"  "<< mControlPointDisplacement->size<<"  "<<i*3+2<<std::endl;
            int nada; std::cin>>nada;
        }

        if(mPushAway)
        {
            if(cnt < (int)(*mDrawNano).size())
            {
                (*mDrawNano)[cnt]->mInterpolator->TranslateControlPoint(ind, x, y, z);
                (*mDrawNano)[cnt]->NeedUpdate(true);
                mControlPointSpheres->TraslateSpherePosition(mAdjacencyList[i][0][0]-2*cnt, glm::vec3(x, y, z));
            }
            else
            {
                mAttractors[i-vertSize].x += x;
                mAttractors[i-vertSize].y += y;
                mAttractors[i-vertSize].z += z;
                mAttractorSpheres->UpdateSpherePosition(i-vertSize+mAttractorSphereIndex, mAttractors[i-vertSize]);
            }
        }
        else
        {
            if(cnt < (int)(*mDrawNano).size())
            {
                (*mDrawNano)[cnt]->mInterpolator->TranslateControlPoint(ind, -x, -y, -z);
                (*mDrawNano)[cnt]->NeedUpdate(true);
                mControlPointSpheres->TraslateSpherePosition(mAdjacencyList[i][0][0]-2*cnt, glm::vec3(-x, -y, -z));
            }
            else
            {
                mAttractors[i-vertSize].x -= x;
                mAttractors[i-vertSize].y -= y;
                mAttractors[i-vertSize].z -= z;
                mAttractorSpheres->UpdateSpherePosition(i-vertSize+mAttractorSphereIndex, mAttractors[i-vertSize]);
            }
        }
    }
}

gsl_matrix* Graph::GetOrderMatrix(std::vector<unsigned int> *color_order,
                            std::vector<std::vector<glm::vec2>> *ConnectedComponent)
{
    std::cout<<"GetOrderMatrix"<<std::endl;
    std::vector<glm::vec2> edges;
    edges = GetEdges(color_order, ConnectedComponent);

    gsl_matrix *matrix = gsl_matrix_alloc(edges.size()+1, (*ConnectedComponent).size());
    gsl_matrix_set_zero(matrix);

    bool verbose = false;

    for(unsigned int row = 0; row < edges.size(); row++)
    {
        int vert1 = SearchInList(edges[row][0], ConnectedComponent);
        int vert2 = SearchInList(edges[row][1], ConnectedComponent);
        if(vert1 > -1 && vert2 > -1)
        {
            gsl_matrix_set(matrix, row, vert1, -1.0);
            gsl_matrix_set(matrix, row, vert2,  1.0);
            if(verbose)
            {
                vert1 = SearchInList(edges[row][0], &mAdjacencyList);
                vert2 = SearchInList(edges[row][1], &mAdjacencyList);
                std::cout<<GetCNT(edges[row][0])<<"."<<GetIndex(edges[row][0])<<"("<<mGraphColoring[vert1]<<")-";
                std::cout<<GetCNT(edges[row][1])<<"."<<GetIndex(edges[row][1])<<"("<<mGraphColoring[vert2]<<")"<<std::endl;
            }
        }
    }
    for(unsigned int col = 0; col < matrix->size2; col++)
    {
        gsl_matrix_set(matrix, matrix->size1-1, col,  1.0); /// \sum = 1.0
    }
    edges.clear();
    return matrix;
}

std::vector<glm::vec2> Graph::GetEdges(std::vector<unsigned int> *color_order,
                            std::vector<std::vector<glm::vec2>> *ConnectedComponent)
{
    std::vector<glm::vec2> edges;
    bool original = false;
    if(original)
    {
        for(unsigned int i = 0; i < (*ConnectedComponent).size(); i++)
        {
            for(unsigned int j = 1; j < (*ConnectedComponent)[i].size(); j++)
            {
                // para não inserir arestas repetidas
                unsigned int k = 0;
                for( ; k < edges.size(); k++)
                {
                    if((edges[k][0] == (*ConnectedComponent)[i][0][0] &&
                        edges[k][1] == (*ConnectedComponent)[i][j][0]) ||
                       (edges[k][0] == (*ConnectedComponent)[i][j][0] &&
                        edges[k][1] == (*ConnectedComponent)[i][0][0]))
                    {
                        break;
                    }
                }
                // não ha arestas repetidas, então
                if(k >= edges.size()) // aresta não encontrada
                {
                    int m = SearchInList((*ConnectedComponent)[i][j][0], ConnectedComponent);
                    if(m != -1)
                    {
                        int vert1 = SearchInList((*ConnectedComponent)[i][0][0], &mAdjacencyList);
                        int vert2 = SearchInList((*ConnectedComponent)[i][j][0], &mAdjacencyList);
                        unsigned int color1 = mGraphColoring[vert1];
                        unsigned int color2 = mGraphColoring[vert2];
                        if(abs(color1 - color2) > 1) continue;
                        unsigned int index1 = 0, index2 = 0;
                        for(unsigned int c = 0; c < (*color_order).size(); c++)
                        {
                            if((*color_order)[c] == color1) index1 = c;
                            if((*color_order)[c] == color2) index2 = c;
                        }
                        if(index1 > index2)
                            edges.push_back(glm::vec2((*ConnectedComponent)[i][j][0], (*ConnectedComponent)[i][0][0]));
                        else
                            edges.push_back(glm::vec2((*ConnectedComponent)[i][0][0], (*ConnectedComponent)[i][j][0]));
                    }
                }
            }
        }

    }
    else // aqui nao retorna-se arestas
    {
        unsigned int total_colors = 0; // da componente
        for(unsigned int i = 0; i < (*ConnectedComponent).size(); i++)
        {
            int vert = SearchInList((*ConnectedComponent)[i][0][0], &mAdjacencyList);
            if(vert != -1)
            {
                if(total_colors < mGraphColoring[vert])
                    total_colors = mGraphColoring[vert];
            }
        }
        for(unsigned int i = 0; i < (*ConnectedComponent).size(); i++)
        {
            int vert = SearchInList((*ConnectedComponent)[i][0][0], &mAdjacencyList);
            if(vert != -1)
            {
                if(mGraphColoring[vert] == (*color_order)[0])
                {
                    /// procurar por alguem que tenha a cor (*color_order)[1]
                    for(unsigned int j = 0; j < mGraphColoring.size(); j++)
                    {
                        if(mGraphColoring[j] != (*color_order)[1]) continue;
                        int vert2 = SearchInList(mAdjacencyList[j][0][0], ConnectedComponent);
                        if(vert2 != -1)
                        {
                            // quem receberá o -1 e quem receberá o 1
                            edges.push_back(glm::vec2((*ConnectedComponent)[i][0][0], (*ConnectedComponent)[vert2][0][0]));
                            //edges.push_back(glm::vec2((*ConnectedComponent)[vert2][0][0], (*ConnectedComponent)[i][0][0]));
                            break;
                        }
                    }
                }
                else
                {
                    // qual o indice da ordem da cor do vertice ConnectedComponent[i][0][0]
                    int ind1 = 0;
                    for(unsigned int j = 0; j < color_order->size(); j++)
                    {
                        if(mGraphColoring[vert] == (*color_order)[j])
                        {
                            ind1 = j-1;
                        }
                    }
                    if(ind1 == -1)
                    {
                         std::cout<<"ops\n";
                         int nada; std::cin>>nada;
                    }
                    // qual o cpid do vertice da componente que tem essa cor?
                    for(unsigned int j = 0; j < (*ConnectedComponent).size(); j++)
                    {
                        int vert2 = SearchInList((*ConnectedComponent)[j][0][0], &mAdjacencyList);
                        if(vert2 != -1)
                        {
                            if(mGraphColoring[vert2] == (*color_order)[ind1])
                            {
                                edges.push_back(glm::vec2((*ConnectedComponent)[j][0][0], (*ConnectedComponent)[i][0][0]));
                                //edges.push_back(glm::vec2((*ConnectedComponent)[i][0][0], (*ConnectedComponent)[j][0][0]));
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    bool verbose = false;
    if(verbose)
    {
        for(glm::vec2 e : edges)
        {
            std::cout<<GetCNT(e[0])<<"."<<GetIndex(e[0])<<"-"<<GetCNT(e[1])<<"."<<GetIndex(e[1])<<"\t";
        }
        std::cout<<std::endl;
    }

    return edges;
}

gsl_vector* Graph::ComputeBvectorOrderMatrix(gsl_matrix *edgeMatrix,
                                             std::vector<unsigned int> *color_order,
                                             std::vector<std::vector<glm::vec2>> *ConnectedComponent)
{
    std::cout<<"ComputeBvectorOrderMatrix"<<std::endl;
    bool verbose = false;
    gsl_vector* b_vector = gsl_vector_alloc(edgeMatrix->size1);
    gsl_vector_set_zero(b_vector);

    double att1 = 0.50, att2 = 0.50;
    if(mAttractors.size() > 0)
    {
        att1 = mAttractors[0].z;
        if(mAttractors.size() > 1)
            att2 = mAttractors[1].z;
    }
    for(unsigned int i = 0; i < edgeMatrix->size1-1; i++)
    {
        int indNeg = -1; // indice da coluna matriz que tem valor -1.0
        int indPos = -1; // indice da coluna matriz que tem valor +1.0
        // as colunas tem mesmo indice do cpid da componente conexa
        for(unsigned int j = 0; j < edgeMatrix->size2; j++)
        {
            if(gsl_matrix_get(edgeMatrix, i, j) == -1.0) indNeg = j;
            if(gsl_matrix_get(edgeMatrix, i, j) ==  1.0) indPos = j;
        }
        //std::cout<<"i  "<<i<<" edgeMatrix->size1 "<<edgeMatrix->size1<<"  indNeg  "<<indNeg<<"  indPos "<<indPos<<std::endl;
        if(indNeg == -1 || indPos == -1) continue;
        // se os planos em Z não forem consecutivos
        unsigned int colorOrder1 = 0;
        unsigned int colorOrder2 = 0;
        for(unsigned int j = 0; j < (*color_order).size(); j++)
        {
            int indNegAdj = SearchInList((*ConnectedComponent)[indNeg][0][0], &mAdjacencyList);
            int indPosAdj = SearchInList((*ConnectedComponent)[indPos][0][0], &mAdjacencyList);
            if(mGraphColoring[indNegAdj] == (*color_order)[j]) colorOrder1 = j;
            if(mGraphColoring[indPosAdj] == (*color_order)[j]) colorOrder2 = j;
        }

        // montando o vetor b
        double val = GetValueForConsecutivePlanes(indNeg, indPos, colorOrder1, colorOrder2, color_order, ConnectedComponent);
        /// afastar planos nao consecutivos
        /*if(abs((int)colorOrder1-(int)colorOrder2) > 1)
        {
            val = GetValueForNonConsecutivePlanes(colorOrder1, colorOrder2, val, color_order, ConnectedComponent);
        }*/
        if(FEQUAL(val, 0.0)) val = 0.0;
        else val = val/(att1-att2)+EPSILON; /// assim, com HYPOTENUSE vemos apenas os contatos errados

        if(val != val) std::cout<<"NAN \n";

        int cntNeg = GetCNT((*ConnectedComponent)[indNeg][0][0]);
        int cntPos = GetCNT((*ConnectedComponent)[indPos][0][0]);
        if(verbose)
        {
            std::cout<<"edge  "<<cntNeg<<"."<<GetIndex((*ConnectedComponent)[indNeg][0][0])<<"-"<<cntPos<<"."<<GetIndex((*ConnectedComponent)[indPos][0][0]);
            std::cout<<"\tindNegAdj  "<<SearchInList((*ConnectedComponent)[indNeg][0][0], &mAdjacencyList);
            std::cout<<"\tindPosAdj  "<<SearchInList((*ConnectedComponent)[indPos][0][0], &mAdjacencyList);
            std::cout<<"\tindNeg  "<<indNeg<<"\tindPos  "<<indPos<<"\tval  "<<val<<std::endl;
        }
        gsl_vector_set(b_vector, i, val);
    }
    gsl_vector_set(b_vector, b_vector->size-1, (edgeMatrix->size2*att1)/(att1-att2));

    return b_vector;
}

double Graph::GetValueForConsecutivePlanes(int indNeg, int indPos, unsigned int colorOrder1, unsigned int colorOrder2,
                                           std::vector<unsigned int> *color_order,
                                           std::vector<std::vector<glm::vec2>> *ConnectedComponent)
{
    ///std::cout<<"GetValueForConsecutivePlanes"<<std::endl;
    int cntNeg = GetCNT((*ConnectedComponent)[indNeg][0][0]);
    int cntPos = GetCNT((*ConnectedComponent)[indPos][0][0]);
    double radiusNeg = (*mDrawNano)[cntNeg]->Radius();
    double radiusPos = (*mDrawNano)[cntPos]->Radius();
    bool verbose = false;
    double critical = 0.0;
    critical = mCriticalDistance;
    //critical = mContacts->GetCriticalDistance();

    // montando o vetor b
    double val = 0.0;
    switch(mOrderSolution)
    {
        case ORIGINAL:
        {
            val = critical;// + 2.0*EPSILON;
            val += radiusNeg + radiusPos;
            /// da valor diferente em relacao ao DIRECT por causa disso.
            /// Aqui não estamos usando o menor ou menor raio.
            /// Fazemos isso apenas quando encontramos cores que sao planos mais afastados
        }
        break;
        case ORIGINAL_MAX:
        {
            std::vector<double> max_distance;
            std::vector<double> min_distance; /// não e' util

            GetConnectedComponentDistances(ConnectedComponent, color_order, &max_distance, &min_distance);

            /// maior raio para as cores
            radiusNeg = max_distance[colorOrder1];
            radiusPos = max_distance[colorOrder2];
            val = critical;// + 2.0*EPSILON;
            val += radiusNeg + radiusPos;
            if(verbose)
            {
                std::cout<<"max_distance "<<std::endl;
                for(double m : max_distance)
                {
                    std::cout<<m<<"\t";
                }
                std::cout<<std::endl;
            }

            max_distance.clear();
            min_distance.clear();
        }
        break;
        case ORIGINAL_MIN:
        {
            std::vector<double> max_distance;
            std::vector<double> min_distance; /// não e' util

            GetConnectedComponentDistances(ConnectedComponent, color_order, &max_distance, &min_distance);

            /// maior raio para as cores
            radiusNeg = min_distance[colorOrder1];
            radiusPos = min_distance[colorOrder2];
            val = critical;// + 2.0*EPSILON;
            val += radiusNeg + radiusPos;
            if(verbose)
            {
                std::cout<<"min_distance "<<std::endl;
                for(double m : min_distance)
                {
                    std::cout<<m<<"\t";
                }
                std::cout<<std::endl;
            }
            max_distance.clear();
            min_distance.clear();
        }
        break;
        case CRITICAL:
        {
            val = critical;// + 2.0*EPSILON;
        }
        break;
        case HYPOTENUSE:
        {
            bool original = false;
            if(original == false)
            {
                glm::vec4 result1 = GetMinMaxRadiusByColor(ConnectedComponent, (*color_order)[colorOrder1]);
                glm::vec4 result2 = GetMinMaxRadiusByColor(ConnectedComponent, (*color_order)[colorOrder2]);

                val  = result1[0]+critical/2.0+1.2*EPSILON;
                val += result2[0]+critical/2.0;

                if(abs((int)colorOrder1-(int)colorOrder2) > 1)
                {
                    val = GetValueForNonConsecutivePlanes(colorOrder1, colorOrder2, val, color_order, ConnectedComponent);
                }
                double cateto = GetMinDistanceBetweenColors((*color_order)[colorOrder1], (*color_order)[colorOrder2]);

                //if(val < cateto)
                //{
                    //std::cout<<"val "<<val<<" cateto "<<cateto<<"  "<<colorOrder1<<"  "<<colorOrder2<<std::endl;
                    //std::cout<<"critical "<<critical<<" "<<mCriticalDistance<<"  "<<mContacts->GetCriticalDistance()<<"  "<<mContacts->GetContactDistance()<<std::endl;
                    //std::cout<<cntNeg<<"."<<GetIndex((*ConnectedComponent)[indNeg][0][0])<<"-"<<cntPos<<"."<<GetIndex((*ConnectedComponent)[indPos][0][0])<<std::endl;

                    //int nada; std::cin>>nada;
                //}

                val = sqrt(val*val - cateto*cateto);
                if(val != val)
                {
                    int indexN = GetIndex((*ConnectedComponent)[indNeg][0][0]);
                    int indexP = GetIndex((*ConnectedComponent)[indPos][0][0]);
                    mNanListHyp.push_back(glm::vec4(cntNeg, indexN, cntPos, indexP));
                    val = 0.0;
                }
                if(verbose) std::cout<<"val   "<<val<<std::endl;
            }
            else
            {
            unsigned int cpidNeg = (*ConnectedComponent)[indNeg][0][0];
            unsigned int cpidPos = (*ConnectedComponent)[indPos][0][0];
            int indN = GetIndex(cpidNeg);
            int indP = GetIndex(cpidPos);

            Vertex posNeg1  = (*mDrawNano)[cntNeg]->mInterpolator->ControlPoints()[indN+1];
            Vertex posPos1  = (*mDrawNano)[cntPos]->mInterpolator->ControlPoints()[indP+1];
            Vertex posNeg   = (*mDrawNano)[cntNeg]->mInterpolator->ControlPoints()[indN];
            Vertex posPos   = (*mDrawNano)[cntPos]->mInterpolator->ControlPoints()[indP];
            Vertex posNeg_1 = (*mDrawNano)[cntNeg]->mInterpolator->ControlPoints()[indN-1];
            Vertex posPos_1 = (*mDrawNano)[cntPos]->mInterpolator->ControlPoints()[indP-1];
            Vertex pt1(0.0, 0.0, 0.0);
            Vertex pt2(0.0, 0.0, 0.0);

            double contactDist  = mContacts->DistFromSegments(posNeg , posPos , posNeg_1, posPos_1, pt1, pt2);
            double sub = abs(pt2.x - pt1.x);
            double contactDist1 = mContacts->DistFromSegments(posNeg , posPos1, posNeg_1, posPos  , pt1, pt2);
            double sub1 = abs(pt2.x - pt1.x);
            double contactDist2 = mContacts->DistFromSegments(posNeg1, posPos , posNeg  , posPos_1, pt1, pt2);
            double sub2 = abs(pt2.x - pt1.x);
            double contactDist3 = mContacts->DistFromSegments(posNeg1, posPos1, posNeg  , posPos  , pt1, pt2);
            double sub3 = abs(pt2.x - pt1.x);

            if(contactDist > contactDist1)
            {
                contactDist = contactDist1;
                sub = sub1;
            }
            if(contactDist > contactDist2)
            {
                contactDist = contactDist2;
                sub = sub2;
            }
            if(contactDist > contactDist3)
            {
                contactDist = contactDist3;
                sub = sub3;
            }

            double intersection = contactDist - radiusNeg - radiusPos;
            double distance = 0.0;
            //double sub = posNeg.x - posPos.x;
            if(verbose)
            {
                std::cout<<std::endl;
                std::cout<<"x2-x1  "<<sub<<"  radiusNeg  "<<radiusNeg<<"  radiusPos  "<<radiusPos<<std::endl;
            }
            if(intersection > critical)
            {
                sub = sub - intersection;
            }
            distance = radiusNeg + radiusPos + critical;
            /*
            double distance = mContacts->DistFromSegments(posNeg, posPos, posNeg_1, posPos_1, pt1, pt2);
            double sub = pt2.x - pt1.x;
            distance = radiusNeg + radiusPos + distance;
            */
            if(verbose)
            {
                std::cout<<"sub    "<<sub<<"  hipotenusa "<<distance<<std::endl;
                std::cout<<"contactDist  "<<contactDist<<"  intersection  "<<intersection<<std::endl;
                std::cout<<"r1+r2+0.3  "<<distance<<"  **2  "<<distance*distance<<"  x2-x1**2  "<<sub*sub<<std::endl;
            }
            /*if(abs((int)colorOrder1-(int)colorOrder2) > 1)
            {
                double diam = GetValueForNonConsecutivePlanes(colorOrder1, colorOrder2, distance, color_order, ConnectedComponent);
                distance += diam;
            }*/

            distance = distance*distance;
            sub = sub*sub;
            /// sem o sub, se comporta como o caso original sem usar GetValueForNonConsecutivePlanes
            if(sub < distance)
            {
                distance = distance - sub;
            }
            else
            {
                std::cout<<" ********************************** "<<std::endl;
                distance = 0.0;
            }

            std::cout<<"distance**2  "<<distance<<std::endl;
            distance = sqrt(distance);
            std::cout<<"sqrt  "<<distance<<std::endl;
            val = distance;
            if(abs((int)colorOrder1-(int)colorOrder2) > 1)
            {
                double diam = GetValueForNonConsecutivePlanes(colorOrder1, colorOrder2, distance, color_order, ConnectedComponent);
                val += diam;
            }

            }
        }
        break;

        case DIRECT: break; // nunca vai cair aqui
    }

    return val;
}

Vertex Graph::GetRadiusProjectionOnEdge(int cnt, unsigned int cpid1, unsigned int cpid2)
{
    /// projeta ortogonalmente a aresta o raio na aresta
    double radius = (*mDrawNano)[cnt]->Radius();
    Vertex rad(radius, 0.0, 0.0);
    Vertex pos1 = (*mDrawNano)[GetCNT(cpid1)]->mInterpolator->ControlPoints()[GetIndex(cpid1)];
    Vertex pos2 = (*mDrawNano)[GetCNT(cpid2)]->mInterpolator->ControlPoints()[GetIndex(cpid2)];
    Vertex sub = pos1 - pos2;
    if(pos1.x < pos2.x)
    {
        sub = pos2 - pos1;
    }
    sub.Normalize();
    double a = ( sub.x*rad.x + sub.y*rad.y + sub.z*rad.z );
    sub.x = sub.x*a;
    sub.y = sub.y*a;
    sub.z = sub.z*a;

    return sub;
}

double Graph::GetValueForNonConsecutivePlanes(unsigned int colorOrder1, unsigned int colorOrder2, double val,
                                             std::vector<unsigned int> *color_order,
                                             std::vector<std::vector<glm::vec2>> *ConnectedComponent)
{
    ///std::cout<<"GetValueForNonConsecutivePlanes"<<std::endl;
    bool verbose = false;
    std::vector<double> max_distance;
    std::vector<double> min_distance; /// não e' util
    GetConnectedComponentDistances(ConnectedComponent, color_order, &max_distance, &min_distance);

    double critical = 0.0;
    critical = mCriticalDistance;
    //critical = mContacts->GetCriticalDistance();

    /// afastar planos nao consecutivos
    if(abs((int)colorOrder1-(int)colorOrder2) > 1)
    {
        if(verbose)
        {
            std::cout<<"Cores em planos não consecutivos  "<<abs((int)colorOrder1-(int)colorOrder2)<<"\t";
            /*std::cout<<cntNeg<<"."<<GetIndex((*ConnectedComponent)[indNeg][0][0])<<"-";
            std::cout<<cntPos<<"."<<GetIndex((*ConnectedComponent)[indPos][0][0])<<std::endl;*/
            std::cout<<"colorOrder1  "<<colorOrder1<<"  colorOrder2 "<<colorOrder2<<std::endl;
        }
        if(colorOrder1 > colorOrder2)
        {
            std::swap(colorOrder1, colorOrder2);
        }
        /// procurando cores intermediarias
        while(colorOrder1+1 < colorOrder2)
        {
            switch(mOrderSolution)
            {
                case CRITICAL:
                {
                    val += critical+2.0*EPSILON;
                }
                break;
                case ORIGINAL: /// pega o raio do 1o ponto do CNT encontrado com a cor intermediaria
                {
                    for(unsigned int k = 0; k < mGraphColoring.size(); k++)
                    {
                        int cc_index = SearchInList(mAdjacencyList[k][0][0], ConnectedComponent);
                        // o ponto exista na componente conexa. podemos analisar a cor
                        if(cc_index >= 0 && mGraphColoring[k] == (*color_order)[colorOrder1+1])
                        {
                            int cnt = GetCNT((*ConnectedComponent)[cc_index][0][0]);
                            double diameter = 2.0*(*mDrawNano)[cnt]->Radius()+critical;
                            val += diameter;
                            if(verbose) std::cout<<cnt<<"."<<GetIndex((*ConnectedComponent)[cc_index][0][0])<<std::endl;
                            break;
                        }
                    }
                }
                break;
                case DIRECT :
                case HYPOTENUSE :
                case ORIGINAL_MAX: /// pega o maior raio dentre os CNTs com a cor intermediaria
                {
                    /*double increment = 0.0;
                    for(unsigned int k = 0; k < mGraphColoring.size(); k++)
                    {
                        int cc_index = SearchInList(mAdjacencyList[k][0][0], ConnectedComponent);
                        // o ponto exista na componente conexa. podemos analisar a cor
                        if(cc_index >= 0 && mGraphColoring[k] == (*color_order)[colorOrder1+1])
                        {
                            int cnt = GetCNT((*ConnectedComponent)[cc_index][0][0]);
                            double diameter = 2.0*(*mDrawNano)[cnt]->Radius()+mContacts->GetCriticalDistance();
                            if(increment < diameter)
                            {
                                increment = diameter;
                                std::cout<<cnt<<"."<<GetIndex((*ConnectedComponent)[cc_index][0][0]);
                                std::cout<<"\t diameter  "<<diameter;
                                std::cout<<"\t increment "<<increment<<std::endl;
                            }
                        }
                    }
                    val += increment;*/
                    double radiusInter = max_distance[colorOrder1];
                    val += 2.0*radiusInter+critical;
                    if(verbose) std::cout<<"val += "<< 2.0*radiusInter+critical<<" = "<<val<<std::endl;
                }
                break;
                case ORIGINAL_MIN: /// pega o menor raio dentre os CNTs com a cor intermediaria
                {
                    /*double increment = INT_MAX;
                    for(unsigned int k = 0; k < mGraphColoring.size(); k++)
                    {
                        int cc_index = SearchInList(mAdjacencyList[k][0][0], ConnectedComponent);
                        // o ponto exista na componente conexa. podemos analisar a cor
                        if(cc_index >= 0 && mGraphColoring[k] == (*color_order)[colorOrder1+1])
                        {
                            int cnt = GetCNT((*ConnectedComponent)[cc_index][0][0]);
                            double diameter = 2.0*(*mDrawNano)[cnt]->Radius()+mContacts->GetCriticalDistance();
                            if(increment > diameter)
                            {
                                increment = diameter;
                                std::cout<<cnt<<"."<<GetIndex((*ConnectedComponent)[cc_index][0][0]);
                                std::cout<<"\t diameter  "<<diameter;
                                std::cout<<"\t increment "<<increment<<std::endl;
                            }
                        }
                    }
                    val += increment;*/
                    double radiusInter = min_distance[colorOrder1];
                    val += 2.0*radiusInter+critical;
                }
                break;
            }
            colorOrder1++;
        }
    }

    max_distance.clear();
    min_distance.clear();


    return val;
}

std::vector<int> Graph::GetGraphComponents(int &component)
{
    std::cout<<"GetGraphComponents"<<std::endl;
    component = 1;
    std::vector<int> visited;
    for(unsigned int i = 0; i < mAdjacencyList.size()-mAttractors.size(); i++)
    {
        visited.push_back(0.0);
    }
    for(unsigned int i = 0; i < visited.size(); i++)
    {
        if(visited[i] == 0)
        {
            GetGraphComponentsUtil(&visited, i, component);
            component++;
        }
    }
    component--;
    bool verbose = false;
    if(verbose)
    {
        std::cout<<"visited *** component  "<<component<<std::endl;
        for(unsigned int i = 0; i < visited.size(); i++)
        {
            std::cout<<visited[i]<<"\t";
        }
        std::cout<<std::endl;
    }
    mTotalComponents = component;
    return visited;
}

void Graph::GetGraphComponentsUtil(std::vector<int> *visited, int v, int component)
{
    (*visited)[v] = component;
    for(unsigned int i = 1; i < mAdjacencyList[v].size()-mAttractors.size(); i++)
    {
        for(unsigned int j = 0; j < mAdjacencyList.size()-mAttractors.size(); j++)
        {
            if(mAdjacencyList[v][i][0] == mAdjacencyList[j][0][0])
            {
                if((*visited)[j] != component)
                {
                    GetGraphComponentsUtil(visited, j, component);
                }
                break;
            }
        }
    }
}

std::vector<std::vector<glm::vec2>> Graph::GetConnectedComponent(int component, std::vector<int> *visited)
{
    std::cout<<"GetConnectedComponent"<<std::endl;
    std::vector<std::vector<glm::vec2>> ConnectedComponent;
    for(unsigned int i = 0; i < mAdjacencyList.size()-mAttractors.size(); i++)
    {
        if((*visited)[i] != component) continue;

        std::vector<glm::vec2> node;
        for(unsigned int j = 0; j < mAdjacencyList[i].size()-mAttractors.size(); j++)
        {
            bool add = false;
            for(unsigned int k = 0; k < mAdjacencyList.size()-mAttractors.size(); k++)
            {
                if(mAdjacencyList[k][0][0] == mAdjacencyList[i][j][0])
                {
                    if((*visited)[k] != component) break;
                    add = true;
                    break;
                }
            }
            if(add) node.push_back(mAdjacencyList[i][j]);
        }
        ConnectedComponent.push_back(node);
    }
    return ConnectedComponent;
}

void Graph::DrawGraph(bool mDrawAtt)
{
    for(std::vector<glm::vec2> node : mAdjacencyList)
    {
        Vertex pt1(0.0,0.0,0.0);
        int total_cps = mContacts->GetTotalControlPoints();
        int cpid1 = node[0][0];
        if(cpid1 < total_cps)
        {
            pt1 = (*mDrawNano)[GetCNT(cpid1)]->mInterpolator->ControlPoints()[GetIndex(cpid1)];
            glColor3f(mGraphColor.x, mGraphColor.y, mGraphColor.z);

            for(unsigned int i = 1; i < node.size(); i++)
            {
                int cpid2 = node[i][0];
                glBegin(GL_LINE_STRIP);
                if(cpid2 < total_cps)
                {
                    Vertex pt2 = (*mDrawNano)[GetCNT(cpid2)]->mInterpolator->ControlPoints()[GetIndex(cpid2)];
                    glVertex3f(pt1.x, pt1.y, pt1.z);
                    glVertex3f(pt2.x, pt2.y, pt2.z);
                }
                glEnd();
            }

        }
        else
        {
            if(mDrawAtt)
            {
                glm::vec3 pt = mAttractors[(cpid1-total_cps)];
                pt1.x = pt.x;
                pt1.y = pt.y;
                pt1.z = pt.z;
                glColor3f(mAttractorColor.x, mAttractorColor.y, mAttractorColor.z);

                for(unsigned int i = 1; i < node.size(); i++)
                {
                    int cpid2 = node[i][0];
                    glBegin(GL_LINE_STRIP);
                    if(cpid2 < total_cps)
                    {
                        Vertex pt2 = (*mDrawNano)[GetCNT(cpid2)]->mInterpolator->ControlPoints()[GetIndex(cpid2)];
                        glVertex3f(pt1.x, pt1.y, pt1.z);
                        glVertex3f(pt2.x, pt2.y, pt2.z);
                    }
                    glEnd();
                }
            }

        }

    }
}

void Graph::RemoveIsolatedVertices()
{
    for(std::vector<std::vector<glm::vec2>>::const_iterator iter = mAdjacencyList.begin();
        iter != mAdjacencyList.end(); iter++)
    {
        if((*iter).size() == 1)
        {
            iter = mAdjacencyList.erase(iter);
            iter--;
        }
    }
}

void Graph::SetAttractors()
{
    double mSphereSize = 4.0;
    unsigned int adj_size = mAdjacencyList.size();
    mAttractorSphereIndex = mAttractorSpheres->GetTotalSpheres();
    bool verbose = false;
    if(verbose)
        std::cout<<"mAttractorSphereIndex  "<<mAttractorSphereIndex<<std::endl;

    switch(mAttractorType)
    {
        case MIDPOINT :
        {
            Vertex attractor(0.0, 0.0, 0.0);

            for(unsigned int i = 0; i < adj_size; i++)
            {
                int cnt = GetCNT(mAdjacencyList[i][0][0]);
                int ind = GetIndex(mAdjacencyList[i][0][0]);
                Vertex pos = (*mDrawNano)[cnt]->mInterpolator->ControlPoints()[ind];
                attractor.x += pos.x;
                attractor.y += pos.y;
            }
            attractor.x = attractor.x/adj_size;
            attractor.y = attractor.y/adj_size;
            attractor.z = mAttractorZ;

            mAttractors.push_back(vec3(attractor.x, attractor.y,  attractor.z));
            mAttractors.push_back(vec3(attractor.x, attractor.y, -attractor.z));

            mAttractorSpheres->PushSphere(glm::vec3(attractor.x, attractor.y, attractor.z), mAttractorColor, mSphereSize);
            mAttractorSpheres->PushSphere(glm::vec3(attractor.x, attractor.y,-attractor.z), mAttractorColor, mSphereSize);

        }
        break;
        case ONEPOINT :
        {
            int point = 0;
            int cnt = GetCNT(mAdjacencyList[point][0][0]);
            int ind = GetIndex(mAdjacencyList[point][0][0]);

            Vertex pos = (*mDrawNano)[cnt]->mInterpolator->ControlPoints()[ind];

            mAttractors.push_back(vec3(pos.x, pos.y,  mAttractorZ));
            mAttractors.push_back(vec3(pos.x, pos.y, -mAttractorZ));

            mAttractorSpheres->PushSphere(glm::vec3(pos.x, pos.y, mAttractorZ), mAttractorColor, mSphereSize);
            mAttractorSpheres->PushSphere(glm::vec3(pos.x, pos.y,-mAttractorZ), mAttractorColor, mSphereSize);
        }
        break;
        case EXTREMES :
        {
            int point1 = 0;
            int point2 = adj_size-1;
            int cnt1 = GetCNT(mAdjacencyList[point1][0][0]);
            int cnt2 = GetCNT(mAdjacencyList[point2][0][0]);
            int ind1 = GetIndex(mAdjacencyList[point1][0][0]);
            int ind2 = GetIndex(mAdjacencyList[point2][0][0]);

            Vertex pos1 = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints()[ind1];
            Vertex pos2 = (*mDrawNano)[cnt2]->mInterpolator->ControlPoints()[ind2];

            mAttractors.push_back(vec3(pos1.x, pos1.y,  mAttractorZ));
            mAttractors.push_back(vec3(pos2.x, pos2.y, -mAttractorZ));
            mAttractorSpheres->PushSphere(glm::vec3(pos1.x, pos1.y, mAttractorZ), mAttractorColor, mSphereSize);
            mAttractorSpheres->PushSphere(glm::vec3(pos2.x, pos2.y,-mAttractorZ), mAttractorColor, mSphereSize);
        }
        break;
        default :
            std::cout<<"No attractors"<<std::endl;
            int nada; std::cin>>nada;
        break;
    }
    if(verbose)
        std::cout<<"mAttractorSphereIndex end "<<mAttractors.size()+mAttractorSphereIndex<<std::endl;
}

void Graph::SetAnchors()
{
    double mSphereSize = 4.0;
    mAnchorSphereIndex = mAnchorSpheres->GetTotalSpheres();
    bool verbose = false;
    if(verbose)
        std::cout<<"mAnchorSphereIndex  "<<mAnchorSphereIndex<<std::endl;

    switch(mAnchorType)
    {
        case SUPERBLOCK :
        {
            unsigned int max_cnt_cpid = 0;
            unsigned int min_cnt_cpid = (*mAllCpids)[mAllCpids->size()-1]+1;
            int cnt = GetCNT((*mAllCpids)[0]);

            for(unsigned int cpid : (*mAllCpids))
            {
                int cnt_vec = GetCNT(cpid);
                //int ind = GetIndex(cpid);
                //std::cout<<cnt_vec<<"."<<ind<<std::endl;
                if(cnt == cnt_vec)
                {
                    if(max_cnt_cpid < cpid)
                    {
                        max_cnt_cpid = cpid;
                    }
                    if(min_cnt_cpid > cpid-1)
                    {
                        min_cnt_cpid = cpid-1;
                    }
                }
                else
                {
                    //td::cout<<"max_cnt_cpid  "<<GetCNT(max_cnt_cpid)<<"."<<GetIndex(max_cnt_cpid)<<"  ";
                    if(!mContacts->WasAddedToBlock(max_cnt_cpid))
                    {
                        //std::cout<<"true  ";
                        mContacts->SetAnchor(max_cnt_cpid, true);
                        mAnchors.push_back(max_cnt_cpid);
                    }
                    //std::cout<<std::endl;
                    //std::cout<<"min_cnt_cpid  "<<GetCNT(min_cnt_cpid)<<"."<<GetIndex(min_cnt_cpid)<<"  ";
                    if(!mContacts->WasAddedToBlock(min_cnt_cpid))
                    {
                        //std::cout<<"true  ";
                        mContacts->SetAnchor(min_cnt_cpid, true);
                        mAnchors.push_back(min_cnt_cpid);
                    }
                    //std::cout<<std::endl;
                    cnt = cnt_vec;
                    max_cnt_cpid = 0;
                    min_cnt_cpid = cpid-1;
                }
            }
            //std::cout<<"max_cnt_cpid  "<<GetCNT(max_cnt_cpid)<<"."<<GetIndex(max_cnt_cpid)<<"  ";
            if(!mContacts->WasAddedToBlock(max_cnt_cpid))
            {
                //std::cout<<"true  ";
                mContacts->SetAnchor(max_cnt_cpid, true);
                mAnchors.push_back(max_cnt_cpid);
            }
            //std::cout<<std::endl;
            //std::cout<<"min_cnt_cpid  "<<GetCNT(min_cnt_cpid)<<"."<<GetIndex(min_cnt_cpid)<<"  ";
            if(!mContacts->WasAddedToBlock(min_cnt_cpid))
            {
                //std::cout<<"true  ";
                mContacts->SetAnchor(min_cnt_cpid, true);
                mAnchors.push_back(min_cnt_cpid);
            }
            //std::cout<<std::endl;
        }
        break;
        case GRAPH :
        {
            unsigned int max_cnt_cpid = 0;
            unsigned int min_cnt_cpid = mAdjacencyList[mAdjacencyList.size()-1][0][0]+1;
            int cnt = GetCNT(mAdjacencyList[0][0][0]);

            for(std::vector<glm::vec2> node : mAdjacencyList)
            {
                unsigned int cpid = node[0][0];
                int cnt_vec = GetCNT(cpid);
                //int ind = GetIndex(cpid);
                //std::cout<<cnt_vec<<"."<<ind<<std::endl;
                if(cnt == cnt_vec)
                {
                    if(max_cnt_cpid < cpid+1)
                    {
                        max_cnt_cpid = cpid+1;
                    }
                    if(min_cnt_cpid > cpid-1)
                    {
                        min_cnt_cpid = cpid-1;
                    }
                }
                else
                {
                    //td::cout<<"max_cnt_cpid  "<<GetCNT(max_cnt_cpid)<<"."<<GetIndex(max_cnt_cpid)<<"  ";
                    if(!mContacts->WasAddedToBlock(max_cnt_cpid))
                    {
                        //std::cout<<"true  ";
                        mContacts->SetAnchor(max_cnt_cpid, true);
                        mAnchors.push_back(max_cnt_cpid);
                    }
                    //std::cout<<std::endl;
                    //std::cout<<"min_cnt_cpid  "<<GetCNT(min_cnt_cpid)<<"."<<GetIndex(min_cnt_cpid)<<"  ";
                    if(!mContacts->WasAddedToBlock(min_cnt_cpid))
                    {
                        //std::cout<<"true  ";
                        mContacts->SetAnchor(min_cnt_cpid, true);
                        mAnchors.push_back(min_cnt_cpid);
                    }
                    //std::cout<<std::endl;
                    cnt = cnt_vec;
                    max_cnt_cpid = cpid+1;
                    min_cnt_cpid = cpid-1;
                }
            }
            //std::cout<<"max_cnt_cpid  "<<GetCNT(max_cnt_cpid)<<"."<<GetIndex(max_cnt_cpid)<<"  ";
            if(!mContacts->WasAddedToBlock(max_cnt_cpid))
            {
                //std::cout<<"true  ";
                mContacts->SetAnchor(max_cnt_cpid, true);
                mAnchors.push_back(min_cnt_cpid);
            }
            //std::cout<<std::endl;
            //std::cout<<"min_cnt_cpid  "<<GetCNT(min_cnt_cpid)<<"."<<GetIndex(min_cnt_cpid)<<"  ";
            if(!mContacts->WasAddedToBlock(min_cnt_cpid))
            {
                //std::cout<<"true  ";
                mContacts->SetAnchor(min_cnt_cpid, true);
                mAnchors.push_back(min_cnt_cpid);
            }

        }
        break;
        default :
            std::cout<<"No anchors"<<std::endl;
            int nada; std::cin>>nada;
        break;
    }

    //std::cout<<"Anchors"<<std::endl;
    for(unsigned int cpid : mAnchors)
    {
        unsigned int cnt = GetCNT(cpid);
        unsigned int ind = GetIndex(cpid);
        Vertex pt1 = (*mDrawNano)[cnt]->mInterpolator->ControlPoints()[ind];
        mAnchorSpheres->PushSphere(vec3(pt1[0], pt1[1], pt1[2]), mAnchorColor, mSphereSize);
    }

    if(verbose)
        std::cout<<"mAnchorSphereIndex end "<<mAnchors.size()+mAnchorSphereIndex<<std::endl;
}

void Graph::PrintGraph(std::vector<std::vector<glm::vec2>> *adj_list)
{
    std::cout<<"Lista de adjacencia do grafo"<<std::endl;
    std::cout<<"(grau do no) [id do no] [vizinhos...] (peso)"<<std::endl;
    for(std::vector<glm::vec2> node : (*adj_list))
    {
        std::cout<<"("<<node.size()-1<<") ";
        for(glm::vec2 id_ : node)
        {
            if(id_.x < mContacts->GetTotalControlPoints())
                std::cout<<GetCNT(id_.x)<<"."<<GetIndex(id_.x)<<"("<<id_.y<<")   ";
            else
                std::cout<<id_.x<<"("<<id_.y<<")   ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    /*for(std::vector<glm::vec2> node : (*adj_list))
    {
        for(glm::vec2 id_ : node)
        {
            if(id_[0] != node[0][0])
            {
                if(GetCNT(id_[0]) < (int)mDrawNano->size() && GetCNT(node[0][0]) < (int)mDrawNano->size())
                {
                    Vertex pos1 = (*mDrawNano)[GetCNT(node[0][0])]->mInterpolator->ControlPoints()[GetIndex(node[0][0])];
                    Vertex pos2 = (*mDrawNano)[GetCNT(id_[0])]->mInterpolator->ControlPoints()[GetIndex(id_[0])];
                    std::cout<<"Edge Distance: "<<GetCNT(node[0][0])<<"."<<GetIndex(node[0][0])<<"-"<<GetCNT(id_[0])<<"."<<GetIndex(id_[0])<<"\t";
                    std::cout<<pos1.Distance(pos2)<<"\t";
                    Vertex r1 = GetRadiusProjectionOnEdge(GetCNT(node[0][0]), node[0][0], id_[0]);
                    Vertex r2 = GetRadiusProjectionOnEdge(GetCNT(id_[0]), node[0][0], id_[0]);
                    std::cout<<r1.Length()<<"\t";
                    std::cout<<r2.Length()<<std::endl;
                    //std::cout<<pos1.Distance(pos2)- (*mDrawNano)[GetCNT(node[0][0])]->Radius()- (*mDrawNano)[GetCNT(id_[0])]->Radius()<<std::endl;
                }
            }
        }
    }*/

    int cnt = -1;
    for(std::vector<glm::vec2> node : (*adj_list))
    {
        if(cnt != GetCNT(node[0][0]))
        {
            cnt = GetCNT(node[0][0]);
            if(cnt >= (int)mDrawNano->size()) continue;
            std::cout<<cnt<<":  "<<(*mDrawNano)[cnt]->Radius()<<"\t";
        }
    }
    std::cout<<std::endl;
}

void Graph::FreeAdjacencyList(std::vector<std::vector<glm::vec2>> *adj_list)
{
    for(unsigned int i = 0; i < adj_list->size(); i++)
    {
        //(*node).clear();
        (*adj_list)[i].clear();
    }
    adj_list->clear();
}

int Graph::SearchInList(unsigned int cpid, std::vector<std::vector<glm::vec2>> *adj_list)
{
    for(unsigned int i = 0; i < (*adj_list).size(); i++)
    {
        if((*adj_list)[i][0][0] == cpid)
            return (int)i;
    }
    return -1;
}

int Graph::SearchInNeighbours(int vert, unsigned int cpid, std::vector<std::vector<glm::vec2>> *adj_list)
{
    if(vert >= 0 && vert < (int)(*adj_list).size())
    {
        for(unsigned int i = 1; i < (*adj_list)[vert].size(); i++)
        {
            if((*adj_list)[vert][i][0] == cpid)
                return (int)i;
        }
    }
    return -1;
}

glm::vec3 Graph::GetAttractorPosition(int att)
{
    if(0 <= att && att < (int)mAttractors.size())
        return glm::vec3(mAttractors[att].x, mAttractors[att].y, mAttractors[att].z);
    return glm::vec3(0.0);
}

unsigned int Graph::GetVertexNeighbourSize(int v)
{
    if(0 <= v && v < (int)mAdjacencyList.size())
        return mAdjacencyList[v].size();
    return -1;
}

unsigned int Graph::GetGraphEdges()
{
    int sum = 0;
    for(unsigned int i = 0; i < mAdjacencyList.size(); i++)
    {
        sum += mAdjacencyList[i].size()-1;
    }
    return sum/2;
}

unsigned int Graph::GetGraphMaxColor()
{
    if(mGraphColoring.size() > 0)
    {
        unsigned int max_color = 0;
        for(unsigned int i = 0; i < mGraphColoring.size(); i++)
        {
            if(max_color < mGraphColoring[i])
            {
                max_color = mGraphColoring[i];
            }
        }
        return max_color;
    }

    return 0;
}

double Graph::GetOrderMatrixConditioning(unsigned int component)
{
    if(mOrderMatrixConditioning.size() > 0 && component >= 0 && component < mOrderMatrixConditioning.size())
    {
        return mOrderMatrixConditioning[component];
    }
    return 0;
}

glm::vec2 Graph::GetVertexContent(int v, int n)
{
    if(0 <= v && v < (int)mAdjacencyList.size())
        if(0 <= n && n < (int)mAdjacencyList[v].size())
        {
            //std::cout<<"GetVertexContent "<<GetCNT(mAdjacencyList[v][n][0])<<"."<<GetIndex(mAdjacencyList[v][n][0])<<": "<<mAdjacencyList[v][n][1]<<std::endl;
            return glm::vec2(mAdjacencyList[v][n][0],mAdjacencyList[v][n][1]) ;
        }
    return glm::vec2(0.0);
}

bool Graph::AddNewEdge(unsigned int cpid1, unsigned int cpid2)
{
    int nada;
    if(!mPushAway)
    {
        std::cout<<"AddNewEdge mPushAway false"<<std::endl;
        std::cin>>nada;
        mPushAway = false;
        SolveGraph();
    } else
    {
        std::cout<<"AddNewEdge mPushAway true"<<std::endl;
        std::cin>>nada;
    }
    ResetControlPointColors();
    int vert1 = SearchInList(cpid1, &mAdjacencyList);
    int vert2 = SearchInList(cpid2, &mAdjacencyList);
    if(vert1 == -1)
    {
        AddVertex(cpid1);
        mNeedGraphUpdate = true; // faz com que tenha atratores com peso zero
    }
    if(vert2 == -1)
    {
        AddVertex(cpid2);
        mNeedGraphUpdate = true; // faz com que tenha atratores com peso zero
    }
    bool added = AddEdge(cpid1, cpid2);

    mNeedGraphUpdate = true; // primeiros testes assim só por precaução

    vert1 = SearchInList(cpid1, &mAdjacencyList);
    vert2 = SearchInList(cpid2, &mAdjacencyList);

    /*sort(mAdjacencyList[vert1].begin()+1, mAdjacencyList[vert1].end(), node_by_cpid);
    sort(mAdjacencyList[vert2].begin()+1, mAdjacencyList[vert2].end(), node_by_cpid);
    sort(mAdjacencyList.begin(), mAdjacencyList.end(), list_by_cpid);*/
    GraphOrdination();

    UpdateGraph();

    return added;
}

void Graph::AddVertex(unsigned int cpid)
{
    std::cout<<"Adding vertex:  "<<GetCNT(cpid)<<"."<<GetIndex(cpid)<<std::endl;
    std::vector<glm::vec2> node;
    node.push_back(glm::vec2(cpid, 0.0));
    mAdjacencyList.push_back(node);
    for(unsigned int i = 0; i < mAttractors.size() ; i++)
    {
        AddEdge(mContacts->GetTotalControlPoints()+i, cpid);
    }
    node.clear();
}

bool Graph::AddEdge(unsigned int cpid1, unsigned int cpid2)
{
    /// cnt1.ind1 - cnt2.ind2
    int vert1 = SearchInList(cpid1, &mAdjacencyList);
    if(vert1 != -1)
    {
        if(SearchInNeighbours(vert1, cpid2, &mAdjacencyList) == -1)
        {
            int vert2 = SearchInList(cpid2, &mAdjacencyList);
            if(vert2 != -1)
            {
                mAdjacencyList[vert1].push_back(glm::vec2(cpid2, 0.0));
                if(SearchInNeighbours(vert2, cpid2, &mAdjacencyList) == -1)
                {
                    /// cnt2.ind2-1 - cnt1.ind1-1
                    mAdjacencyList[vert2].push_back(glm::vec2(cpid1, 0.0));
                    return true;
                }
            }
        }
    }
    return false;
}

bool Graph::RemoveEdge(unsigned int cpid1, unsigned int cpid2)
{
    int nada;
    if(!mPushAway)
    {
        std::cout<<"RemoveEdge mPushAway false"<<std::endl;
        std::cin>>nada;
        mPushAway = false;
        SolveGraph();
    } else
    {
        std::cout<<"RemoveEdge mPushAway true"<<std::endl;
        std::cin>>nada;
    }
    ResetControlPointColors();
    /// cnt1.ind1 - cnt2.ind2
    bool remove1 = false;
    bool remove2 = false;
    for(std::vector<std::vector<glm::vec2>>::iterator iter = mAdjacencyList.begin();
        iter != mAdjacencyList.end(); iter++)
    {
        if((*iter)[0][0] == cpid1)
        {
            for(std::vector<glm::vec2>::iterator n_iter = (*iter).begin();
                n_iter != (*iter).end(); n_iter++)
            {
                if((*n_iter)[0] == cpid2)
                {
                    n_iter = mAdjacencyList[std::distance(mAdjacencyList.begin(),iter)].erase(n_iter);
                    n_iter--;
                    remove1 = true;
                    mNeedGraphUpdate = true;
                    break;
                }
            }
        }
        if((*iter)[0][0] == cpid2)
        {
            for(std::vector<glm::vec2>::iterator n_iter = (*iter).begin();
                n_iter != (*iter).end(); n_iter++)
            {
                if((*n_iter)[0] == cpid1)
                {
                    n_iter = mAdjacencyList[std::distance(mAdjacencyList.begin(),iter)].erase(n_iter);
                    n_iter--;
                    remove2 = true;
                    mNeedGraphUpdate = true;
                    break;
                }
            }
        }
        if((*iter).size() == 1+mAttractors.size())
        {
            iter = mAdjacencyList.erase(iter);
            iter--;
        }
        if(remove1 && remove2) break;
    }
    UpdateGraph();
    return (remove1 && remove2) ;
}

void Graph::UpdateGraph()
{
    int nada;
    if(!mPushAway)
    {
        std::cout<<"UpdateGraph mPushAway false"<<std::endl;
        std::cin>>nada;
        mPushAway = false;
        SolveGraph();
    } else
    {
        std::cout<<"UpdateGraph mPushAway true"<<std::endl;
        std::cin>>nada;
    }
    if(mNeedGraphUpdate)
    {
        std::cout<<"mNeedGraphUpdate"<<std::endl;
        /// resetting graph coloring
        mGraphColoring.clear();
        /// resetting displacement vector
        gsl_vector_free(mControlPointDisplacement);
        mControlPointDisplacement = NULL;
        ResetGraphWeights();
        SetWeights();
        /// setting new colors
        SetControlPointColor();
        mNeedGraphUpdate = false;
    }
}

void Graph::ResetControlPointColors()
{
    if(mAdjacencyList.size() == 0)
    {
        std::cout<<"ResetControlPointColors: No graph"<<std::endl;
        return;
    }
    for(unsigned int i = 0; i < mAdjacencyList.size(); i++)
    {
        int cnt = GetCNT(mAdjacencyList[i][0][0]);
        mControlPointSpheres->UpdateSphereColor(mAdjacencyList[i][0][0]-2*cnt, glm::vec3(1.0));
    }
}

unsigned int Graph::ResetGraph()
{
    if(!mPushAway)
    {
        //std::cout<<"ResetGraph mPushAway false"<<std::endl;
        //int nada;std::cin>>nada;
        mPushAway = false;
        SolveGraph();
    } /*else std::cout<<"ResetGraph mPushAway true"<<std::endl;
    int nada;std::cin>>nada;*/
    ResetControlPointColors();
    std::cout<<"Choose graph assemble heuristic: "<<std::endl;
    std::cout<<"CONTACTS: C\t CONNECTED: N\t ULTRA_CONNECTED: U\t SIMPLE_CONNECTED: S\t CONTACT_TO_POINT: P"<<std::endl;
    char option = 'a';
    std::cin>>option;
    switch(option)
    {
        case 'C':
        case 'c':
            mGraphType = CONTACTS;
        break;
        case 'N':
        case 'n':
            mGraphType = CONNECTED;
        break;
        case 'U':
        case 'u':
            mGraphType = ULTRA_CONNECTED;
        break;
        case 'S':
        case 's':
            mGraphType = SIMPLE_CONNECTED;
        break;
        case 'P':
        case 'p':
            mGraphType = CONTACT_TO_POINT;
        break;
        default : mGraphType = CONNECTED; break;
    }
    std::cout<<"Choose color order search: "<<std::endl;
    std::cout<<"INITIAL: I\t BEST: B\t VERY_BEST: V"<<std::endl;
    option = 'a';
    std::cin>>option;
    switch(option)
    {
        case 'I':
        case 'i':
            mColorOrder = INITIAL;
        break;
        case 'B':
        case 'b':
            mColorOrder = BEST;
        break;
        case 'V':
        case 'v':
            mColorOrder = VERY_BEST;
        break;
        default : mColorOrder = BEST; break;
    }
    std::cout<<"Choose graph coloring heuristic: "<<std::endl;
    std::cout<<"FIRST_FIT: F\t DFS: D\t LDO: L\t DFS_LDO: O \t BFS: B"<<std::endl;
    option = 'a';
    std::cin>>option;
    switch(option)
    {
        case 'F':
        case 'f':
            mColoringHeuristic = FIRST_FIT;
        break;
        case 'D':
        case 'd':
            mColoringHeuristic = DFS;
        break;
        case 'L':
        case 'l':
            mColoringHeuristic = LDO;
        break;
        case 'O':
        case 'o':
            mColoringHeuristic = DFS_LDO;
        break;
        case 'B':
        case 'b':
            mColoringHeuristic = BFS;
        break;
        default : mColoringHeuristic = DFS; break;
    }
    std::cout<<"Choose graph color choice heuristic: "<<std::endl;
    std::cout<<"MIN_INDEX: M\t LAST_INDEX: L\t CLOSEST_CNT_INDEX: C"<<std::endl;
    option = 'a';
    std::cin>>option;
    switch(option)
    {
        case 'M':
        case 'm':
            mColoringChoice = MIN_INDEX;
        break;
        case 'L':
        case 'l':
            mColoringChoice = LAST_INDEX;
        break;
        case 'C':
        case 'c':
            mColoringChoice = CLOSEST_CNT_INDEX;
        break;
        default : mColoringChoice = MIN_INDEX; break;
    }
    std::cout<<"Choose graph ordination: "<<std::endl;
    std::cout<<"INCREASE: I\t UP_DOWN: U\t CNT_HIGHEST_CONNECTION: C"<<std::endl;
    option = 'a';
    std::cin>>option;
    switch(option)
    {
        case 'I':
        case 'i':
            mGraphOrdination = INCREASE;
        break;
        case 'U':
        case 'u':
            mGraphOrdination = UP_DOWN;
        break;
        case 'C':
        case 'c':
            mGraphOrdination = CNT_HIGHEST_CONNECTION;
        break;
        default : mGraphOrdination = INCREASE; break;
    }

    DisplayGraphInfo();

    unsigned int anchorUpdate = ClearGraph();
    SetGraph();

    return anchorUpdate-mAnchors.size();
}

void Graph::DisplayGraphInfo()
{

    /*if(mPushAway) std::cout<<"DisplayGraphInfo mPushAway true"<<std::endl;
    else std::cout<<"DisplayGraphInfo mPushAway false"<<std::endl;
    int nada;std::cin>>nada;*/
    /// Atencao: opção VERY_BEST altera a opção para a heuristica de coloração
    std::cout<<"Setting Graph as : "<<std::endl;
    std::cout<<"mGraphType\t mColorOrder\t mColoringHeuristic\t mColoringChoice\t mGraphOrdination "<<std::endl;
    switch(mGraphType)
    {
        case CONTACTS         : std::cout<<"CONTACTS  \t"; break;
        case CONNECTED        : std::cout<<"CONNECTED  \t"; break;
        case ULTRA_CONNECTED  : std::cout<<"ULTRA_CONNECTED  \t"; break;
        case SIMPLE_CONNECTED : std::cout<<"SIMPLE_CONNECTED  \t"; break;
        case CONTACT_TO_POINT : std::cout<<"CONTACT_TO_POINT  \t"; break;
        default : std::cout<<"NONE\t"; break;
    }
    switch(mColorOrder)
    {
        case INITIAL   : std::cout<<"INITIAL \t"; break;
        case BEST      : std::cout<<"BEST    \t"; break;
        case VERY_BEST : std::cout<<"VERY_BEST \t"; break;
        default : std::cout<<"NONE\t"; break;
    }
    switch(mColoringHeuristic)
    {
        case FIRST_FIT : std::cout<<"FIRST_FIT\t"; break;
        case DFS       : std::cout<<"DFS   \t"; break;
        case LDO       : std::cout<<"LDO   \t"; break;
        case DFS_LDO   : std::cout<<"DFS_LDO\t"; break;
        default : std::cout<<"NONE\t"; break;
    }
    switch(mColoringChoice)
    {
        case MIN_INDEX          : std::cout<<"MIN_INDEX   \t"; break;
        case LAST_INDEX         : std::cout<<"LAST_INDEX  \t"; break;
        case CLOSEST_CNT_INDEX  : std::cout<<"CLOSEST_CNT_INDEX\t"; break;
        default : std::cout<<"NONE\t"; break;
    }
    switch(mGraphOrdination)
    {
        case INCREASE : std::cout<<"INCREASE"; break;
        case UP_DOWN  : std::cout<<"UP_DOWN"; break;
        case CNT_HIGHEST_CONNECTION  : std::cout<<"CNT_HIGHEST_CONNECTION"; break;
        default : std::cout<<"NONE\t"; break;
    }
    std::cout<<"\n"<<std::endl;
    std::cout<<"Show adjacency list? (y/n)"<<std::endl;
    char option = 'n';
    std::cin>>option;
    if(option == 'y') PrintAdjacencyList();

    std::cout<<"Show color indices? (y/n)"<<std::endl;
    option = 'n';
    std::cin>>option;
    if(option == 'y')
    {
        for(unsigned int i = 0; i < mAdjacencyList.size()-mAttractors.size(); i++)
        {
            int cnt = GetCNT(mAdjacencyList[i][0][0]);
            int ind = GetIndex(mAdjacencyList[i][0][0]);
            std::cout<<cnt<<"."<<ind<<"("<<mGraphColoring[i]<<")\t";
        }
    }
    std::cout<<"\n"<<std::endl;
}

std::vector<unsigned int> Graph::GraphColoringGreedy()
{
    std::vector<unsigned int> graphColoring;
    if(mAdjacencyList.size() == 0)
    {
        std::cout<<"Graph not computed. Press G"<<std::endl;
        int nada; std::cin>>nada;
        return graphColoring;
    }
    bool verbose = false;
    for(unsigned int i = 0; i < mAdjacencyList.size()-mAttractors.size(); i++)
    {
        graphColoring.push_back(0);
    }
    int last_color = 0;
    switch(mColoringHeuristic)
    {
        case FIRST_FIT :
        {
        for(unsigned int i = 0; i < graphColoring.size(); i++)
        {
            if(graphColoring[i] == 0)
            {
                graphColoring[i] = GetColor(i, &graphColoring, &mAdjacencyList, last_color);
                if(verbose)
                {
                    std::cout<<GetCNT(mAdjacencyList[i][0][0])<<"."<<GetIndex(mAdjacencyList[i][0][0])<<"("<<graphColoring[i]<<")\t";
                }
                last_color = graphColoring[i];
            }
        }
        if(verbose) std::cout<<std::endl;
        }
        break;
        case DFS :
        {
        for(unsigned int i = 0; i < graphColoring.size(); i++)
        {
            if(graphColoring[i] == 0)
            {
                VertexColoring(i, &graphColoring, verbose, last_color);
                // melhor não fazer assim pois pode dar problema quando se tem mais de uma componente conexa
                //last_color = graphColoring[i];
            }
        }
        if(verbose) std::cout<<std::endl;
        }
        break;
        case DFS_LDO:
        {
        unsigned int max_ind = 0;
        unsigned int max_degree = 0;
        for(unsigned int i = 0; i < mAdjacencyList.size()-mAttractors.size(); i++)
        {
            if(mAdjacencyList[i].size() > max_degree)
            {
                max_degree = mAdjacencyList[i].size();
                max_ind = i;
            }
        }

        for(unsigned int i = max_ind; i < graphColoring.size(); i++)
        {
            if(graphColoring[i] == 0)
            {
                VertexColoring(i, &graphColoring, verbose, last_color);
            }
        }
        for(unsigned int i = 0; i < max_ind; i++)
        {
            if(graphColoring[i] == 0)
            {
                VertexColoring(i, &graphColoring, verbose, last_color);
            }
        }
        if(verbose) std::cout<<std::endl;
        }
        break;
        case LDO :
        {
        if(verbose) PrintGraph(&mAdjacencyList);

        std::vector<unsigned int> graphColoringLDO = graphColoring;
        std::vector<std::vector<glm::vec2>> mAdjacencyListLDO;
        mAdjacencyListLDO = mAdjacencyList; // copiando lista

        sort(mAdjacencyListLDO.begin(), mAdjacencyListLDO.end()-mAttractors.size(), list_by_degree);
        if(verbose) PrintGraph(&mAdjacencyListLDO);
        /// colorindo em LDO
        for(unsigned int i = 0; i < graphColoringLDO.size(); i++)
        {
            if(graphColoringLDO[i] == 0)
            {
                for(unsigned int j = 0; j < mAdjacencyListLDO[i].size()-mAttractors.size(); j++)
                {
                    int adjIndex = SearchInList(mAdjacencyListLDO[i][j][0], &mAdjacencyListLDO);
                    if(graphColoringLDO[adjIndex] == 0)
                    {
                        graphColoringLDO[adjIndex] = GetColor(adjIndex, &graphColoringLDO, &mAdjacencyListLDO, last_color);
                        last_color = graphColoringLDO[adjIndex];
                        if(verbose)
                        {
                            std::cout<<GetCNT(mAdjacencyListLDO[adjIndex][0][0])<<"."<<GetIndex(mAdjacencyListLDO[adjIndex][0][0])<<"("<<graphColoring[adjIndex]<<")\t";
                        }
                    }
                }
            }
        }
        /// salvando as cores na ordem certa da lista de adjacencia original
        for(unsigned int i = 0; i < mAdjacencyListLDO.size(); i++)
        {
            int origListIndex = SearchInList(mAdjacencyListLDO[i][0][0], &mAdjacencyList);
            if(origListIndex > -1)
            {
                graphColoring[origListIndex] = graphColoringLDO[i];
            }
        }

        if(verbose)
        {
            std::cout<<std::endl;
            std::cout<<"\ngraphColoring"<<std::endl;
            for(unsigned int i = 0; i < mAdjacencyList.size()-mAttractors.size(); i++)
            {
                std::cout<<GetCNT(mAdjacencyList[i][0][0])<<".";
                std::cout<<GetIndex(mAdjacencyList[i][0][0])<<"(";
                std::cout<<mAdjacencyList[i].size()-1<<")(";
                std::cout<<graphColoring[i]<<")\t";
            }
            std::cout<<std::endl;
            std::cout<<std::endl;
            std::cout<<"graphColoringLDO"<<std::endl;
            for(unsigned int i = 0; i < mAdjacencyListLDO.size()-mAttractors.size(); i++)
            {
                std::cout<<GetCNT(mAdjacencyListLDO[i][0][0])<<".";
                std::cout<<GetIndex(mAdjacencyListLDO[i][0][0])<<" ";
                std::cout<<mAdjacencyListLDO[i].size()-1<<")(";
                std::cout<<graphColoringLDO[i]<<")\t";
            }
            std::cout<<std::endl;
            //int nada; std::cin>>nada;
        }
        FreeAdjacencyList(&mAdjacencyListLDO);
        }
        break;
        case BFS :
        {
        for(unsigned int i = 0; i < mAdjacencyList.size()-mAttractors.size(); i++)
        {
            if(graphColoring[i] == 0)
            {
                graphColoring[i] = GetColor(i, &graphColoring, &mAdjacencyList, last_color);
                last_color = graphColoring[i];
                if(verbose)
                {
                    std::cout<<GetCNT(mAdjacencyList[i][0][0])<<"."<<GetIndex(mAdjacencyList[i][0][0])<<"("<<graphColoring[i]<<")\t";
                }
                if(verbose) std::cout<<std::endl;
                for(unsigned int j = 1; j < mAdjacencyList[i].size()-mAttractors.size(); j++)
                {
                    for(unsigned int k = 0; k < mAdjacencyList.size()-mAttractors.size(); k++)
                    {
                        if(mAdjacencyList[k][0][0] == mAdjacencyList[i][j][0])
                        {
                            graphColoring[k] = GetColor(k, &graphColoring, &mAdjacencyList, last_color);
                            last_color = graphColoring[k];
                            if(verbose)
                            {
                                std::cout<<GetCNT(mAdjacencyList[k][0][0])<<"."<<GetIndex(mAdjacencyList[k][0][0])<<"("<<graphColoring[k]<<")"<<std::endl;
                            }
                            break;
                        }
                    }
                }
                last_color = graphColoring[i];
            }
        }
        }
        break;
        default :
            std::cout<<"No coloring heuristic selected"<<std::endl;
            return graphColoring;
    }
    if(verbose)
    {
        std::cout<<"Colors"<<std::endl;
        for(unsigned int i = 0; i < mAdjacencyList.size()-mAttractors.size(); i++)
        {
            std::cout<<GetCNT(mAdjacencyList[i][0][0])<<"."<<GetIndex(mAdjacencyList[i][0][0])<<"("<<graphColoring[i]<<")\t";
        }
        std::cout<<std::endl;
    }

    return graphColoring;
}

void Graph::VertexColoring(int v, std::vector<unsigned int> *colors, bool verbose, int last_color)
{
    int c = GetColor(v, colors, &mAdjacencyList, last_color);
    last_color = c;
    (*colors)[v] = c;
    if(verbose)
    {
        std::cout<<GetCNT(mAdjacencyList[v][0][0])<<"."<<GetIndex(mAdjacencyList[v][0][0])<<"("<<c<<")-"<<last_color<<"\t";
    }
    for(unsigned int i = 1; i < mAdjacencyList[v].size()-mAttractors.size(); i++)
    {
        //procurar na lista de adjacencia quem eh o 0.6 e passar o indice dele diretamente
        for(unsigned int j = 0; j < mAdjacencyList.size()-mAttractors.size(); j++)
        {
            if(mAdjacencyList[j][0][0] == mAdjacencyList[v][i][0])
            {
                if((*colors)[j] == 0)
                    VertexColoring(j, colors, verbose, last_color);
                break;
            }
        }
    }
}

int Graph::GetColor(int v, std::vector<unsigned int> *colors, std::vector<std::vector<glm::vec2>> *adj_list, int last_color)
{
    bool verbose = false;
    int c = 1;
    switch(mColoringChoice)
    {
        case MIN_INDEX : /// escolhe a cor de menor indice
        {
            while(CheckColor(c, v, colors, adj_list))
            {
                c++;
                if(c > mTotalCnts) break;
            }
        }
        break;
        case LAST_INDEX : /// escolhe a cor a partir do indice da cor dada ao último vértice colorido
        {
             if(last_color == 0) /// primeira cor a ser dada ao grafo
             {
                while(CheckColor(c, v, colors, adj_list))
                {
                    c++;
                    if(c > mTotalCnts) break;
                }
             }
             else
             {
                c = last_color;
                /// procurando a menor cor mais próxima
                while(CheckColor(c, v, colors, adj_list))
                {
                    c--;
                    if(c == 0) break;
                }
                if(c == 0)
                {
                    /// procurando a maior cor mais próxima
                    while(CheckColor(last_color, v, colors, adj_list))
                    {
                        last_color++;
                        if(last_color > mTotalCnts) break;
                    }
                    c = last_color;
                }
             }
        }
        break;
        case CLOSEST_CNT_INDEX : /// escolhe a cor observando a cor dos pontos mais próximos do mesmo CNT
        {
            /// verificando a cor do ponto acima e abaixo do mesmo CNT se houver.
            unsigned int colorPrev = 0;
            unsigned int colorNext = 0;
            if(verbose)
            {
                std::cout<<std::endl;
                std::cout<<"-1:  "<<GetCNT((*adj_list)[v][0][0]-1)<<"."<<GetIndex((*adj_list)[v][0][0]-1)<<std::endl;
                std::cout<<" 0:  "<<GetCNT((*adj_list)[v][0][0])  <<"."<<GetIndex((*adj_list)[v][0][0])  <<std::endl;
                std::cout<<"+1:  "<<GetCNT((*adj_list)[v][0][0]+1)<<"."<<GetIndex((*adj_list)[v][0][0]+1)<<std::endl;
            }

            for(unsigned int i = 0; i < colors->size(); i++)
            {
                if((*colors)[i] == 0) continue;

                if(verbose)
                {
                    std::cout<<GetCNT((*adj_list)[i][0][0])<<"."<<GetIndex((*adj_list)[i][0][0])<<"= ? ";
                    std::cout<<GetCNT((*adj_list)[v][0][0]-1)<<"."<<GetIndex((*adj_list)[v][0][0]-1)<<"= ? ";
                    std::cout<<GetCNT((*adj_list)[v][0][0]+1)<<"."<<GetIndex((*adj_list)[v][0][0]+1)<<std::endl;
                }

                if((*adj_list)[i][0][0] == (*adj_list)[v][0][0]-1) colorPrev = (*colors)[i];
                if((*adj_list)[i][0][0] == (*adj_list)[v][0][0]+1) colorNext = (*colors)[i];

                if(colorNext != 0 && colorPrev != 0) break;
            }
            if(verbose)
            {
                std::cout<<GetCNT((*adj_list)[v][0][0])<<"."<<GetIndex((*adj_list)[v][0][0])<<std::endl;
                std::cout<<"colorPrev  "<<colorPrev<<std::endl;
                std::cout<<"colorNext  "<<colorNext<<std::endl;
            }

            if(colorNext == 0 && colorPrev == 0)
            {
                while(CheckColor(c, v, colors, adj_list))
                {
                    c++;
                    ///if(c > mTotalCnts+1) break; /// qualquer cor
                }
            }
            if(colorNext != 0 && colorPrev != 0)
            {
                int great = -1;
                //int lesser = -1;
                if(colorNext >= colorPrev)
                {
                    great = colorNext;
                    //lesser = colorPrev;
                } else
                {
                    great = colorPrev;
                    //lesser = colorNext;
                }

                c = great;
                while(CheckColor(c, v, colors, adj_list))
                {
                    c--;
                    if(c == 0) break;
                }
                if(c == 0)
                {
                    c = great;
                    while(CheckColor(c, v, colors, adj_list))
                    {
                        c++;
                        ///if(c > mTotalCnts+1) break; /// qualquer cor
                    }
                }
            }
            if(colorNext == 0 && colorPrev != 0)
            {
                c = colorPrev;
                while(CheckColor(c, v, colors, adj_list))
                {
                    c--;
                    if(c == 0) break;
                }
                if(c == 0)
                {
                    c = colorPrev;
                    while(CheckColor(c, v, colors, adj_list))
                    {
                        c++;
                        ///if(c > mTotalCnts+1) break; /// qualquer cor
                    }
                }
            }
            if(colorNext != 0 && colorPrev == 0)
            {
                c = colorNext;
                while(CheckColor(c, v, colors, adj_list))
                {
                    c--;
                    if(c == 0) break;
                }
                if(c == 0)
                {
                    c = colorNext;
                    while(CheckColor(c, v, colors, adj_list))
                    {
                        c++;
                        ///if(c > mTotalCnts+1) break; /// qualquer cor
                    }
                }
            }


            //int nada;std::cin>>nada;
        }
        break;
    }


    return c;
}

double Graph::GetAllDisplacements()
{
    if(mControlPointDisplacement)
    {
        double sum = 0.0;
        for(unsigned int i = 0; i < mControlPointDisplacement->size; i++)
        {
            sum += abs(gsl_vector_get(mControlPointDisplacement, i));
        }
        return sum;
    }
    return 0.0;
}

unsigned int Graph::GetControlPointColor(int i)
{
    if(i >= 0 && i < (int)mGraphColoring.size())
    {
        return mGraphColoring[i];
    }
    return 0;
}

glm::vec2 Graph::GetGraphCPID(int vert, int neighbour)
{
    if(vert >= 0 && vert < (int)mAdjacencyList.size())
    {
        if(neighbour >= 0 && neighbour < (int)mAdjacencyList[vert].size())
        {
            return mAdjacencyList[vert][neighbour];
        }
    }
    return glm::vec2(-1.0 -1.0);
}


bool Graph::CheckColor(unsigned int c, int v,
                       std::vector<unsigned int> *colors,
                       std::vector<std::vector<glm::vec2>> *adj_list)
{
    /// em todos os vertices vizinhos
    for(unsigned int i = 1; i < (*adj_list)[v].size()-mAttractors.size(); i++)
    {
        /// buscar indice da cor
        for(unsigned int j = 0; j < (*adj_list).size()-mAttractors.size(); j++)
        {
            if((*adj_list)[j][0][0] == (*adj_list)[v][i][0])
            {
                if((*colors)[j] == c)
                {
                    return true;
                }
                break;
            }
        }
    }
    return false;
}

int Graph::GetGraphType()
{
    /*std::string type("");
    switch(mGraphType)
    {
        case CONTACTS: type = "CONTACTS"; break;
        case CONNECTED: type = "CONNECTED"; break;
        case ULTRA_CONNECTED: type = "ULTRA_CONNECTED"; break;
        case SIMPLE_CONNECTED: type = "SIMPLE_CONNECTED"; break;
        case CONTACT_TO_POINT: type = "CONTACT_TO_POINT"; break;
        default: break;
    }
    return type;*/
    return (int)mGraphType;
}
int Graph::GraphAttractors()
{
    /*std::string type("");
    switch(mAttractorType)
    {
        case MIDPOINT: type = "MIDPOINT"; break;
        case ONEPOINT: type = "ONEPOINT"; break;
        case EXTREMES: type = "EXTREMES"; break;
        default: break;
    }
    return type;*/
    return (int)mAttractorType;
}
int Graph::GraphAnchors()
{
    /*std::string type("");
    switch(mAnchorType)
    {
        case SUPERBLOCK: type = "SUPERBLOCK"; break;
        case GRAPH: type = "ONEPOINT"; break;
        default: break;
    }
    return type;*/
    return (int)mAnchorType;
}
int Graph::GraphColorOrder()
{
    /*std::string type("");
    switch(mColorOrder)
    {
        case INITIAL: type = "INITIAL"; break;
        case BEST: type = "BEST"; break;
        case VERY_BEST: type = "VERY_BEST"; break;
        default: break;
    }
    return type;*/
    return (int)mColorOrder;
}
int Graph::GraphListOrder()
{
    /*std::string type("");
    switch(mGraphOrdination)
    {
        case INCREASE: type = "INCREASE"; break;
        case UP_DOWN: type = "UP_DOWN"; break;
        case CNT_HIGHEST_CONNECTION: type = "CNT_HIGHEST_CONNECTION"; break;
        default: break;
    }
    return type;*/
    return (int)mGraphOrdination;
}
int Graph::GraphHeuristic()
{
    /*std::string type("");
    switch(mColoringHeuristic)
    {
        case FIRST_FIT: type = "FIRST_FIT"; break;
        case DFS: type = "DFS"; break;
        case LDO: type = "LDO"; break;
        case SDO: type = "SDO"; break;
        case IDO: type = "IDO"; break;
        case DFS_LDO: type = "DFS_LDO"; break;
        case BFS: type = "BFS"; break;
        default: break;
    }
    return type;*/
    return (int)mColoringHeuristic;
}
int Graph::GraphColorChoice()
{
    /*std::string type("");
    switch(mColoringChoice)
    {
        case MIN_INDEX: type = "MIN_INDEX"; break;
        case LAST_INDEX: type = "LAST_INDEX"; break;
        case CLOSEST_CNT_INDEX: type = "CLOSEST_CNT_INDEX"; break;
        default: break;
    }
    return type;*/
    return (int)mColoringChoice;
}
int Graph::GraphSolution()
{
    /*std::string type("");
    switch(mOrderSolution)
    {
        case ORIGINAL: type = "ORIGINAL"; break;
        case ORIGINAL_MAX: type = "ORIGINAL_MAX"; break;
        case ORIGINAL_MIN: type = "ORIGINAL_MIN"; break;
        case CRITICAL: type = "CRITICAL"; break;
        case DIRECT: type = "DIRECT"; break;
        case HYPOTENUSE: type = "HYPOTENUSE"; break;
        default: break;
    }
    return type;*/
    return (int)mOrderSolution;
}

void Graph::SaveGraph(std::string mFilePath)
{
    ///std::cout<<"SaveGraph"<<std::endl;
    std::ofstream outputFile(mFilePath, outputFile.app);
    outputFile<<"g\n";
    outputFile<<mPushAway<<"\n";

    outputFile<<mCriticalDistance<<" ";
    outputFile<<GetGraphType()<<" ";
    outputFile<<GraphAttractors()<<" ";
    outputFile<<GraphAnchors()<<" ";
    outputFile<<GraphColorOrder()<<" ";
    outputFile<<GraphListOrder()<<" ";
    outputFile<<GraphHeuristic()<<" ";
    outputFile<<GraphColorChoice()<<" ";
    outputFile<<GraphSolution()<<"\n";

    outputFile<<"t\n";
    outputFile<<mAttractors.size()<<"\n";
    outputFile<<mAttractorSphereIndex<<"\n";
    for(unsigned int i = 0; i < mAttractors.size(); i++)
    {
        outputFile<<mAttractors[i][0]<<" "<<mAttractors[i][1]<<" "<<mAttractors[i][2]<<"\n";
    }
    outputFile<<"a\n";
    outputFile<<mAnchors.size()<<"\n";
    outputFile<<mAnchorSphereIndex<<"\n";
    for(unsigned int i = 0; i < mAnchors.size(); i++)
    {
        outputFile<<mAnchors[i]<<" ";
    }
    outputFile<<"\n";

    for(unsigned int i = 0; i < mAdjacencyList.size(); i++)
    {
        if(i < mAdjacencyList.size() - mAttractors.size())
            outputFile<<mGraphColoring[i]<<" ";
        else
            outputFile<<"0 ";

        for(unsigned int j = 0; j < mAdjacencyList[i].size(); j++)
        {
            outputFile<<mAdjacencyList[i][j][0]<<" "<<mAdjacencyList[i][j][1]<<" ";
        }
        outputFile<<"\n";
    }

    outputFile<<"NanList ";
    if(mOrderSolution == DIRECT)
    {
        outputFile<<"DIR "<<mNanListDir.size()<<"\n";
        for(unsigned int i = 0; i < mNanListDir.size(); i++)
        {
            outputFile<<mNanListDir[i][0]<<" "<<mNanListDir[i][1]<<"\n";
        }
    }
    if(mOrderSolution == HYPOTENUSE)
    {
        outputFile<<"HYP "<<mNanListHyp.size()<<"\n";
        for(unsigned int i = 0; i < mNanListHyp.size(); i++)
        {
            outputFile<<mNanListHyp[i][0]<<" "<<mNanListHyp[i][1]<<mNanListHyp[i][2]<<" "<<mNanListHyp[i][3]<<"\n";
        }
    }

    outputFile<<"d\n";
    outputFile<<mControlPointDisplacement->size<<"\n";
    for(unsigned int i = 0; i < mControlPointDisplacement->size; i++)
    {
        outputFile<<gsl_vector_get(mControlPointDisplacement, i)<<" ";
    }
    outputFile<<"\n";

    outputFile.close();
}

bool Graph::LoadGraph(std::string mFilePath, int &line)
{
    std::ifstream inputFile(mFilePath);
    bool verbose = false;
    if(verbose) std::cout<<"LoadGraph  "<<line<<std::endl;

    for (int i = 0; i < line; i++)
    {
        std::string buffer = "";
        std::getline(inputFile, buffer);
    }
    //int nada;
    while(!inputFile.eof())
    {
        std::string buffer = "";
        std::getline(inputFile, buffer);
        line++;
        if(verbose) std::cout<<line<<": 1 mPushAway ---- "<<buffer<<std::endl;
        std::stringstream ss(buffer);
        ss >> mPushAway;

        std::getline(inputFile, buffer);
        line++;
        if(verbose) std::cout<<line<<": 2---- "<<buffer<<std::endl;
        ss.str(buffer);

        unsigned int g_type, att, anchor, c_order, l_order, heuristic, c_choice, solution;
        ss >> mCriticalDistance >> g_type >> att >> anchor >> c_order >> l_order >> heuristic >> c_choice >> solution;
        ss.clear();

        mGraphType = (GRAPH_TYPE) g_type;
        mAttractorType = (ATTRACTOR) att;
        mAnchorType = (ANCHOR) anchor;
        mColorOrder = (COLOR_ORDER) c_order;
        mGraphOrdination = (GRAPH_ORDER) l_order;
        mColoringHeuristic = (HEURISTIC) heuristic;
        mColoringChoice = (COLOR_CHOICE) c_choice;
        mOrderSolution = (SOLUTION) solution;

        std::getline(inputFile, buffer);
        line++;
        if(verbose) std::cout<<line<<":  3----- "<<buffer<<std::endl;
        //std::cin>>nada;

        if(buffer[0] == 't') /// attractors
        {
            //std::cout<<"attractors-------------------------"<<std::endl;
            std::getline(inputFile, buffer);
            line++;
            if(verbose) std::cout<<line<<":  "<<buffer<<std::endl;
            //std::cin>>nada;
            ss.str(buffer);
            unsigned int att_size;
            ss >> att_size;
            ss.clear();

            std::getline(inputFile, buffer);
            line++;
            if(verbose) std::cout<<line<<":  "<<buffer<<std::endl;
            //std::cin>>nada;
            ss.str(buffer);
            ss >> mAttractorSphereIndex;
            ss.clear();
            for(unsigned int i = 0; i < att_size; i++)
            {
                std::getline(inputFile, buffer);
                line++;
                if(verbose) std::cout<<line<<":  "<<buffer<<std::endl;
                //std::cin>>nada;
                ss.str(buffer);
                glm::vec3 attractor_pos;
                ss >> attractor_pos[0] >> attractor_pos[1] >> attractor_pos[2];
                mAttractors.push_back(attractor_pos);

                double mSphereSize = 4.0;
                mAttractorSpheres->PushSphere(attractor_pos, mAttractorColor, mSphereSize);

                ss.clear();
            }
        }
        std::getline(inputFile, buffer);
        line++;

        if(verbose) std::cout<<line<<":  "<<buffer<<std::endl;
        //std::cin>>nada;

        if(buffer[0] == 'a') /// anchors
        {
            //std::cout<<"anchors----------------------------"<<std::endl;
            std::getline(inputFile, buffer);
            line++;
            //if(verbose) std::cout<<line<<":  "<<buffer<<std::endl;
            //std::cin>>nada;
            ss.str(buffer);
            unsigned int anchor_size;
            ss >> anchor_size;
            ss.clear();

            std::getline(inputFile, buffer);
            line++;
            if(verbose) std::cout<<line<<":  "<<buffer<<std::endl;
            //std::cin>>nada;
            ss.str(buffer);
            ss >> mAnchorSphereIndex;
            ss.clear();

            std::getline(inputFile, buffer);
            line++;
            if(verbose) std::cout<<line<<": "<<buffer<<std::endl;
            //std::cin>>nada;
            char *token = strtok((char*) buffer.c_str()," ");
            while (token != NULL)
            {
                unsigned int anchor_cpid;
                ss.str(token);
                ss >> anchor_cpid;
                mAnchors.push_back(anchor_cpid);
                mContacts->SetAnchor(anchor_cpid, true);

                double mSphereSize = 4.0;
                unsigned int cnt = GetCNT(anchor_cpid);
                unsigned int ind = GetIndex(anchor_cpid);
                Vertex pt1 = (*mDrawNano)[cnt]->mInterpolator->ControlPoints()[ind];
                mAnchorSpheres->PushSphere(vec3(pt1[0], pt1[1], pt1[2]), mAnchorColor, mSphereSize);

                ss.clear();
                token = strtok(NULL," ");
            }
        }
        if(verbose)
        {
            std::cout<<"mAtt size  "<<mAttractors.size()<<std::endl;
            std::cout<<"mAnc size  "<<mAnchors.size()<<std::endl;
        }

        do
        {
            std::getline(inputFile, buffer);
            line++;
            if(verbose) std::cout<<line<<":  "<<buffer<<std::endl;
            if(buffer[0] == 'd') break;

            std::vector<glm::vec2> nodes;

            int cont = 0;
            char *token = strtok((char*) buffer.c_str()," ");
            glm::vec2 node(0.0, 0.0);
            while (token != NULL)
            {
                std::stringstream ss_(token);
                if(cont == 0)
                {
                    unsigned int color;
                    ss_ >> color;
                    if(color > 0) mGraphColoring.push_back(color);
                    cont++;
                    token = strtok(NULL," ");
                    continue;
                }
                else
                {
                    if(cont%2 == 1)
                    {
                        unsigned int cpid;
                        ss_ >> cpid;
                        node[0] = cpid;
                    }
                    else
                    {
                        double weight;
                        ss_ >> weight;
                        node[1] = weight;
                        nodes.push_back(node);
                    }
                }

                ss_.clear();
                cont++;

                token = strtok(NULL," ");
            }
            mAdjacencyList.push_back(nodes);
        } while(buffer[0] != 'd' || inputFile.eof() == true);

        if(verbose) PrintAdjacencyList();
        SetControlPointColor();
        ///std::cin>>nada;
        // deslocamentos
        std::getline(inputFile, buffer);
        line++;
        if(verbose) std::cout<<line<<":  "<<buffer<<std::endl;
        ///std::cin>>nada;

        if(mControlPointDisplacement == NULL)
        {
            std::stringstream ss2(buffer);
            unsigned int vec_size;
            ss2 >> vec_size;
            mControlPointDisplacement = gsl_vector_alloc(vec_size);
            gsl_vector_set_zero(mControlPointDisplacement);
            ss2.clear();
        }

        std::getline(inputFile, buffer);
        line++;
        int cont = 0;
        char *token = strtok((char*) buffer.c_str()," ");
        while (token != NULL)
        {
            std::stringstream ss_(token);
            double displ;
            ss_ >> displ;
            ss_.clear();
            gsl_vector_set(mControlPointDisplacement, cont, displ);
            cont++;

            token = strtok(NULL," ");
        }
        if(verbose)
        {
            std::cout<<"mControlPointDisplacement"<<std::endl;
            for(unsigned int i = 0; i < mControlPointDisplacement->size; i++)
            {
                std::cout<<gsl_vector_get(mControlPointDisplacement, i)<<"\t";
            }
            std::cout<<std::endl;
        }

        if(buffer[0] != 's') break;
    }

    bool eof = inputFile.eof();

    if(verbose)
    {
        if(eof) std::cout<<"Graph eof true "<<std::endl;
        else    std::cout<<"Graph eof false"<<std::endl;
    }
    inputFile.close();
    ///int nada; std::cin>>nada;

    return eof;
}

unsigned int Graph::GetControlPointID(int cnt, int ind)
{
    return cnt * segmentsPerCNT + ind -1;
}

int Graph::GetCNT(unsigned int id)
{
    return (id+1)/segmentsPerCNT;
}

int Graph::GetIndex(unsigned int id)
{
    return (id+1)%segmentsPerCNT;
}


}
