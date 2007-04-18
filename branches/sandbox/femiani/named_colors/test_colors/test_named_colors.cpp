

//todo use boost.Unit

#include <iostream>
#include <iomanip>
#include <boost/gil/gil_all.hpp>
#include <boost/algorithm/string.hpp>
#include "html_colors.hpp"
#include <map>
#include <string>


int main(int argc, char** argv)
{
    using namespace boost::gil;
    using namespace std;

    string colorname = "";
    map<string, int> named_colors;
    html_colors::copy_color_name_value_pairs_lc(inserter(named_colors, named_colors.begin()));

    while (colorname != "end"){
        cin >> colorname;
        boost::algorithm::to_lower(colorname);
        rgb8_pixel_t clr;
        if (named_colors.find(colorname) != named_colors.end()){
            int hcolor = named_colors[colorname];
            clr = html_colors::hex_color(named_colors[colorname]);
            cout << setw(6) << setfill('0') << setbase(16) << hcolor << setbase(10) << ": " 
                 << "("  << setw(3) << (int)at_c<0>(clr) 
                 << ","  << setw(3) << (int)at_c<1>(clr) 
                 << ","  << setw(3) << (int)at_c<2>(clr) 
                 << ")\n";
        }
        else
            cout << "no such color\n";
    };

}