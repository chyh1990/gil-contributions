#ifndef HTML_COLORS_HPP
#define HTML_COLORS_HPP

#include <utility>
#include <map>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>


namespace html_colors{
    using boost::uint32_t;
    using std::make_pair;

    inline uint32_t AliceBlue() {return 0xF0F8FF;}   
    inline uint32_t AntiqueWhite() {return 0xFAEBD7;}   
    inline uint32_t Aqua() {return 0x00FFFF;}   
    inline uint32_t Aquamarine() {return 0x7FFFD4;}   
    inline uint32_t Azure() {return 0xF0FFFF;}   
    inline uint32_t Beige() {return 0xF5F5DC;}   
    inline uint32_t Bisque() {return 0xFFE4C4;}   
    inline uint32_t Black() {return 0x000000;}   
    inline uint32_t BlanchedAlmond() {return 0xFFEBCD;}   
    inline uint32_t Blue() {return 0x0000FF;}   
    inline uint32_t BlueViolet() {return 0x8A2BE2;}   
    inline uint32_t Brown() {return 0xA52A2A;}   
    inline uint32_t BurlyWood() {return 0xDEB887;}   
    inline uint32_t CadetBlue() {return 0x5F9EA0;}   
    inline uint32_t Chartreuse() {return 0x7FFF00;}   
    inline uint32_t Chocolate() {return 0xD2691E;}   
    inline uint32_t Coral() {return 0xFF7F50;}   
    inline uint32_t CornflowerBlue() {return 0x6495ED;}   
    inline uint32_t Cornsilk() {return 0xFFF8DC;}   
    inline uint32_t Crimson() {return 0xDC143C;}   
    inline uint32_t Cyan() {return 0x00FFFF;}   
    inline uint32_t DarkBlue() {return 0x00008B;}   
    inline uint32_t DarkCyan() {return 0x008B8B;}   
    inline uint32_t DarkGoldenRod() {return 0xB8860B;}   
    inline uint32_t DarkGray() {return 0xA9A9A9;}   
    inline uint32_t DarkGrey() {return 0xA9A9A9;}   
    inline uint32_t DarkGreen() {return 0x006400;}   
    inline uint32_t DarkKhaki() {return 0xBDB76B;}   
    inline uint32_t DarkMagenta() {return 0x8B008B;}   
    inline uint32_t DarkOliveGreen() {return 0x556B2F;}   
    inline uint32_t Darkorange() {return 0xFF8C00;}   
    inline uint32_t DarkOrchid() {return 0x9932CC;}   
    inline uint32_t DarkRed() {return 0x8B0000;}   
    inline uint32_t DarkSalmon() {return 0xE9967A;}   
    inline uint32_t DarkSeaGreen() {return 0x8FBC8F;}   
    inline uint32_t DarkSlateBlue() {return 0x483D8B;}   
    inline uint32_t DarkSlateGray() {return 0x2F4F4F;}   
    inline uint32_t DarkSlateGrey() {return 0x2F4F4F;}   
    inline uint32_t DarkTurquoise() {return 0x00CED1;}   
    inline uint32_t DarkViolet() {return 0x9400D3;}   
    inline uint32_t DeepPink() {return 0xFF1493;}   
    inline uint32_t DeepSkyBlue() {return 0x00BFFF;}   
    inline uint32_t DimGray() {return 0x696969;}   
    inline uint32_t DimGrey() {return 0x696969;}   
    inline uint32_t DodgerBlue() {return 0x1E90FF;}   
    inline uint32_t FireBrick() {return 0xB22222;}   
    inline uint32_t FloralWhite() {return 0xFFFAF0;}   
    inline uint32_t ForestGreen() {return 0x228B22;}   
    inline uint32_t Fuchsia() {return 0xFF00FF;}   
    inline uint32_t Gainsboro() {return 0xDCDCDC;}   
    inline uint32_t GhostWhite() {return 0xF8F8FF;}   
    inline uint32_t Gold() {return 0xFFD700;}   
    inline uint32_t GoldenRod() {return 0xDAA520;}   
    inline uint32_t Gray() {return 0x808080;}   
    inline uint32_t Grey() {return 0x808080;}   
    inline uint32_t Green() {return 0x008000;}   
    inline uint32_t GreenYellow() {return 0xADFF2F;}   
    inline uint32_t HoneyDew() {return 0xF0FFF0;}   
    inline uint32_t HotPink() {return 0xFF69B4;}   
    inline uint32_t IndianRed() {return 0xCD5C5C;}   
    inline uint32_t Indigo() {return 0x4B0082;}   
    inline uint32_t Ivory() {return 0xFFFFF0;}   
    inline uint32_t Khaki() {return 0xF0E68C;}   
    inline uint32_t Lavender() {return 0xE6E6FA;}   
    inline uint32_t LavenderBlush() {return 0xFFF0F5;}   
    inline uint32_t LawnGreen() {return 0x7CFC00;}   
    inline uint32_t LemonChiffon() {return 0xFFFACD;}   
    inline uint32_t LightBlue() {return 0xADD8E6;}   
    inline uint32_t LightCoral() {return 0xF08080;}   
    inline uint32_t LightCyan() {return 0xE0FFFF;}   
    inline uint32_t LightGoldenRodYellow() {return 0xFAFAD2;}   
    inline uint32_t LightGray() {return 0xD3D3D3;}   
    inline uint32_t LightGrey() {return 0xD3D3D3;}   
    inline uint32_t LightGreen() {return 0x90EE90;}   
    inline uint32_t LightPink() {return 0xFFB6C1;}   
    inline uint32_t LightSalmon() {return 0xFFA07A;}   
    inline uint32_t LightSeaGreen() {return 0x20B2AA;}   
    inline uint32_t LightSkyBlue() {return 0x87CEFA;}   
    inline uint32_t LightSlateGray() {return 0x778899;}   
    inline uint32_t LightSlateGrey() {return 0x778899;}   
    inline uint32_t LightSteelBlue() {return 0xB0C4DE;}   
    inline uint32_t LightYellow() {return 0xFFFFE0;}   
    inline uint32_t Lime() {return 0x00FF00;}   
    inline uint32_t LimeGreen() {return 0x32CD32;}   
    inline uint32_t Linen() {return 0xFAF0E6;}   
    inline uint32_t Magenta() {return 0xFF00FF;}   
    inline uint32_t Maroon() {return 0x800000;}   
    inline uint32_t MediumAquaMarine() {return 0x66CDAA;}   
    inline uint32_t MediumBlue() {return 0x0000CD;}   
    inline uint32_t MediumOrchid() {return 0xBA55D3;}   
    inline uint32_t MediumPurple() {return 0x9370D8;}   
    inline uint32_t MediumSeaGreen() {return 0x3CB371;}   
    inline uint32_t MediumSlateBlue() {return 0x7B68EE;}   
    inline uint32_t MediumSpringGreen() {return 0x00FA9A;}   
    inline uint32_t MediumTurquoise() {return 0x48D1CC;}   
    inline uint32_t MediumVioletRed() {return 0xC71585;}   
    inline uint32_t MidnightBlue() {return 0x191970;}   
    inline uint32_t MintCream() {return 0xF5FFFA;}   
    inline uint32_t MistyRose() {return 0xFFE4E1;}   
    inline uint32_t Moccasin() {return 0xFFE4B5;}   
    inline uint32_t NavajoWhite() {return 0xFFDEAD;}   
    inline uint32_t Navy() {return 0x000080;}   
    inline uint32_t OldLace() {return 0xFDF5E6;}   
    inline uint32_t Olive() {return 0x808000;}   
    inline uint32_t OliveDrab() {return 0x6B8E23;}   
    inline uint32_t Orange() {return 0xFFA500;}   
    inline uint32_t OrangeRed() {return 0xFF4500;}   
    inline uint32_t Orchid() {return 0xDA70D6;}   
    inline uint32_t PaleGoldenRod() {return 0xEEE8AA;}   
    inline uint32_t PaleGreen() {return 0x98FB98;}   
    inline uint32_t PaleTurquoise() {return 0xAFEEEE;}   
    inline uint32_t PaleVioletRed() {return 0xD87093;}   
    inline uint32_t PapayaWhip() {return 0xFFEFD5;}   
    inline uint32_t PeachPuff() {return 0xFFDAB9;}   
    inline uint32_t Peru() {return 0xCD853F;}   
    inline uint32_t Pink() {return 0xFFC0CB;}   
    inline uint32_t Plum() {return 0xDDA0DD;}   
    inline uint32_t PowderBlue() {return 0xB0E0E6;}   
    inline uint32_t Purple() {return 0x800080;}   
    inline uint32_t Red() {return 0xFF0000;}   
    inline uint32_t RosyBrown() {return 0xBC8F8F;}   
    inline uint32_t RoyalBlue() {return 0x4169E1;}   
    inline uint32_t SaddleBrown() {return 0x8B4513;}   
    inline uint32_t Salmon() {return 0xFA8072;}   
    inline uint32_t SandyBrown() {return 0xF4A460;}   
    inline uint32_t SeaGreen() {return 0x2E8B57;}   
    inline uint32_t SeaShell() {return 0xFFF5EE;}   
    inline uint32_t Sienna() {return 0xA0522D;}   
    inline uint32_t Silver() {return 0xC0C0C0;}   
    inline uint32_t SkyBlue() {return 0x87CEEB;}   
    inline uint32_t SlateBlue() {return 0x6A5ACD;}   
    inline uint32_t SlateGray() {return 0x708090;}   
    inline uint32_t SlateGrey() {return 0x708090;}   
    inline uint32_t Snow() {return 0xFFFAFA;}   
    inline uint32_t SpringGreen() {return 0x00FF7F;}   
    inline uint32_t SteelBlue() {return 0x4682B4;}   
    inline uint32_t Tan() {return 0xD2B48C;}   
    inline uint32_t Teal() {return 0x008080;}   
    inline uint32_t Thistle() {return 0xD8BFD8;}   
    inline uint32_t Tomato() {return 0xFF6347;}   
    inline uint32_t Turquoise() {return 0x40E0D0;}   
    inline uint32_t Violet() {return 0xEE82EE;}   
    inline uint32_t Wheat() {return 0xF5DEB3;}   
    inline uint32_t White() {return 0xFFFFFF;}   
    inline uint32_t WhiteSmoke() {return 0xF5F5F5;}   
    inline uint32_t Yellow() {return 0xFFFF00;}   
    inline uint32_t YellowGreen() {return 0x9ACD32;} 

    using boost::gil::rgb8_pixel_t;
    using boost::gil::bits8;

    rgb8_pixel_t hex_color(uint32_t clr) {
        return rgb8_pixel_t(
            static_cast<bits8>((clr & 0xFF0000) >> 16), 
            static_cast<bits8>((clr & 0x00FF00) >> 8), 
            static_cast<bits8>( clr & 0x0000FF) 
            );
    } 


    template<class It>
    inline void copy_color_name_value_pairs(It i) {
        *i++ = make_pair("AliceBlue", 0xF0F8FF);   
        *i++ = make_pair("AntiqueWhite", 0xFAEBD7);   
        *i++ = make_pair("Aqua", 0x00FFFF);   
        *i++ = make_pair("Aquamarine", 0x7FFFD4);   
        *i++ = make_pair("Azure", 0xF0FFFF);   
        *i++ = make_pair("Beige", 0xF5F5DC);   
        *i++ = make_pair("Bisque", 0xFFE4C4);   
        *i++ = make_pair("Black", 0x000000);   
        *i++ = make_pair("BlanchedAlmond", 0xFFEBCD);   
        *i++ = make_pair("Blue", 0x0000FF);   
        *i++ = make_pair("BlueViolet", 0x8A2BE2);   
        *i++ = make_pair("Brown", 0xA52A2A);   
        *i++ = make_pair("BurlyWood", 0xDEB887);   
        *i++ = make_pair("CadetBlue", 0x5F9EA0);   
        *i++ = make_pair("Chartreuse", 0x7FFF00);   
        *i++ = make_pair("Chocolate", 0xD2691E);   
        *i++ = make_pair("Coral", 0xFF7F50);   
        *i++ = make_pair("CornflowerBlue", 0x6495ED);   
        *i++ = make_pair("Cornsilk", 0xFFF8DC);   
        *i++ = make_pair("Crimson", 0xDC143C);   
        *i++ = make_pair("Cyan", 0x00FFFF);   
        *i++ = make_pair("DarkBlue", 0x00008B);   
        *i++ = make_pair("DarkCyan", 0x008B8B);   
        *i++ = make_pair("DarkGoldenRod", 0xB8860B);   
        *i++ = make_pair("DarkGray", 0xA9A9A9);   
        *i++ = make_pair("DarkGrey", 0xA9A9A9);   
        *i++ = make_pair("DarkGreen", 0x006400);   
        *i++ = make_pair("DarkKhaki", 0xBDB76B);   
        *i++ = make_pair("DarkMagenta", 0x8B008B);   
        *i++ = make_pair("DarkOliveGreen", 0x556B2F);   
        *i++ = make_pair("Darkorange", 0xFF8C00);   
        *i++ = make_pair("DarkOrchid", 0x9932CC);   
        *i++ = make_pair("DarkRed", 0x8B0000);   
        *i++ = make_pair("DarkSalmon", 0xE9967A);   
        *i++ = make_pair("DarkSeaGreen", 0x8FBC8F);   
        *i++ = make_pair("DarkSlateBlue", 0x483D8B);   
        *i++ = make_pair("DarkSlateGray", 0x2F4F4F);   
        *i++ = make_pair("DarkSlateGrey", 0x2F4F4F);   
        *i++ = make_pair("DarkTurquoise", 0x00CED1);   
        *i++ = make_pair("DarkViolet", 0x9400D3);   
        *i++ = make_pair("DeepPink", 0xFF1493);   
        *i++ = make_pair("DeepSkyBlue", 0x00BFFF);   
        *i++ = make_pair("DimGray", 0x696969);   
        *i++ = make_pair("DimGrey", 0x696969);   
        *i++ = make_pair("DodgerBlue", 0x1E90FF);   
        *i++ = make_pair("FireBrick", 0xB22222);   
        *i++ = make_pair("FloralWhite", 0xFFFAF0);   
        *i++ = make_pair("ForestGreen", 0x228B22);   
        *i++ = make_pair("Fuchsia", 0xFF00FF);   
        *i++ = make_pair("Gainsboro", 0xDCDCDC);   
        *i++ = make_pair("GhostWhite", 0xF8F8FF);   
        *i++ = make_pair("Gold", 0xFFD700);   
        *i++ = make_pair("GoldenRod", 0xDAA520);   
        *i++ = make_pair("Gray", 0x808080);   
        *i++ = make_pair("Grey", 0x808080);   
        *i++ = make_pair("Green", 0x008000);   
        *i++ = make_pair("GreenYellow", 0xADFF2F);   
        *i++ = make_pair("HoneyDew", 0xF0FFF0);   
        *i++ = make_pair("HotPink", 0xFF69B4);   
        *i++ = make_pair("IndianRed", 0xCD5C5C);   
        *i++ = make_pair("Indigo", 0x4B0082);   
        *i++ = make_pair("Ivory", 0xFFFFF0);   
        *i++ = make_pair("Khaki", 0xF0E68C);   
        *i++ = make_pair("Lavender", 0xE6E6FA);   
        *i++ = make_pair("LavenderBlush", 0xFFF0F5);   
        *i++ = make_pair("LawnGreen", 0x7CFC00);   
        *i++ = make_pair("LemonChiffon", 0xFFFACD);   
        *i++ = make_pair("LightBlue", 0xADD8E6);   
        *i++ = make_pair("LightCoral", 0xF08080);   
        *i++ = make_pair("LightCyan", 0xE0FFFF);   
        *i++ = make_pair("LightGoldenRodYellow", 0xFAFAD2);   
        *i++ = make_pair("LightGray", 0xD3D3D3);   
        *i++ = make_pair("LightGrey", 0xD3D3D3);   
        *i++ = make_pair("LightGreen", 0x90EE90);   
        *i++ = make_pair("LightPink", 0xFFB6C1);   
        *i++ = make_pair("LightSalmon", 0xFFA07A);   
        *i++ = make_pair("LightSeaGreen", 0x20B2AA);   
        *i++ = make_pair("LightSkyBlue", 0x87CEFA);   
        *i++ = make_pair("LightSlateGray", 0x778899);   
        *i++ = make_pair("LightSlateGrey", 0x778899);   
        *i++ = make_pair("LightSteelBlue", 0xB0C4DE);   
        *i++ = make_pair("LightYellow", 0xFFFFE0);   
        *i++ = make_pair("Lime", 0x00FF00);   
        *i++ = make_pair("LimeGreen", 0x32CD32);   
        *i++ = make_pair("Linen", 0xFAF0E6);   
        *i++ = make_pair("Magenta", 0xFF00FF);   
        *i++ = make_pair("Maroon", 0x800000);   
        *i++ = make_pair("MediumAquaMarine", 0x66CDAA);   
        *i++ = make_pair("MediumBlue", 0x0000CD);   
        *i++ = make_pair("MediumOrchid", 0xBA55D3);   
        *i++ = make_pair("MediumPurple", 0x9370D8);   
        *i++ = make_pair("MediumSeaGreen", 0x3CB371);   
        *i++ = make_pair("MediumSlateBlue", 0x7B68EE);   
        *i++ = make_pair("MediumSpringGreen", 0x00FA9A);   
        *i++ = make_pair("MediumTurquoise", 0x48D1CC);   
        *i++ = make_pair("MediumVioletRed", 0xC71585);   
        *i++ = make_pair("MidnightBlue", 0x191970);   
        *i++ = make_pair("MintCream", 0xF5FFFA);   
        *i++ = make_pair("MistyRose", 0xFFE4E1);   
        *i++ = make_pair("Moccasin", 0xFFE4B5);   
        *i++ = make_pair("NavajoWhite", 0xFFDEAD);   
        *i++ = make_pair("Navy", 0x000080);   
        *i++ = make_pair("OldLace", 0xFDF5E6);   
        *i++ = make_pair("Olive", 0x808000);   
        *i++ = make_pair("OliveDrab", 0x6B8E23);   
        *i++ = make_pair("Orange", 0xFFA500);   
        *i++ = make_pair("OrangeRed", 0xFF4500);   
        *i++ = make_pair("Orchid", 0xDA70D6);   
        *i++ = make_pair("PaleGoldenRod", 0xEEE8AA);   
        *i++ = make_pair("PaleGreen", 0x98FB98);   
        *i++ = make_pair("PaleTurquoise", 0xAFEEEE);   
        *i++ = make_pair("PaleVioletRed", 0xD87093);   
        *i++ = make_pair("PapayaWhip", 0xFFEFD5);   
        *i++ = make_pair("PeachPuff", 0xFFDAB9);   
        *i++ = make_pair("Peru", 0xCD853F);   
        *i++ = make_pair("Pink", 0xFFC0CB);   
        *i++ = make_pair("Plum", 0xDDA0DD);   
        *i++ = make_pair("PowderBlue", 0xB0E0E6);   
        *i++ = make_pair("Purple", 0x800080);   
        *i++ = make_pair("Red", 0xFF0000);   
        *i++ = make_pair("RosyBrown", 0xBC8F8F);   
        *i++ = make_pair("RoyalBlue", 0x4169E1);   
        *i++ = make_pair("SaddleBrown", 0x8B4513);   
        *i++ = make_pair("Salmon", 0xFA8072);   
        *i++ = make_pair("SandyBrown", 0xF4A460);   
        *i++ = make_pair("SeaGreen", 0x2E8B57);   
        *i++ = make_pair("SeaShell", 0xFFF5EE);   
        *i++ = make_pair("Sienna", 0xA0522D);   
        *i++ = make_pair("Silver", 0xC0C0C0);   
        *i++ = make_pair("SkyBlue", 0x87CEEB);   
        *i++ = make_pair("SlateBlue", 0x6A5ACD);   
        *i++ = make_pair("SlateGray", 0x708090);   
        *i++ = make_pair("SlateGrey", 0x708090);   
        *i++ = make_pair("Snow", 0xFFFAFA);   
        *i++ = make_pair("SpringGreen", 0x00FF7F);   
        *i++ = make_pair("SteelBlue", 0x4682B4);   
        *i++ = make_pair("Tan", 0xD2B48C);   
        *i++ = make_pair("Teal", 0x008080);   
        *i++ = make_pair("Thistle", 0xD8BFD8);   
        *i++ = make_pair("Tomato", 0xFF6347);   
        *i++ = make_pair("Turquoise", 0x40E0D0);   
        *i++ = make_pair("Violet", 0xEE82EE);   
        *i++ = make_pair("Wheat", 0xF5DEB3);   
        *i++ = make_pair("White", 0xFFFFFF);   
        *i++ = make_pair("WhiteSmoke", 0xF5F5F5);   
        *i++ = make_pair("Yellow", 0xFFFF00);   
        *i++ = make_pair("YellowGreen", 0x9ACD32); 
    }


    template<class It>
    inline void copy_color_name_value_pairs_lc(It i) {
        *i++ = make_pair("aliceblue", 0xf0f8ff);   
        *i++ = make_pair("antiquewhite", 0xfaebd7);   
        *i++ = make_pair("aqua", 0x00ffff);   
        *i++ = make_pair("aquamarine", 0x7fffd4);   
        *i++ = make_pair("azure", 0xf0ffff);   
        *i++ = make_pair("beige", 0xf5f5dc);   
        *i++ = make_pair("bisque", 0xffe4c4);   
        *i++ = make_pair("black", 0x000000);   
        *i++ = make_pair("blanchedalmond", 0xffebcd);   
        *i++ = make_pair("blue", 0x0000ff);   
        *i++ = make_pair("blueviolet", 0x8a2be2);   
        *i++ = make_pair("brown", 0xa52a2a);   
        *i++ = make_pair("burlywood", 0xdeb887);   
        *i++ = make_pair("cadetblue", 0x5f9ea0);   
        *i++ = make_pair("chartreuse", 0x7fff00);   
        *i++ = make_pair("chocolate", 0xd2691e);   
        *i++ = make_pair("coral", 0xff7f50);   
        *i++ = make_pair("cornflowerblue", 0x6495ed);   
        *i++ = make_pair("cornsilk", 0xfff8dc);   
        *i++ = make_pair("crimson", 0xdc143c);   
        *i++ = make_pair("cyan", 0x00ffff);   
        *i++ = make_pair("darkblue", 0x00008b);   
        *i++ = make_pair("darkcyan", 0x008b8b);   
        *i++ = make_pair("darkgoldenrod", 0xb8860b);   
        *i++ = make_pair("darkgray", 0xa9a9a9);   
        *i++ = make_pair("darkgrey", 0xa9a9a9);   
        *i++ = make_pair("darkgreen", 0x006400);   
        *i++ = make_pair("darkkhaki", 0xbdb76b);   
        *i++ = make_pair("darkmagenta", 0x8b008b);   
        *i++ = make_pair("darkolivegreen", 0x556b2f);   
        *i++ = make_pair("darkorange", 0xff8c00);   
        *i++ = make_pair("darkorchid", 0x9932cc);   
        *i++ = make_pair("darkred", 0x8b0000);   
        *i++ = make_pair("darksalmon", 0xe9967a);   
        *i++ = make_pair("darkseagreen", 0x8fbc8f);   
        *i++ = make_pair("darkslateblue", 0x483d8b);   
        *i++ = make_pair("darkslategray", 0x2f4f4f);   
        *i++ = make_pair("darkslategrey", 0x2f4f4f);   
        *i++ = make_pair("darkturquoise", 0x00ced1);   
        *i++ = make_pair("darkviolet", 0x9400d3);   
        *i++ = make_pair("deeppink", 0xff1493);   
        *i++ = make_pair("deepskyblue", 0x00bfff);   
        *i++ = make_pair("dimgray", 0x696969);   
        *i++ = make_pair("dimgrey", 0x696969);   
        *i++ = make_pair("dodgerblue", 0x1e90ff);   
        *i++ = make_pair("firebrick", 0xb22222);   
        *i++ = make_pair("floralwhite", 0xfffaf0);   
        *i++ = make_pair("forestgreen", 0x228b22);   
        *i++ = make_pair("fuchsia", 0xff00ff);   
        *i++ = make_pair("gainsboro", 0xdcdcdc);   
        *i++ = make_pair("ghostwhite", 0xf8f8ff);   
        *i++ = make_pair("gold", 0xffd700);   
        *i++ = make_pair("goldenrod", 0xdaa520);   
        *i++ = make_pair("gray", 0x808080);   
        *i++ = make_pair("grey", 0x808080);   
        *i++ = make_pair("green", 0x008000);   
        *i++ = make_pair("greenyellow", 0xadff2f);   
        *i++ = make_pair("honeydew", 0xf0fff0);   
        *i++ = make_pair("hotpink", 0xff69b4);   
        *i++ = make_pair("indianred", 0xcd5c5c);   
        *i++ = make_pair("indigo", 0x4b0082);   
        *i++ = make_pair("ivory", 0xfffff0);   
        *i++ = make_pair("khaki", 0xf0e68c);   
        *i++ = make_pair("lavender", 0xe6e6fa);   
        *i++ = make_pair("lavenderblush", 0xfff0f5);   
        *i++ = make_pair("lawngreen", 0x7cfc00);   
        *i++ = make_pair("lemonchiffon", 0xfffacd);   
        *i++ = make_pair("lightblue", 0xadd8e6);   
        *i++ = make_pair("lightcoral", 0xf08080);   
        *i++ = make_pair("lightcyan", 0xe0ffff);   
        *i++ = make_pair("lightgoldenrodyellow", 0xfafad2);   
        *i++ = make_pair("lightgray", 0xd3d3d3);   
        *i++ = make_pair("lightgrey", 0xd3d3d3);   
        *i++ = make_pair("lightgreen", 0x90ee90);   
        *i++ = make_pair("lightpink", 0xffb6c1);   
        *i++ = make_pair("lightsalmon", 0xffa07a);   
        *i++ = make_pair("lightseagreen", 0x20b2aa);   
        *i++ = make_pair("lightskyblue", 0x87cefa);   
        *i++ = make_pair("lightslategray", 0x778899);   
        *i++ = make_pair("lightslategrey", 0x778899);   
        *i++ = make_pair("lightsteelblue", 0xb0c4de);   
        *i++ = make_pair("lightyellow", 0xffffe0);   
        *i++ = make_pair("lime", 0x00ff00);   
        *i++ = make_pair("limegreen", 0x32cd32);   
        *i++ = make_pair("linen", 0xfaf0e6);   
        *i++ = make_pair("magenta", 0xff00ff);   
        *i++ = make_pair("maroon", 0x800000);   
        *i++ = make_pair("mediumaquamarine", 0x66cdaa);   
        *i++ = make_pair("mediumblue", 0x0000cd);   
        *i++ = make_pair("mediumorchid", 0xba55d3);   
        *i++ = make_pair("mediumpurple", 0x9370d8);   
        *i++ = make_pair("mediumseagreen", 0x3cb371);   
        *i++ = make_pair("mediumslateblue", 0x7b68ee);   
        *i++ = make_pair("mediumspringgreen", 0x00fa9a);   
        *i++ = make_pair("mediumturquoise", 0x48d1cc);   
        *i++ = make_pair("mediumvioletred", 0xc71585);   
        *i++ = make_pair("midnightblue", 0x191970);   
        *i++ = make_pair("mintcream", 0xf5fffa);   
        *i++ = make_pair("mistyrose", 0xffe4e1);   
        *i++ = make_pair("moccasin", 0xffe4b5);   
        *i++ = make_pair("navajowhite", 0xffdead);   
        *i++ = make_pair("navy", 0x000080);   
        *i++ = make_pair("oldlace", 0xfdf5e6);   
        *i++ = make_pair("olive", 0x808000);   
        *i++ = make_pair("olivedrab", 0x6b8e23);   
        *i++ = make_pair("orange", 0xffa500);   
        *i++ = make_pair("orangered", 0xff4500);   
        *i++ = make_pair("orchid", 0xda70d6);   
        *i++ = make_pair("palegoldenrod", 0xeee8aa);   
        *i++ = make_pair("palegreen", 0x98fb98);   
        *i++ = make_pair("paleturquoise", 0xafeeee);   
        *i++ = make_pair("palevioletred", 0xd87093);   
        *i++ = make_pair("papayawhip", 0xffefd5);   
        *i++ = make_pair("peachpuff", 0xffdab9);   
        *i++ = make_pair("peru", 0xcd853f);   
        *i++ = make_pair("pink", 0xffc0cb);   
        *i++ = make_pair("plum", 0xdda0dd);   
        *i++ = make_pair("powderblue", 0xb0e0e6);   
        *i++ = make_pair("purple", 0x800080);   
        *i++ = make_pair("red", 0xff0000);   
        *i++ = make_pair("rosybrown", 0xbc8f8f);   
        *i++ = make_pair("royalblue", 0x4169e1);   
        *i++ = make_pair("saddlebrown", 0x8b4513);   
        *i++ = make_pair("salmon", 0xfa8072);   
        *i++ = make_pair("sandybrown", 0xf4a460);   
        *i++ = make_pair("seagreen", 0x2e8b57);   
        *i++ = make_pair("seashell", 0xfff5ee);   
        *i++ = make_pair("sienna", 0xa0522d);   
        *i++ = make_pair("silver", 0xc0c0c0);   
        *i++ = make_pair("skyblue", 0x87ceeb);   
        *i++ = make_pair("slateblue", 0x6a5acd);   
        *i++ = make_pair("slategray", 0x708090);   
        *i++ = make_pair("slategrey", 0x708090);   
        *i++ = make_pair("snow", 0xfffafa);   
        *i++ = make_pair("springgreen", 0x00ff7f);   
        *i++ = make_pair("steelblue", 0x4682b4);   
        *i++ = make_pair("tan", 0xd2b48c);   
        *i++ = make_pair("teal", 0x008080);   
        *i++ = make_pair("thistle", 0xd8bfd8);   
        *i++ = make_pair("tomato", 0xff6347);   
        *i++ = make_pair("turquoise", 0x40e0d0);   
        *i++ = make_pair("violet", 0xee82ee);   
        *i++ = make_pair("wheat", 0xf5deb3);   
        *i++ = make_pair("white", 0xffffff);   
        *i++ = make_pair("whitesmoke", 0xf5f5f5);   
        *i++ = make_pair("yellow", 0xffff00);   
        *i++ = make_pair("yellowgreen", 0x9acd32); 
    }
} //html_colors

#endif //HTML_COLORS_HPP