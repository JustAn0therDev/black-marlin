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
    // Sets the HAS_FILE_WITH_SSL_CERTIFICATE_PATHS macro value. This function
    // (and what it does altogether) will probably change in the future.
    void SetSSLMacroValue();
    // Returns a struct with paths to the certificate files.
    SSLCertificateFilePaths GetSSLCertificateFilePaths();
}


#endif /* SSLCONFIGSCPP */
