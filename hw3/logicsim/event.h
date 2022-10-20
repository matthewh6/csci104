#ifndef EVENT_H
#define EVENT_H
#include "wire.h"

struct Event
{
    uint64_t time;
    Wire* wire;
    char state;
};

typedef struct EventLess {
        //write the operator() required to make this a functor that compares Events by time
         bool operator()(Event* e1, Event* e2) {
					return (e1->time < e2->time);
				}
} EventLess;
	
#endif
