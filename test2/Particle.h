#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <GLUT/GLUT.h>


#pragma once

class Particle
{
	private:
        sf::Vector3f top;
        sf::Vector3f left;
        sf::Vector3f bottom;
        sf::Vector3f right;
        
        sf::Vector3f location;
        sf::Vector3f velocity;
    
        sf::Vector3f rotate;
    
        GLuint texture_handle;
      
        bool collision;
	public:
	
		
    
        sf::Vector3f getRotate();
        void setRotate(const sf::Vector3f &rotate);
    
		sf::Vector3f getVelocity();
		void setVelocity(const sf::Vector3f &velocity);
		
        //bool distance(sf::Vector3f normal, sf::Vector3f plane,std::list<Particle> &particles);
        float product(sf::Vector3f a, sf::Vector3f b);
        sf::Vector3f normalize(sf::Vector3f vec);
        float magnitude(sf::Vector3f vector);
    
		bool getCollision();
		void setCollision(bool collision);
    
		sf::Vector3f getLocation();
		void setLocation(const sf::Vector3f &location);
		void update(const sf::Time &deltaTime);
		bool checkCollision(std::list<Particle> &particles);
		void checkEdges();
		void checkWalls(sf::Vector2f start, sf::Vector2f end);
        bool checkPocket();
    
        GLuint getTextureHandle();
		
		Particle(const sf::Vector3f &location,const GLuint &texture);
		Particle();
		~Particle();
};

