﻿#include "Peptide.h"
#include "Residue.h"
#include "OldSchoolModificationWithMultiplePossibilities.h"


namespace Proteomics {
    namespace AminoAcidPolymer    {
        Peptide::Peptide() {
        }

        Peptide::Peptide(const std::string &sequence) : AminoAcidPolymer(sequence) {
        }
        
        Peptide::Peptide(AminoAcidPolymer *aminoAcidPolymer) : Peptide(aminoAcidPolymer, true) {
        }
        
        Peptide::Peptide(AminoAcidPolymer *aminoAcidPolymer, bool includeModifications) : AminoAcidPolymer(aminoAcidPolymer, includeModifications) {
            privateParent = aminoAcidPolymer;
            privateStartResidue = 0;
            privateEndResidue = getLength() - 1;
        }

        Peptide::Peptide(AminoAcidPolymer *aminoAcidPolymer, int firstResidue, int length) : Peptide(aminoAcidPolymer, firstResidue, length, true) {
        }

        Peptide::Peptide(AminoAcidPolymer *aminoAcidPolymer, int firstResidue, int length, bool includeModifications) : AminoAcidPolymer(aminoAcidPolymer, firstResidue, length, includeModifications) {
            privateParent = aminoAcidPolymer;
            privateStartResidue = firstResidue;
            privateEndResidue = firstResidue + length - 1;
            privatePreviousResidue = aminoAcidPolymer->GetResidue(getStartResidue() - 1);
            privateNextResidue  = aminoAcidPolymer->GetResidue(getEndResidue() + 1);
        }
        
        int Peptide::getStartResidue() const {
            return privateStartResidue;
        }
        
        void Peptide::setStartResidue(int value) {
            privateStartResidue = value;
        }
        
        int Peptide::getEndResidue() const {
            return privateEndResidue;
        }
        
        void Peptide::setEndResidue(int value) {
            privateEndResidue = value;
        }
        
        AminoAcidPolymer *Peptide::getParent() const {
            return privateParent;
        }
        
        void Peptide::setParent(AminoAcidPolymer *value) {
            privateParent = value;
        }
        
        Residue *Peptide::getPreviousResidue() const {
            return privatePreviousResidue;
        }
        
        void Peptide::setPreviousResidue(Residue *value) {
            privatePreviousResidue = value;
        }
        
        Residue *Peptide::getNextResidue() const {
            return privateNextResidue;
        }
        
        void Peptide::setNextResidue(Residue *value) {
            privateNextResidue = value;
        }
        
        std::vector<Peptide*> Peptide::GenerateAllModificationCombinations() {
            // Get all the modifications that are isotopologues
            auto is = GetUniqueModifications<ModificationWithMultiplePossibilitiesCollection*>();
            std::vector<ModificationWithMultiplePossibilitiesCollection*> isotopologues(is.begin(), is.end());
            std::vector<Peptide*> res;
            
            // Base condition, no more isotopologues to make, so just return
            if (isotopologues.size() < 1) {
                return res;
            }
            
            // Grab the the first isotopologue
            ModificationWithMultiplePossibilitiesCollection *isotopologue = isotopologues[0];
            
            // Loop over each modification in the isotopologue
            // for (auto mod : isotopologue) {
            for ( int i =0; i< isotopologue->getCount(); i++ ) {
                auto mod = isotopologues[i];
                
                // Create a clone of the peptide, cloning modifications as well.
                Peptide *peptide = new Peptide(this);
                
                // Replace the base isotopologue mod with the specific version
                peptide->ReplaceModification(isotopologue, mod);
                
                // There were more than one isotopologue, so we must go deeper
                if (isotopologues.size() > 1) {
                    // Call the same rotuine on the newly generate peptide that has one less isotopologue
                    for (auto subpeptide : peptide->GenerateAllModificationCombinations()) {
                        res.push_back(subpeptide);
                    }
                }
                else {
                    // Return this peptide
                    res.push_back(peptide);
                }
                
                delete peptide;
            }
            return res;
        }
        
        Peptide *Peptide::GetSubPeptide(int firstResidue, int length) {
            return new Peptide(this, firstResidue, length);
        }
    }
}
