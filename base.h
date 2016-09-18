//
// Created by cubla on 12.09.2016.
//


#ifndef DRONE_BASE_H
#define DRONE_BASE_H
#include <string>
#include <vector>
#include <utility>
#include <map>

class Base
{
public:
    typedef void (*callback_req)(void*);
    Base();
    virtual ~Base();

    double on(std::string, callback_req);
    void off(double);
    void trigger(std::string, void* data);

private:
    double eventId = 0;
    std::map<std::string, std::pair<double, callback_req>> _events;
};



#endif //DRONE_BASE_H
