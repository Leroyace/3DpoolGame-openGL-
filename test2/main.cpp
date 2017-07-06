#include "GL/glew.h"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp" // SFML OpenGL include
#include <GLUT/GLUT.h>
#include <iostream>
#include <cmath>
#include <list>
#include <Particle.h>
#include <random>

void drawTable() {
    
    glBegin(GL_QUADS);
    
    glTexCoord2f(1, 1);
    glVertex3f( -10.0f, .0f, -5.0f);
    glTexCoord2f(0, 1);
    glVertex3f(-10.0f, .0f, 5.0f);
    glTexCoord2f(0, 0);
    glVertex3f(10.0f,.0f, 5.0f);
    glTexCoord2f(1, 0);
    glVertex3f( 10.0f,.0f, -5.0f);
    
    glTexCoord2f(1, 1);
    glVertex3f( 10.0f, 2.0f, -5.0f);
    glTexCoord2f(0, 1);
    glVertex3f(-10.0f, 2.0f, -5.0f);
    glTexCoord2f(0, 0);
    glVertex3f(-10.0f,0.0f, -5.0f);
    glTexCoord2f(1, 0);
    glVertex3f( 10.0f,0.0f, -5.0f);
    
    glTexCoord2f(1, 1);
    glVertex3f( 10.0f, 2.0f, 5.0f);
    glTexCoord2f(0, 1);
    glVertex3f(-10.0f, 2.0f, 5.0f);
    glTexCoord2f(0, 0);
    glVertex3f(-10.0f,0.0f, 5.0f);
    glTexCoord2f(1, 0);
    glVertex3f( 10.0f,0.0f, 5.0f);
    
    glTexCoord2f(1, 1);
    glVertex3f( -10.0f, 2.0f, -5.0f);
    glTexCoord2f(0, 1);
    glVertex3f(-10.0f, 2.0f, 5.0f);
    glTexCoord2f(0, 0);
    glVertex3f(-10.0f,0.0f, 5.0f);
    glTexCoord2f(1, 0);
    glVertex3f(-10.0f,0.0f, -5.0f);
    
    glTexCoord2f(1, 1);
    glVertex3f( 10.0f, 2.0f, 5.0f);
    glTexCoord2f(0, 1);
    glVertex3f(10.0f, 2.0f, -5.0f);
    glTexCoord2f(0, 0);
    glVertex3f(10.0f,0.0f, -5.0f);
    glTexCoord2f(1, 0);
    glVertex3f(10.0f,0.0f, 5.0f);
    
    glEnd();
}


void createParticle(std::list <Particle> &particles, const sf::Vector3f &location,const int &texture,const sf::Vector3f &vec)
{

    Particle particle = Particle(location,texture);
    particle.setVelocity(vec);
    
    particles.push_front(particle);
}
int main()
{
    bool texturesOn = true;
    bool wireframe = false;
    bool mouseClicked = false;
    bool reset = false;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pool game");
    Particle particle;
    std::list <Particle> particles;
    //window.setFramerateLimit(100);
    
    // Create a clock for measuring time elapsed
    sf::Clock clock;
    sf::Time TimePerFrame = sf::seconds(1.f / 60);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // nicest perspective correction calculations
    
    //prepare OpenGL surface for HSR
    glClearDepth(1.f); // clear the z-buffer/depth buffer completely +1.0f is the furtherest away
    glClearColor(0.3f, 0.3f, 0.3f, 0.f); // set the background colour for when we clear the screen RGBA values in the 0.0 to 1.0 range. This gives us a nice grey background.
    
    float z = 0;
    
    const int size = 17;
    
    sf::Vector3f vec;
    
    GLuint texture_handle[size];
    sf::Image texture[size];
    if (texturesOn)
    {
        //load texture
        texture[0].loadFromFile("/Users/LeroyTse/Desktop/Xcode/3DpoolGame(openGL)/test2/image/pool_table.png");
        
        for (int i = 1; i < size-1; i++) {
            texture[i].loadFromFile("/Users/LeroyTse/Desktop/Xcode/3DpoolGame(openGL)/test2/image/Ball"+std::to_string(i)+".jpg");
        }
        texture[16].loadFromFile("/Users/LeroyTse/Desktop/Xcode/3DpoolGame(openGL)/test2/image/BallCue.jpg");
        
        glEnable(GL_TEXTURE_2D); // enable 2D textures
        glGenTextures(size, texture_handle); // allocate a texture handle within OpenGL
        
        for (int i = 0; i < size; i++) {
            // bind to the texture handle target
            glBindTexture(GL_TEXTURE_2D, texture_handle[i]);
            // import texture into OpenGL
            glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA,texture[i].getSize().x,texture[i].getSize().y,0,GL_RGBA, GL_UNSIGNED_BYTE, texture[i].getPixelsPtr());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
    }
    
//    createParticle(particles,sf::Vector3f(-5,0,0),2,vec);
//    createParticle(particles,sf::Vector3f(-4,0,0.6),4,vec);
//    createParticle(particles,sf::Vector3f(-4,0,-0.6),12,vec);
 
    createParticle(particles,sf::Vector3f(3,0,0),2,vec);
    
    createParticle(particles,sf::Vector3f(4.1,0,0.6),4,vec);
    createParticle(particles,sf::Vector3f(4.1,0,-0.6),12,vec);
    
    createParticle(particles,sf::Vector3f(5.2,0,1.1),15,vec);
    createParticle(particles,sf::Vector3f(5.2,0,0),9,vec);
    createParticle(particles,sf::Vector3f(5.2,0,-1.1),7,vec);

    createParticle(particles,sf::Vector3f(6.3,0,1.7),10,vec);
    createParticle(particles,sf::Vector3f(6.3,0,0.6),5,vec);
    createParticle(particles,sf::Vector3f(6.3,0,-0.6),16,vec);
    createParticle(particles,sf::Vector3f(6.3,0,-1.7),14,vec);
    
    createParticle(particles,sf::Vector3f(7.4,0,2.2),13,vec);
    createParticle(particles,sf::Vector3f(7.4,0,1.1),6,vec);
    createParticle(particles,sf::Vector3f(7.4,0,0),11,vec);
    createParticle(particles,sf::Vector3f(7.4,0,-1.1),3,vec);
    createParticle(particles,sf::Vector3f(7.4,0,-2.2),8,vec);
    
    createParticle(particles,sf::Vector3f(-6.1,0,0),17,sf::Vector3f(0.1f,0,0));//white ball start position
    
    
    if (!wireframe)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        
        glShadeModel(GL_FLAT);
    }
    // Setup a perspective projection & Camera position
    
    // GL_PROJECTION what we actually see
    glMatrixMode(GL_PROJECTION); // Select the builtin projection matrix
    glLoadIdentity();  // reset the projection matrix by loading the projection identity matrix
    
    GLdouble fovY = 90;
    GLdouble aspect = 1.0f;
    GLdouble zNear = 1.0f;
    GLdouble zFar = 300.0f;
    
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;
    
    fH = tan(fovY / 360 * pi) * zNear;
    fW = fH * aspect;
    
    float angle = 0;
    
    // define a perspective projection
    glFrustum(-fW, fW, -fH, fH, zNear, zFar); // multiply the set matrix; by a perspective matrix
    
    GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat DIFFUSE_COLOR[] = { 1.f, 1.f, 1.f, 1.0f };
    GLfloat SPECULAR_COLOR[] = { 1.f, 1.f, 1.f, 1.0f };
    GLfloat LIGHT_POSITION[] = { 0.f, 1, 0, .0f };
    glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, DIFFUSE_COLOR);
    glLightfv(GL_LIGHT0, GL_SPECULAR, SPECULAR_COLOR);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    
    
    float angleX = 0.f;
    float angleY = 2.7f;
    float rX = 0.f;
    float rY = 0.f;
    
    sf::Vector2i position1,position2;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    // Start game loop
    while (window.isOpen())
    {
        
        float time = TimePerFrame.asSeconds();
        
        // get global mouse position
        sf::Vector2i position = sf::Mouse::getPosition(window);
       
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Escape key : exit
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();
            
            if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::A)) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))) {
                angleX = angleX - 0.1f;
            }
            
            if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::D)) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right))) {
                angleX = angleX + 0.1f;
            }
            
            if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::W)) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))) {
                angleY = angleY + 0.1f;
                            }
            
            if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::S)) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))) {
                angleY = angleY - 0.1f;
               
            }
            
            if (event.type == sf::Event::MouseWheelMoved)
            {
                z = z + (event.mouseWheel.delta*0.1f);
            }
            
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                position1 = sf::Mouse::getPosition(window);
            
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                position2 = sf::Mouse::getPosition(window);
                if (((position1.x - position.x) * 0.001f) >= 0.25 && ((position1.y - position.y) * 0.001f) >= 0.25 ) {
                    
                    particle.setVelocity(sf::Vector3f(0.15,0,-0.15));
                    
                }
                if (((position1.x - position.x) * 0.001f) <= -0.25 && ((position1.y - position.y) * 0.001f) <= -0.25) {
                    
                    particle.setVelocity(sf::Vector3f(-0.15,0,0.15));
                }
                if (((position1.x - position.x) * 0.001f) <= -0.25 && ((position1.y - position.y) * 0.001f) >= 0.25 ) {
                    
                    particle.setVelocity(sf::Vector3f(-0.15,0,-0.15));
                    
                }
                if (((position1.x - position.x) * 0.001f) >= 0.25 && ((position1.y - position.y) * 0.001f) <= -0.25) {
                    
                    particle.setVelocity(sf::Vector3f(0.15,0,0.15));
                }
                
                if (((position1.x - position.x) * 0.001f) <= 0.25 && ((position1.x - position.x) * 0.001f) >= -0.25 && ((position1.y - position.y) * 0.001f) <= 0.25 && ((position1.y - position.y) * 0.001f) >= -0.25){
                    particle.setVelocity(sf::Vector3f((position1.x - position.x) * 0.001f,0,(-(position1.y - position.y) * 0.001f)));
                }
                
//                std::cout << (position1.y - position.y) * 0.001f << std::endl;
                mouseClicked = true;
            }
            
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::R)){
                reset = true;
            }
        }
        if (reset) {
            reset = false;
            particles.clear();
            
            createParticle(particles,sf::Vector3f(3,0,0),2,vec);
            
            createParticle(particles,sf::Vector3f(4.1,0,0.6),4,vec);
            createParticle(particles,sf::Vector3f(4.1,0,-0.6),12,vec);
            
            createParticle(particles,sf::Vector3f(5.2,0,1.1),15,vec);
            createParticle(particles,sf::Vector3f(5.2,0,0),9,vec);
            createParticle(particles,sf::Vector3f(5.2,0,-1.1),7,vec);
            
            createParticle(particles,sf::Vector3f(6.3,0,1.7),10,vec);
            createParticle(particles,sf::Vector3f(6.3,0,0.6),5,vec);
            createParticle(particles,sf::Vector3f(6.3,0,-0.6),16,vec);
            createParticle(particles,sf::Vector3f(6.3,0,-1.7),14,vec);
            
            createParticle(particles,sf::Vector3f(7.4,0,2.2),13,vec);
            createParticle(particles,sf::Vector3f(7.4,0,1.1),6,vec);
            createParticle(particles,sf::Vector3f(7.4,0,0),11,vec);
            createParticle(particles,sf::Vector3f(7.4,0,-1.1),3,vec);
            createParticle(particles,sf::Vector3f(7.4,0,-2.2),8,vec);
            
            createParticle(particles,sf::Vector3f(-6,0,0),17,vec);//white ball start position
        }
        
        
        //Prepare for drawing
        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear z-buffer and set previously selected colour
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); // reset
        
        glEnable(GL_CULL_FACE); // enable back face culling so we don't see the hidden vertices / textures of the cube
        glCullFace(GL_BACK);
        
        GLUquadric *quad;
        quad = gluNewQuadric();
        glTranslatef(0, 0,-15);
        if (texturesOn)
        {
            gluQuadricTexture(quad, 1);
        }
        else
        {
            glColor3f(1, 0, 0);
            if (wireframe)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else
            {
                glEnable(GL_COLOR_MATERIAL);
            }
        }		
        
        glTranslatef(0, -2, z);// position the cube model at z-position -200; ie. away from us
        // rotate x,y,z by a given angle in degrees
        glRotatef(angleX * 20, 0.0f, 1.0f, 0.f); // rotate around the x-axis
        glRotatef(angleY * 20, 1.0f, 0.0f, 0.f); // rotate around the y-axis
        
        glBindTexture(GL_TEXTURE_2D, texture_handle[0]);
        drawTable();
        
        timeSinceLastUpdate += clock.restart();
        
        while (timeSinceLastUpdate > TimePerFrame)
        {
            
            timeSinceLastUpdate -= TimePerFrame;
            
            for(std::list<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
            {
                if (mouseClicked /*&& it->getVelocity() == sf::Vector3f(0,0,0)*/) {
                    mouseClicked = false;
                    particles.begin()->setVelocity(particle.getVelocity());
                }
                it->checkEdges();
                it->update(TimePerFrame);
                if(it->checkCollision(particles)){
                    //it->setVelocity(it->getVelocity());
                    
//                    if (it->getVelocity().x || it->getVelocity().z > 0) {
//                        std::cout << "Yes" << std::endl;
//                        it->setVelocity(sf::Vector3f(it->getVelocity().x,0,-it->getVelocity().z));
//                    }
//                    if (it->getVelocity().x < -0.01f) {
//                        it->setVelocity(sf::Vector3f(-0.01f,0,0));
//                    }
////                    if (it->getVelocity().x < -0.01f) {
////                        it->setVelocity(sf::Vector3f(-0.01f,0,0));
////                    }
//                    if (it->getVelocity().z < -0.01f) {
//                        it->setVelocity(sf::Vector3f(0,0,-0.01f));
//                    }
////                    if (it->getVelocity().z < -0.01f) {
////                        it->setVelocity(sf::Vector3f(-0.01f,0,0));
////                    }

                }
                
                if (it->checkPocket()) {
                    if (it == particles.begin()) {
                        particles.erase(it);
                        createParticle(particles,sf::Vector3f(-6,0,0),17,vec);
                    }
                    else{
                        particles.erase(it);
                    }
                    break;
                }
            }
        }
       
        glRotatef(180, 1.0f, 0.0f, 0.f);
        for(std::list<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
        {
            glBindTexture(GL_TEXTURE_2D,it->getTextureHandle());
            glPushMatrix();
            glTranslatef(it->getLocation().x, 0, it->getLocation().z);
            glRotatef(it->getRotate().x, 0.0f, 0.0f, 1.f); // rotate around the x-axis
            glRotatef(it->getRotate().z, 1.0f, 0.0f, 0.f); // rotate around the y-axis
            gluSphere(quad, .5f, 100, 100);
            glPopMatrix();
           
        }
      
        window.display();
    }
    
    return EXIT_SUCCESS;
}