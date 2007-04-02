/*
 * FastRPC -- Fast RPC library compatible with XML-RPC
 * Copyright (C) 2005-7  Seznam.cz, a.s.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Seznam.cz, a.s.
 * Radlicka 2, Praha 5, 15000, Czech Republic
 * http://www.seznam.cz, mailto:fastrpc@firma.seznam.cz
 *
 * FILE          $Id: frpcunmarshaller.cc,v 1.2 2007-04-02 15:28:20 vasek Exp $
 *
 * DESCRIPTION   
 *
 * AUTHOR        
 *              Miroslav Talasek <miroslav.talasek@firma.seznam.cz>
 *
 * HISTORY
 *       
 */
#include "frpcunmarshaller.h"
#include <frpcbinunmarshaller.h>
#include <frpcxmlunmarshaller.h>
#include <frpcerror.h>
#include <frpcinternals.h>

namespace FRPC
{

UnMarshaller_t::UnMarshaller_t()
{}


UnMarshaller_t::~UnMarshaller_t()
{}


UnMarshaller_t* UnMarshaller_t::create(long contentType,
                                       DataBuilder_t& dataBuilder)
{
    UnMarshaller_t *unMarshaller;

    switch(contentType)
    {
    case BINARY_RPC:
        unMarshaller = new BinUnMarshaller_t(dataBuilder);
        break;

    case XML_RPC:
        unMarshaller = new XmlUnMarshaller_t(dataBuilder);
        break;

    default:
        throw Error_t("This unMarshaller not exists");
        break;
    }

    return unMarshaller;
}

UnMarshaller_t* UnMarshaller_t::create(const char* data, long size,
                                       DataBuilder_t& dataBuilder)
{
    UnMarshaller_t *unMarshaller;
    char magic[]={0xCA, 0x11, FRPC_MAJOR_VERSION, FRPC_MINOR_VERSION};
    
    if(size < 4)
    {
        unMarshaller = new XmlUnMarshaller_t(dataBuilder);
        unMarshaller->unMarshall(data, size, TYPE_ANY);
    }
        
    if(memcmp(data, magic, 4) != 0)
    {
        unMarshaller = new XmlUnMarshaller_t(dataBuilder);
        unMarshaller->unMarshall(data, size, TYPE_ANY);
    }
    else
    {
        unMarshaller = new BinUnMarshaller_t(dataBuilder);
        unMarshaller->unMarshall(data, size, TYPE_ANY);
    }  
        

    return unMarshaller;
}
}

