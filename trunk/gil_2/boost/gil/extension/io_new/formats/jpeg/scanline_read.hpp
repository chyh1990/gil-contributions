/*
    Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
    Use, modification and distribution are subject to the Boost Software License,
    Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
*/

/*************************************************************************************************/

#ifndef BOOST_GIL_EXTENSION_IO_JPEG_IO_SCANLINE_READ_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_IO_SCANLINE_READ_HPP

////////////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief
/// \author Christian Henning, Andreas Pokorny, Lubomir Bourdev \n
///
/// \date   2007-2012 \n
///
////////////////////////////////////////////////////////////////////////////////////////

#include <csetjmp>
#include <vector>

#include <boost/function.hpp>

#include <boost/gil/extension/io_new/detail/base.hpp>
#include <boost/gil/extension/io_new/detail/conversion_policies.hpp>
#include <boost/gil/extension/io_new/detail/reader_base.hpp>
#include <boost/gil/extension/io_new/detail/io_device.hpp>
#include <boost/gil/extension/io_new/detail/typedefs.hpp>

#include "backend.hpp"
#include "base.hpp"
#include "is_allowed.hpp"

namespace boost { namespace gil {

///
/// JPEG Scanline Reader
///
template< typename Device >
class scanline_reader< Device
                     , jpeg_tag
                     >
    : public reader_backend< Device
                           , jpeg_tag
                           >
{
public:

    typedef reader_backend< Device, jpeg_tag > backend_t;

public:
    scanline_reader( Device&                                device
                   , const image_read_settings< jpeg_tag >& settings
                   )
    : reader_backend< Device
                    , jpeg_tag
                     >( device
                      , settings
                      )
    {}

    void initialize()
    {
        this->_cinfo.dct_method = this->_settings._dct_method;

        io_error_if( jpeg_start_decompress( &this->_cinfo ) == false
                    , "Cannot start decompression." );

        switch( this->_info._color_space )
        {
            case JCS_GRAYSCALE:
            {
                this->_scanline_length = this->_info._width;

                break;
            }

            case JCS_RGB:
            //!\todo add Y'CbCr? We loose image quality when reading JCS_YCbCr as JCS_RGB
            case JCS_YCbCr:
            {
                this->_scanline_length = this->_info._width * num_channels< rgb8_view_t >::value;

                break;
            }


            case JCS_CMYK:
            //!\todo add Y'CbCrK? We loose image quality when reading JCS_YCCK as JCS_CMYK
            case JCS_YCCK:
            {
                this->_cinfo.out_color_space = JCS_CMYK;
                this->_scanline_length = this->_info._width * num_channels< cmyk8_view_t >::value;

                break;
            }

            default: { io_error( "Unsupported jpeg color space." ); }
        }
    }

    void read( byte_t* dst, int pos )
    {
        // Fire exception in case of error.
        if( setjmp( this->_mark )) { this->raise_error(); }

        // read data
        read_scanline( dst );
    }

    /// Skip over a scanline.
    void skip( byte_t* dst, int )
    {
        // Fire exception in case of error.
        if( setjmp( this->_mark )) { this->raise_error(); }

        // read data
        read_scanline( dst );
    }

    void clean_up()
    {
        ///@todo
        //jpeg_finish_decompress ( &this->_cinfo );
    }

private:

    void read_scanline( byte_t* dst )
    {
        JSAMPLE *row_adr = reinterpret_cast< JSAMPLE* >( dst );

        // Read data.
        io_error_if( jpeg_read_scanlines( &this->_cinfo
                                        , &row_adr
                                        , 1
                                        ) != 1
                    , "jpeg_read_scanlines: fail to read JPEG file"
                    );

    }
};

} // namespace gil
} // namespace boost

#endif // BOOST_GIL_EXTENSION_IO_JPEG_IO_SCANLINE_READ_HPP