/**
 * @file
 * @brief The curlal cpp file with the functions
 *
 * We abstract the curl layer to use some cpp functions
 *
 * @remarks The CurlAl is not thread safe
 *
 * @author Lukas Deutscher
 * @date 26.07.2018
 */

#include "curlal.h"

/**
 * @brief Initializes the curl library
 *
 * @return void
 */
void CurlAlInit()
{
    curl_global_init(CURL_GLOBAL_ALL);
}

/**
 * @brief Cleanup of the connection curl uses
 *
 * @return void
 */
void CurlAlCleanup()
{
    curl_global_cleanup();
}

/**
 * Here are the functions for the CurlAl class defined.
 */

/**
 * First the functions to handle the memory
 */
/**
 * @brief Writes the bytedata to the given buffer
 *
 * @param Buffer    The void* to the data
 * @param Size      The Size of a single char
 * @param NNemb     The length of the data
 * @param UserPtr   The Ptr to the buffer to which the first buffer should be written
 * @return size_t   The written bytes
 */
size_t WriteResponseData(void* Buffer, size_t Size, size_t NMemb, void* UserPtr)
{
    size_t BufferSize = Size * NMemb;
    std::string NewString((char*)Buffer, NMemb);
    std::string* CurlBuffer = (std::string*) UserPtr;

    *CurlBuffer += NewString;

    return BufferSize;
}

/**
 * The the class members
 */

CurlAlHandle::CurlAlHandle()
{
    // Initializing the curl handle
    this->CurlHandler = curl_easy_init();

    // Getting ram for the error buffer
    this->CurlErrorBuffer = (char*) calloc(CURL_ERROR_SIZE, sizeof(char));

    // Setting the default options
    this->ResetOptions();
}

CurlAlHandle::~CurlAlHandle()
{
    curl_easy_cleanup(this->CurlHandler);
}

bool CurlAlHandle::Execute()
{
    CURLcode CurlResult;
    CurlResult = curl_easy_perform(this->CurlHandler);

    if (CurlResult != CURLE_OK) {
        return false;
    }

    return true;
}

void CurlAlHandle::ResetOptions()
{
    curl_easy_reset(this->CurlHandler);

    // Options to write the buffer to the member string
    curl_easy_setopt(this->CurlHandler, CURLOPT_WRITEFUNCTION, WriteResponseData);
    curl_easy_setopt(this->CurlHandler, CURLOPT_WRITEDATA,  &this->CurlResponseBuffer);

    // Setting the error buffer
    curl_easy_setopt(this->CurlHandler, CURLOPT_ERRORBUFFER, this->CurlErrorBuffer);
}

bool CurlAlHandle::SetUrl(const std::string &URL)
{
    CURLcode Res = curl_easy_setopt(this->CurlHandler, CURLOPT_URL, URL.c_str());

    if (Res != CURLE_OK) {
        return false;
    }

    return true;
}

bool CurlAlHandle::SetPost(std::map<std::string, std::string>* PostData)
{
    std::string PostStr;

    // Building the Post Str
    for (auto Iter = PostData->begin(); Iter != PostData->end(); ++Iter) {
        if (Iter != PostData->begin()) {
            PostStr += "&";
        }

        PostStr += this->UrlEscapeString(Iter->first);
        PostStr += "=";
        PostStr += this->UrlEscapeString(Iter->second);
    }

    // Copying the post string to the curl handler
    CURLcode Res = curl_easy_setopt(
        this->CurlHandler,
        CURLOPT_COPYPOSTFIELDS,
        PostStr.c_str()
    );

    // Return
    if (Res != CURLE_OK) {
        return false;
    }

    return true;
}

std::string CurlAlHandle::GetResponseBuffer()
{
    return this->CurlResponseBuffer;
}

std::string CurlAlHandle::GetErrorBuffer()
{
    std::string CurlErrorStr(this->CurlErrorBuffer);
    return CurlErrorStr;
}

std::string CurlAlHandle::UrlEscapeString(const std::string &Str)
{
    char* EscapedStr = curl_easy_escape(this->CurlHandler, Str.c_str(), Str.length());

    std::string ReturnStr(EscapedStr);

    curl_free(EscapedStr);

    return ReturnStr;
}
