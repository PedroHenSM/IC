#include "Visualizer.h"

#include "Utility.h"
#include "Mouse.h"
#include "Keyboard.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <gsl/gsl_multiroots.h>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_blas.h>

#include <sys/stat.h>

namespace Library
{
    /**
    args[1]:
    r - run script
    m - manual
    l - load

    args[2]: densidade
    args[3]: semente
    args[4]: desvio padrao
    args[5]: distancia critica
    args[6]: metodo

    */
    Visualizer::Visualizer(std::string windowName, char **args)
        : Renderer(windowName),
          execution(MANUAL),
          //mFilePathAttributes(std::string(args[1])),
          //mFilePathControlPoints(std::string(args[2])),
          mDragging(false),
          mZooming(false),
          mDrawContactLine(false),
          mDrawSplineContactLine(false),
          mDrawGraph(false),
          mDrawAttractors(false),
          vis(SuperBlock::NONE),
          mSuperblockIterator(-1),
          mSegmentsPerCNT(0),
          mDistance(0.3),
          mIncrement(0.1),
          mSolveWholeForest(false),
          mSuperStart(0),
          mSuperBreak(0),
          mContactIterator(-1),
          mDuplicates(true),
          mNeedContactUpdate(false),
          mPushAwayCNTs(true),
          mOrderSolution(Graph::DIRECT)
    {
        mStartTime = clock();

        mCameraScale[0] = 0.002f;
        mCameraScale[1] = 0.002f;
        mCameraScale[2] = 0.002f;
        if(mSolveWholeForest)
        {
            std::cout<<"Solving whole forest."<<std::endl;
            mSuperStart = 0;
            mSuperBreak = (int)mForest->GetSuperBlocksSize();
        }
        std::string arg0(args[0]);
        std::string arg1(args[1]);

        std::size_t found;

        found = arg0.find("build/");
        if (found!=std::string::npos)
        {
            mDirectoryPath.append(arg0.substr(0, found));
        }

        //int nada;std::cin>>nada;

        int i = 1;
        if(arg1[0] == 'r')
        {
            execution = RUN_SCRIPT;
            SaveConfiguration(args, i);
        }
        else if(arg1[0] == 'l')
        {
            execution = LOAD;
            i = SetAttributteFilename(args, i);
            SetControlPointsFilename(args, i);
        }
        else
        {
            execution = MANUAL;
            SetAttributteFilename(args, i);
            i = SetControlPointsFilename(args, i);
            SetGraphConfig(args, i);
        }
    }

    Visualizer::~Visualizer()
    {
        mDrawNano.clear();
    }

    void Visualizer::Run()
    {
		//std::cout<<"Run"<<std::endl;
		if(execution == RUN_SCRIPT)
            Initialize();
		else
            Renderer::Run();
        /// tudo o que for chamado depois daqui só aparece depois que o programa for fechado
    }

    void Visualizer::Exit()
    {
        ///delete mSolidMaterial;

        // Deleta as variaveis estáticas do renderizador
        Text2D::Exit();
        Renderer::Exit();
    }

    void Visualizer::Initialize()
    {
	    //std::cout<<"Initialize"<<std::endl;
        mCamera = new OrbitCamera(*this);
		mComponents.push_back(mCamera);
		mServices.AddService(OrbitCamera::TypeIdClass(), mCamera);

		mControlPointsSpheres = new DrawableSpheres(*this, *mCamera);
		mControlPointsSpheres->SetEnabled(false);
		mComponents.push_back(mControlPointsSpheres);

		mIntersectionSpheres = new DrawableSpheres(*this, *mCamera);
		mIntersectionSpheres->SetEnabled(false);
		mComponents.push_back(mIntersectionSpheres);

		mAnchorSpheres = new DrawableSpheres(*this, *mCamera);
		mAnchorSpheres->SetEnabled(true);
		mComponents.push_back(mAnchorSpheres);

		mAttractorSpheres = new DrawableSpheres(*this, *mCamera);
		mAttractorSpheres->SetEnabled(true);
		mComponents.push_back(mAttractorSpheres);

        if(execution != RUN_SCRIPT) Renderer::Initialize();

        mCamera->SetPosition(0.0f, 0.0f, 3.0f);

        if(execution != RUN_SCRIPT)
        {
            mSolidMaterial = new NanotubeMaterial();
            mSolidMaterial->Initialize();

            Text2D::Initialize(this);
        }

        ReadData();

        mSegmentsPerCNT = mDrawNano[0]->mInterpolator->ControlPointsNumber();
        ///int nada; std::cin>>nada;
        if(execution == RUN_SCRIPT) RunScript();
        ///std::cin>>nada;
        //DisplayMenu();
    }

    void Visualizer::Update(const RendererTime& rendererTime)
    {
        if(mMouse->IsButtonHeldDown(MouseButtonsRight) && mMouse->IsButtonHeldDown(MouseButtonsLeft))
        {
            //if(mMouse->IsButtonHeldDown(MouseButtonsMiddle))
            vec2 pan(-mMouse->deltaX() / mScreenWidth, -mMouse->deltaY() / mScreenWidth);
            mCamera->Pan(pan);
        }
        else
        {
            if(mMouse->IsButtonDown(MouseButtonsRight))
            {
                static float dxAccum = 0;
                if(mZooming)
                {
                    dxAccum += mMouse->deltaX();
                    float zoomFactor = -mMouse->deltaX()/mScreenWidth;
                    mCamera->Zoom(zoomFactor);
                }
                else
                {
                    dxAccum = 0;
                }

                mZooming = true;
            }
            if(mMouse->IsButtonUp(MouseButtonsRight)) mZooming = false;
            if(mMouse->IsButtonHeldDown(MouseButtonsLeft))
            {
                vec2 orbit(-mMouse->deltaX()/ mScreenWidth, -mMouse->deltaY()/ mScreenWidth);
                mCamera->Orbit(orbit);
            }
        }

        Renderer::Update(rendererTime);
    }

    void Visualizer::Draw(const RendererTime& rendererTime)
    {
        Renderer::Draw(rendererTime);
        // BUG Draw Line
        // Desabilita o DEPTH_TEST para que as linhas aparecam sobre os cilindros
        glDisable(GL_DEPTH_TEST);
        glLineWidth(3.0f);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadMatrixf(&mCamera->ViewProjectionMatrix()[0][0]);
        glScalef(mCameraScale[0], mCameraScale[1], mCameraScale[2]);
        if(mDrawContactLine)
        {
            mForest->DrawContacts();
        }

        if(mDrawGraph)
        {
            mForest->DrawSuperblocksGraphs(mDrawAttractors);
        }

        double size_ = 100.0;
        glBegin(GL_LINES);
            glColor3d(1.0, 0.0, 0.0);
            glVertex3d(0.0, 0.0, 0.0);
            glVertex3d(size_, 0.0, 0.0);
            glColor3d(0.0, 1.0, 0.0);
            glVertex3d(0.0, 0.0, 0.0);
            glVertex3d(0.0, size_, 0.0);
            glColor3d(0.0, 0.0, 1.0);
            glVertex3d(0.0, 0.0, 0.0);
            glVertex3d(0.0, 0.0, size_);
        glEnd();

        glPopMatrix();



        glLineWidth(1.0f);
        glEnable(GL_DEPTH_TEST);


        /*if(contacts.size() > 0)
        {
            Text2D::Print(mScreenWidth-300, mScreenHeight-32, 32, vec3(0.0), (char*)"%d contact points");
        }*/

        //vec3 pos = mCamera->Position();
        //Text2D::Print(12, mScreenHeight-24, 24, vec3(0.0), (char*)"x:%.3f y:%.3f z:%.3f", pos.x, pos.y, pos.z);
    }

    void Visualizer::Resize(int width, int height)
    {
        Renderer::Resize(width, height);
        mCamera->SetAspectRatio(static_cast<float>(width)/height);
    }///1480469433

    void Visualizer::ReadData()
    {
        mForest = new Forest(mAttractorSpheres, mAnchorSpheres, mControlPointsSpheres, (int) execution, mGraphCriticalDistance);
        mForest->ConfigureGraph(Graph::MIDPOINT, Graph::SUPERBLOCK, Graph::ULTRA_CONNECTED,
                   Graph::FIRST_FIT, Graph::BEST, Graph::CLOSEST_CNT_INDEX,
                   Graph::CNT_HIGHEST_CONNECTION, mOrderSolution);
        //if(IsSolvedForestFile())
        if(execution == LOAD)
        {
            std::cout<<"LoadVisualizer"<<std::endl;
            LoadVisualizer();
        }
        else
        {
            /*mDrawNano = mForest->ReadData(Utility::GetPath(mFilePathAttributes),
                                  Utility::GetPath(mFilePathControlPoints),
                                  this, mCamera, mSolidMaterial);*/
            mDrawNano = mForest->ReadData(mFilePathAttributes,
                                  mFilePathControlPoints,
                                  this, mCamera, mSolidMaterial);
        }
        /// A montagem do grafo deve respeitar a distância usada na busca por contatos
        mDistance = mGraphCriticalDistance;

        for(unsigned int i = 0; i < mDrawNano.size(); i++)
        {
            DrawableNanotube* dCNT = mDrawNano[i];
            mComponents.push_back(dCNT);
            double distortion = dCNT->mInterpolator->ArcLength();
            mInitialCNTDistortion.push_back(distortion);
        }
        glm::vec3 focus = mForest->GetInitialCameraFocus();
        mCamera->LookAt(focus);
    }

    void Visualizer::Input(int key, int scanCode, int action, int mod)
    {
        {
        if (mKeyboard->IsKeyDown(GLFW_KEY_Q)) /// Display Menu
        {
            DisplayMenu();
        }
        if (mKeyboard->IsKeyDown(GLFW_KEY_U)) /// Decrease
        {
            mDistance -= mIncrement;
            if(FEQUAL(mDistance, 0.0) || mDistance < 0.0) mDistance = 0.0; // para não aparecer alguma coisa e-17 em vez de zero
            std::cout<<"Contact distance: "<<mDistance<<std::endl;
            mNeedContactUpdate = true;
            mForest->mContacts->SetContactDistance(mDistance);
        }
        if (mKeyboard->IsKeyDown(GLFW_KEY_I)) /// Increase
        {
            mDistance += mIncrement;
            if(FEQUAL(mDistance, 0.0)) mDistance = 0.0;
            std::cout<<"Contact distance: "<<mDistance<<std::endl;
            mNeedContactUpdate = true;
            mForest->mContacts->SetContactDistance(mDistance);
        }
        if (mKeyboard->IsKeyDown(GLFW_KEY_J)) /// Decrease mCriticalDistance
        {
            mCriticalDistance -= mIncrement/10.0;
            if(FEQUAL(mCriticalDistance, 0.0) || mCriticalDistance < 0.0) mCriticalDistance = 0.0; // para não aparecer alguma coisa e-17 em vez de zero
            std::cout<<"Critical distance: "<<mCriticalDistance<<std::endl;
            std::cout<<"Clear graph to see changes. "<<std::endl;
            mForest->mContacts->SetCriticalDistance(mCriticalDistance);
        }
        if (mKeyboard->IsKeyDown(GLFW_KEY_K)) /// Increase mCriticalDistance
        {
            mCriticalDistance += mIncrement/10.0;
            if(FEQUAL(mCriticalDistance, 0.0)) mCriticalDistance = 0.0;
            std::cout<<"Critical distance: "<<mCriticalDistance<<std::endl;
            std::cout<<"Clear graph to see changes. "<<std::endl;
            mForest->mContacts->SetCriticalDistance(mCriticalDistance);
        }
        if (mKeyboard->IsKeyDown(GLFW_KEY_D)) /// Compute contacts duplicates or not
        {
            mDuplicates = !mDuplicates;
            if(mDuplicates)
                std::cout<<"Computing duplicates in contact look up."<<std::endl;
            else std::cout<<"No duplicates in contact look up."<<std::endl;
            mForest->mContacts->IncludeDuplicates(mDuplicates);
            mNeedContactUpdate = true;
        }
        if (mKeyboard->IsKeyDown(GLFW_KEY_C)) /// Contact search
		{
		    if(mForest->mContacts->GetTotalContacts() == 0 || mNeedContactUpdate == true)
            {
                ClearSpheres(mIntersectionSpheres);
                mForest->ContactLookUp(mIntersectionSpheres);
                mForest->mContacts->SaveContactList(GetForestSolutionFilename("contacts/contacts_b4_"));
                mNeedContactUpdate = false;
                std::cout<<"Total contatos: "<<mForest->mContacts->GetTotalContacts()<<std::endl;
                if(execution == LOAD)
                {
                    std::string remainingContacts(mFilePathControlPoints);
                    std::string toBeReplaced("_solution");
                    std::string replaceTo("_remaining");

                    size_t start = remainingContacts.find(toBeReplaced);
                    if(start != std::string::npos)
                    {
                        size_t end_ = toBeReplaced.size();
                        remainingContacts.replace(start, end_, replaceTo);
                        CompareContacts(remainingContacts);
                    }
                }
            }
            else
            {
                std::cout<<"Lista de contatos ja montada. Nada a fazer."<<std::endl;
            }
		}
        if (mKeyboard->IsKeyDown(GLFW_KEY_N)) /// Next
        {
            int conts = mForest->mContacts->GetTotalContacts();
            if(conts > 0)
            {
                mContactIterator++;
                if(mContactIterator < 0) mContactIterator = conts-1;
                if(mContactIterator >= conts) mContactIterator = mContactIterator%conts;

                if(mContactIterator >= 0 && mContactIterator < conts)
                {
                    mForest->mContacts->PrintContact(mContactIterator);
                    glm::vec3 focus = mForest->GetContactCameraFocus(mContactIterator);
                    mCamera->LookAt(focus);
                }

            }
        }
        if (mKeyboard->IsKeyDown(GLFW_KEY_B)) /// Back
        {
            int conts = mForest->mContacts->GetTotalContacts();
            if(conts > 0)
            {
                mContactIterator--;
                if(mContactIterator < 0) mContactIterator = conts-1;
                if(mContactIterator >= conts) mContactIterator = mContactIterator%conts;

                if(mContactIterator >= 0 && mContactIterator < conts)
                {
                    mForest->mContacts->PrintContact(mContactIterator);
                    glm::vec3 focus = mForest->GetContactCameraFocus(mContactIterator);
                    mCamera->LookAt(focus);
                }

            }

        }
        if(key == GLFW_KEY_L && action == GLFW_PRESS) /// Draw Line
        {
            static bool drawLines = false;

            if(!drawLines)
                glEnable(GL_DEPTH_TEST);
            else
                glDisable(GL_DEPTH_TEST);

            for(RendererComponent *dc : mComponents)
            {
                DrawableNanotube *dn = dynamic_cast<DrawableNanotube *>(dc);
                if(dn)
                {
                    dn->SetDrawLine(!drawLines);
                }
            }

            mControlPointsSpheres->SetEnabled(!drawLines);
            drawLines = !drawLines;
        }
        if(key == GLFW_KEY_P && action == GLFW_PRESS) /// Draw control points
        {
            mControlPointsSpheres->SetEnabled(!mControlPointsSpheres->Enabled());

            //mDrawNano[0]->mInterpolator->UpdateControlPoint(5, 0, 0, 0);
            mDrawNano[0]->NeedUpdate(true);
        }
        if(key == GLFW_KEY_W && action == GLFW_PRESS) /// Wireframe
        {
            static bool wireframe = false;
            if(!wireframe)
            {
                glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
                wireframe = true;
            }
            else
            {
                glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
                wireframe = false;
            }
        }
        /// ALTERNA ENTRE OS MODOS DE VISUALIZAÇÂO DOS PONTOS DE CONTATO ENTRE SEGMENTOS DE RETA
        if(key == GLFW_KEY_V && action == GLFW_PRESS)
        {
            if(!mDrawContactLine && mSolidMaterial->GetDrawMode() == DrawModeContacts)
            {
                // Desenha linhas de contato
                mDrawContactLine = true;
                mIntersectionSpheres->SetEnabled(true);
            }
            else if(mDrawContactLine && mSolidMaterial->GetDrawMode() == DrawModeContacts)
            {
                // Apaga a cor do material e deixa a cor do CNT
                mSolidMaterial->SetDrawMode(DrawModeSolidColor);
            }
            else if( mDrawContactLine && mSolidMaterial->GetDrawMode() == DrawModeSolidColor)
            {
                // Desbilita tudo
                mDrawContactLine = false;
                mIntersectionSpheres->SetEnabled(false);
            }
            else
            {
                // Desenha solidos. Com a cor vermelha depois de buscar contatos
                mSolidMaterial->SetDrawMode(DrawModeContacts);
            }
        }
        if(mKeyboard->IsKeyDown(GLFW_KEY_Z)) /// Clearing superblocks
        {
            std::cout<<"Clearing superblocks... ";
            mForest->ClearSuperblocks();
            ClearSpheres(mAnchorSpheres);
            ClearSpheres(mAttractorSpheres);
            for(unsigned int i = 0; i < mForest->mContacts->GetTotalControlPoints(); i++)
            {
                mForest->mContacts->SetAnchor(i, false);
            }
            mSuperStart = 0;
            mSuperBreak = 0;
            mNeedContactUpdate = true;
            std::cout<<"Done"<<std::endl;
        }
        if(mKeyboard->IsKeyDown(GLFW_KEY_M)) /// Defining blocks and superblocks and setting its visualization
        {
            if(mForest->GetSuperBlocksSize() == 0)
            {
                mForest->SetSuperBlocks();
                if(mSolveWholeForest)
                {
                    mSuperStart = 0;
                    mSuperBreak = mForest->GetSuperBlocksSize();
                }
                else
                {
                    if(mSuperblockIterator < 0)
                    {
                        mSuperStart = 0;
                        mSuperBreak = 0;
                    }
                    else
                    {
                        mSuperStart = mSuperblockIterator;///53;//39;//25;//28;//12;//2;//37;
                        mSuperBreak = mSuperStart+1;

                    }
                }
            }
            switch(vis)
            {
                case SuperBlock::NONE :
                {
                    vis = SuperBlock::BLOCK;
                    std::cout<<"Showing blocks"<<std::endl;
                }
                break;
                case SuperBlock::BLOCK :
                {
                    vis = SuperBlock::SUPERBLOCK;
                    std::cout<<"Showing superblocks"<<std::endl;
                }
                break;
                case SuperBlock::SUPERBLOCK :
                {
                    vis = SuperBlock::CONTACTS;
                    std::cout<<"Showing contacts"<<std::endl;
                }
                break;
                case SuperBlock::CONTACTS :
                {
                    vis = SuperBlock::NONE;
                    std::cout<<"Clearing CNTs"<<std::endl;
                }
                break;
            }

            mForest->SetVisualization(vis);
        }
        if(mKeyboard->IsKeyDown(GLFW_KEY_T)) /// Previous superblock
        {
            int supers = (int)mForest->GetSuperBlocksSize();
            if(supers > 0)
            {
                mSuperblockIterator--;
                if(mSuperblockIterator < 0) mSuperblockIterator = supers-1;
                if(mSuperblockIterator >= supers) mSuperblockIterator = mSuperblockIterator%supers;

                if(mSuperblockIterator >= 0 && mSuperblockIterator < supers)
                {
                    std::cout<<"Looking at superblock "<<mSuperblockIterator<<std::endl;
                    glm::vec3 focus = mForest->GetSuperblockCameraFocus((unsigned int)mSuperblockIterator);
                    mCamera->LookAt(focus);
                }
                if(!mSolveWholeForest)
                {
                    mSuperStart = mSuperblockIterator;///53;//39;//25;//28;//12;//2;//37;
                    mSuperBreak = mSuperStart+1;
                }
                else
                {
                    mSuperStart = 0;
                    mSuperBreak = supers;
                }
            }
            else
            {
                std::cout<<"No superblocks computed. Press G and M"<<std::endl;
            }
            //mCriticalDistance = 0.3;
            //mForest->mContacts->SetCriticalDistance(mCriticalDistance);
        }
        if(mKeyboard->IsKeyDown(GLFW_KEY_Y)) /// Next superblock
        {
            int supers = (int)mForest->GetSuperBlocksSize();
            if(supers > 0)
            {
                mSuperblockIterator++;
                if(mSuperblockIterator < 0) mSuperblockIterator = supers-1;
                if(mSuperblockIterator >= supers) mSuperblockIterator = mSuperblockIterator%supers;

                if(mSuperblockIterator >= 0 && mSuperblockIterator < supers)
                {
                    std::cout<<"Looking at superblock "<<mSuperblockIterator<<std::endl;
                    glm::vec3 focus = mForest->GetSuperblockCameraFocus((unsigned int)mSuperblockIterator);
                    mCamera->LookAt(focus);
                }
                if(!mSolveWholeForest)
                {
                    mSuperStart = mSuperblockIterator;
                    mSuperBreak = mSuperStart+1;
                }
                else
                {
                    mSuperStart = 0;
                    mSuperBreak = supers;
                }
            }
            else
            {
                std::cout<<"No superblocks computed. Press G and M"<<std::endl;
            }
            mCriticalDistance = 0.3;
            mForest->mContacts->SetCriticalDistance(mCriticalDistance);
        }
        if(mKeyboard->IsKeyDown(GLFW_KEY_E)) /// Add edge on superblock
        {
            int supers = (int)mForest->GetSuperBlocksSize();
            if(supers > 0 && mSuperblockIterator >= 0 && mSuperblockIterator < supers)
            {
                char option = 'z';
                std::cout<<"Add edge: A\tRemove edge: R\tClear this graph: C\tChange this graph: m\tShow Info: i"<<std::endl;
                std::cin>>option;
                switch(option)
                {
                    case 'a' :
                        std::cout<<"Add edge"<<std::endl;
                        mForest->AddEdgeOnSuperblock(mSuperblockIterator);
                    break;
                    case 'r' :
                        std::cout<<"Remove edge"<<std::endl;
                        mForest->RemoveEdgeOnSuperblock(mSuperblockIterator);
                    break;
                    case 'c' :
                        std::cout<<"Clear this graph"<<std::endl;
                        mForest->ClearSuperblockGraph(mSuperblockIterator);
                    break;
                    case 'm' :
                        std::cout<<"Change this graph"<<std::endl;
                        mForest->ResetSuperblockGraph(mSuperblockIterator);
                    break;
                    case 'i' :
                        std::cout<<"Show Info"<<std::endl;
                        mForest->DisplayGraphInfo(mSuperblockIterator);
                    break;
                    default : std::cout<<"No change"<<std::endl; break;
                }
            }
            else
            {
                if(supers <= 0) std::cout<<"No superblocks. Press M"<<std::endl;
                else if(mSuperblockIterator < 0 || mSuperblockIterator >= supers)
                {
                    std::cout<<"No superblock iterator. Press T(-) or Y(+): "<<mSuperblockIterator<<std::endl;
                }
                else if(mForest->IsSuperblockGraphComputed(mSuperblockIterator, mSuperblockIterator+1))
                {
                    char option = 'N';
                    std::cout<<"No superblock graph: "<<mSuperblockIterator<<std::endl;
                    std::cout<<"Wish to compute it now? Y/N "<<std::endl;
                    std::cin>>option;
                    if(option == 'Y' || option == 'y')
                    {
                        mForest->SetSuperBlocksGraphs(mSuperblockIterator, mSuperblockIterator+1);
                    }
                }
            }
        }
        }
        if(mKeyboard->IsKeyDown(GLFW_KEY_X)) /// Solve whole forest or not
        {
            mSolveWholeForest = !mSolveWholeForest;
            if(mSolveWholeForest)
            {
                std::cout<<"Solving whole forest."<<std::endl;
                mSuperStart = 0;
                mSuperBreak = (int)mForest->GetSuperBlocksSize();
            }
            else
            {
                std::cout<<"Solving superblock on focus."<<std::endl;
                mSuperStart = mSuperblockIterator;
                if(mSuperStart < 0) mSuperStart = 0;
                mSuperBreak = mSuperStart+1;
            }
        }

        if(mKeyboard->IsKeyDown(GLFW_KEY_F)) /// Correct CNT
        {
            mForest->SolveForest(mSuperStart, mSuperBreak);
            SaveVisualizer();
        }
        if(mKeyboard->IsKeyDown(GLFW_KEY_G)) /// Set Graph
        {
            /// se o grafo nao foi computado no intervalo, criar grafo
            /// caso contrario, apenas mudar a visualização
            if(!mForest->IsSuperblockGraphComputed(mSuperStart, mSuperBreak))
            {
                std::cout<<"Computing graph..."<<std::endl;
                mForest->SetSuperBlocksGraphs(mSuperStart, mSuperBreak);
            }
            if(mDrawGraph)
            {
                std::cout<<"Disabling Graph lines"<<std::endl;
                mDrawGraph = false;
            }
            else
            {
                std::cout<<"Enabling Graph lines"<<std::endl;
                mDrawGraph = true;
            }
        }
        if(mKeyboard->IsKeyDown(GLFW_KEY_A)) /// Draw attractors
        {
            if(mDrawAttractors)
            {
                std::cout<<"Disabling attractors lines"<<std::endl;
                mDrawAttractors = false;
            }
            else
            {
                std::cout<<"Enabling attractors lines"<<std::endl;
                mDrawAttractors = true;
            }
            mAttractorSpheres->SetEnabled(mDrawAttractors);
        }
        if(mKeyboard->IsKeyDown(GLFW_KEY_S)) /// Draw anchors
        {
            /*mAnchorSpheres->SetEnabled(!mAnchorSpheres->Enabled());
            if(!mAnchorSpheres->Enabled())
            {
                std::cout<<"Disabling anchors"<<std::endl;
            }
            else
            {
                std::cout<<"Enabling anchors"<<std::endl;
            }*/
            mForest->ComparePoints();
        }

        if(mKeyboard->IsKeyDown(GLFW_KEY_O))
        {
            RunScript();
        }

    }

    void Visualizer::CompareContacts(std::string remainingContacts)
    {
        std::cout<<"CompareContacts\n";
        std::cout<<"Mostra os contatos que existem no arquivo gerado pelo AG que nao foram encontrados na lista de contatos do Visualizador.\n";
        std::ifstream inputFile(remainingContacts);

        std::string buffer = "";
        std::getline(inputFile, buffer);
        ///if(buffer[0] == '#') continue;

        std::getline(inputFile, buffer);
        std::stringstream ss(buffer);
        int length;
        ss >>length;

        //for(int i = 0; i < length; i++)
        while(!inputFile.eof())
        {
            std::getline(inputFile, buffer);
            std::stringstream ss(buffer);
            int cnt1, ind1, cnt2, ind2;
            double radius1, radius2, distance1, distance2;

            ss >> cnt1 >> ind1 >> cnt2 >> ind2 >> radius1 >> radius2 >> distance1 >> distance2;
            //std::cout<<cnt1<<" "<<ind1<<" "<<cnt2<<" "<<ind2<<" "<<radius1<<" "<<radius2<<" "<<distance1<<" "<<distance2<<std::endl;
            bool exists1 = mForest->mContacts->ContactExists(cnt1, ind1  , cnt2, ind2);
            bool exists2 = mForest->mContacts->ContactExists(cnt1, ind1-1, cnt2, ind2);
            bool exists3 = mForest->mContacts->ContactExists(cnt1, ind1  , cnt2, ind2-1);
            bool exists4 = mForest->mContacts->ContactExists(cnt1, ind1-1, cnt2, ind2-1);

            if(!exists1 && !exists2 && !exists3 && !exists4)
            {
                std::cout<<cnt1<<"."<<ind1<<"-"<<cnt2<<"."<<ind2<<std::endl;
            }
        }

        inputFile.close();
    }

    void Visualizer::ClearSpheres(DrawableSpheres *spheres)
    {
        int totalSpheres = spheres->GetTotalSpheres();
        for(int i = 0; i < totalSpheres ; i++)
        {
            spheres->PopSphere();
        }
    }

    void Visualizer::SetControlPointSpheres(unsigned int super_start,unsigned int super_break)
    {
        for(unsigned int i = 0; i < mDrawNano.size(); i++)
        {
            std::vector<Vertex> cpt = mDrawNano[i]->mInterpolator->ControlPoints();
            for(unsigned int j = 1; j < cpt.size()-1; j++)
            {
                mControlPointsSpheres->PushSphere(vec3(cpt[j].x, cpt[j].y, cpt[j].z), vec3(1.0), 1.5);
            }
            cpt.clear();
        }
        mForest->SetSuperBlocksGraphsColors(super_start, super_break);
    }

    void Visualizer::DisplayMenu()
    {
        std::cout<<"*** Menu *** (press Q)"<<std::endl;
        std::cout<<"Contacts"<<std::endl;
        std::cout<<"\tc:\t Compute contacts"<<std::endl;
        std::cout<<"\td:\t Compute contacts' duplicates or not"<<std::endl;
        std::cout<<"\ti:\t Increase contact range"<<std::endl;
        std::cout<<"\tu:\t Decrease contact range"<<std::endl;
        std::cout<<"\tn:\t Next contact"<<std::endl;
        std::cout<<"\tb:\t Previous contact"<<std::endl;
        std::cout<<"Superblocks"<<std::endl;
        std::cout<<"\tm:\t Set superblocks"<<std::endl;
        std::cout<<"\tz:\t Clear superblocks"<<std::endl;
        std::cout<<"\tg:\t Set superblocks' graphs"<<std::endl;
        std::cout<<"\tf:\t Solve forest"<<std::endl;
        std::cout<<"\ty:\t Next superblock"<<std::endl;
        std::cout<<"\tt:\t Previous superblock"<<std::endl;
        std::cout<<"\te:\t Edge editing"<<std::endl;
        std::cout<<"Visualization"<<std::endl;
        std::cout<<"\tl:\t See CNTs line segments"<<std::endl;
        std::cout<<"\tw:\t See CNTs wireframe"<<std::endl;
        std::cout<<"\tv:\t Change forest visualization"<<std::endl;
        std::cout<<"\ta:\t Draw attractors lines"<<std::endl;
        std::cout<<"\ts:\t Draw anchors"<<std::endl;
        std::cout<<"\tp:\t Draw control points"<<std::endl;
    }

    std::string Visualizer::GetForestSolutionFilename(std::string base)
    {
        std::string filename("");
        std::size_t found = mFilePathControlPoints.find("forests/");
        if (found!=std::string::npos)
        {
            filename.append(mFilePathControlPoints.substr(0, found+8));
        }
        //filename.append("solution/forest_solution_");
        //filename.append("solution/forest_data_");
        filename.append(base);
        filename.append(mForestSeed);
        filename.append("_");
        filename.append(mForest->GetSolutionMethod());
        filename.append(std::to_string(mGraphCriticalDistance).substr(0, 3));

        found = mFilePathControlPoints.find("_30_");
        if (found!=std::string::npos)
        {
            filename.append(mFilePathControlPoints.substr(found));
        }

        return filename;
    }

    void Visualizer::SaveVisualizer()
    {
        std::string filename = GetForestSolutionFilename("solution/forest_solution_");
        //std::cout<<filename<<std::endl;
        //int nada; std::cin>>nada;

        std::ofstream outputFile(filename);
        /// CNTs info
        outputFile<<mSegmentsPerCNT<<" ";
        outputFile<<mDistance<<" ";
        outputFile<<mIncrement<<" ";
        outputFile<<mCriticalDistance<<" ";
        outputFile<<mSolveWholeForest<<" ";
        outputFile<<mSuperStart<<" ";
        outputFile<<mSuperBreak<<" ";

        outputFile<<mDuplicates<<"\n";
        outputFile.close();

        mForest->SaveSolvedForest(filename);
        SaveForestData();
    }

    void GetHourMinuteSeconds(clock_t TimeDiff, int &hours, int &minutes, int &secs)
    {
        secs = 0;
        minutes = 0;
        hours = 0;
        secs = TimeDiff%60;
        if(secs < TimeDiff || secs == 0)
        {
            minutes = (TimeDiff-secs)/60;
            minutes = minutes%60;
            if(minutes < TimeDiff-secs)
            {
                hours = (TimeDiff-minutes*60-secs)/3600;
            }
        }
    }

    double Visualizer::GetDiedralAngle(int cnt, int ind, double &cosine)
    {
        double angle = 0.0;
        Vertex pos2 = mDrawNano[cnt]->mInterpolator->ControlPoints()[ind+1];
        Vertex pos1 = mDrawNano[cnt]->mInterpolator->ControlPoints()[ind];
        Vertex pos0 = mDrawNano[cnt]->mInterpolator->ControlPoints()[ind-1];

        Vertex diff1 = pos2-pos1;
        Vertex diff2 = pos1-pos0;
        diff1.Normalize();
        diff2.Normalize();

        cosine = diff1.x*diff2.x + diff1.y*diff2.y + diff1.z*diff2.z;
        if(FEQUAL(cosine, 0.0) == 1) return 90.0;
        if(FEQUAL(cosine, 1.0) == 1) return 0.0;
        angle = std::acos(cosine)*180.0/M_PI;
        return angle;
    }

    void Visualizer::SaveForestData()
    {
        mEndTime = clock();
        clock_t TimeDiff = (mEndTime - mStartTime)/CLOCKS_PER_SEC;
        int secs = 0, minutes = 0, hours = 0;
        GetHourMinuteSeconds(TimeDiff, hours, minutes, secs);

        std::cout<<"TimeDiff  "<<TimeDiff<<std::endl;
        std::cout<<hours<<":"<<minutes<<":"<<secs<<std::endl;

        std::string filename = GetForestSolutionFilename("data/forest_data_");

        /// Abrindo arquivo
        std::ofstream outputFile(filename);

        outputFile<<mForestSeed<<"\t# semente da floresta\n";
        outputFile<<mForestDensity<<"\t# densidade da floresta\n";
        outputFile<<mForestStdDev<<"\t# desvio padrao da floresta\n";

        outputFile<<mForest->mContacts->GetTotalContacts()<<"\t# total contacts\n";
        if(mDuplicates)
            outputFile<<"true\t# duplicates\n";
        else
            outputFile<<"false\t# duplicates\n";

        outputFile<<TimeDiff<<"\t# tempo de execucao secs\n";
        outputFile<<hours<<" "<<minutes<<" "<<secs<<"\t# tempo de execucao em horas minutos\n";

        outputFile<<mForest->GetSuperBlocksSize()<<"\t# total superblocos\n";
        outputFile<<mGraphCriticalDistance<<"\t# Distancia critica usada para resolver\n";
        outputFile<<mSegmentsPerCNT<<"\t# mSegmentsPerCNT\n";

        if(mAttractorType == Graph::MIDPOINT) outputFile<<"MIDPOINT\t# mAttractorType\n";
        if(mAttractorType == Graph::ONEPOINT) outputFile<<"ONEPOINT\t# mAttractorType\n";
        if(mAttractorType == Graph::EXTREMES) outputFile<<"EXTREMES\t# mAttractorType\n";

        if(mAnchorType == Graph::SUPERBLOCK)    outputFile<<"SUPERBLOCK\t# mAnchorType\n";
        if(mAnchorType == Graph::GRAPH)         outputFile<<"GRAPH\t# mAnchorType\n";

        if(mGraphType == Graph::CONTACTS)       outputFile<<"CONTACTS\t# mGraphType\n";
        if(mGraphType == Graph::CONNECTED)      outputFile<<"CONNECTED\t# mGraphType\n";
        if(mGraphType == Graph::ULTRA_CONNECTED) outputFile<<"ULTRA_CONNECTED\t# mGraphType\n";
        if(mGraphType == Graph::SIMPLE_CONNECTED) outputFile<<"SIMPLE_CONNECTED\t# mGraphType\n";
        if(mGraphType == Graph::CONTACT_TO_POINT) outputFile<<"CONTACT_TO_POINT\t# mGraphType\n";

        if(mColorOrder == Graph::INITIAL)   outputFile<<"INITIAL \t# mColorOrder\n";
        if(mColorOrder == Graph::BEST)      outputFile<<"BEST\t\t# mColorOrder\n";
        if(mColorOrder == Graph::VERY_BEST) outputFile<<"VERY_BEST\t# mColorOrder\n";

        if(mGraphOrdination == Graph::INCREASE) outputFile<<"INCREASE\t# mGraphOrdination\n";
        if(mGraphOrdination == Graph::UP_DOWN)  outputFile<<"UP_DOWN\t# mGraphOrdination\n";
        if(mGraphOrdination == Graph::CNT_HIGHEST_CONNECTION) outputFile<<"CNT_HIGHEST_CONNECTION # mGraphOrdination\n";

        if(mColoringHeuristic == Graph::FIRST_FIT)  outputFile<<"FIRST_FIT\t# mColoringHeuristic\n";
        if(mColoringHeuristic == Graph::DFS)        outputFile<<"DFS\t\t# mColoringHeuristic\n";
        if(mColoringHeuristic == Graph::DFS_LDO)    outputFile<<"DFS_LDO\t# mColoringHeuristic\n";
        if(mColoringHeuristic == Graph::BFS)        outputFile<<"BFS\t\t# mColoringHeuristic\n";

        if(mColoringChoice == Graph::MIN_INDEX)     outputFile<<"MIN_INDEX\t# mColoringHeuristic\n";
        if(mColoringChoice == Graph::LAST_INDEX)    outputFile<<"LAST_INDEX\t# mColoringHeuristic\n";
        if(mColoringChoice == Graph::CLOSEST_CNT_INDEX) outputFile<<"CLOSEST_CNT_INDEX # mColoringHeuristic\n";

        if(mOrderSolution == Graph::ORIGINAL)       outputFile<<"ORIGINAL\t# mOrderSolution\n";
        if(mOrderSolution == Graph::ORIGINAL_MAX)   outputFile<<"ORIGINAL_MAX\t# mOrderSolution\n";
        if(mOrderSolution == Graph::ORIGINAL_MIN)   outputFile<<"ORIGINAL_MIN\t# mOrderSolution\n";
        if(mOrderSolution == Graph::CRITICAL)       outputFile<<"CRITICAL\t# mOrderSolution\n";
        if(mOrderSolution == Graph::DIRECT)         outputFile<<"DIRECT\t# mOrderSolution\n";
        if(mOrderSolution == Graph::HYPOTENUSE)     outputFile<<"HYPOTENUSE\t# mOrderSolution\n";

        outputFile<<"# CNT: distorcao da solucao, distorcao original, diferenca de distorcoes e raio\n";
        double total_distortion = 0;
        double total_no_module = 0;
        for(unsigned int i = 0; i < mDrawNano.size(); i++)
        {
            double arcLength = mDrawNano[i]->mInterpolator->ArcLength();
            double distortionDiff = arcLength-mInitialCNTDistortion[i];
            double radius = mDrawNano[i]->Radius();
            outputFile<<arcLength<<"\t"<<mInitialCNTDistortion[i]<<"\t"<<distortionDiff<<"\t"<<radius<<"\t# "<<i<<"\n";
            total_distortion += abs(distortionDiff);
            total_no_module += distortionDiff;
        }
        outputFile<<total_distortion<<"\t# Soma do modulo da diferenca das distorcoes em toda a floresta\n";
        outputFile<<total_no_module<<"\t# Soma sem modulo da diferenca das distorcoes em toda a floresta\n";

        outputFile<<"# Soma do deslocamento de cada CNT\n";
        double forest_sum = 0;
        double forest_sum2 = 0;
        for(unsigned int i = 0; i < mDrawNano.size(); i++)
        {
            double cnt_sum = 0;
            double cnt_sum2 = 0;
            unsigned int total = mDrawNano[i]->mInterpolator->ControlPointsNumber();
            for(unsigned int j = 0; j < total; j++)
            {
                Vertex pos = mDrawNano[i]->mInterpolator->ControlPoints()[j];
                cnt_sum += abs(pos.z);
                cnt_sum2 += pos.z;
            }
            outputFile<<cnt_sum<<"\t"<<cnt_sum2<<"\t# "<<i<<"\n";
            forest_sum += cnt_sum;
            forest_sum2 += cnt_sum2;
        }
        outputFile<<forest_sum<<"\t"<<forest_sum2<<"\t# Soma dos deslocamentos da floresta. Com e sem modulo\n";

        outputFile<<"# Angulo diedral em graus e radianos. Cosseno\n";
        for(unsigned int cnt = 0; cnt < mDrawNano.size(); cnt++)
        {
            unsigned int total = mDrawNano[cnt]->mInterpolator->ControlPointsNumber();
            for(unsigned int ind = 0; ind < total; ind++)
            {
                double cosine = 0.0;
                double angle = GetDiedralAngle(cnt, ind, cosine);
                outputFile<<angle<<" "<<angle*M_PI/180.0<<" "<<cosine<<"\t# "<<cnt<<"."<<ind<<"\n";
            }
        }

        for(unsigned int i = 0; i < mForest->GetSuperBlocksSize(); i++)
        {
            outputFile<<"# Superblock "<<i<<"\n";
            outputFile<<mForest->GetBlocksSize(i)<<"\t# numero de blocos no superbloco\n";
            outputFile<<mForest->GetGraphSize(i)<<"\t# numero de nos no grafo\n";
            outputFile<<mForest->GetGraphEdges(i)<<"\t# numero de arestas no grafo\n";
            outputFile<<mForest->GetGraphMaxColor(i)<<"\t# cor de maior indice\n";
            outputFile<<mForest->GetGraphColorPermutationIndex(i)<<"\t# permutacao que resolveu ou nao a floresta\n";
            outputFile<<mForest->GetGraphColorTotalPermutation(i)<<"\t# todas as permutacoes\n";

            std::vector<glm::vec4> mSegmentsInContact = mForest->GetContactsSize(i);
            outputFile<<mSegmentsInContact.size()<<"\t# Numero de segmentos em contato\n";
            outputFile<<"# cpid1, cpid2, distancia original, distancia atual, com e sem subtrair os raios\n";
            for(unsigned int j = 0; j < mSegmentsInContact.size(); j++)
            {
                int cnt1 = GetCNT(mSegmentsInContact[j].x);
                int ind1 = GetIndex(mSegmentsInContact[j].x);
                int cnt2 = GetCNT(mSegmentsInContact[j].y);
                int ind2 = GetIndex(mSegmentsInContact[j].y);
                outputFile<<cnt1<<" "<<ind1<<" "<<cnt2<<" "<<ind2<<" "<<mSegmentsInContact[j].z<<" "<<mSegmentsInContact[j].w<<" ";
                double radius1 = mDrawNano[cnt1]->Radius();
                double radius2 = mDrawNano[cnt2]->Radius();
                outputFile<<mSegmentsInContact[j].z-radius1-radius2<<" "<<mSegmentsInContact[j].w-radius1-radius2;
                if(mSegmentsInContact[j].w-radius1-radius2 < mCriticalDistance)
                {
                    outputFile<<" # CONTATO\n";
                }
                else outputFile<<"\n";
            }

            int components = mForest->GetTotalComponents(i);
            outputFile<<components<<"\t# todas as componentes\n";
            for(unsigned int j = 0; j < (unsigned int)components; j++)
            {
                outputFile<<mForest->GetOrderMatrixConditioning(i, j)<<"\t# condicionamento da matriz de ordem\n";
            }

        }

        outputFile.close();
    }

    void Visualizer::LoadVisualizer()
    {
        std::ifstream inputFile(Utility::GetPath(mFilePathControlPoints));

        inputFile >> mSegmentsPerCNT >> mDistance >> mIncrement >> mCriticalDistance >> mSolveWholeForest>> mSuperStart >> mSuperBreak >> mDuplicates;

        inputFile.close();

        mDrawNano = mForest->LoadSolvedForest(mFilePathAttributes, mFilePathControlPoints,
                                              this, mCamera, mSolidMaterial);
    }

    bool Visualizer::IsSolvedForestFile()
    {
        std::string path(mFilePathControlPoints);
        std::size_t found = path.find("forest_solution_");
        if (found!=std::string::npos)
            return true;
        return false;
    }

    bool Visualizer::IsScript(std::string scriptPath)
    {
        std::string path(scriptPath);
        std::size_t found = path.find("script_");
        if (found!=std::string::npos)
            return true;
        return false;
    }

    bool Visualizer::FileExists(const std::string& name)
    {
        struct stat buffer;
        return (stat (name.c_str(), &buffer) == 0);
    }

    int Visualizer::SetControlPointsFilename(char **args, int i)
    {
        /**
        args[1]:
        r - run script
        m - manual
        l - load

        args[2]: densidade
        args[3]: semente
        args[4]: desvio padrao
        args[5]: distancia critica
        args[6]: metodo

        */
        /// densidade + dist. critica + config do grafo

        //../../forests/attributes.txt  ../../forests/step30_15dens.txt forest_simulation_1_4_15_10
        if(execution == LOAD)
        {
            std::string arg(args[++i]);
            mFilePathControlPoints.append(mDirectoryPath);
            mFilePathControlPoints.append("forests/solution/");
            mFilePathControlPoints.append(arg);
            std::cout<<"mFilePathControlPoints  "<<mFilePathControlPoints<<std::endl;

            if(FileExists(mFilePathControlPoints) == false)
            {
                std::cout<<mFilePathControlPoints<<"  nao existe ********* "<<std::endl;
            }
            return i;
        }

        mFilePathControlPoints.append(mDirectoryPath);
        mFilePathControlPoints.append("forests/simulation/forest_simulation_");

        std::string dens(args[++i]);
        std::string seed(args[++i]);
        std::string stdDev(args[++i]);

        /*std::cout<<"args 0    "<<args[0]<<std::endl;
        std::cout<<"dens      "<<dens<<std::endl;
        std::cout<<"seed      "<<seed<<std::endl;
        std::cout<<"stdDev    "<<stdDev<<std::endl;*/

        mFilePathControlPoints.append(seed);
        mFilePathControlPoints.append("_30");
        std::size_t found;

        found = dens.find("25");
        if (found!=std::string::npos)
        {
            mFilePathControlPoints.append("_25_");
        }
        else
        {
            found = dens.find("15");
            if (found!=std::string::npos)
            {
                mFilePathControlPoints.append("_15_");
            }
            else
            {
                found = dens.find("5");
                if (found!=std::string::npos)
                {
                    mFilePathControlPoints.append("_5_");
                }
                else
                {
                    found = dens.find("10");
                    if (found!=std::string::npos)
                    {
                        mFilePathControlPoints.append("_10_");
                    }
                }
            }
        }
        mFilePathControlPoints.append(stdDev);
        mFilePathControlPoints.append(".txt");
        ///std::cout<<"mFilePathControlPoints  "<<mFilePathControlPoints<<std::endl;

        if(FileExists(mFilePathControlPoints) == false)
        {
            std::cout<<mFilePathControlPoints<<"  nao existe ********* "<<std::endl;
            exit(2);
        }
        return i;
    }

    int Visualizer::SetAttributteFilename(char **args, int i)
    {
        /**
        args[1]:
        r - run script
        m - manual
        l - load

        args[2]: densidade
        args[3]: semente
        args[4]: desvio padrao
        args[5]: distancia critica
        args[6]: metodo

        */
        /// densidade + dist. critica + config do grafo
        std::string dens(args[++i]);
        std::string seed(args[++i]);
        std::string stdDev(args[++i]);

        mForestSeed = seed;
        mForestDensity = dens;
        mForestStdDev = stdDev;

        /*std::cout<<"args 0    "<<args[0]<<std::endl;
        std::cout<<"dens      "<<dens<<std::endl;
        std::cout<<"seed      "<<seed<<std::endl;
        std::cout<<"stdDev    "<<stdDev<<std::endl;*/

        //../../forests/attributes.txt  ../../forests/step30_15dens.txt forest_simulation_1_4_15_10

        mFilePathAttributes.append(mDirectoryPath);
        mFilePathAttributes.append("forests/attributes/forest_attributes_");

        mFilePathAttributes.append(seed);
        std::size_t found;

        found = dens.find("25");
        if (found!=std::string::npos)
        {
            mFilePathAttributes.append("_25_");
        }
        else
        {
            found = dens.find("15");
            if (found!=std::string::npos)
            {
                mFilePathAttributes.append("_15_");
            }
            else
            {
                found = dens.find("5");
                if (found!=std::string::npos)
                {
                    mFilePathAttributes.append("_5_");
                }
                else
                {
                    found = dens.find("10");
                    if (found!=std::string::npos)
                    {
                        mFilePathAttributes.append("_10_");
                    }
                }
            }
        }
        mFilePathAttributes.append(stdDev);
        mFilePathAttributes.append(".txt");
        std::cout<<"mFilePathAttributes  "<<mFilePathAttributes<<std::endl;

        if(FileExists(mFilePathAttributes) == false)
        {
            std::cout<<mFilePathAttributes<<"  nao existe ********* "<<std::endl;
            exit(2);
        }
        return i;
    }

    void Visualizer::SaveConfiguration(char **args, int &i)
    {
        SetAttributteFilename(args, i);
        i = SetControlPointsFilename(args, i);
        SetGraphConfig(args, i);

        //int nada; std::cin>>nada;
    }

    void Visualizer::SetGraphConfig(char **args, int &i)
    {
        /**
        args[1]:
        r - run script
        m - manual
        l - load

        args[2]: densidade
        args[3]: semente
        args[4]: desvio padrao
        args[5]: distancia critica
        args[6]: metodo

        */
        std::string crit(args[++i]);
        std::stringstream ss(crit);
        ss >> mGraphCriticalDistance;
        ///std::cout<<"mGraphCriticalDistance  "<<mGraphCriticalDistance<<std::endl;

        std::string solution(args[++i]);
        ///std::cout<<"solution  "<<solution<<std::endl;
        std::size_t found;

        ///Graph::SOLUTION mOrderSolution;
        found = solution.find("DIRECT");
        if (found!=std::string::npos)
        {
            mOrderSolution = Graph::DIRECT;
            ///std::cout<<"Graph::DIRECT"<<std::endl;
        }
        found = solution.find("HYPOTENUSE");
        if (found!=std::string::npos)
        {
            mOrderSolution = Graph::HYPOTENUSE;
            ///std::cout<<"Graph::HYPOTENUSE"<<std::endl;
        }
        found = solution.find("ORIGINAL");
        if (found!=std::string::npos)
        {
            mOrderSolution = Graph::ORIGINAL;
            ///std::cout<<"Graph::ORIGINAL"<<std::endl;
        }
        found = solution.find("ORIGINAL_MAX");
        if (found!=std::string::npos)
        {
            mOrderSolution = Graph::ORIGINAL_MAX;
            ///std::cout<<"Graph::ORIGINAL_MAX"<<std::endl;
        }
        found = solution.find("ORIGINAL_MIN");
        if (found!=std::string::npos)
        {
            mOrderSolution = Graph::ORIGINAL_MIN;
            ///std::cout<<"Graph::ORIGINAL_MIN"<<std::endl;
        }
        found = solution.find("CRITICAL");
        if (found!=std::string::npos)
        {
            mOrderSolution = Graph::CRITICAL;
            ///std::cout<<"Graph::CRITICAL"<<std::endl;
        }

        mAttractorType =  Graph::MIDPOINT;
        mAnchorType = Graph::SUPERBLOCK;
        mGraphType = Graph::ULTRA_CONNECTED;
        mColoringHeuristic = Graph::FIRST_FIT;
        mColorOrder = Graph::BEST;
        mColoringChoice = Graph::CLOSEST_CNT_INDEX;
        mGraphOrdination =  Graph::CNT_HIGHEST_CONNECTION;

        {/**
        std::string choice(args[++i]);
        std::string greedy(args[++i]);
        std::string g_order(args[++i]);
        std::string c_order(args[++i]);
        std::string type(args[++i]);
        std::string anc(args[++i]);
        std::string att(args[++i]);
        std::cout<<"choice    "<<choice<<std::endl;
        std::cout<<"greedy    "<<greedy<<std::endl;
        std::cout<<"g_order   "<<g_order<<std::endl;
        std::cout<<"c_order   "<<c_order<<std::endl;
        std::cout<<"type      "<<type<<std::endl;
        std::cout<<"anc       "<<anc<<std::endl;

        ///Graph::ATTRACTOR mAttractorType;
        found = att.find("MIDPOINT");
        if (found!=std::string::npos)
        {
            mAttractorType = Graph::MIDPOINT;
            std::cout<<"Graph::MIDPOINT"<<std::endl;
        }
        found = att.find("ONEPOINT");
        if (found!=std::string::npos)
        {
            mAttractorType = Graph::ONEPOINT;
            std::cout<<"Graph::ONEPOINT"<<std::endl;
        }
        found = att.find("EXTREMES");
        if (found!=std::string::npos)
        {
            mAttractorType = Graph::EXTREMES;
            std::cout<<"Graph::EXTREMES"<<std::endl;
        }
        ///Graph::ANCHOR mAnchorType;
        found = anc.find("SUPERBLOCK");
        if (found!=std::string::npos)
        {
            mAnchorType = Graph::SUPERBLOCK;
            std::cout<<"Graph::SUPERBLOCK"<<std::endl;
        }
        found = anc.find("GRAPH");
        if (found!=std::string::npos)
        {
            mAnchorType = Graph::GRAPH;
            std::cout<<"Graph::GRAPH"<<std::endl;
        }
        ///Graph::GRAPH_TYPE mGraphType;
        found = type.find("CONTACTS");
        if (found!=std::string::npos)
        {
            mGraphType = Graph::CONTACTS;
            std::cout<<"Graph::CONTACTS"<<std::endl;
        }
        found = type.find("ULTRA_CONNECTED");
        if (found!=std::string::npos)
        {
            mGraphType = Graph::ULTRA_CONNECTED;
            std::cout<<"Graph::ULTRA_CONNECTED"<<std::endl;
        }
        found = type.find("SIMPLE_CONNECTED");
        if (found!=std::string::npos)
        {
            mGraphType = Graph::SIMPLE_CONNECTED;
            std::cout<<"Graph::SIMPLE_CONNECTED"<<std::endl;
        }
        found = type.find("CONNECTED");
        if (found!=std::string::npos)
        {
            mGraphType = Graph::CONNECTED;
            std::cout<<"Graph::CONNECTED"<<std::endl;
        }
        found = type.find("CONTACT_TO_POINT");
        if (found!=std::string::npos)
        {
            mGraphType = Graph::CONTACT_TO_POINT;
            std::cout<<"Graph::CONTACT_TO_POINT"<<std::endl;
        }
        ///Graph::HEURISTIC mColoringHeuristic;
        found = greedy.find("FIRST_FIT");
        if (found!=std::string::npos)
        {
            mColoringHeuristic = Graph::FIRST_FIT;
            std::cout<<"Graph::FIRST_FIT"<<std::endl;
        }
        found = greedy.find("DFS");
        if (found!=std::string::npos)
        {
            mColoringHeuristic = Graph::DFS;
            std::cout<<"Graph::DFS"<<std::endl;
        }
        found = greedy.find("BFS");
        if (found!=std::string::npos)
        {
            mColoringHeuristic = Graph::BFS;
            std::cout<<"Graph::BFS"<<std::endl;
        }
        found = greedy.find("DFS_LDO");
        if (found!=std::string::npos)
        {
            mColoringHeuristic = Graph::DFS_LDO;
            std::cout<<"Graph::DFS_LDO"<<std::endl;
        }
        ///Graph::COLOR_ORDER mColorOrder;
        found = c_order.find("INITIAL");
        if (found!=std::string::npos)
        {
            mColorOrder = Graph::INITIAL;
            std::cout<<"Graph::INITIAL"<<std::endl;
        }
        found = c_order.find("BEST");
        if (found!=std::string::npos)
        {
            mColorOrder = Graph::BEST;
            std::cout<<"Graph::BEST"<<std::endl;
        }
        found = c_order.find("VERY_BEST");
        if (found!=std::string::npos)
        {
            mColorOrder = Graph::VERY_BEST;
            std::cout<<"Graph::VERY_BEST"<<std::endl;
        }
        ///Graph::GRAPH_ORDER mGraphOrdination;
        found = g_order.find("INCREASE");
        if (found!=std::string::npos)
        {
            mGraphOrdination = Graph::INCREASE;
            std::cout<<"Graph::INCREASE"<<std::endl;
        }
        found = g_order.find("UP_DOWN");
        if (found!=std::string::npos)
        {
            mGraphOrdination = Graph::UP_DOWN;
            std::cout<<"Graph::UP_DOWN"<<std::endl;
        }
        found = g_order.find("CNT_HIGHEST_CONNECTION");
        if (found!=std::string::npos)
        {
            mGraphOrdination = Graph::CNT_HIGHEST_CONNECTION;
            std::cout<<"Graph::CNT_HIGHEST_CONNECTION"<<std::endl;
        }
        ///Graph::COLOR_CHOICE mColoringChoice;
        found = choice.find("MIN_INDEX");
        if (found!=std::string::npos)
        {
            mColoringChoice = Graph::MIN_INDEX;
            std::cout<<"Graph::MIN_INDEX"<<std::endl;
        }
        found = choice.find("LAST_INDEX");
        if (found!=std::string::npos)
        {
            mColoringChoice = Graph::LAST_INDEX;
            std::cout<<"Graph::LAST_INDEX"<<std::endl;
        }
        found = choice.find("CLOSEST_CNT_INDEX");
        if (found!=std::string::npos)
        {
            mColoringChoice = Graph::CLOSEST_CNT_INDEX;
            std::cout<<"Graph::CLOSEST_CNT_INDEX"<<std::endl;
        }
*/
        }

    }

    void Visualizer::RunScript()
    {
        bool auto_crit_dist = false; /// procurar automaticamente pela distancia critica minima para resolver todos os contatos

        std::string contacts_b4_filename("contacts/contacts_b4_");
        contacts_b4_filename.append(std::to_string(mForest->mContacts->GetContactDistance()).substr(0, 3));
        contacts_b4_filename.append("_");

        std::cout<<"Searching for contacts...";
        mForest->ContactLookUp(mIntersectionSpheres);
        mForest->mContacts->SaveContactList(GetForestSolutionFilename(contacts_b4_filename));
        int total_contacts = mForest->mContacts->GetTotalContacts();
        std::cout<<" Total contacts: "<<total_contacts<<std::endl;

        vis = SuperBlock::BLOCK;
        mForest->SetSuperBlocks();
        mForest->SetVisualization(vis);

        mSolveWholeForest = true;
        mSuperStart = 0;
        mSuperBreak = (int)mForest->GetSuperBlocksSize();

        /*if(!auto_crit_dist)
        {
            mForest->mContacts->SetCriticalDistance(mGraphCriticalDistance);
        }*/

        mForest->SetSuperBlocksGraphs(mSuperStart, mSuperBreak);
        mDrawGraph = true;

        mForest->SolveForest(mSuperStart, mSuperBreak);
        std::cout<<"Forest solved"<<std::endl;

        /*if(!auto_crit_dist)
        {
            mForest->mContacts->SetCriticalDistance(mCriticalDistance);
        }*/


        std::cout<<"Searching for remaining contacts... "<<std::endl;
        std::string contacts_filename("contacts/contacts_");
        contacts_filename.append(std::to_string(mForest->mContacts->GetContactDistance()).substr(0, 3));
        contacts_filename.append("_");

        if(auto_crit_dist)
        {
            mForest->ContactLookUp(mIntersectionSpheres);
            mForest->mContacts->SaveContactList(GetForestSolutionFilename(contacts_filename));
            total_contacts = mForest->mContacts->GetTotalContacts();

            if(total_contacts > 0)
            {
                /// procurando automaticamente qual a menor distancia critica maior que 0.3 para resolver a floresta toda
                for(unsigned int i = mSuperStart; i < mSuperBreak; i++)
                {
                    double prev_crit = mCriticalDistance;
                    int superblock_contacts = mForest->GetSuperblockContacts(i);
                    while(superblock_contacts > 0)
                    {
                        mForest->SolveForest(i, i+1); /// resolve o superbloco apenas. Desfazendo o deslocamento
                        mForest->ContactLookUp(mIntersectionSpheres);
                        total_contacts = mForest->mContacts->GetTotalContacts();
                        mCriticalDistance += mIncrement/10.0;
                        mForest->mContacts->SetCriticalDistance(mCriticalDistance);
                        mForest->ClearSuperblockGraph(i);
                        mForest->SetSuperBlocksGraphs(i, i+1);
                        mForest->SolveForest(i, i+1); /// resolve o superbloco apenas
                        superblock_contacts = mForest->GetSuperblockContacts(i);
                        std::cout<<i<<": "<<superblock_contacts<<"  "<<mCriticalDistance<<std::endl;
                    }
                    mCriticalDistance = prev_crit;
                    mForest->mContacts->SetCriticalDistance(mCriticalDistance);
                }
            }
        }

        mForest->ContactLookUp(mIntersectionSpheres);
        mForest->mContacts->SaveContactList(GetForestSolutionFilename(contacts_filename));
        total_contacts = mForest->mContacts->GetTotalContacts();
        std::cout<<"Total contacts: "<<total_contacts<<std::endl;
        std::cout<<GetForestSolutionFilename(contacts_b4_filename)<<std::endl;
        std::cout<<GetForestSolutionFilename(contacts_filename)<<std::endl;

        std::cout<<"Saving result"<<std::endl;
        mForest->SetVisualization(vis);
        SaveVisualizer();

        exit(1);
    }

    void Visualizer::ScriptReader()
    {
        /// nao use
        std::ifstream inputFile(Utility::GetPath(mDirectoryPath));

        while(!inputFile.eof())
        {
            std::string buffer = "";
            std::getline(inputFile, buffer);
            if(buffer[0] == '#') continue; /// ignorando comentarios
            std::cout<<"buffer****   "<<buffer<<std::endl;

            std::size_t found = buffer.find("att");
            if (found!=std::string::npos)
            {
                mFilePathAttributes = buffer.substr(4);
                //std::cout<<buffer.substr(4)<<std::endl;
                continue;
            }
            found = buffer.find("ctrl");
            if (found!=std::string::npos)
            {
                mFilePathControlPoints = buffer.substr(5);
                //std::cout<<buffer.substr(5)<<std::endl;
                continue;
            }
            found = buffer.find("solveall");
            if (found!=std::string::npos)
            {
                found = buffer.find("0");
                if(found!=std::string::npos)
                {
                    mSolveWholeForest = false;
                    mSuperStart = 0;
                    mSuperBreak = 1;
                }
                else
                {
                    mSolveWholeForest = true;
                }
                //std::cout<<buffer.substr(9)<<std::endl;
                continue;
            }
            found = buffer.find("dist");
            if (found!=std::string::npos)
            {
                found = buffer.find("0");
                if(found!=std::string::npos)
                {
                    mSolveWholeForest = false;
                    mSuperStart = 0;
                    mSuperBreak = 1;
                }
                else
                {
                    mSolveWholeForest = true;
                }
                //std::cout<<buffer.substr(5)<<std::endl;
                continue;
            }
        }

        inputFile.close();

    }

    unsigned int Visualizer::GetControlPointID(int cnt, int ind)
    {
        return cnt * mSegmentsPerCNT + ind -1;
    }

    int Visualizer::GetCNT(unsigned int id)
    {
        return (id+1)/mSegmentsPerCNT;
    }

    int Visualizer::GetIndex(unsigned int id)
    {
        return (id+1)%mSegmentsPerCNT;
    }

}
