#ifndef BaseLabOutput_h
#define BaseLabOutput_h 1

#include "globals.hh"

#include <filesystem>

namespace BaseLab
{
namespace Output
{
void Initialize(const std::filesystem::path& sourceDirectory);
G4String RunFile(G4bool isMaster, G4int runId, const G4String& fileName);
}
}

#endif
