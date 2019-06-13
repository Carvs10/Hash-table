#include<iostream>
#include<cmath>

int main(){

	//std::cout << next_prime( 5 ) << "  \n";
	std::cout << " Hash (123) = " << std::hash < int >()( 123 ) << std::endl ;
	std::cout << " Hash ( -123) = " << std::hash < int >()( -123 ) << std::endl ;

	return 0;
}