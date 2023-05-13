//
// Created by Administrator on 2023/5/12.
//

#ifndef MUSIC163SONGDOWNLOAD_CLOUDMUSIC_H
#define MUSIC163SONGDOWNLOAD_CLOUDMUSIC_H
#include "include/plugins/v1/NetifePlugins.h"
#include "include/plugins/v1/NetifePluginAgent.h"
#include "Poco/ClassLibrary.h"
class CloudMusic : public NetifePlugins{
private:
    std::string lastSongDownloadUrl;
public:
    CloudMusic() : NetifePlugins(){

    }

    ~CloudMusic() override = default;

    std::string GetName() const override;

    std::string GetVersion() const override;

    std::string DispatcherCommand(std::string commandHead, std::map<std::string, std::optional<std::string>> params) override;

    //当插件启用的时候 [顺序不明确]
    bool OnEnable() override { return true;}

    //当插件关闭的时候 [可能是人为禁用单独的插件]
    bool OnDisable() override { return true; }

    //当插件全部加载完毕的时候 [此时可以使用依赖插件]
    void OnLoaded() override {}

    //当软件即将退出的时候 [此时所有插件都即将关闭]
    void OnExiting() override {}

    bool OnRequestSendingOut(NetworkRequest* request) override;

    std::string GetLastDownloadUrl();
};


#endif //MUSIC163SONGDOWNLOAD_CLOUDMUSIC_H
