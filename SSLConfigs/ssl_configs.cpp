#include <iostream>
#include "ssl_configs.hpp"
#include "../PathHandler/path_handler.hpp"

bool SSLConfigs::HasSSLConfigFileInSameDir() 
{
    const auto full_path_to_cert_files = PathHandler::GetThisExecutingBinaryFullPath() + BM_CERT_KEY_PATHS;

    std::fstream file_stream(full_path_to_cert_files, std::ios::in);

    return file_stream.good();
}

SSLCertificateFilePaths SSLConfigs::GetSSLCertificateFilePaths()
{
    std::string buffer;
    SSLCertificateFilePaths return_value;

    const auto full_path_to_cert_files = PathHandler::GetThisExecutingBinaryFullPath() + BM_CERT_KEY_PATHS;

    std::fstream file_stream(full_path_to_cert_files, std::ios::in);

    if (file_stream.good())
    {
        while (std::getline(file_stream, buffer))
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
    }
    else 
    {
        std::cout << "File found but could not be read. Please check the integrity of the file and make sure that the program has access to create and read files." << "\n";
        exit(1);
    }

    return return_value;
}
