#include <vector>
#include <random>
#include <iostream>
#include <sstream>
#include <fstream>

//#include "../heap.h" //bring in your heap implementation
#include "heap.h"
#include "wire.h"
#include "gate.h"
#include "circuit.h"
#include "event.h"

Circuit::Circuit() : m_current_time(0)
{
    
}

Circuit::~Circuit()
{
    for(auto i : m_wires)
    {
        delete i;
    }
    for(auto i : m_gates)
    {
        delete i;
    }
}

void Circuit::test()
{
    m_wires.push_back(new Wire(0, "input A"));
	m_wires.push_back(new Wire(1, "input B"));
	m_wires.push_back(new Wire(2, "output"));
    
    Gate* g = new And2Gate(m_wires[0], m_wires[1], m_wires[2]);
	m_gates.push_back(g);
    
	Event* e = new Event {0,m_wires[0],'0'};
	m_pq.push(e);
	
	e = new Event {0,m_wires[1],'1'};
	m_pq.push(e);
	
	e = new Event {4,m_wires[0],'1'};
	m_pq.push(e);

  e = new Event {6,m_wires[1],'0'};
	m_pq.push(e);
	
}

bool Circuit::parse(const char* fname)
{
    std::ifstream inFile(fname);
    if(!inFile)
    {
        return false;
    }
    
    std::string line;
    while( getline(inFile, line))
    {
        if(line == "WIRES")
        {
            std::string t_line;
            getline(inFile,t_line);
            int n = stoi(t_line);
            for(int i = 0;i<n;i++)
            {
                getline(inFile,t_line);
                std::stringstream ss(t_line);
                std::string s_id;
                getline(ss, s_id, ',');
                std::string s_name;
                getline(ss, s_name, ',');
                m_wires.push_back(new Wire(stoi(s_id), s_name));
            }
        }
        if(line == "GATES")
        {
            std::string t_line;
            getline(inFile,t_line);
            int n = stoi(t_line);
            for(int i = 0;i<n;i++)
            {
                getline(inFile,t_line);
                std::stringstream ss(t_line);
                std::string s_type;
                getline(ss, s_type, ',');
                if(s_type == "AND2")
                {
                    std::string s_in1;
                    getline(ss, s_in1, ',');
                    std::string s_in2;
                    getline(ss, s_in2, ',');
                    std::string s_output;
                    getline(ss, s_output, ',');
                    m_gates.push_back(new And2Gate(m_wires[stoi(s_in1)], m_wires[stoi(s_in2)], m_wires[stoi(s_output)]));
                }
                if(s_type == "OR2")
                {
                    std::string s_in1;
                    getline(ss, s_in1, ',');
                    std::string s_in2;
                    getline(ss, s_in2, ',');
                    std::string s_output;
                    getline(ss, s_output, ',');
                    m_gates.push_back(new Or2Gate(m_wires[stoi(s_in1)], m_wires[stoi(s_in2)], m_wires[stoi(s_output)]));
                }
                //Add code here to support the NOT gate type
                if(s_type == "NOT")
                {
                    std::string s_in1;
                    getline(ss, s_in1, ',');
                    std::string s_output;
                    getline(ss, s_output, ',');
                    m_gates.push_back(new NotGate(m_wires[stoi(s_in1)], m_wires[stoi(s_output)]));
                }
            }
        }
        if(line == "INJECT")
        {
            std::string t_line;
            getline(inFile,t_line);
            int n = stoi(t_line);
            for(int i = 0;i<n;i++)
            {
                getline(inFile,t_line);
                std::stringstream ss(t_line);
                std::string s_time;
                getline(ss, s_time, ',');
                std::string s_wire;
                getline(ss, s_wire, ',');
                std::string s_state;
                getline(ss, s_state, ',');
            	Event* e = new Event {static_cast<uint64_t>(stoi(s_time)),m_wires[stoi(s_wire)],s_state[0]};
                //std::cout << s_time << "," << s_wire << "," << s_state << std::endl;
            	m_pq.push(e);
            }
        }
    }
    return true;
}

bool Circuit::advance(std::ostream& os)
{
	if(m_pq.size() == 0)
	{
		return false;
	}
    
    m_current_time = m_pq.top()->time;
    std::stringstream ss;
    ss << "@" << m_current_time << std::endl;
    bool updated = false;
    
    while(m_pq.top()->time == m_current_time)
    {
        if(m_pq.size() >= 1)
        {
            std::string temp = m_pq.top()->wire->setState(m_pq.top()->state, m_current_time);
            if(temp != "")
            {
                ss << temp << std::endl;
                updated = true;
            }
            delete m_pq.top();
            m_pq.pop();
            if(m_pq.size() == 0) break;
        }
        else
        {
            break;
        }
        
    }
    if(updated)
    {
        os << ss.str();
    }
    for(auto g : m_gates)
    {
        Event* e = g->update(m_current_time);
        if(e)
        {
            m_pq.push(e);
        }
    }
	return true;
}

void Circuit::run(std::ostream& os)
{
	
	while(advance(os)){
        
	}
}

void Circuit::startUml(std::ostream& os)
{
	os << "@startuml" << std::endl;
    for(auto w : m_wires)
    {
        if(w->getName().size() > 0)
				{
					os << "binary " << "\"" << w->getName() << "\"" << " as W" << w->getId() << std::endl;
				}
		}
    os << std::endl;
    os << "@0" << std::endl;
    for(auto w : m_wires)
    {
        if(w->getName().size() > 0)
				{
					os << "W" << w->getId() << " is {low,high} " << std::endl;
				}
		}
    os << std::endl;
    
}

void Circuit::endUml(std::ostream& os)
{
    os << "@enduml" << std::endl;
}
