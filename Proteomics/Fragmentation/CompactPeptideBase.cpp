﻿#include <algorithm>
#include <cmath>

#include "CompactPeptideBase.h"
#include "NeutralTerminusFragment.h"
#include "../Modifications/Modification.h"
#include "MzLibAssert.h"

using namespace Chemistry;
using namespace Proteomics::AminoAcidPolymer;
using namespace Proteomics::ProteolyticDigestion;
namespace Proteomics
{
    namespace Fragmentation
    {

        std::vector<NeutralTerminusFragment*> CompactPeptideBase::getTerminalMasses() const
        {
            return privateTerminalMasses;
        }

        void CompactPeptideBase::setTerminalMasses(const std::vector<NeutralTerminusFragment*> &value)
        {
            privateTerminalMasses = value;
        }

        double CompactPeptideBase::getMonoisotopicMassIncludingFixedMods() const
        {
            return privateMonoisotopicMassIncludingFixedMods;
        }

        void CompactPeptideBase::setMonoisotopicMassIncludingFixedMods(double value)
        {
            privateMonoisotopicMassIncludingFixedMods = value;
        }


        int CompactPeptideBase::GetHashCode()
        {
            // unchecked
            auto result = 0;
            if (!getTerminalMasses().empty())
            {
                for (auto mass : getTerminalMasses())
                {
                    result += (result * 31) ^ mass->GetHashCode();
                }
            }
            return result;
            //C# TO C++ CONVERTER TODO TASK: End of the original C# 'unchecked' block.
        }

        bool CompactPeptideBase::Equals(CompactPeptideBase *cp)
        {
            if (!getTerminalMasses().empty() && !cp->getTerminalMasses().empty()) 
            {
                //neither series is nulll

#ifdef ORIG
                return getTerminalMasses().SequenceEqual(cp->getTerminalMasses());
#endif
                return Assert::SequenceEqual ( getTerminalMasses(), cp->getTerminalMasses() );
            }
            else //Cannot compare
            {
                return false;
            }
        }

        std::vector<NeutralTerminusFragment*> CompactPeptideBase::ComputeNeutralTerminusFragments(PeptideWithSetModifications *peptide, FragmentationTerminus fragmentationTerminus)
        {
            double mass = 0;
            std::vector<NeutralTerminusFragment*> v;
            
            if (fragmentationTerminus == FragmentationTerminus::N ||
                fragmentationTerminus == FragmentationTerminus::Both)
            {
                for (int r = 0; r <= peptide->getLength() - 1; r++) 
                {
                    //This is a zero based indexed for residues. The index of the first amino acid
                    // in the peptide is 0.
#ifdef ORIG
                    mass += Residue::ResidueMonoisotopicMass[peptide[r]];
#endif
                    char OneLetter = peptide->getBaseSequence()[r];
                    auto res = Residue::GetResidue(OneLetter);
                    if ( res != nullptr ) {
                        mass += res->getMonoisotopicMass();
                    }
                    else {
                        mass =std::nan("0");
                    }
                            
                    // side-chain mod
                    Modification* currentModification;
                    std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator = peptide->getAllModsOneIsNterminus().find(r + 2);
                    if ( AllModsOneIsNterminus_iterator != peptide->getAllModsOneIsNterminus().end()) 
                    {
                        //This is a one based index. The index of the fragment from the first amino acid is 1.
                        currentModification = AllModsOneIsNterminus_iterator->second;
                        mass += static_cast<double>(currentModification->getMonoisotopicMass().value());
                    }

                    // N-terminal mod
                    std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator2 = peptide->getAllModsOneIsNterminus().find(1);
                    if (r == 0 && AllModsOneIsNterminus_iterator2 != peptide->getAllModsOneIsNterminus().end())
                    {
                        currentModification = AllModsOneIsNterminus_iterator2->second;
                        mass += static_cast<double>(currentModification->getMonoisotopicMass().value());
                    }

                    if (r != peptide->getLength() - 1)
                    {
                        //This is a one based index. The index of the fragment from the first amino acid is 1.
                        //yield return new NeutralTerminusFragment(FragmentationTerminus::N, mass, r + 1, r + 1);
                        NeutralTerminusFragment* ntf = new NeutralTerminusFragment(FragmentationTerminus::N, mass,
                                                                                  r + 1, r + 1);
                        v.push_back(ntf);
                        
                    }
                }
            }

            if (fragmentationTerminus == FragmentationTerminus::C || fragmentationTerminus == FragmentationTerminus::Both)
            {
                mass = 0;

                for (int r = peptide->getLength() - 1; r >= 0; r--)
                {
#ifdef ORIG
                    mass += Residue::ResidueMonoisotopicMass[peptide[r]];
#endif
                    char OneLetter = peptide->getBaseSequence()[r];
                    auto res = Residue::GetResidue(OneLetter);
                    if ( res != nullptr ) {
                        mass += res->getMonoisotopicMass();
                    }
                    else {
                        mass = std::nan("0");
                    }

                    // side-chain mod
                    Modification *currentModification;
                    std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator = peptide->getAllModsOneIsNterminus().find(r + 2);
                    if ( AllModsOneIsNterminus_iterator != peptide->getAllModsOneIsNterminus().end())
                    {
                        currentModification = AllModsOneIsNterminus_iterator->second;
                        mass += static_cast<double>(currentModification->getMonoisotopicMass().value());
                    }

                    // C-terminal mod
                    std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator2 = peptide->getAllModsOneIsNterminus().find(peptide->getLength() + 2);
                    if (r == peptide->getLength() - 1 &&
                        AllModsOneIsNterminus_iterator2 != peptide->getAllModsOneIsNterminus().end())
                    {
                        currentModification = AllModsOneIsNterminus_iterator2->second;
                        mass += static_cast<double>(currentModification->getMonoisotopicMass().value());
                    }

                    if (r != -1)
                    {
                        //yield return new NeutralTerminusFragment(FragmentationTerminus::C, mass,
                        //                                         peptide->getLength() - r, r + 1);
                        NeutralTerminusFragment* ntf = new NeutralTerminusFragment(FragmentationTerminus::C, mass,
                                                                                  peptide->getLength() - r, r + 1);
                        v.push_back(ntf);
                    }
                }
            }
            return v;
        }
    }
}
