
#include "HWCPipeNodeRegister.hpp"
static vector<shared_ptr<HWCNodeBase>> HWCPipeNodeRegister::nodes;


static HWCPipeNodeRegister& getInstance(){
    static HWCPipeNodeRegister hwcPipeNodeRegister;
    return hwcPipeNodeRegister;
}

void HWCPipeNodeRegister::avRegisterAllNode(HWCNodeBase& node){
    
}
