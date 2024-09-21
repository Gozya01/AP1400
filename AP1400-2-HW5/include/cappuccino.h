#pragma once

#include "ingredient.h"
#include "espresso_based.h"
#include <vector>
#include <type_traits>
class Cappuccino:public EspressoBased
{
public:
    Cappuccino(){
        side_items.clear();
    }
    std::vector<Ingredient*>& get_side_items(){
        return side_items;
    }
    Cappuccino(const Cappuccino& cap){
        // auto s=const_cast<Cappuccino&>(cap).get_side_items();
        auto s=cap.side_items;
        for(int i=0;i<s.size();++i){
            auto z=*s[i];
            using class_name=decltype(z);
            auto it=new class_name(*s[i]);
        }
    }
	~Cappuccino(){
        for(const auto&i:side_items){
            delete i;
        }
    }
    void operator=(const Cappuccino& cap){

    }

    virtual std::string get_name();
    virtual double price();

    void add_side_item(Ingredient* side);
    

private:
    std::vector<Ingredient*> side_items;

};