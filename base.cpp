//
// Created by cubla on 12.09.2016.
//

#include "base.h"
Base::Base() {
}

Base::~Base() {

}

double Base::on(std::string name, callback_req callback)
{
    this->_events.insert(std::pair<std::string, std::pair<double, callback_req>>(name, std::pair<double,callback_req >(this->eventId, callback)));
    return this->eventId++;
}

void Base::off(double id)
{
    std::map<std::string, std::pair<double, callback_req>>::iterator it = this->_events.begin();
    std::map<std::string, std::pair<double, callback_req>>::iterator it_end = this->_events.end();
    while (it != it_end)
    {
        if (it->second.first == id)
        {
            this->_events.erase(it);
            break;
        }
        it++;
    }
}

void Base::trigger(std::string name, void* data)
{
    std::map<std::string, std::pair<double, callback_req>>::iterator it = this->_events.begin();
    std::map<std::string, std::pair<double, callback_req>>::iterator it_end = this->_events.end();
    while (it != it_end)
    {
        if (it->first == name)
        {
            it->second.second(data);
        }
        it++;
    }
}
