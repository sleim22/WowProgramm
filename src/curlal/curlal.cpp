/**
 * @file
 * @brief The curlal cpp file with the functions
 *
 * We abstract the curl layer to use some cpp functions
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
