#ifndef OPERATORIDTEST_H
#define OPERATORIDTEST_H

#include <ais/task/Task.h>

#include <interfaces/LpsSaListMgr/InterfaceCommon.h>
#include <bdt/CPMOperatorIdList.h>
#include "../../apps/LpsSaListMgrApp/OperatorIdListMgr.hpp"
#include <interfaces/LpsSaListMgr/TxInterface.hpp>
#include <interfaces/LpsSaListMgr/TxInterfaceInputChannel.h>

class OperatorIdTest: public task::Task
{
public:
    OperatorIdTest( const std::string& taskName );
    virtual ~OperatorIdTest( );

    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );

protected:
private:
    static constexpr auto CsvInFile = "/media/sf_My_Shared_Folder/OperatorID.csv";
    static constexpr auto CsvOutFile = "/media/sf_My_Shared_Folder/OperatorID_out.csv";
    static constexpr auto JsonOutFile = "/media/sf_My_Shared_Folder/OperatorID_out_";

    // For receiving list locations from the list manager app.
    bool listLocationsKnown_;
    LpsSaListMgrTxInterface listTx_;
    LpsSaListMgrTxInterfaceInputChannel* listTxInputChannel_;

    void ExportToJSON(OperatorIdStatus& operatorIdStatus, int32_t passcode);
    void getOperatorNameTest(int32_t passcode);

    OperatorIdListMgr operatorIdListMgr;

    tes_common_ais::CPMOperatorIdList operatorIdList;
    tes_common_ais::CPMOperatorIdListEntry operatorId;
    std::string logPrefix_;
};

#endif //OPERATORIDTEST_H
