#ifndef BaseLabRunAction_h
#define BaseLabRunAction_h 1

#include "G4Accumulable.hh"
#include "G4UserRunAction.hh"

namespace BaseLab
{
class BaseLabDetectorConstruction;

class BaseLabRunAction : public G4UserRunAction
{
  public:
    explicit BaseLabRunAction(BaseLabDetectorConstruction* detectorConstruction = nullptr);
    ~BaseLabRunAction() override = default;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;
    void AddEventEnergyDeposit(G4double eventEnergyDeposit);
    G4double GetRunEnergyDeposit() const;

  private:
    BaseLabDetectorConstruction* fDetectorConstruction = nullptr;
    G4Accumulable<G4double> fRunEnergyDeposit = 0.0;
};

}  // namespace BaseLab

#endif
