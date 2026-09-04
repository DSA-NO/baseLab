#ifndef BaseLabDetectorMessenger_h
#define BaseLabDetectorMessenger_h 1

#include "G4UImessenger.hh"

class G4UIcmdWithADoubleAndUnit;
class G4UIcommand;

namespace BaseLab
{
class BaseLabDetectorConstruction;

class BaseLabDetectorMessenger : public G4UImessenger
{
  public:
    explicit BaseLabDetectorMessenger(BaseLabDetectorConstruction* detector);
    ~BaseLabDetectorMessenger() override;

    void SetNewValue(G4UIcommand* command, G4String newValue) override;
    G4String GetCurrentValue(G4UIcommand* command) override;

  private:
    BaseLabDetectorConstruction* fDetector = nullptr;

    // Generic geometry commands.
    G4UIcmdWithADoubleAndUnit* fSetWorldSizeCmd = nullptr;
    G4UIcmdWithADoubleAndUnit* fSetPhantomHalfXCmd = nullptr;
    G4UIcmdWithADoubleAndUnit* fSetPhantomHalfYCmd = nullptr;
    G4UIcmdWithADoubleAndUnit* fSetPhantomHalfZCmd = nullptr;
    G4UIcmdWithADoubleAndUnit* fSetSampleDepthCmd = nullptr;
    G4UIcmdWithADoubleAndUnit* fSetSampleRadiusCmd = nullptr;
    G4UIcmdWithADoubleAndUnit* fSetSampleThicknessCmd = nullptr;

    // Generic source commands.
    G4UIcmdWithADoubleAndUnit* fSetSourceEnergyCmd = nullptr;
    G4UIcommand* fSetParticleNameCmd = nullptr;
    G4UIcommand* fUpdateCmd = nullptr;
    G4UIcommand* fPrintCmd = nullptr;

    // Compatibility aliases for the legacy commands used by the earlier app build.
    G4UIcmdWithADoubleAndUnit* fSetWorldSizeLegacyCmd = nullptr;
    G4UIcmdWithADoubleAndUnit* fSetSampleDepthLegacyCmd = nullptr;
    G4UIcmdWithADoubleAndUnit* fSetSampleRadiusLegacyCmd = nullptr;
    G4UIcmdWithADoubleAndUnit* fSetSampleThicknessLegacyCmd = nullptr;
    G4UIcmdWithADoubleAndUnit* fSetSourceEnergyLegacyCmd = nullptr;
    G4UIcommand* fSetParticleNameLegacyCmd = nullptr;
};

}  // namespace BaseLab

#endif
