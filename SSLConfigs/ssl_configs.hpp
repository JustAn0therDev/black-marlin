#ifndef SSLCONFIGSCPP
#define SSLCONFIGSCPP
#include <fstream>

constexpr const char BM_CERT_KEY_PATHS[] = "bm_cert_key_paths.txt";

struct SSLCertificateFilePaths 
{
    std::string CertPath;
    std::string PrivateKeyPath;
};

namespace SSLConfigs 
{
    // Returns true if the SSL config file with the paths in it exists in the same directory; false otherwise.
    bool HasSSLConfigFileInSameDir();
    // Returns a struct with paths to the certificate files.
    SSLCertificateFilePaths GetSSLCertificateFilePaths();
}


#endif /* SSLCONFIGSCPP */
