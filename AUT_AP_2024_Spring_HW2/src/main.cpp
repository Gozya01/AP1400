#include <gtest/gtest.h>

#include <iostream>

#include "Account.h"
#include "Bank.h"
#include "Person.h"
#include "Utils.h"

int main(int argc, char **argv) {
	if (false)  // make false to run unit-tests
	{
		// debug section
		std::string name="zya";
		size_t age=24;
		std::string gender="male";
		std::string fingerprint="1";
		size_t set_socioeconomic_rank=10;
		bool is_alive=false;
		std::string password="123456";
		Person x(name,age,gender,fingerprint,set_socioeconomic_rank,is_alive);

		std::string bank_name="bank";
		std::string bank_fingerprint="2";
		Bank b(bank_name,bank_fingerprint);
		Account *a=b.create_account(x,fingerprint,password);
		b.deposit(*a,fingerprint,32);
		// std::cout<<b.delete_customer(x,fingerprint)<<std::endl;
		// if(a==nullptr)std::cout<<222222<<std::endl;
		// std::cout<<a->get_owner()->get_name()<<std::endl;
		// std::cout<<b.delete_account(*a,fingerprint)<<std::endl;
		// std::cout<<b.delete_account(*a,fingerprint)<<std::endl;
		// Person y(name,age,gender,fingerprint,set_socioeconomic_rank,is_alive);
		// std::cout<< ((x<=y)&&(x>=y)) <<std::endl;
	} else {
		// std::cout<<argc<<" "<<argv;
		::testing::InitGoogleTest(&argc, argv);
		std::cout << "RUNNING TESTS ..." << std::endl;
		int ret{RUN_ALL_TESTS()};
		if (!ret)
			std::cout << "<<<SUCCESS>>>" << std::endl;
		else
			std::cerr << "FAILED" << std::endl;
	}
	return 0;
}
