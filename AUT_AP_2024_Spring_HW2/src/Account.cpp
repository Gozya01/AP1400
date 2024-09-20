#include "Account.h"
#include "Bank.h"
#include "Person.h"
#include "Utils.h"

Account::Account(const Person* const owner, const Bank* const bank, std::string& password)
        : bank(bank),account_number(get_random_string(16)),CVV2("1234"),password(password){
            this->owner=const_cast<Person*>(owner);
            balance=0.0;
            account_status=true; 
            exp_date="11-22";
}

const Person* Account::get_owner() const{
    return const_cast<const Person *>(this->owner);
}
double Account::get_balance() const{
    return this->balance;
}
std::string Account::get_account_number() const{
    return this->account_number;
}
bool Account::get_status() const{
    return this->account_status;
}
std::string Account::get_CVV2(std::string& owner_fingerprint) const{
    if(std::hash<std::string>{}(owner_fingerprint)!=this->owner->get_hashed_fingerprint()){
        throw std::runtime_error("fingerprint not match.");
    }
    return this->CVV2;
}
std::string Account::get_password(std::string& owner_fingerprint) const{
     if(std::hash<std::string>{}(owner_fingerprint)!=this->owner->get_hashed_fingerprint()){
        throw std::runtime_error("fingerprint not match.");
    }
    return this->password;
}
std::string Account::get_exp_date(std::string& owner_fingerprint) const{
    if(std::hash<std::string>{}(owner_fingerprint)!=this->owner->get_hashed_fingerprint()){
        throw std::runtime_error("fingerprint not match.");
    }
    return this->exp_date;
}

bool Account::set_password(std::string& password, std::string& owner_fingerprint){
    if(std::hash<std::string>{}(owner_fingerprint)!=this->owner->get_hashed_fingerprint()){
        throw std::runtime_error("fingerprint not match.");
    }
    this->password=password;
    return true;
}
std::strong_ordering Account::operator<=>(const Account &other) const
{
    return this->account_number <=> other.account_number;
}
void Account::get_info(std::optional<std::string> file_name) const{
    std::string file=file_name.value_or("no");
    if(file=="no"){
        std::cout<<"balance:"<<this->get_balance()<<std::endl;
        std::cout<<"account_number:"<<this->get_account_number()<<std::endl;
        std::cout<<"status:"<<this->get_status()<<std::endl;
    }
    else {
        std::ofstream output_file(file);
        if(output_file.is_open()){
            output_file<<"balance:"<<this->get_balance()<<std::endl;
            output_file<<"account_number:"<<this->get_account_number()<<std::endl;
            output_file<<"status:"<<this->get_status()<<std::endl;
            output_file.close();
        }
        else {
            throw std::runtime_error("open file failed.");
        }
    }
}
bool Account::add_value(const std::string&owner_fingerprint,double value){
    if(std::hash<std::string>{}(owner_fingerprint)!=this->owner->get_hashed_fingerprint()){
        // throw std::runtime_error("fingerprint not match.");
    }
    this->balance+=value;
    return true;
}