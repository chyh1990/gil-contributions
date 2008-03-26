/*
    Copyright 2007-2008 Christian Henning, Andreas Pokorny
    Use, modification and distribution are subject to the Boost Software License,
    Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
*/

/*************************************************************************************************/

#ifndef BOOST_GIL_EXTENSION_IO_WRITE_IMAGE_HPP_INCLUDED
#define BOOST_GIL_EXTENSION_IO_WRITE_IMAGE_HPP_INCLUDED

#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/mpl/and.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/gil/extension/io_new_2/detail/base.hpp>
#include <boost/gil/extension/io_new_2/detail/io_device.hpp>
#include <boost/gil/extension/io_new_2/detail/path_spec.hpp>
#include <boost/gil/extension/io_new_2/detail/conversion_policies.hpp>

#include <boost/gil/extension/io_new_2/detail/jpeg_io_write.hpp>
#include <boost/gil/extension/io_new_2/detail/png_io_write.hpp>
#include <boost/gil/extension/io_new_2/detail/tiff_io_write.hpp>

////////////////////////////////////////////////////////////////////////////////////////
/// \file               
/// \brief
/// \author Christian Henning and Andreas Pokorny \n
/// 
/// \date   2007-2008 \n
///
////////////////////////////////////////////////////////////////////////////////////////

namespace boost{ namespace gil {

/// \ingroup IO
template< typename Device
        , typename View
        , typename FormatTag
        >
inline
void write_view( Device&          device
               , const View&      view
               , const FormatTag& tag
               , typename enable_if< typename mpl::and_< typename detail::is_output_device< Device >::type
                                                                        , typename is_format_tag< FormatTag >::type
                                                                        , typename is_supported< typename View::value_type
                                                                                               , FormatTag
                                                                                               >::type
                                                                        >::type
                                                    >::type* ptr = 0
               )
{
    detail::writer< Device
                  , FormatTag
                  > writer( device );

    writer.apply( view );
}

template< typename Device
        , typename View
        , typename FormatTag
        >
inline
void write_view( Device&          device
               , const View&      view
               , const FormatTag& tag
               , typename enable_if< typename mpl::and_< typename detail::is_adaptable_output_device< FormatTag
                                                                                                                           , Device
                                                                                                                           >::type
                                                                              , typename is_format_tag< FormatTag >::type
                                                                              , typename is_supported< typename View::value_type
                                                                                                     , FormatTag>::type
                                                                              >::type
                                                          >::type* ptr = 0
        )
{
    typename detail::is_adaptable_output_device< Device >::device_type dev( device );

    write_view( dev
              , view );
}

template< typename String
        , typename View
        , typename FormatTag
        >
inline
void write_view( const String&    file_name
               , const View&      view
               , const FormatTag& tag
               , typename enable_if< typename mpl::and_< typename detail::is_supported_path_spec< String >::type
                                                       , typename is_format_tag< FormatTag >::type
                                                       , typename is_supported< typename View::value_type
                                                                              , FormatTag
                                                                              >::type
                                                       >::type
                                   >::type* ptrdiff_t = 0
               )
{
    detail::file_stream_device<FormatTag> device( detail::convert_to_string( file_name )
                                                , detail::file_stream_device<FormatTag>::write_tag()
                                                );

    write_view( device
               , view
               , tag
               );
}

/// \ingroup IO
template< typename Device
        , typename View
        , typename FormatTag
        > 
inline
void write_view( Device&                            device
               , const View&                        view
               , const image_write_info<FormatTag>& info
               , typename enable_if< typename mpl::and_< typename detail::is_output_device< Device >::type
                                                                        , typename is_format_tag< FormatTag >::type
                                                                        , typename is_supported< typename View::value_type
                                                                                               , FormatTag
                                                                                               >::type
                                                                        >::type
                                                    >::type* ptr = 0 
               )
{
    detail::writer< Device
                  , FormatTag
                  > writer( device );

    writer.apply( view
                , info );
}

template< typename Device
        , typename View
        , typename FormatTag
        > 
inline
void write_view( Device&                              device
               , const View&                          view
               , const image_write_info< FormatTag >& info
               , typename enable_if< typename mpl::and_< typename detail::is_adaptable_output_device< FormatTag
                                                                                                                           , Device
                                                                                                                           >::type
                                                                              , typename is_format_tag< FormatTag >::type
                                                                              , typename is_supported< typename View::value_type
                                                                                                     , FormatTag>::type
                                                                              >::type
                                                          >::type* ptr = 0 
               )
{
    typename detail::is_adaptable_output_device< Device >::device_type dev( device );

    write_view( dev
              , view
              , info
              );
}

template< typename String
        , typename View
        , typename FormatTag
        > 
inline
void write_view( const String&                        file_name
               , const View&                          view
               , const image_write_info< FormatTag >& info
               , typename enable_if< typename mpl::and_< typename detail::is_supported_path_spec< String >::type
                                                       , typename is_format_tag< FormatTag >::type
                                                       , typename is_supported< typename View::value_type
                                                                              , FormatTag
                                                                              >::type
                                                       >::type
                                   >::type* ptrdiff_t = 0
               )
{
    detail::file_stream_device< FormatTag > device( detail::convert_to_string( file_name )
                                                  , detail::file_stream_device< FormatTag >::write_tag()
                                                  );

    write_view( device
              , view
              , info
              );
}

} // namespace gil
} // namespace boost

#endif // BOOST_GIL_EXTENSION_IO_WRITE_IMAGE_HPP_INCLUDED