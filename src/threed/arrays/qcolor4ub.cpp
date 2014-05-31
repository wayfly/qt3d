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

#include "qcolor4ub.h"
#include <QtCore/qdebug.h>

QT_BEGIN_NAMESPACE

/*!
    \class QColor4ub
    \brief The QColor4ub class represents a color by four unsigned byte components.
    \since 4.8
    \ingroup qt3d
    \ingroup qt3d::arrays

    OpenGL applications commonly use four unsigned byte values to compactly
    represent a color value.  QColor4ub provides a convenience
    class for manipulating such compact color values.

    An alternative is to represent a color value as four floating-point
    values between 0.0 and 1.0.  The QVector4D class can be used for
    that purpose if required.
*/

/*!
    \fn QColor4ub::QColor4ub()

    Constructs a four-byte default color value of (0, 0, 0, 255).
*/

/*!
    \fn QColor4ub::QColor4ub(int red, int green, int blue, int alpha)

    Constructs a four-byte color value with the components \a red,
    \a green, \a blue, and \a alpha.
*/

/*!
    \fn QColor4ub::QColor4ub(const QColor& color)

    Constructs a four-byte color value from \a color.
*/

/*!
    \fn QColor4ub::QColor4ub(Qt::GlobalColor color)

    Constructs a four-byte color value from \a color.
*/

/*!
    \fn QColor4ub::QColor4ub(QRgb rgba)

    Constructs a four-byte color value from the red, green, blue, and
    alpha components of \a rgba.
*/

/*!
    \fn QColor4ub& QColor4ub::operator=(const QColor& color)

    Copies the red, green, blue, and alpha components of \a color
    into this object.
*/

/*!
    \fn QColor4ub& QColor4ub::operator=(Qt::GlobalColor color)

    Copies the red, green, blue, and alpha components of the
    specified global \a color name into this object.
*/

/*!
    \fn int QColor4ub::red() const

    Returns the red component of this color, between 0 and 255.

    \sa green(), blue(), alpha(), setRed(), redF()
*/

/*!
    \fn int QColor4ub::green() const

    Returns the green component of this color, between 0 and 255.

    \sa red(), blue(), alpha(), setGreen(), greenF()
*/

/*!
    \fn int QColor4ub::blue() const

    Returns the blue component of this color, between 0 and 255.

    \sa red(), green(), alpha(), setBlue(), blueF()
*/

/*!
    \fn int QColor4ub::alpha() const

    Returns the alpha component of this color, between 0 and 255.

    \sa red(), green(), blue(), setAlpha(), alphaF()
*/

/*!
    \fn void QColor4ub::setRed(int value)

    Sets the red component of this color to \a value, between 0 and 255.

    \sa setGreen(), setBlue(), setAlpha(), red(), setRedF()
*/

/*!
    \fn void QColor4ub::setGreen(int value)

    Sets the green component of this color to \a value, between 0 and 255.

    \sa setRed(), setBlue(), setAlpha(), green(), setGreenF()
*/

/*!
    \fn void QColor4ub::setBlue(int value)

    Sets the blue component of this color to \a value, between 0 and 255.

    \sa setRed(), setGreen(), setAlpha(), blue(), setBlueF()
*/

/*!
    \fn void QColor4ub::setAlpha(int value)

    Sets the alpha component of this color to \a value, between 0 and 255.

    \sa setRed(), setGreen(), setBlue(), alpha(), setAlphaF()
*/

/*!
    \fn float QColor4ub::redF() const { return m_red / 255.0f; }

    Returns the red component of this color as a floating-point
    value between 0 and 1.

    \sa greenF(), blueF(), alphaF(), setRedF(), red()
*/

/*!
    \fn float QColor4ub::greenF() const { return m_green / 255.0f; }

    Returns the green component of this color as a floating-point
    value between 0 and 1.

    \sa redF(), blueF(), alphaF(), setGreenF(), green()
*/

/*!
    \fn float QColor4ub::blueF() const { return m_blue / 255.0f; }

    Returns the blue component of this color as a floating-point
    value between 0 and 1.

    \sa redF(), greenF(), alphaF(), setBlueF(), blue()
*/

/*!
    \fn float QColor4ub::alphaF() const { return m_alpha / 255.0f; }

    Returns the alpha component of this color as a floating-point
    value between 0 and 1.

    \sa redF(), greenF(), blueF(), setAlphaF(), alpha()
*/

/*!
    \fn void QColor4ub::setRedF(float value)

    Sets the red component of this color to a floating-point \a value,
    between 0 and 1.

    \sa setGreenF(), setBlueF(), setAlphaF(), redF(), setRed()
*/

/*!
    \fn void QColor4ub::setGreenF(float value)

    Sets the green component of this color to a floating-point \a value,
    between 0 and 1.

    \sa setRedF(), setBlueF(), setAlphaF(), greenF(), setGreen()
*/

/*!
    \fn void QColor4ub::setBlueF(float value)

    Sets the blue component of this color to a floating-point \a value,
    between 0 and 1.

    \sa setRedF(), setGreenF(), setAlphaF(), blueF(), setBlue()
*/

/*!
    \fn void QColor4ub::setAlphaF(float value)

    Sets the alpha component of this color to a floating-point \a value,
    between 0 and 1.

    \sa setRedF(), setGreenF(), setBlueF(), alphaF(), setAlpha()
*/

/*!
    \fn void QColor4ub::setRgb(int red, int green, int blue, int alpha)

    Sets the components of this color to \a red, \a green, \a blue,
    and \a alpha.  Each component is between 0 and 255.

    \sa setRgbF(), fromRgb()
*/

/*!
    \fn void QColor4ub::setRgbF(float red, float green, float blue, float alpha)

    Sets the components of this color to \a red, \a green, \a blue,
    and \a alpha.  Each component is a floating-point value between 0 and 1.

    \sa setRgb(), fromRgbF()
*/

/*!
    \fn QColor4ub QColor4ub::fromRgb(int red, int green, int blue, int alpha)

    Returns a QColor4ub with the components \a red, \a green, \a blue,
    and \a alpha.  Each component is between 0 and 255.

    \sa fromRgbF(), setRgb()
*/

/*!
    \fn QColor4ub QColor4ub::fromRgbF(float red, float green, float blue, float alpha)

    Returns a QColor4ub with the components \a red, \a green, \a blue,
    and \a alpha.  Each component is a floating-point value between 0 and 1.

    \sa fromRgb(), setRgbF()
*/

/*!
    \fn QColor4ub QColor4ub::fromRaw(const uchar *data)

    Returns a QColor4ub with components from the first four elements
    in \a data.  The \a data parameter must contain at least four
    elements and not be null.
*/

/*!
    \fn QColor QColor4ub::toColor() const

    Returns this color as a QColor.
*/

/*!
    \fn bool QColor4ub::operator==(const QColor4ub& other) const

    Returns true if this color is the same as \a other; false otherwise.
*/

/*!
    \fn bool QColor4ub::operator!=(const QColor4ub& other) const

    Returns true if this color is not the same as \a other; false otherwise.
*/

#ifndef QT_NO_DEBUG_STREAM

QDebug operator<<(QDebug dbg, const QColor4ub &color)
{
    dbg.nospace() << "QColor4ub("
        << color.redF() << ", " << color.greenF() << ", "
        << color.blueF() << ", " << color.alphaF() << ')';
    return dbg.space();
}

#endif

QT_END_NAMESPACE
