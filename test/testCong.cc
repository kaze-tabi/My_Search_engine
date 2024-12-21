#include "Configuration.h"
#include <iostream>
#include "DirScanner.h"

using namespace std;

int main()
{
    try {
        DirScanner dirScanner;
       Configuration::getInstance()->LoadConfig("conf/config.conf");

        auto config = Configuration::getInstance()->getConfigMap(YULIAO);
        if (config.contains("WEB_YULIAO_PATH") && !config["WEB_YULIAO_PATH"].is_null()) {
            string webYuliaolPath = config["WEB_YULIAO_PATH"].get<string>();
            dirScanner.traverse(webYuliaolPath);
            dirScanner.getFiles();
        } else {
            cerr << "Error: WEB_YULIAO_PATH is not set or is null in the configuration." << endl;
        }
    } catch (const nlohmann::json::exception& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
    } catch (const std::exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
    }

    return 0;
} 