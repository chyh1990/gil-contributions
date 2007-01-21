/*
  Copyright 2005-2006 Adobe Systems Incorporated
  Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
  or a copy at http://opensource.adobe.com/licenses.html)
*/

/*************************************************************************************************/

#ifndef GIL_BMP_IO_H
#define GIL_BMP_IO_H

/// \file
/// \brief  Support for reading and writing BMP files
//
/// \author Svetlozar Fotev, Motorola Inc.
/// \author Christian Henning
///         
/// \date   2005-2006 \n Last updated January 21, 2007

#include <cstdio>
#include <algorithm>
#include <string>
#include <boost/static_assert.hpp>
#include <boost/shared_ptr.hpp>
#include "io_error.hpp"
#include "bmp_io_private.hpp"

ADOBE_GIL_NAMESPACE_BEGIN

/// Determines whether the given view type is supported for reading

/// \brief Determines whether the given view type is supported for reading
/// \ingroup BMP_IO
template <typename VIEW> struct bmp_read_write_support {

    BOOST_STATIC_CONSTANT( bool
                         , is_supported =
                           (detail::bmp_read_write_support_private<typename VIEW::channel_t
                                                               , typename VIEW::color_space_t::base>::supported ));

    BOOST_STATIC_CONSTANT( unsigned int
                         , bit_depth =
                           ( detail::bmp_read_write_support_private<typename VIEW::channel_t
                                                                 , typename VIEW::color_space_t::base>::channel ));

    BOOST_STATIC_CONSTANT( unsigned int
                         , bit_pixel =
                           ( detail::bmp_read_write_support_private< typename VIEW::channel_t
                                                                   , typename VIEW::color_space_t::base>::pixel ));

    BOOST_STATIC_CONSTANT(bool, value=is_supported);
};

/// \brief Returns the width and height of the BMP file at the specified location.
/// Throws std::ios_base::failure if the location does not correspond to a valid BMP file
/// \ingroup BMP_IO
inline point2<int> bmp_read_dimensions(const char* filename) {
    detail::bmp_reader m(filename);
    return m.get_dimensions();
}

/// \brief Returns the width and height of the BMP file at the specified location.
/// Throws std::ios_base::failure if the location does not correspond to a valid BMP file
/// \ingroup BMP_IO
inline point2<int> bmp_read_dimensions(const std::string& filename) {
    return bmp_read_dimensions(filename.c_str());
}

/// \brief Loads the image specified by the given bmp image file name into the given view.
/// \ingroup BMP_IO
/// Triggers a compile assert if the view color space and channel depth are not supported by the BMP library or by the I/O extension.
/// Throws std::ios_base::failure if the file is not a valid BMP file, or if its color space or channel depth are not 
/// compatible with the ones specified by VIEW, or if its dimensions don't match the ones of the view.
template <typename VIEW>
inline void bmp_read_view(const char* filename,const VIEW& view) {
    BOOST_STATIC_ASSERT(bmp_read_write_support<VIEW>::is_supported);

    detail::bmp_reader m(filename);
    m.apply(view);
}

/// \brief Loads the image specified by the given bmp image file name into the given view.
/// \ingroup BMP_IO
template <typename VIEW>
inline void bmp_read_view(const std::string& filename,const VIEW& view) {
    bmp_read_view(filename.c_str(),view);
}

/// \brief Allocates a new image whose dimensions are determined by the given bmp image file, and loads the pixels into it.
/// \ingroup BMP_IO
/// Triggers a compile assert if the image color space or channel depth are not supported by the BMP library or by the I/O extension.
/// Throws std::ios_base::failure if the file is not a valid BMP file, or if its color space or channel depth are not 
/// compatible with the ones specified by IMAGE
template <typename IMAGE>
inline void bmp_read_image(const char* filename,IMAGE& im) {
   BOOST_STATIC_ASSERT(bmp_read_write_support<VIEW>::is_supported);

    detail::bmp_reader m(filename);
    m.read_image(im);
}

/// \brief Allocates a new image whose dimensions are determined by the given bmp image file, and loads the pixels into it.
/// \ingroup BMP_IO
template <typename IMAGE>
inline void bmp_read_image(const std::string& filename,IMAGE& im) {
    bmp_read_image(filename.c_str(),im);
}

/// \brief Loads and color-converts the image specified by the given bmp image file name into the given view.
/// \ingroup BMP_IO
/// Throws std::ios_base::failure if the file is not a valid BMP file, or if its dimensions don't match the ones of the view.
template <typename VIEW>
inline void bmp_read_and_convert_view(const char* filename,const VIEW& view) {
    detail::bmp_reader_color_convert m(filename);
    m.apply(view);
}

/// \brief Loads and color-converts the image specified by the given bmp image file name into the given view.
/// \ingroup BMP_IO
template <typename VIEW>
inline void bmp_read_and_convert_view(const std::string& filename,const VIEW& view) {
    bmp_read_and_convert_view(filename.c_str(),view);
}

/// \brief Allocates a new image whose dimensions are determined by the given bmp image file, loads and color-converts the pixels into it.
/// \ingroup BMP_IO
/// Throws std::ios_base::failure if the file is not a valid BMP file
template <typename IMAGE>
inline void bmp_read_and_convert_image(const char* filename,IMAGE& im) {
    detail::bmp_reader_color_convert m(filename);
    m.read_image(im);
}

/// \brief Allocates a new image whose dimensions are determined by the given bmp image file, loads and color-converts the pixels into it.
/// \ingroup BMP_IO
template <typename IMAGE>
inline void bmp_read_and_convert_image(const std::string& filename,IMAGE& im) {
    bmp_read_and_convert_image(filename.c_str(),im);
}

/// \brief Saves the view to a bmp file specified by the given bmp image file name.
/// \ingroup bmp_IO
/// Triggers a compile assert if the view color space and channel depth are not supported by the bmp library or by the I/O extension.
/// Throws std::ios_base::failure if it fails to create the file.
template <typename VIEW>
inline void bmp_write_view(const char* filename,const VIEW& view ) {
    BOOST_STATIC_ASSERT(bmp_read_write_support<VIEW>::is_supported);

    detail::bmp_writer m(filename);
    m.apply(view);
}

/// \brief Saves the view to a bmp file specified by the given bmp image file name.
/// \ingroup bmp_IO
template <typename VIEW>
inline void bmp_write_view(const std::string& filename,const VIEW& view ) {
    bmp_write_view(filename.c_str(),view);
}

ADOBE_GIL_NAMESPACE_END

#endif
