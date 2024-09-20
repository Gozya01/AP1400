#include "Person.h"
#include "Utils.h"


Person::Person(std::string &name, size_t age, std::string &gender,
           std::string &fingerprint, size_t socioeconomic_rank, bool is_alive):
           name(name),age(age),gender(gender),hashed_fingerprint(std::hash<std::string>{}(fingerprint)),
           socioeconomic_rank(socioeconomic_rank),is_alive(is_alive){
                if(gender!="Female" && gender!="Male"){
                    throw std::invalid_argument("gender must be female or male");
                }
                if(socioeconomic_rank<1||socioeconomic_rank>10){
                    throw std::invalid_argument("socioeconomic_rank must be [0,10].");
                }
           }
std::string Person::get_name() const{
    return this->name;
}
size_t Person::get_age() const{
    return this->age;
}
std::string Person::get_gender() const{
    return this->gender;
}
size_t Person::get_hashed_fingerprint() const{
    return this->hashed_fingerprint;
}
size_t Person::get_socioeconomic_rank() const{
    return this->socioeconomic_rank;
}
bool Person::get_is_alive() const{
    return this->is_alive;
}

bool Person::set_age(size_t age){
    this->age=age;
    return true;
}
bool Person::set_socioeconomic_rank(size_t rank){
    // std::cout<<rank<<std::endl;
    if(rank>10){
        throw std::invalid_argument("rank must be [0,10]");
        return false;
    }
    this->socioeconomic_rank=rank;
    return true;
}
bool Person::set_is_alive(bool is_alive){
    this->is_alive=is_alive;
    return true;
}
std::strong_ordering Person::operator <=>(const Person &other) const
{
    return this->hashed_fingerprint <=>other.hashed_fingerprint;
}

void Person::get_info(std::optional<std::string> file_name ) const{
std::string file=file_name.value_or("no");
    if(file=="no"){
        std::cout<<"balance:"<<this->get_name()<<std::endl;
    }
    else {
        std::ofstream output_file(file);
        if(output_file.is_open()){
            output_file<<"balance:"<<this->get_name()<<std::endl;
            output_file.close();
        }
        else {
            throw std::runtime_error("open file failed.");
        }
    }
}
