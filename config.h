#ifndef CONFIG_H
#define CONFIG_H

#include <string>

struct EmailConfig {
    bool activateEmail;
    std::string smtpServer;
    int smtpPort;
    std::string emailAddress;
    std::string emailPassword;
};

struct AppConfig {
    std::string rssLink;
    std::string lastRunDate;
};

void saveEmailConfig(const EmailConfig& config);
EmailConfig loadEmailConfig();
void saveAppConfig(const AppConfig& config);
AppConfig loadAppConfig();

#endif // CONFIG_H
