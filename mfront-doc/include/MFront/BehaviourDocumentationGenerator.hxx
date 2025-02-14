/*!
 * \file  BehaviourDocumentationGenerator.hxx
 * \brief
 * \author Thomas Helfer
 * \date   04 mars 2015
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
 * reserved.
 * This project is publicly released under either the GNU GPL Licence
 * or the CECILL-A licence. A copy of thoses licences are delivered
 * with the sources of TFEL. CEA or EDF may also distribute this
 * project under specific licensing conditions.
 */

#ifndef LIB_MFRONT_BEHAVIOURDOCUMENTATIONGENERATOR_H
#define LIB_MFRONT_BEHAVIOURDOCUMENTATIONGENERATOR_H

#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <functional>

#include "TFEL/Utilities/ArgumentParserBase.hxx"
#include "TFEL/Material/ModellingHypothesis.hxx"
#include "MFront/MFrontBase.hxx"

namespace mfront {

  // forward declaration
  struct AbstractBehaviourDSL;
  // forward declaration
  struct BehaviourDescription;
  // forward declaration
  struct FileDescription;

  /*!
   * Class used by the mfront-query tool to extract information from
   * behaviour implementation
   */
  struct BehaviourDocumentationGenerator
      : public tfel::utilities::ArgumentParserBase<
            BehaviourDocumentationGenerator>,
        public MFrontBase {
    //! \brief type of documentation to be generated
    enum OutputType { FULL, WEB };
    /*!
     * build a BehaviourDocumentationGenerator object based on command line
     * arguments
     * \param[in] argc : number of command line arguments
     * \param[in] argv : command line arguments
     * \param[in] d    : behaviour domain specific language
     * \param[in] f    : behaviour domain specific language
     */
    BehaviourDocumentationGenerator(const int,
                                    const char *const *const,
                                    std::shared_ptr<AbstractBehaviourDSL>,
                                    const std::string &);
    //! treat the requests
    void exe();
    //! destructor
    ~BehaviourDocumentationGenerator() override;

   private:
    //! ArgumentParserBase must be a friend
    friend struct tfel::utilities::ArgumentParserBase<
        BehaviourDocumentationGenerator>;
    //! \brief register call-backs associated with command line arguments
    virtual void registerCommandLineCallBacks();
    //! treat the web argument
    virtual void treatWeb();
    virtual void writeWebOutput(std::ostream &,
                                const BehaviourDescription &,
                                const FileDescription &) const;
    virtual void writeFullOutput(std::ostream &,
                                 const BehaviourDescription &,
                                 const FileDescription &) const;
    //! return the current argument
    const tfel::utilities::Argument &getCurrentCommandLineArgument()
        const override final;
    //! treat an unknown argument
    void treatUnknownArgument() override final;
    //! get the version description
    std::string getVersionDescription() const override final;
    //! get the usage description
    std::string getUsageDescription() const override final;
    //! abstract behaviour dsl
    std::shared_ptr<AbstractBehaviourDSL> dsl;
    //! input file name
    std::string file;
    //! type of ouput
    OutputType otype;
    //! \brief generate output on standard output
    bool std_output = false;
    /*!
     * \brief boolean whose meaning is the following:
     * - if true, the generated documentation is contained in a whole document.
     * - if false, the generated documentation is contained in a section meant
     *   to be included in a bigger document.
     */
    bool standalone = false;
  };  // end of struct BehaviourDocumentationGenerator

}  // end of namespace mfront

#endif /* LIB_MFRONT_BEHAVIOURDOCUMENTATIONGENERATOR_H */
