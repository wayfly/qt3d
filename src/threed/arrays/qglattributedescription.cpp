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

#include "qglattributedescription.h"
#include "qopenglfunctions.h"

QT_BEGIN_NAMESPACE

/*!
    \class QGLAttributeDescription
    \brief The QGLAttributeDescription class encapsulates information about an OpenGL attribute value's layout and type.
    \since 4.8
    \ingroup qt3d
    \ingroup qt3d::arrays

    OpenGL has many functions that take a pointer to vertex attribute
    values: \c{glVertexPointer()}, \c{glNormalPointer()},
    \c{glVertexAttribPointer()}, etc.  These functions typically
    take four arguments: tuple size (1, 2, 3, or 4), component type
    (e.g. GL_FLOAT), stride, and data pointer (\c{glNormalPointer()}
    does not use tuple size, assuming that it is 3).  When used with
    vertex buffers, the data pointer may be an offset into the vertex
    buffer instead.

    QGLAttributeDescription encapsulates the vertex attribute() kind
    (QGL::Position, QGL::Normal, etc) with the type(), tupleSize(),
    and stride() information of an attribute.  The companion
    QGLAttributeValue class adds the data pointer.

    \sa QGLAttributeValue
*/

/*!
    \fn QGLAttributeDescription::QGLAttributeDescription()

    Constructs a null attribute description with default parameters of
    tupleSize() and stride() set to zero, type() set to GL_FLOAT,
    and attribute() set to QGL::Position.

    \sa isNull()
*/

/*!
    \fn QGLAttributeDescription::QGLAttributeDescription(QGL::VertexAttribute attribute, int tupleSize, GLenum type, int stride)

    Constructs an attribute description with the fields \a attribute,
    \a tupleSize, \a type, and \a stride.
*/

/*!
    \fn bool QGLAttributeDescription::isNull() const

    Returns true if tupleSize() is zero, which indicates an unset
    attribute description; false otherwise.
*/

/*!
    \fn QGL::VertexAttribute QGLAttributeDescription::attribute() const

    Returns the vertex attribute that this description applies to.
    The default value is QGL::Position.

    \sa setAttribute(), type()
*/

/*!
    \fn void QGLAttributeDescription::setAttribute(QGL::VertexAttribute attribute)

    Sets the vertex \a attribute that this description applies to.

    \sa attribute()
*/

/*!
    \fn GLenum QGLAttributeDescription::type() const

    Returns the component type for this attribute description.  The default
    value is GL_FLOAT.

    \sa setType(), sizeOfType(), attribute()
*/

/*!
    \fn void QGLAttributeDescription::setType(GLenum type)

    Sets the component \a type for this attribute description.

    \sa type(), sizeOfType()
*/

/*!
    Returns the size in bytes of type().

    \sa type(), tupleSize()
*/
int QGLAttributeDescription::sizeOfType() const
{
    switch (m_type) {
    case GL_BYTE:           return int(sizeof(GLbyte));
    case GL_UNSIGNED_BYTE:  return int(sizeof(GLubyte));
    case GL_SHORT:          return int(sizeof(GLshort));
    case GL_UNSIGNED_SHORT: return int(sizeof(GLushort));
    case GL_INT:            return int(sizeof(GLint));
    case GL_UNSIGNED_INT:   return int(sizeof(GLuint));
    case GL_FLOAT:          return int(sizeof(GLfloat));
#if defined(GL_DOUBLE) && !defined(QT_OPENGL_ES)
    case GL_DOUBLE:         return int(sizeof(GLdouble));
#endif
    default:                return 0;
    }
}

/*!
    \fn int QGLAttributeDescription::tupleSize() const

    Returns the tuple size of this attribute in components.  For example,
    a return value of 3 indicates a vector of 3-dimensional values.
    If tupleSize() is zero, then this attribute description is null.

    \sa setTupleSize(), isNull(), sizeOfType()
*/

/*!
    \fn void QGLAttributeDescription::setTupleSize(int tupleSize)

    Sets the tuple size of this attribute in components to \a tupleSize.

    \sa tupleSize()
*/

/*!
    \fn int QGLAttributeDescription::stride() const

    Returns the stride in bytes from one vertex element to the
    next for this attribute description.  The default value of 0 indicates
    that the elements are tightly packed within the data array.

    \sa setStride()
*/

/*!
    \fn void QGLAttributeDescription::setStride(int stride)

    Sets the \a stride in bytes from one vertex element to the next
    for this attribute description.

    \sa stride()
*/

QT_END_NAMESPACE
