#include<iostream>

int main(){

	std::cout<< "ola mundo!!!\n";
	std::cout << " Hash (123) = " << std::hash < int >()( 123 ) << std::endl ;
	std::cout << " Hash ( -123) = " << std::hash < int >()( -123 ) << std::endl ;

	return 0;
}