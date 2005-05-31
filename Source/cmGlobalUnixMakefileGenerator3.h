/*=========================================================================

  Program:   CMake - Cross-Platform Makefile Generator3
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2005 Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef cmGlobalUnixMakefileGenerator3_h
#define cmGlobalUnixMakefileGenerator3_h

#include "cmGlobalGenerator.h"

class cmGeneratedFileStream;
class cmLocalUnixMakefileGenerator3;

/** \class cmGlobalUnixMakefileGenerator3
 * \brief Write a Unix makefiles.
 *
 * cmGlobalUnixMakefileGenerator3 manages UNIX build process for a tree
 */
class cmGlobalUnixMakefileGenerator3 : public cmGlobalGenerator
{
public:
  cmGlobalUnixMakefileGenerator3();
  static cmGlobalGenerator* New() { return new cmGlobalUnixMakefileGenerator3; }

  ///! Get the name for the generator.
  virtual const char* GetName() const {
    return cmGlobalUnixMakefileGenerator3::GetActualName();}
  static const char* GetActualName() {return "Unix Makefiles";}

  /** Get the documentation entry for this generator.  */
  virtual void GetDocumentation(cmDocumentationEntry& entry) const;
  
  ///! Create a local generator appropriate to this Global Generator3
  virtual cmLocalGenerator *CreateLocalGenerator();

  /**
   * Try to determine system infomation such as shared library
   * extension, pthreads, byte order etc.  
   */
  virtual void EnableLanguage(std::vector<std::string>const& languages, cmMakefile *);

  /**
   * Generate the all required files for building this project/tree. This
   * basically creates a series of LocalGenerators for each directory and
   * requests that they Generate.  
   */
  virtual void Generate();

protected:
  void WriteMainMakefile();
  void WriteMainCMakefile();
  void WriteMainCMakefileLanguageRules(cmGeneratedFileStream& cmakefileStream);
  void WriteAllRules(cmLocalUnixMakefileGenerator3 *lg, 
                     std::ostream& makefileStream);
  void WriteHelpRule(std::ostream& ruleFileStream);
  
  void WriteConvenienceRules(std::ostream& ruleFileStream, 
                             cmLocalUnixMakefileGenerator3 *,
                             bool exclude);
  void WriteDirectoryRules(std::ostream& ruleFileStream, 
                           cmLocalUnixMakefileGenerator3 *lg);

  void AppendGlobalTargetDepends(std::vector<std::string>& depends,
                                 const cmTarget& target);
  void AppendAnyGlobalDepend(std::vector<std::string>& depends, const char* name);

  // does this generator need a requires step for any of its targets
  bool NeedRequiresStep(cmLocalUnixMakefileGenerator3 *lg);

};

#endif
