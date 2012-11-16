#include <boost/test/unit_test.hpp>

#include <boost/type_traits/is_same.hpp>

#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/toolbox/metafunctions/channel_type.hpp>
#include <boost/gil/extension/toolbox/metafunctions/get_num_bits.hpp>

using namespace boost;
using namespace gil;

BOOST_AUTO_TEST_SUITE( get_num_bits_test )

BOOST_AUTO_TEST_CASE( get_num_bits_test )
{
    typedef bit_aligned_image4_type<4, 4, 4, 4, rgb_layout_t>::type image_t;
    typedef channel_type< image_t::view_t::reference >::type channel_t;
    //int i = get_num_bits< channel_t >::value;
}

BOOST_AUTO_TEST_SUITE_END()