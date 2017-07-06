#include "Particle.h"
#include <iostream>
#include <cmath>

Particle::Particle()
{
	location = sf::Vector3f(0, 0,0);
	velocity = sf::Vector3f(0, 0,0);
//	acceleration = sf::Vector2f(0, 0);

	this->collision = false;

    this->top = sf::Vector3f(0, 0,-5.0f);
    this->bottom = sf::Vector3f(0,0,5);
    this->right = sf::Vector3f(10.0f, 0,0);
    this->left = sf::Vector3f(-10.f,0,0);
}

Particle::Particle(const sf::Vector3f &location, const GLuint &texture)
{
    this->location = location;
    this->velocity = sf::Vector3f();
//        this->acceleration = sf::Vector2f();
    
    this->texture_handle = texture;
    
    this->collision = false;
    
    this->top = sf::Vector3f(0, 0,-5.0f);
    this->bottom = sf::Vector3f(0,0,5);
    this->right = sf::Vector3f(10.0f, 0,0);
    this->left = sf::Vector3f(-10.f,0,0);
    
}

GLuint Particle::getTextureHandle()
{
    return texture_handle;
}
void Particle::setRotate(const sf::Vector3f &rotate)
{
    this->rotate = rotate;
}
void Particle::setLocation(const sf::Vector3f &location)
{
    this->location = location;
}
void Particle::setVelocity(const sf::Vector3f &velocity)
{
    this->velocity = velocity;
}
void Particle::setCollision(bool collision)
{
    this->collision = collision;
}
bool Particle::getCollision(){
    return collision;
}


void Particle::update(const sf::Time &deltaTime)
{
    float x=0.01f;

    
    if (velocity.x != 0 && velocity.x > 0) {
      
        velocity.x = velocity.x - (x * deltaTime.asSeconds());
        
    }
    if (velocity.x != 0 && velocity.x < 0) {
        
        velocity.x = velocity.x + (x * deltaTime.asSeconds());
        
    }
    
    if (velocity.z != 0 && velocity.z > 0) {
        
        velocity.z = velocity.z - (x * deltaTime.asSeconds());
        
    }
    if (velocity.z != 0 && velocity.z < 0) {
        
        velocity.z = velocity.z + (x * deltaTime.asSeconds());
    }

    
    location = location + velocity;
    rotate = rotate + (velocity * 100.f);
}

sf::Vector3f Particle::getLocation()
{
    return location;
}

sf::Vector3f Particle::getVelocity()
{
    return velocity;
}
sf::Vector3f Particle::getRotate()
{
    return rotate;
}

bool Particle::checkCollision(std::list<Particle> &particles)
{
    for (std::list<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
    {
        sf::Vector3f difference = location - it->getLocation();

        float distance = magnitude(difference);

        float radiusSum = .5f + .5f;
        
        if (collision)
        {
            if (distance != 0.0f)
            {
                if (distance > radiusSum)
                {
                    collision = false;
                }
            }
        }
        else
        {
            if (distance != 0.0f)
            {
                if (distance <= radiusSum)
                {
                    
//                    if (velocity.x < -0.001) {
//                        velocity.x = -0.001;
//                    }
//                    if (velocity.z < -0.001) {
//                        velocity.z = -0.001f;
//                    }
//                    if (velocity.x < 0.001) {
//                        velocity.x = 0.001;
//                    }
//                    if (velocity.z < 0.001) {
//                        velocity.z = 0.001f;
//                    }
                    it->velocity = velocity;
                    velocity = velocity * -0.2f;
//                    std::cout << velocity.x << "  ,  " << velocity.z << std::endl;
                    collision = true;
                    break;
                }

            }
        }
    }
    return collision;
}

//bool Particle::distance(sf::Vector3f normal, sf::Vector3f plane,std::list<Particle> &particles)
//{
////    for (std::list<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
////    {
//        sf::Vector3f temp = location - plane;
//        
//        float scale = product(temp, normal);
//        
//        sf::Vector3f projection = normal * scale;
//        
//        float dist = magnitude(projection);
//        
//        //std::cout << "distance:" << dist << std::endl;
//        
//        if (dist <= .5f || dist >= 19.5)
//        {
//            return true;
//        }
//        else
//        {
//            return false;
//        }
////    }
//}

void Particle::checkEdges()
{
    if (location.z < -4.5f)
    {
        velocity.z = velocity.z * -1;
    }
    if (location.x <= -9.5f)
    {
        velocity.x = velocity.x * -1;
    }
    
    if(location.x >= 9.5f) {
        velocity.x = velocity.x * -1;
    }
    if(location.z > 4.5f) {
        velocity.z = velocity.z * -1;
    }
}

bool Particle::checkPocket()
{
    if ((location.x <= -9.3f && location.z <= -4.3f) || (location.x >= 9.3f && location.z >= 4.3f) || (location.x <= -9.3f && location.z >= 4.3f) || (location.x >= 9.3f && location.z <= -4.3f) || ((location.x <= .2f && location.x >= -.2f)  && location.z >= 4.3f) || ((location.x <= .2f && location.x >= -.2f) && location.z <= -4.3f)) {
        return true;
    }
    else
    {
        return false;
    }
}



float Particle::product(sf::Vector3f a, sf::Vector3f b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

sf::Vector3f Particle::normalize(sf::Vector3f vec)
{
    float m = magnitude(vec);
    
    return vec / m;
};

float Particle::magnitude(sf::Vector3f vector)
{
    return std::sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

Particle::~Particle()
{
}
