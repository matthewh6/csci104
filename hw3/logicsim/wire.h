#ifndef WIRE_H
#define WIRE_H
#include <string>

class Wire 
{
    public:
        Wire(int, std::string name="");
        const char& getState() const;
        std::string setState(char, uint64_t);
        void wireInput(int id, Wire* in);
        std::string getName() const;
        int getId() const;
        
    private:
        char m_state;
        std::string m_name;
        int m_id;
};

#endif
