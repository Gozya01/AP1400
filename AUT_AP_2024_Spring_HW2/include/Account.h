#ifndef ACCOUNT_H // Prevents double inclusion of this header
#define ACCOUNT_H

#include <compare>  // For std::strong_ordering
#include <optional> // For std::optional
#include <string>   // For std::string
#include <unordered_set>

class Bank; // Forward declaration of Bank
class Person; // Forward declaration of Person

// Represents a bank account with owner, bank, balance, status, and credentials
class Account {
    friend class Bank; // Make Bank a friend of Account for full access

public:
    // Constructor with owner, bank, and password
    Account(const Person* const owner, const Bank* const bank, std::string& password);

    // Getters
    const Person* get_owner() const;
    double get_balance() const;
    std::string get_account_number() const;
    bool get_status() const;

    // Getters requiring owner's fingerprint for authentication
    std::string get_CVV2(std::string& owner_fingerprint) const;
    std::string get_password(std::string& owner_fingerprint) const;
    std::string get_exp_date(std::string& owner_fingerprint) const;

    // Setters requiring owner's fingerprint for authentication
    bool set_password(std::string& password, std::string& owner_fingerprint);
    bool add_value(const std::string&owner_fingerprint,double value);
    bool set_owner(const Person* owner){
        this->owner=const_cast<Person*>(owner);
        return true;
    }
    bool set_status(bool status){
        this->account_status=status;
        return true;
    }
    bool set_exp_data(const std::string&exp_date){
        this->exp_date=exp_date;
        return true;
    }

    // Spaceship operator for Account comparison
    std::strong_ordering operator <=> (const Account& other) const;
    bool operator==(const Account& other) const {
        return this->account_number == other.account_number;
    }
        // return this->account_number <=> other.account_number;
    // }

    // Outputs account information, supports writing to file
    void get_info(std::optional<std::string> file_name = std::nullopt) const;

private:
    // Member variables
    Person* owner;
    const Bank* bank;
    const std::string account_number;
    double balance;
    bool account_status;

    // Credential variables
    const std::string CVV2;
    std::string password;
    std::string exp_date;
};

#endif // ACCOUNT_H
