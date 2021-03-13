/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "cube_window.h"

#include <QGuiApplication>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QtMath>
#include <QColorDialog>

#include <QApplication>

#include <QStyleHints>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include <QLayout>
#include <QSlider>
#include <QHBoxLayout>
#include <QLabel>
#include <QSurfaceFormat>

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);
    QColorDialog* dialog = new QColorDialog();
    dialog->setOption(QColorDialog::NoButtons);
    CubeWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();
    window.setAnimating(true);
    QObject::connect(dialog, &QColorDialog::currentColorChanged, &window, &CubeWindow::slot_for_color);

    QWidget *widget = new QWidget;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(dialog);

    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setMaximum(360);
    QLabel *label = new QLabel("0");
    layout->addWidget(label);
    layout->addWidget(slider);

    QSlider *slider1 = new QSlider(Qt::Horizontal);
    slider1->setMaximum(180);
    QLabel *label1 = new QLabel("0");
    layout->addWidget(label1);
    layout->addWidget(slider1);

    QSlider *slider2 = new QSlider(Qt::Horizontal);
    slider2->setMaximum(20);
    slider2->setMinimum(1);
    QLabel *label2 = new QLabel("1");
    layout->addWidget(label2);
    layout->addWidget(slider2);

    QSlider *slider3 = new QSlider(Qt::Horizontal);
    slider3->setMaximum(100);
    //slider3->setMinimum(0);
    QLabel *label3 = new QLabel("0");
    layout->addWidget(label3);
    layout->addWidget(slider3);


    QObject::connect(slider, &QSlider::valueChanged, label,
      static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    QObject::connect(slider, &QSlider::valueChanged, &window,
      &CubeWindow::slot_for_phi);

    QObject::connect(slider1, &QSlider::valueChanged, label1,
      static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    QObject::connect(slider1, &QSlider::valueChanged, &window,
      &CubeWindow::slot_for_theta);

    QObject::connect(slider2, &QSlider::valueChanged, label2,
      static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    QObject::connect(slider2, &QSlider::valueChanged, &window,
      &CubeWindow::slot_for_N);

    QObject::connect(slider3, &QSlider::valueChanged, label3,
      static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    QObject::connect(slider3, &QSlider::valueChanged, &window,
      &CubeWindow::slot_for_shaping_presentage);

    widget->setLayout(layout);
    widget->show();

    return app.exec();
}
