﻿/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#include "ProteinXmlEntry.h"
#include "../Proteomics/Protein/ProteolysisProduct.h"
#include "../Proteomics/Protein/SequenceVariation.h"
#include "../Proteomics/Protein/DisulfideBond.h"
#include "../Proteomics/Protein/SpliceSite.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Protein/DatabaseReference.h"
#include "../Proteomics/Protein/Protein.h"
#include "ProteinDbLoader.h"
#include "../Proteomics/Modifications/ModificationMotif.h"

using namespace Proteomics;

namespace UsefulProteomicsDatabases
{

	std::regex *const ProteinXmlEntry::SubstituteWhitespace = new std::regex(R"(\s+)");

	std::string ProteinXmlEntry::getAccession() const
	{
		return privateAccession;
	}

	void ProteinXmlEntry::setAccession(const std::string &value)
	{
		privateAccession = value;
	}

	std::string ProteinXmlEntry::getName() const
	{
		return privateName;
	}

	void ProteinXmlEntry::setName(const std::string &value)
	{
		privateName = value;
	}

	std::string ProteinXmlEntry::getFullName() const
	{
		return privateFullName;
	}

	void ProteinXmlEntry::setFullName(const std::string &value)
	{
		privateFullName = value;
	}

	std::string ProteinXmlEntry::getOrganism() const
	{
		return privateOrganism;
	}

	void ProteinXmlEntry::setOrganism(const std::string &value)
	{
		privateOrganism = value;
	}

	std::string ProteinXmlEntry::getSequence() const
	{
		return privateSequence;
	}

	void ProteinXmlEntry::setSequence(const std::string &value)
	{
		privateSequence = value;
	}

	std::string ProteinXmlEntry::getFeatureType() const
	{
		return privateFeatureType;
	}

	void ProteinXmlEntry::setFeatureType(const std::string &value)
	{
		privateFeatureType = value;
	}

	std::string ProteinXmlEntry::getFeatureDescription() const
	{
		return privateFeatureDescription;
	}

	void ProteinXmlEntry::setFeatureDescription(const std::string &value)
	{
		privateFeatureDescription = value;
	}

	std::string ProteinXmlEntry::getSubFeatureType() const
	{
		return privateSubFeatureType;
	}

	void ProteinXmlEntry::setSubFeatureType(const std::string &value)
	{
		privateSubFeatureType = value;
	}

	std::string ProteinXmlEntry::getSubFeatureDescription() const
	{
		return privateSubFeatureDescription;
	}

	void ProteinXmlEntry::setSubFeatureDescription(const std::string &value)
	{
		privateSubFeatureDescription = value;
	}

	std::string ProteinXmlEntry::getOriginalValue() const
	{
		return privateOriginalValue;
	}

	void ProteinXmlEntry::setOriginalValue(const std::string &value)
	{
		privateOriginalValue = value;
	}

	std::string ProteinXmlEntry::getVariationValue() const
	{
		return privateVariationValue;
	}

	void ProteinXmlEntry::setVariationValue(const std::string &value)
	{
		privateVariationValue = value;
	}

	std::string ProteinXmlEntry::getDBReferenceType() const
	{
		return privateDBReferenceType;
	}

	void ProteinXmlEntry::setDBReferenceType(const std::string &value)
	{
		privateDBReferenceType = value;
	}

	std::string ProteinXmlEntry::getDBReferenceId() const
	{
		return privateDBReferenceId;
	}

	void ProteinXmlEntry::setDBReferenceId(const std::string &value)
	{
		privateDBReferenceId = value;
	}

	std::vector<std::string> ProteinXmlEntry::getPropertyTypes() const
	{
		return privatePropertyTypes;
	}

	void ProteinXmlEntry::setPropertyTypes(const std::vector<std::string> &value)
	{
		privatePropertyTypes = value;
	}

	std::vector<std::string> ProteinXmlEntry::getPropertyValues() const
	{
		return privatePropertyValues;
	}

	void ProteinXmlEntry::setPropertyValues(const std::vector<std::string> &value)
	{
		privatePropertyValues = value;
	}

	int ProteinXmlEntry::getOneBasedFeaturePosition() const
	{
		return privateOneBasedFeaturePosition;
	}

	void ProteinXmlEntry::setOneBasedFeaturePosition(int value)
	{
		privateOneBasedFeaturePosition = value;
	}

	int ProteinXmlEntry::getOneBasedFeatureSubPosition() const
	{
		return privateOneBasedFeatureSubPosition;
	}

	void ProteinXmlEntry::setOneBasedFeatureSubPosition(int value)
	{
		privateOneBasedFeatureSubPosition = value;
	}

	std::optional<int> ProteinXmlEntry::getOneBasedBeginPosition() const
	{
		return privateOneBasedBeginPosition;
	}

	void ProteinXmlEntry::setOneBasedBeginPosition(const std::optional<int> &value)
	{
		privateOneBasedBeginPosition = value;
	}

	std::optional<int> ProteinXmlEntry::getOneBasedEndPosition() const
	{
		return privateOneBasedEndPosition;
	}

	void ProteinXmlEntry::setOneBasedEndPosition(const std::optional<int> &value)
	{
		privateOneBasedEndPosition = value;
	}

	std::vector<ProteolysisProduct*> ProteinXmlEntry::getProteolysisProducts() const
	{
		return privateProteolysisProducts;
	}

	void ProteinXmlEntry::setProteolysisProducts(const std::vector<ProteolysisProduct*> &value)
	{
		privateProteolysisProducts = value;
	}

	std::vector<SequenceVariation*> ProteinXmlEntry::getSequenceVariations() const
	{
		return privateSequenceVariations;
	}

	void ProteinXmlEntry::setSequenceVariations(const std::vector<SequenceVariation*> &value)
	{
		privateSequenceVariations = value;
	}

	std::vector<DisulfideBond*> ProteinXmlEntry::getDisulfideBonds() const
	{
		return privateDisulfideBonds;
	}

	void ProteinXmlEntry::setDisulfideBonds(const std::vector<DisulfideBond*> &value)
	{
		privateDisulfideBonds = value;
	}

	std::vector<SpliceSite*> ProteinXmlEntry::getSpliceSites() const
	{
		return privateSpliceSites;
	}

	void ProteinXmlEntry::setSpliceSites(const std::vector<SpliceSite*> &value)
	{
		privateSpliceSites = value;
	}

	std::unordered_map<int, std::vector<Modification*>> ProteinXmlEntry::getOneBasedModifications() const
	{
		return privateOneBasedModifications;
	}

	void ProteinXmlEntry::setOneBasedModifications(const std::unordered_map<int, std::vector<Modification*>> &value)
	{
		privateOneBasedModifications = value;
	}

	std::unordered_map<int, std::vector<Modification*>> ProteinXmlEntry::getOneBasedVariantModifications() const
	{
		return privateOneBasedVariantModifications;
	}

	void ProteinXmlEntry::setOneBasedVariantModifications(const std::unordered_map<int, std::vector<Modification*>> &value)
	{
		privateOneBasedVariantModifications = value;
	}

	std::vector<std::tuple<std::string, std::string>> ProteinXmlEntry::getGeneNames() const
	{
		return privateGeneNames;
	}

	void ProteinXmlEntry::setGeneNames(const std::vector<std::tuple<std::string, std::string>> &value)
	{
		privateGeneNames = value;
	}

	std::vector<DatabaseReference*> ProteinXmlEntry::getDatabaseReferences() const
	{
		return privateDatabaseReferences;
	}

	void ProteinXmlEntry::setDatabaseReferences(const std::vector<DatabaseReference*> &value)
	{
		privateDatabaseReferences = value;
	}

	bool ProteinXmlEntry::getReadingGene() const
	{
		return privateReadingGene;
	}

	void ProteinXmlEntry::setReadingGene(bool value)
	{
		privateReadingGene = value;
	}

	bool ProteinXmlEntry::getReadingOrganism() const
	{
		return privateReadingOrganism;
	}

	void ProteinXmlEntry::setReadingOrganism(bool value)
	{
		privateReadingOrganism = value;
	}

	void ProteinXmlEntry::ParseElement(const std::string &elementName, xmlTextReaderPtr *xml)
	{
		int outValue;
		xmlChar *delXmlChar1, *delXmlChar2, *delXmlChar3, *delXmlChar4, *delXmlChar5;
		if (elementName == "accession")
		{
			if (getAccession() == "")
			{
                                auto delXmlChar1 = xmlTextReaderReadString(*xml);
                                if ( delXmlChar1 != nullptr ) {
                                    setAccession((char *)delXmlChar1);
                                    xmlFree(delXmlChar1);
                                }
			}

		}
		else if (elementName == "name")
		{
			if (xmlTextReaderDepth(*xml) == 2 && !getReadingGene() && !getReadingOrganism())
			{
                                auto delXmlChar1 = xmlTextReaderReadString(*xml);
                                if ( delXmlChar1 != nullptr ) {
                                    setName((char *)delXmlChar1);
                                    xmlFree(delXmlChar1);
                                }				
			}
			if (getReadingGene() && !getReadingOrganism())
			{
				getGeneNames().push_back(std::tuple<std::string, std::string>(std::string((char *) xmlTextReaderGetAttribute(*xml, (xmlChar*)"type")), (char *)xmlTextReaderReadString(*xml)));
			}
			if (getReadingOrganism())
			{
				if (std::string((char *) (delXmlChar1 = xmlTextReaderGetAttribute(*xml, (xmlChar*)"type"))) == "scientific")
				{
					setOrganism((char *) (delXmlChar2 = xmlTextReaderReadString(*xml)));
					xmlFree(delXmlChar2);
				}
				xmlFree(delXmlChar1);
			}

		}
		else if (elementName == "gene")
		{
			setReadingGene(true);

		}
		else if (elementName == "organism")
		{
			if (getOrganism() == "")
			{
				setReadingOrganism(true);
			}

		}
		else if (elementName == "fullName")
		{
			if (getFullName() == "")
			{
                                auto delXmlChar1 = xmlTextReaderReadString(*xml);
                                if ( delXmlChar1 != nullptr ) {
                                    setFullName((char *) delXmlChar1);
                                    xmlFree(delXmlChar1);
                                }
			}

		}
		else if (elementName == "feature")
		{
                    auto delXmlChar1 = xmlTextReaderGetAttribute(*xml, (xmlChar*)"type");
                    if ( delXmlChar1 != nullptr ) {
			setFeatureType(std::string((char *) delXmlChar1));
                        xmlFree(delXmlChar1);
                    }
                    auto delXmlChar2 = xmlTextReaderGetAttribute(*xml, (xmlChar*)"description");
                    if ( delXmlChar2 != nullptr ) {
                        setFeatureDescription(std::string((char*)delXmlChar2));
                        xmlFree(delXmlChar2);
                    }
		}
		else if (elementName == "subfeature")
		{
                        auto delXmlChar1 = xmlTextReaderGetAttribute(*xml, (xmlChar*)"type");
                        if ( delXmlChar1 != nullptr ) {
                            setSubFeatureType(std::string((char *) delXmlChar1));
                            xmlFree(delXmlChar1);
                        }
                        auto delXmlChar2 = xmlTextReaderGetAttribute(*xml, (xmlChar*)"description");
                        if ( delXmlChar2 != nullptr ) {
                            setSubFeatureDescription(std::string((char*) delXmlChar2));
                            xmlFree(delXmlChar2);
                        }
		}
		else if (elementName == "original")
		{
                        auto delXmlChar1 = xmlTextReaderReadString(*xml);
                        if ( delXmlChar1 != nullptr ) {
                            setOriginalValue((char *)delXmlChar1 );
                            xmlFree(delXmlChar1);
                        }

		}
		else if (elementName == "variation")
		{
                        auto delXmlChar1 = xmlTextReaderReadString(*xml);
                        if ( delXmlChar1 != nullptr ) {
                            setVariationValue((char *)delXmlChar1);
                            xmlFree(delXmlChar1);
                        }
		}
		else if (elementName == "dbReference")
		{
			getPropertyTypes().clear();
			getPropertyValues().clear();

                        auto delXmlChar1 = xmlTextReaderGetAttribute(*xml, (xmlChar*)"type");
                        if ( delXmlChar1 != nullptr ) {
                            setDBReferenceType(std::string((char *) delXmlChar1 ));
                            xmlFree(delXmlChar1);
                        }
                        auto delXmlChar2 = xmlTextReaderGetAttribute(*xml, (xmlChar*)"id");
                        if ( delXmlChar2 != nullptr ) {
                            setDBReferenceId(std::string((char*)delXmlChar2 ));
                            xmlFree(delXmlChar2);
                        }
		}
		else if (elementName == "property")
		{
                        auto delXmlChar1 = xmlTextReaderGetAttribute(*xml, (xmlChar*)"type");
                        if ( delXmlChar1 != nullptr ) {
                            getPropertyTypes().push_back(std::string((char *) delXmlChar1 ));
                            xmlFree(delXmlChar1);
                        }
                        auto delXmlChar2 = xmlTextReaderGetAttribute(*xml, (xmlChar*)"value");
                        if ( delXmlChar2 != nullptr ) {
                            getPropertyValues().push_back(std::string((char *) delXmlChar2 ));
                            xmlFree(delXmlChar2);
                        }
		}
		else if (elementName == "position")
		{
                        auto delXmlChar1 = xmlTextReaderGetAttribute(*xml, (xmlChar*)"position");
                        if ( delXmlChar1 != nullptr ) {
                            setOneBasedFeaturePosition(std::stoi(std::string((char *) delXmlChar1 )));
                            xmlFree(delXmlChar1);
                        }

		}
		else if (elementName == "subposition")
		{
                        auto delXmlChar1 = xmlTextReaderGetAttribute(*xml, (xmlChar*)"subposition");
                        if ( delXmlChar1 != nullptr ) {
                            setOneBasedFeatureSubPosition(std::stoi(std::string((char *) delXmlChar1 )));
                            xmlFree(delXmlChar1);
                        }
		}
		else if (elementName == "begin")
		{
			// setOneBasedBeginPosition(int::TryParse(std::string((char *) xmlTextReaderGetAttribute(*xml, (xmlChar*)"position")), outValue) ? static_cast<std::optional<int>>(outValue): nullptr);
                        auto delXmlChar1 = xmlTextReaderGetAttribute(*xml, (xmlChar*) "position");
                        std::string positionStringToInt;
                        bool isAllInt = true;
                        if ( delXmlChar1 != nullptr ) {
                            positionStringToInt = std::string((char *)(delXmlChar1 ));
                            xmlFree(delXmlChar1);
                        }
                        else {
                            isAllInt = false;
                        }
                        
			for (const char& it : positionStringToInt) {
				if (!std::isdigit(it)) {
					isAllInt = false;
					break;
				}
			}


			setOneBasedBeginPosition(isAllInt ? static_cast<std::optional<int>>(std::stoi(positionStringToInt)) : std::nullopt);
		}
		else if (elementName == "end")
		{
			// setOneBasedEndPosition(int::TryParse(std::string((char *) xmlTextReaderGetAttribute(*xml, (xmlChar*)"position")), outValue) ? static_cast<std::optional<int>>(outValue): nullptr);

                        auto delXmlChar1 = xmlTextReaderGetAttribute(*xml, (xmlChar*) "position");
			std::string positionStringToInt = std::string((char *)(delXmlChar1));
			bool isAllInt = true;
                        if ( delXmlChar1 != nullptr ) {
                            positionStringToInt = std::string((char *)(delXmlChar1));
                            xmlFree(delXmlChar1);
                        }
                        else {
                            isAllInt = false;
                        }
			for (const char& it : positionStringToInt) {
				if (!std::isdigit(it)) {
					isAllInt = false;
					break;
				}
			}

			setOneBasedEndPosition(isAllInt ? static_cast<std::optional<int>>(std::stoi(positionStringToInt)) : std::nullopt);
		}
		else if (elementName == "sequence")
		{
			//setSequence(SubstituteWhitespace->Replace((char *)xmlTextReaderReadString(*xml), ""));
                        auto delXmlChar1 = xmlTextReaderReadString(*xml);
                        if ( delXmlChar1 != nullptr )  {
                            setSequence(std::regex_replace((char *)(delXmlChar1), *SubstituteWhitespace, ""));
                            xmlFree(delXmlChar1);
                        }
                        else {
                            setSequence ("");
                        }
		}
	}

	Protein *ProteinXmlEntry::ParseEndElement(xmlTextReaderPtr *xml, std::vector<std::string> &modTypesToExclude,
                                                  std::unordered_map<std::string, Modification*> &unknownModifications,
                                                  bool isContaminant, const std::string &proteinDbLocation)
	{
		Protein *protein = nullptr;
		xmlChar *delXmlChar1;
		char* Name = (char*) (delXmlChar1 = xmlTextReaderName(*xml));

		if (std::string(Name) == "feature")
		{
			ParseFeatureEndElement(xml, modTypesToExclude, unknownModifications);
		}
		if (std::string(Name) == "subfeature")
		{
			ParseSubFeatureEndElement(xml, modTypesToExclude, unknownModifications);
		}
		else if (std::string(Name) == "dbReference")
		{
			ParseDatabaseReferenceEndElement(xml);
		}
		else if (std::string(Name) == "gene")
		{
			setReadingGene(false);
		}
		else if (std::string(Name) == "organism")
		{
			setReadingOrganism(false);
		}
		else if (std::string(Name) == "entry")
		{
			protein = ParseEntryEndElement(xml, isContaminant, proteinDbLocation, modTypesToExclude, unknownModifications);
		}

		xmlFree(delXmlChar1);
		return protein;
	}

	Protein *ProteinXmlEntry::ParseEntryEndElement(xmlTextReaderPtr *xml, bool isContaminant,
                                                       const std::string &proteinDbLocation,
                                                       std::vector<std::string> &modTypesToExclude,
                                                       std::unordered_map<std::string, Modification*> &unknownModifications)
	{
		Protein *result = nullptr;
		if (getAccession() != "" && getSequence() != "")
		{
			ParseAnnotatedMods(privateOneBasedModifications, modTypesToExclude, unknownModifications, AnnotatedMods);
			//	result = new Protein(getSequence(), getAccession(), getOrganism(), getGeneNames(), getOneBasedModifications(), getProteolysisProducts(), getName(), getFullName(), false, isContaminant, getDatabaseReferences(), getSequenceVariations(), std::vector<SequenceVariation>(), "", getDisulfideBonds(), getSpliceSites(), proteinDbLocation);
			std::vector<SequenceVariation*> tempAppliedSequenceVariations = std::vector<SequenceVariation*>();
			std::string tempSampleNameForVariants = "";
			result = new Protein(privateSequence, privateAccession, privateOrganism, 
					privateGeneNames, 
					privateOneBasedModifications, 
					privateProteolysisProducts,
					privateName, privateFullName,
					false, isContaminant, 
					privateDatabaseReferences,
					privateSequenceVariations, tempAppliedSequenceVariations,
					tempSampleNameForVariants,
					privateDisulfideBonds,
					privateSpliceSites,
					proteinDbLocation);
		}
		Clear();
		return result;
	}

	void ProteinXmlEntry::ParseSubFeatureEndElement(xmlTextReaderPtr *xml, std::vector<std::string> &modTypesToExclude,
                                                        std::unordered_map<std::string, Modification*> &unknownModifications)
	{
		if (getSubFeatureType() == "modified residue")
		{
			setSubFeatureDescription(StringHelper::split(getSubFeatureDescription(), ';')[0]);
			AnnotatedVariantMods.push_back( new std::tuple<int, std::string>(privateOneBasedFeatureSubPosition, privateSubFeatureDescription));
		}
	}

	void ProteinXmlEntry::ParseFeatureEndElement(xmlTextReaderPtr *xml, std::vector<std::string> &modTypesToExclude,
                                                     std::unordered_map<std::string, Modification*> &unknownModifications)
	{
		if (privateFeatureType == "modified residue")
		{
			setFeatureDescription(StringHelper::split(getFeatureDescription(), ';')[0]);
			AnnotatedMods.push_back(new std::tuple<int, std::string> (getOneBasedFeaturePosition(), getFeatureDescription()));
		}
		else if (getFeatureType() == "peptide" || getFeatureType() == "propeptide" ||
                         getFeatureType() == "chain" || getFeatureType() == "signal peptide")
		{
			ProteolysisProduct tempVar(getOneBasedBeginPosition(), getOneBasedEndPosition(), getFeatureType());
			getProteolysisProducts().push_back(&tempVar);
		}
		else if (getFeatureType() == "sequence variant" && getVariationValue() != "" && getVariationValue() != "") 
		{
                        // Only keep if there is variant sequence information and position information
			ParseAnnotatedMods(privateOneBasedVariantModifications, modTypesToExclude, unknownModifications, AnnotatedVariantMods);
			if (getOneBasedBeginPosition() && getOneBasedEndPosition())
			{
                                 auto tempVar2 = new SequenceVariation(getOneBasedBeginPosition().value(), getOneBasedEndPosition().value(),
                                                                       getOriginalValue(), getVariationValue(), getFeatureDescription(),
                                                                       getOneBasedVariantModifications());
				getSequenceVariations().push_back(tempVar2);
			}
			else if (getOneBasedFeaturePosition() >= 1)
			{
				auto tempVar3 = new SequenceVariation(getOneBasedFeaturePosition(), getOriginalValue(), getVariationValue(),
                                                                      getFeatureDescription(), getOneBasedVariantModifications());
				getSequenceVariations().push_back(tempVar3);
			}
			AnnotatedVariantMods = std::vector<std::tuple<int, std::string>*>();
		}
		else if (getFeatureType() == "disulfide bond")
		{
			if (getOneBasedBeginPosition() && getOneBasedEndPosition())
			{
                                auto tempVar4 = new DisulfideBond (getOneBasedBeginPosition().value(), getOneBasedEndPosition().value(),
                                                                   getFeatureDescription());
				getDisulfideBonds().push_back(tempVar4);
			}
			else if (getOneBasedFeaturePosition() >= 1)
			{
				auto tempVar5 = new DisulfideBond (getOneBasedFeaturePosition(), getFeatureDescription());
				getDisulfideBonds().push_back(tempVar5);
			}
		}
		else if (getFeatureType() == "splice site")
		{
			if (getOneBasedBeginPosition() && getOneBasedEndPosition())
			{
				auto tempVar6 = new SpliceSite (getOneBasedBeginPosition().value(), getOneBasedEndPosition().value(),
                                                                getFeatureDescription());
				getSpliceSites().push_back(tempVar6);
			}
			else if (getOneBasedFeaturePosition() >= 1)
			{
				auto tempVar7 = new SpliceSite (getOneBasedFeaturePosition(), getFeatureDescription());
				getSpliceSites().push_back(tempVar7);
			}
		}
		setOneBasedBeginPosition(std::nullopt);
		setOneBasedEndPosition(std::nullopt);
		setOneBasedFeaturePosition(-1);
		setOriginalValue("");
		setVariationValue("");
	}

	void ProteinXmlEntry::ParseAnnotatedMods(std::unordered_map<int, std::vector<Modification*>> &destination,
                                                 std::vector<std::string> &modTypesToExclude,
                                                 std::unordered_map<std::string, Modification*> &unknownModifications,
                                                 std::vector<std::tuple<int, std::string>*> &annotatedMods)
	{
		for (auto annotatedMod : annotatedMods)
		{
			std::string annotatedId = std::get<1>(*annotatedMod);
			int annotatedModLocation = std::get<0>(*annotatedMod);

			Modification *foundMod;
			if (ProteinDbLoader::IdWithMotifToMod.find(annotatedId) != ProteinDbLoader::IdWithMotifToMod.end())
			{
				foundMod = ProteinDbLoader::IdWithMotifToMod.at(annotatedId);
				// if the list of known mods contains this IdWithMotif
				if (std::find(modTypesToExclude.begin(), modTypesToExclude.end(), foundMod->getModificationType()) == modTypesToExclude.end())
				{
					std::vector<Modification*> listOfModsAtThisLocation;

					if (destination.find(annotatedModLocation) != destination.end())
					{
						destination.at(annotatedModLocation).push_back(new Modification(*foundMod));
					}
					else
					{
						destination.emplace(annotatedModLocation, std::vector<Modification*> {foundMod});
					}
				}
				// else - the mod ID was found but the motif didn't fit the annotated location
			}

			// no known mod - try looking it up in the dictionary of mods without motif appended
			else
			{
				// foundMod = ProteinDbLoader::IdWithMotifToMod.at(annotatedId);
				std::vector<Modification*> mods;
				if (ProteinDbLoader::IdToPossibleMods.find(annotatedId) != ProteinDbLoader::IdToPossibleMods.end())
				{
					mods = ProteinDbLoader::IdToPossibleMods.at(annotatedId);
					for (Modification *mod : mods)
					{
						if (std::find(modTypesToExclude.begin(), modTypesToExclude.end(), mod->getModificationType()) == modTypesToExclude.end())
						{
							// TValue listOfModsAtThisLocation;

							if (destination.find(annotatedModLocation) != destination.end())
							{
								destination.at(annotatedModLocation).push_back(new Modification(*mod));
							}
							else
							{
								destination.emplace(annotatedModLocation, std::vector<Modification*> {mod});
							}
							break;
						}
					}
				}
				else
				{
					// could not find the annotated mod's ID in our list of known mods - it's an unknown mod
					// I don't think this really does anything...
					if (unknownModifications.find(annotatedId) == unknownModifications.end())
					{
						auto tempVar = new Modification (annotatedId);
						unknownModifications.emplace(annotatedId, tempVar);
					}
				}
			}
		}
	}

	ModificationMotif *ProteinXmlEntry::GetMotif(const std::string &proteinSequence, int position)
	{
		std::string aminoAcid = proteinSequence.substr(position - 1, 1);
		ModificationMotif *motif;
		if (ModificationMotif::TryGetMotif(aminoAcid, &motif))
		{
			return motif;
		}
		else
		{
			return nullptr;
		}
	}

	void ProteinXmlEntry::ParseDatabaseReferenceEndElement(xmlTextReaderPtr *xml)
	{
		/*DatabaseReference tempVar(getDBReferenceType(), getDBReferenceId(), Enumerable::Range(0, getPropertyTypes().size())->Select([&] (std::any i)
		  {
		  return std::tuple < std::string;
		  }, std::string > (getPropertyTypes()[i], getPropertyValues()[i])).ToList());*/

		std::vector<std::tuple<std::string, std::string>> tempProperties;
		for (int i = 0; i < getPropertyTypes().size(); i++) {
			tempProperties.push_back(std::tuple<std::string, std::string>(privatePropertyTypes[i], privatePropertyTypes[i]));
		}

		auto tempVar = new DatabaseReference (getDBReferenceType(), getDBReferenceId(), tempProperties);
		//getDatabaseReferences().push_back(&tempVar);
		privateDatabaseReferences.push_back(tempVar);
		setPropertyTypes(std::vector<std::string>());
		setPropertyValues(std::vector<std::string>());
		setDBReferenceType("");
		setDBReferenceId("");
	}
	
	void ProteinXmlEntry::Clear()
	{
		// SHANE: Unknown if needed. 
		// Probably not needed as program is based off of shallow copies rather than deep copies.
		// destructor();

		setAccession("");
		setName("");
		setFullName("");
		setSequence("");
		setOrganism("");
		setFeatureType("");
		setFeatureDescription("");
		setSubFeatureType("");
		setSubFeatureDescription("");
		setOriginalValue("");
		setVariationValue("");
		setDBReferenceType("");
		setDBReferenceId("");
		setPropertyTypes(std::vector<std::string>());
		setPropertyValues(std::vector<std::string>());
		setOneBasedFeaturePosition(-1);
		setOneBasedFeatureSubPosition(-1);
		AnnotatedMods = std::vector<std::tuple<int, std::string>*>();
		setOneBasedModifications(std::unordered_map<int, std::vector<Modification*>>());
		setProteolysisProducts(std::vector<ProteolysisProduct*>());
		setSequenceVariations(std::vector<SequenceVariation*>());
		setDisulfideBonds(std::vector<DisulfideBond*>());
		setSpliceSites(std::vector<SpliceSite*>());
		setDatabaseReferences(std::vector<DatabaseReference*>());
		setGeneNames(std::vector<std::tuple<std::string, std::string>>());
		setReadingGene(false);
		setReadingOrganism(false);
	}
}
