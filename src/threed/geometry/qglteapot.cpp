/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qglteapot.h"
#include "qglteapot_data_p.h"

QT_BEGIN_NAMESPACE

/*!
    \class QGLTeapot
    \brief The QGLTeapot class represents a 3D teapot object.
    \since 4.8
    \ingroup qt3d
    \ingroup qt3d::geometry

    The classic 3D "Utah Teapot" was originally drawn by Martin Newell
    in 1975.  The vertex data was made publicly available by him and
    it has been a standard 3D test object ever since.

    For more information on the history of the "Utah Teapot", see
    Wikipedia, http://en.wikipedia.org/wiki/Utah_teapot.

    The following example code uses QGLTeapot to draw a teapot of size
    0.5 at the origin:

    \code
    QGLBuilder builder;
    builder << QGLTeapot();
    teapot = builder.finalizedSceneNode();

    painter.modelViewMatrix().scale(0.5f);
    teapot->draw(painter);
    \endcode

    The QGLTeapot object contains a lot of vertex data once it has
    been subdivided into triangles.  It is recommended that instances
    of this class be created at startup, added to a QGLBuilder,
    and then the finalized scene node can be reused over and over.

    \sa QGLBezierPatches
*/

/*!
    Constructs a new 3D teapot geometry object.
*/
QGLTeapot::QGLTeapot()
{
    QVector3DArray positions;
    for (int pindex = 0; pindex < teapotPatchCount * 16; ++pindex) {
        int vindex = teapotPatchData[pindex];
        positions.append(teapotBezierVertexData[vindex * 3],
                         teapotBezierVertexData[vindex * 3 + 1],
                         teapotBezierVertexData[vindex * 3 + 2]);
    }
    setPositions(positions);
    setSubdivisionDepth(teapotDepth);
}

/*!
    Destroys this teapot geometry object.
*/
QGLTeapot::~QGLTeapot()
{
}

QT_END_NAMESPACE
