/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2014 Artem Pavlenko
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

#ifndef MAPNIK_IMAGE_UTIL_HPP
#define MAPNIK_IMAGE_UTIL_HPP

// mapnik
#include <mapnik/config.hpp>
#include <mapnik/image.hpp>
#include <mapnik/image_any.hpp>
#include <mapnik/image_view.hpp>
#include <mapnik/image_view_any.hpp>
#include <mapnik/color.hpp>

// boost
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedef"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/optional.hpp>
#pragma GCC diagnostic pop

// stl
#include <string>
#include <exception>

namespace mapnik {

// fwd declares
class rgba_palette;

class ImageWriterException : public std::exception
{
private:
    std::string message_;
public:
    ImageWriterException(std::string const& message)
        : message_(message) {}

    ~ImageWriterException() throw() {}

    virtual const char* what() const throw()
    {
        return message_.c_str();
    }
};

template <typename T>
MAPNIK_DECL void save_to_file(T const& image,
                              std::string const& filename,
                              std::string const& type);

template <typename T>
MAPNIK_DECL void save_to_file(T const& image,
                              std::string const& filename,
                              std::string const& type,
                              rgba_palette const& palette);

// guess type from file extension
template <typename T>
MAPNIK_DECL void save_to_file(T const& image,
                              std::string const& filename);

template <typename T>
MAPNIK_DECL void save_to_file(T const& image,
                              std::string const& filename,
                              rgba_palette const& palette);

template <typename T>
MAPNIK_DECL std::string save_to_string(T const& image,
                                       std::string const& type);

template <typename T>
MAPNIK_DECL std::string save_to_string(T const& image,
                                       std::string const& type,
                                       rgba_palette const& palette);

template <typename T>
MAPNIK_DECL void save_to_stream
(
    T const& image,
    std::ostream & stream,
    std::string const& type,
    rgba_palette const& palette
);

template <typename T>
MAPNIK_DECL void save_to_stream
(
    T const& image,
    std::ostream & stream,
    std::string const& type
);

template <typename T>
MAPNIK_DECL bool premultiply_alpha(T & image);

template <typename T>
MAPNIK_DECL bool demultiply_alpha(T & image);

template <typename T>
MAPNIK_DECL void set_premultiplied_alpha(T & image, bool status);

template <typename T>
MAPNIK_DECL bool is_solid (T const& image);

template <typename T>
MAPNIK_DECL void set_alpha (T & image, float opacity);

template <typename T>
MAPNIK_DECL void set_grayscale_to_alpha (T & image);

template <typename T>
MAPNIK_DECL void set_grayscale_to_alpha (T & image, color const& c);

template <typename T>
MAPNIK_DECL void set_color_to_alpha (T & image, color const& c);

template <typename T>
MAPNIK_DECL void fill (image_any & data, T const&);

template <typename T>
MAPNIK_DECL void fill (image_rgba8 & data, T const&);

template <typename T>
MAPNIK_DECL void fill (image_gray8 & data, T const&);

template <typename T>
MAPNIK_DECL void fill (image_gray16 & data, T const&);

template <typename T>
MAPNIK_DECL void fill (image_gray32f & data, T const&);

template <typename T>
MAPNIK_DECL void set_rectangle (T & dst, T const& src, int x = 0, int y = 0);

template <typename T>
MAPNIK_DECL bool check_bounds (T const& data, std::size_t x, std::size_t y)
{
    return (x < static_cast<int>(data.width()) && y < static_cast<int>(data.height()));
}

template <typename T>
MAPNIK_DECL void composite_pixel(T & data, unsigned op, int x, int y, unsigned c, unsigned cover, double opacity );

template <typename T>
MAPNIK_DECL void set_pixel(image_rgba8 & data, std::size_t x, std::size_t y, T const& val);

template <typename T>
MAPNIK_DECL void set_pixel(image_gray8 & data, std::size_t x, std::size_t y, T const& val);

template <typename T>
MAPNIK_DECL void set_pixel(image_gray16 & data, std::size_t x, std::size_t y, T const& val);

template <typename T>
MAPNIK_DECL void set_pixel(image_gray32f & data, std::size_t x, std::size_t y, T const& val);

template <typename T1, typename T2>
MAPNIK_DECL void set_pixel(T1 & data, std::size_t x, std::size_t y, T2 const& val);

template <typename T>
MAPNIK_DECL T get_pixel(image_rgba8 const& data, std::size_t x, std::size_t y);

template <typename T>
MAPNIK_DECL T get_pixel(image_gray8 const& data, std::size_t x, std::size_t y);

template <typename T>
MAPNIK_DECL T get_pixel(image_gray16 const& data, std::size_t x, std::size_t y);

template <typename T>
MAPNIK_DECL T get_pixel(image_gray32f const& data, std::size_t x, std::size_t y);

template <typename T1, typename T2>
MAPNIK_DECL T2 get_pixel(T1 const& data, std::size_t x, std::size_t y);

MAPNIK_DECL void view_to_string (image_view_any const& view, std::ostringstream & ss);

MAPNIK_DECL image_view_any create_view (image_any const& data, unsigned x, unsigned y, unsigned w, unsigned h);

template <typename T>
MAPNIK_DECL unsigned compare(T const& im1, T const& im2, double threshold = 0, bool alpha = true);

inline bool is_png(std::string const& filename)
{
    return boost::algorithm::iends_with(filename,std::string(".png"));
}

inline bool is_jpeg(std::string const& filename)
{
    return boost::algorithm::iends_with(filename,std::string(".jpg")) ||
        boost::algorithm::iends_with(filename,std::string(".jpeg"));
}

inline bool is_tiff(std::string const& filename)
{
    return boost::algorithm::iends_with(filename,std::string(".tif")) ||
        boost::algorithm::iends_with(filename,std::string(".tiff"));
}

inline bool is_pdf(std::string const& filename)
{
    return boost::algorithm::iends_with(filename,std::string(".pdf"));
}

inline bool is_svg(std::string const& filename)
{
    return boost::algorithm::iends_with(filename,std::string(".svg"));
}

inline bool is_ps(std::string const& filename)
{
    return boost::algorithm::iends_with(filename,std::string(".ps"));
}

inline bool is_webp(std::string const& filename)
{
    return boost::algorithm::iends_with(filename,std::string(".webp"));
}

inline boost::optional<std::string> type_from_filename(std::string const& filename)

{
    using result_type = boost::optional<std::string>;
    if (is_png(filename)) return result_type("png");
    if (is_jpeg(filename)) return result_type("jpeg");
    if (is_tiff(filename)) return result_type("tiff");
    if (is_pdf(filename)) return result_type("pdf");
    if (is_svg(filename)) return result_type("svg");
    if (is_ps(filename)) return result_type("ps");
    if (is_webp(filename)) return result_type("webp");
    return result_type();
}

inline std::string guess_type( std::string const& filename )
{
    std::string::size_type idx = filename.find_last_of(".");
    if ( idx != std::string::npos ) {
        return filename.substr( idx + 1 );
    }
    return "<unknown>";
}

// add 1-px border around image - useful for debugging alignment issues
template <typename T>
void add_border(T & image)
{
    for (unsigned  x = 0; x < image.width();++x)
    {
        image(x,0) = 0xff0000ff; // red
        image(x,image.height()-1) = 0xff00ff00; //green
    }
    for (unsigned y = 0; y < image.height();++y)
    {
        image(0,y) = 0xff00ffff; //yellow
        image(image.width()-1,y) = 0xffff0000; // blue
    }
}

/*
extern template MAPNIK_DECL void save_to_file<image_rgba8>(image_rgba8 const&,
                                                      std::string const&,
                                                      std::string const&,
                                                      rgba_palette const&);

extern template MAPNIK_DECL void save_to_file<image_any>(image_any const&,
                                                      std::string const&,
                                                      std::string const&,
                                                      rgba_palette const&);

extern template MAPNIK_DECL void save_to_file<image_rgba8>(image_rgba8 const&,
                                                      std::string const&,
                                                      std::string const&);

extern template MAPNIK_DECL void save_to_file<image_any>(image_any const&,
                                                      std::string const&,
                                                      std::string const&);

extern template MAPNIK_DECL void save_to_file<image_rgba8>(image_rgba8 const&,
                                                      std::string const&,
                                                      rgba_palette const&);

extern template MAPNIK_DECL void save_to_file<image_any>(image_any const&,
                                                      std::string const&,
                                                      rgba_palette const&);

extern template MAPNIK_DECL void save_to_file<image_rgba8>(image_rgba8 const&,
                                                      std::string const&);

extern template MAPNIK_DECL void save_to_file<image_any>(image_any const&,
                                                      std::string const&);

extern template MAPNIK_DECL void save_to_file<image_view_any>(image_view_any const&,
                                                                    std::string const&,
                                                                    std::string const&,
                                                                    rgba_palette const&);

extern template MAPNIK_DECL void save_to_file<image_view_any>(image_view_any const&,
                                                                    std::string const&,
                                                                    std::string const&);

extern template MAPNIK_DECL void save_to_file<image_view_any>(image_view_any const&,
                                                                    std::string const&,
                                                                    rgba_palette const&);

extern template MAPNIK_DECL void save_to_file<image_view_any>(image_view_any const&,
                                                                    std::string const&);

extern template MAPNIK_DECL std::string save_to_string<image_rgba8>(image_rgba8 const&,
                                                               std::string const&);

extern template MAPNIK_DECL std::string save_to_string<image_rgba8>(image_rgba8 const&,
                                                               std::string const&,
                                                               rgba_palette const&);

extern template MAPNIK_DECL std::string save_to_string<image_view_rgba8> (image_view_rgba8 const&,
                                                                             std::string const&);

extern template MAPNIK_DECL std::string save_to_string<image_view_rgba8> (image_view_rgba8 const&,
                                                                             std::string const&,
                                                                             rgba_palette const&);

extern template MAPNIK_DECL std::string save_to_string<image_any>(image_any const&,
                                                               std::string const&);

extern template MAPNIK_DECL std::string save_to_string<image_any>(image_any const&,
                                                               std::string const&,
                                                               rgba_palette const&);

extern template MAPNIK_DECL std::string save_to_string<image_view_any> (image_view_any const&,
                                                                             std::string const&);

extern template MAPNIK_DECL std::string save_to_string<image_view_any> (image_view_any const&,
                                                                             std::string const&,
                                                                             rgba_palette const&);
*/
#ifdef _MSC_VER

template MAPNIK_DECL void save_to_stream<image_rgba8>(
    image_rgba8 const& image,
    std::ostream & stream,
    std::string const& type,
    rgba_palette const& palette
);

template MAPNIK_DECL void save_to_stream<image_rgba8>(
    image_rgba8 const& image,
    std::ostream & stream,
    std::string const& type
);

template MAPNIK_DECL void save_to_stream<image_view_rgba8> (
    image_view_rgba8 const& image,
    std::ostream & stream,
    std::string const& type,
    rgba_palette const& palette
);

template MAPNIK_DECL void save_to_stream<image_view_rgba8> (
    image_view_rgba8 const& image,
    std::ostream & stream,
    std::string const& type
);
#endif

}

#endif // MAPNIK_IMAGE_UTIL_HPP
