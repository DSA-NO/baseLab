#ifndef BaseLabPrimaryGeneratorAction_h
#define BaseLabPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4Event;
class G4GeneralParticleSource;

namespace BaseLab
{
class BaseLabPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    BaseLabPrimaryGeneratorAction();
    ~BaseLabPrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event* event) override;

  private:
    G4GeneralParticleSource* fParticleSource = nullptr;
};

}  // namespace BaseLab

#endif
