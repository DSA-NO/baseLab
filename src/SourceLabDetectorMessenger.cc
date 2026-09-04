#include "SourceLabDetectorMessenger.hh"

#include "SourceLabDetectorConstruction.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIparameter.hh"
#include "G4UIdirectory.hh"

namespace SourceLab
{
namespace
{
G4double GetDoubleValueFromCommand(G4UIcmdWithADoubleAndUnit* primaryCmd,
  G4UIcmdWithADoubleAndUnit* legacyCmd,
  G4UIcommand* command,
  const G4String& newValue)
{
  if (command == legacyCmd && legacyCmd) {
    return legacyCmd->GetNewDoubleValue(newValue);
  }
  if (primaryCmd) {
    return primaryCmd->GetNewDoubleValue(newValue);
  }
  return 0.0;
}
}

SourceLabDetectorMessenger::SourceLabDetectorMessenger(SourceLabDetectorConstruction* detector)
: fDetector(detector)
{
  auto* geomDir = new G4UIdirectory("/sourceLab/geometry/");
  geomDir->SetGuidance("Generic geometry controls");

  auto* sourceDir = new G4UIdirectory("/sourceLab/source/");
  sourceDir->SetGuidance("Generic source controls");

  auto* rootDir = new G4UIdirectory("/sourceLab/");
  rootDir->SetGuidance("sourceLab controls");

  fSetWorldSizeCmd = new G4UIcmdWithADoubleAndUnit("/sourceLab/geometry/worldSize", this);
  fSetWorldSizeCmd->SetGuidance("Set the world size");
  fSetWorldSizeCmd->SetParameterName("size", false);
  fSetWorldSizeCmd->SetDefaultUnit("m");

  fSetPhantomHalfXCmd = new G4UIcmdWithADoubleAndUnit("/sourceLab/geometry/phantomHalfX", this);
  fSetPhantomHalfXCmd->SetGuidance("Set half-size of the phantom in x");
  fSetPhantomHalfXCmd->SetParameterName("x", false);
  fSetPhantomHalfXCmd->SetDefaultUnit("m");

  fSetPhantomHalfYCmd = new G4UIcmdWithADoubleAndUnit("/sourceLab/geometry/phantomHalfY", this);
  fSetPhantomHalfYCmd->SetGuidance("Set half-size of the phantom in y");
  fSetPhantomHalfYCmd->SetParameterName("y", false);
  fSetPhantomHalfYCmd->SetDefaultUnit("m");

  fSetPhantomHalfZCmd = new G4UIcmdWithADoubleAndUnit("/sourceLab/geometry/phantomHalfZ", this);
  fSetPhantomHalfZCmd->SetGuidance("Set half-size of the phantom in z");
  fSetPhantomHalfZCmd->SetParameterName("z", false);
  fSetPhantomHalfZCmd->SetDefaultUnit("m");

  fSetSampleDepthCmd = new G4UIcmdWithADoubleAndUnit("/sourceLab/geometry/sampleDepth", this);
  fSetSampleDepthCmd->SetGuidance("Set the sample depth in the phantom");
  fSetSampleDepthCmd->SetParameterName("depth", false);
  fSetSampleDepthCmd->SetDefaultUnit("cm");

  fSetSampleRadiusCmd = new G4UIcmdWithADoubleAndUnit("/sourceLab/geometry/sampleRadius", this);
  fSetSampleRadiusCmd->SetGuidance("Set the sample radius");
  fSetSampleRadiusCmd->SetParameterName("radius", false);
  fSetSampleRadiusCmd->SetDefaultUnit("cm");

  fSetSampleThicknessCmd = new G4UIcmdWithADoubleAndUnit("/sourceLab/geometry/sampleThickness", this);
  fSetSampleThicknessCmd->SetGuidance("Set the sample thickness");
  fSetSampleThicknessCmd->SetParameterName("thickness", false);
  fSetSampleThicknessCmd->SetDefaultUnit("mm");

  fSetSourceEnergyCmd = new G4UIcmdWithADoubleAndUnit("/sourceLab/source/energy", this);
  fSetSourceEnergyCmd->SetGuidance("Set the primary source energy");
  fSetSourceEnergyCmd->SetParameterName("energy", false);
  fSetSourceEnergyCmd->SetDefaultUnit("MeV");

  fSetParticleNameCmd = new G4UIcommand("/sourceLab/source/particle", this);
  fSetParticleNameCmd->SetGuidance("Set the primary particle type");
  auto* particleName = new G4UIparameter("particle", 's', false);
  particleName->SetDefaultValue("gamma");
  fSetParticleNameCmd->SetParameter(particleName);

  fUpdateCmd = new G4UIcommand("/sourceLab/update", this);
  fUpdateCmd->SetGuidance("Update geometry values. Apply this before /run/initialize.");

  fPrintCmd = new G4UIcommand("/sourceLab/print", this);
  fPrintCmd->SetGuidance("Print the current generic detector configuration.");

  // Legacy aliases retained for compatibility with the earlier project macros.
  fSetWorldSizeLegacyCmd = new G4UIcmdWithADoubleAndUnit("/sourceLab/setWorldSize", this);
  fSetWorldSizeLegacyCmd->SetGuidance("Legacy alias for /sourceLab/geometry/worldSize");
  fSetWorldSizeLegacyCmd->SetParameterName("size", false);
  fSetWorldSizeLegacyCmd->SetDefaultUnit("m");

  fSetSampleDepthLegacyCmd = new G4UIcmdWithADoubleAndUnit("/sourceLab/setSampleDepth", this);
  fSetSampleDepthLegacyCmd->SetGuidance("Legacy alias for /sourceLab/geometry/sampleDepth");
  fSetSampleDepthLegacyCmd->SetParameterName("depth", false);
  fSetSampleDepthLegacyCmd->SetDefaultUnit("cm");

  fSetSampleRadiusLegacyCmd = new G4UIcmdWithADoubleAndUnit("/sourceLab/setSampleRadius", this);
  fSetSampleRadiusLegacyCmd->SetGuidance("Legacy alias for /sourceLab/geometry/sampleRadius");
  fSetSampleRadiusLegacyCmd->SetParameterName("radius", false);
  fSetSampleRadiusLegacyCmd->SetDefaultUnit("cm");

  fSetSampleThicknessLegacyCmd = new G4UIcmdWithADoubleAndUnit("/sourceLab/setSampleThickness", this);
  fSetSampleThicknessLegacyCmd->SetGuidance("Legacy alias for /sourceLab/geometry/sampleThickness");
  fSetSampleThicknessLegacyCmd->SetParameterName("thickness", false);
  fSetSampleThicknessLegacyCmd->SetDefaultUnit("mm");

  fSetSourceEnergyLegacyCmd = new G4UIcmdWithADoubleAndUnit("/sourceLab/setSourceEnergy", this);
  fSetSourceEnergyLegacyCmd->SetGuidance("Legacy alias for /sourceLab/source/energy");
  fSetSourceEnergyLegacyCmd->SetParameterName("energy", false);
  fSetSourceEnergyLegacyCmd->SetDefaultUnit("MeV");

  fSetParticleNameLegacyCmd = new G4UIcommand("/sourceLab/setParticle", this);
  fSetParticleNameLegacyCmd->SetGuidance("Legacy alias for /sourceLab/source/particle");
  auto* legacyParticleName = new G4UIparameter("particle", 's', false);
  legacyParticleName->SetDefaultValue("gamma");
  fSetParticleNameLegacyCmd->SetParameter(legacyParticleName);
}

SourceLabDetectorMessenger::~SourceLabDetectorMessenger()
{
  delete fSetWorldSizeCmd;
  delete fSetPhantomHalfXCmd;
  delete fSetPhantomHalfYCmd;
  delete fSetPhantomHalfZCmd;
  delete fSetSampleDepthCmd;
  delete fSetSampleRadiusCmd;
  delete fSetSampleThicknessCmd;
  delete fSetSourceEnergyCmd;
  delete fSetParticleNameCmd;
  delete fUpdateCmd;
  delete fPrintCmd;

  delete fSetWorldSizeLegacyCmd;
  delete fSetSampleDepthLegacyCmd;
  delete fSetSampleRadiusLegacyCmd;
  delete fSetSampleThicknessLegacyCmd;
  delete fSetSourceEnergyLegacyCmd;
  delete fSetParticleNameLegacyCmd;
}

void SourceLabDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == fSetWorldSizeCmd || command == fSetWorldSizeLegacyCmd) {
    fDetector->SetWorldSize(GetDoubleValueFromCommand(fSetWorldSizeCmd, fSetWorldSizeLegacyCmd, command, newValue));
  }
  else if (command == fSetPhantomHalfXCmd) {
    fDetector->SetPhantomHalfSize(GetDoubleValueFromCommand(fSetPhantomHalfXCmd, nullptr, command, newValue),
      fDetector->GetWorldSize(),
      fDetector->GetSampleDepth());
  }
  else if (command == fSetPhantomHalfYCmd) {
    fDetector->SetPhantomHalfSize(fDetector->GetWorldSize(),
      GetDoubleValueFromCommand(fSetPhantomHalfYCmd, nullptr, command, newValue),
      fDetector->GetSampleDepth());
  }
  else if (command == fSetPhantomHalfZCmd) {
    fDetector->SetPhantomHalfSize(fDetector->GetWorldSize(),
      fDetector->GetSampleDepth(),
      GetDoubleValueFromCommand(fSetPhantomHalfZCmd, nullptr, command, newValue));
  }
  else if (command == fSetSampleDepthCmd || command == fSetSampleDepthLegacyCmd) {
    fDetector->SetSampleDepth(GetDoubleValueFromCommand(fSetSampleDepthCmd, fSetSampleDepthLegacyCmd, command, newValue));
  }
  else if (command == fSetSampleRadiusCmd || command == fSetSampleRadiusLegacyCmd) {
    fDetector->SetSampleSize(GetDoubleValueFromCommand(fSetSampleRadiusCmd, fSetSampleRadiusLegacyCmd, command, newValue),
      fDetector->GetSampleThickness());
  }
  else if (command == fSetSampleThicknessCmd || command == fSetSampleThicknessLegacyCmd) {
    fDetector->SetSampleSize(fDetector->GetSampleRadius(),
      GetDoubleValueFromCommand(fSetSampleThicknessCmd, fSetSampleThicknessLegacyCmd, command, newValue));
  }
  else if (command == fSetSourceEnergyCmd || command == fSetSourceEnergyLegacyCmd) {
    fDetector->SetSourceEnergy(GetDoubleValueFromCommand(fSetSourceEnergyCmd, fSetSourceEnergyLegacyCmd, command, newValue));
  }
  else if (command == fSetParticleNameCmd || command == fSetParticleNameLegacyCmd) {
    fDetector->SetSourceParticle(newValue);
  }
  else if (command == fUpdateCmd) {
    G4cout << "sourceLab configuration updated; apply before /run/initialize." << G4endl;
  }
  else if (command == fPrintCmd || command->GetCommandPath() == "/sourceLab/print") {
    fDetector->PrintConfig();
  }
}

G4String SourceLabDetectorMessenger::GetCurrentValue(G4UIcommand* command)
{
  if (command == fSetWorldSizeCmd || command == fSetWorldSizeLegacyCmd) {
    return G4UIcommand::ConvertToString(fDetector->GetWorldSize(), "m");
  }
  if (command == fSetPhantomHalfXCmd) {
    return G4UIcommand::ConvertToString(fDetector->GetConfig().phantomHalfX, "m");
  }
  if (command == fSetPhantomHalfYCmd) {
    return G4UIcommand::ConvertToString(fDetector->GetConfig().phantomHalfY, "m");
  }
  if (command == fSetPhantomHalfZCmd) {
    return G4UIcommand::ConvertToString(fDetector->GetConfig().phantomHalfZ, "m");
  }
  if (command == fSetSampleDepthCmd || command == fSetSampleDepthLegacyCmd) {
    return G4UIcommand::ConvertToString(fDetector->GetSampleDepth(), "cm");
  }
  if (command == fSetSampleRadiusCmd || command == fSetSampleRadiusLegacyCmd) {
    return G4UIcommand::ConvertToString(fDetector->GetSampleRadius(), "cm");
  }
  if (command == fSetSampleThicknessCmd || command == fSetSampleThicknessLegacyCmd) {
    return G4UIcommand::ConvertToString(fDetector->GetSampleThickness(), "mm");
  }
  if (command == fSetSourceEnergyCmd || command == fSetSourceEnergyLegacyCmd) {
    return G4UIcommand::ConvertToString(fDetector->GetSourceEnergy(), "MeV");
  }
  if (command == fSetParticleNameCmd || command == fSetParticleNameLegacyCmd) {
    return fDetector->GetSourceParticle();
  }
  return "";
}

}  // namespace SourceLab
