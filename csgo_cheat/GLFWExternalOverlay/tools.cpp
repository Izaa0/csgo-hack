#include "datatypes.h"
#include "GLFW/glfw3.h"

void DrawBox(Vec2& feetCoords, Vec2& headCoords)
{
  
    float height = headCoords.Y - feetCoords.Y;
    float width = height / 3.8f;

    glLineWidth(3.0f);

    glBegin(GL_LINES);
    glVertex2f(feetCoords.X - (width / 2), feetCoords.Y);
    glVertex2f(feetCoords.X - (width / 2), headCoords.Y);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(feetCoords.X - (width / 2), headCoords.Y);
    glVertex2f(feetCoords.X + (width / 2), headCoords.Y);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(feetCoords.X + (width / 2), headCoords.Y);
    glVertex2f(feetCoords.X + (width / 2), feetCoords.Y);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(feetCoords.X + (width / 2), feetCoords.Y);
    glVertex2f(feetCoords.X - (width / 2), feetCoords.Y);
    glEnd();
}

void DrawSnapLines(Vec2& feetCoords)
{
    glBegin(GL_LINES);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(feetCoords.X, feetCoords.Y);
    glEnd();
}

void DrawHealthBar(Vec2& feetCoords, Vec2& headCoords, int health)
{
    float height = headCoords.Y - feetCoords.Y;
    float width = height / 3.8f;

    if (health >= 70)
    {
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(feetCoords.X - (width / 1.5), feetCoords.Y);
        glVertex2f(feetCoords.X - (width / 1.5), headCoords.Y);
        glEnd();
    }
    else if (health <= 70 && health >= 40)
    {
        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(feetCoords.X - (width / 1.5), feetCoords.Y);
        glVertex2f(feetCoords.X - (width / 1.5), headCoords.Y - (width / 0.85));
        glEnd();
    }
    else if (health <= 40 && health >= 0)
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(feetCoords.X - (width / 1.5), feetCoords.Y);
        glVertex2f(feetCoords.X - (width / 1.5), headCoords.Y - (width / 0.40));
        glEnd();
    }
}

void DrawArmorBar(Vec2& feetCoords, Vec2& headCoords, int armor)
{
    float height = headCoords.Y - feetCoords.Y;
    float width = height / 3.8f;

    glColor3f(0.0f, 0.0f, 1.0f);

    
    if (armor >= 70)
    {
        glBegin(GL_LINES);
        glVertex2f(feetCoords.X - (width / 1.0), feetCoords.Y);
        glVertex2f(feetCoords.X - (width / 1.0), headCoords.Y);
        glEnd();
    }
    else if (armor <= 70 && armor >= 40)
    {
        glBegin(GL_LINES);
        glVertex2f(feetCoords.X - (width / 1.0), feetCoords.Y);
        glVertex2f(feetCoords.X - (width / 1.0), headCoords.Y - (width / 0.85));
        glEnd();
    }
    else if (armor <= 40 && armor >= 0)
    {
        
        glBegin(GL_LINES);
        glVertex2f(feetCoords.X - (width / 1.0), feetCoords.Y);
        glVertex2f(feetCoords.X - (width / 1.0), headCoords.Y - (width / 0.40));
        glEnd();
    }
    else if (armor == 0)
    {
        return;
    }
    
   
}