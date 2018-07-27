#include "../include/curlal.h"

#include <string>
#include <iostream>
#include <map>

void CurlAlDemo()
{
    CurlAlHandle* Handler = new CurlAlHandle();
    Handler->SetUrl("http://demosite.com");

    std::map<std::string, std::string> PostData;

    PostData["post1"] = "value";
    PostData["post2"] = "value2";

    bool Res = Handler->SetPost(&PostData);

    if (!Res) {
        std::cout << Handler->GetErrorBuffer() << std::endl;
    }

    bool ResOk = Handler->Execute();

    if (!ResOk) {
        std::string Buffer = Handler->GetErrorBuffer();
        std::cout << Buffer << std::endl;
    } else {
        std::cout << Handler->GetResponseBuffer() << std::endl;
    }
}
