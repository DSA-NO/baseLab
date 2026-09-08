#include "BaseLabRunAction.hh"

#include "BaseLabDetectorConstruction.hh"

#include "G4AccumulableManager.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"

namespace BaseLab
{

BaseLabRunAction::BaseLabRunAction(BaseLabDetectorConstruction* detectorConstruction)
: fDetectorConstruction(detectorConstruction)
{
  auto* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Register(fRunEnergyDeposit);

  auto* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
  analysisManager->CreateH1("Edep", "Energy deposit in sample", 100, 0., 10 * MeV);
  fSampleNtupleId = analysisManager->CreateNtuple("sample", "Sample energy deposit per event");
  analysisManager->CreateNtupleDColumn("Edep");
  analysisManager->FinishNtuple(fSampleNtupleId);

  fRunNtupleId = analysisManager->CreateNtuple("run", "Run-level sample summary");
  analysisManager->CreateNtupleIColumn("Events");
  analysisManager->CreateNtupleDColumn("RunEdep");
  analysisManager->CreateNtupleIColumn("ThreadId");
  analysisManager->FinishNtuple(fRunNtupleId);
}

void BaseLabRunAction::BeginOfRunAction(const G4Run*)
{
  auto* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

  auto* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Reset();
  analysisManager->OpenFile("baseLab.root");

  if (isMaster) {
    G4cout << "Starting run." << G4endl;
    if (fDetectorConstruction) {
      G4cout << "World size: " << fDetectorConstruction->GetWorldSize() / m << " m" << G4endl;
      G4cout << "Sample depth: " << fDetectorConstruction->GetSampleDepth() / cm << " cm" << G4endl;
    }
  }
}

void BaseLabRunAction::EndOfRunAction(const G4Run* run)
{
  auto* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  auto* analysisManager = G4AnalysisManager::Instance();
  const auto writeRunRow = !G4Threading::IsMultithreadedApplication() || !isMaster;
  if (writeRunRow && fRunNtupleId >= 0) {
    analysisManager->FillNtupleIColumn(fRunNtupleId, 0, run->GetNumberOfEvent());
    analysisManager->FillNtupleDColumn(fRunNtupleId, 1, GetRunEnergyDeposit());
    analysisManager->FillNtupleIColumn(fRunNtupleId, 2, G4Threading::G4GetThreadId());
    analysisManager->AddNtupleRow(fRunNtupleId);
  }
  analysisManager->Write();
  analysisManager->CloseFile(false);

  if (isMaster) {
    G4cout << "Run summary: " << run->GetNumberOfEvent() << " events" << G4endl;
    G4cout << "Total energy deposit in sample: " << GetRunEnergyDeposit() / MeV << " MeV" << G4endl;
  }
}

void BaseLabRunAction::AddEventEnergyDeposit(G4double eventEnergyDeposit)
{
  fRunEnergyDeposit += eventEnergyDeposit;
}

G4double BaseLabRunAction::GetRunEnergyDeposit() const
{
  return fRunEnergyDeposit.GetValue();
}

G4int BaseLabRunAction::GetSampleNtupleId() const
{
  return fSampleNtupleId;
}

}  // namespace BaseLab
