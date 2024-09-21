#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#endif // SUB_INGREDIENTS_H
#include "ingredient.h"

#define DEFCLASS(Name,Price)\
class Name:public Ingredient{\
public:\
    Name(size_t units) : Ingredient{Price, units}\
    {\
        this->name = #Name;\
    }\
    Name(const Name & other){\
        price_unit=other.price_unit;\
        units=other.units;\
        name=other.name;\
    }\
    virtual std::string get_name() {return this->name;}\
};

DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);

