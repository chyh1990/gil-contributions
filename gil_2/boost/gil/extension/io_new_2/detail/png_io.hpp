/*
  Copyright 2007-2008 Andreas Pokorny
  Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
  or a copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/*************************************************************************************************/

#ifndef BOOST_GIL_EXTENSION_IO_DETAIL_PNG_IO_HPP_INCLUDED
#define BOOST_GIL_EXTENSION_IO_DETAIL_PNG_IO_HPP_INCLUDED 

extern "C" {
#include <png.h>
}

#include <boost/gil/extension/io_new_2/detail/base.hpp>
#include <boost/gil/extension/io_new_2/png_tags.hpp>

namespace boost { namespace gil { namespace detail {

template<typename Device>
class png_io_base
{
public:
    png_io_base( Device & io_dev )
        : _io_dev(io_dev)
    {}

protected:
    Device & _io_dev;

    void check() const
    {
        unsigned char buf[PNG_BYTES_TO_CHECK];

        io_error_if(_io_dev.read(buf, PNG_BYTES_TO_CHECK) != PNG_BYTES_TO_CHECK,
                "png_check_validity: failed to read image");

        io_error_if(png_sig_cmp(png_bytep(buf), png_size_t(0), PNG_BYTES_TO_CHECK)!=0,
                "png_check_validity: invalid png image");
    }

    static void read_data(png_structp png_ptr, png_bytep data, png_size_t length)
    {
        static_cast<Device*>(png_get_io_ptr(png_ptr) )->read(data, length );
    }
    static void write_data(png_structp png_ptr,
            png_bytep data, png_size_t length)
    {
        static_cast<Device*>(png_get_io_ptr(png_ptr) )->write(data, length );
    }
    static void flush(png_structp png_ptr)
    {
        static_cast<Device*>(png_get_io_ptr(png_ptr) )->flush();
    }

};

template< typename Device
        , typename ConversionPolicy
        >
class reader< Device
            , png_tag
            , ConversionPolicy
            > : public png_io_base< Device >
{
public:

    reader( Device& io_dev )
    : png_io_base< Device >( io_dev )
    , _png_ptr ( 0 )
    , _info_ptr( 0 )
    {
        this->check();
        init_reader();
    }

    reader( Device& io_dev
          , const typename ConversionPolicy::color_converter_type& cc )
    : png_io_base< Device >( io_dev )
    , cc_policy( cc )
    , _png_ptr ( 0 )
    , _info_ptr( 0 )
    {
        this->check();
        init_reader();
    }

    ~reader()
    {
        png_destroy_read_struct(&_png_ptr,&_info_ptr,png_infopp_NULL);
    }

    image_read_info<png_tag> get_info() const
    {
        image_read_info<png_tag> ret = {0};
        png_get_IHDR(_png_ptr, _info_ptr, 
                &ret._width, &ret._height,
                &ret._bit_depth,&ret._color_type,
                &ret._interlace_method, &ret._compression_method,
                &ret._filter_method );

        int res_unit = PNG_RESOLUTION_METER;
        png_get_pHYs(_png_ptr, _info_ptr, &ret._x_res, &ret._y_res, &res_unit);
        png_get_sBIT(_png_ptr, _info_ptr, &ret._sbits );

#ifdef PNG_FLOATING_POINT_SUPPORTED 
        png_get_gAMA(_png_ptr, _info_ptr, &ret._gamma );
#else
        png_get_gAMA_fixed(_png_ptr, _info_ptr, &ret._gamma );
#endif
        return ret;
    }

    template<typename Image>
    void read_image( Image&         image
                   , const point_t& top_left
                   , const point_t& bottom_right
                   )
    {
        image_read_info< png_tag > info( get_info() );

        check_coordinates( top_left
                         , bottom_right
                         , info
                         );

        point_t _bottom_right;

        if( bottom_right == point_t( 0, 0 ))
        {
            _bottom_right.x = info._width  - 1;
            _bottom_right.y = info._height - 1;
        }
        else
        {
            _bottom_right = bottom_right;
        }

        image.recreate( ( _bottom_right.x + 1 ) - top_left.x
                      , ( _bottom_right.y + 1 ) - top_left.y );

        read_data( view( image )
                 , top_left
                 , _bottom_right
                 , info
                 );
    }

    template<typename View>
    void read_view( const View&    view
                  , const point_t& top_left
                  , const point_t& bottom_right
                  )
    {
        image_read_info<png_tag> info(get_info());

        check_coordinates( top_left
                         , bottom_right
                         , _info
                         );

        point_t _bottom_right;

        if( bottom_right == point_t( 0, 0 ))
        {
            _bottom_right.x = info._width  - 1;
            _bottom_right.y = info._height - 1;
        }
        else
        {
            _bottom_right = bottom_right;
        }

        read_data( view
                 , top_left
                 , _bottom_right
                 , info
                 );
    }

private:
    template<typename View>
    void read_data( const View&                       view
                  , const point_t&                    top_left
                  , const point_t&                    bottom_right
                  , const image_read_info< png_tag >& info
                  )
    {
        if (little_endian() )
        {   
            if( info._bit_depth == 16 )
                png_set_swap(_png_ptr);
            if( info._bit_depth < 8 )
                png_set_packswap(_png_ptr);
        }
        png_bitdepth::type bit_depth = info._bit_depth;
        png_color_type::type color_type = info._color_type;
        
        if(color_type == PNG_COLOR_TYPE_PALETTE)
        {
            color_type = PNG_COLOR_TYPE_RGB;
            bit_depth = 8;
            png_set_palette_to_rgb(_png_ptr);
        }

        if(png_get_valid(_png_ptr, _info_ptr,PNG_INFO_tRNS)) 
        {
            if( color_type == PNG_COLOR_TYPE_RGB )
                color_type = PNG_COLOR_TYPE_RGBA;
            else if( color_type== PNG_COLOR_TYPE_GRAY )
                color_type = PNG_COLOR_TYPE_GA;

            png_set_tRNS_to_alpha(_png_ptr);
        }

        typedef unsigned char byte;
        typedef bit_aligned_pixel_reference<byte,mpl::vector_c<int,1>,gray_layout_t,true> gray_1b;
        typedef bit_aligned_pixel_reference<byte,mpl::vector_c<int,2>,gray_layout_t,true> gray_2b;
        typedef bit_aligned_pixel_reference<byte,mpl::vector_c<int,4>,gray_layout_t,true> gray_4b;


        switch( color_type )
        {
            case PNG_COLOR_TYPE_GRAY:
            {
                switch( bit_depth )
                {
                    case 1: read_rows< gray_1b >       ( view, top_left, bottom_right ); break;
                    case 2: read_rows< gray_2b >       ( view, top_left, bottom_right ); break;
                    case 4: read_rows< gray_4b >       ( view, top_left, bottom_right ); break;
                    case 8: read_rows< gray8_pixel_t > ( view, top_left, bottom_right ); break;
                    case 16:read_rows< gray16_pixel_t >( view, top_left, bottom_right ); break;
                    default: io_error("png_reader::read_data(): unknown combination of color type and bit depth");
                }

                break;
            }
            case PNG_COLOR_TYPE_GA:
            {
                switch( bit_depth )
                {
                    case 8: read_rows< gray_alpha8_pixel_t > ( view, top_left, bottom_right ); break;
                    case 16:read_rows< gray_alpha16_pixel_t >( view, top_left, bottom_right ); break;
                    default: io_error("png_reader::read_data(): unknown combination of color type and bit depth");
                }

                break;
            }
            case PNG_COLOR_TYPE_RGB:
            {
                switch (bit_depth)
                {
                    case 8:  read_rows< rgb8_pixel_t > ( view, top_left, bottom_right ); break;
                    case 16: read_rows< rgb16_pixel_t >( view, top_left, bottom_right ); break;
                    default: io_error("png_reader::read_data(): unknown combination of color type and bit depth");
                }

                break;
            }
            case PNG_COLOR_TYPE_RGBA:
            {
                switch( bit_depth )
                {
                    case 8 : read_rows< rgba8_pixel_t > ( view,top_left, bottom_right ); break;
                    case 16: read_rows< rgba16_pixel_t >( view,top_left, bottom_right ); break;
                    default: io_error("png_reader_color_convert::read_data(): unknown combination of color type and bit depth");
                }

                break;
            }
            default: io_error("png_reader_color_convert::read_data(): unknown color type");
        }

        png_read_end( _png_ptr
                    , NULL
                    );
    }

    template< typename ImagePixel
            , typename View
            >
    void read_rows( const View& view
                  , const point_t& top_left
                  , const point_t& bottom_right
                  )
    {
        io_error_if( ! ConversionPolicy::template is_allowed< ImagePixel
                                                            , typename View::value_type
                                                            >::type::value
                    , "User provided view has incorrect size."
                    );

        row_buffer_helper<ImagePixel> buffer( static_cast<int>( view.width() ));

        // skip rows
        for( int y = 0; y < top_left.y; ++y )
        {
            png_read_row( _png_ptr
                        , reinterpret_cast< png_bytep >( buffer.data() )
                        , 0
                        );
        }

        for(int y = 0; y < view.height(); ++y )
        {
            png_read_row( _png_ptr
                        , reinterpret_cast< png_bytep >( buffer.data() )
                        , 0
                        );

            cc_policy.read( buffer.begin() + top_left.x
                          , buffer.begin() + bottom_right.x + 1
                          , view.row_begin( y )
                          );
        }
    }

    void init_reader()
    {
        _png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
        io_error_if(_png_ptr==NULL,"png_reader: fail to call png_create_write_struct()");
        // allocate/initialize the image information data
        _info_ptr = png_create_info_struct(_png_ptr);

        if (_info_ptr == NULL) {
            png_destroy_read_struct(&_png_ptr,png_infopp_NULL,png_infopp_NULL);
            io_error("png_reader: fail to call png_create_info_struct()");
        }
        if (setjmp(png_jmpbuf(_png_ptr))) {
            //free all of the memory associated with the png_ptr and info_ptr
            png_destroy_read_struct(&_png_ptr, &_info_ptr, png_infopp_NULL);
            io_error("png_reader: fail to call setjmp()");
        }

        init_io( _png_ptr );

        png_set_sig_bytes(_png_ptr,PNG_BYTES_TO_CHECK);
        png_read_info(_png_ptr, _info_ptr);
    }

    void init_io( png_structp png_ptr )
    {
        png_set_read_fn(png_ptr, 
                static_cast<void*>(&this->_io_dev), 
                static_cast<void(*)(png_structp, png_bytep, png_size_t)>(&png_io_base<Device>::read_data));
    }

    ConversionPolicy cc_policy;
    png_structp _png_ptr;
    png_infop _info_ptr;
};

template<typename Device>
class writer<Device,png_tag> : png_io_base<Device>
{
public:

    writer( Device & io_dev )
        : png_io_base<Device>(io_dev), _png_ptr(0), _info_ptr(0)
    {
        _png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
        io_error_if(_png_ptr==NULL,"png_writer: fail to call png_create_write_struct()");
        // allocate/initialize the image information data
        _info_ptr = png_create_info_struct(_png_ptr);

        if (_info_ptr == NULL) {
            png_destroy_write_struct(&_png_ptr,png_infopp_NULL);
            io_error("png_writer: fail to call png_create_info_struct()");
        }
        if (setjmp(png_jmpbuf(_png_ptr))) {
            //free all of the memory associated with the png_ptr and info_ptr
            png_destroy_write_struct(&_png_ptr, &_info_ptr);
            io_error("png_writer: fail to call setjmp()");
        }

        this->init_io( _png_ptr );
    }
    ~writer()
    {
        png_destroy_write_struct(&_png_ptr,&_info_ptr);
    }


    template <typename View>
    void apply( const View&                      view
              , const image_write_info<png_tag>& info )
    {
        typedef png_rw_support< typename channel_type<View>::type
                              , typename color_space_type<View>::type
                              > png_rw_info;

        png_set_IHDR( _png_ptr
                    , _info_ptr
                    , view.width()
                    , view.height()
                    , png_rw_info::bit_depth
                    , png_rw_info::color_type
                    , info._interlace_method
                    , info._compression_method
                    , info._filter_method 
                    );

#ifdef PNG_FLOATING_POINT_SUPPORTED 
        png_set_gAMA( _png_ptr
                    , _info_ptr
                    , info._gamma
                    );
#else
        png_set_gAMA_fixed( _png_ptr
                          , _info_ptr
                          , info._gamma
                          );
#endif

        png_set_pHYs( _png_ptr
                    , _info_ptr
                    , &info._x_res
                    , &info._y_res
                    , PNG_RESOLUTION_METER
                    );

        png_set_sBIT( _png_ptr
                    , _info_ptr
                    , const_cast< png_color_8* >( &info._sbits )
                    );

        png_write_info( _png_ptr
                      ,_info_ptr
                      );

        write_view( view
                  , is_bit_aligned< View >::type );
    }

    template< typename View >
    void apply( const View& view )
    {
        typedef png_rw_support<
                        typename kth_semantic_element_type<typename View::value_type, 0>::type,
                        typename color_space_type<View>::type
                        > png_rw_info;
        png_set_IHDR(_png_ptr, _info_ptr, 
                view.width(),
                view.height(),
                png_rw_info::bit_depth,
                png_rw_info::color_type,
                PNG_INTERLACE_NONE,
                PNG_COMPRESSION_TYPE_DEFAULT,
                PNG_FILTER_TYPE_DEFAULT);

        png_write_info(_png_ptr,_info_ptr);
        write_view( view
                  , is_bit_aligned< View >::type() );
    }

private:
    template<typename View>
    void write_view( const View& view
                   ,  boost::mpl::false_ // is bit aligned
                   )
    {
        typedef png_rw_support<
                        typename channel_type<View>::type,
                        typename color_space_type<View>::type
                        > png_rw_info;

        if (little_endian() )
        {   
            if( png_rw_info::bit_depth == 16 )
                png_set_swap(_png_ptr);
            if( png_rw_info::bit_depth < 8 )
                png_set_packswap(_png_ptr);
        }

        row_buffer_helper_view<View> row_buffer( view.width() );

        for( int y = 0; y != view.height(); ++ y) 
        {
            std::copy( view.row_begin( y )
                     , view.row_end  ( y )
                     , row_buffer.begin()
                     );

            png_write_row( _png_ptr
                         , reinterpret_cast< png_bytep >( row_buffer.data() )
                         );
        }
        
        png_write_end( _png_ptr
                     , _info_ptr
                     );
    }

    template<typename View>
    void write_view( const View& view
                   , boost::mpl::true_ // is bit aligned
                   ) 
    {
        typedef png_rw_support< typename kth_semantic_element_type< typename View::value_type
                                                                 , 0>::type,
                        typename color_space_type<View>::type
                        > png_rw_info;

        if (little_endian() )
        {   
            if( png_rw_info::bit_depth == 16 )
                png_set_swap(_png_ptr);
            if( png_rw_info::bit_depth < 8 )
                png_set_packswap(_png_ptr);
        }

        row_buffer_helper_view< View > row_buffer( view.width() );

        for( int y = 0; y != view.height(); ++ y) 
        {
            std::copy( view.row_begin( y )
                     , view.row_end  ( y )
                     , row_buffer.begin()
                     );

            png_write_row( _png_ptr
                         , reinterpret_cast< png_bytep >( row_buffer.data() )
                         );
        }
        
        png_write_end(_png_ptr,_info_ptr);
    }

    void init_io( png_structp png_ptr )
    {
        png_set_write_fn(png_ptr, 
                static_cast<void*>(&this->_io_dev), 
                static_cast<png_rw_ptr>(&png_io_base<Device>::write_data),
                static_cast<png_flush_ptr>(&png_io_base<Device>::flush)
                );
    }

    png_structp _png_ptr;
    png_infop _info_ptr;
};


} // namespace detail
} // namespace gil
} // namespace boost



#endif // BOOST_GIL_EXTENSION_IO_DETAIL_PNG_IO_HPP_INCLUDED