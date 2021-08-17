#include <fstream>
#include "ssl_configs.hpp"
#include "../PathHandler/path_handler.hpp"

void SSLConfigs::SetSSLMacroValue() 
{
    const auto full_path_to_cert_files = PathHandler::GetThisExecutingBinaryFullPath() + BM_CERT_KEY_PATHS;

    std::fstream fstream(full_path_to_cert_files, std::ios::in);
#define HAS_FILE_WITH_SSL_CERTIFICATE_PATHS 1
}

SSLCertificateFilePaths SSLConfigs::GetSSLCertificateFilePaths()
{
    std::string buffer;
    SSLCertificateFilePaths return_value;

    const auto full_path_to_cert_files = PathHandler::GetThisExecutingBinaryFullPath() + BM_CERT_KEY_PATHS;

    std::fstream fstream(full_path_to_cert_files, std::ios::in);

    while (std::getline(fstream, buffer))
    {
        if (std::empty(return_value.CertPath)) 
        {
            return_value.CertPath = buffer;
        }
        else 
        {
            return_value.PrivateKeyPath = buffer;
        }
    }

    return return_value;
}
