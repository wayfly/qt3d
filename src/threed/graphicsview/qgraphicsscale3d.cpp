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

#include "qgraphicsscale3d.h"

QT_BEGIN_NAMESPACE

/*!
    \class QGraphicsScale3D
    \brief The QGraphicsScale3D class supports scaling of items in 3D.
    \since 4.8
    \ingroup qt3d
    \ingroup qt3d::graphicsview

    \sa QGraphicsRotation3D, QGraphicsTranslation3D
*/

/*!
    \qmltype Scale3D
    \instantiates QGraphicsScale3D
    \brief The Scale3D item supports scaling of items in 3D.
    \since 4.8
    \ingroup qt3d::qml3d

    3D items in QML can have a simple scale applied directly as follows:

    \code
    Item3D {
        mesh: Mesh { source: "chair.3ds" }
        scale: 0.5
    }
    \endcode

    An alternative is to use Scale3D to apply a transform directly
    to an item as part of a sequence of transformations:

    \code
    Item3D {
        mesh: Mesh { source: "chair.3ds" }
        transform: [
            Translation3D { translate: Qt.vector3d(5, 0, 0) },
            Scale3D { scale: 0.5 }
        ]
    }
    \endcode

    This allows the application writer to control exactly when the
    scale occurs relative to other transformations.  In the example
    above, the item is first translated by 5 units along the x-axis,
    and then the co-ordinates are scaled by half.  This is distinct
    from the following example which scales the object to half its
    original size and then translates it by 5 units along the x-axis:

    \code
    Item3D {
        mesh: Mesh { source: "chair.3ds" }
        transform: [
            Scale3D { scale: 0.5 },
            Translation3D { translate: Qt.vector3d(5, 0, 0) }
        ]
    }
    \endcode

    The scale property on the item itself is applied before
    any of the transforms.  So the previous example is equivalent to:

    \code
    Item3D {
        mesh: Mesh { source: "chair.3ds" }
        scale: 0.5
        transform: [
            Translation3D { translate: Qt.vector3d(5, 0, 0) }
        ]
    }
    \endcode

    Scale values can also affect the x, y, and z axes by different amounts
    by using a \c{vector3D} value:

    \code
    Item3D {
        mesh: Mesh { source: "chair.3ds" }
        transform: [
            Scale3D { scale: Qt.vector3d(0.5, 0.2, 1.0) },
            Translation3D { translate: Qt.vector3d(5, 0, 0) }
        ]
    }
    \endcode

    \sa Rotation3D, Translation3D
*/

class QGraphicsScale3DPrivate
{
public:
    QGraphicsScale3DPrivate()
        : scale(1, 1, 1)
        , isIdentityScale(true)
        , isIdentityOrigin(true)
    {}

    QVector3D origin;
    QVector3D scale;
    bool isIdentityScale;
    bool isIdentityOrigin;
};

/*!
    Construct a 3D scale transform and attach it to \a parent.
*/
QGraphicsScale3D::QGraphicsScale3D(QObject *parent)
    : QQuickQGraphicsTransform3D(parent), d_ptr(new QGraphicsScale3DPrivate)
{
}

/*!
    Destroy this 3D scale transform.
*/
QGraphicsScale3D::~QGraphicsScale3D()
{
}

/*!
    \property QGraphicsScale3D::origin
    \brief the origin about which to scale.

    The default value for this property is (0, 0, 0).
*/

/*!
    \qmlproperty vector3D Scale3D::origin

    The origin about which to scale.  The default value for this
    property is (0, 0, 0).
*/

QVector3D QGraphicsScale3D::origin() const
{
    Q_D(const QGraphicsScale3D);
    return d->origin;
}

void QGraphicsScale3D::setOrigin(const QVector3D &value)
{
    Q_D(QGraphicsScale3D);

    // Optimise for the common case of setting the origin to 0, 0, 0
    // Also minimise the number of floating point compares required
    bool changed = false;
    QVector3D v = value;

    // Are we about to set to 0, 0, 0 ...?
    // Normalise inbound value & record in bool to save on compares
    bool isSetToZeroOrigin = false;
    if (qFuzzyIsNull(v.x()) && qFuzzyIsNull(v.y()) && qFuzzyIsNull(v.z()))
    {
        v = QVector3D(0, 0, 0);
        isSetToZeroOrigin = true;
    }
    if (!isSetToZeroOrigin)
    {
        if (d->origin != v)
        {
            d->origin = v;
            d->isIdentityOrigin = false;
            changed = true;
        }
    }
    else
    {
        if (!d->isIdentityOrigin)
        {
            d->origin = v;
            d->isIdentityOrigin = true;
            changed = true;
        }
    }
    if (changed)
    {
        emit transformChanged();
        emit originChanged();
    }
}

/*!
    \property QGraphicsScale3D::scale
    \brief the amount with which to scale each component.

    The default value for this property is QVector3D(1, 1, 1).
*/

/*!
    \qmlproperty vector3D Scale3D::scale

    The amount with which to scale each component.  The default value for
    this property is (1, 1, 1).

    This property can be specified as either a vector3D or a single
    floating-point value.  A single floating-point value will set
    the x, y, and z scale components to the same value.  In other words,
    the following two transformations are equivalent:

    \code
    Scale3D { scale: 2 }
    Scale3D { scale: Qt.vector3d(2, 2, 2) }
    \endcode
*/

QVector3D QGraphicsScale3D::scale() const
{
    Q_D(const QGraphicsScale3D);
    return d->scale;
}

void QGraphicsScale3D::setScale(const QVector3D &value)
{
    Q_D(QGraphicsScale3D);

    // Optimise for the common case of setting the scale to 1, 1, 1
    // Also minimise the number of floating point compares required
    bool changed = false;
    QVector3D v = value;

    // Are we about to set to 1, 1, 1 ...?
    // Normalise inbound value & record in bool to save on compares
    bool isSetToIdentity = false;
    if (qFuzzyIsNull(v.x() - 1.0f) && qFuzzyIsNull(v.y() - 1.0f) && qFuzzyIsNull(v.z() - 1.0f))
    {
        v = QVector3D(1, 1, 1);
        isSetToIdentity = true;
    }
    if (!isSetToIdentity)
    {
        if (d->scale != v)
        {
            d->scale = v;
            d->isIdentityScale = false;
            changed = true;
        }
    }
    else
    {
        if (!d->isIdentityScale)
        {
            d->scale = v;
            d->isIdentityScale = true;
            changed = true;
        }
    }
    if (changed)
    {
        emit transformChanged();
        emit scaleChanged();
    }
}

/*!
    \internal
*/
void QGraphicsScale3D::applyTo(QMatrix4x4 *matrix) const
{
    Q_D(const QGraphicsScale3D);
    if (!d->isIdentityScale)
    {
        if (d->isIdentityOrigin)
        {
            matrix->scale(d->scale);
        }
        else
        {
            matrix->translate(d->origin);
            matrix->scale(d->scale);
            matrix->translate(-d->origin);
        }
    }
}

/*!
    \internal
*/
QQuickQGraphicsTransform3D *QGraphicsScale3D::clone(QObject *parent) const
{
    Q_D(const QGraphicsScale3D);
    QGraphicsScale3D *copy = new QGraphicsScale3D(parent);
    copy->setOrigin(d->origin);
    copy->setScale(d->scale);
    return copy;
}

/*!
    \fn void QGraphicsScale3D::originChanged()

    Signal that is emitted when origin() changes.
*/

/*!
    \fn void QGraphicsScale3D::scaleChanged()

    Signal that is emitted when scale() changes.
*/

QT_END_NAMESPACE
