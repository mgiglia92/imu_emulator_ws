#ifndef SERIAL_STATE_MACHINE_H
#define SERIAL_STATE_MACHINE_H
#include <string>
#include <iostream>
#include <CppLinuxSerial/Exception.hpp>

using namespace std;
namespace SerialStateMachine{
    struct StateMachine
    {
        std::string bom = "$";
        std::string eom = "%";
        std::string previous = "";
        std::string current = "";
        std::string incoming = "";
        bool ready = false;
    };
    void smInit(StateMachine *sm, std::string bom = "$", std::string eom = "%")
    {   
        sm->previous="";
        sm->current = "";
        sm->incoming = "";
        sm->ready = false;
    }



    int16_t findBOM(std::string *s, std::string *bom)
    {
        return s->find(*bom, 0);
    }

    int16_t findEOM(std::string *s, std::string *eom)
    {
        return s->find(*eom, 0);

    }

    void update(StateMachine* sm)
    {
        StateMachine m = *sm;
        //See Data at beginning of incoming is equivalent to a valid string
        int16_t somPos = findBOM(&m.incoming, &m.bom);
        int16_t eomPos = findEOM(&m.incoming, &m.eom);
        stringstream ss;
        // ss << bomPos;
        // cout << ss.str() <<  std::endl;

        if(somPos != string::npos && eomPos !=string::npos)
        {
            sm->previous = sm->current;
            sm->current = sm->incoming;
            sm->incoming = "";
        }
        // else if(somPos > 0)
        // {
        //     //Remove character up till SOM
        //     sm->incoming = sm->incoming.substr(0, somPos-1);
        // }
        // cout << somPos << std::endl;
    }

    void append(struct StateMachine *sm, std::string data)
    {
        sm->incoming.append(data);
        update(sm);
        
    }
}
#endif 