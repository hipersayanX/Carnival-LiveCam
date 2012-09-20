#ifndef CUBEGL_H
#define CUBEGL_H

#include <QtOpenGL>

class CubeGL: public QGLWidget
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage RESET resetImage)
    Q_PROPERTY(float xrot READ xrot WRITE setXrot RESET resetXrot)
    Q_PROPERTY(float yrot READ yrot WRITE setYrot RESET resetYrot)

    public:
        CubeGL();
        QImage image();
        float xrot();
        float yrot();

    private:
        QImage m_image;
        bool m_mousePressed;
        QPoint m_mousePos0;
        GLfloat m_xrot;
        GLfloat m_yrot;

        void initializeGL();
        void resizeGL(qint32 width, qint32 height);
        void paintGL();

    signals:
        void xrotChanged(float xrot);
        void yrotChanged(float yrot);

    public slots:
        void setImage(const QImage &image);
        void setXrot(float xrot);
        void setYrot(float yrot);
        void resetImage();
        void resetXrot();
        void resetYrot();

        void mouseMove(QMouseEvent *event);
        void mousePress(QMouseEvent *event);
        void mouseRelease(QMouseEvent *event);
};

#endif // CUBEGL_H
