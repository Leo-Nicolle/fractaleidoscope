#include <GL/glew.h>
#include <GL/glut.h>
#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace std;
using namespace cv;

Mat src;
GLuint texture;

// Function turn a cv::Mat into a texture, and return the texture ID as a GLuint for use
GLuint matToTexture(cv::Mat &mat, GLenum minFilter, GLenum magFilter, GLenum wrapFilter)
{
    // Generate a number for our textureID's unique handle
    GLuint textureID;
    glGenTextures(1, &textureID);
 
    // Bind to our texture handle
    glBindTexture(GL_TEXTURE_2D, textureID);
 
    // Catch silly-mistake texture interpolation method for magnification
    if (magFilter == GL_LINEAR_MIPMAP_LINEAR  ||
        magFilter == GL_LINEAR_MIPMAP_NEAREST ||
        magFilter == GL_NEAREST_MIPMAP_LINEAR ||
        magFilter == GL_NEAREST_MIPMAP_NEAREST)
    {
        cout << "You can't use MIPMAPs for magnification - setting filter to GL_LINEAR" << endl;
        magFilter = GL_LINEAR;
    }
 
    // Set texture interpolation methods for minification and magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
 
    // Set texture clamping method
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapFilter);
 
    // Set incoming texture format to:
    // GL_BGR       for CV_CAP_OPENNI_BGR_IMAGE,
    // GL_LUMINANCE for CV_CAP_OPENNI_DISPARITY_MAP,
    // Work out other mappings as required ( there's a list in comments in main() )
    GLenum inputColourFormat = GL_BGR;
    if (mat.channels() == 1)
    {
        inputColourFormat = GL_LUMINANCE;
    }
 
    // Create the texture
    glTexImage2D(GL_TEXTURE_2D,     // Type of texture
                 0,                 // Pyramid level (for mip-mapping) - 0 is the top level
                 GL_RGB,            // Internal colour format to convert to
                 mat.cols,          // Image width  i.e. 640 for Kinect in standard mode
                 mat.rows,          // Image height i.e. 480 for Kinect in standard mode
                 0,                 // Border width in pixels (can either be 1 or 0)
                 inputColourFormat, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                 GL_UNSIGNED_BYTE,  // Image data type
                 mat.ptr());        // The actual image data itself
 
    // If we're using mipmaps then generate them. Note: This requires OpenGL 3.0 or higher
    if (minFilter == GL_LINEAR_MIPMAP_LINEAR  ||
        minFilter == GL_LINEAR_MIPMAP_NEAREST ||
        minFilter == GL_NEAREST_MIPMAP_LINEAR ||
        minFilter == GL_NEAREST_MIPMAP_NEAREST)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
 
    return textureID;
}

void setTexture() {
    cv::VideoCapture capture( CV_CAP_OPENNI );
     
    // Check that we have actually opened a connection to the sensor
    if( !capture.isOpened() )
    {
        cout << "Cannot open capture object." << endl;
        exit(-1);
    }
 
    // Create our cv::Mat object
    cv::Mat camFrame;
 
    // Grab the device
    capture.grab();
 
    // Retrieve desired sensor data (in this case the standard camera image)
    capture.retrieve(camFrame, CV_CAP_OPENNI_BGR_IMAGE);
 
    // Convert to texture
    GLuint tex = matToTexture(camFrame, GL_NEAREST, GL_NEAREST, GL_CLAMP);
 
    // Bind texture
    glBindTexture(GL_TEXTURE_2D, tex);
 
    // Do whatever you want with the texture here...
 
    // Free the texture memory
    glDeleteTextures(1, &tex);
 
    // *** End of loop ***
 
    // Release the device
    capture.release();
}

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glEnable(GL_TEXTURE_2D);
    texture = matToTexture(src, GL_NEAREST, GL_NEAREST, GL_CLAMP);
    glBindTexture(GL_TEXTURE_2D, texture); 
    glBegin(GL_POLYGON);
        glTexCoord2f(1.0,1.0);
        glVertex3f(-1.0, -1.0, 0.0);
        
        glTexCoord2f(0.0,1.0);
        glVertex3f(0.0, -1.0, 0.0);
        
        glTexCoord2f(0.0,0.0);
        glVertex3f(0.0, 1.0, 0.0);
        
        glTexCoord2f(1.0,0.0);       
        glVertex3f(-1.0, 1.0, 0.0);
    glEnd();

     glBegin(GL_POLYGON);
        glTexCoord2f(0.0,1.0);
        glVertex3f(0.0, -1.0, 0.0);
        
        glTexCoord2f(1.0,1.0);
        glVertex3f(1.0, -1.0, 0.0);
        
        glTexCoord2f(1.0,0.0);
        glVertex3f(1.0, 1.0, 0.0);
        
        glTexCoord2f(0.0,0.0);       
        glVertex3f(0.0, 1.0, 0.0);
    glEnd();


    glFlush();

    glDeleteTextures(1, &texture);

    glDisable(GL_TEXTURE_2D);
}

int main(int argc, char** argv)
{
    src = imread("./img/2.png");


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(560, 840);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world :D");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}