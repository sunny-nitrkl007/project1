#include <ais/serialization/Datum.h> // For Boost serialization

#ifndef _SwitchInputScs_h_
#define _SwitchInputScs_h_

#define NO_OF_STG_INPUTS  4

enum STG : int
{
    OPEN = 0,
    CLOSED,
    UNKNOWN
};


class SwitchInputScsStorage : public csvable
{  
    public:
        SwitchInputScsStorage() :
            STG_values{STG::UNKNOWN, STG::UNKNOWN, STG::UNKNOWN, STG::UNKNOWN} {}

        template <class Archive>
        void serialize(Archive &ar, unsigned int version)
        {
            ar & STG_values;
        }

        void toCsv(CsvOutStream& out) const
        {
           // Do nothing for now. Method exists to conform to the interface template and to avoid compilation warnings
        }

        void set_STG_value(int index, int value)
        {
            if (index < NO_OF_STG_INPUTS) {
                STG_values[index] = value;
            }
        }

        int get_STG_value(int index)
        {
            if (index < NO_OF_STG_INPUTS) {
                return STG_values[index];
            }

            return STG::UNKNOWN;
        }

     private:
         /* Add Fields Here */
        int STG_values[NO_OF_STG_INPUTS];
};  

typedef Datum<SwitchInputScsStorage> SwitchInputScs;

BOOST_CLASS_VERSION(SwitchInputScsStorage, 1);
#endif

