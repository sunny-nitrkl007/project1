#pragma once

#ifndef BASE64_BASE64_HPP
#define BASE64_BASE64_HPP

#include <string>
#include <iterator>
#include <type_traits>
#include <stdexcept>

#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/remove_whitespace.hpp>


namespace tes_common_ais {

    namespace {
        unsigned char count_trailing_equals(const std::string& str) {
            unsigned char count = 0;
            for (auto it = str.crbegin(); it != str.crend(); ++it) {
                if (*it == '=') {
                    ++count;
                }
                else if (std::isspace(*it)) {
                    continue;
                }
                else {
                    break;
                }
            }
            return count;
        }
    }

    template<class R> inline
    R base_64_decode(const std::string& encoded) {
        typedef std::string::const_iterator it1_;
        typedef boost::archive::iterators::binary_from_base64<it1_> it2_;
        typedef boost::archive::iterators::transform_width<it2_, 8, 6> it3_;
        unsigned char eqs = count_trailing_equals(encoded);
        R ans;
        if (eqs > 2) {
            throw std::invalid_argument("Cannot have > 2 trailing padding characters '='.");
        }
        else {
            // throws boost::archive::iterators::dataflow_exception
            ans = R(it3_(encoded.cbegin()), it3_(encoded.cend()));

            if (eqs > 0) {
                ans.resize(ans.size() - eqs);
            }
        }

        return ans;
    }

    template<class R> inline
    R base_64_decode_remove_whitespace(const std::string& encoded) {
        typedef std::string::const_iterator it1_;
        typedef boost::archive::iterators::remove_whitespace<it1_> it2_;
        typedef boost::archive::iterators::binary_from_base64<it2_> it3_;
        typedef boost::archive::iterators::transform_width<it3_, 8, 6> it4_;
        unsigned char eqs = count_trailing_equals(encoded);
        R ans;
        if (eqs > 2) {
            throw std::invalid_argument("Cannot have > 2 trailing padding characters '='.");
        }
        else {
            // Find first non-whitespace character from the end
            auto pred = [](unsigned char c) { return std::isspace(c); };
            auto found = std::find_if_not(encoded.crbegin(), encoded.crend(), pred);
            auto d = std::distance(found, encoded.crend());
            if (0 == d) {
                // No non-whitespace characters found
                ans = R();
            }
            else {
                auto end = encoded.cend() - (encoded.size() - d);

                // throws boost::archive::iterators::dataflow_exception
                ans = R(it4_(encoded.cbegin()), it4_(end));

                if (eqs > 0) {
                    ans.resize(ans.size() - eqs);
                }
            }
        }

        return ans;
    }

    template<int LineLength = 0> inline
    typename std::enable_if<(LineLength == 0), std::string>::type base_64_encode(const std::vector<unsigned char>& raw) {
        typedef std::vector<unsigned char>::const_iterator it1_;
        typedef boost::archive::iterators::transform_width<it1_, 6, 8> it2_;
        typedef boost::archive::iterators::base64_from_binary<it2_> it3_;

        // throws boost::archive::iterators::dataflow_exception
        std::string ans = std::string(it3_(raw.cbegin()), it3_(raw.cend()));

        // Add padding
        auto r = raw.size() % 3; // either 0, 1, or 2
        if (r > 0) {
            ans.append(3 - r, '=');
        }

        return ans;
    }

    template<int LineLength = 0> inline
    typename std::enable_if<(LineLength > 0), std::string>::type base_64_encode(const std::vector<unsigned char>& raw) {
        typedef boost::archive::iterators::insert_linebreaks<std::string::const_iterator, LineLength> it_;
        std::string ans = base_64_encode<0>(raw);

        // Insert linebreaks
        // throws boost::archive::iterators::dataflow_exception
        ans = std::string(it_(ans.cbegin()), it_(ans.cend()));

        return ans;
    }

}

#endif
