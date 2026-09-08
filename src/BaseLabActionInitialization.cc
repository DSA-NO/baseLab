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
  SetUserAction(new BaseLabPrimaryGeneratorAction());
  auto* runAction = new BaseLabRunAction(fDetectorConstruction);
  SetUserAction(runAction);
  SetUserAction(new BaseLabEventAction(runAction));
}

}  // namespace BaseLab
