#ifndef CUBEWINDOW_H
#define CUBEWINDOW_H

#include "openglwindow.h"
#include <QOpenGLShaderProgram>
//#include <QOpenGLFunctions_3_0>

class CubeWindow : public OpenGLWindow//, public OpenGLFunctions_3_0
{
public:
    using OpenGLWindow::OpenGLWindow;

    void initialize() override;
    void render() override;
public slots:
    void slot_for_color(QColor color);
    void slot_for_phi(int phi_);
    void slot_for_theta(int theta_);
    void slot_for_N(int N);
    void slot_for_sphere_degree(int deg_);
    void slot_for_shaping_presentage(int shapingPresentage_);

private:
    GLint m_posAttr = 0;
    GLint m_colUniform = 0;
    GLint m_matrixUniform = 0;
    GLint m_matrix_edge = 0;
    GLint m_shapingPercentage = 0;
    GLint m_radius = 0;
    QOpenGLShaderProgram *m_program = nullptr;
    int m_frame = 0;
    QColor color;
    QColor color_lines;
    float axis_of_rotate[3];
    float theta;
    float phi;
    float radius;
    float shapingPercentage;
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> vertices1;
    int N;
    GLfloat a;
    void calculating_axis();
    void make_edge();
    void make_up_edge();
    void draw_edge();
};

#endif // CUBEWINDOW_H
