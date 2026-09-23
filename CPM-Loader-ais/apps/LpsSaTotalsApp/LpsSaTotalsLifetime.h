#ifndef LPSSATOTALSLIFETIME_H
#define LPSSATOTALSLIFETIME_H

#include <cstdint>
#include <string>
#include <iostream>
#include <array>

#include <boost/filesystem.hpp>
#include <boost/serialization/version.hpp>
#include <boost/array.hpp>
#include <boost/serialization/array.hpp>

/*
 * Lifetime Totals Storage
 */
struct LpsSaTotalsLifetimeStorage {
public:
    struct Total {
    public:
        uint32_t loadCount;
        uint32_t passCount;
        double weightTonnes;

        inline void reset() {
            loadCount = 0;
            passCount = 0;
            weightTonnes = 0.0;
        }

        inline void update(uint32_t numLoads, uint32_t numPasses, float weight) {
            loadCount += numLoads;
            passCount += numPasses;
            weightTonnes += weight;
        }

    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & loadCount;
            ar & passCount;
            ar & weightTonnes;
        }
    };

    Total lifetime;
    std::array<Total, 2> tripSnapshots;

    inline void reset() {
        lifetime.reset();
        resetTrips();
    }

    inline void resetTrips() {
        resetTripA();
        resetTripB();
    }

    inline void resetTripA() {
        tripSnapshots[0] = lifetime;
    }

    inline void resetTripB() {
        tripSnapshots[1] = lifetime;
    }

    inline void update(uint32_t numLoads, uint32_t numPasses, float weight) {
        lifetime.update(numLoads, numPasses, weight);
    }

    inline void setLifetimeWeight(double weightTonnes) {
        lifetime.weightTonnes = weightTonnes;
        resetTrips();
    }

    inline void setLifetimePassCount(uint32_t passCount) {
        lifetime.passCount = passCount;
        resetTrips();
    }

    inline void setLifetimeLoadCount(uint32_t loadCount) {
        lifetime.loadCount = loadCount;
        resetTrips();
    }

    bool load(const boost::filesystem::path& filePath);
    bool save(const boost::filesystem::path& filePath);

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & lifetime;
        ar & tripSnapshots;
    }

    friend std::ostream& operator<<(std::ostream& os, const LpsSaTotalsLifetimeStorage& o);
};

BOOST_CLASS_VERSION(LpsSaTotalsLifetimeStorage, 0);

#endif
