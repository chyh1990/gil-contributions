/*
    Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
    Use, modification and distribution are subject to the Boost Software License,
    Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
*/

/*************************************************************************************************/

#ifndef BOOST_GIL_EXTENSION_IO_READ_AND_CONVERT_IMAGE_HPP
#define BOOST_GIL_EXTENSION_IO_READ_AND_CONVERT_IMAGE_HPP

////////////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief
/// \author Christian Henning, Andreas Pokorny, Lubomir Bourdev \n
///
/// \date   2007-2012 \n
///
////////////////////////////////////////////////////////////////////////////////////////

#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/mpl/and.hpp>
#include <boost/utility/enable_if.hpp>

#include "base.hpp"
#include "io_device.hpp"
#include "path_spec.hpp"
#include "conversion_policies.hpp"

namespace boost{ namespace gil {

/// \ingroup IO

/// \brief Reads and color-converts an image. Image memory is allocated.
/// \param reader    An image reader.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \param cc        Color converter function object.
/// \throw std::ios_base::failure
template< typename Reader
        , typename Image
        >
inline
void read_and_convert_image( Reader&                                 reader
                           , Image&                                  img
                           , typename enable_if< mpl::and_< detail::is_reader< Reader >
                                                          , is_format_tag< typename Reader::format_tag_t >
                                                          >
                           >::type* /* ptr */ = 0
                           )
{
    reader.init_image( img
                     , reader._settings
                     );

    reader.apply( view( img ));
}

/// \brief Reads and color-converts an image. Image memory is allocated.
/// \param file      It's a device. Must satisfy is_input_device metafunction.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \param cc        Color converter function object.
/// \throw std::ios_base::failure
template< typename Device
        , typename Image
        , typename ColorConverter
        , typename FormatTag
        >
inline
void read_and_convert_image( Device&                                 file
                           , Image&                                  img
                           , const image_read_settings< FormatTag >& settings
                           , const ColorConverter&                   cc
                           , typename enable_if< mpl::and_< detail::is_read_device< FormatTag
                                                                                  , Device
                                                                                  >
                                                          , is_format_tag< FormatTag >
                                                          >
                                                >::type* /* ptr */ = 0
                           )
{
    read_and_convert_image( make_reader( file
                                       , settings
                                       , detail::read_and_convert< ColorConverter >( cc )
                                       )
                          , img
                          );
}

/// \brief Reads and color-converts an image. Image memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \param cc        Color converter function object.
/// \throw std::ios_base::failure
template < typename String
         , typename Image
         , typename ColorConverter
         , typename FormatTag
         >
inline
void read_and_convert_image( const String&                           file_name
                           , Image&                                  img
                           , const image_read_settings< FormatTag >& settings
                           , const ColorConverter&                   cc
                           , typename enable_if< mpl::and_< is_format_tag< FormatTag >
                                                          , detail::is_supported_path_spec< String >
                                                          >
                                               >::type* /* ptr */ = 0
                           )
{
    read_and_convert_image( make_reader( file_name
                                       , settings
                                       , detail::read_and_convert< ColorConverter >( cc )
                                       )
                          , img
                          );
}

/// \brief Reads and color-converts an image. Image memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into.
/// \param cc        Color converter function object.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template < typename String
         , typename Image
         , typename ColorConverter
         , typename FormatTag
         >
inline
void read_and_convert_image( const String&         file_name
                           , Image&                img
                           , const ColorConverter& cc
                           , const FormatTag&      tag
                           , typename enable_if< mpl::and_< is_format_tag< FormatTag >
                                                          , detail::is_supported_path_spec< String >
                                                          >
                                               >::type* /* ptr */ = 0
                           )
{
    read_and_convert_image( make_reader( file_name
                                       , tag
                                       , detail::read_and_convert< ColorConverter >( cc )
                                       )
                          , img
                          );
}

/// \brief Reads and color-converts an image. Image memory is allocated.
/// \param file It's a device. Must satisfy is_input_device metafunction or is_adaptable_input_device.
/// \param img  The image in which the data is read into.
/// \param cc   Color converter function object.
/// \param tag  Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template < typename Device
         , typename Image
         , typename ColorConverter
         , typename FormatTag
         >
inline
void read_and_convert_image( Device&               device
                           , Image&                img
                           , const ColorConverter& cc
                           , const FormatTag&      tag
                           , typename enable_if< mpl::and_< detail::is_read_device< FormatTag
                                                                                  , Device
                                                                                  >
                                                          , is_format_tag< FormatTag >
                                                          >
                                               >::type* /* ptr */ = 0
                           )
{
    read_and_convert_image( make_reader( device
                                       , tag
                                       , detail::read_and_convert< ColorConverter >( cc )
                                       )
                          , img
                          );
}

/// \brief Reads and color-converts an image. Image memory is allocated. Default color converter is used.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template < typename String
         , typename Image
         , typename FormatTag
         >
inline
void read_and_convert_image( const String&                           file_name
                           , Image&                                  img
                           , const image_read_settings< FormatTag >& settings
                           , typename enable_if< mpl::and_< is_format_tag< FormatTag >
                                                          , detail::is_supported_path_spec< String >
                                                          >
                                               >::type* /* ptr */ = 0
                           )
{
    read_and_convert_image( make_reader( file_name
                                       , settings
                                       , detail::read_and_convert< default_color_converter >()
                                       )
                          , img
                          );
}

/// \brief Reads and color-converts an image. Image memory is allocated. Default color converter is used.
/// \param file      It's a device. Must satisfy is_input_device metafunction or is_adaptable_input_device.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template < typename Device
         , typename Image
         , typename FormatTag
         >
inline
void read_and_convert_image( Device&                                 device
                           , Image&                                  img
                           , const image_read_settings< FormatTag >& settings
                           , typename enable_if< mpl::and_< detail::is_read_device< FormatTag
                                                                                  , Device
                                                                                  >
                                                          , is_format_tag< FormatTag >
                                                          >
                                               >::type* /* ptr */ = 0
                           )
{
    read_and_convert_image( make_reader( device
                                       , settings
                                       , detail::read_and_convert< default_color_converter >()
                                       )
                          , img
                          );
}

/// \brief Reads and color-converts an image. Image memory is allocated. Default color converter is used.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template < typename String
         , typename Image
         , typename FormatTag
         >
inline
void read_and_convert_image( const String&    file_name
                           , Image&           img
                           , const FormatTag& tag
                           , typename enable_if< mpl::and_< is_format_tag< FormatTag >
                                                          , detail::is_supported_path_spec< String >
                                                          >
                                               >::type* /* ptr */ = 0
                           )
{
    read_and_convert_image( make_reader( file_name
                                       , tag
                                       , detail::read_and_convert< default_color_converter >()
                                       )
                          , img
                          );
}

/// \brief Reads and color-converts an image. Image memory is allocated. Default color converter is used.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template < typename Device
         , typename Image
         , typename FormatTag
         >
inline
void read_and_convert_image( Device&          device
                           , Image&           img
                           , const FormatTag& tag
                           , typename enable_if< mpl::and_< detail::is_read_device< FormatTag
                                                                                  , Device
                                                                                  >
                                                          , is_format_tag< FormatTag >
                                                          >
                                               >::type* /* ptr */ = 0
                           )
{
    read_and_convert_image( make_reader( device
                                       , tag
                                       , detail::read_and_convert< default_color_converter >()
                                       )
                          , img
                          );
}

} // namespace gil
} // namespace boost

#endif // BOOST_GIL_EXTENSION_IO_READ_AND_CONVERT_IMAGE_HPP
