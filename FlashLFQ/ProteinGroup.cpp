﻿#include "ProteinGroup.h"
#include "SpectraFileInfo.h"
#include "stringhelper.h"


namespace FlashLFQ
{

    ProteinGroup::ProteinGroup(const std::string &proteinGroupName, const std::string &geneName, const std::string &organism) : ProteinGroupName(proteinGroupName), GeneName(geneName), Organism(organism)
    {
        //intensities = std::unordered_map<SpectraFileInfo*, double>();
    }

    double ProteinGroup::GetIntensity(SpectraFileInfo *fileInfo)
    {
        double intensity;
        std::unordered_map<SpectraFileInfo*, double>::const_iterator intensities_iterator = intensities.find(fileInfo);
        if (intensities_iterator != intensities.end())
        {
            intensity = intensities_iterator->second;
            return intensity;
        }
        else
        {
            return 0;
        }
    }

    void ProteinGroup::SetIntensity(SpectraFileInfo *fileInfo, double intensity)
    {
        if (intensities.find(fileInfo) != intensities.end())
        {
            intensities[fileInfo] = intensity;
        }
        else
        {
            intensities.emplace(fileInfo, intensity);
        }
    }

    std::string ProteinGroup::TabSeparatedHeader(std::vector<SpectraFileInfo*> &rawFiles)
    {
        auto sb = new StringBuilder();
        sb->append(std::string("Protein Groups") + "\t");
        sb->append(std::string("Gene Name") + "\t");
        sb->append(std::string("Organism") + "\t");

        for (auto rawfile : rawFiles)
        {
            sb->append("Intensity_" + rawfile->FilenameWithoutExtension + "\t");
        }

        std::string s =  sb->toString();
        delete sb;
        return s;
    }

    std::string ProteinGroup::ToString(std::vector<SpectraFileInfo*> &rawFiles)
    {
        StringBuilder *str = new StringBuilder();
        str->append(ProteinGroupName + "\t");
        str->append(GeneName + "\t");
        str->append(Organism + "\t");

        for (auto file : rawFiles)
        {
            double intensity;
            std::unordered_map<SpectraFileInfo*, double>::const_iterator intensities_iterator = intensities.find(file);
            if (intensities_iterator != intensities.end())
            {
                intensity = intensities_iterator->second;
                str->append(std::to_string(intensity) + "\t");
            }
            else
            {
                str->append(std::to_string(0) + "\t");
            }
        }

        std::string s = str->toString();
        delete str;
        return s;
    }

    bool ProteinGroup::Equals(ProteinGroup *other)
    {
        return other->ProteinGroupName == this->ProteinGroupName;
    }

    int ProteinGroup::GetHashCode()
    {
        return StringHelper::GetHashCode(ProteinGroupName);
    }
}
