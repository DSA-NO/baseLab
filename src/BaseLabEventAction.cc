#include "BaseLabEventAction.hh"

#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "G4VHitsCollection.hh"

namespace BaseLab
{

BaseLabEventAction::BaseLabEventAction() = default;

void BaseLabEventAction::Reset()
{
  fTotalEnergyDeposit = 0.0;
}

G4double BaseLabEventAction::GetTotalEnergyDeposit() const
{
  return fTotalEnergyDeposit;
}

void BaseLabEventAction::BeginOfEventAction(const G4Event*)
{
  Reset();
}

void BaseLabEventAction::EndOfEventAction(const G4Event* anEvent)
{
  auto* hce = anEvent->GetHCofThisEvent();
  if (!hce) {
    return;
  }

  const G4int collectionID = G4SDManager::GetSDMpointer()->GetCollectionID("SampleSD/eDep");
  auto* hc = hce->GetHC(collectionID);
  if (!hc) {
    return;
  }

  auto* hitsMap = dynamic_cast<G4THitsMap<G4double>*>(hc);
  if (!hitsMap) {
    return;
  }

  auto* map = hitsMap->GetMap();
  for (auto const& hit : *map) {
    fTotalEnergyDeposit += *(hit.second);
  }
}

}  // namespace BaseLab
