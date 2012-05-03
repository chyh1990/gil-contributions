/*
    Copyright 2012 Christian Henning
    Use, modification and distribution are subject to the Boost Software License,
    Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
*/

/*************************************************************************************************/

#ifndef BOOST_GIL_EXTENSION_IO_BMP_IO_READ_HPP
#define BOOST_GIL_EXTENSION_IO_BMP_IO_READ_HPP

////////////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief
/// \author Christian Henning \n
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

#include "reader_backend.hpp"
#include "is_allowed.hpp"

namespace boost { namespace gil {

///
/// BMP Reader
///
template< typename Device
        , typename ConversionPolicy
        >
class reader< Device
            , bmp_tag
            , ConversionPolicy
            >
    : public reader_base< bmp_tag
                        , ConversionPolicy
                        >
    , public reader_backend< Device
                           , bmp_tag
                           >
{
private:

    typedef reader< Device
                  , bmp_tag
                  , ConversionPolicy
                  > this_t;

    typedef typename ConversionPolicy::color_converter_type cc_t;

public:

    typedef reader_backend< Device, bmp_tag > backend_t;

public:

    //
    // Constructor
    //
    reader( const Device&                         io_dev
          , const image_read_settings< bmp_tag >& settings
          )
    : backend_t( io_dev
               , settings
               )
    {}

    //
    // Constructor
    //
    reader( const Device&                         io_dev
          , const cc_t&                           cc
          , const image_read_settings< bmp_tag >& settings
          )
    : reader_base< bmp_tag
                 , ConversionPolicy
                 >( cc )
    , backend_t( io_dev
               , settings
               )
    {}


    /// Read image.
    template< typename View >
    void apply( const View& dst_view )
    {
        if( this->_info._valid == false )
        {
            io_error( "Image header was not read." );
        }


        typedef typename is_same< ConversionPolicy
                                , detail::read_and_no_convert
                                >::type is_read_and_convert_t;

        io_error_if( !detail::is_allowed< View >( this->_info
                                                , is_read_and_convert_t()
                                                )
                   , "Image types aren't compatible."
                   );

        // the row pitch must be multiple 4 bytes
        int pitch;

        if( _info._bits_per_pixel < 8 )
        {
            pitch = (( this->_info._width * this->_info._bits_per_pixel ) + 7 ) >> 3;
        }
        else
        {
            pitch = _info._width * (( this->_info._bits_per_pixel + 7 ) >> 3);
        }

        pitch = (pitch + 3) & ~3;


        std::ptrdiff_t ybeg = 0;
        std::ptrdiff_t yend = this->_settings._dim.y;
        std::ptrdiff_t yinc = 1;

        // offset to first scanline
        std::ptrdiff_t offset = 0;

        if( _info._height > 0 )
        {
            // the image is upside down
            ybeg = this->_settings._dim.y - 1;
            yend = -1;
            yinc = -1;

            offset = _info._offset
                   + (   this->_info._height
                       - this->_settings._top_left.y
                       - this->_settings._dim.y
                     ) * pitch;


        }
        else
        {
            offset = _info._offset
                   + this->_settings._top_left.y * pitch;
        }

        switch( _info._bits_per_pixel )
        {
            case 1:
            {
                this->_scanline_length = ( this->_info._width * num_channels< rgba8_view_t >::value + 3 ) & ~3;

                read_palette_image< gray1_image_t::view_t
                                  , detail::mirror_bits< byte_vector_t
                                                       , mpl::true_
                                                       >
                                  > ( dst_view
                                    , pitch
                                    , ybeg
                                    , yend
                                    , yinc
                                    , offset
                                    );
                break;
            }

            case 4:
            {
				switch ( _info._compression )
				{
				    case bmp_compression::_rle4:
				    {
                        ///@todo How can we determine that?
                        this->_scanline_length = 0;

					    read_palette_image_rle( dst_view
					                          , ybeg
					                          , yend
					                          , yinc
					                          , offset
					                          );

					    break;
                    }

				    case bmp_compression::_rgb:
				    {
                        this->_scanline_length = ( this->_info._width * num_channels< rgba8_view_t >::value + 3 ) & ~3;

					    read_palette_image< gray4_image_t::view_t
									      , detail::swap_half_bytes< byte_vector_t
									                               , mpl::true_
									                               >
									      > ( dst_view
									        , pitch
									        , ybeg
									        , yend
									        , yinc
									        , offset
									        );
					    break;
                    }

				    default:
				    {
					    io_error( "Unsupported compression mode in BMP file." );
                        break;
                    }
                }
                break;
            }

            case 8:
            {
				switch ( _info._compression )
				{
				    case bmp_compression::_rle8:
				    {
                        ///@todo How can we determine that?
                        this->_scanline_length = 0;
                        
                        read_palette_image_rle( dst_view
					                          , ybeg
					                          , yend
					                          , yinc
					                          , offset
					                          );
					    break;
                    }

				    case bmp_compression::_rgb:
				    {
                        this->_scanline_length = ( this->_info._width * num_channels< rgba8_view_t >::value + 3 ) & ~3;

					    read_palette_image< gray8_image_t::view_t
									      , detail::do_nothing< std::vector< gray8_pixel_t > >
									      > ( dst_view
									        , pitch
									        , ybeg
									        , yend
									        , yinc
									        , offset
									        );
					    break;
                    }

				    default:
				    {
					    io_error( "Unsupported compression mode in BMP file." );
                        break;
				    }
                }

                break;
            }

            case 15: case 16:
            {
                this->_scanline_length = ( this->_info._width * num_channels< rgb8_view_t >::value + 3 ) & ~3;

                read_data_15( dst_view
                            , pitch
                            , ybeg
                            , yend
                            , yinc
                            , offset
                            );

                break;
            }

            case 24:
            {
                _scanline_length = ( this->_info._width * num_channels< rgb8_view_t >::value + 3 ) & ~3;

                read_data< bgr8_view_t  >( dst_view, pitch, ybeg, yend, yinc, offset  ); 

                break;
            }

            case 32:
            {
                _scanline_length = ( this->_info._width * num_channels< rgba8_view_t >::value + 3 ) & ~3;

                read_data< bgra8_view_t >( dst_view, pitch, ybeg, yend, yinc, offset  ); 

                break;
            }
        }
    }

private:

    template< typename View_Src
            , typename Byte_Manipulator
            , typename View_Dst
            >
    void read_palette_image( const View_Dst& view
                           , int             pitch
                           , std::ptrdiff_t  ybeg
                           , std::ptrdiff_t  yend
                           , std::ptrdiff_t  yinc
                           , std::ptrdiff_t  offset
                           )
    {
        // jump to first scanline
        _io_dev.seek( static_cast< long >( offset ));

        typedef detail::row_buffer_helper_view< View_Src > rh_t;
        typedef typename rh_t::iterator_t          it_t;

        rh_t rh( pitch, true );

        // we have to swap bits
        Byte_Manipulator byte_manipulator;

        for( std::ptrdiff_t y = ybeg; y != yend; y += yinc )
        {
            // @todo: For now we're reading the whole scanline which is
            // slightly inefficient. Later versions should try to read
            // only the bytes which are necessary.
            _io_dev.read( reinterpret_cast< byte_t* >( rh.data() )
                        , pitch
                        );

            byte_manipulator( rh.buffer() );

            typename View_Dst::x_iterator dst_it = view.row_begin( y );

            it_t it  = rh.begin() + this->_settings._top_left.x;
            it_t end = it + this->_settings._dim.x;

            for( ; it != end; ++it, ++dst_it )
            {
                unsigned char c = get_color( *it, gray_color_t() );
                *dst_it = this->_palette[ c ];
            }
        }
    }

    template< typename View >
    void read_data_15( const View&    view
                     , int            pitch
                     , std::ptrdiff_t ybeg
                     , std::ptrdiff_t yend
                     , std::ptrdiff_t yinc
                     , std::ptrdiff_t offset
                     )
    {
        byte_vector_t row( pitch );

        // read the color masks
        color_mask mask = { {0} };
        if( _info._compression == bmp_compression::_bitfield )
        {
            this->_mask.red.mask    = this->_io_dev.read_uint32();
            this->_mask.green.mask  = this->_io_dev.read_uint32();
            this->_mask.blue.mask   = this->_io_dev.read_uint32();

            this->_mask.red.width   = detail::count_ones( this->_mask.red.mask   );
            this->_mask.green.width = detail::count_ones( this->_mask.green.mask );
            this->_mask.blue.width  = detail::count_ones( this->_mask.blue.mask  );

            this->_mask.red.shift   = detail::trailing_zeros( this->_mask.red.mask   );
            this->_mask.green.shift = detail::trailing_zeros( this->_mask.green.mask );
            this->_mask.blue.shift  = detail::trailing_zeros( this->_mask.blue.mask  );
        }
        else if( _info._compression == bmp_compression::_rgb )
        {
            switch( _info._bits_per_pixel )
            {
                case 15:
                case 16:
                {
                    _mask.red.mask   = 0x007C00; _mask.red.width   = 5; _mask.red.shift   = 10;
                    _mask.green.mask = 0x0003E0; _mask.green.width = 5; _mask.green.shift =  5;
                    _mask.blue.mask  = 0x00001F; _mask.blue.width  = 5; _mask.blue.shift  =  0;

                    break;
                }

                case 24:
                case 32:
                {
                    _mask.red.mask   = 0xFF0000; _mask.red.width   = 8; _mask.red.shift   = 16;
                    _mask.green.mask = 0x00FF00; _mask.green.width = 8; _mask.green.shift =  8;
                    _mask.blue.mask  = 0x0000FF; _mask.blue.width  = 8; _mask.blue.shift  =  0;

                    break;
                }
            }
        }
        else
        {
            io_error( "bmp_reader::apply(): unsupported BMP compression" );
        }

        // jump to first scanline
        _io_dev.seek( static_cast< long >( offset ));

        typedef rgb8_image_t image_t;
        typedef image_t::view_t::x_iterator it_t;

        for( std::ptrdiff_t y = ybeg; y != yend; y += yinc )
        {
            // @todo: For now we're reading the whole scanline which is
            // slightly inefficient. Later versions should try to read
            // only the bytes which are necessary.
            _io_dev.read( &row.front(), row.size() );

            image_t img_row( _info._width, 1 );
            image_t::view_t v = gil::view( img_row );
            it_t it = v.row_begin( 0 );

            it_t beg = v.row_begin( 0 ) + this->_settings._top_left.x;
            it_t end = beg + this->_settings._dim.x;

            byte_t* src = &row.front();
            for( int32_t i = 0 ; i < _info._width; ++i, src += 2 )
            {
                int p = ( src[1] << 8 ) | src[0];

                int r = ((p & _mask.red.mask)   >> _mask.red.shift)   << (8 - _mask.red.width);
                int g = ((p & _mask.green.mask) >> _mask.green.shift) << (8 - _mask.green.width);
                int b = ((p & _mask.blue.mask)  >> _mask.blue.shift)  << (8 - _mask.blue.width);

                get_color( it[i], red_t()   ) = static_cast< byte_t >( r );
                get_color( it[i], green_t() ) = static_cast< byte_t >( g );
                get_color( it[i], blue_t()  ) = static_cast< byte_t >( b );
            }

            this->_cc_policy.read( beg
                                 , end
                                 , view.row_begin( y )
                                 );
        }
    }


    // 8-8-8 BGR
    // 8-8-8-8 BGRA
    template< typename View_Src
            , typename View_Dst
            >
    void read_data( const View_Dst& view
                  , int             pitch
                  , std::ptrdiff_t  ybeg
                  , std::ptrdiff_t  yend
                  , std::ptrdiff_t  yinc
                  , std::ptrdiff_t  offset
                  )
    {
        byte_vector_t row( pitch );

        // jump to first scanline
        _io_dev.seek( static_cast< long >( offset ));

        View_Src v = interleaved_view( _info._width
                                     , 1
                                     , (typename View_Src::value_type*) &row.front()
                                     , _info._width * num_channels< View_Src >::value
                                     );

        typename View_Src::x_iterator beg = v.row_begin( 0 ) + this->_settings._top_left.x;
        typename View_Src::x_iterator end = beg + this->_settings._dim.x;

        for( std::ptrdiff_t y = ybeg; y != yend; y += yinc )
        {
            // @todo: For now we're reading the whole scanline which is
            // slightly inefficient. Later versions should try to read
            // only the bytes which are necessary.
            _io_dev.read( &row.front(), row.size() );

            this->_cc_policy.read( beg
                                 , end
                                 , view.row_begin( y )
                                 );
        }
    }


	template< typename Buffer
            , typename View
	        >
	void copy_row_if_needed( const Buffer&  buf
	                       , const View&    view
						   , std::ptrdiff_t y
						   )
	{
		if(  y >= this->_settings._top_left.y
		  && y <  this->_settings._dim.y
		  )
		{
            typename Buffer::const_iterator beg = buf.begin() + this->_settings._top_left.x;
            typename Buffer::const_iterator end = beg + this->_settings._dim.x;

			std::copy( beg
			         , end
			         , view.row_begin( y )
			         );
		}
	}

    template< typename View_Dst >
    void read_palette_image_rle( const View_Dst& view
                               , std::ptrdiff_t  ybeg
                               , std::ptrdiff_t  yend
                               , std::ptrdiff_t  yinc
                               , std::ptrdiff_t  offset
                               )
    {
        assert(  _info._compression == bmp_compression::_rle4
              || _info._compression == bmp_compression::_rle8
              );

        read_palette();

        // jump to start of rle4 data
        _io_dev.seek( static_cast< long >( offset ));

        // we need to know the stream position for padding purposes
        std::size_t stream_pos = offset;

        typedef std::vector< rgba8_pixel_t > Buf_type;
        Buf_type buf( this->_settings._dim.x );
        Buf_type::iterator dst_it  = buf.begin();
        Buf_type::iterator dst_end = buf.end();

        std::ptrdiff_t y = ybeg;
        bool finished = false;

        while ( !finished )
        {
            std::ptrdiff_t count  = _io_dev.read_uint8();
            std::ptrdiff_t second = _io_dev.read_uint8();
            stream_pos += 2;

            if ( count )
            {
                // encoded mode

                // clamp to boundary
                if( count > dst_end - dst_it )
                {
                    count = dst_end - dst_it;
                }

                if( _info._compression == bmp_compression::_rle4 )
                {
                    std::ptrdiff_t cs[2] = { second >> 4, second & 0x0f };

                    for( int i = 0; i < count; ++i )
                    {
                        *dst_it++ = this->_palette[ cs[i & 1] ];
                    }
                }
                else
                {
                    for( int i = 0; i < count; ++i )
                    {
                        *dst_it++ = this->_palette[ second ];
                    }
                }
            }
            else
            {
                switch( second )
                {
                    case 0:  // end of row
                    {
                        copy_row_if_needed( buf, view, y );

                        y += yinc;
                        if( y == yend )
                        {
                            finished = true;
                        }
                        else
                        {
                            dst_it = buf.begin();
                            dst_end = buf.end();
                        }

                        break;
                    }

                    case 1:  // end of bitmap
                    {
                        copy_row_if_needed( buf, view, y );
                        finished = true;

                        break;
                    }

                    case 2:  // offset coordinates
                    {
                        std::ptrdiff_t dx = _io_dev.read_uint8();
                        std::ptrdiff_t dy = _io_dev.read_uint8() * yinc;
                        stream_pos += 2;

                        if( dy )
                        {
                            copy_row_if_needed( buf, view, y );
                        }

                        std::ptrdiff_t x = dst_it - buf.begin();
                        x += dx;

                        if( x > _info._width )
                        {
                            io_error( "Mangled BMP file." );
                        }

                        y += dy;
                        if( yinc > 0 ? y > yend : y < yend )
                        {
                            io_error( "Mangled BMP file." );
                        }

                        dst_it = buf.begin() + x;
                        dst_end = buf.end();

                        break;
                    }

                    default:  // absolute mode
                    {
                        count = second;

                        // clamp to boundary
                        if( count > dst_end - dst_it )
                        {
                            count = dst_end - dst_it;
                        }

                        if ( _info._compression == bmp_compression::_rle4 )
                        {
                            for( int i = 0; i < count; ++i )
                            {
                                uint8_t packed_indices = _io_dev.read_uint8();
                                ++stream_pos;

                                *dst_it++ = this->_palette[ packed_indices >> 4 ];
                                if( ++i == second )
                                    break;

                                *dst_it++ = this->_palette[ packed_indices & 0x0f ];
                            }
                        }
                        else
                        {
                            for( int i = 0; i < count; ++i )
                            {
                                uint8_t c = _io_dev.read_uint8();
                                ++stream_pos;
                                *dst_it++ = this->_palette[ c ];
                             }
                        }

                        // pad to word boundary
                        if( ( stream_pos - offset ) & 1 )
                        {
                            _io_dev.seek( 1, SEEK_CUR );
                            ++stream_pos;
                        }

                        break;
                    }
                }
            }
        }
	}
};

///
/// BMP Dynamic Reader
///
template< typename Device >
class dynamic_image_reader< Device
                          , bmp_tag
                          >
    : public reader< Device
                   , bmp_tag
                   , detail::read_and_no_convert
                   >
{
    typedef reader< Device
                  , bmp_tag
                  , detail::read_and_no_convert
                  > parent_t;

public:

    dynamic_image_reader( const Device&                         io_dev
                        , const image_read_settings< bmp_tag >& settings
                        )
    : parent_t( io_dev
              , settings
              )
    {}

    template< typename Images >
    void apply( any_image< Images >& images )
    {
        detail::bmp_type_format_checker format_checker( this->_info._bits_per_pixel );

        if( !construct_matched( images
                              , format_checker
                              ))
        {
            io_error( "No matching image type between those of the given any_image and that of the file" );
        }
        else
        {
            init_image( images
                      , this->_settings
                      );

            detail::dynamic_io_fnobj< detail::bmp_read_is_supported
                                    , parent_t
                                    > op( this );

            apply_operation( view( images )
                           , op
                           );
        }
    }
};

namespace detail {

class bmp_type_format_checker
{
public:

    bmp_type_format_checker( const bmp_bits_per_pixel::type& bpp )
    : _bpp( bpp )
    {}

    template< typename Image >
    bool apply()
    {
        if( _bpp < 32 )
        {
            return pixels_are_compatible< typename Image::value_type, rgb8_pixel_t >::value
                   ? true
                   : false;
        }
        else
        {
            return pixels_are_compatible< typename Image::value_type, rgba8_pixel_t >::value
                   ? true
                   : false;
        }
    }

private:

    const bmp_bits_per_pixel::type& _bpp;
};

struct bmp_read_is_supported
{
    template< typename View >
    struct apply : public is_read_supported< typename get_pixel_type< View >::type
                                           , bmp_tag
                                           >
    {};
};

} // detail

} // gil
} // boost

#endif // BOOST_GIL_EXTENSION_IO_BMP_IO_READ_HPP
