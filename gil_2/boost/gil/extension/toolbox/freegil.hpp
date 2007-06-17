#ifndef _freegil_hpp_
#define _freegil_hpp_

// (C) Copyright Tom Brinkman 2007.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/cast.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/spirit/core.hpp>
#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "utilgil.hpp"
#include "utilstl.hpp"

namespace boost {
namespace gil {

struct make_metric
{
	template <typename glyph_t>
	FT_Glyph_Metrics operator()(glyph_t glyph)
	{
		BOOST_ASSERT(glyph->face);
		int load_flags = FT_LOAD_DEFAULT;
		int index = FT_Get_Char_Index(glyph->face,glyph->ch);
		FT_Load_Glyph(glyph->face, index, load_flags);
		return glyph->face->glyph->metrics;
	}
};

struct make_kerning
{
	int left_glyph;
	make_kerning() : left_glyph(0) {}

	template <typename glyph_t>
	int operator()(glyph_t glyph)
	{
		int right_glyph = FT_Get_Char_Index(glyph->face, glyph->ch); 
		if (!FT_HAS_KERNING(glyph->face) || !left_glyph || !right_glyph) 
			return 0;

		FT_Vector delta; 
		FT_Get_Kerning(glyph->face, left_glyph, right_glyph, FT_KERNING_DEFAULT, &delta); 
		left_glyph = right_glyph; 
		return delta.x >> 6; 
	}
};

struct make_width
{
	int advance;
	int lastwidth;
	int lastadvance;
	make_width() : advance(0), lastwidth(0), lastadvance(0) {}
	operator int(){return advance-(lastadvance-lastwidth);}
	void operator()(FT_Glyph_Metrics metrics, int kerning)
	{
		lastadvance = kerning + (metrics.horiAdvance >> 6); 
		lastwidth = (metrics.width >> 6);
		advance += lastadvance;
	}
};

struct make_advance_width
{
	int advance;
	make_advance_width() : advance(0){}
	operator int(){return advance;}
	void operator()(FT_Glyph_Metrics metrics, int kerning)
	{
		advance += kerning + (metrics.horiAdvance >> 6);
	}
};

struct make_advance_height
{
	int height;
	make_advance_height() : height(0){}
	operator int(){return height;}
	void operator()(FT_Glyph_Metrics metrics)
	{
		int advance = (metrics.vertAdvance >> 6);
		height = (std::max)(height,advance);
	}
};

struct make_height
{
	int height;
	make_height() : height(0){}
	operator int(){return height;}
	void operator()(FT_Glyph_Metrics metrics)
	{
		int h = (metrics.height >> 6);
		height = (std::max)(height,h);
	}
};

struct make_glyph_height
{
	int height;
	make_glyph_height() : height(0) {} 
	operator int(){return height;}
	void operator()(FT_Glyph_Metrics metrics)
	{
		int n = (metrics.height >> 6) -	(metrics.horiBearingY >> 6);
		height = (std::max)(height,n);
	}
};

template <typename view_t>
struct render_gray_glyph
{
	int x;
	const view_t& view;
	render_gray_glyph(const view_t& view) : view(view), x(0){}	

	template <typename glyph_t>
	void operator()(glyph_t glyph, int kerning = 0)
	{
		x += kerning;

		FT_GlyphSlot slot = glyph->face->glyph; 

		int load_flags = FT_LOAD_DEFAULT;
		int index = FT_Get_Char_Index(glyph->face,glyph->ch);
		FT_Load_Glyph(glyph->face, index, load_flags);
		FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);

		int y = view.height() - (glyph->face->glyph->metrics.horiBearingY >> 6);
		int width = glyph->face->glyph->metrics.width >> 6;
		int height = glyph->face->glyph->metrics.height >> 6;
		int xadvance = glyph->face->glyph->advance.x >> 6;

		BOOST_ASSERT(width == slot->bitmap.width);
		BOOST_ASSERT(height == slot->bitmap.rows);

		typedef boost::gil::gray8_pixel_t pixel_t;
		boost::gil::gray8c_view_t grayview = boost::gil::interleaved_view(
			width,height,(pixel_t*)slot->bitmap.buffer,
				sizeof(unsigned char)*slot->bitmap.width);
		copy_alpha_blended_pixels(glyph->color,grayview,
			boost::gil::subimage_view(view,x,y,width,height));

		x += xadvance; 
	}
};

struct find_last_fitted_glyph
{
	int width,x;
	find_last_fitted_glyph(int width) : width(width),x(0){}
	bool operator()(FT_Glyph_Metrics metric, int kerning)
	{
		x += kerning;
		int tmp = x + (metric.width >> 6);
		x += (metric.horiAdvance >> 6); 
		return tmp > width;
	}
};

} 
} 

#endif


