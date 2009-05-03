//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009      Bastian Holst <bastianholst@gmx.de>
//

// Self
#include "CoordinatesParser.h"

// Marble
#include "GeoDataCoordinates.h"

using namespace Marble;

CoordinatesParser::CoordinatesParser( GeoDataCoordinates *coordinates )
    : m_coordinates( coordinates )
{
}

bool CoordinatesParser::read( QIODevice *device ) {
    setDevice( device );
    
    while( !atEnd() ) {
        readNext();
        
        if( isStartElement() ) {
            if ( name() == "rsp" && attributes().value( "stat" ) == "ok" )
                readRsp();
            else if ( name() == "rsp" )
                raiseError( "Query failed" );
            else
                raiseError( "The file is not an valid Flickr answer." );
        }
    }
    
    return !error();
}


void CoordinatesParser::readUnknownElement() {
    Q_ASSERT( isStartElement() );

    while ( !atEnd() ) {
        readNext();

        if ( isEndElement() )
            break;

        if ( isStartElement() )
            readUnknownElement();
    }
}

void CoordinatesParser::readRsp() {
    Q_ASSERT( isStartElement() );
    
    while( !atEnd() ) {
        readNext();
        
        if( isEndElement() )
            break;
        
        if( isStartElement() ) {
            if( name() == "photo" )
                readPhoto();
            else
                readUnknownElement();
        }
    }
}

void CoordinatesParser::readPhoto() {
    Q_ASSERT( isStartElement()
              && name() == "photo" );
    
    while( !atEnd() ) {
        readNext();
        
        if( isEndElement() )
            break;
        
        if( isStartElement() ) {
            if( name() == "location" )
                readLocation();
            else
                readUnknownElement();
        }
    }
}

void CoordinatesParser::readLocation() {
    Q_ASSERT( isStartElement()
              && name() == "location" );
 
    m_coordinates->setLatitude( attributes().value( "latitude" ).string()->toDouble() * DEG2RAD );
    m_coordinates->setLongitude( attributes().value( "longitude" ).string()->toDouble() * DEG2RAD );
    
    while( !atEnd() ) {
        readNext();
        
        if( isEndElement() )
            break;
        
        if( isStartElement() )
            break;
    }
}
