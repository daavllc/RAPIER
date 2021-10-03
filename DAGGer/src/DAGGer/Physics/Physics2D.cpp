#include "drpch.h"
#include "Physics2D.h"

//	Box2D
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>

namespace DAGGer
{
	void Physics2D::ApplyForce(DrVec2 v2)
	{
		b2Body* body = (b2Body*)s_RB2D.RuntimeBody;
		body->ApplyForce( b2Vec2(v2.x, v2.y), body->GetWorldCenter(), true);
	}
	void Physics2D::ApplyLinearImpulse(DrVec2 v2)
	{
		b2Body* body = (b2Body*)s_RB2D.RuntimeBody;
		body->ApplyLinearImpulse(b2Vec2(v2.x, v2.y), body->GetWorldCenter(), true);
	}
	void Physics2D::SetTransform(DrVec2 v2)
	{
		b2Body* body = (b2Body*)s_RB2D.RuntimeBody;
		body->SetTransform(b2Vec2(v2.x, v2.y), 0.0f);
	}
}	//	END namespace DAGGer
