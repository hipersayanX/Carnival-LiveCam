#include <GL/glu.h>

#include "include/ogl.h"

OGL::OGL(): QGLWidget()
{
    this->m_mousePressed = false;
    this->m_xrot = 30.0f;
    this->m_yrot = 60.0f;
}

void OGL::initializeGL()
{
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void OGL::resizeGL(qint32 width, qint32 height)
{
    if (height == 0)
        height = 1;

    GLfloat ratio = (GLfloat) width / (GLfloat) height;
    glViewport(0, 0, (GLint) width, (GLint) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);

    glRotatef(this->m_xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(this->m_yrot, 0.0f, 1.0f, 0.0f);
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f);

    GLuint texture = this->bindTexture(this->m_image, GL_TEXTURE_2D, GL_RGBA);

    glBegin(GL_QUADS);
        // Front
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

        // Back
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);

        // Top
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f,  1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f,  1.0f);

        // Bottom
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

        // Right
        glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,  1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,  1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f,  1.0f);

        // Left
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();

    this->swapBuffers();
    this->deleteTexture(texture);
}

void OGL::mouseMove(QMouseEvent *event)
{
    if (this->m_mousePressed)
    {
        QPoint diffPos = event->pos() - this->m_mousePos0;

        this->m_xrot += diffPos.y() / 10;
        this->m_yrot += diffPos.x() / 10;
    }
}

void OGL::mousePress(QMouseEvent *event)
{
    this->m_mousePos0 = event->pos();
    this->m_mousePressed = true;
}

void OGL::mouseRelease(QMouseEvent *event)
{
    Q_UNUSED(event);

    this->m_mousePressed = false;
}

QImage OGL::image()
{
    return this->m_image;
}

float OGL::xrot()
{
    return this->m_xrot;
}

float OGL::yrot()
{
    return this->m_yrot;
}

void OGL::setImage(const QImage &image)
{
    this->m_image = image;
}

void OGL::setXrot(float xrot)
{
    this->m_xrot = xrot;
    emit(xrotChanged(xrot));
}

void OGL::setYrot(float yrot)
{
    this->m_yrot = yrot;
    emit(yrotChanged(yrot));
}

void OGL::resetImage()
{
    this->m_image = QImage();
}

void OGL::resetXrot()
{
    this->setXrot(30.0f);
}

void OGL::resetYrot()
{
    this->setYrot(60.0f);
}
