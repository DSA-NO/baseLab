#ifndef BaseLabEventAction_h
#define BaseLabEventAction_h 1

#include "G4SystemOfUnits.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"

namespace BaseLab
{
class BaseLabRunAction;

class BaseLabEventAction : public G4UserEventAction
{
  public:
    explicit BaseLabEventAction(BaseLabRunAction* runAction = nullptr);
    ~BaseLabEventAction() override = default;

    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;

    void ResetEvent();
    G4double GetEventEnergyDeposit() const;

  private:
    BaseLabRunAction* fRunAction = nullptr;
    G4int fSampleEdepCollectionID = -1;
    G4double fEventEnergyDeposit = 0.0;
};

}  // namespace BaseLab

#endif
