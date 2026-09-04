#include "BaseLabRunAction.hh"

#include "BaseLabDetectorConstruction.hh"
#include "BaseLabEventAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

namespace BaseLab
{

BaseLabRunAction::BaseLabRunAction(BaseLabDetectorConstruction* detectorConstruction)
: fDetectorConstruction(detectorConstruction)
{
}

void BaseLabRunAction::BeginOfRunAction(const G4Run*)
{
  G4cout << "Starting run." << G4endl;
  if (fDetectorConstruction) {
    G4cout << "World size: " << fDetectorConstruction->GetWorldSize() / m << " m" << G4endl;
    G4cout << "Sample depth: " << fDetectorConstruction->GetSampleDepth() / cm << " cm" << G4endl;
  }

  const auto* eventActionConst = dynamic_cast<const BaseLabEventAction*>(
    G4RunManager::GetRunManager()->GetUserEventAction());
  if (eventActionConst) {
    auto* eventAction = const_cast<BaseLabEventAction*>(eventActionConst);
    eventAction->Reset();
  }
}

void BaseLabRunAction::EndOfRunAction(const G4Run* run)
{
  G4cout << "Run summary: " << run->GetNumberOfEvent() << " events" << G4endl;

  const auto* eventActionConst = dynamic_cast<const BaseLabEventAction*>(
    G4RunManager::GetRunManager()->GetUserEventAction());
  if (eventActionConst) {
    G4cout << "Total energy deposit in sample: " << eventActionConst->GetTotalEnergyDeposit() / MeV << " MeV"
           << G4endl;
  }
}

}  // namespace BaseLab
