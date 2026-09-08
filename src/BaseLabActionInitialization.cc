#include "BaseLabActionInitialization.hh"

#include "BaseLabDetectorConstruction.hh"
#include "BaseLabPrimaryGeneratorAction.hh"
#include "BaseLabRunAction.hh"
#include "BaseLabEventAction.hh"

namespace BaseLab
{

BaseLabActionInitialization::BaseLabActionInitialization(
  BaseLabDetectorConstruction* detectorConstruction,
  const G4String& emModel,
  G4bool enableRadioactiveDecay)
: fDetectorConstruction(detectorConstruction)
, fEmModel(emModel)
, fEnableRadioactiveDecay(enableRadioactiveDecay)
{
}

void BaseLabActionInitialization::BuildForMaster() const
{
  SetUserAction(new BaseLabRunAction(fDetectorConstruction, fEmModel, fEnableRadioactiveDecay));
}

void BaseLabActionInitialization::Build() const
{
  SetUserAction(new BaseLabPrimaryGeneratorAction());
  auto* runAction = new BaseLabRunAction(fDetectorConstruction, fEmModel, fEnableRadioactiveDecay);
  SetUserAction(runAction);
  SetUserAction(new BaseLabEventAction(runAction));
}

}  // namespace BaseLab
