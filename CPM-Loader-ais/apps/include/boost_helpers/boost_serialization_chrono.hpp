#ifndef BOOST_SERIALIZATION_CHRONO_HPP
#define BOOST_SERIALIZATION_CHRONO_HPP

#include <chrono>

#include <boost/serialization/split_free.hpp>

namespace boost {
    namespace serialization {

        // serialization for std::chrono::duration
        template<class Archive, class Rep, class Period>
        inline void serialize(
            Archive& ar,
            std::chrono::duration<Rep, Period>& t,
            const unsigned int file_version
        )
        {
            boost::serialization::split_free(ar, t, file_version);
        }

        template<class Archive, class Rep, class Period>
        inline void save(
            Archive& ar,
            const std::chrono::duration<Rep, Period>& t,
            const unsigned int file_version
        )
        {
            auto count = t.count();
            ar << count;
        }

        template<class Archive, class Rep, class Period>
        inline void load(
            Archive & ar,
            std::chrono::duration<Rep, Period>& t,
            const unsigned int file_version
        )
        {
            Rep rep;
            ar >> rep;
            t = std::chrono::duration<Rep, Period>(rep);
        }


        // serialization for std::chrono::time_point
        template<class Archive, class C, class D> // = typename C::duration>
        inline void serialize(
            Archive& ar,
            std::chrono::time_point<C, D>& t,
            const unsigned int file_version
        )
        {
            boost::serialization::split_free(ar, t, file_version);
        }

        template<class Archive, class C, class D> // = typename C::duration>
        inline void save(
            Archive& ar,
            const std::chrono::time_point<C, D>& t,
            const unsigned int file_version
        )
        {
            auto time_since_epoch = t.time_since_epoch();
            ar << time_since_epoch;
        }

        template<class Archive, class C, class D> // = typename C::duration>
        inline void load(
            Archive & ar,
            std::chrono::time_point<C, D>& t,
            const unsigned int file_version
        )
        {
            D dur;
            ar >> dur;
            t = std::chrono::time_point<C, D>(dur);
        }

    } // serialization
} // namespace boost

#endif // BOOST_SERIALIZATION_CHRONO_HPP
