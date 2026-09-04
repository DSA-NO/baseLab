#ifndef BaseLabPrimaryGeneratorAction_h
#define BaseLabPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

namespace BaseLab
{
class BaseLabDetectorConstruction;

class BaseLabPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    explicit BaseLabPrimaryGeneratorAction(BaseLabDetectorConstruction* detectorConstruction = nullptr);
    ~BaseLabPrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event* anEvent) override;

  private:
    BaseLabDetectorConstruction* fDetectorConstruction = nullptr;
    G4ParticleGun* fParticleGun = nullptr;
};

}  // namespace BaseLab

#endif
