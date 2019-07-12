﻿#pragma once

#include "VariantApplication.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace Proteomics { class Modification; }
#include "../Modifications/Modification.h"
//namespace Proteomics { class SequenceVariation; }
#include "SequenceVariation.h"
//namespace Proteomics { class DisulfideBond; }
#include "DisulfideBond.h"
//namespace Proteomics { class SpliceSite; }
#include "SpliceSite.h"
//namespace Proteomics { class ProteolysisProduct; }
#include "ProteolysisProduct.h"
//namespace Proteomics { class DatabaseReference; }
#include "DatabaseReference.h"

//using namespace Proteomics::ProteolyticDigestion;
#include "../ProteolyticDigestion/PeptideWithSetModifications.h"

namespace Proteomics
{
    class Protein
    {
    private:
        std::unordered_map<int, std::vector<Modification*>> privateOneBasedPossibleLocalizedModifications;
        std::vector<std::tuple<std::string, std::string>> privateGeneNames;
        std::string privateAccession;
        std::string privateBaseSequence;
        std::string privateOrganism;
        bool privateIsDecoy = false;
        std::vector<SequenceVariation*> privateSequenceVariations;
        std::vector<DisulfideBond*> privateDisulfideBonds;
        std::vector<SpliceSite*> privateSpliceSites;
        std::vector<ProteolysisProduct*> privateProteolysisProducts;
        std::vector<DatabaseReference*> privateDatabaseReferences;
        std::string privateDatabaseFilePath;
        Protein *privateNonVariantProtein;
        std::vector<SequenceVariation*> privateAppliedSequenceVariations;
        std::string privateSampleNameForVariants;
        std::string privateName;
        std::string privateFullName;
        bool privateIsContaminant = false;
        std::unordered_map<int, std::vector<Modification*>> privateOriginalNonVariantModifications;

        /// <summary>
        /// Protein. Filters out modifications that do not match their amino acid target site.
        /// </summary>
        /// <param name="sequence">Base sequence of the protein.</param>
        /// <param name="accession">Unique accession for the protein.</param>
        /// <param name="organism">Organism with this protein.</param>
        /// <param name="geneNames">List of gene names as tuple of (nameType, name), e.g. (primary, HLA-A)</param>
        /// <param name="oneBasedModifications">Modifications at positions along the sequence.</param>
        /// <param name="proteolysisProducts"></param>
        /// <param name="name"></param>
        /// <param name="fullName"></param>
        /// <param name="isDecoy"></param>
        /// <param name="isContaminant"></param>
        /// <param name="databaseReferences"></param>
        /// <param name="sequenceVariations"></param>
        /// <param name="disulfideBonds"></param>
        /// <param name="spliceSites"></param>
        /// <param name="databaseFilePath"></param>
    public:
        Protein(const std::string &sequence,
                const std::string &accession,
                const std::string &organism = "",
                std::vector<std::tuple<std::string, std::string>> &geneNames = std::vector<std::tuple<std::string, std::string>>(),
                std::unordered_map<int, std::vector<Modification*>> &oneBasedModifications = std::unordered_map<int, std::vector<Modification*>>(),
                std::vector<ProteolysisProduct*> &proteolysisProducts = std::vector<ProteolysisProduct*>(),
                const std::string &name = "",
                const std::string &fullName = "",
                bool isDecoy = false,
                bool isContaminant = false,
                std::vector<DatabaseReference*> &databaseReferences = std::vector<DatabaseReference*>(),
                std::vector<SequenceVariation*> &sequenceVariations = std::vector<SequenceVariation*>(),
                std::vector<SequenceVariation*> &appliedSequenceVariations = std::vector<SequenceVariation*>(),
                const std::string &sampleNameForVariants = "",
                std::vector<DisulfideBond*> &disulfideBonds = std::vector<DisulfideBond*>(),
                std::vector<SpliceSite*> &spliceSites = std::vector<SpliceSite*>(),
                const std::string &databaseFilePath = "");

#ifdef LATER
        /// <summary>
        /// Protein construction with applied variations
        /// </summary>
        /// <param name="variantBaseSequence"></param>
        /// <param name="protein"></param>
        /// <param name="appliedSequenceVariations"></param>
        /// <param name="applicableProteolysisProducts"></param>
        /// <param name="oneBasedModifications"></param>
        /// <param name="sampleNameForVariants"></param>
        Protein(std::string variantBaseSequence,
                Protein protein,
                std::vector<SequenceVariation*> appliedSequenceVariations,
                std::vector<ProteolysisProduct*> applicableProteolysisProducts,
                std::unordered_map<int, std::vector<Modification*>> oneBasedModifications,
                std::string sampleNameForVariants) :
        this( variantBaseSequence,
              VariantApplication::GetAccession(protein, appliedSequenceVariations),
              organism: protein::Organism,
              geneNames: std::vector<std::tuple<std::string,
              std::string>>(protein::GeneNames),
              oneBasedModifications: oneBasedModifications != nullptr ? oneBasedModifications::ToDictionary([&] (std::any x)
                                                                                                            {
                                                                                                                x::Key;
                                                                                                            }, [&] (std::any x)
                                                                                                            {
                                                                                                                x->Value;
                                                                                                            }) :
              std::unordered_map<int, std::vector<Modification*>>(),
              proteolysisProducts: std::vector<ProteolysisProduct*>((applicableProteolysisProducts != nullptr) ? applicableProteolysisProducts : std::vector<ProteolysisProduct*>()),
              name: GetName(appliedSequenceVariations, protein->Name),
              fullName: GetName(appliedSequenceVariations, protein->FullName),
              isDecoy: protein::IsDecoy,
              isContaminant: protein::IsContaminant,
              databaseReferences: std::vector<DatabaseReference*>(protein::DatabaseReferences),
              sequenceVariations: std::vector<SequenceVariation*>(protein::SequenceVariations),
              disulfideBonds: std::vector<DisulfideBond*>(protein::DisulfideBonds),
              spliceSites: std::vector<SpliceSite*>(protein::SpliceSites),
              databaseFilePath: protein::DatabaseFilePath) {
            NonVariantProtein = protein::NonVariantProtein;
            setOriginalNonVariantModifications(getNonVariantProtein()->getOriginalNonVariantModifications());
            AppliedSequenceVariations = ((appliedSequenceVariations != nullptr) ? appliedSequenceVariations : std::vector<SequenceVariation*>())->ToList();
            SampleNameForVariants = sampleNameForVariants;
        };
#endif
        
        /// <summary>
        /// Modifications (values) located at one-based protein positions (keys)
        /// </summary>
        // get private set
        std::unordered_map<int, std::vector<Modification*>> getOneBasedPossibleLocalizedModifications () const;


        /// <summary>
        /// The list of gene names consists of tuples, where Item1 is the type of gene name, and Item2 is the name.
        /// There may be many genes and names of a certain type produced when reading an XML protein database.
        /// </summary>
        // get
        std::vector<std::tuple<std::string, std::string>> getGeneNames() const;

        /// <summary>
        /// Unique accession for this protein.
        /// </summary>
        // get
        std::string getAccession() const;

        /// <summary>
        /// Base sequence, which may contain applied sequence variations.
        /// </summary>
        // get
        std::string getBaseSequence () const;

        // get
        std::string getOrganism () const;

        // get
        bool getIsDecoy() const;

        //get
        std::vector<SequenceVariation*> getSequenceVariations () const;

        //get
        std::vector<DisulfideBond*> getDisulfideBonds() const;

        //get
        std::vector<SpliceSite*> getSpliceSites() const;

        //get
        std::vector<ProteolysisProduct*>  getProteolysisProducts() const;

        //get
        std::vector<DatabaseReference*> getDatabaseReferences() const;

        //get
        std::string getDatabaseFilePath() const;

        /// <summary>
        /// Protein before applying variations.
        /// </summary>
        // get
        Protein* getNonVariantProtein() const;

        /// <summary>
        /// Sequence variations that have been applied to the base sequence.
        /// </summary>
        // get
        std::vector<SequenceVariation*> getAppliedSequenceVariations() const;

        
        /// <summary>
        /// Sample name from which applied variants came, e.g. tumor or normal.
        /// </summary>
        //get
        std::string getSampleNameForVariants() const;

        int getLength() const;
        std::string getFullDescription() const;

        //get
        std::string getName () const;

        //get
        std::string getFullName() const;

        //get
        bool getIsContaminant() const;

        //get, set
        std::unordered_map<int, std::vector<Modification*>>  getOriginalNonVariantModifications() const;
        void setOriginalNonVariantModifications( std::unordered_map<int, std::vector<Modification*>> &value);

#ifdef LATER
        //C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public char this[int zeroBasedIndex]
        {
            char get(int zeroBasedIndex);
        }
#endif

        /// <summary>
        /// Formats a string for a UniProt fasta header. See https://www.uniprot.org/help/fasta-headers.
        /// Note that the db field isn't very applicable here, so mz is placed in to denote written by mzLib.
        /// </summary>
        std::string GetUniProtFastaHeader();

        /// <summary>
        /// Formats a string for an ensembl header
        /// </summary>
        std::string GetEnsemblFastaHeader();

        /// <summary>
        /// The protein object uses the default equals method for speed, 
        /// but note that two protein objects with the same information will not be equal by this method.
        /// </summary>
        /// <param name="obj"></param>
        /// <returns></returns>
        bool Equals(Protein *obj);

        /// <summary>
        /// The protein object uses the default hash code method for speed, 
        /// but note that two protein objects with the same information will give two different hash codes.
        /// </summary>
        /// <returns></returns>
        int GetHashCode();

        /// <summary>
        /// Gets peptides for digestion of a protein
        /// </summary>
        std::vector<PeptideWithSetModifications* > Digest(Proteomics::ProteolyticDigestion::DigestionParams digestionParams,
                                                          std::vector<Modification*> allKnownFixedModifications,
                                                          std::vector<Modification*> variableModifications);

        /// <summary>
        /// Gets proteins with applied variants from this protein
        /// </summary>
        std::vector<Protein *> GetVariantProteins(int maxAllowedVariantsForCombinitorics = 4, int minAlleleDepth = 1);

        /// <summary>
        /// Restore all modifications that were read in, including those that did not match their target amino acid.
        /// </summary>
        void RestoreUnfilteredModifications();

        /// <summary>
        /// Filters modifications that do not match their target amino acid.
        /// </summary>
        /// <param name="dict"></param>
        /// <returns></returns>

    private:
        void setOneBasedPossibleLocalizedModifications ( const std::unordered_map<int, std::vector<Modification*>> &value);
        std::unordered_map<int, std::vector<Modification*>> SelectValidOneBaseMods( std::unordered_map<int, std::vector<Modification*>>  dict);
        std::string GetName(  std::vector<SequenceVariation*> appliedVariations, std::string name);
    };
}
