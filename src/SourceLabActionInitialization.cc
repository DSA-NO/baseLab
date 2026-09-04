#include "SourceLabActionInitialization.hh"

#include "SourceLabDetectorConstruction.hh"
#include "SourceLabPrimaryGeneratorAction.hh"
#include "SourceLabRunAction.hh"
#include "SourceLabEventAction.hh"

namespace SourceLab
{

SourceLabActionInitialization::SourceLabActionInitialization(
  SourceLabDetectorConstruction* detectorConstruction)
: fDetectorConstruction(detectorConstruction)
{
}

void SourceLabActionInitialization::BuildForMaster() const
{
  SetUserAction(new SourceLabRunAction(fDetectorConstruction));
}

void SourceLabActionInitialization::Build() const
{
  auto* eventAction = new SourceLabEventAction;
  SetUserAction(new SourceLabPrimaryGeneratorAction(fDetectorConstruction));
  SetUserAction(new SourceLabRunAction(fDetectorConstruction, eventAction));
  SetUserAction(eventAction);
}

}  // namespace SourceLab
