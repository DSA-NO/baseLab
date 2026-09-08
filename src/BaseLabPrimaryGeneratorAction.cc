#include "BaseLabPrimaryGeneratorAction.hh"

#include "G4GeneralParticleSource.hh"

namespace BaseLab
{

BaseLabPrimaryGeneratorAction::BaseLabPrimaryGeneratorAction()
{
  // GPS provides particle generation configured entirely through macros or UI commands.
  fParticleSource = new G4GeneralParticleSource();
}

BaseLabPrimaryGeneratorAction::~BaseLabPrimaryGeneratorAction()
{
  delete fParticleSource;
}

void BaseLabPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  fParticleSource->GeneratePrimaryVertex(event);
}

}  // namespace BaseLab
