/*
    Copyright 2012 Kenneth Riddile and Christian Henning
    Use, modification and distribution are subject to the Boost Software License,
    Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
*/

/*************************************************************************************************/

#ifndef BOOST_GIL_EXTENSION_IO_TARGA_IO_SCANLINE_READ_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_IO_SCANLINE_READ_HPP

////////////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief
/// \author Kenneth Riddile and Christian Henning \n
///
/// \date 2012 \n
///
////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <boost/gil/extension/io_new/detail/base.hpp>
#include <boost/gil/extension/io_new/detail/bit_operations.hpp>
#include <boost/gil/extension/io_new/detail/conversion_policies.hpp>
#include <boost/gil/extension/io_new/detail/row_buffer_helper.hpp>
#include <boost/gil/extension/io_new/detail/reader_base.hpp>
#include <boost/gil/extension/io_new/detail/io_device.hpp>
#include <boost/gil/extension/io_new/detail/typedefs.hpp>

#include "backend.hpp"
#include "is_allowed.hpp"

namespace boost { namespace gil {

///
/// Targa Scanline Reader
///
template< typename Device >
class scanline_reader< Device
                     , targa_tag
                     >
    : public reader_backend< Device
                           , targa_tag
                           >
{
private:

    typedef scanline_reader< Device
                           , targa_tag
                           > this_t;

public:

    typedef reader_backend< Device
                          , targa_tag
                          > backend_t;

public:

    //
    // Constructor
    //
    scanline_reader( Device&                                 device
                   , const image_read_settings< targa_tag >& settings
                   )
    : reader_backend( device
                    , settings
                    )
    {}

    void initialize()
    {
        std::ptrdiff_t yend = this->_settings._dim.y;
        
        switch( this->_info._image_type )
        {
            case targa_image_type::_rgb:
            {
                if( this->_info._color_map_type != targa_color_map_type::_rgb )
                {
                    io_error( "Inconsistent color map type and image type in targa file." );
                }
                
                if( this->_info._color_map_length != 0 )
                {
                    io_error( "Non-indexed targa files containing a palette are not supported." );
                }
                
                switch( _info._bits_per_pixel )
                {
                    case 24:
                    case 32:
                    {
                        this->_scanline_length = this->_info._width * ( this->_info._bits_per_pixel / 8 );

                        // jump to first scanline
                        this->_io_dev.seek( static_cast<long>(_info._offset) );

                        break;
                    }
                    default:
                    {
                        io_error( "Unsupported bit depth in targa file." );
                        break;
                    }
                }
                
                break;
            }
            default:
            {
                io_error( "Unsupported image type in targa file." );
                break;
            }
        }
    }

    void clean_up() {}

    /// Read part of image defined by View and return the data.
    void read( byte_t* dst, int pos )
    {
        read_row( dst );
    }

    /// Skip over a scanline.
    void skip( byte_t*, int )
    {
        _io_dev.seek( static_cast<long>( this->_scanline_length ), SEEK_CUR );
    }

private:

    void read_row( byte_t* dst )
    {
        _io_dev.read( dst, this->_scanline_length );
    }
};

} // namespace gil
} // namespace boost

#endif // BOOST_GIL_EXTENSION_IO_TARGA_IO_SCANLINE_READ_HPP
