//
// Created by Administrator on 2023/5/12.
//

#include "CloudMusic.h"
#include "TextHelper.h"
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/ParseHandler.h>
#include <Poco/JSON/Stringifier.h>
#include <vector>
#include <map>
using Poco::JSON::Object;
using Poco::JSON::Array;
using Poco::JSON::ParseHandler;
using Poco::JSON::Parser;
using Poco::JSON::Stringifier;

namespace var = Poco::Dynamic;
using namespace std;
std::string CloudMusic::GetName() const {
    return "CloudMusic";
}

std::string CloudMusic::GetVersion() const {
    return "1.0.0";
}

std::string CloudMusic::DispatcherCommand(std::string commandHead, std::map<std::string, std::optional<std::string>> params) {
    if (commandHead == "getLastDownloadUrl"){
        return GetLastDownloadUrl();
    }

    return "";
}

bool CloudMusic::OnRequestSendingOut(NetworkRequest *request) {
    std::vector<string> rawContent;
    rawContent.emplace_back("parserRawHtml");
    rawContent.push_back(request->RawText);
    auto parsers = agent->CarryPluginCommandWithVector("parserRawHtml", rawContent);
    if (parsers.has_value()){
        auto map = agent->WrapperCommandResultWithMap(parsers.value());
        if (Netife::TextHelper::split(map["status"], " ")[1] == "/o_live_p2p_mobilesdk"){
            Parser parser;
            var::Var result = parser.parse(map["dataBody"]); // 解析 JSON 文件
            Poco::JSON::Array::Ptr array = result.extract<Poco::JSON::Array::Ptr>();
            Poco::Dynamic::Var ele = array->get(0);
            Poco::JSON::Object theObj = *ele.extract<Poco::JSON::Object::Ptr>();
            Poco::Dynamic::Var url = theObj.get("u");
            lastSongDownloadUrl = url.toString();
            agent->LogInfo("Caught the song: " + lastSongDownloadUrl);
        }
    }
    return true;
}

std::string CloudMusic::GetLastDownloadUrl() {
    return lastSongDownloadUrl;
}
POCO_BEGIN_MANIFEST(NetifePlugins)
    POCO_EXPORT_CLASS(CloudMusic)
POCO_END_MANIFEST