#include "Block.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

namespace Library
{
Block::Block(Contact *c) :
     contacts(c), segmentsPerCNT(0)
{
    //ctor
    if(contacts != NULL)
        segmentsPerCNT = contacts->GetSegmentsPerCNT();
}

Block::~Block()
{
    //dtor
    content.clear();
}

//void Block::SetBlock(std::vector<cpList> *controlPointsContacts, int point)
void Block::SetBlock(int StartPoint)
{
    contacts->SetAnchor(StartPoint, false);
    if(contacts->GetContactsSize(StartPoint) == 0)
    {
        return;
        //continue;
    }

    if(contacts->WasAddedToBlock(StartPoint))
    {
        return;
        //continue;   // Não precisamos filtrar os contatos usando isso
    }

    //std::cout<<"SetBlock2"<<std::endl;
    bool verbose = false;
    block_content b_content;
    std::vector<unsigned int> cp_ids;

    color = vec3(rand() / static_cast<float>(RAND_MAX), rand() / static_cast<float>(RAND_MAX), rand() / static_cast<float>(RAND_MAX));

    cp_ids.push_back(StartPoint); // v.id
    FillVector(cp_ids, StartPoint);   // salvando pontos do bloco
    sort(cp_ids.begin(),cp_ids.end());

    /// Para ver a lista de contatos como grafo não direcionado dentro do bloco
    if(verbose)
    {
        std::cout<<"cpids"<<std::endl;
        for(unsigned int i = 0; i < cp_ids.size(); i++)
        {
            contacts->PrintContacts(cp_ids[i]);
        }
    }

    int cnt0 = GetCNT(cp_ids[0]);
    int cnts_ = 1;
    for(unsigned int cpid : cp_ids)
    {
        if(cnt0 != GetCNT(cpid))
        {
            cnts_++;
            cnt0 = GetCNT(cpid);
        }
        b_content.cp_ids = cpid;
        b_content.cnts = 0;
        b_content.type = SIMPLE;
        b_content.contacts_size = contacts->GetContactsSize(cpid);
        content.push_back(b_content);
    }
    cnts = cnts_;
    //b.displ = NULL;
    //setContactTypes(&b)  // salvando contatos como SIMPLE, COMPOSED ou MULTIPLE
    //blocks.push_back(b);
    // marcando quem já foi adicionado.
    for(block_content bc : content)
    {
        contacts->SetAddedToBlock(bc.cp_ids, true);
    }

    if(verbose)
    {
        contacts->PrintContacts(StartPoint);
        std::cout<<"b.content"<<std::endl;
        for(unsigned int i = 0; i < content.size(); i++)
        {
            int cnt = GetCNT(content[i].cp_ids);
            int ind = GetIndex(content[i].cp_ids);
            std::cout<<i<<": "<<cnt<<"."<<ind<<"\t";
        }
        std::cout<<std::endl;

        //int nada;std::cin>>nada;
    }
}

void Block::ClearBlock()
{
    content.clear();
}

void Block::FillVector(std::vector<unsigned int>&vec, unsigned int id)
{
    //static unsigned int segmentsPerCNT = mDrawNano[0]->mInterpolator->ControlPointsNumber();
    ///cpList v = controlPointsContacts[id];
    //for(std::list<glm::uvec4>::const_iterator i = v.contacts.begin(); i != v.contacts.end(); i++)
    //for(int i = 0; i < v.contacts.size(); i++)
    for(int i = 0; i < contacts->GetContactsSize(id); i++)
    {
        //int id0 = GetControlPointID(v.contacts[i].x, v.contacts[i].y);
        //int id1 = GetControlPointID(v.contacts[i].z, v.contacts[i].w);
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
    }
}

bool Block::contains(const std::vector<unsigned int>&a, const unsigned int b)
{
    for(unsigned int i : a)
    {
        if(i == b) return true;
    }
    return false;
}

unsigned int Block::GetContentControlPointID(int i)
{
    if(0 <= i && i < (int)content.size())
    {
        return content[i].cp_ids;
    }
    return -1;
}

void Block::SaveBlock(std::string mFilePath)
{
    std::ofstream outputFile(mFilePath, outputFile.app);

    outputFile<<"b\n";
    outputFile<<cnts<<" "<<added<<"\n";
    outputFile<<color[0]<<" "<<color[1]<<" "<<color[2]<<"\n";

    for(block_content cont : content)
    {
        outputFile<<cont.cp_ids<<" ";
        outputFile<<cont.cnts<<" ";
        outputFile<<cont.type<<" ";
        outputFile<<cont.contacts_size<<"\n";
    }

    outputFile.close();
}

bool Block::LoadBlock(std::string mFilePath, int &line, bool &end_of_blocks)
{
    std::ifstream inputFile(mFilePath);
    bool verbose = false;
    if(verbose) std::cout<<"LoadBlock  "<<line<<std::endl;

    for (int i = 0; i < line; i++)
    {
        std::string buffer = "";
        std::getline(inputFile, buffer);
    }

    int cont = 0;
    while(!inputFile.eof())
    {
        std::string buffer = "";
        std::getline(inputFile, buffer);
        line++;
        if(verbose) std::cout<<line<<":  "<<buffer<<std::endl;
        if(cont == 0)
        {
            std::stringstream ss(buffer);
            ss >> cnts >> added;
            ss.clear();
        }
        else if(cont == 1)
        {
            std::stringstream ss(buffer);
            ss >> color[0] >> color[1] >> color[2];
            ss.clear();
        }
        else
        {
            while(!inputFile.eof())
            {
                std::stringstream ss(buffer);
                block_content b_cont;
                unsigned int type;
                ss >> b_cont.cp_ids >> b_cont.cnts >> type >>  b_cont.contacts_size ;
                switch(type)
                {
                    case SIMPLE   : b_cont.type = SIMPLE; break;
                    case COMPOSED : b_cont.type = COMPOSED; break;
                    case MULTIPLE : b_cont.type = MULTIPLE; break;
                }
                content.push_back(b_cont);
                ss.clear();
                std::getline(inputFile, buffer);
                line++;
                if(verbose) std::cout<<line<<":  "<<buffer<<std::endl;
                if(buffer[0] == 'b')
                {
                    end_of_blocks = false;
                    break;
                }
                if(buffer[0] == 'g')
                {
                    end_of_blocks = true;
                    break;
                }
            }
        }
        cont++;

        if(buffer[0] == 'b')
        {
            end_of_blocks = false;
            break;
        }
        if(buffer[0] == 'g')
        {
            end_of_blocks = true;
            break;
        }
    }

    bool eof = inputFile.eof();
    if(verbose)
    {
        if(eof) std::cout<<"Block eof true "<<std::endl;
        else    std::cout<<"Block eof false"<<std::endl;
    }

    inputFile.close();

    return eof;
}

unsigned int Block::GetControlPointID(int cnt, int ind)
{
    return cnt * segmentsPerCNT + ind -1;
}

int Block::GetCNT(unsigned int id)
{
    return (id+1)/segmentsPerCNT;
}

int Block::GetIndex(unsigned int id)
{
    return (id+1)%segmentsPerCNT;
}

}
