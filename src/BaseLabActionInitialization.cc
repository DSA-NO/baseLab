#include "BaseLabActionInitialization.hh"

#include "BaseLabDetectorConstruction.hh"
#include "BaseLabPrimaryGeneratorAction.hh"
#include "BaseLabRunAction.hh"
#include "BaseLabEventAction.hh"

namespace BaseLab
{

BaseLabActionInitialization::BaseLabActionInitialization(
  BaseLabDetectorConstruction* detectorConstruction)
: fDetectorConstruction(detectorConstruction)
{
}

void BaseLabActionInitialization::BuildForMaster() const
{
  SetUserAction(new BaseLabRunAction(fDetectorConstruction));
}

void BaseLabActionInitialization::Build() const
{
  SetUserAction(new BaseLabPrimaryGeneratorAction(fDetectorConstruction));
  auto* eventAction = new BaseLabEventAction;
  SetUserAction(eventAction);
  SetUserAction(new BaseLabRunAction(fDetectorConstruction));
}

}  // namespace BaseLab
