#ifndef XCPSERVERDB_HPP_
#define XCPSERVERDB_HPP_


#if __cplusplus >= 201103L
#include <cstdint>
#else
#include <stdint.h>
#endif

#include <iostream>
#include <exception>

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility.hpp>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/exception/all.hpp>

#include "../XCPServer.h"

// Macros that are used to push SCS data into 'db': DB_PUSH invokes db.update, DB_PUSH_ARRAY expands into a for-loop with DB_PUSH invocations
#define DB_PUSH(item) db.update(((index << 16) | offset++), (item))
#define DB_PUSH_ARRAY(array_name, num_elements)       \
  for (uint8_t iter = 0; iter < num_elements; iter++) \
  {                                                   \
    DB_PUSH(array_name[iter]);                        \
  }
// Use only if the container size is known and static
#define DB_PUSH_CONTAINER(container) \
  for (auto entry : container)       \
  {                                  \
    DB_PUSH(entry);                  \
  }

// Used with a base address instead of an index
#define DB_INCR_ADDR(addr) addr += (1 << 16)
#define DB_PUSH_ADDR(item) db.update((baseAddr | offset++), (item))
#define DB_PUSH_ADDR_ARRAY(array_name, num_elements)       \
  for (uint8_t iter = 0; iter < num_elements; iter++) \
  {                                                   \
    DB_PUSH_ADDR(array_name[iter]);                        \
  }
// Use only if the container size is known and static
#define DB_PUSH_ADDR_CONTAINER(container) \
  for (auto entry : container)       \
  {                                  \
    DB_PUSH_ADDR(entry);                  \
  }

// pack 4 bytes into a unit32_t
inline uint32_t DB_PACK_32(char c0, char c1, char c2, char c3) 
{
    return (c0 << 24) | (c1 << 16) | (c2 << 8) | c3;
}


namespace xcp_server
{
    class DbEntry
    {
        public:
            virtual ~DbEntry() {}
            virtual bool validate(uint8_t addrExt, uint16_t numBytes) const = 0;
            virtual bool write(uint8_t destAddrExt, uint8_t const *pSrc, uint16_t numBytes) = 0;
            virtual bool read(uint8_t srcAddrExt, uint8_t *pDest, uint16_t numBytes) const = 0;

            virtual void getValue(uint32_t& value) const = 0;
            virtual void getValue(uint16_t& value) const = 0;
            virtual void getValue(uint8_t& value) const = 0;
            virtual void getValue(int32_t& value) const = 0;
            virtual void getValue(int16_t& value) const = 0;
            virtual void getValue(int8_t& value) const = 0;
            virtual void getValue(bool& value) const = 0;
            virtual void getValue(float& value) const = 0;
            virtual void getValue(double& value) const = 0;

            inline uint32_t getU32Value() const { uint32_t v; getValue(v); return v; }
            inline uint16_t getU16Value() const { uint16_t v; getValue(v); return v; }
            inline uint8_t getU8Value() const { uint8_t v; getValue(v); return v; }
            inline int32_t getI32Value() const { int32_t v; getValue(v); return v; }
            inline int16_t getI16Value() const { int16_t v; getValue(v); return v; }
            inline int8_t getI8Value() const { int8_t v; getValue(v); return v; }
            inline bool getBoolValue() const { bool v; getValue(v); return v; }
            inline float getFloatValue() const { float v; getValue(v); return v; }
            inline double getDoubleValue() const { double v; getValue(v); return v; }

            virtual void setValue(uint32_t value) = 0;
            virtual void setValue(uint16_t value) = 0;
            virtual void setValue(uint8_t value) = 0;
            virtual void setValue(int32_t value) = 0;
            virtual void setValue(int16_t value) = 0;
            virtual void setValue(int8_t value) = 0;
            virtual void setValue(bool value) = 0;
            virtual void setValue(float value) = 0;
            virtual void setValue(double value) = 0;

            virtual bool isDirty() const = 0;
    };

    /*
     * Add useful operators
     */
    inline const DbEntry& operator>>(const DbEntry& dbe, uint32_t& value) { dbe.getValue(value); return dbe; }
    inline const DbEntry& operator>>(const DbEntry& dbe, uint16_t& value) { dbe.getValue(value); return dbe; }
    inline const DbEntry& operator>>(const DbEntry& dbe, uint8_t& value) { dbe.getValue(value); return dbe; }
    inline const DbEntry& operator>>(const DbEntry& dbe, int32_t& value) { dbe.getValue(value); return dbe; }
    inline const DbEntry& operator>>(const DbEntry& dbe, int16_t& value) { dbe.getValue(value); return dbe; }
    inline const DbEntry& operator>>(const DbEntry& dbe, int8_t& value) { dbe.getValue(value); return dbe; }
    inline const DbEntry& operator>>(const DbEntry& dbe, bool& value) { dbe.getValue(value); return dbe; }
    inline const DbEntry& operator>>(const DbEntry& dbe, float& value) { dbe.getValue(value); return dbe; }
    inline const DbEntry& operator>>(const DbEntry& dbe, double& value) { dbe.getValue(value); return dbe; }

    inline uint32_t& operator<<(uint32_t& value, const DbEntry& dbe) { dbe.getValue(value); return value; }
    inline uint16_t& operator<<(uint16_t& value, const DbEntry& dbe) { dbe.getValue(value); return value; }
    inline uint8_t& operator<<(uint8_t& value, const DbEntry& dbe) { dbe.getValue(value); return value; }
    inline int32_t& operator<<(int32_t& value, const DbEntry& dbe) { dbe.getValue(value); return value; }
    inline int16_t& operator<<(int16_t& value, const DbEntry& dbe) { dbe.getValue(value); return value; }
    inline int8_t& operator<<(int8_t& value, const DbEntry& dbe) { dbe.getValue(value); return value; }
    inline bool& operator<<(bool& value, const DbEntry& dbe) { dbe.getValue(value); return value; }
    inline float& operator<<(float& value, const DbEntry& dbe) { dbe.getValue(value); return value; }
    inline double& operator<<(double& value, const DbEntry& dbe) { dbe.getValue(value); return value; }

    inline uint32_t operator>>(uint32_t value, DbEntry& dbe) { dbe.setValue(value); return value; }
    inline uint16_t operator>>(uint16_t value, DbEntry& dbe) { dbe.setValue(value); return value; }
    inline uint8_t operator>>(uint8_t value, DbEntry& dbe) { dbe.setValue(value); return value; }
    inline int32_t operator>>(int32_t value, DbEntry& dbe) { dbe.setValue(value); return value; }
    inline int16_t operator>>(int16_t value, DbEntry& dbe) { dbe.setValue(value); return value; }
    inline int8_t operator>>(int8_t value, DbEntry& dbe) { dbe.setValue(value); return value; }
    inline bool operator>>(bool value, DbEntry& dbe) { dbe.setValue(value); return value; }
    inline float operator>>(float value, DbEntry& dbe) { dbe.setValue(value); return value; }
    inline double operator>>(double value, DbEntry& dbe) { dbe.setValue(value); return value; }

    inline DbEntry& operator<<(DbEntry& dbe, uint32_t value) { dbe.setValue(value); return dbe; }
    inline DbEntry& operator<<(DbEntry& dbe, uint16_t value) { dbe.setValue(value); return dbe; }
    inline DbEntry& operator<<(DbEntry& dbe, uint8_t value) { dbe.setValue(value); return dbe; }
    inline DbEntry& operator<<(DbEntry& dbe, int32_t value) { dbe.setValue(value); return dbe; }
    inline DbEntry& operator<<(DbEntry& dbe, int16_t value) { dbe.setValue(value); return dbe; }
    inline DbEntry& operator<<(DbEntry& dbe, int8_t value) { dbe.setValue(value); return dbe; }
    inline DbEntry& operator<<(DbEntry& dbe, bool value) { dbe.setValue(value); return dbe; }
    inline DbEntry& operator<<(DbEntry& dbe, float value) { dbe.setValue(value); return dbe; }
    inline DbEntry& operator<<(DbEntry& dbe, double value) { dbe.setValue(value); return dbe; }

    inline std::ostream& operator<<(std::ostream& ostr, DbEntry const & o) {
        ostr << o.getDoubleValue();  // use the biggest thing we can think of.
        return ostr;
    }

    struct NullDbEntryException : public std::exception
    {
        const char* what() const throw() /*noexcept*/ {
            return "Cannot access the value of NullDbEntry.";
        }
    };

    namespace internal_
    {
        class NullDbEntry : public DbEntry
        {
            public:
                virtual bool validate(uint8_t addrExt, uint16_t numBytes) const { return false; }
                virtual bool write(uint8_t destAddrExt, uint8_t const *pSrc, uint16_t numBytes) { return false; }
                virtual bool read(uint8_t srcAddrExt, uint8_t *pDest, uint16_t numBytes) const { return false; }

                virtual void getValue(uint32_t& value) const { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void getValue(uint16_t& value) const { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void getValue(uint8_t& value) const { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void getValue(int32_t& value) const { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void getValue(int16_t& value) const { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void getValue(int8_t& value) const { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void getValue(bool& value) const { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void getValue(float& value) const { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void getValue(double& value) const { BOOST_THROW_EXCEPTION(NullDbEntryException()); }

                virtual void setValue(uint32_t value) { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void setValue(uint16_t value) { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void setValue(uint8_t value) { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void setValue(int32_t value) { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void setValue(int16_t value) { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void setValue(int8_t value) { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void setValue(bool value) { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void setValue(float value) { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
                virtual void setValue(double value) { BOOST_THROW_EXCEPTION(NullDbEntryException()); }

                virtual bool isDirty() const { BOOST_THROW_EXCEPTION(NullDbEntryException()); }
        };
    }

    extern internal_::NullDbEntry NullDbEntry;

    template<typename T> class PrimitiveDbEntry : public DbEntry
    {
        BOOST_STATIC_ASSERT(boost::is_arithmetic<T>::value);

        public:
            PrimitiveDbEntry(): value_(static_cast<T>(0)), dirty_(false) {}

            PrimitiveDbEntry(const T& value): value_(value), dirty_(false) {}

            // Use default copy constructor

            virtual bool validate(uint8_t addrExt, uint16_t numBytes) const
            {
                if ((sizeof(T) == numBytes) ||
                    (0 == numBytes)) {
                    return true;
                }
                return false;
            }

            virtual bool write(uint8_t destAddrExt, uint8_t const *pSrc, uint16_t numBytes)
            {
                if (sizeof(T) != numBytes) {
                    return false;
                }
                memcpy(static_cast<void*>(&value_), pSrc, numBytes);
                dirty_ = true;
                return true;
            }

            virtual bool read(uint8_t srcAddrExt, uint8_t *pDest, uint16_t numBytes) const
            {
                if (sizeof(T) != numBytes) {
                    return false;
                }
                memcpy(pDest, static_cast<const void*>(&value_), numBytes);
                return true;
            }

            virtual void getValue(uint32_t& value) const { getValueAs<uint32_t>(value); }
            virtual void getValue(uint16_t& value) const { getValueAs<uint16_t>(value); }
            virtual void getValue(uint8_t& value) const { getValueAs<uint8_t>(value); }
            virtual void getValue(int32_t& value) const { getValueAs<int32_t>(value); }
            virtual void getValue(int16_t& value) const { getValueAs<int16_t>(value); }
            virtual void getValue(int8_t& value) const { getValueAs<int8_t>(value); }
            virtual void getValue(bool& value) const { getValueAs<bool>(value); }
            virtual void getValue(float& value) const { getValueAs<float>(value); }
            virtual void getValue(double& value) const { getValueAs<double>(value); }

            virtual void setValue(uint32_t value) { setValueAs<uint32_t>(value); }
            virtual void setValue(uint16_t value) { setValueAs<uint16_t>(value); }
            virtual void setValue(uint8_t value) { setValueAs<uint8_t>(value); }
            virtual void setValue(int32_t value) { setValueAs<int32_t>(value); }
            virtual void setValue(int16_t value) { setValueAs<int16_t>(value); }
            virtual void setValue(int8_t value) { setValueAs<int8_t>(value); }
            virtual void setValue(bool value) { setValueAs<bool>(value); }
            virtual void setValue(float value) { setValueAs<float>(value); }
            virtual void setValue(double value) { setValueAs<double>(value); }

            virtual bool isDirty() const { return dirty_; };

        protected:
            /*
             * We could get really fancy here with different conversion between different types
             *  I just stuck with a static cast.
             */
            template<typename Q>
            inline void getValueAs(typename boost::disable_if<boost::is_same<Q, T>, Q>::type& value) const
            {
                value = static_cast<Q>(value_);
                dirty_ = false;
            };

            template<typename Q>
            inline void getValueAs(typename boost::enable_if<boost::is_same<Q, T>, Q>::type& value) const
            {
                value = value_;
                dirty_ = false;
            };

            template<typename Q>
            inline void setValueAs(typename boost::disable_if<boost::is_same<Q, T>, Q>::type value)
            {
                value_ = static_cast<Q>(value);
				dirty_ = false;
            };

            template<typename Q>
            inline void setValueAs(typename boost::enable_if<boost::is_same<Q, T>, Q>::type value)
            {
                value_ = value;
				dirty_ = false;
            };


        private:
            T value_;

            /*
             * This is `mutable` because, even for a const object, the read operation resets
             */
            mutable bool dirty_;
    };

    class ParameterDb;

    namespace internal_
    {
        typedef boost::unordered_map<uint32_t, boost::shared_ptr<DbEntry> > DbEntryMap;

        extern "C"
        {
            XCPServer_MemValidateFunc_t memValidateCallback;
            XCPServer_MemWriteFunc_t memWriteCallback;
            XCPServer_MemReadFunc_t memReadCallback;
        }
    }

    class ParameterDb
    {
        public:
            ParameterDb(): db_() {};
            ~ParameterDb() {};

            inline ParameterDb& update(uint32_t addr, const uint32_t& value) { return update<uint32_t>(addr, value); }
            inline ParameterDb& update(uint32_t addr, const uint16_t& value) { return update<uint16_t>(addr, value); }
            inline ParameterDb& update(uint32_t addr, const uint8_t& value) { return update<uint8_t>(addr, value); }
            inline ParameterDb& update(uint32_t addr, const int32_t& value) { return update<int32_t>(addr, value); }
            inline ParameterDb& update(uint32_t addr, const int16_t& value) { return update<int16_t>(addr, value); }
            inline ParameterDb& update(uint32_t addr, const int8_t& value) { return update<int8_t>(addr, value); }
            inline ParameterDb& update(uint32_t addr, const bool& value) { return update<bool>(addr, value); }
            inline ParameterDb& update(uint32_t addr, const float& value) { return update<float>(addr, value); }
            inline ParameterDb& update(uint32_t addr, const double& value) { return update<double>(addr, value); }

            // Do not keep and hold onto the reference returned
            //  from this function... it could be deleted out
            //  from under your nose.
            DbEntry& operator[](const uint32_t& addr) const
            {
                try {
                    return *(db_.at(addr));
                } catch (const std::out_of_range& e) {
                    return NullDbEntry;
                }
            }

            inline internal_::DbEntryMap::size_type erase(uint32_t addr) { return db_.erase(addr); }

            inline ParameterDb& clear() { db_.clear(); return *this; }

            inline bool empty() const throw() /*noexcept*/ { return db_.empty(); }

            inline internal_::DbEntryMap::size_type size() const throw() /*noexcept*/ { return db_.size(); }

            inline bool memValidate(uint32_t addr, uint8_t addrExt, uint16_t numBytes)
            {
                return operator[](addr).validate(addrExt, numBytes);
            }

            inline bool memWrite(uint32_t destAddr, uint8_t destAddrExt, uint8_t const * pSrc, uint16_t numBytes)
            {
                return operator[](destAddr).write(destAddrExt, pSrc, numBytes);
            }

            inline bool memRead(uint32_t srcAddr, uint8_t srcAddrExt, uint8_t *pDest, uint16_t numBytes)
            {
                return operator[](srcAddr).read(srcAddrExt, pDest, numBytes);
            }

            void registerWithServer(XCPServer_t* pXCP)
            {
                XCPServer_registerMemValidate(pXCP, &internal_::memValidateCallback, static_cast<void*>(this));
                XCPServer_registerMemWrite(pXCP, &internal_::memWriteCallback, static_cast<void*>(this));
                XCPServer_registerMemRead(pXCP, &internal_::memReadCallback, static_cast<void*>(this));
            }

        protected:

            template<typename Q>
            ParameterDb& update(uint32_t addr, const Q& value)
            {
                boost::shared_ptr<DbEntry> sp;
                try {
                    sp = db_.at(addr);
                } catch (const std::out_of_range& e) {
                    sp = boost::make_shared<PrimitiveDbEntry<Q> >(value);
                    db_.insert(std::make_pair(addr, sp));  // what if this fails?
                }
                value >> *sp;  // stick in the value
                return *this;
            }

        private:
            // Mapping of address to DbEntry
            internal_::DbEntryMap db_;
    };

    // Provide an interface for object to update an xcp ParameterDb with their contents
    class xcpable
    {
        public:
            virtual ~xcpable() {}

            ///////////////////////////////////////////////////////////////////////////////
            /// @brief Update db starting at startAddr
            /// @param db
            /// @param start address
            /// @return the next free address
            ///////////////////////////////////////////////////////////////////////////////
            virtual uint32_t toXcp(ParameterDb& db, uint32_t startAddr) const = 0;
    };
}

#endif /* XCPSERVERDB_HPP_ */
