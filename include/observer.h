#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <algorithm>

class observer{
    public:
        virtual ~observer() = default;
        virtual void update(const std::string& event, const int value, const std::string& source) = 0; // Pure virtual function to be implemented by concrete observers
};

class subject{
    protected:
        std::vector<std::shared_ptr<observer>> observers; // List of observers attached to the subject
    public:
        virtual ~subject() = default;
        void attach(std::shared_ptr<observer> obs){
            observers.push_back(obs); // Add an observer to the list
        }
        void detach(std::shared_ptr<observer> obs){
            observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end()); // Remove an observer from the list
        }
        void notify(const std::string& event,const int value = 0,const std::string& source = " "){
            for(auto obs : observers){
                obs->update(event, value, source); // Call the update function for each observer
            }
        }
    };