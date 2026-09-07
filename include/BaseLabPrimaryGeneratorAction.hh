#ifndef BaseLabPrimaryGeneratorAction_h
#define BaseLabPrimaryGeneratorAction_h 1

#include "G4GeneralParticleSource.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

namespace BaseLab
{
class BaseLabPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    BaseLabPrimaryGeneratorAction();
    ~BaseLabPrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event* anEvent) override;

  private:
    G4GeneralParticleSource* fParticleSource = nullptr;
};

}  // namespace BaseLab

#endif
