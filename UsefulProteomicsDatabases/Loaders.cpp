﻿/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#include "Loaders.h"
#include "UnimodLoader.h"
#include "../Proteomics/Modifications/Modification.h"
#include "PtmListLoader.h"

#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <regex>

using namespace Proteomics;
using namespace UsefulProteomicsDatabases;

namespace UsefulProteomicsDatabases
{
    // Edgar: ignoring for the C++ version for now.
    //Loaders::StaticConstructor::StaticConstructor()
    //{
    //    ServicePointManager->SecurityProtocol = SecurityProtocolType::Tls12 | SecurityProtocolType::Tls11 | SecurityProtocolType::Tls;
    //}
    //
    //Loaders::StaticConstructor Loaders::staticConstructor;

    void Loaders::UpdateUniprot(const std::string &uniprotLocation)
    {
#ifdef ORIG
        // Edgar: not downloading file in C++ version. 
        DownloadUniprot(uniprotLocation);
#endif
        if (!FileSystem::fileExists(uniprotLocation))
        {
            std::cout << "Uniprot database does not exist please provide the file as " <<
                uniprotLocation << std::endl;
            //FileSystem::renamePath(uniprotLocation + ".temp", uniprotLocation);
            return;
        }

#ifdef ORIG
        bool ye = FilesAreEqual_Hash(uniprotLocation + ".temp", uniprotLocation);
        if (ye)
        {
            std::cout << "Uniprot database is up to date, doing nothing" << std::endl;
            //File::Delete(uniprotLocation + ".temp");
            std::remove((uniprotLocation + ".temp").c_str());
        }
        else
        {
            std::cout << "Uniprot database updated, saving old version as backup" << std::endl;

            //FileSystem::renamePath(uniprotLocation, uniprotLocation + DateTime::Now.ToString("dd-MMM-yyyy-HH-mm-ss"));
            time_t now = time(0);
            std::string s = ctime(&now);
            FileSystem::renamePath(uniprotLocation, uniprotLocation + s);
            FileSystem::renamePath(uniprotLocation + ".temp", uniprotLocation);
        }
#endif
    }

    void Loaders::UpdateUnimod(const std::string &unimodLocation)
    {
#ifdef ORIG
        // Edgar: not downloading file in C++ version. 
        DownloadUnimod(unimodLocation);
#endif
        if (!FileSystem::fileExists(unimodLocation))
        {
            std::cout << "Unimod database does not exist, please provide the file as " <<
                unimodLocation << std::endl;
            //FileSystem::renamePath(unimodLocation + ".temp", unimodLocation);
            return;
        }
#ifdef ORIG
        bool ye = FilesAreEqual_Hash(unimodLocation + ".temp", unimodLocation);
        if (ye)
        {
            std::cout << "Unimod database is up to date, doing nothing" << std::endl;
            //File::Delete(unimodLocation + ".temp");
            std::remove((unimodLocation + ".temp").c_str());
        }
        else
        {
            std::cout << "Unimod database updated, saving old version as backup" << std::endl;

            //FileSystem::renamePath(unimodLocation, unimodLocation + DateTime::Now.ToString("dd-MMM-yyyy-HH-mm-ss"));
            time_t now = time(0);
            std::string s = ctime(&now);
            FileSystem::renamePath(unimodLocation, unimodLocation + s);
            FileSystem::renamePath(unimodLocation + ".temp", unimodLocation);
        }
#endif
    }

    void Loaders::UpdatePsiMod(const std::string &psimodLocation)
    {
#ifdef ORIG
        // Edgar: not downloading file in C++ version. 
        DownloadPsiMod(psimodLocation);
#endif
        if (!FileSystem::fileExists(psimodLocation))
        {
            std::cout << "PSI-MOD database does not exist, please provide file as " <<
                psimodLocation << std::endl;
            //FileSystem::renamePath(psimodLocation + ".temp", psimodLocation);
            return;
        }
#ifdef ORIG
        if (FilesAreEqual_Hash(psimodLocation + ".temp", psimodLocation))
        {
            std::cout << "PSI-MOD database is up to date, doing nothing" << std::endl;
            //File::Delete(psimodLocation + ".temp");
            std::remove((psimodLocation + ".temp").c_str());
        }
        else
        {
            std::cout << "PSI-MOD database updated, saving old version as backup" << std::endl;

            //FileSystem::renamePath(psimodLocation, psimodLocation + DateTime::Now.ToString("dd-MMM-yyyy-HH-mm-ss"));
            time_t now = time(0);
            std::string s = ctime(&now);
            FileSystem::renamePath(psimodLocation, psimodLocation + s);
            FileSystem::renamePath(psimodLocation + ".temp", psimodLocation);
        }
#endif
    }

    void Loaders::UpdateElements(const std::string &elementLocation)
    {
#ifdef ORIG
        // Edgar: not downloading file in C++ version. 
        DownloadElements(elementLocation);
#endif
        if (!FileSystem::fileExists(elementLocation))
        {
            std::cout << "Element database does not exist, please provide file as " <<
                elementLocation << std::endl;
            //FileSystem::renamePath(elementLocation + ".temp", elementLocation);
            return;
        }
#ifdef ORIG        
        if (FilesAreEqual_Hash(elementLocation + ".temp", elementLocation))
        {
            std::cout << "Element database is up to date, doing nothing" << std::endl;
            //File::Delete(elementLocation + ".temp");
            std::remove((elementLocation + ".temp").c_str());
        }
        else
        {
            std::cout << "Element database updated, saving old version as backup" << std::endl;

            //FileSystem::renamePath(elementLocation, elementLocation + DateTime::Now.ToString("dd-MMM-yyyy-HH-mm-ss"));
            time_t now = time(0);
            std::string s = ctime(&now);
            FileSystem::renamePath(elementLocation, elementLocation + s);
            FileSystem::renamePath(elementLocation + ".temp", elementLocation);
        }
#endif
    }

    std::unordered_map<std::string, int> Loaders::GetFormalChargesDictionary(
        std::unique_ptr<obo> &psiModDeserialized)
    {
#ifdef ORIG
        auto modsWithFormalCharges = psiModDeserialized->getItems().OfType<UsefulProteomicsDatabases::Generated::oboTerm*>().Where([&] (std::any b)
        {
            return b::xref_analog != nullptr && b::xref_analog::Any([&] (std::any c)
            {
                c::dbname->Equals("FormalCharge");
            });
        });
        Regex *digitsOnly = new Regex(R"([^\d])");

        //C# TO C++ CONVERTER TODO TASK: The following lambda expression could not be converted:
        //return modsWithFormalCharges->ToDictionary(b =>
        //                                           TangibleLambdaToken712public
        // static void LoadElements(std::string elementLocation){
        //    if (!FileSystem::fileExists(elementLocation)){UpdateElements(elementLocation);
        //   } }
#endif
        
        std::unordered_map<std::string, int> modsWithFormalCharges;
        std::regex digitsOnly(R"([^\d])");

        std::vector<term> v;
        // Edgar: will have to revisit this part on how to implement the equivalent of OfType in C++
        for ( auto b: psiModDeserialized->term() ) {
            if  (!b.xref_analog().empty() ) {
                bool found = false;
                std::string valstring ;
                for ( auto c: b.xref_analog() ) {
                    if ( c.dbname().get() == "FormalCharge") {
                        found = true;
                        valstring = c.name().get();
                        break;
                    }
                }
                if ( found )  {
                    std::string key = "PSI-MOD; " + b.id().get();
                    std::string vals = std::regex_replace(valstring, digitsOnly, "" );
                    try
                    {
                        int val = std::stoi (vals);
                        modsWithFormalCharges.emplace(key, val);
                    }
                    catch (...)
                    {
                        std::cout << " error extracting int from " << vals << std::endl;
                    }
                }                
            }
        }

        return  modsWithFormalCharges;
    }

    void Loaders::LoadElements(std::string elementLocation){
        if (!FileSystem::fileExists(elementLocation)) {
            Loaders::UpdateElements(elementLocation);
        }
        return;
    }

    
    std::vector<Modification*> Loaders::LoadUnimod(const std::string &unimodLocation)
    {
        if (!FileSystem::fileExists(unimodLocation))
        {
            Loaders::UpdateUnimod(unimodLocation);
        }
        return UnimodLoader::ReadMods(unimodLocation);
    }

    std::unique_ptr<obo> Loaders::LoadPsiMod(const std::string &psimodLocation)
    {
#ifdef ORIG
        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        auto psimodSerializer = new XmlSerializer(typeof(Generated::obo));

        if (!FileSystem::fileExists(psimodLocation))
        {
            Loaders::UpdatePsiMod(psimodLocation);
        }

        FileStream tempVar(psimodLocation, FileMode::Open, FileAccess::Read, FileShare::Read);        
        return dynamic_cast<Generated::obo*>(psimodSerializer->Deserialize(&tempVar));
#endif
        std::ifstream input(psimodLocation);
        auto obores = obo_ (input, xml_schema::flags::dont_validate); 
        
        return obores;
    }

    std::vector<Modification*> Loaders::LoadUniprot(const std::string &uniprotLocation,
                                                    std::unordered_map<std::string, int> formalChargesDictionary)
    {
        if (!FileSystem::fileExists(uniprotLocation))
        {
            Loaders::UpdateUniprot(uniprotLocation);
        }
        std::vector<std::tuple<Modification*, std::string>> errors;
#ifdef ORIG
        return PtmListLoader::ReadModsFromFile(uniprotLocation, formalChargesDictionary, errors).OfType<Modification*>();
#endif
        return PtmListLoader::ReadModsFromFile(uniprotLocation, formalChargesDictionary, errors);        
    }

    bool Loaders::FilesAreEqual_Hash(const std::string &first, const std::string &second)
    {
        return true;
#ifdef ORIG
        FileStream a = File::Open(first, FileMode::Open, FileAccess::Read);
        FileStream b = File::Open(second, FileMode::Open, FileAccess::Read);
        std::vector<unsigned char> firstHash = MD5::Create()->ComputeHash(a);
        std::vector<unsigned char> secondHash = MD5::Create()->ComputeHash(b);
        for (int i = 0; i < firstHash.size(); i++)
        {
            if (firstHash[i] != secondHash[i])
            {
                return false;
            }
        }
        return true;
#endif
    }
            
    
#ifdef ORIG
    // NOt dealing with downloading files in the C++ version.
    void Loaders::DownloadPsiMod(const std::string &psimodLocation)
    {
        WebClient Client = WebClient();
        Client.DownloadFile(R"(https://raw.githubusercontent.com/HUPO-PSI/psi-mod-CV/master/PSI-MOD.obo.xml)", psimodLocation + ".temp");
    }

    void Loaders::DownloadUnimod(const std::string &unimodLocation)
    {
        WebClient Client = WebClient();
        Client.DownloadFile(R"(http://www.unimod.org/xml/unimod.xml)", unimodLocation + ".temp");
    }

    void Loaders::DownloadElements(const std::string &elementLocation)
    {
        WebClient Client = WebClient();
        Client.DownloadFile(R"(http://physics.nist.gov/cgi-bin/Compositions/stand_alone.pl?ele=&ascii=ascii2&isotype=some)",
                            elementLocation + ".temp");
    }

    void Loaders::DownloadUniprot(const std::string &uniprotLocation)
    {
        WebClient Client = WebClient();
        Client.DownloadFile(R"(http://www.uniprot.org/docs/ptmlist.txt)", uniprotLocation + ".temp");
    }
#endif
}
