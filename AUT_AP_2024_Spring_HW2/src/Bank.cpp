#include "Bank.h"
#include "Person.h"
#include "Account.h"
#include "Utils.h"
Bank::Bank(const std::string& bank_name, const std::string& bank_fingerprint):
           bank_name(bank_name),hashed_bank_fingerprint(std::hash<std::string>{}(bank_fingerprint)){
    bank_customers.clear();
    bank_accounts.clear();
    account_2_customer.clear();
    customer_2_accounts.clear();
    customer_2_paid_loan.clear();
    customer_2_unpaid_loan.clear();
    bank_total_balance=0; // Total bank profit
    bank_total_loan=0; // Total loans issued
}
Account* Bank::create_account(Person& owner, const std::string& owner_fingerprint, std::string password){
    if(owner.get_hashed_fingerprint()!=std::hash<std::string>{}(owner_fingerprint)){
        throw std::runtime_error("fingerprint not match");
    }
    Account *acc=new Account(&owner,this,password);
    bank_accounts.push_back(acc);
    account_2_customer[acc]=&owner;
    if(this->customer_2_accounts.count(&owner)){
        //add 账户
        customer_2_accounts[&owner].push_back(acc);
    }
    else {
        customer_2_accounts[&owner]=std::vector<Account*>{acc};
        bank_customers.push_back(&owner);
    }
    return acc;
}

bool Bank::delete_account(Account& account, const std::string& owner_fingerprint){
    if(account.get_owner()->get_hashed_fingerprint()!=std::hash<std::string>{}(owner_fingerprint)){
        throw std::runtime_error("fingerprint not match!");
    }
    if(!customer_2_accounts.count(const_cast<Person*>(account.get_owner()))){
        throw std::runtime_error("no account1!");
    }
    if(!account_2_customer.count(&account)){
        throw std::runtime_error("no account2!");
    }
    const Person *owner=account.get_owner();
    double ex=1e-6;
    if(customer_2_unpaid_loan[const_cast<Person*>(owner)]>ex){
        throw std::runtime_error("exist unpaid.");
    }
    account_2_customer.erase(&account);
    std::vector<Account*> &acc=customer_2_accounts[const_cast<Person*>(owner)];
    for(auto it=acc.begin();it!=acc.end();it++){
        if((*(*it))==account){
            acc.erase(it);
            break;
        }
    }
    if(acc.size()==0){
        customer_2_accounts.erase(const_cast<Person*>(owner));
    }
    for(auto it=bank_accounts.begin();it!=bank_accounts.end();it++){
        if(**it==account){
            bank_accounts.erase(it);
            break;
        }
    }
    return true;
}

bool Bank::delete_customer(Person& owner, const std::string& owner_fingerprint){
    if(owner.get_hashed_fingerprint()!=std::hash<std::string>{}(owner_fingerprint)){
        throw std::runtime_error("fingerprint not match!");
    }
    if(!customer_2_accounts.count(&owner) ){
        throw std::runtime_error("no such person!");
    }
    std::vector<Account*> &acc=customer_2_accounts[&owner];
    for(int i=0;i<(int)acc.size();i++){
        if (delete_account(*acc[i],owner_fingerprint)==false){
            throw std::runtime_error("delete account failed.");
        }
    }
    for(auto it=bank_customers.begin();it!=bank_customers.end();it++){
        if(**it>=owner&&**it<=owner){
            bank_customers.erase(it);
            break;
        }
    }
    // customer_2_accounts.erase(&owner);
    // todo
    // customer_2_paid_loan
    // customer_2_unpaid_loan
    return true;
}

bool Bank::deposit(Account& account, const std::string& owner_fingerprint, double amount){
    if(account.get_owner()->get_hashed_fingerprint()!=std::hash<std::string>{}(owner_fingerprint)){
        throw std::runtime_error("fingerprint not match");
    }
    if(!account_2_customer.count(&account)){
        throw std::runtime_error("no such account.");
    }
    account.add_value(owner_fingerprint,amount);
    return true;
}

bool Bank::withdraw(Account& account, const std::string& owner_fingerprint, double amount){
    if(account.get_owner()->get_hashed_fingerprint()!=std::hash<std::string>{}(owner_fingerprint)){
        throw std::runtime_error("fingerprint not match");
    }
    if(!account_2_customer.count(&account)){
        throw std::runtime_error("no such account.");
    }
    if(account.get_balance()<amount){
        throw std::runtime_error("no such money");
    }
    account.add_value(owner_fingerprint,-amount);
    return true;
}
bool Bank::transfer(Account& source, Account& destination, const std::string& owner_fingerprint,
            const std::string& CVV2, const std::string& password, 
            const std::string& exp_date, double amount){
            // std::cout<<exp_date<<" "<<password<<" "<<CVV2<<std::endl;
            if(exp_date=="1"&&password=="1"&&CVV2=="1"){}
    if(source.get_owner()->get_hashed_fingerprint()!=std::hash<std::string>{}(owner_fingerprint)
        || 
        destination.get_owner()->get_hashed_fingerprint()!=std::hash<std::string>{}(owner_fingerprint)
        ){
            // throw std::runtime_error("no account.");
        }
    if(source.get_balance()<amount){
        throw std::runtime_error("no money.");
    }
    source.add_value(owner_fingerprint,-amount);
    destination.add_value(owner_fingerprint,amount);
    return true;
}
bool Bank::take_loan(Account& account, const std::string& owner_fingerprint, double amount){
    if(account.get_owner()->get_hashed_fingerprint()!=std::hash<std::string>{}(owner_fingerprint)){
        throw std::runtime_error("no account.");
    }
    double tot_balance=0;
    const Person *owner=account.get_owner();
    std::vector<Account*> &accs=customer_2_accounts[const_cast<Person*>(owner)];
    for(auto it=accs.begin();it!=accs.end();it++){
        tot_balance+=(*it)->get_balance();
    }
    tot_balance*=0.1*owner->get_socioeconomic_rank();
    double total_loans=0;
    if(customer_2_unpaid_loan.count(const_cast<Person*>(owner))){
        total_loans=customer_2_unpaid_loan[const_cast<Person*>(owner)];
    }
    std::cout<<amount<<" "<<total_loans<<" "<<tot_balance<<std::endl;
    if(total_loans+amount>tot_balance){
        throw std::runtime_error("no money."); 
    }
    customer_2_unpaid_loan[const_cast<Person*>(owner)]+=amount+amount*10/owner->get_socioeconomic_rank()/100;
    bank_total_balance+=amount*10/owner->get_socioeconomic_rank()/100;
    bank_total_loan+=amount+amount*10/owner->get_socioeconomic_rank()/100;
    return true;
}
bool Bank::pay_loan(Account& account, double amount){
    const Person *owner=account.get_owner();
    customer_2_unpaid_loan[const_cast<Person*>(owner)]-=amount;
    customer_2_paid_loan[const_cast<Person*>(owner)]+=amount;
    int rank=0;
    double rank_money=1;
    double pay_loan=customer_2_paid_loan[const_cast<Person*>(owner)];
    while(rank<10&&rank_money<pay_loan){
        rank++;
        rank_money*=10;
    }
    if((int)const_cast<Person*>(owner)->get_socioeconomic_rank()<rank)
        const_cast<Person*>(owner)->set_socioeconomic_rank((size_t)rank);
    return true;
}

const std::vector<Person*>& Bank::get_bank_customers(std::string& bank_fingerprint) const{
    if(this->get_hashed_bank_fingerprint()!=std::hash<std::string>{}(bank_fingerprint)){
        throw std::runtime_error("fingerprint not match!\n");
    }
    return this->bank_customers;
}
const std::vector<Account*>& Bank::get_bank_accounts(std::string& bank_fingerprint) const{
    if(this->get_hashed_bank_fingerprint()!=std::hash<std::string>{}(bank_fingerprint)){
        throw std::runtime_error("fingerprint not match!\n");
    }
    return this->bank_accounts;
}
const std::map<Account*, Person*>& Bank::get_account_2_customer_map(std::string& bank_fingerprint) const{
    if(this->get_hashed_bank_fingerprint()!=std::hash<std::string>{}(bank_fingerprint)){
        throw std::runtime_error("fingerprint not match!\n");
    }
    return this->account_2_customer;
}
const std::map<Person*, std::vector<Account*>>& Bank::get_customer_2_accounts_map(std::string& bank_fingerprint) const{
    if(this->get_hashed_bank_fingerprint()!=std::hash<std::string>{}(bank_fingerprint)){
        throw std::runtime_error("fingerprint not match!\n");
    }
    return this->customer_2_accounts;
}
const std::map<Person*, double>& Bank::get_customer_2_paid_loan_map(std::string& bank_fingerprint) const{
    if(this->get_hashed_bank_fingerprint()!=std::hash<std::string>{}(bank_fingerprint)){
        throw std::runtime_error("fingerprint not match!\n");
    }
    return this->customer_2_paid_loan;
}
const std::map<Person*, double>& Bank::get_customer_2_unpaid_loan_map(std::string& bank_fingerprint) const{
    if(this->get_hashed_bank_fingerprint()!=std::hash<std::string>{}(bank_fingerprint)){
        throw std::runtime_error("fingerprint not match!\n");
    }
    return this->customer_2_unpaid_loan;
}
double Bank::get_bank_total_balance(std::string& bank_fingerprint) const{
    if(this->get_hashed_bank_fingerprint()!=std::hash<std::string>{}(bank_fingerprint)){
        throw std::runtime_error("fingerprint not match!\n");
    }
    return this->bank_total_balance;
}
double Bank::get_bank_total_loan(std::string& bank_fingerprint) const{
    if(this->get_hashed_bank_fingerprint()!=std::hash<std::string>{}(bank_fingerprint)){
        throw std::runtime_error("fingerprint not match!\n");
    }
    return this->bank_total_loan;
}

 bool Bank::set_owner(Account& account, const Person* new_owner, std::string& owner_fingerprint, std::string& bank_fingerprint){
    if(this->get_hashed_bank_fingerprint()!=std::hash<std::string>{}(bank_fingerprint)){
        throw std::runtime_error("bank fingerprint not match!\n");
    }
    if(new_owner->get_hashed_fingerprint()!=std::hash<std::string>{}(owner_fingerprint)){
        throw std::runtime_error("owner fingerprint not match!\n");
    }
    // const Person* old_owner=account.get_owner();
    account.set_owner(new_owner);
    //todo yichu
    return true;
 }

bool Bank::set_account_status(Account& account, bool status, std::string& bank_fingerprint){
    if(this->get_hashed_bank_fingerprint()!=std::hash<std::string>{}(bank_fingerprint)){
        throw std::runtime_error("bank fingerprint not match!\n");
    }
    account.set_status(status);
    return true;
}
bool Bank::set_exp_date(Account& account, std::string& exp_date, std::string& bank_fingerprint){
    if(this->get_hashed_bank_fingerprint()!=std::hash<std::string>{}(bank_fingerprint)){
        throw std::runtime_error("bank fingerprint not match!\n");
    }
    account.set_exp_data(exp_date);
    return true;
}
void Bank::get_info(std::optional<std::string> file_name) const{
    std::string file=file_name.value_or("no");
    if(file=="no"){
        std::cout<<"balance:"<<this->bank_name<<std::endl;
    }
    else {
        std::ofstream output_file(file);
        if(output_file.is_open()){
            output_file<<"balance:"<<this->bank_name<<std::endl;
            output_file.close();
        }
        else {
            throw std::runtime_error("open file failed.");
        }
    }
}
const std::string& Bank::get_bank_name() const{
    return this->bank_name;
}
size_t Bank::get_hashed_bank_fingerprint() const{
    return this->hashed_bank_fingerprint;
}