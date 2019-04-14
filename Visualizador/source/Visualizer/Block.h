#ifndef BLOCK_H
#define BLOCK_H

#include "Common.h"
#include "Contact.h"
#include <vector>

namespace Library
{
class Block
{
    public:
        Block(Contact *c);
        virtual ~Block();

        void SetBlock(int StartPoint);
        bool WasAdded() { return added; };
        void SetAddition(bool add) { added = add; };
        glm::vec3 GetColor() { return color; };
        unsigned int GetContentControlPointID(int i);
        unsigned int GetContentSize() { return content.size(); };
        void ClearBlock();

        void SaveBlock(std::string mFilePath);
        bool LoadBlock(std::string mFilePath, int &line, bool &end_of_blocks);

    protected:

    private:

        typedef enum
        {
            SIMPLE = 0,
            COMPOSED = 1,
            MULTIPLE = 2
        } contact_type;

        typedef struct
        {
            unsigned int cp_ids;
            unsigned int cnts;
            contact_type type;
            int contacts_size;
        } block_content;

        Contact *contacts;

        int segmentsPerCNT;
        int cnts;
        bool added = false; // para saber se o bloco foi adicionado a um superbloco
        glm::vec3 color;
        std::vector<block_content> content;

        void FillVector(std::vector<unsigned int>&vec, unsigned int id);
        bool contains(const std::vector<unsigned int>&a, const unsigned int b);

        int GetCNT(unsigned int id);
        int GetIndex(unsigned int id);
        unsigned int GetControlPointID(int cnt, int ind);
};
}
#endif // BLOCK_H
