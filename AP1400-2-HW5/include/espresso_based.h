#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H

#endif // ESPRESSO_BASED_H
#include<string>
#include<vector>
#include<iostream>
#include"ingredient.h"
class EspressoBased
{
public:
    virtual std::string get_name() = 0;
    virtual double price() = 0;
    EspressoBased()=default;
    void brew(){
        for(const auto&i:ingredients){
            std::cout<<i->get_name()<<std::endl;
        }
    }
    std::vector<Ingredient*>& get_ingredients(){
        return ingredients;
    }

    ~EspressoBased()
    {
        for(const auto& i : ingredients)
            delete i;
        ingredients.clear();
    }

protected:
    EspressoBased();
    EspressoBased(const EspressoBased& esp);
    void operator=(const EspressoBased& esp);

    std::vector<Ingredient*> ingredients;
    std::string name;
};
