#include "AstManagement.h"
#include <iostream>

AstManagement::AstManagement() {}

Asteroid* AstManagement::create(AST_SIZE size) {
	return new Asteroid(size);
}





