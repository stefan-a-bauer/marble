//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2007      Murad Tagirov <tmurad@gmail.com>
//


#ifndef GEODATAICONSTYLE_H
#define GEODATAICONSTYLE_H

#include <QtGui/QPixmap>
#include "GeoDataColorStyle.h"

class GeoDataIconStyle : public GeoDataColorStyle
{
  public:
    GeoDataIconStyle();

    void setIcon( const QPixmap &value );
    QPixmap icon() const;

    /*
     * Serializable methods
     */
    virtual void pack( QDataStream& stream ) const;
    virtual void unpack( QDataStream& stream );

  private:
    QPixmap m_pixmap;
};

#endif // GEODATAICONSTYLE_H
