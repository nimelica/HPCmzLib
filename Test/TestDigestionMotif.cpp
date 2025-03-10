﻿#include "TestDigestionMotif.h"
#include "../Chemistry/Chemistry.h"
#include "../Proteomics/Proteomics.h"
//#include "../MzLibUtil/MzLibException.h"

#include <limits>
#include "MzLibAssert.h"

using namespace MzLibUtil;
using namespace Proteomics;
using namespace Proteomics::ProteolyticDigestion;

int main ( int argc, char **argv )
{

    int i=0;
    std::cout << i << ". PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    Chemistry::PeriodicTable::Load (elr);

    std::cout <<++i << ". TestParseProtease" << std::endl;    
    Test::TestDigestionMotif::TestParseProtease();

    std::cout <<++i << ". TestBasicProtease1" << std::endl;    
    Test::TestDigestionMotif::TestBasicProtease1();

    std::cout <<++i << ". TestBasicProtease2" << std::endl;    
    Test::TestDigestionMotif::TestBasicProtease2();

    std::cout <<++i << ". TestWildCardExclusion" << std::endl;    
    Test::TestDigestionMotif::TestWildCardExclusion();

    std::cout <<++i << ". TestMultiLetterProtease" << std::endl;    
    Test::TestDigestionMotif::TestMultiLetterProtease();

    std::cout <<++i << ". TestNTerminusProtease" << std::endl;    
    Test::TestDigestionMotif::TestNTerminusProtease();

#ifdef LATER
    // Tests for Exception handling
    std::cout <<++i << "TestSyntax" << std::endl;    
    Test::TestDigestionMotif::TestSyntax();
#endif
    return 0;
}

namespace Test
{

    void TestDigestionMotif::TestParseProtease()
    {
        auto argn = DigestionMotif::ParseDigestionMotifsFromString("|D");
        Assert::AreEqual( (int)argn.size(), 1);

        auto c = argn[0];
        std::string a = "D";
        Assert::AreEqual(c->InducingCleavage, a);
        Assert::AreEqual((int)c->PreventingCleavage.size(), 0);
        Assert::AreEqual(c->CutIndex, 0);

        auto chymotrypsin = DigestionMotif::ParseDigestionMotifsFromString("F[P]|,W[P]|,Y[P]|");
        Assert::AreEqual((int)chymotrypsin.size(), 3);
    }

    void TestDigestionMotif::TestBasicProtease1()
    {
        auto empty = std::vector<Modification*>();
        DigestionParams *myDigestionParams = new DigestionParams("trypsin", 0, 1, std::numeric_limits<int>::max(), 1024,
                                                                 InitiatorMethionineBehavior::Variable, 2,
                                                                 CleavageSpecificity::Full, FragmentationTerminus::Both);

        // create a protein
        Protein *myProtein = new Protein("PROTEIN", "myAccession");

        // digest it into peptides
        auto myPeptides = myProtein->Digest(myDigestionParams, empty, empty);
        std::string first = myPeptides.front()->ToString();
        std::string last =  myPeptides.back()->ToString();

        std::string a = "PR";
        std::string b = "OTEIN";
        
        Assert::AreEqual(first, a);
        Assert::AreEqual(last, b);

        delete myProtein;
        delete myDigestionParams;
    }

    void TestDigestionMotif::TestBasicProtease2()
    {
        auto empty = std::vector<Modification*>();
        DigestionParams *myDigestionParams = new DigestionParams("Lys-C (don't cleave before proline)", 0, 1,
                                                                 std::numeric_limits<int>::max(), 1024,
                                                                 InitiatorMethionineBehavior::Variable, 2,
                                                                 CleavageSpecificity::Full, FragmentationTerminus::Both);

        // create a protein
        Protein *myProtein = new Protein("MKPKPKPMKA", "myAccession");

        // digest it into peptides
        auto myPeptides = myProtein->Digest(myDigestionParams, empty, empty);
        std::string first = myPeptides.front()->ToString();
        std::string last = myPeptides.back()->ToString();

        std::string a = "MKPKPKPMK";
        std::string b = "A";
        Assert::AreEqual(first, a);
        Assert::AreEqual(last, b);

        delete myProtein;
        delete myDigestionParams;
    }

    void TestDigestionMotif::TestWildCardExclusion()
    {
        auto empty = std::vector<Modification*>();
        auto digestionmotifs = DigestionMotif::ParseDigestionMotifsFromString("RX{P}|");
        Protease *multiletter = new Protease("multiletter", CleavageSpecificity::Full, "", "", digestionmotifs);
        ProteaseDictionary::insert(multiletter->getName(), multiletter);

        DigestionParams *myDigestionParams = new DigestionParams("multiletter", 0, 1, std::numeric_limits<int>::max(),
                                                                 1024, InitiatorMethionineBehavior::Variable, 2,
                                                                 CleavageSpecificity::Full, FragmentationTerminus::Both);

        // create a protein
        Protein *myProtein = new Protein("PROPRPPM", "myAccession");

        // digest it into peptides
        auto myPeptides = myProtein->Digest(myDigestionParams, empty, empty);
        std::string first = myPeptides.front()->ToString();
        std::string last = myPeptides.back()->ToString();

        std::string a = "PRO";
        std::string b = "PRPPM";
        Assert::AreEqual(first, a);
        Assert::AreEqual(last, b);

        delete myProtein;
        delete myDigestionParams;
        delete multiletter;
    }

    void TestDigestionMotif::TestMultiLetterProtease()
    {
        auto empty = std::vector<Modification*>();
        DigestionParams *myDigestionParams = new DigestionParams("collagenase", 0, 1, std::numeric_limits<int>::max() ,
                                                                 1024, InitiatorMethionineBehavior::Variable, 2,
                                                                 CleavageSpecificity::Full, FragmentationTerminus::Both);

        // create a protein
        Protein *myProtein = new Protein("ABCGPXGPMFKCGPMKK", "myAccession");

        // digest it into peptides
        auto myPeptides = myProtein->Digest(myDigestionParams, empty, empty);
        std::string first = myPeptides.front()->ToString();
        std::string last = myPeptides.back()->ToString();

        std::string a = "ABCGPX";
        std::string b = "GPMFKCGPMKK";
        Assert::AreEqual(first, a);
        Assert::AreEqual(last, b);

        delete myProtein;
        delete myDigestionParams;
    }

    void TestDigestionMotif::TestNTerminusProtease()
    {
        auto empty = std::vector<Modification*>();
        DigestionParams *myDigestionParams = new DigestionParams("Asp-N", 0, 1, std::numeric_limits<int>::max(), 1024,
                                                                 InitiatorMethionineBehavior::Variable, 2,
                                                                 CleavageSpecificity::Full, FragmentationTerminus::Both);

        // create a protein
        Protein *myProtein = new Protein("PADDMSKDPDMMAASMDJSSM", "myAccession");

        // digest it into peptides
        auto myPeptides = myProtein->Digest(myDigestionParams, empty, empty);
        std::string first = myPeptides.front()->ToString();
        std::string last = myPeptides.back()->ToString();

        std::string a = "PA";
        std::string b = "DJSSM";
        Assert::AreEqual(first, a);
        Assert::AreEqual(last, b);

        delete myProtein;
        delete myDigestionParams;
    }

#ifdef LATER
    void TestDigestionMotif::TestSyntax()
    {
        Assert::Throws<MzLibException*>([&] ()
        {
            auto protease = DigestionMotif::ParseDigestionMotifsFromString("X[Y,P]");
            Assert::Fail("Exception shold be thrown for incorrect syntax.");
        });
    }
#endif
}
