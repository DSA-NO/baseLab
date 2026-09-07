#include "BaseLabDetectorMessenger.hh"

#include "BaseLabDetectorConstruction.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

namespace BaseLab
{
BaseLabDetectorMessenger::BaseLabDetectorMessenger(BaseLabDetectorConstruction* detector)
: fDetector(detector)
{
  auto* geomDir = new G4UIdirectory("/baseLab/geometry/");
  geomDir->SetGuidance("Generic geometry controls");

  auto* rootDir = new G4UIdirectory("/baseLab/");
  rootDir->SetGuidance("baseLab controls");

  fSetWorldSizeCmd = new G4UIcmdWithADoubleAndUnit("/baseLab/geometry/worldSize", this);
  fSetWorldSizeCmd->SetGuidance("Set the world size");
  fSetWorldSizeCmd->SetParameterName("size", false);
  fSetWorldSizeCmd->SetDefaultUnit("m");

  fSetPhantomHalfXCmd = new G4UIcmdWithADoubleAndUnit("/baseLab/geometry/phantomHalfX", this);
  fSetPhantomHalfXCmd->SetGuidance("Set half-size of the phantom in x");
  fSetPhantomHalfXCmd->SetParameterName("x", false);
  fSetPhantomHalfXCmd->SetDefaultUnit("m");

  fSetPhantomHalfYCmd = new G4UIcmdWithADoubleAndUnit("/baseLab/geometry/phantomHalfY", this);
  fSetPhantomHalfYCmd->SetGuidance("Set half-size of the phantom in y");
  fSetPhantomHalfYCmd->SetParameterName("y", false);
  fSetPhantomHalfYCmd->SetDefaultUnit("m");

  fSetPhantomHalfZCmd = new G4UIcmdWithADoubleAndUnit("/baseLab/geometry/phantomHalfZ", this);
  fSetPhantomHalfZCmd->SetGuidance("Set half-size of the phantom in z");
  fSetPhantomHalfZCmd->SetParameterName("z", false);
  fSetPhantomHalfZCmd->SetDefaultUnit("m");

  fSetSampleDepthCmd = new G4UIcmdWithADoubleAndUnit("/baseLab/geometry/sampleDepth", this);
  fSetSampleDepthCmd->SetGuidance("Set the sample depth in the phantom");
  fSetSampleDepthCmd->SetParameterName("depth", false);
  fSetSampleDepthCmd->SetDefaultUnit("cm");

  fSetSampleRadiusCmd = new G4UIcmdWithADoubleAndUnit("/baseLab/geometry/sampleRadius", this);
  fSetSampleRadiusCmd->SetGuidance("Set the sample radius");
  fSetSampleRadiusCmd->SetParameterName("radius", false);
  fSetSampleRadiusCmd->SetDefaultUnit("cm");

  fSetSampleThicknessCmd = new G4UIcmdWithADoubleAndUnit("/baseLab/geometry/sampleThickness", this);
  fSetSampleThicknessCmd->SetGuidance("Set the sample thickness");
  fSetSampleThicknessCmd->SetParameterName("thickness", false);
  fSetSampleThicknessCmd->SetDefaultUnit("mm");

  fUpdateCmd = new G4UIcommand("/baseLab/update", this);
  fUpdateCmd->SetGuidance("Update geometry values. Apply this before /run/initialize.");

  fPrintCmd = new G4UIcommand("/baseLab/print", this);
  fPrintCmd->SetGuidance("Print the current generic detector configuration.");
}

BaseLabDetectorMessenger::~BaseLabDetectorMessenger()
{
  delete fSetWorldSizeCmd;
  delete fSetPhantomHalfXCmd;
  delete fSetPhantomHalfYCmd;
  delete fSetPhantomHalfZCmd;
  delete fSetSampleDepthCmd;
  delete fSetSampleRadiusCmd;
  delete fSetSampleThicknessCmd;
  delete fUpdateCmd;
  delete fPrintCmd;
}

void BaseLabDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == fSetWorldSizeCmd) {
    fDetector->SetWorldSize(fSetWorldSizeCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fSetPhantomHalfXCmd) {
    fDetector->SetPhantomHalfSize(fSetPhantomHalfXCmd->GetNewDoubleValue(newValue),
      fDetector->GetWorldSize(),
      fDetector->GetSampleDepth());
  }
  else if (command == fSetPhantomHalfYCmd) {
    fDetector->SetPhantomHalfSize(fDetector->GetWorldSize(),
      fSetPhantomHalfYCmd->GetNewDoubleValue(newValue),
      fDetector->GetSampleDepth());
  }
  else if (command == fSetPhantomHalfZCmd) {
    fDetector->SetPhantomHalfSize(fDetector->GetWorldSize(),
      fDetector->GetSampleDepth(),
      fSetPhantomHalfZCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fSetSampleDepthCmd) {
    fDetector->SetSampleDepth(fSetSampleDepthCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fSetSampleRadiusCmd) {
    fDetector->SetSampleSize(fSetSampleRadiusCmd->GetNewDoubleValue(newValue),
      fDetector->GetSampleThickness());
  }
  else if (command == fSetSampleThicknessCmd) {
    fDetector->SetSampleSize(fDetector->GetSampleRadius(),
      fSetSampleThicknessCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fUpdateCmd) {
    G4cout << "baseLab configuration updated; apply before /run/initialize." << G4endl;
  }
  else if (command == fPrintCmd || command->GetCommandPath() == "/baseLab/print") {
    fDetector->PrintConfig();
  }
}

G4String BaseLabDetectorMessenger::GetCurrentValue(G4UIcommand* command)
{
  if (command == fSetWorldSizeCmd) {
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
  if (command == fSetSampleDepthCmd) {
    return G4UIcommand::ConvertToString(fDetector->GetSampleDepth(), "cm");
  }
  if (command == fSetSampleRadiusCmd) {
    return G4UIcommand::ConvertToString(fDetector->GetSampleRadius(), "cm");
  }
  if (command == fSetSampleThicknessCmd) {
    return G4UIcommand::ConvertToString(fDetector->GetSampleThickness(), "mm");
  }
  return "";
}

}  // namespace BaseLab
