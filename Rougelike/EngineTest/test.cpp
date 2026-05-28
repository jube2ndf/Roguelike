#include "pch.h"
#include "../Engine/TransformComponent.h"

TEST(VectorTests, ZeroContructor)
{
	
	Engine::TransformComponent comp;
	EXPECT_EQ(0, 0);
}
