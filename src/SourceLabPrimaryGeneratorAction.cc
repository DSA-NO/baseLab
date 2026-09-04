#include "SourceLabPrimaryGeneratorAction.hh"

#include "SourceLabDetectorConstruction.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

namespace SourceLab
{

SourceLabPrimaryGeneratorAction::SourceLabPrimaryGeneratorAction(
  SourceLabDetectorConstruction* detectorConstruction)
: fDetectorConstruction(detectorConstruction)
{
  fParticleGun = new G4ParticleGun(1);
  auto* particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  if (particle) {
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(1.25 * MeV);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -0.75 * m));
  }
}

SourceLabPrimaryGeneratorAction::~SourceLabPrimaryGeneratorAction()
{
  delete fParticleGun;
}

void SourceLabPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  if (!fParticleGun) {
    return;
  }

  if (fDetectorConstruction) {
    const auto config = fDetectorConstruction->GetConfig();
    auto* particle = G4ParticleTable::GetParticleTable()->FindParticle(config.sourceParticle);
    if (particle) {
      fParticleGun->SetParticleDefinition(particle);
    }
    fParticleGun->SetParticleEnergy(config.sourceEnergy);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -0.75 * m));
  }

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

}  // namespace SourceLab
