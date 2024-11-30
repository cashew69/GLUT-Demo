#include <GL/freeglut.h>
#include <cmath>  
GLfloat cloudX = -0.8f; // Initial cloud position (off-screen to the left)
GLfloat cloudY = 0.6f;  // Cloud height (constant in this case)

// Function to draw the cloud (a simple ellipse-like shape)
void drawCloud() {
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);  // White color for the cloud

    // Drawing a simple cloud shape using a circle-like approximation (multiple points)
    for (int i = 0; i < 360; i++) {
        GLfloat angle = i * 3.14159f / 180.0f;
        GLfloat x = 0.1f * cos(angle);  // radius of cloud
        GLfloat y = 0.05f * sin(angle); // height of the cloud
        glVertex2f(x + cloudX, y + cloudY);  // Translate cloud position here
    }
    glEnd();
}

// Function to update the cloud's position (move the cloud to the right)
void updateCloud(int value) {
    cloudX += 0.01f;  // Move the cloud to the right

    // If the cloud goes off the screen, reset its position to the left
    if (cloudX > 1.0f) {
        cloudX = -1.0f;  // Reset cloud to start from the left
    }

    glutPostRedisplay();  // Request a redraw
    glutTimerFunc(16, updateCloud, 0);  // Set the timer to update every 16ms (about 60 FPS)
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    drawCloud();  // Draw the cloud

    glutSwapBuffers();  
}

// Initialize OpenGL settings
void initialize(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600); 
    glutCreateWindow("Moving Cloud");

    initialize();  

    glutDisplayFunc(display);  // Set the display function
    glutTimerFunc(25, updateCloud, 0);  // Start the cloud movement with a timer

    glutMainLoop();  
    return 0;
}
