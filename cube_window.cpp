#include "cube_window.h"
#include <QRandomGenerator>
#include <QScreen>
#include <cmath>
#define SQR3 1.73205080

void CubeWindow::slot_for_color(QColor color_ = {1, 1, 1, 1}){
    color = color_;
}

void CubeWindow::slot_for_shaping_presentage(int shapingPercentage_){
  shapingPercentage = static_cast<float>(shapingPercentage_)/100.0f;

}

void CubeWindow::slot_for_N(int N_){
    N = N_;
    make_edge();
}

void CubeWindow::calculating_axis(){
    axis_of_rotate[0] = sin(theta)*cos(phi);
    axis_of_rotate[1] = sin(theta)*sin(phi);
    axis_of_rotate[2] = cos(theta);
}

void CubeWindow::slot_for_phi(int phi_){
    phi=static_cast<float>(phi_)/180*3.14;
    calculating_axis();
}

void CubeWindow::slot_for_theta(int theta_){
    theta = static_cast<float>(theta_)/180*3.14;
    calculating_axis();
}

void CubeWindow::initialize()
{
    N=1;
    a=2.0f;
    radius = a*SQR3;
    make_edge();
    axis_of_rotate[0]=0;
    axis_of_rotate[1]=0;
    axis_of_rotate[2]=1;

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":vertex.vsh");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":fragment.fsh");
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colUniform = m_program->uniformLocation("col");
    Q_ASSERT(m_colUniform != -1);
    m_matrixUniform = m_program->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
    m_matrix_edge = m_program->uniformLocation("matrix_edge");
    Q_ASSERT(m_matrix_edge != -1);
    m_shapingPercentage = m_program->uniformLocation("shapingPercentage");
    Q_ASSERT(m_shapingPercentage != -1);
    m_radius = m_program->uniformLocation("radius");
    Q_ASSERT(m_radius != -1);

    QSurfaceFormat surf_form;
    surf_form.setSamples(4);
    color = {255, 255, 255};
    color_lines = {0, 0, 0};
}

void CubeWindow:: make_edge (){
    vertices.clear();
    GLfloat step = 2*a/N;
    GLfloat x = -a;
    GLfloat y = a;
    GLfloat z = a;
    for(int k=0; k<N; k++)
    {
        for(int i=0; i<=N; i++){
            vertices.push_back(x+step*i); //top x
            vertices.push_back(y); //top y
            vertices.push_back(z); // top z
            vertices.push_back(x+step*i); // bottom x
            vertices.push_back(y-step ); // bottom y
            vertices.push_back(z); // bottom z
        }
        y-=step;
    }
}

void CubeWindow::draw_edge (){

    for (int i = 0; i <6; i++){
        QMatrix4x4 matrix_for_edge;
        switch (i)
            {
            case 0:
                matrix_for_edge.rotate(0, 0, 1, 0);
                break;
            case 1:
                matrix_for_edge.rotate(90, 0, 1, 0);
                break;
            case 2:
                matrix_for_edge.rotate(180, 0, 1, 0);
                break;
            case 3:
                matrix_for_edge.rotate(270, 0, 1, 0);
                break;
            case 4:
                matrix_for_edge.rotate(90, 1, 0, 0);
                break;
            case 5:
                matrix_for_edge.rotate(270, 1, 0, 0);
                break;
            default:
                break;
            }
        m_program->setUniformValue(m_matrix_edge, matrix_for_edge);
        for(int j = 0; j<N; j++){
            m_program->setUniformValue(m_colUniform, color);
            glDrawArrays(GL_TRIANGLE_STRIP, (N+1)*2*j, (N+1)*2);
            color_lines = {0, 0, 0};
            m_program->setUniformValue(m_colUniform, color_lines);
            glPolygonOffset(2.0f, 2.0f);
            //glDisable(GL_POLYGON_OFFSET_FILL);
            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawArrays(GL_LINE_STRIP, (N+1)*2*j, (N+1)*2);
        }
    }
}

void CubeWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -10);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), axis_of_rotate[0], axis_of_rotate[1], axis_of_rotate[2]);

    m_program->setUniformValue(m_matrixUniform, matrix);
    m_program->setUniformValue(m_shapingPercentage, shapingPercentage);
    m_program->setUniformValue(m_radius, radius);

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());
    glEnableVertexAttribArray(m_posAttr);
    draw_edge();
    glDisableVertexAttribArray(m_colUniform);

    m_program->release();
    ++m_frame;
}
