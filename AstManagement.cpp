#include "AstManagement.h"
#include <iostream>

AstManagement::AstManagement()
{
}

Asteroid* AstManagement::create(AST_SIZE size) {
	std::cout << "AstManagement::create(AST_SIZE size = " << size << ")\n";
	return new Asteroid(size);
}





