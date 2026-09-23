#include <interfaces/VP3Record/InterfaceTypes.h>
#include <interfaces/CycleSeg/TxInterfaceOutputChannel.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <gps_public.h>
#ifdef __cplusplus
}
#endif


class CycleSegOutput {
public:
    CycleSegOutput();

    bool initialize();
    void update(bool skipVP3);

private:
    VP3RecordOutput* vp3RecordOutputChannel_;
    CycleSegTxInterfaceOutputChannel* txOutputChannel_;
};


