#include "Windows.h"

#include  "HWCPipe.hpp"
#include  "HWCPipeParser.hpp"
#include  "HWCPipeNodeRegister.hpp"
#include  "Log.h"
#include  <fstream>

Windows::Windows(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	HWCPipeNodeRegister::getInstance().avRegisterAllNode();
	std::ifstream istream("./mediaconfig.json");
	std::string text;
	text.assign(std::istreambuf_iterator<char>(istream), std::istreambuf_iterator<char>());

	std::shared_ptr<HWCPipeInfo> pipeInfoPtr=HWCPipeParser::parser(text);
	std::shared_ptr<HWCPipe> pipe = std::make_shared<HWCPipe>();
	pipe->createPipe(pipeInfoPtr.get());
	pipe->registerEventBus(pipeInfoPtr.get());

	HWCEvent event;
	event.eventType = EVENT_START;
	pipe->postSyncEvent(event);

}
