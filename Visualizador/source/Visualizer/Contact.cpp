#include "Contact.h"
#include "VisualizerCommon.h"
#include "Utility.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace Library
{
Contact::Contact(std::vector<DrawableNanotube*> *cnts, std::string controlPointsFilePath) :
    mDrawNano(cnts),
    segmentsPerCNT(0),
    mTotalContacts(0),
    mDuplicates(true),
    mContactDistance(0.3),
    mFilePathControlPoints(controlPointsFilePath)
{
    //ctor
    segmentsPerCNT = (*mDrawNano)[0]->mInterpolator->ControlPointsNumber();
    controlPointsContacts.resize(mDrawNano->size() * segmentsPerCNT);
    for(unsigned int i = 0; i < controlPointsContacts.size(); i++)
        controlPointsContacts[i].id = i;

    mContactDistance = GetCriticalDistance();
}

Contact::~Contact()
{
    //dtor
    ClearContacts();
}

void Contact::Configure(double crit, double distance, bool dupli)
{
    mCriticalDistance = crit;
    mContactDistance = distance;
    mDuplicates = dupli;
}

void Contact::ClearContacts()
{
    for(unsigned int i = 0; i < controlPointsContacts.size(); i++)
        controlPointsContacts[i].contacts.clear();
    // para podermos ver os blocos depois de uma correcao dos pontos de controle
    controlPointsContacts.clear();
    // para mudar a cor dos novos contatos segundo novo criterio de distancia
    for(unsigned int i = 0; i < (*mDrawNano).size(); i++)
    {
        (*mDrawNano)[i]->ClearOverlapPoints();
    }
    // Para limpar a lista por completo
    mIndices.clear();
    mContactCNT1.clear();
    mContactCNT2.clear();
}

void Contact::ResetContacts()
{
    ClearContacts();
    controlPointsContacts.resize((*mDrawNano).size() * segmentsPerCNT);
    for(unsigned int i = 0; i < controlPointsContacts.size(); i++)
        controlPointsContacts[i].id = i;
}

void Contact::ContactLookUp(DrawableSpheres *mIntersectionSpheres)
{
    ResetContacts();

    Vertex pt1;
    Vertex pt2;
    double dist;
    mTotalContacts = 0;
    ///total_critical = 0;

    int cont = 0;
    int lim = -1;

    for(int cnt1 = 0; cnt1 < (int)mDrawNano->size()-1; cnt1++)
    {
        std::vector<Vertex> cp1 = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints();

        // comeca do 2 pois o ponto 1 do cp1 eh o ponto no substrato que não deve ser contato na busca por contatos
        // não contar o ultimo ponto pois ele não faz parte dos dados do CNT salvos no arquivo
        for(int ind1 = 2; ind1 < (int)cp1.size()-1; ind1++)
        {
            for(int cnt2 = cnt1+1; cnt2 < (int)mDrawNano->size(); cnt2++)
            {
                std::vector<Vertex> cp2 = (*mDrawNano)[cnt2]->mInterpolator->ControlPoints();

                for(int ind2 = 2; ind2 < (int)cp2.size()-1; ind2++)
                {
                    dist = DistFromSegments(cp2[ind2], cp1[ind1], cp2[ind2-1], cp1[ind1-1], pt1, pt2);
                    dist = dist - (*mDrawNano)[cnt1]->Radius() - (*mDrawNano)[cnt2]->Radius();

                    ///if(FEQUAL(dist - mContactDistance, 0.0) == 1 || dist <= mContactDistance)
                    if(dist < mContactDistance && FEQUAL(dist, mContactDistance) == false)
                    {
                        if(!mDuplicates)
                        {
                            /// procurar na lista de pontos de contato se existe o mesmo
                            /// eh mais provavel que ele tenha sido o último adicionado
                            bool found = false;
                            for(int i = mContactCNT1.size()-1; i >= 0; i--)
                            {
                                Vertex pos1 = mContactCNT1[i];
                                Vertex pos2 = mContactCNT2[i];
                                if(FEQUAL(pos1.x,pt1.x) && FEQUAL(pos1.y,pt1.y) && FEQUAL(pos1.z,pt1.z))
                                {
                                    if(FEQUAL(pos2.x,pt2.x) && FEQUAL(pos2.y,pt2.y) && FEQUAL(pos2.z,pt2.z))
                                    {
                                        std::cout<<"Skiping contact "<<cnt1<<"."<<ind1<<"-"<<cnt2<<"."<<ind2<<std::endl;
                                        found = true;
                                        break;
                                    }
                                }
                            }
                            if (found) continue;
                        }

                        /*if(cont < 15)
                        {
                            std::cout<<cnt1<<"."<<ind1<<"-"<<cnt2<<"."<<ind2<<std::endl;
                        }*/


                        (*mDrawNano)[cnt1]->AddOverlapPoint(ind1);
                        (*mDrawNano)[cnt2]->AddOverlapPoint(ind2);

                        controlPointsContacts[GetControlPointID(cnt1, ind1)].contacts.push_back(glm::uvec4(cnt1, ind1, cnt2, ind2));
                        controlPointsContacts[GetControlPointID(cnt2, ind2)].contacts.push_back(glm::uvec4(cnt2, ind2, cnt1, ind1));

                        /// para visualização dos contatos
                        mIndices.push_back(glm::uvec4(cnt1, ind1, cnt2, ind2));
                        mContactCNT1.push_back(Vertex(pt1[0], pt1[1], pt1[2]));
                        mContactCNT2.push_back(Vertex(pt2[0], pt2[1], pt2[2]));

                        Vertex vert1(0.0, 0.0, 0.0);
                        Vertex vert2(0.0, 0.0, 0.0);
                        double distance1 = SegmentCyllinderIntersection(GetControlPointID(cnt1, ind1), pt2, pt1, vert1);
                        double distance2 = SegmentCyllinderIntersection(GetControlPointID(cnt2, ind2), pt1, pt2, vert2);
                        ///std::cout<<"radius1  "<<(*mDrawNano)[cnt1]->Radius()<<"  radius2  "<<(*mDrawNano)[cnt2]->Radius()<<std::endl;
                        ///std::cout<<"distance1  "<<distance1<<"  distance2  "<<distance2<<std::endl;

                        if(FEQUAL(pt1.x, pt2.x) && FEQUAL(pt1.y, pt2.y) && FEQUAL(pt1.z, pt2.z))
                        {
                            double radius  = (*mDrawNano)[cnt2]->Radius();
                            Vertex d__ = cp2[ind2] - cp2[ind2-1];
                            Vertex z_axis(0.0, 0.0, -1.0);
                            vert2 = d__.Cross(z_axis);
                            vert2.Normalize();
                            vert2.x = radius*vert2.x + pt2.x;
                            vert2.y = radius*vert2.y + pt2.y;
                            vert2.z = radius*vert2.z + pt2.z;
                        }

                        if(distance1 > -1.0)
                        {
                            //double distance3 = pt1.Distance(pt2) - distance1-distance2;
                            ///std::cout<<"distance3  "<<distance3<<std::endl;

                            ///mIntersectionSpheres->PushSphere(vec3(vert1[0], vert1[1], vert1[2]), vec3(0.0, 1.0, 1.0), mCriticalDistance/2.0);
                        }
                        if(distance2 > -1.0)
                        {
                            //double distance3 = pt1.Distance(pt2) - distance1-distance2;
                            ///std::cout<<"distance3  "<<distance3<<std::endl;

                            ///mIntersectionSpheres->PushSphere(vec3(vert2[0], vert2[1], vert2[2]), vec3(0.0, 1.0, 0.0), mCriticalDistance/2.0);
                        }
                        //std::cout<<"int\t";
                        //int nada;std::cin>>nada;

                        cont++;
                    }
                    // tem que somar os raios novamente para ser o criterio de inserção
                    if(FEQUAL(pt1.Distance(pt2), 0.0) == 1)
                    {
                        mIntersectionSpheres->PushSphere(vec3(pt1[0], pt1[1], pt1[2]), vec3(1.0, 0.0, 0.0), 1.0);
                    }

                    /*if(FEQUAL(dist - criticalDistance, 0.0) == 1 || dist <= criticalDistance)
                    {
                        total_critical++;
                    }*/
                    if(cont == lim) break;
                }
                cp2.clear();
                if(cont == lim) break;
            }
            if(cont == lim) break;
        }
        cp1.clear();
        if(cont == lim) break;
    }
    mTotalContacts = mIndices.size();
    ///SaveContactList();
}

double Contact::SegmentCyllinderIntersection(unsigned int cpid1, Vertex pt1, Vertex pt2, Vertex &vert)
{
    int cnt1 = GetCNT(cpid1);
    int ind1 = GetIndex(cpid1);

    Vertex pos1   = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints()[ind1];   // q
    Vertex pos1_1 = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints()[ind1-1]; // p


    Vertex d__ = pos1 - pos1_1; // centro do cilindro : d
    pos1 = pos1 + d__;
    pos1_1 = pos1_1 - d__;
    d__ = pos1+d__ -(pos1_1 - d__);
    double radius = (*mDrawNano)[cnt1]->Radius(); // r
    bool verbose = false;

    if(FEQUAL(pt1.x, pt2.x) && FEQUAL(pt1.y, pt2.y) && FEQUAL(pt1.z, pt2.z))
    {
        /// interseção
        Vertex z_axis(0.0, 0.0, 1.0);
        vert = d__.Cross(z_axis);
        vert.Normalize();
        vert.x = radius*vert.x + pt2.x;
        vert.y = radius*vert.y + pt2.y;
        vert.z = radius*vert.z + pt2.z;
        if(verbose) std::cout<<"vert 0 "<<vert.x<<"  "<<vert.y<<"  "<<vert.z<<std::endl;
        return 0.0;
    }

    Vertex m__ = pt1 - pos1_1; // m = sa - p
    Vertex n__ = pt2 - pt1;    // n = sb - sa
    Vertex solution(0.0, 0.0, 0.0);

    double m_d = DotVector(m__, d__);
    double n_d = DotVector(n__, d__);
    double d_d = DotVector(d__, d__);

    /// limita a projeção ao tamanho do segmento do cilindro
    /*if(m_d < 0.0 && m_d + n_d < 0.0)
    {
        std::cout<<"m_d < 0.0 && m_d + n_d < 0.0"<<std::endl;
        return -1.0; // segmento fora do lado P do cilindro
    }
    if(m_d > d_d && m_d + n_d > d_d)
    {
        std::cout<<"m_d > d_d && m_d + n_d > d_d"<<std::endl;
        return -1.0; // segmento fora do lado Q do cilindro
    }*/

    double n_n = DotVector(n__, n__);
    double m_n = DotVector(m__, n__);

    double a = d_d*n_n - n_d*n_d;
    double k = DotVector(m__, m__) - radius*radius;
    double c = d_d*k - m_d*m_d;
    double t = 0.0;

    if(abs(a) < EPSILON)
    {
        /// segmento paralelo ao eixo do cilindro
        if(c > 0.0)
        {
            std::cout<<"c > 0.0  :  "<<c<<std::endl;
            int nada; std::cin>>nada;
            return -1.0;
        }
        if(m_d < 0.0) t = -m_n/n_n; // intercepta no ponto P
        else if(m_d > d_d) t = (n_d - m_n)/n_n; // intercepta no ponto Q
        else t = 0.0;
        vert.x = m__.x + t*n__.x + pos1_1.x;
        vert.y = m__.y + t*n__.y + pos1_1.y;
        vert.z = m__.z + t*n__.z + pos1_1.z;

        solution = vert - pt2;

        /*solution.x = m__.x + t*n__.x - pt1.x;
        solution.y = m__.y + t*n__.y - pt1.y;
        solution.z = m__.z + t*n__.z - pt1.z;*/

        if(verbose) std::cout<<"vert 1 "<<vert.x<<"  "<<vert.y<<"  "<<vert.z<<std::endl;
        return solution.Length();
    }

    double b = d_d*m_n - n_d*m_d;
    double discr = b*b - a*c;
    if(discr < 0.0)
    {
        std::cout<<"discr < 0.0  :  "<<discr<<std::endl;
        int nada; std::cin>>nada;
        return -1.0; //sem raiz real
    }

    t = (-b-sqrt(discr))/a;

    /// limita a projecao ao tamanho do contato
    /*if(t < 0.0 || t > 1.0)
    {
        std::cout<<"t < 0.0 || t > 1.0  :  "<<t<<std::endl;
        return -1.0; // intersecao fora do segmento
    }*/

    if(m_d + t*n_d < 0.0)
    {
        /// intersecao fora do cilindro no lado do P
        if(n_d < 0.0 || FEQUAL(n_d, 0.0))
        {
            std::cout<<"n_d < 0.0 || FEQUAL(n_d, 0.0)  :  "<<n_d<<std::endl;
            int nada; std::cin>>nada;
            return -1.0; // segmento aponta pra fora do endcap
        }
        t = - m_d/n_d;
        double result = k + 2.0*t*(m_n + t*n_n);
        // mesma posição do ponto de controle
        vert.x = m__.x + t*n__.x + pos1_1.x;
        vert.y = m__.y + t*n__.y + pos1_1.y;
        vert.z = m__.z + t*n__.z + pos1_1.z;

        solution = vert - pt2;

        if(verbose) std::cout<<"vert 2 "<<vert.x<<"  "<<vert.y<<"  "<<vert.z<<std::endl;
        /*if(( result < 0.0 || FEQUAL(result, 0.0)))
        {
            return solution.Length();
        }*/
        if(verbose) std::cout<<"result 1  "<<result<<std::endl;

        return solution.Length();
        ///return -1.0;
    } else if(m_d + t*n_d > d_d)
    {
        /// intersecao fora do cilindro no lado do Q
        if(n_d > 0.0 || FEQUAL(n_d, 0.0))
        {
            std::cout<<"n_d > 0.0 || FEQUAL(n_d, 0.0)  :  "<<n_d<<std::endl;
            int nada; std::cin>>nada;
            return -1.0; // segmento aponta pra fora do endcap
        }
        t = (d_d - m_d)/n_d;
        double result = k + d_d - 2.0*m_d + t*(2.0 * (m_n - n_d) + t*n_n);
        // mesma posição do ponto de controle
        vert.x = m__.x + t*n__.x + pos1_1.x;
        vert.y = m__.y + t*n__.y + pos1_1.y;
        vert.z = m__.z + t*n__.z + pos1_1.z;

        solution = vert - pt2;

        if(verbose) std::cout<<"vert 3 "<<vert.x<<"  "<<vert.y<<"  "<<vert.z<<std::endl;
        /*if(( result < 0.0 || FEQUAL(result, 0.0)))
        {
            return solution.Length();
        }*/
        if(verbose) std::cout<<"result 2  "<<result<<std::endl;

        return solution.Length();
        ///return -1.0;
    }
    // segmento intercepta o cilindro entre os endcaps do cilindro. T esta correto.
    /// v = X - P = m + t*n, m = A - P, n = B - A
    vert.x = m__.x + t*n__.x + pos1_1.x;
    vert.y = m__.y + t*n__.y + pos1_1.y;
    vert.z = m__.z + t*n__.z + pos1_1.z;

    solution = vert - pt2;

    if(verbose) std::cout<<"vert 4 "<<vert.x<<"  "<<vert.y<<"  "<<vert.z<<std::endl;
    return solution.Length();
}

double Contact::DotVector(Vertex v1, Vertex v2)
{
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

double Contact::GetContactPointRatio(Vertex pt1, unsigned int cpid1)
{
    int cnt1 = GetCNT(cpid1);
    int ind1 = GetIndex(cpid1);

    Vertex pos1   = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints()[ind1];
    Vertex pos1_1 = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints()[ind1-1];

    double ratio1 = pos1_1.Distance(pt1)/pos1.Distance(pos1_1);

    return ratio1;
}

glm::vec3 Contact::GetContactCenter(int i)
{
    glm::vec3 center(0.0);
    if(0 <= i && i < mTotalContacts)
    {
        center.x = (mContactCNT1[i].x + mContactCNT2[i].x)/2.0;
        center.y = (mContactCNT1[i].y + mContactCNT2[i].y)/2.0;
        center.z = (mContactCNT1[i].z + mContactCNT2[i].z)/2.0;
    }
    return center;
}
Vertex Contact::GetContact1(int i)
{
    if(0 <= i && i < mTotalContacts)
    {
        return mContactCNT1[i];
    }
    return Vertex(0.0, 0.0, 0.0);
}
Vertex Contact::GetContact2(int i)
{
    if(0 <= i && i < mTotalContacts)
    {
        return mContactCNT2[i];
    }
    return Vertex(0.0, 0.0, 0.0);
}
glm::uvec4 Contact::GetContactIndices(int i)
{
    if(0 <= i && i < mTotalContacts)
    {
        //std::cout<<mIndices[i][0]<<"."<<mIndices[i][1]<<"-"<<mIndices[i][2]<<"."<<mIndices[i][3]<<std::endl;
        return mIndices[i];
    }
    return uvec4(0.0);
}

bool Contact::IsAnchor(unsigned int cpid)
{
    if(0 <= cpid && cpid < controlPointsContacts.size())
    {
        return controlPointsContacts[cpid].isAnchor;
    }
    return false;
}
void Contact::SetAnchor(unsigned int cpid, bool isAnchor)
{
    if(0 <= cpid && cpid < controlPointsContacts.size())
    {
        controlPointsContacts[cpid].isAnchor = isAnchor;
    }
}
bool Contact::WasAddedToBlock(unsigned int cpid)
{
    if(0 <= cpid && cpid < controlPointsContacts.size())
    {
        return controlPointsContacts[cpid].added;
    }
    return false;
}
void Contact::SetAddedToBlock(unsigned int cpid, bool added)
{
    if(0 <= cpid && cpid < controlPointsContacts.size())
    {
        controlPointsContacts[cpid].added = added;
    }
}
int Contact::GetContactsSize(unsigned int cpid)
{
    if(0 <= cpid && cpid < controlPointsContacts.size())
    {
        return controlPointsContacts[cpid].contacts.size();
    }
    return -1;
}
glm::uvec4 Contact::GetControlPointContact(unsigned int cpid, int i)
{
    if(0 <= cpid && cpid < controlPointsContacts.size())
    {
        if(0 <= i && i < (int)controlPointsContacts[cpid].contacts.size())
        {
            return controlPointsContacts[cpid].contacts[i];
        }
    }
    return glm::uvec4(0.0);
}
void Contact::GetContactRatio(int cnt1, int ind1, int cnt2, int ind2, double &ratio1, double &ratio2)
{
    Vertex pos_m1   = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints()[ind1];
    Vertex pos_m1_1 = (*mDrawNano)[cnt1]->mInterpolator->ControlPoints()[ind1-1];
    Vertex pos_m2   = (*mDrawNano)[cnt2]->mInterpolator->ControlPoints()[ind2];
    Vertex pos_m2_1 = (*mDrawNano)[cnt2]->mInterpolator->ControlPoints()[ind2-1];
    Vertex pt1, pt2;
    ///pos_m1.z = pos_m2.z = pos_m2_1.z = pos_m1_1.z = 0.0; /// para reverter o deslocamento
    DistFromSegments(pos_m2, pos_m1, pos_m2_1, pos_m1_1, pt1, pt2);
    ratio1 = pt1.Distance(pos_m1_1)/pos_m1.Distance(pos_m1_1);
    ratio2 = pt2.Distance(pos_m2_1)/pos_m2.Distance(pos_m2_1);
}
void Contact::PrintContacts(unsigned int cpid)
{
    int cnt = GetCNT(cpid);
    int ind = GetIndex(cpid);
    std::cout<<cnt<<"."<<ind<<" ";
    for(uvec4 c : controlPointsContacts[cpid].contacts)
    {
        std::cout<<"-"<<c.z<<"."<<c.w;
    }
    std::cout<<std::endl;

}
void Contact::PrintContact(int mContactIterator)
{
    glm::vec4 contact = GetContactIndices(mContactIterator);
    Vertex cont1 = GetContact1(mContactIterator);
    Vertex cont2 = GetContact2(mContactIterator);

    //double dist = glm::length(cont1 - cont2);
    double radius1 = (*mDrawNano)[contact.x]->Radius();
    double radius2 = (*mDrawNano)[contact.z]->Radius();
    double dist = cont1.Distance(cont2);
    double dist2 = dist-radius1-radius2;
    std::cout<<"Contato numero "<<mContactIterator<<": ";
    std::cout<<contact.x<<"."<<contact.y<<"-"<<contact.z<<"."<<contact.w;
    if(FEQUAL(dist, 0.0))
    {
        std::cout<<" INTERSECAO"<<std::endl;
    }
    else
    {
        //if(FEQUAL(dist2, mCriticalDistance)|| dist2 <= mCriticalDistance)
        if(dist2 < mCriticalDistance)
            std::cout<<" -> "<<dist<<" ("<<dist2<<") CRITICO"<<std::endl;
        else
            std::cout<<" -> "<<dist<<" ("<<dist2<<")"<<std::endl;
    }

    Vertex segment1 = mDrawNano->at(contact.x)->mInterpolator->ControlPoint(contact.y);
    Vertex segment2 = mDrawNano->at(contact.z)->mInterpolator->ControlPoint(contact.w);

    //std::cout<<"pt1    "<<cont1.x<<"   "<<cont1.y<<"   "<<cont1.z<<std::endl;
    //std::cout<<"pt2    "<<cont2.x<<"   "<<cont2.y<<"   "<<cont2.z<<std::endl;
    std::cout<<"seg1   "<<segment1.x<<"   "<<segment1.y<<"   "<<segment1.z<<std::endl;
    std::cout<<"seg2   "<<segment2.x<<"   "<<segment2.y<<"   "<<segment2.z<<std::endl;
    std::cout<<"CNT: "<<contact.x<<" of radius "<<radius1<<", CNT "<<contact.z<<" of radius "<<radius2<<", radii sum: "<<radius1+radius2<<std::endl;
    std::cout<<std::endl;
}
void Contact::SaveContactList(std::string filename)
{
    if(GetTotalContacts() == 0) return;
    // Salvando lista de contato a partir da distancia usada como parametro, e nome do arquivo da floresta
    ///filename.append("forests/contacts_");

    /*std::string filename(Utility::GetPath("../../forests/contacts_"));
    std::ostringstream *ss = new std::ostringstream();
    *ss<<mContactDistance;
    filename.append(ss->str());
    int length = mFilePathControlPoints.length();
    filename.append(mFilePathControlPoints.substr(length-17, length));
    delete ss;*/

    std::ofstream outputFile(filename);
    for(unsigned int i = 0; i < GetTotalContacts(); i++)
    {
        outputFile<<i<<": ";
        outputFile<<mIndices[i][0]<<"."<<mIndices[i][1]<<"-"<<mIndices[i][2]<<"."<<mIndices[i][3];

        //double dist = glm::length(GetContact1(i) - GetContact2(i));
        Vertex pos1 = GetContact1(i);
        Vertex pos2 = GetContact2(i);
        double dist = pos1.Distance(pos2);
        double dist2 = dist-(*mDrawNano)[mIndices[i][0]]->Radius()-(*mDrawNano)[mIndices[i][2]]->Radius();
        if(FEQUAL(dist, 0.0) == 1)
        {
            outputFile<<" INTERSECAO\n";
        }
        else
        {
            if(FEQUAL(dist2, mCriticalDistance) == 1 || dist2 <= mCriticalDistance)
                outputFile<<"\t"<<dist<<" , "<<dist2<<" nm\tCRITICO\n";
            else
                outputFile<<"\t"<<dist<<" , "<<dist2<<" nm\n";
        }
    }
    outputFile.close();
}


unsigned int Contact::GetControlPointID(int cnt, int ind)
{
    return cnt * segmentsPerCNT + ind -1;
}

int Contact::GetCNT(unsigned int id)
{
    return (id+1)/segmentsPerCNT;
}

int Contact::GetIndex(unsigned int id)
{
    return (id+1)%segmentsPerCNT;
}

bool Contact::ContactExists(int cnt1, int ind1, int cnt2, int ind2)
{
    for(int i = 0; i < GetTotalContacts(); i++)
    {
        if(cnt1 == mIndices[i][0] && ind1 == mIndices[i][1] &&
           cnt2 == mIndices[i][2] && ind2 == mIndices[i][3])
        {
            return true;
        }
    }
    return false;
}

double Contact::DistFromSegments(Vertex pos_m2, Vertex pos_m1,Vertex pos_m2_1,
                                 Vertex pos_m1_1, Vertex &pt1, Vertex &pt2)
{
    Vertex p1_(pos_m1[0], pos_m1[1], pos_m1[2]);
    Vertex p2_(pos_m2[0], pos_m2[1], pos_m2[2]);
    Vertex q1_(pos_m1_1[0], pos_m1_1[1], pos_m1_1[2]);
    Vertex q2_(pos_m2_1[0], pos_m2_1[1], pos_m2_1[2]);
    Vertex r__;
    Vertex d1_; // Direction vector of segment S1
    Vertex d2_; // Direction vector of segment S2
    d1_ = q1_ - p1_;// Vector d1 = q1 - p1;
    d2_ = q2_ - p2_;// Vector d2 = q2 - p2;
    r__ = p1_ - p2_;// Vector r = p1 - p2;

    double a, e, f, s, t;
    ///#define gcgDOTVECTOR2(v1, v2) ((v1)[0] * (v2)[0] + (v1)[1] * (v2)[1])
    a = d1_[0]*d1_[0] + d1_[1]*d1_[1] + d1_[2]*d1_[2]; // Squared length of segment S1, always nonnegative
    e = d2_[0]*d2_[0] + d2_[1]*d2_[1] + d2_[2]*d2_[2]; // Squared length of segment S1, always nonnegative
    f = d2_[0]*r__[0] + d2_[1]*r__[1] + d2_[2]*r__[2];
    // Check if either or both segments degenerate into points
    ///if (a <= EPSILON && e <= EPSILON) {
    if ((FEQUAL(a, EPSILON) == 1 || a <= EPSILON) && (FEQUAL(e, EPSILON) == 1 || e <= EPSILON))
    {
        // Both segments degenerate into points
        s = r__.Length();

        /*gsl_vector_free(d1_);
        gsl_vector_free(d2_);
        gsl_vector_free(p1_);
        gsl_vector_free(p2_);
        gsl_vector_free(q1_);
        gsl_vector_free(q2_);
        gsl_vector_free(r__);*/
        return s;
    }
    if (FEQUAL(a, EPSILON) == 1 && a <= EPSILON)
    {
        // First segment degenerates into a point
        s = 0.0f;
        t = f / e; // s = 0 => t = (b*s + f) / e = f / e
        t = clamp(t, 0.0f, 1.0f);
    }
    else
    {
        double c;
        c  = d1_[0]*r__[0] + d1_[1]*r__[1] + d1_[2]*r__[2];
        if (FEQUAL(e, EPSILON) == 1 || e <= EPSILON)
        {
            // Second segment degenerates into a point
            t = 0.0f;
            s = clamp(-c / a, 0.0f, 1.0f); // t = 0 => s = (b*t - c) / a = -c / a
        }
        else
        {
            // The general nondegenerate case starts here
            double b;
            b  = d1_[0]*d2_[0] + d1_[1]*d2_[1] + d1_[2]*d2_[2];
            double denom = a*e-b*b; // Always nonnegative
            // If segments not parallel, compute closest point on L1 to L2 and
            // clamp to segment S1. Else pick arbitrary s (here 0)
            ///if (denom != 0.0f) {
            if (FEQUAL(denom, 0) == 0)
            {
                s = clamp((b*f - c*e) / denom, 0.0f, 1.0f);
            }
            else s = 0.0f;
            // Compute point on L2 closest to S1(s) using
            // t = Dot((P1 + D1*s) - P2,D2) / Dot(D2,D2) = (b*s + f) / e
            t = (b*s + f) / e;
            // If t in [0,1] done. Else clamp t, recompute s for the new value
            // of t using s = Dot((P2 + D2*t) - P1,D1) / Dot(D1,D1)= (t*b - c) / a
            // and clamp s to [0, 1]
            if (t < 0.0f)
            {
                t = 0.0f;
                s = clamp(-c / a, 0.0f, 1.0f);
            }
            else
            {
                if (t > 1.0f)
                {
                    t = 1.0f;
                    s = clamp((b - c) / a, 0.0f, 1.0f);
                }
            }
        }
    }
    //cout<<"s "<<s<<" t "<<t<<endl;
    Vertex d1_s(d1_[0]*s, d1_[1]*s, d1_[2]*s);
    Vertex d2_s(d2_[0]*t, d2_[1]*t, d2_[2]*t);
    d1_s = d1_s + p1_;
    d2_s = d2_s + p2_;
    //cout<<"c1_ "; printVector(d1_);
    //cout<<"c2_ "; printVector(d2_);
    /// saving points on the segment
    //gsl_vector_memcpy(pt1, d1_);
    //gsl_vector_memcpy(pt2, d2_);
    pt1 = d1_s;
    pt2 = d2_s;
    d1_s = d1_s-d2_s;
    //cout<<"dist: \t\t    "<<gsl_blas_dnrm2(d1_)<<endl;
    s = d1_s.Length();


    /*gsl_vector_free(d1_);
    gsl_vector_free(d2_);
    gsl_vector_free(p1_);
    gsl_vector_free(p2_);
    gsl_vector_free(q1_);
    gsl_vector_free(q2_);
    gsl_vector_free(r__);*/

    return s;
}



}
