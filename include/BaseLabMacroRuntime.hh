// Resolves macro execution working directories and normalizes macro paths.
// baseLab - Geant4 dose calculation application

#ifndef BaseLabMacroRuntime_h
#define BaseLabMacroRuntime_h 1

#include "globals.hh"

namespace BaseLab
{
namespace MacroRuntime
{

struct RuntimeMacroConfig
{
  G4String batchMacroArg;
  G4String visMacroArg;
  G4String workingDirectory;
};

RuntimeMacroConfig ResolveRuntimeMacroConfig(char** argv,
                                             const G4String& macro,
                                             const G4String& visMacro);

G4bool ApplyWorkingDirectory(const RuntimeMacroConfig& config, G4String& warning);

}  // namespace MacroRuntime
}  // namespace BaseLab

#endif