#include <stdio.h>

#include "Box2D/Box2D.h"

int main(int argc, char const* argv[]) {
    printf("Application started.\n");
    b2World world(b2Vec2(0, -0.98));


    b2Body* groundBody = [&world]() {
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0, -10.0);
        return world.CreateBody(&groundBodyDef);
    }();

    {
        b2PolygonShape groundBox;
        groundBox.SetAsBox(50, 10);
        groundBody->CreateFixture(&groundBox, 0.0f);
    }

    b2Body* body = [&world]() {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(0, 5.0);
        bodyDef.angle = 25.0f * (b2_pi / 180.0f);
        return world.CreateBody(&bodyDef);
    }();

    
    [&body]() {
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(1, 1);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;

        body->CreateFixture(&fixtureDef);
    }();


    float timeStep = 1.0f / 60.0f;
    int velocityIterations = 6;
    int positionIterations = 2;

    for (int i = 0; i < 200; i++) {
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        printf("[%i] %4.2f %4.2f %4.2f\n", i, position.x, position.y, angle);
    }


    return 0;
}
