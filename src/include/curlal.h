/**
 * @file
 * @brief The curlal public header
 *
 * @author Lukas Deutscher
 * @date 26.07.2018
 */

#ifndef CURLAL_H
#define CURLAL_H

#include <curl/curl.h> // The curl header
#include <string>
#include <map>

void CurlAlInit();
void CurlAlCleanup();

class CurlAlHandle
{
    private:
    CURL* CurlHandler;
    char* CurlErrorBuffer;
    std::string CurlResponseBuffer;

    public:
    CurlAlHandle();
    ~CurlAlHandle();

    /**
     * @brief Executes the query to the webserver
     *
     * If this function returns false, you should get more details with the
     * GetErrorBuffer function.
     *
     * @return bool The success of the operation
     */
    bool Execute();

    /**
     * @brief Resets the options to the default
     *
     * @return void
     */
    void ResetOptions();
    /**
     * @brief Sets the url for the query
     *
     * @param URL The Url as string to set.
     * @return bool Success of the operation
     */
    bool SetUrl(const std::string &URL);
    /**
     * @brief Sets the postfields for the query
     *
     * This function takes a map with 2 strings as argument and sets the underlying
     * query string.
     *
     * @param PostData The post data as map of 2 strings
     * @return bool The success of the opteration
     */
    bool SetPost(std::map<std::string, std::string>* PostData);

    /**
     * @brief Returns the Response after execute is called
     *
     * @return std::string The string with the response
     */
    std::string GetResponseBuffer();
    /**
     * @brief Returns the error in the buffer in human readable form
     *
     * @return std::string The error
     */
    std::string GetErrorBuffer();

    /**
     * @brief Escapes the given string to url encoded chars
     *
     * @param Str The string to escape
     * @return string The escaped string
     */
    std::string UrlEscapeString(const std::string &Str);
};

#endif
