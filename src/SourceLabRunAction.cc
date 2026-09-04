#include "SourceLabRunAction.hh"

#include "SourceLabDetectorConstruction.hh"
#include "SourceLabEventAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

namespace SourceLab
{

SourceLabRunAction::SourceLabRunAction(SourceLabDetectorConstruction* detectorConstruction,
  SourceLabEventAction* eventAction)
: fDetectorConstruction(detectorConstruction), fEventAction(eventAction)
{
}

void SourceLabRunAction::BeginOfRunAction(const G4Run*)
{
  G4cout << "Starting run." << G4endl;
  if (fDetectorConstruction) {
    G4cout << "World size: " << fDetectorConstruction->GetWorldSize() / m << " m" << G4endl;
    G4cout << "Sample depth: " << fDetectorConstruction->GetSampleDepth() / cm << " cm" << G4endl;
  }
  if (fEventAction) {
    fEventAction->Reset();
  }
}

void SourceLabRunAction::EndOfRunAction(const G4Run* run)
{
  G4cout << "Run summary: " << run->GetNumberOfEvent() << " events" << G4endl;
  if (fEventAction) {
    G4cout << "Total energy deposit in sample: " << fEventAction->GetTotalEnergyDeposit() / MeV << " MeV"
           << G4endl;
  }
}

}  // namespace SourceLab
